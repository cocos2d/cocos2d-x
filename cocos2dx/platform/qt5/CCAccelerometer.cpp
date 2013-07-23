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

#include "CCAccelerometer.h"
#include "AccelerometerListener.h"

#include <QAccelerometer>
#include <QAccelerometerReading>

NS_CC_BEGIN

static CCAccelerometer *
shared_accelerometer = NULL;

CCAccelerometer::CCAccelerometer()
    : m_accelerometer(new QAccelerometer)
    , m_listener(new AccelerometerListener(this))
    , m_delegate(NULL)
{
    QObject::connect(m_accelerometer, SIGNAL(readingChanged()),
            m_listener, SLOT(onReadingChanged()));
}

CCAccelerometer::~CCAccelerometer()
{
    delete m_listener;
    delete m_accelerometer;
}

CCAccelerometer *
CCAccelerometer::sharedAccelerometer()
{
    if (shared_accelerometer == NULL) {
        shared_accelerometer = new CCAccelerometer;
    }

    return shared_accelerometer;
}


void
CCAccelerometer::setDelegate(CCAccelerometerDelegate *pDelegate)
{
    m_delegate = pDelegate;
}

void
CCAccelerometer::setAccelerometerInterval(float interval)
{
    if (interval == 0.0) {
        m_accelerometer->setDataRate(0.0);
    } else {
        // Interval is specified in seconds
        m_accelerometer->setDataRate(1.0 / interval);
    }
}

void
CCAccelerometer::readingChanged()
{
    if (m_delegate == NULL) {
        return;
    }

    QAccelerometerReading *reading = m_accelerometer->reading();

    CCAcceleration accel;
    accel.x = reading->x();
    accel.y = reading->y();
    accel.z = reading->z();
    accel.timestamp = reading->timestamp();

    m_delegate->didAccelerate(&accel);
}

NS_CC_END
