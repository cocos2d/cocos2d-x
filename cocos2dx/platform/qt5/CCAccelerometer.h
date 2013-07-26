/**
 *
 * Cocos2D-X Qt 5 Platform
 *
 * Copyright (C) 2013 Jolla Ltd.
 * Contact: Thomas Perl <thomas.perl@jollamobile.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **/


#ifndef CCACCELEROMETER_QT5_H
#define CCACCELEROMETER_QT5_H

#include "platform/CCCommon.h"
#include "platform/CCAccelerometerDelegate.h"
#include <functional>

class QAccelerometer;
class AccelerometerListener;

NS_CC_BEGIN

class Accelerometer {
    public:
        Accelerometer();
        ~Accelerometer();

        static Accelerometer *sharedAccelerometer();

        void setDelegate(std::function<void(Acceleration*)> function);
        void setAccelerometerInterval(float interval);

        /* Functions to be called from AccelerometerListener */
        void readingChanged();

    private:
        QAccelerometer *m_accelerometer;
        AccelerometerListener *m_listener;
        std::function<void(Acceleration*)> m_function;
};

NS_CC_END

#endif /* CCACCELEROMETER_QT5_H */
