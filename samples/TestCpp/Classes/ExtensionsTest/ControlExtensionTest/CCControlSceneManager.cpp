/*
 * CCControlSceneManager.m
 *
 * Copyright (c) 2011 Yannick Loriot
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
 */

#include "CCControlSceneManager.h"
#include "CCControlScene.h"
#include "CCControlButtonTest/CCControlButtonTest.h"
#include "CCControlColourPicker/CCControlColourPickerTest.h"
#include "CCControlSliderTest/CCControlSliderTest.h"
#include "CCControlSwitchTest/CCControlSwitchTest.h"
#include "CCControlPotentiometerTest/CCControlPotentiometerTest.h"
#include "CCControlStepperTest/CCControlStepperTest.h"

USING_NS_CC;

enum
{
    kCCControlSliderTest = 0,
    kCCControlColourPickerTest,
    kCCControlSwitchTest,
    kCCControlButtonTest_HelloVariableSize,
    kCCControlButtonTest_Event,
    kCCControlButtonTest_Styling,
    kCCControlPotentiometerTest,
    kCCControlStepperTest,
    kCCControlTestMax
};

static const char* s_testArray[] = {
    "CCControlSliderTest",
    "ControlColourPickerTest",
    "ControlSwitchTest",
    "ControlButtonTest_HelloVariableSize",
    "ControlButtonTest_Event",
    "ControlButtonTest_Styling",
    "ControlPotentiometerTest",
    "CCControlStepperTest"
};

static CCControlSceneManager *sharedInstance = NULL;


CCControlSceneManager::CCControlSceneManager()
{
    m_nCurrentControlSceneId = kCCControlSliderTest;
}

CCControlSceneManager::~CCControlSceneManager()
{
    CC_SAFE_RELEASE(sharedInstance);
}

CCControlSceneManager * CCControlSceneManager::sharedControlSceneManager()
{
    if (sharedInstance == NULL)
    {
        sharedInstance = new CCControlSceneManager();
    }
    return sharedInstance;
}

CCScene *CCControlSceneManager::nextControlScene()
{
    m_nCurrentControlSceneId = (m_nCurrentControlSceneId + 1) % kCCControlTestMax;

    return currentControlScene();
}

CCScene *CCControlSceneManager::previousControlScene()
{
    m_nCurrentControlSceneId = m_nCurrentControlSceneId - 1;
    if (m_nCurrentControlSceneId < 0)
    {
        m_nCurrentControlSceneId = kCCControlTestMax - 1;
    }

    return currentControlScene();
}

CCScene *CCControlSceneManager::currentControlScene()
{
    switch (m_nCurrentControlSceneId)
    {
    case kCCControlSliderTest: return CCControlSliderTest::sceneWithTitle(s_testArray[m_nCurrentControlSceneId]);
    case kCCControlColourPickerTest:return CCControlColourPickerTest::sceneWithTitle(s_testArray[m_nCurrentControlSceneId]);
    case kCCControlSwitchTest:return CCControlSwitchTest::sceneWithTitle(s_testArray[m_nCurrentControlSceneId]);
    case kCCControlButtonTest_HelloVariableSize:return CCControlButtonTest_HelloVariableSize::sceneWithTitle(s_testArray[m_nCurrentControlSceneId]);
    case kCCControlButtonTest_Event:return CCControlButtonTest_Event::sceneWithTitle(s_testArray[m_nCurrentControlSceneId]);
    case kCCControlButtonTest_Styling:return CCControlButtonTest_Styling::sceneWithTitle(s_testArray[m_nCurrentControlSceneId]);
    case kCCControlPotentiometerTest:return CCControlPotentiometerTest::sceneWithTitle(s_testArray[m_nCurrentControlSceneId]);
    case kCCControlStepperTest:return CCControlStepperTest::sceneWithTitle(s_testArray[m_nCurrentControlSceneId]);
    }
    return NULL;
}
