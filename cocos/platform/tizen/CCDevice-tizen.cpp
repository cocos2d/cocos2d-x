/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN

#include "platform/CCDevice.h"

#include <app.h>
#include <Evas.h>
#include <Elementary.h>
#include <Evas_Engine_Buffer.h>
#include <sensor.h>
#include <system_info.h>

#include "base/CCEventDispatcher.h"
#include "base/CCEventAcceleration.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"
#include "platform/tizen/CCApplication-tizen.h"

using namespace std;
NS_CC_BEGIN

static sensor_h s_sensorHandle = nullptr;
static sensor_listener_h s_sensorListener = nullptr;
static float s_sensorInterval = 30.0f;

#define GRAVITY_EARTH 9.80665f

static bool checkAccelerometerValues(sensor_event_s *sensor_data)
{
    for(int i = 0; i < sensor_data->value_count; ++i)
    {
        float value = sensor_data->values[i];

        if(isnan(value))//or other limitations
        {
            return false;
        }
    }
    return true;
}

static void accelerometer_sensor_cb(sensor_h _sensor, sensor_event_s *sensor_data, void *user_data)
{
    if(!checkAccelerometerValues(sensor_data))
    {
        CCLOG("sensor value is invalid!!");
        return;
    }
    if(3 != sensor_data->value_count)
    {
        return;
    }
    Acceleration *_acceleration = new Acceleration();
    _acceleration->x = sensor_data->values[0] / GRAVITY_EARTH;
    _acceleration->y = sensor_data->values[1] / GRAVITY_EARTH;
    _acceleration->z = sensor_data->values[2] / GRAVITY_EARTH;
    _acceleration->timestamp = sensor_data->timestamp;

    double tmp = _acceleration->x;
    Application *app = Application::getInstance();
    int orientation = elm_win_rotation_get(app->_win);

    switch (orientation)
    {
    case 0:
        _acceleration->x = _acceleration->y;
        _acceleration->y = tmp;
        break;

    case 90:
        _acceleration->x = -_acceleration->y;
        _acceleration->y = tmp;
        break;

    case 180:
        _acceleration->x = -_acceleration->y;
        _acceleration->y = -tmp;
        break;

    case 270:
        _acceleration->x = _acceleration->y;
        _acceleration->y = -tmp;
        break;
    default:
        CCLOG("unknown orientation");
    }

    cocos2d::EventAcceleration event(*_acceleration);
    auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchEvent(&event);
}

void stopAccelerometerSensor()
{
    if (s_sensorListener)
    {
        sensor_listener_stop(s_sensorListener);
        sensor_destroy_listener(s_sensorListener);
        s_sensorListener = nullptr;
        s_sensorHandle = nullptr;
    }
}

void startAccelerometerSensor()
{
    if (!s_sensorListener)
    {
        sensor_get_default_sensor(SENSOR_ACCELEROMETER, &s_sensorHandle);
        auto err = sensor_create_listener(s_sensorHandle, &s_sensorListener);
        if(SENSOR_ERROR_NONE != err)
        {
            CCLOG("create sensor failed!");
        }
        sensor_listener_set_event_cb(s_sensorListener, s_sensorInterval, accelerometer_sensor_cb, NULL);
        sensor_listener_start(s_sensorListener);
    }
}

static bool s_resumeAccelerometerSensor = false;

void pauseAccelerometerSensor()
{
    if (s_sensorListener)
    {
        s_resumeAccelerometerSensor = true;
        stopAccelerometerSensor();
    }
    else
    {
        s_resumeAccelerometerSensor = false;
    }
}

void resumeAccelerometerSensor()
{
    if (s_resumeAccelerometerSensor)
    {
        startAccelerometerSensor();
    }
}

void Device::setAccelerometerEnabled(bool isEnabled)
{
    if(isEnabled)
    {
        startAccelerometerSensor();
    }
    else
    {
        stopAccelerometerSensor();
    }
}

void Device::setAccelerometerInterval(float interval)
{
    s_sensorInterval = interval;
    if(s_sensorListener)
    {
        sensor_listener_set_interval(s_sensorListener, s_sensorInterval);
    }
}

int Device::getDPI()
{
    static int dpi = -1;
    if (dpi == -1)
    {
        auto ret = system_info_get_platform_int("tizen.org/feature/screen.dpi",&dpi);
        if(ret != SYSTEM_INFO_ERROR_NONE)
        {
            //error handing
            dpi = -1;
        }
    }
    return dpi;
}

static void getTextBitmapData(const char * text, const FontDefinition& textDefinition, Data& bitmapData, int &bitmapWidth, int &bitmapHeight)
{
    //create canvas object
    auto method = evas_render_method_lookup("buffer");
    if (method <= 0)
    {
        log("ERROR: evas was not compiled with 'buffer' engine!");
        return ;
    }

    //evas_init();//not necessary, removed when use Tizen 2.4.
    auto canvas = evas_new();
    if(!canvas){
        log("ERROR: could not instantiate new evas canvas.");
        return;
    }
    evas_output_method_set(canvas, method);

    std::string fontFullPath;
    if(textDefinition._fontName.empty())
    {
        fontFullPath = "Sans";
    }
    else
    {
        fontFullPath= FileUtils::getInstance()->fullPathForFilename(textDefinition._fontName);
    }

    const char* fontName = fontFullPath.c_str();
    const char* textAlign = "left";
    const char* textValign = "top";
    char richTextStyle[50];
    richTextStyle[0] = 0;

    if (textDefinition._stroke._strokeEnabled)
    {
        sprintf(richTextStyle,"style=outline outline_color=#%02X%02X%02X",
            textDefinition._stroke._strokeColor.r, textDefinition._stroke._strokeColor.g, textDefinition._stroke._strokeColor.b);
    }

    switch (textDefinition._alignment)
    {
    case TextHAlignment::CENTER:
        textAlign = "center";
        break;
    case TextHAlignment::RIGHT:
        textAlign = "right";
        break;
    default:
        break;
    }
    double valignment = 0.0;
    switch(textDefinition._vertAlignment)
    {
    case TextVAlignment::CENTER:
        textValign = "center";
        valignment = 0.5;
        break;
    case TextVAlignment::BOTTOM:
        textValign = "bottom";
        valignment = 1.0;
        break;
    default:
        break;
    }

    auto richText = (char*)malloc(strlen(text) + 150);
    sprintf(richText,"DEFAULT='font=%s font_size=%d align=%s valign=%s %s color=#%02X%02X%02X wrap=word'",
        fontName, textDefinition._fontSize, textAlign, textValign, richTextStyle,
        textDefinition._fontFillColor.b, textDefinition._fontFillColor.g, textDefinition._fontFillColor.r);

    auto entry = evas_object_textblock_add(canvas);
    auto st = evas_textblock_style_new();
    evas_textblock_style_set(st, richText);
    evas_object_textblock_style_set(entry, st);
    evas_textblock_style_free(st);
    evas_object_textblock_valign_set(entry, valignment);

    evas_object_textblock_text_markup_set(entry, evas_textblock_text_utf8_to_markup(entry, text));
    free(richText);

    evas_object_resize(entry, 2048, 0);//allocate one default size first.

    Evas_Coord width = textDefinition._dimensions.width;
    Evas_Coord height = textDefinition._dimensions.height;
    if(0==width*height)
    {
        evas_object_textblock_size_formatted_get(entry, &width, &height);
    }

    evas_object_resize(entry, width, height);

    //init canvas
    evas_output_size_set(canvas, width, height);
    evas_output_viewport_set(canvas, 0, 0, width, height);

    auto einfo = (Evas_Engine_Info_Buffer *)evas_engine_info_get(canvas);
    if (!einfo){
        log("ERROR: could not get evas engine info!");
        evas_free(canvas);
        return ;
    }

    // ARGB32 is sizeof(int), that is 4 bytes, per pixel
    bitmapWidth = width;
    bitmapHeight = height;
    void* pixels = malloc(bitmapWidth * bitmapHeight * 4);
    if (!pixels){
        log("ERROR: could not allocate canvas pixels!");
        evas_free(canvas);
        return;
    }

    einfo->info.depth_type = EVAS_ENGINE_BUFFER_DEPTH_ARGB32;
    einfo->info.dest_buffer = pixels;
    einfo->info.dest_buffer_row_bytes = bitmapWidth * sizeof(int);
    einfo->info.use_color_key = 0;
    einfo->info.alpha_threshold = 0;
    einfo->info.func.new_update_region = NULL;
    einfo->info.func.free_update_region = NULL;
    evas_engine_info_set(canvas, (Evas_Engine_Info *)einfo);

    //render
    evas_object_show(entry);
    auto updates = evas_render_updates(canvas);
    evas_render_updates_free(updates);
    
    bitmapData.fastSet((unsigned char*)pixels,bitmapWidth * bitmapHeight * 4);

    evas_free(canvas);
    //evas_shutdown();//not necessary, removed when use Tizen 2.4.
}

Data Device::getTextureDataForText(const char * text, const FontDefinition& textDefinition, TextAlign align, int &width, int &height, bool& hasPremultipliedAlpha)
{
    Data ret;
    do 
    {
        getTextBitmapData(text, textDefinition, ret, width, height);
        hasPremultipliedAlpha = true;
    } while (0);

    return ret;
}

void Device::setKeepScreenOn(bool value)
{
}

void Device::vibrate(float /*duration*/)
{
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN
