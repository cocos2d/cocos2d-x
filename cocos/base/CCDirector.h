/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2013 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#ifndef __CCDIRECTOR_H__
#define __CCDIRECTOR_H__

#include <stack>
#include <thread>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "2d/CCScene.h"
#include "math/CCMath.h"
#include "platform/CCGL.h"
#include "platform/CCGLView.h"

NS_CC_BEGIN

/**
 * @addtogroup base
 * @{
 */

/* Forward declarations.*/
class LabelAtlas;
//class GLView;
class DirectorDelegate;
class Node;
class Scheduler;
class ActionManager;
class EventDispatcher;
class EventCustom;
class EventListenerCustom;
class TextureCache;
class Renderer;
class Camera;

class Console;
namespace experimental
{
    class FrameBuffer;
}

/**
 * @brief @~english Matrix stack type.
 * @~chinese 矩阵栈类型。
 */
enum class MATRIX_STACK_TYPE
{
    /// Model view matrix stack
    MATRIX_STACK_MODELVIEW,
    
    /// projection matrix stack
    MATRIX_STACK_PROJECTION,
    
    /// texture matrix stack
    MATRIX_STACK_TEXTURE
};

/**
 @brief @~english Class that creates and handles the main Window and manages how
 and when to execute the Scenes.
 
 The Director is also responsible for:
 - initializing the OpenGL context
 - setting the OpenGL buffer depth (default one is 0-bit)
 - setting the projection (default one is 3D)
 
 Since the Director is a singleton, the standard way to use it is by calling:
 * Director::getInstance()->methodName();
 * @~chinese 导演类，负责创建和处理主窗口，以及管理场景执行。
 * 
 * 导演还负责:
 * -初始化OpenGL上下文
 * -设置OpenGL缓冲区深度(默认是0)
 * -设置投影(默认是3d)
 * 
 * Since the Director is a singleton, the standard way to use it is by calling:
 * 导演类是一个单例，标准的调用方法如下：
 * Director::getInstance()- > methodName();
 */
class CC_DLL Director : public Ref
{
public:
    /** @~english Director will trigger an event when projection type is changed.  @~chinese 当投影类型变化时导演将触发一个事件。*/
    static const char* EVENT_PROJECTION_CHANGED;
    /** Director will trigger an event before Schedule::update() is invoked. */
    static const char* EVENT_BEFORE_UPDATE;
    /** @~english Director will trigger an event after Schedule::update() is invoked.  @~chinese 在调用Schedule::update()后导演会触发一个事件。*/
    static const char* EVENT_AFTER_UPDATE;
    /** @~english Director will trigger an event after Scene::render() is invoked.  @~chinese 在调用Scene::render()后导演将触发一个事件。*/
    static const char* EVENT_AFTER_VISIT;
    /** @~english Director will trigger an event after a scene is drawn, the data is sent to GPU.  @~chinese 当一个场景绘制,数据被发送到GPU后导演将触发一个事件。*/
    static const char* EVENT_AFTER_DRAW;

    /**
     * @brief @~english Possible OpenGL projections used by director
     * @~chinese 导演使用的可能的OpenGL投影类型
     */
    enum class Projection
    {
        /// Sets a 2D projection (orthogonal projection).
        _2D,
        
        /// Sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
        _3D,
        
        /// It calls "updateProjection" on the projection delegate.
        CUSTOM,
        
        /// Default projection is 3D projection.
        DEFAULT = _3D,
    };
    
    /** @~english
     * Returns a shared instance of the director. 
     * @~chinese 
     * 返回一个导演的单例。
     * @js _getInstance
     */
    static Director* getInstance();

    /**
     * @deprecated Use getInstance() instead.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE static Director* sharedDirector() { return Director::getInstance(); }
    
    /**
     * @js ctor
     */
    Director();
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Director();
    virtual bool init();

    // attribute

    /** @~english Gets current running Scene. Director can only run one Scene at a time.  @~chinese 得到当前运行场景。导演一次只能运行一个场景。*/
    inline Scene* getRunningScene() { return _runningScene; }

    /** @~english Gets the FPS value.  @~chinese 得到了FPS的值。*/
    inline float getAnimationInterval() { return _animationInterval; }
    /** @~english Sets the FPS value. FPS = 1 @~chinese 设置FPS的值。FPS = 1 */
    virtual void setAnimationInterval(float interval) = 0;

    /** @~english Whether or not to display the FPS on the bottom-left corner.  @~chinese 左下角是否有显示FPS。*/
    inline bool isDisplayStats() { return _displayStats; }
    /** @~english Display the FPS on the bottom-left corner.  @~chinese 设置是否在左下角显示FPS。*/
    inline void setDisplayStats(bool displayStats) { _displayStats = displayStats; }
    
    /** @~english Get seconds per frame.  @~chinese 获取每帧间隔几秒。*/
    inline float getSecondsPerFrame() { return _secondsPerFrame; }

    /** @~english
     * Get the GLView.
     * @~chinese 
     * 获取GLView。
     * @lua NA
     */
    inline GLView* getOpenGLView() { return _openGLView; }
    /** @~english
     * Sets the GLView. 
     * @~chinese 
     * 设置GLView。
     * @lua NA
     */
    void setOpenGLView(GLView *openGLView);

    /*@~english
     * Gets singleton of TextureCache.
     * @~chinese 
     * 获取TextureCache单例。
     * @js NA
     */
    TextureCache* getTextureCache() const;

    /** @~english Whether or not `_nextDeltaTimeZero` is set to 0.  @~chinese “_nextDeltaTimeZero”是否设置为0。*/
    inline bool isNextDeltaTimeZero() { return _nextDeltaTimeZero; }
    /** @~english
     * Sets the delta time between current frame and next frame is 0.
     * This value will be used in Schedule, and will affect all functions that are using frame delta time, such as Actions.
     * This value will take effect only one time.
     * @~chinese 
     * 设置当前帧和下一个帧之间时间为0。
     * 这个值用于Schedule,将会影响所有使用帧间隔时间的函数,比如Actions。
     * 这个值只生效一次。
     */
    void setNextDeltaTimeZero(bool nextDeltaTimeZero);

    /** @~english Whether or not the Director is paused.  @~chinese 导演是否暂停。*/
    inline bool isPaused() { return _paused; }

    /** @~english How many frames were called since the director started  @~chinese 获取导演开始以来游戏运行的总帧数。*/
    inline unsigned int getTotalFrames() { return _totalFrames; }
    
    /** @~english Gets an OpenGL projection.
     * @~chinese 获取OpenGL投影。
     * @since v0.8.2
     * @lua NA
     */
    inline Projection getProjection() { return _projection; }
    /** @~english Sets OpenGL projection.  @~chinese 设置OpenGL投影。*/
    void setProjection(Projection projection);
    
    /** @~english Sets the glViewport. @~chinese 设置glViewport。*/
    void setViewport();    
    
    /** @~english Whether or not the replaced scene will receive the cleanup message.
     * If the new scene is pushed, then the old scene won't receive the "cleanup" message.
     * If the new scene replaces the old one, the it will receive the "cleanup" message.
     * @~chinese 更换场景时是否接收清理消息。
     * 如果新场景是采用push方式进入的，那么旧的场景将不会接收到"cleanup"消息。
     * 如果新场景取代旧的场景,它将会接收到"cleanup"消息。
     * @since v0.99.0
     */
    inline bool isSendCleanupToScene() { return _sendCleanupToScene; }

    /** @~english This object will be visited after the main scene is visited.
     * This object MUST implement the "visit" function.
     * Useful to hook a notification object, like Notifications (http://github.com/manucorporat/CCNotifications)
     * @~chinese 这个对象将会在主场景渲染完后渲染。
     * 这个对象必须实现“visit”功能。
     * 对于hook一个通知节点很有用,比如 Notifications (http://github.com/manucorporat/CCNotifications)
     * @since v0.99.5
     */
    Node* getNotificationNode() const { return _notificationNode; }
    /** @~english
     * Sets the notification node.
     * @~chinese 
     * 设置通知节点。
     * @see Director::getNotificationNode()
     */
    void setNotificationNode(Node *node);
    
    // window size

    /** @~english Returns the size of the OpenGL view in points.  @~chinese 返回OpenGL视图的大小，以点为单位。*/
    const Size& getWinSize() const;

    /** @~english Returns the size of the OpenGL view in pixels.  @~chinese 返回OpenGL视图中大小。以像素为单位。*/
    Size getWinSizeInPixels() const;
    
    /** @~english
     * Returns visible size of the OpenGL view in points.
     * The value is equal to `Director::getWinSize()` if don't invoke `GLView::setDesignResolutionSize()`.
     * @~chinese 
     * 返回可见OpenGL视图大小，以点为单位。
     * 如果不调用GLView:setDesignResolutionSize"的话，其值等于“Director::getWinSize()”。
     */
    Size getVisibleSize() const;
    
    /** @~english Returns visible origin coordinate of the OpenGL view in points.  @~chinese 返回可见OpenGL视图起始点，以点为单位。*/
    Vec2 getVisibleOrigin() const;

    /** @~english
     * Converts a screen coordinate to an OpenGL coordinate.
     * Useful to convert (multi) touch coordinates to the current layout (portrait or landscape).
     * @~chinese 
     * 将屏幕坐标转换为一个OpenGL坐标。
     * 对于将(多点)触摸坐标转换为当前布局(横向或纵向)很有用。
     */
    Vec2 convertToGL(const Vec2& point);

    /** @~english
     * Converts an OpenGL coordinate to a screen coordinate.
     * Useful to convert node points to window points for calls such as glScissor.
     * @~chinese 
     * 转换一个OpenGL坐标到屏幕坐标。
     * 对于比如glScissor调用将node点转换到窗口点很有用。
     */
    Vec2 convertToUI(const Vec2& point);

    /** @~english
     * Gets the distance between  camera and near clipping frame.
     * It is correct for default camera that near clipping frame is the same as screen.
     * @~chinese 
     * 获取camera到near clipping frame的距离。
     * 默认的camera，near clipping frame是和screen一样的。
     */
    float getZEye() const;

    // Scene Management

    /** @~english
     * Enters the Director's main loop with the given Scene.
     * Call it to run only your FIRST scene.
     * Don't call it if there is already a running scene.
     *
     * It will call pushScene: and then it will call startAnimation
     * @~chinese 
     * 通过给定的场景进入导演的主循环。
     * 只能在运行你的第一个场景调用它。
     * 它如果已经有一个正在运行的场景不要调用它。
     * 
     * 它将调用pushScene:然后将调用startAnimation
     * @js NA
     */
    void runWithScene(Scene *scene);

    /** @~english
     * Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
     * The new scene will be executed.
     * Try to avoid big stacks of pushed scenes to reduce memory allocation. 
     * ONLY call it if there is a running scene.
     * @~chinese 
     * 暂停当前运行的场景,压入到暂停的场景栈中。
     * 新场景将被执行。
     * 尽量避免压入大场景,以减少内存分配。
     * 只能在有运行场景时调用它。
     */
    void pushScene(Scene *scene);

    /** @~english
     * Pops out a scene from the stack.
     * This scene will replace the running one.
     * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
     * ONLY call it if there is a running scene.
     * @~chinese 
     * 从堆栈中弹出了一个场景。
     * 这一场景将会取代当前运行的场景。
     * 运行场景将被删除。如果场景栈没有更多的场景的话执行将被终止。
     * 只能在有运行场景时调用它。
     */
    void popScene();

    /** @~english
     * Pops out all scenes from the stack until the root scene in the queue.
     * This scene will replace the running one.
     * Internally it will call `popToSceneStackLevel(1)`.
     * @~chinese 
     * 从堆栈中弹出所有场景，到根场景。
     * 这一场景将会取代当前运行的场景。
     * 内部会调用“popToSceneStackLevel(1)”。
     */
    void popToRootScene();

    /** @~english Pops out all scenes from the stack until it reaches `level`.
     If level is 0, it will end the director.
     If level is 1, it will pop all scenes until it reaches to root scene.
     If level is <= than the current stack level, it won't do anything.
     * @~chinese 从堆栈中弹出所有场景,直到到达第“level”个。
     * 如果级别为0,它将结束导演的执行。
     * 如果级别是1,那么它将弹出所有场景,直到到达根的场景。
     * 如果级别小于等于比当前堆栈级别,它不会做任何事情。
     */
 	void popToSceneStackLevel(int level);

    /** @~english Replaces the running scene with a new one. The running scene is terminated.
     * ONLY call it if there is a running scene.
     * @~chinese 用新的场景替换运行场景。终止正在运行的场景。
     * 只能在有运行场景时调用它。
     * @js NA
     */
    void replaceScene(Scene *scene);

    /** @~english Ends the execution, releases the running scene.
     * @~chinese 执行结束,释放运行场景。
     * @lua endToLua
     */
    void end();

    /** @~english Pauses the running scene.
     * The running scene will be drawed, but all scheduled timers will be paused.
     * While paused, the draw rate will be 4 FPS to reduce CPU consumption.
     * @~chinese 暂停正在运行的场景。
     * 运行场景将绘制，但所有scheduled timers将暂停。
     * 一旦暂停,FPS将会降到将4以减少CPU消耗。
     */
    void pause();

    /** @~english Resumes the paused scene.
     * The scheduled timers will be activated again.
     * The "delta time" will be 0 (as if the game wasn't paused).
     * @~chinese 恢复暂停场景。
     * scheduled timers将再次被激活。
     * “delta time”将会为0(就像是游戏没有暂停一样)。
     */
    void resume();
    
    /*@~english
     * Restart the director. 
     * @~chinese 
     * 重新启动导演。
     * @js NA
     */
    void restart();

    /** @~english Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
     * If you don't want to pause your animation call [pause] instead.
     * @~chinese 停止动画。不进行绘制。主循环不会再被触发。
     * 如果你不想暂停动画，请调用[pause]。
     */
    virtual void stopAnimation() = 0;

    /** @~english The main loop is triggered again.
     * Call this function only if [stopAnimation] was called earlier.
     * @~chinese 主循环触发一次。
     * 只有之前调用过stopAnimation，才能调用这个函数。
     * @warning @~english Don't call this function to start the main loop. To run the main loop call runWithScene.
     * @~chinese 不调用这个函数来开始主循环。请调用runWithScene来开始主循环。
     */
    virtual void startAnimation() = 0;

    /** @~english Draw the scene.
     * This method is called every frame. Don't call it manually.
     * @~chinese 绘制场景。
     * 每一帧都会调用此方法。不要手动调用它。
     */
    void drawScene();

    // Memory Helper

    /** @~english Removes all cocos2d cached data.
     * It will purge the TextureCache, SpriteFrameCache, LabelBMFont cache
     * @~chinese 删除所有cocos2d缓存的数据。
     * 它将清除TextureCache，SpriteFrameCache，LabelBMFont缓存
     * @since v0.99.3
     */
    void purgeCachedData();

	/** @~english Sets the default values based on the Configuration info.  @~chinese 根据Configuration信息设置默认值。*/
    void setDefaultValues();

    // OpenGL Helper

    /** @~english Sets the OpenGL default values.
     * It will enable alpha blending, disable depth test.
     * @~chinese 设置OpenGL默认值。
     * 它将启用alpha blending，禁用深度测试。
     * @js NA
     */
    void setGLDefaultValues();

    /** @~english Enables/disable alpha blending @~chinese 启用/禁用alpha blending */
    void setAlphaBlending(bool on);
    
    /** @~english Sets clear values for the color buffers,
     * value range of each element is [0.0, 1.0].
     * @~chinese 设置色缓冲区的清除值,
     * 每个元素的值范围是[0.0,1.0]。
     * @js NA
     */
    void setClearColor(const Color4F& clearColor);

    /** @~english Enable/disable depth test @~chinese 启用/禁用深度测试  */
    void setDepthTest(bool on);

    virtual void mainLoop() = 0;

    /** @~english The size in pixels of the surface. It could be different than the screen size.
     * High-res devices might have a higher surface size than the screen size.
     * Only available when compiled using SDK >= 4.0.
     * @~chinese surface的大小(以像素为单位)。它可能会屏幕大小不同。
     * 高分辨率的设备比起屏幕尺寸大小，它可能有一个更高的surface。
     * 只有当使用大于4.0的SDK编译才有效。
     * @since v0.99.4
     */
    void setContentScaleFactor(float scaleFactor);
    /**@~english
     * Gets content scale factor.
     * @~chinese 
     * 获取内容缩放比例。
     * @see Director::setContentScaleFactor()
     */
    float getContentScaleFactor() const { return _contentScaleFactor; }

    /** @~english Gets the Scheduler associated with this director.
     * @~chinese 获取和导演相关联的调度器。
     * @since v2.0
     */
    Scheduler* getScheduler() const { return _scheduler; }
    
    /** @~english Sets the Scheduler associated with this director.
     * @~chinese 设置和导演相关联的调度器。
     * @since v2.0
     */
    void setScheduler(Scheduler* scheduler);

    /** @~english Gets the ActionManager associated with this director.
     * @~chinese 获取和导演相关联的动作管理器。
     * @since v2.0
     */
    ActionManager* getActionManager() const { return _actionManager; }
    
    /** @~english Sets the ActionManager associated with this director.
     * @~chinese 设置和导演相关联的动作管理器。
     * @since v2.0
     */
    void setActionManager(ActionManager* actionManager);
    
    /** @~english Gets the EventDispatcher associated with this director.
     * @~chinese 获取和导演相关联的事件分发器。
     * @since v3.0
     * @js NA
     */
    EventDispatcher* getEventDispatcher() const { return _eventDispatcher; }
    
    /** @~english Sets the EventDispatcher associated with this director.
     * @~chinese 设置和导演相关联的事件分发器。
     * @since v3.0
     * @js NA
     */
    void setEventDispatcher(EventDispatcher* dispatcher);

    /** @~english Returns the Renderer associated with this director.
     * @~chinese 获取和导演相关联的渲染器。
     * @since v3.0
     */
    Renderer* getRenderer() const { return _renderer; }

    /** @~english Returns the Console associated with this director.
     * @~chinese 获取和导演相关联的控制台。
     * @since v3.0
     * @js NA
     */
    Console* getConsole() const { return _console; }

    /* @~english Gets delta time since last tick to main loop.  @~chinese 获取mainloop距上一个tick的时间间隔。*/
    float getDeltaTime() const;
    
    /**@~english
     *  Gets Frame Rate.
     * @~chinese 
     * 获取帧速率。
     * @js NA
     */
    float getFrameRate() const { return _frameRate; }

    /** @~english
     * Clones a specified type matrix and put it to the top of specified type of matrix stack.
     * @~chinese 
     * 克隆一个指定类型的矩阵,把它放到指定类型的矩阵堆栈的顶部。
     * @js NA
     */
    void pushMatrix(MATRIX_STACK_TYPE type);
    /** @~english Pops the top matrix of the specified type of matrix stack.
     * @~chinese 弹出指定类型的矩阵堆栈的顶部矩阵。
     * @js NA
     */
    void popMatrix(MATRIX_STACK_TYPE type);
    /** @~english Adds an identity matrix to the top of specified type of matrxi stack.
     * @~chinese 给指定类型的矩阵堆栈的顶部添加一个单位矩阵。
     * @js NA
     */
    void loadIdentityMatrix(MATRIX_STACK_TYPE type);
    /**@~english
     * Adds a matrix to the top of specified type of matrix stack.
     * 
     * @~chinese 
     * 给指定类型的矩阵堆栈的顶部添加一个矩阵。
     * 
     * @param type @~english Matrix type.
     * @~chinese 矩阵类型。
     * @param mat @~english The matrix that to be added.
     * @~chinese 要添加的矩阵。
     * @js NA
     */
    void loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    /**@~english
     * Multiplies a matrix to the top of specified type of matrix stack.
     *
     * @~chinese 
     * 对指定类型的矩阵堆栈的顶部矩阵进行乘法运算。
     * 
     * @param type @~english Matrix type.
     * @~chinese 矩阵类型。
     * @param mat @~english The matrix that to be multipied.
     * @~chinese 要进行乘法运算的矩阵。
     * @js NA
     */
    void multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    /**@~english
     * Gets the top matrix of specified type of matrix stack.
     * @~chinese 
     * 获取指定类型的矩阵堆栈顶部的矩阵。
     * @js NA
     */
    const Mat4& getMatrix(MATRIX_STACK_TYPE type);
    /**@~english
     * Clears all types of matrix stack, and add indentity matrix to these matrix stacks.
     * @~chinese 
     * 清除所有类型的矩阵堆栈,并添加单位矩阵到这些矩阵栈。
     * @js NA
     */
    void resetMatrixStack();

    /**
     * returns the cocos2d thread id.
     Useful to know if certain code is already running on the cocos2d thread
     */
    const std::thread::id& getCocos2dThreadId() const { return _cocos2d_thread_id; }

protected:
    void reset();
    
    void purgeDirector();
    bool _purgeDirectorInNextLoop; // this flag will be set to true in end()
    
    void restartDirector();
    bool _restartDirectorInNextLoop; // this flag will be set to true in restart()
    
    void setNextScene();
    
    void showStats();
    void createStatsLabel();
    void calculateMPF();
    void getFPSImageData(unsigned char** datapointer, ssize_t* length);
    
    /** @~english calculates delta time since last time it was called  @~chinese 计算三角洲自上次被称为*/    
    void calculateDeltaTime();

    //textureCache creation or release
    void initTextureCache();
    void destroyTextureCache();

    void initMatrixStack();

    std::stack<Mat4> _modelViewMatrixStack;
    std::stack<Mat4> _projectionMatrixStack;
    std::stack<Mat4> _textureMatrixStack;

    /** @~english Scheduler associated with this director
     * @~chinese 调度器与此相关
     @since v2.0
     */
    Scheduler *_scheduler;
    
    /** @~english ActionManager associated with this director
     * @~chinese ActionManager与此相关
     @since v2.0
     */
    ActionManager *_actionManager;
    
    /** @~english EventDispatcher associated with this director
     * @~chinese EventDispatcher与此相关
     @since v3.0
     */
    EventDispatcher* _eventDispatcher;
    EventCustom *_eventProjectionChanged, *_eventAfterDraw, *_eventAfterVisit, *_eventBeforeUpdate, *_eventAfterUpdate;
        
    /* @~english delta time since last tick to main loop  @~chinese 三角洲自去年蜱虫主循环*/
	float _deltaTime;
    
    /* @~english The _openGLView, where everything is rendered, GLView is a abstract class,cocos2d-x provide GLViewImpl
     * @~chinese _openGLView,一切呈现,GLView是一个抽象类,cocos2d-x提供GLViewImpl
     which inherit from it as default renderer context,you can have your own by inherit from it*/
    GLView *_openGLView;

    //texture cache belongs to this director
    TextureCache *_textureCache;

    float _animationInterval;
    float _oldAnimationInterval;

    /* @~english landscape mode ?  @~chinese 景观模式?*/
    bool _landscape;
    
    bool _displayStats;
    float _accumDt;
    float _frameRate;
    
    LabelAtlas *_FPSLabel;
    LabelAtlas *_drawnBatchesLabel;
    LabelAtlas *_drawnVerticesLabel;
    
    /** @~english Whether or not the Director is paused  @~chinese 导演是否暂停*/
    bool _paused;

    /* @~english How many frames were called since the director started  @~chinese 导演开始以来有多少帧被称为*/
    unsigned int _totalFrames;
    float _secondsPerFrame;
    
    /* @~english The running scene  @~chinese 运行场景*/
    Scene *_runningScene;
    
    /* @~english will be the next 'runningScene' in the next frame
     * @~chinese 将成为下一个“runningScene”下一个框架
     nextScene is a weak reference. */
    Scene *_nextScene;
    
    /* @~english If true, then "old" scene will receive the cleanup message  @~chinese 如果这是真的,那么“旧”的场景将得到清理的消息*/
    bool _sendCleanupToScene;

    /* @~english scheduled scenes  @~chinese 预定的场景*/
    Vector<Scene*> _scenesStack;
    
    /* @~english last time the main loop was updated  @~chinese 最后一次更新主循环*/
    struct timeval *_lastUpdate;

    /* @~english whether or not the next delta time will be zero  @~chinese 是否下一个增量时间将是零*/
    bool _nextDeltaTimeZero;
    
    /* @~english projection used  @~chinese 投影使用*/
    Projection _projection;

    /* @~english window size in points  @~chinese 窗口大小的点*/
    Size _winSizeInPoints;
    
    /* @~english content scale factor  @~chinese 内容比例因子*/
    float _contentScaleFactor;

    /* @~english This object will be visited after the scene. Useful to hook a notification node  @~chinese 现场后将渲染这个对象。有用的钩通知节点*/
    Node *_notificationNode;

    /* @~english Renderer for the Director  @~chinese 渲染器的导演*/
    Renderer *_renderer;
    
    /* Default FrameBufferObject*/
    experimental::FrameBuffer* _defaultFBO;

    /* @~english Console for the director  @~chinese 控制台的导演*/
    Console *_console;

    bool _isStatusLabelUpdated;

    /* cocos2d thread id */
    std::thread::id _cocos2d_thread_id;

    // GLView will recreate stats labels to fit visible rect
    friend class GLView;
};

// end of base group
/** @~english @}  @~chinese @ }*/

/** 
 @brief @~english DisplayLinkDirector is a Director that synchronizes timers with the refresh rate of the display.
 
 Features and Limitations:
  - Scheduled timers & drawing are synchronizes with the refresh rate of the display
  - Only supports animation intervals of 1/60 1/30 & 1/15
 
 * @~chinese DisplayLinkDirector是一个导演,同步与显示器的刷新率计时器。
 * 
 * 特性和限制:
 * —将计时器&图纸与显示器的刷新频率同步
 * —只支持动画间隔为1
 * 
 @since v0.8.2
 */
class DisplayLinkDirector : public Director
{
public:
    DisplayLinkDirector() 
        : _invalid(false)
    {}
    virtual ~DisplayLinkDirector(){}

    //
    // Overrides
    //
    virtual void mainLoop() override;
    virtual void setAnimationInterval(float value) override;
    virtual void startAnimation() override;
    virtual void stopAnimation() override;

protected:
    bool _invalid;
};

NS_CC_END

#endif // __CCDIRECTOR_H__
