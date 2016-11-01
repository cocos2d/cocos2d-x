//
//  CCBXNodeLoaderLibrary.cpp
//  cocos2d_libs
//
//  Created by Sergey on 29.10.14.
//
//

#include "CCBXNodeLoaderLibrary.h"
#include "CCBXNodeLoader.h"
#include "CCBXNodeColorLoader.h"
#include "CCBXScale9SpriteLoader.h"
#include "CCBXLabelTTFLoader.h"
#include "CCBXSpriteLoader.h"
#include "CCBXProgressTimerLoader.h"
#include "CCBXParticleSystemQuadLoader.h"
#include "CCBXFileLoader.h"

#include "CCBXWidgetLoader.h"
#include "CCBXButtonLoader.h"
#include "CCBXLayoutBoxLoader.h"
#include "CCBXTextLoader.h"
#include "CCBXImageViewLoader.h"
#include "CCBXLoadingBarLoader.h"
#include "CCBXScrollViewLoader.h"
#include "CCBXTextFieldLoader.h"
#include "CCBXSliderLoader.h"
#include "CCBXScissorsNodeLoader.h"
#include "CCBXScrollListViewLoader.h"
#include "CCBXEditBoxLoader.h"

NS_CC_BEGIN
namespace spritebuilder {
    
NodeLoaderLibrary *NodeLoaderLibrary::create()
{
    NodeLoaderLibrary *ret = new(std::nothrow) NodeLoaderLibrary();
    ret->autorelease();
    return ret;
}

NodeLoaderLibrary *NodeLoaderLibrary::createDefault()
{
    NodeLoaderLibrary *ret = new(std::nothrow) NodeLoaderLibrary();
    ret->autorelease();
    ret->registerDefaultLoaders();
    return ret;
}


static NodeLoaderLibrary *s_SharedNodeLoaderLibrary = nullptr;

NodeLoaderLibrary *NodeLoaderLibrary::getDefault()
{
    if (!s_SharedNodeLoaderLibrary)
    {
        s_SharedNodeLoaderLibrary = new (std::nothrow) NodeLoaderLibrary();
        s_SharedNodeLoaderLibrary->registerDefaultLoaders();
    }
    
    return s_SharedNodeLoaderLibrary;
}
    
NodeLoaderLibrary *NodeLoaderLibrary::copyDefault()
{
    return getDefault()->copy();
}
    
NodeLoaderLibrary *NodeLoaderLibrary::copy() const
{
    NodeLoaderLibrary *ret = new(std::nothrow) NodeLoaderLibrary();
    if(ret)
    {
        ret->autorelease();
        ret->_loaders = _loaders;
    }
    return ret;
}

NodeLoader *NodeLoaderLibrary::createNodeLoader(const std::string &name) const
{
    auto it = _loaders.find(name);
    if(it == _loaders.end())
        return nullptr;
    return it->second();
}

void NodeLoaderLibrary::registerNodeLoader(const std::string &name, const NodeLoaderCreateFuntion &func)
{
    _loaders.emplace(name, func);
}
    
void NodeLoaderLibrary::removeNodeLoader(const std::string &name)
{
    _loaders.erase(name);
}

NodeLoaderLibrary::NodeLoaderLibrary()
{
    
}

void NodeLoaderLibrary::registerDefaultLoaders()
{
    _loaders.emplace("CCNodeColor", NodeLoaderCreateFuntion(&NodeColorLoader::create));
    _loaders.emplace("CCNode", NodeLoaderCreateFuntion(&NodeLoader::create));
    _loaders.emplace("CCSprite", NodeLoaderCreateFuntion(&SpriteLoader::create));
    _loaders.emplace("CCSprite9Slice", NodeLoaderCreateFuntion(&Scale9SpriteLoader::create));
    _loaders.emplace("CCProgressNode", NodeLoaderCreateFuntion(&ProgressTimerLoader::create));
    _loaders.emplace("CCLabelTTF", NodeLoaderCreateFuntion(&LabelTTFLoader::create));
    _loaders.emplace("CCParticleSystem", NodeLoaderCreateFuntion(&ParticleSystemQuadLoader::create));
    _loaders.emplace("CCBFile", NodeLoaderCreateFuntion(&FileLoader::create));
    
    _loaders.emplace("CCWidget", NodeLoaderCreateFuntion(&WidgetLoader::create));
    _loaders.emplace("CCButton", NodeLoaderCreateFuntion(&ButtonLoader::create));
    _loaders.emplace("CCText", NodeLoaderCreateFuntion(&TextLoader::create));
    _loaders.emplace("CCLayoutBox", NodeLoaderCreateFuntion(&LayoutBoxLoader::create));
    _loaders.emplace("CCImage", NodeLoaderCreateFuntion(&ImageViewLoader::create));
    _loaders.emplace("CCLoadingBar", NodeLoaderCreateFuntion(&LoadingBarLoader::create));
    _loaders.emplace("CCScrollView", NodeLoaderCreateFuntion(&ScrollViewLoader::create));
    _loaders.emplace("CCTextField", NodeLoaderCreateFuntion(&TextFieldLoader::create));
    _loaders.emplace("CCSlider", NodeLoaderCreateFuntion(&SliderLoader::create));
    _loaders.emplace("CCScissorsNode", NodeLoaderCreateFuntion(&ScissorsNodeLoader::create));
    _loaders.emplace("CCScrollListView", NodeLoaderCreateFuntion(&ScrollListViewLoader::create));
    _loaders.emplace("CCEditBox", NodeLoaderCreateFuntion(&EditBoxLoader::create));
}

}

NS_CC_END
