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

#include "CocostudioParserJsonTest.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "../CocostudioParserTest.h"
#include "../CustomWidget/CustomImageView.h"
#include "../CustomWidget/CustomImageViewReader.h"
#include "../CustomWidget/CustomParticleWidgetReader.h"
#include "../CustomWidget/CustomParticleWidget.h"


USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

// CustomImageLayer
CocostudioParserJsonLayer::CocostudioParserJsonLayer(std::string jsonFile)
{
    _jsonFile = jsonFile;
}

void CocostudioParserJsonLayer::onEnter()
{
    Layer::onEnter();
    
    GUIReader* guiReader = GUIReader::getInstance();
    guiReader->registerTypeAndCallBack("CustomImageView",
                                       &CustomImageView::createInstance,
                                       CustomImageViewReader::getInstance(),
                                       parseselector(CustomImageViewReader::setProperties));
    guiReader->registerTypeAndCallBack("CustomParticleWidget",
                                       &CustomParticleWidget::createInstance,
                                       CustomParticleWidgetReader::getInstance(),
                                       parseselector(CustomParticleWidgetReader::setProperties));
    
    Layout* layout = static_cast<Layout*>(guiReader->widgetFromJsonFile(_jsonFile.c_str()));
    layout->setScale(0.5);
    addChild(layout);
}


// CocostudioParserJsonScene

CocostudioParserJsonScene* CocostudioParserJsonScene::create(const std::string& jsonFile)
{
    auto scene = new (std::nothrow) CocostudioParserJsonScene;
    if (scene && scene->init())
    {
        auto layer = new (std::nothrow) CocostudioParserJsonLayer(jsonFile);
        scene->addChild(layer);
        layer->release();

        scene->autorelease();
    }
    else
    {
        delete scene;
        scene = nullptr;
    }
    
    return scene;
}
