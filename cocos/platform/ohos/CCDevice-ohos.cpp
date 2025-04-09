#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
#include "platform/CCDevice.h"
#include "base/ccTypes.h"
#include "CCTextBitmap.h"
#include "napi/helper/NapiHelper.h"
#include "sensors/oh_sensor.h"
#include <window_manager/oh_display_info.h>
#include <window_manager/oh_display_manager.h>
#include "cocos2d.h"

NS_CC_BEGIN

#define TG3_GRAVITY_EARTH                    (9.80665f)
// The default accelerometer interval is 10000000 ns, that is, 10 ms.
float SENSOR_SAMPLE_PERIOD = 10000000.0f;
Sensor_Subscriber *accelerometer_g_user = nullptr;
Sensor_SubscriptionAttribute *accelerometer_sensor_attr = nullptr;
Sensor_SubscriptionId *accelerometer_sensor_id = nullptr;
cocos2d::Acceleration *acceleration = nullptr;

class DeviceSensor {
public:
    static void enableSensor() {
        enableAccelerometer();
    }
    
    static void disableSensor() {
        disableAccelerometer();
    }
    
private:
    static void enableAccelerometer() {
        if (accelerometer_g_user != nullptr) {
            LOGI("Sensor Accelerometer is Listen");
            return;
        }
        accelerometer_g_user = OH_Sensor_CreateSubscriber();
        OH_SensorSubscriber_SetCallback(accelerometer_g_user, dispatchAccelerometer);
        accelerometer_sensor_attr = OH_Sensor_CreateSubscriptionAttribute();
        OH_SensorSubscriptionAttribute_SetSamplingInterval(accelerometer_sensor_attr, SENSOR_SAMPLE_PERIOD);
        
        accelerometer_sensor_id = OH_Sensor_CreateSubscriptionId();
        OH_SensorSubscriptionId_SetType(accelerometer_sensor_id, SENSOR_TYPE_ACCELEROMETER);
        
        OH_Sensor_Subscribe(accelerometer_sensor_id, accelerometer_sensor_attr, accelerometer_g_user);
        LOGI("Sensor Accelerometer is enable Listen");
    }
    
    static void disableAccelerometer() {
        if (accelerometer_g_user == nullptr) {
            LOGI("Sensor Accelerometer is not Listen");
            return;
        }
        if (accelerometer_sensor_id != nullptr) {
            OH_Sensor_Unsubscribe(accelerometer_sensor_id, accelerometer_g_user);
            OH_Sensor_DestroySubscriptionId(accelerometer_sensor_id);   
        }
        if (accelerometer_sensor_attr != nullptr) {
            OH_Sensor_DestroySubscriptionAttribute(accelerometer_sensor_attr);
        }
        OH_Sensor_DestroySubscriber(accelerometer_g_user);
        accelerometer_g_user = nullptr;
        accelerometer_sensor_id = nullptr;
        accelerometer_sensor_attr = nullptr;
        LOGI("Sensor Accelerometer is disable Listen");
    }
    
    static void dispatchAccelerometer(Sensor_Event *event) {
        if (event == nullptr) {
            LOGI("dispatchAccelerometer event is null");
            return;
        }
        
        float *data = nullptr;
        uint32_t length = 0;
        int32_t ret = OH_SensorEvent_GetData(event, &data, &length); 
        if (ret != SENSOR_SUCCESS) {
            return;
        }
        
        int64_t timeStamp = -1;
        OH_SensorEvent_GetTimestamp(event, &timeStamp); 
        
        NativeDisplayManager_Rotation displayRotation;
        NativeDisplayManager_ErrorCode errCode = OH_NativeDisplayManager_GetDefaultDisplayRotation(&displayRotation);
        if (errCode != NativeDisplayManager_ErrorCode::DISPLAY_MANAGER_OK) {
            LOGI("dispatchAccelerometer displayRotation error code = %{public}d", errCode);
            return;
        }
        
        double x, y, z;
        
        if (displayRotation == DISPLAY_MANAGER_ROTATION_0) {
            x = data[0];
            y = data[1];
            z = data[2];
        } else if (displayRotation == DISPLAY_MANAGER_ROTATION_90) {
            x = data[1];
            y = -data[0];
            z = data[2];
        } else if (displayRotation == DISPLAY_MANAGER_ROTATION_180) {
            x = -data[0];
            y = -data[1];
            z = data[2];
        } else if (displayRotation == DISPLAY_MANAGER_ROTATION_270) {
            x = -data[1];
            y = data[0];
            z = data[2]; 
        }
        
        if (acceleration == nullptr) {
            acceleration = new (std::nothrow) cocos2d::Acceleration();
        }
        
        acceleration->x = -(x / TG3_GRAVITY_EARTH);
        acceleration->y = -(y / TG3_GRAVITY_EARTH);
        acceleration->z = -(z / TG3_GRAVITY_EARTH);
        acceleration->timestamp = (double)timeStamp;
        
    }
};


int Device::getDPI() {
    static int dpi = -1;
    if (dpi == -1)
    {
        dpi = JSFunction::getFunction("DeviceUtils.getDpi").invoke<int>();
    }
    return dpi;
}

void Device::setAccelerometerEnabled(bool isEnabled) {
    if (isEnabled) {
        DeviceSensor::enableSensor();
    }
    else {
        DeviceSensor::disableSensor();
    }
}

void Device::sendAndClearAcc() {
    if (acceleration == nullptr) {
        return;
    }
    cocos2d::EventAcceleration cocosEvent(*acceleration);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&cocosEvent);
    acceleration = nullptr;
}

void Device::setAccelerometerInterval(float interval) {
    if (interval == SENSOR_SAMPLE_PERIOD) {
        return;
    }
    SENSOR_SAMPLE_PERIOD = interval;
    if (accelerometer_sensor_attr != nullptr) {
     OH_SensorSubscriptionAttribute_SetSamplingInterval(accelerometer_sensor_attr, SENSOR_SAMPLE_PERIOD);   
    }
//     Js_Cocos2dxHelper::setAccelerometerInterval(interval);
}

class BitmapDC {
public:

    BitmapDC()
    : m_nWidth(0)
    , m_nHeight(0)
    , m_pData(NULL) {
    }

    ~BitmapDC(void) {
        if (m_pData) {
            delete [] m_pData;
        }
    }
    
    bool getBitmapWithDrawing(	const char *text, int nWidth, int nHeight, Device::TextAlign eAlignMask, const FontDefinition& textDefinition) {
        CCTextBitmap *cCtextBitmap = new CCTextBitmap();
        CCTextBitmap::createCCTextBitmap(cCtextBitmap, text, textDefinition._fontName.data(), textDefinition._fontAlpha, textDefinition._fontFillColor.r, 
            textDefinition._fontFillColor.g, textDefinition._fontFillColor.b ,eAlignMask, nWidth, nHeight, textDefinition._fontSize);
        void* pixels = cCtextBitmap->getPixelAddr();
        cocos2d::BitmapDC& bitmapDC = sharedBitmapDC();
        bitmapDC.m_nWidth = cCtextBitmap->GetWidth();
        bitmapDC.m_nHeight = cCtextBitmap->GetHeight();
        long size = bitmapDC.m_nWidth * bitmapDC.m_nHeight * 4;
        bitmapDC.m_pData = (unsigned char*)malloc(sizeof(unsigned char) * size);
        memcpy(bitmapDC.m_pData, pixels, size);
        
        delete cCtextBitmap;
        return true;
    }

public:
    int m_nWidth;
    int m_nHeight;
    unsigned char *m_pData;


    
    static BitmapDC& sharedBitmapDC() {
        // TBD not safe for multi threads
        static BitmapDC s_BmpDC;
        return s_BmpDC;
    }
};

Data Device::getTextureDataForText(const char * text, const FontDefinition& textDefinition, TextAlign align, int &width, int &height, bool& hasPremultipliedAlpha) {
    Data ret;
    do {
        BitmapDC &dc = BitmapDC::sharedBitmapDC();
        if(!dc.getBitmapWithDrawing(text, (int)textDefinition._dimensions.width, (int)textDefinition._dimensions.height, align, textDefinition )) { 
            break;
        };

        width = dc.m_nWidth;
        height = dc.m_nHeight;
        ret.fastSet(dc.m_pData,width * height * 4);
        hasPremultipliedAlpha = true;
    } while (0);

    return ret;
}


void Device::setKeepScreenOn(bool value) {
    JSFunction::getFunction("DeviceUtils.setKeepScreenOn").invoke<void>(value);
}

void Device::vibrate(float duration) {
    JSFunction::getFunction("DeviceUtils.startVibration").invoke<void>(duration);
}
NS_CC_END
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
