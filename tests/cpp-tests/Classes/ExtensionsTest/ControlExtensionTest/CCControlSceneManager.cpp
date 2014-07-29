/*
 * ControlSceneManager.m
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
    kControlSliderTest = 0,
    kControlColourPickerTest,
    kControlSwitchTest,
    kControlButtonTest_HelloVariableSize,
    kControlButtonTest_Event,
    kControlButtonTest_Styling,
    kControlPotentiometerTest,
    kControlStepperTest,
    kControlTestMax
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

static ControlSceneManager *sharedInstance = nullptr;


ControlSceneManager::ControlSceneManager()
{
    _currentControlSceneId = kControlSliderTest;
}

ControlSceneManager::~ControlSceneManager()
{
    CC_SAFE_RELEASE(sharedInstance);
}

ControlSceneManager * ControlSceneManager::sharedControlSceneManager()
{
    if (sharedInstance == nullptr)
    {
        sharedInstance = new ControlSceneManager();
    }
    return sharedInstance;
}

Scene *ControlSceneManager::nextControlScene()
{
    _currentControlSceneId = (_currentControlSceneId + 1) % kControlTestMax;

    return currentControlScene();
}

Scene *ControlSceneManager::previousControlScene()
{
    _currentControlSceneId = _currentControlSceneId - 1;
    if (_currentControlSceneId < 0)
    {
        _currentControlSceneId = kControlTestMax - 1;
    }

    return currentControlScene();
}

Scene *ControlSceneManager::currentControlScene()
{
    switch (_currentControlSceneId)
    {
    case kControlSliderTest: return ControlSliderTest::sceneWithTitle(s_testArray[_currentControlSceneId]);
    case kControlColourPickerTest:return ControlColourPickerTest::sceneWithTitle(s_testArray[_currentControlSceneId]);
    case kControlSwitchTest:return ControlSwitchTest::sceneWithTitle(s_testArray[_currentControlSceneId]);
    case kControlButtonTest_HelloVariableSize:return ControlButtonTest_HelloVariableSize::sceneWithTitle(s_testArray[_currentControlSceneId]);
    case kControlButtonTest_Event:return ControlButtonTest_Event::sceneWithTitle(s_testArray[_currentControlSceneId]);
    case kControlButtonTest_Styling:return ControlButtonTest_Styling::sceneWithTitle(s_testArray[_currentControlSceneId]);
    case kControlPotentiometerTest:return ControlPotentiometerTest::sceneWithTitle(s_testArray[_currentControlSceneId]);
    case kControlStepperTest:return ControlStepperTest::sceneWithTitle(s_testArray[_currentControlSceneId]);
    }
    return nullptr;
}
