/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#ifndef __CC_NODE_CACHE_H__
#define __CC_NODE_CACHE_H__

#include "CCTimeLine.h"
#include "cocostudio/DictionaryHelper.h"


namespace cocostudio {

class WidgetPropertiesReader0300;

namespace timeline{

class NodeCache
{
public:
    static NodeCache* getInstance();
    static void destroyInstance();

    void purge();

    void init();

    cocos2d::Node* createNode(const std::string& filename);

    cocos2d::Node* loadNodeWithFile(const std::string& fileName);
    cocos2d::Node* loadNodeWithContent(const std::string& content);
protected:

    cocos2d::Node* loadNode(const rapidjson::Value& json);
    
    void locateNodeWithMulresPosition(cocos2d::Node* node, const rapidjson::Value& json);

    void initNode(cocos2d::Node* node, const rapidjson::Value& json);

    // load nodes
    cocos2d::Node* loadSimpleNode(const rapidjson::Value& json);
    cocos2d::Node* loadSubGraph  (const rapidjson::Value& json);
    cocos2d::Node* loadSprite    (const rapidjson::Value& json);
    cocos2d::Node* loadParticle  (const rapidjson::Value& json);

    // load gui
    cocos2d::Node* loadWidget(const rapidjson::Value& json);

    typedef std::function<cocos2d::Node*(const rapidjson::Value& json)> NodeCreateFunc;
    typedef std::pair<std::string, NodeCreateFunc> Pair;

    std::unordered_map<std::string, NodeCreateFunc> _funcs;
    cocos2d::Map<std::string, cocos2d::Node*> _nodes;

    WidgetPropertiesReader0300* _guiReader;
};

}
}


#endif /*__CC_NODE_CACHE_H__*/
