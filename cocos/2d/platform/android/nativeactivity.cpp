/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "nativeactivity.h"

#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/configuration.h>

#include <pthread.h>
#include <chrono>

#include "CCDirector.h"
#include "CCApplication.h"
#include "CCEventType.h"
#include "CCFileUtilsAndroid.h"
#include "jni/JniHelper.h"

#include "CCGLView.h"
#include "CCDrawingPrimitives.h"
#include "CCShaderCache.h"
#include "CCTextureCache.h"
#include "CCEventDispatcher.h"
#include "CCEventAcceleration.h"
#include "CCEventKeyboard.h"
#include "CCEventCustom.h"

#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "cocos2dx/nativeactivity.cpp", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "cocos2dx/nativeactivity.cpp", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "cocos2dx/nativeactivity.cpp", __VA_ARGS__))

#define LOG_RENDER_DEBUG(...)
// #define LOG_RENDER_DEBUG(...)  ((void)__android_log_print(ANDROID_LOG_INFO, "cocos2dx/nativeactivity.cpp", __VA_ARGS__))

#define LOG_EVENTS_DEBUG(...)
// #define LOG_EVENTS_DEBUG(...)  ((void)__android_log_print(ANDROID_LOG_INFO, "cocos2dx/nativeactivity.cpp", __VA_ARGS__))

/* For debug builds, always enable the debug traces in this library */
#ifndef NDEBUG
#  define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "cocos2dx/nativeactivity.cpp", __VA_ARGS__))
#else
#  define LOGV(...)  ((void)0)
#endif

void cocos_android_app_init(struct android_app* app);

/**
 * Our saved state data.
 */
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

/**
 * Shared state for our app.
 */
struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};

static bool isContentRectChanged = false;
static std::chrono::steady_clock::time_point timeRectChanged;

static struct engine engine;

static char* editboxText = NULL;
extern EditTextCallback s_pfEditTextCallback;
extern void* s_ctx;

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetEditTextDialogResult(JNIEnv * env, jobject obj, jbyteArray text) { 
        jsize  size = env->GetArrayLength(text);
        pthread_mutex_lock(&(engine.app->mutex));
        if (size > 0) {
            jbyte * data = (jbyte*)env->GetByteArrayElements(text, 0);
            char* pBuf = (char*)malloc(size+1);
            if (pBuf != NULL) {
                memcpy(pBuf, data, size);
                pBuf[size] = '\0';
                editboxText = pBuf;
            }
            env->ReleaseByteArrayElements(text, data, 0);

        } else {
            char* pBuf = (char*)malloc(1);
            pBuf[0] = '\0';
            editboxText = pBuf;
        }
        pthread_cond_broadcast(&engine.app->cond);
        pthread_mutex_unlock(&(engine.app->mutex));
    }
}

typedef struct cocos_dimensions {
    int w;
    int h;
} cocos_dimensions;

static void cocos_init(cocos_dimensions d, struct android_app* app)
{
    LOGI("cocos_init(...)");
    pthread_t thisthread = pthread_self();
    LOGI("pthread_self() = %X", thisthread);

    cocos2d::FileUtilsAndroid::setassetmanager(app->activity->assetManager);

    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview)
    {
        glview = cocos2d::GLView::create("Android app");
        glview->setFrameSize(d.w, d.h);
        director->setOpenGLView(glview);

        cocos_android_app_init(app);

        cocos2d::Application::getInstance()->run();
    }
    else
    {
        cocos2d::GL::invalidateStateCache();
        cocos2d::ShaderCache::getInstance()->reloadDefaultShaders();
        cocos2d::DrawPrimitives::init();
        cocos2d::VolatileTextureMgr::reloadAllTextures();

        cocos2d::EventCustom foregroundEvent(EVENT_COME_TO_FOREGROUND);
        director->getEventDispatcher()->dispatchEvent(&foregroundEvent);
        director->setGLDefaultValues();
    }
}

/**
 * Initialize an EGL context for the current display.
 */
static cocos_dimensions engine_init_display(struct engine* engine)
{
    cocos_dimensions r;
    r.w = -1;
    r.h = -1;

    // initialize OpenGL ES and EGL

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_BLUE_SIZE, 5,
            EGL_GREEN_SIZE, 6,
            EGL_RED_SIZE, 5,
            EGL_DEPTH_SIZE, 16,
            EGL_STENCIL_SIZE, 8,
            EGL_NONE
    };
    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);

    const EGLint eglContextAttrs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    context = eglCreateContext(display, config, NULL, eglContextAttrs);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("Unable to eglMakeCurrent");
        return r;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;
    engine->state.angle = 0;

    r.w = w;
    r.h = h;


    return r;
}

/**
 * Invoke the dispatching of the next bunch of Runnables in the Java-Land
 */
static bool s_methodInitialized = false;
static void dispatch_pending_runnables() {
    static cocos2d::JniMethodInfo info;
    
    if (!s_methodInitialized) {
        s_methodInitialized = cocos2d::JniHelper::getStaticMethodInfo(
            info,
            "org/cocos2dx/lib/Cocos2dxHelper",
            "dispatchPendingRunnables",
            "()V"
        );

        if (!s_methodInitialized) {
            LOGW("Unable to dispatch pending Runnables!");
            return;
        }
    }

    info.env->CallStaticVoidMethod(info.classID, info.methodID);
}

/**
 * Just the current frame in the display.
 */
static void engine_draw_frame(struct engine* engine)
{
    LOG_RENDER_DEBUG("engine_draw_frame(...)");
    pthread_t thisthread = pthread_self();
    LOG_RENDER_DEBUG("pthread_self() = %X", thisthread);

    if (engine->display == NULL) {
        // No display.
        LOGW("engine_draw_frame : No display.");
        return;
    }

    dispatch_pending_runnables();
    cocos2d::Director::getInstance()->mainLoop();
    LOG_RENDER_DEBUG("engine_draw_frame : just called cocos' mainLoop()");

    /* // Just fill the screen with a color. */
    /* glClearColor(((float)engine->state.x)/engine->width, engine->state.angle, */
    /*         ((float)engine->state.y)/engine->height, 1); */
    /* glClear(GL_COLOR_BUFFER_BIT); */ 
    
    if (s_pfEditTextCallback && editboxText)
    {
        s_pfEditTextCallback(editboxText, s_ctx);
        free(editboxText);
        editboxText = NULL;
    }   

    eglSwapBuffers(engine->display, engine->surface);
}

/**
 * Tear down the EGL context currently associated with the display.
 */
static void engine_term_display(struct engine* engine)
{
    if (engine->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (engine->context != EGL_NO_CONTEXT) {
            eglDestroyContext(engine->display, engine->context);
        }
        if (engine->surface != EGL_NO_SURFACE) {
            eglDestroySurface(engine->display, engine->surface);
        }
        eglTerminate(engine->display);
    }
    engine->animating = 0;
    engine->display = EGL_NO_DISPLAY;
    engine->context = EGL_NO_CONTEXT;
    engine->surface = EGL_NO_SURFACE;
}

/*
 * Get X, Y positions and ID's for all pointers
 */
static void getTouchPos(AInputEvent *event, int ids[], float xs[], float ys[]) {
    int pointerCount = AMotionEvent_getPointerCount(event);
    for(int i = 0; i < pointerCount; ++i) {
        ids[i] = AMotionEvent_getPointerId(event, i);
        xs[i] = AMotionEvent_getX(event, i);
        ys[i] = AMotionEvent_getY(event, i);
    }
}

/*
 * Handle Touch Inputs
 */
static int32_t handle_touch_input(AInputEvent *event) {

    pthread_t thisthread = pthread_self();
    LOG_EVENTS_DEBUG("handle_touch_input(%X), pthread_self() = %X", event, thisthread);

    switch(AMotionEvent_getAction(event) &
           AMOTION_EVENT_ACTION_MASK) {

    case AMOTION_EVENT_ACTION_DOWN:
        {
            LOG_EVENTS_DEBUG("AMOTION_EVENT_ACTION_DOWN");
            int pointerId = AMotionEvent_getPointerId(event, 0);
            float xP = AMotionEvent_getX(event,0);
            float yP = AMotionEvent_getY(event,0);

            LOG_EVENTS_DEBUG("Event: Action DOWN x=%f y=%f pointerID=%d\n",
                 xP, yP, pointerId);
            float x = xP;
            float y = yP;

            cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesBegin(1, &pointerId, &x, &y);
            return 1;
        }
        break;

    case AMOTION_EVENT_ACTION_POINTER_DOWN:
        {
            LOG_EVENTS_DEBUG("AMOTION_EVENT_ACTION_POINTER_DOWN");
            int pointerIndex = AMotionEvent_getAction(event) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
            int pointerId = AMotionEvent_getPointerId(event, pointerIndex);
            float xP = AMotionEvent_getX(event,pointerIndex);
            float yP = AMotionEvent_getY(event,pointerIndex);

            LOG_EVENTS_DEBUG("Event: Action POINTER DOWN x=%f y=%f pointerID=%d\n",
                 xP, yP, pointerId);
            float x = xP;
            float y = yP;

            cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesBegin(1, &pointerId, &x, &y);
            return 1;
        }
        break;

    case AMOTION_EVENT_ACTION_MOVE:
        {
            LOG_EVENTS_DEBUG("AMOTION_EVENT_ACTION_MOVE");
            int pointerCount = AMotionEvent_getPointerCount(event);
            int ids[pointerCount];
            float xs[pointerCount], ys[pointerCount];
            getTouchPos(event, ids, xs, ys);
            cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesMove(pointerCount, ids, xs, ys);
            return 1;
        }
        break;

    case AMOTION_EVENT_ACTION_UP:
        {
            LOG_EVENTS_DEBUG("AMOTION_EVENT_ACTION_UP");
            int pointerId = AMotionEvent_getPointerId(event, 0);
            float xP = AMotionEvent_getX(event,0);
            float yP = AMotionEvent_getY(event,0);
            LOG_EVENTS_DEBUG("Event: Action UP x=%f y=%f pointerID=%d\n",
                 xP, yP, pointerId);
            float x = xP;
            float y = yP;

            cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesEnd(1, &pointerId, &x, &y);
            return 1;
        }
        break;

    case AMOTION_EVENT_ACTION_POINTER_UP:
        {
            LOG_EVENTS_DEBUG("AMOTION_EVENT_ACTION_POINTER_UP");
            int pointerIndex = AMotionEvent_getAction(event) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
            int pointerId = AMotionEvent_getPointerId(event, pointerIndex);
            float xP = AMotionEvent_getX(event,pointerIndex);
            float yP = AMotionEvent_getY(event,pointerIndex);
            LOG_EVENTS_DEBUG("Event: Action POINTER UP x=%f y=%f pointerID=%d\n",
                 xP, yP, pointerIndex);
            float x = xP;
            float y = yP;

            cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesEnd(1, &pointerId, &x, &y);
            return 1;
        }
        break;

    case AMOTION_EVENT_ACTION_CANCEL:
        {
            LOG_EVENTS_DEBUG("AMOTION_EVENT_ACTION_CANCEL");
            int pointerCount = AMotionEvent_getPointerCount(event);
            int ids[pointerCount];
            float xs[pointerCount], ys[pointerCount];
            getTouchPos(event, ids, xs, ys);
            cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesCancel(pointerCount, ids, xs, ys);
            return 1;
        }
        break;

    default:
        LOG_EVENTS_DEBUG("handle_touch_input() default case.... NOT HANDLE");
        return 0;
        break;
    }
}

/*
* Handle Key Inputs
*/
static int32_t handle_key_input(AInputEvent *event)
{
    if (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_UP)
    {
        auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();

        switch (AKeyEvent_getKeyCode(event))
        {
        case AKEYCODE_BACK: 
            {
                cocos2d::EventKeyboard event(cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE, false);
                dispatcher->dispatchEvent(&event);
            }
            return 1;
        case AKEYCODE_MENU:
            {
                cocos2d::EventKeyboard event(cocos2d::EventKeyboard::KeyCode::KEY_MENU, false);
                dispatcher->dispatchEvent(&event);
            }
            return 1;
        default:
            break;
        }
    }
    return 0;
}

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {

    pthread_t thisthread = pthread_self();
    LOG_EVENTS_DEBUG("engine_handle_input(%X, %X), pthread_self() = %X", app, event, thisthread);

    struct engine* engine = (struct engine*)app->userData;

    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        engine->animating = 1;
        engine->state.x = AMotionEvent_getX(event, 0);
        engine->state.y = AMotionEvent_getY(event, 0);

        return handle_touch_input(event);
    }
    else
        return handle_key_input(event);

    return 0;
}

void enableAccelerometerJni(void) {
    LOGI("enableAccelerometerJni()");

    if (engine.accelerometerSensor != NULL) {
        ASensorEventQueue_enableSensor(engine.sensorEventQueue,
                                       engine.accelerometerSensor);

        // Set a default sample rate
        // We'd like to get 60 events per second (in us).
        ASensorEventQueue_setEventRate(engine.sensorEventQueue,
                                       engine.accelerometerSensor, (1000L/60)*1000);
    }
}

void disableAccelerometerJni(void) {
    LOGI("disableAccelerometerJni()");

    if (engine.accelerometerSensor != NULL) {
        ASensorEventQueue_disableSensor(engine.sensorEventQueue,
                                        engine.accelerometerSensor);
    }
}

void setAccelerometerIntervalJni(float interval) {
    LOGI("setAccelerometerIntervalJni(%f)", interval);
        // We'd like to get 60 events per second (in us).
        ASensorEventQueue_setEventRate(engine.sensorEventQueue,
                                       engine.accelerometerSensor, interval * 1000000L);
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{ 
    struct engine* engine = (struct engine*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
            engine->app->savedState = malloc(sizeof(struct saved_state));
            *((struct saved_state*)engine->app->savedState) = engine->state;
            engine->app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (engine->app->window != NULL) {
                cocos_dimensions d = engine_init_display(engine);
                if ((d.w > 0) &&
                    (d.h > 0)) {
                    cocos2d::JniHelper::setJavaVM(app->activity->vm);
                    cocos2d::JniHelper::setClassLoaderFrom(app->activity->clazz);

                    // call Cocos2dxHelper.init()
                    cocos2d::JniMethodInfo ccxhelperInit;
                    if (!cocos2d::JniHelper::getStaticMethodInfo(ccxhelperInit,
                                                                 "org/cocos2dx/lib/Cocos2dxHelper",
                                                                 "init",
                                                                 "(Landroid/app/Activity;)V")) {
                        LOGI("cocos2d::JniHelper::getStaticMethodInfo(ccxhelperInit) FAILED");
                    }
                    ccxhelperInit.env->CallStaticVoidMethod(ccxhelperInit.classID,
                                                            ccxhelperInit.methodID,
                                                            app->activity->clazz);

                    cocos_init(d, app);
                }
                engine->animating = 1;
                engine_draw_frame(engine);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            engine_term_display(engine);
            break;
        case APP_CMD_GAINED_FOCUS:
            if (cocos2d::Director::getInstance()->getOpenGLView()) {
                cocos2d::Application::getInstance()->applicationWillEnterForeground();
                engine->animating = 1;
            }

            break;
        case APP_CMD_LOST_FOCUS:
            {
                cocos2d::Application::getInstance()->applicationDidEnterBackground();
                cocos2d::EventCustom backgroundEvent(EVENT_COME_TO_BACKGROUND);
                cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&backgroundEvent);
                // Also stop animating.
                engine->animating = 0;
                engine_draw_frame(engine);
            }
            break;
    }
}

static void onContentRectChanged(ANativeActivity* activity, const ARect* rect) {
    timeRectChanged = std::chrono::steady_clock::now();
    isContentRectChanged = true;
}

static void process_input(struct android_app* app, struct android_poll_source* source)
{
    AInputEvent* event = NULL;
    while (AInputQueue_getEvent(app->inputQueue, &event) >= 0) {
        LOGV("New input event: type=%d\n", AInputEvent_getType(event));
        if (AInputQueue_preDispatchEvent(app->inputQueue, event)) {
            continue;
        }
        int32_t handled = 0;
        if (app->onInputEvent != NULL) handled = app->onInputEvent(app, event);
        AInputQueue_finishEvent(app->inputQueue, event, handled);
    }
}
/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) {

    // Make sure glue isn't stripped.
    app_dummy();

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    state->inputPollSource.process = process_input;
    engine.app = state;

    // Prepare to monitor accelerometer
    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
            ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
            state->looper, LOOPER_ID_USER, NULL, NULL);

    if (state->savedState != NULL) {
        // We are starting with a previous saved state; restore from it.
        engine.state = *(struct saved_state*)state->savedState;
    }

    // Screen size change support
    state->activity->callbacks->onContentRectChanged = onContentRectChanged;

    // loop waiting for stuff to do.

    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
                (void**)&source)) >= 0) {

            // Process this event.
            if (source != NULL) {
                source->process(state, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {
                if (engine.accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
                            &event, 1) > 0) {

                        LOG_EVENTS_DEBUG("accelerometer: x=%f y=%f z=%f",
                                event.acceleration.x, event.acceleration.y,
                                event.acceleration.z);

                        AConfiguration* _currentconf = AConfiguration_new();
                        AConfiguration_fromAssetManager(_currentconf,
                                                        state->activity->assetManager);
                        static int32_t _orientation = AConfiguration_getOrientation(_currentconf);

                        if (ACONFIGURATION_ORIENTATION_LAND != _orientation) {
                            // ACONFIGURATION_ORIENTATION_ANY
                            // ACONFIGURATION_ORIENTATION_PORT
                            // ACONFIGURATION_ORIENTATION_SQUARE
                            cocos2d::Acceleration acc;
                            acc.x = -event.acceleration.x/10;
                            acc.y = -event.acceleration.y/10;
                            acc.z = event.acceleration.z/10;
                            acc.timestamp = 0;
                            cocos2d::EventAcceleration accEvent(acc);
                            auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
                            dispatcher->dispatchEvent(&accEvent);
                        } else {
                            // ACONFIGURATION_ORIENTATION_LAND
                            // swap x and y parameters
                            cocos2d::Acceleration acc;
                            acc.x = event.acceleration.y/10;
                            acc.y = -event.acceleration.x/10;
                            acc.z = event.acceleration.z/10;
                            acc.timestamp = 0;
                            cocos2d::EventAcceleration accEvent(acc);
                            auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
                            dispatcher->dispatchEvent(&accEvent);
                        }
                    }
                }
            }

            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                engine_term_display(&engine);

                memset(&engine, 0, sizeof(engine));
                s_methodInitialized = false;
                return;
            }
        }

        if (engine.animating) {
            // Done with events; draw next animation frame.
            engine.state.angle += .01f;
            if (engine.state.angle > 1) {
                engine.state.angle = 0;
            }

            // Drawing is throttled to the screen update rate, so there
            // is no need to do timing here.
            LOG_RENDER_DEBUG("android_main : engine.animating");
            engine_draw_frame(&engine);
        } else {
            LOG_RENDER_DEBUG("android_main : !engine.animating");
        }

        // Check if screen size changed
        if (isContentRectChanged) {
            std::chrono::duration<int, std::milli> duration(
                    std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(std::chrono::steady_clock::now() - timeRectChanged));

            // Wait about 30 ms to get new width and height. Without waiting we can get old values sometime
            if (duration.count() > 30) {
                isContentRectChanged = false;

                int32_t newWidth = ANativeWindow_getWidth(engine.app->window);
                int32_t newHeight = ANativeWindow_getHeight(engine.app->window);
                cocos2d::Application::getInstance()->applicationScreenSizeChanged(newWidth, newHeight);
            }
        }
    }
}

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
