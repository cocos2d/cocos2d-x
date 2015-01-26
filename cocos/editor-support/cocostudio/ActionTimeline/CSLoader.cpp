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

#include "CSLoader.h"

#include "base/ObjectFactory.h"

#include "../../cocos/ui/CocosGUI.h"
#include "CCActionTimelineCache.h"
#include "CCActionTimeline.h"
#include "CCActionTimelineNode.h"
#include "../CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CSParseBinary_generated.h"

#include "cocostudio/WidgetReader/NodeReaderProtocol.h"
#include "cocostudio/WidgetReader/NodeReaderDefine.h"

#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "cocostudio/WidgetReader/SingleNodeReader/SingleNodeReader.h"
#include "cocostudio/WidgetReader/SpriteReader/SpriteReader.h"
#include "cocostudio/WidgetReader/ParticleReader/ParticleReader.h"
#include "cocostudio/WidgetReader/GameMapReader/GameMapReader.h"
#include "cocostudio/WidgetReader/ProjectNodeReader/ProjectNodeReader.h"
#include "cocostudio/WidgetReader/ComAudioReader/ComAudioReader.h"

#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "cocostudio/WidgetReader/CheckBoxReader/CheckBoxReader.h"
#include "cocostudio/WidgetReader/ImageViewReader/ImageViewReader.h"
#include "cocostudio/WidgetReader/TextBMFontReader/TextBMFontReader.h"
#include "cocostudio/WidgetReader/TextReader/TextReader.h"
#include "cocostudio/WidgetReader/TextFieldReader/TextFieldReader.h"
#include "cocostudio/WidgetReader/TextAtlasReader/TextAtlasReader.h"
#include "cocostudio/WidgetReader/LoadingBarReader/LoadingBarReader.h"
#include "cocostudio/WidgetReader/SliderReader/SliderReader.h"
#include "cocostudio/WidgetReader/LayoutReader/LayoutReader.h"
#include "cocostudio/WidgetReader/ScrollViewReader/ScrollViewReader.h"
#include "cocostudio/WidgetReader/PageViewReader/PageViewReader.h"
#include "cocostudio/WidgetReader/ListViewReader/ListViewReader.h"
#include "cocostudio/WidgetReader/ArmatureNodeReader/ArmatureNodeReader.h"

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/util.h"

#include "cocostudio/FlatBuffersSerialize.h"

#include "cocostudio/WidgetCallBackHandlerProtocol.h"

#include <fstream>

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocostudio::timeline;
/* peterson */
using namespace flatbuffers;
/**/

NS_CC_BEGIN

static const char* ClassName_Node     = "Node";
static const char* ClassName_SubGraph = "SubGraph";
static const char* ClassName_Sprite   = "Sprite";
static const char* ClassName_Particle = "Particle";
static const char* ClassName_TMXTiledMap = "TMXTiledMap";

static const char* ClassName_Panel      = "Panel";
static const char* ClassName_Button     = "Button";
static const char* ClassName_CheckBox   = "CheckBox";
static const char* ClassName_ImageView  = "ImageView";
static const char* ClassName_TextAtlas  = "TextAtlas";
static const char* ClassName_LabelAtlas = "LabelAtlas";
static const char* ClassName_LabelBMFont= "LabelBMFont";
static const char* ClassName_TextBMFont = "TextBMFont";
static const char* ClassName_Text       = "Text";
static const char* ClassName_LoadingBar = "LoadingBar";
static const char* ClassName_TextField  = "TextField";
static const char* ClassName_Slider     = "Slider";
static const char* ClassName_Layout     = "Layout";
static const char* ClassName_ScrollView = "ScrollView";
static const char* ClassName_ListView   = "ListView";
static const char* ClassName_PageView   = "PageView";
static const char* ClassName_Widget     = "Widget";
static const char* ClassName_Label      = "Label";

static const char* ClassName_ComAudio = "ComAudio";


static const char* NODE        = "nodeTree";
static const char* CHILDREN    = "children";
static const char* CLASSNAME   = "classname";
static const char* FILE_PATH   = "fileName";
static const char* PLIST_FILE  = "plistFile";
static const char* TMX_FILE  = "tmxFile";
static const char* TMX_STRING  = "tmxString";
static const char* RESOURCE_PATH  = "resourcePath";

static const char* COMPONENTS     = "components";
static const char* COMPONENT_TYPE     = "componentType";
static const char* COMPONENT_NAME  = "componentName";
static const char* COMPONENT_ENABLED  = "componentEnabled";
static const char* COMPONENT_AUDIO_FILE_PATH  = "comAudioFilePath";
static const char* COMPONENT_LOOP  = "comAudioloop";

static const char* TAG         = "tag";
static const char* ACTION_TAG  = "actionTag";

static const char* OPTIONS     = "options";

static const char* WIDTH            = "width";
static const char* HEIGHT           = "height";
static const char* X                = "x";
static const char* Y                = "y";
static const char* SCALE_X          = "scaleX";
static const char* SCALE_Y          = "scaleY";
static const char* SKEW_X           = "skewX";
static const char* SKEW_Y           = "skewY";
static const char* ROTATION         = "rotation";
static const char* ROTATION_SKEW_X  = "rotationSkewX";
static const char* ROTATION_SKEW_Y  = "rotationSkewY";
static const char* ANCHOR_X         = "anchorPointX";
static const char* ANCHOR_Y         = "anchorPointY";
static const char* ALPHA            = "opacity";
static const char* RED              = "colorR";
static const char* GREEN            = "colorG";
static const char* BLUE             = "colorB";
static const char* ZORDER           = "ZOrder";
static const char* PARTICLE_NUM     = "particleNum";
static const char* FLIPX            = "flipX";
static const char* FLIPY            = "flipY";
static const char* VISIBLE          = "visible";

static const char* TEXTURES     = "textures";
static const char* TEXTURES_PNG = "texturesPng";

static const char* MONO_COCOS2D_VERSION     = "cocos2dVersion";


// CSLoader
static CSLoader* _sharedCSLoader = nullptr;

CSLoader* CSLoader::getInstance()
{
    if (! _sharedCSLoader)
    {
        _sharedCSLoader = new CSLoader();
        _sharedCSLoader->init();
    }
    
    return _sharedCSLoader;
}

void CSLoader::destroyInstance()
{
    CC_SAFE_DELETE(_sharedCSLoader);
    ActionTimelineCache::destroyInstance();
}

CSLoader::CSLoader()
: _recordJsonPath(true)
, _jsonPath("")
, _monoCocos2dxVersion("")
, _rootNode(nullptr)
, _csBuildID("2.1.0.0")
{
    CREATE_CLASS_NODE_READER_INFO(NodeReader);
    CREATE_CLASS_NODE_READER_INFO(SingleNodeReader);
    CREATE_CLASS_NODE_READER_INFO(SpriteReader);
    CREATE_CLASS_NODE_READER_INFO(ParticleReader);
    CREATE_CLASS_NODE_READER_INFO(GameMapReader);
    
    CREATE_CLASS_NODE_READER_INFO(ButtonReader);
    CREATE_CLASS_NODE_READER_INFO(CheckBoxReader);
    CREATE_CLASS_NODE_READER_INFO(ImageViewReader);
    CREATE_CLASS_NODE_READER_INFO(TextBMFontReader);
    CREATE_CLASS_NODE_READER_INFO(TextReader);
    CREATE_CLASS_NODE_READER_INFO(TextFieldReader);
    CREATE_CLASS_NODE_READER_INFO(TextAtlasReader);
    CREATE_CLASS_NODE_READER_INFO(LoadingBarReader);
    CREATE_CLASS_NODE_READER_INFO(SliderReader);
    CREATE_CLASS_NODE_READER_INFO(LayoutReader);
    CREATE_CLASS_NODE_READER_INFO(ScrollViewReader);
    CREATE_CLASS_NODE_READER_INFO(PageViewReader);
    CREATE_CLASS_NODE_READER_INFO(ListViewReader);
    
    CREATE_CLASS_NODE_READER_INFO(ArmatureNodeReader);
    
}

void CSLoader::purge()
{
}

void CSLoader::init()
{
    using namespace std::placeholders;
    
    _funcs.insert(Pair(ClassName_Node,      std::bind(&CSLoader::loadSimpleNode, this, _1)));
    _funcs.insert(Pair(ClassName_SubGraph,  std::bind(&CSLoader::loadSubGraph,   this, _1)));
    _funcs.insert(Pair(ClassName_Sprite,    std::bind(&CSLoader::loadSprite,     this, _1)));
    _funcs.insert(Pair(ClassName_Particle,  std::bind(&CSLoader::loadParticle,   this, _1)));
    _funcs.insert(Pair(ClassName_TMXTiledMap,  std::bind(&CSLoader::loadTMXTiledMap,   this, _1)));
    _funcs.insert(Pair(ClassName_LabelAtlas,std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_LabelBMFont,std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Panel,     std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Button,    std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_CheckBox,  std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_ImageView, std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_TextAtlas, std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_TextBMFont,std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Text,      std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_LoadingBar,std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_TextField, std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Slider,    std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Layout,    std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_ScrollView,std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_ListView,  std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_PageView,  std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Widget,    std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Label,     std::bind(&CSLoader::loadWidget,   this, _1)));
    
    _componentFuncs.insert(ComponentPair(ClassName_ComAudio, std::bind(&CSLoader::loadComAudio, this, _1)));
    
}

Node* CSLoader::createNode(const std::string& filename)
{
    std::string path = filename;
    size_t pos = path.find_last_of('.');
    std::string suffix = path.substr(pos + 1, path.length());
    CCLOG("suffix = %s", suffix.c_str());
    
    CSLoader* load = CSLoader::getInstance();
    
    if (suffix == "csb")
    {
        return load->createNodeWithFlatBuffersFile(filename);
    }
    else if (suffix == "json" || suffix == "ExportJson")
    {
        return load->createNodeFromJson(filename);
    }
    
    return nullptr;
}

ActionTimeline* CSLoader::createTimeline(const std::string &filename)
{
    std::string path = filename;
    size_t pos = path.find_last_of('.');
    std::string suffix = path.substr(pos + 1, path.length());
    CCLOG("suffix = %s", suffix.c_str());
    
    ActionTimelineCache* cache = ActionTimelineCache::getInstance();
    
    if (suffix == "csb")
    {
        return cache->createActionWithFlatBuffersFile(filename);
    }
    else if (suffix == "json" || suffix == "ExportJson")
    {
        return cache->createActionFromJson(filename);
    }
    
    return nullptr;
}

/*
ActionTimelineNode* CSLoader::createActionTimelineNode(const std::string& filename)
{
    Node* root = createNode(filename);
    ActionTimeline* action = createTimeline(filename);
    
    if(root && action)
    {
        root->runAction(action);
        action->gotoFrameAndPlay(0);
    }
    
    ActionTimelineNode* node = ActionTimelineNode::create(root, action);
    return node;
}
ActionTimelineNode* CSLoader::createActionTimelineNode(const std::string& filename, int startIndex, int endIndex, bool loop)
{
    ActionTimelineNode* node = createActionTimelineNode(filename);
    ActionTimeline* action = node->getActionTimeline();
    if(action)
        action->gotoFrameAndPlay(startIndex, endIndex, loop);
    
    return node;
}
 */



Node* CSLoader::createNodeFromJson(const std::string& filename)
{
    if (_recordJsonPath)
    {
        std::string jsonPath = filename.substr(0, filename.find_last_of('/') + 1);
        GUIReader::getInstance()->setFilePath(jsonPath);
        
        _jsonPath = jsonPath;
    }
    else
    {
        GUIReader::getInstance()->setFilePath("");
        _jsonPath = "";
    }
    
    Node* node = loadNodeWithFile(filename);
    
    return node;
}

Node* CSLoader::loadNodeWithFile(const std::string& fileName)
{
    // Read content from file
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(fileName);
    
    Node* node = loadNodeWithContent(contentStr);
    
    // Load animation data from file
    ActionTimelineCache::getInstance()->loadAnimationActionWithContent(fileName, contentStr);
    
    return node;
}

Node* CSLoader::loadNodeWithContent(const std::string& content)
{
    rapidjson::Document doc;
    doc.Parse<0>(content.c_str());
    if (doc.HasParseError())
    {
        CCLOG("GetParseError %s\n", doc.GetParseError());
    }
    
    // cocos2dx version mono editor is based on
    _monoCocos2dxVersion = DICTOOL->getStringValue_json(doc, MONO_COCOS2D_VERSION, "");
    
    // decode plist
    int length = DICTOOL->getArrayCount_json(doc, TEXTURES);
    
    for(int i=0; i<length; i++)
    {
        std::string plist = DICTOOL->getStringValueFromArray_json(doc, TEXTURES, i);
        std::string png   = DICTOOL->getStringValueFromArray_json(doc, TEXTURES_PNG, i);
        plist = _jsonPath + plist;
        png   = _jsonPath + png;
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist, png);
    }
    
    // decode node tree
    const rapidjson::Value& subJson = DICTOOL->getSubDictionary_json(doc, NODE);
    Node* root = loadNode(subJson);
    root->release();
    
    return root;
}

Node* CSLoader::loadNode(const rapidjson::Value& json)
{
    Node* node = nullptr;
    std::string nodeType = DICTOOL->getStringValue_json(json, CLASSNAME);
    
    NodeCreateFunc func = _funcs[nodeType];
    if (func != nullptr)
    {
        const rapidjson::Value& options = DICTOOL->getSubDictionary_json(json, OPTIONS);
        node = func(options);
        
        // component
        if (node)
        {
            const rapidjson::Value& components = DICTOOL->getSubDictionary_json(options, COMPONENTS);
            int componentSize = DICTOOL->getArrayCount_json(options, COMPONENTS, 0);
            for (int i = 0; i < componentSize; ++i)
            {
                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(components, COMPONENTS, i);
                Component* component = loadComponent(dic);
                if (component)
                {
                    node->addComponent(component);
                }
            }
        }
    }
    
    if(node)
    {
        int length = DICTOOL->getArrayCount_json(json, CHILDREN, 0);
        for (int i = 0; i<length; i++)
        {
            const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, CHILDREN, i);
            Node* child = loadNode(dic);
            if (child)
            {
                PageView* pageView = dynamic_cast<PageView*>(node);
                ListView* listView = dynamic_cast<ListView*>(node);
                if (pageView)
                {
                    Layout* layout = dynamic_cast<Layout*>(child);
                    if (layout)
                    {
                        pageView->addPage(layout);
                    }
                }
                else if (listView)
                {
                    Widget* widget = dynamic_cast<Widget*>(child);
                    if (widget)
                    {
                        listView->pushBackCustomItem(widget);
                    }
                }
                else
                {
                    if (_monoCocos2dxVersion != "3.x")
                    {
                        Widget* widget = dynamic_cast<Widget*>(child);
                        Widget* parent = dynamic_cast<Widget*>(node);
                        if (widget
                            && parent
                            && !dynamic_cast<Layout*>(parent))
                        {
                            if (widget->getPositionType() == ui::Widget::PositionType::PERCENT)
                            {
                                widget->setPositionPercent(Vec2(widget->getPositionPercent().x + parent->getAnchorPoint().x, widget->getPositionPercent().y + parent->getAnchorPoint().y));
                                widget->setPosition(Vec2(widget->getPositionX() + parent->getAnchorPointInPoints().x, widget->getPositionY() + parent->getAnchorPointInPoints().y));
                            }
                            else
                            {
                                Size parentSize = parent->getContentSize();
                                widget->setPosition(Vec2(widget->getPositionX() + parentSize.width * parent->getAnchorPoint().x,
                                                         widget->getPositionY() + parentSize.height * parent->getAnchorPoint().y));
                            }
                        }
                    }
                    
                    node->addChild(child);
                }
                child->release();
            }
        }
    }
    else
    {
        CCLOG("Not supported NodeType: %s", nodeType.c_str());
    }
    
    return node;
}

void CSLoader::initNode(Node* node, const rapidjson::Value& json)
{
    float width         = DICTOOL->getFloatValue_json(json, WIDTH);
    float height        = DICTOOL->getFloatValue_json(json, HEIGHT);
    float x             = DICTOOL->getFloatValue_json(json, X);
    float y             = DICTOOL->getFloatValue_json(json, Y);
    float scalex        = DICTOOL->getFloatValue_json(json, SCALE_X, 1);
    float scaley        = DICTOOL->getFloatValue_json(json, SCALE_Y, 1);
    float rotation      = DICTOOL->getFloatValue_json(json, ROTATION);
    float rotationSkewX = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_X);
    float rotationSkewY = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_Y);
    float skewx         = DICTOOL->getFloatValue_json(json, SKEW_X);
    float skewy         = DICTOOL->getFloatValue_json(json, SKEW_Y);
    float anchorx       = DICTOOL->getFloatValue_json(json, ANCHOR_X, 0.5f);
    float anchory       = DICTOOL->getFloatValue_json(json, ANCHOR_Y, 0.5f);
    GLubyte alpha       = (GLubyte)DICTOOL->getIntValue_json(json, ALPHA, 255);
    GLubyte red         = (GLubyte)DICTOOL->getIntValue_json(json, RED, 255);
    GLubyte green       = (GLubyte)DICTOOL->getIntValue_json(json, GREEN, 255);
    GLubyte blue        = (GLubyte)DICTOOL->getIntValue_json(json, BLUE, 255);
    int zorder		    = DICTOOL->getIntValue_json(json, ZORDER);
    int tag             = DICTOOL->getIntValue_json(json, TAG);
    int actionTag       = DICTOOL->getIntValue_json(json, ACTION_TAG);
    bool visible        = DICTOOL->getBooleanValue_json(json, VISIBLE);
    
    if(x != 0 || y != 0)
        node->setPosition(Point(x, y));
    if(scalex != 1)
        node->setScaleX(scalex);
    if(scaley != 1)
        node->setScaleY(scaley);
    if (rotation != 0)
        node->setRotation(rotation);
    if(rotationSkewX != 0)
        node->setRotationSkewX(rotationSkewX);
    if(rotationSkewY != 0)
        node->setRotationSkewY(rotationSkewY);
    if(skewx != 0)
        node->setSkewX(skewx);
    if(skewy != 0)
        node->setSkewY(skewy);
    if(anchorx != 0.5f || anchory != 0.5f)
        node->setAnchorPoint(Point(anchorx, anchory));
    if(width != 0 || height != 0)
        node->setContentSize(Size(width, height));
    if(zorder != 0)
        node->setLocalZOrder(zorder);
    if(visible != true)
        node->setVisible(visible);
    
    if(alpha != 255)
    {
        node->setOpacity(alpha);
    }
    if(red != 255 || green != 255 || blue != 255)
    {
        node->setColor(Color3B(red, green, blue));
    }
    
    
    node->setTag(tag);
    node->setUserObject(ActionTimelineData::create(actionTag));
}

Node* CSLoader::loadSimpleNode(const rapidjson::Value& json)
{
    Node* node = Node::create();
    // fix memory leak for v3.3
    //node->retain();
    initNode(node, json);
    
    return node;
}

Node* CSLoader::loadSubGraph(const rapidjson::Value& json)
{
    const char* filePath = DICTOOL->getStringValue_json(json, FILE_PATH);
    
    Node* node = nullptr;
    if (filePath && strcmp("", filePath) != 0)
    {
        node = createNode(filePath);
    }
    else
    {
        node = Node::create();
    }
    // fix memory leak for v3.3
    //node->retain();
    
    initNode(node, json);
    
    return node;
}

Node* CSLoader::loadSprite(const rapidjson::Value& json)
{
    const char* filePath = DICTOOL->getStringValue_json(json, FILE_PATH);
    Sprite *sprite = nullptr;
    
    if(filePath != nullptr)
    {
        std::string path = filePath;
        
        SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(path);
        if(!spriteFrame)
        {
            path = _jsonPath + path;
            sprite = Sprite::create(path);
        }
        else
        {
            sprite = Sprite::createWithSpriteFrame(spriteFrame);
        }
        
        if(!sprite)
        {
            sprite = CCSprite::create();
            CCLOG("filePath is empty. Create a sprite with no texture");
        }
    }
    else
    {
        sprite = Sprite::create();
    }
    
    // fix memory leak for v3.3
    //sprite->retain();
    
    initNode(sprite, json);
    
    bool flipX          = DICTOOL->getBooleanValue_json(json, FLIPX);
    bool flipY          = DICTOOL->getBooleanValue_json(json, FLIPY);
    
    if(flipX != false)
        sprite->setFlippedX(flipX);
    if(flipY != false)
        sprite->setFlippedY(flipY);
    
    return sprite;
}

Node* CSLoader::loadParticle(const rapidjson::Value& json)
{
    const char* filePath = DICTOOL->getStringValue_json(json, PLIST_FILE);
    int num = DICTOOL->getIntValue_json(json, PARTICLE_NUM);
    
    ParticleSystemQuad* particle = ParticleSystemQuad::create(filePath);
    particle->setTotalParticles(num);
    // fix memory leak for v3.3
    //particle->retain();
    
    initNode(particle, json);
    
    return particle;
}

Node* CSLoader::loadTMXTiledMap(const rapidjson::Value &json)
{
    const char* tmxFile = DICTOOL->getStringValue_json(json, TMX_FILE);
    const char* tmxString = DICTOOL->getStringValue_json(json, TMX_STRING);
    const char* resourcePath = DICTOOL->getStringValue_json(json, RESOURCE_PATH);
    
    TMXTiledMap* tmx = nullptr;
    
    if (tmxFile && strcmp("", tmxFile) != 0)
    {
        tmx = TMXTiledMap::create(tmxFile);
    }
    else if ((tmxString && strcmp("", tmxString) != 0)
             && (resourcePath && strcmp("", resourcePath) != 0))
    {
        tmx = TMXTiledMap::createWithXML(tmxString, resourcePath);
    }
    
    return tmx;
    
}

Node* CSLoader::loadWidget(const rapidjson::Value& json)
{
    const char* str = DICTOOL->getStringValue_json(json, CLASSNAME);
    if(str == nullptr)
        return nullptr;
    
    std::string classname = str;
    
    
    
    WidgetPropertiesReader0300* widgetPropertiesReader = new WidgetPropertiesReader0300();
    Widget* widget = nullptr;
    
    if (isWidget(classname))
    {
        std::string readerName = getGUIClassName(classname);
        readerName.append("Reader");
        
        std::string guiClassName = getGUIClassName(classname);
        widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(guiClassName));
        // fix memory leak for v3.3
        //widget->retain();
        
        WidgetReaderProtocol* reader = dynamic_cast<WidgetReaderProtocol*>(ObjectFactory::getInstance()->createObject(readerName));
        
        widgetPropertiesReader->setPropsForAllWidgetFromJsonDictionary(reader, widget, json);
    }
    else if (isCustomWidget(classname))
    {
        widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(classname));
        
        //fix memory leak for v3.3
        //widget->retain();
        
        //
        // 1st., custom widget parse properties of parent widget with parent widget reader
        std::string readerName = getWidgetReaderClassName(widget);
        WidgetReaderProtocol* reader = dynamic_cast<WidgetReaderProtocol*>(ObjectFactory::getInstance()->createObject(readerName));
        if (reader && widget)
        {
            widgetPropertiesReader->setPropsForAllWidgetFromJsonDictionary(reader, widget, json);
            
            // 2nd., custom widget parse with custom reader
            const char* customProperty = DICTOOL->getStringValue_json(json, "customProperty");
            rapidjson::Document customJsonDict;
            customJsonDict.Parse<0>(customProperty);
            if (customJsonDict.HasParseError())
            {
                CCLOG("GetParseError %s\n", customJsonDict.GetParseError());
            }
            
            widgetPropertiesReader->setPropsForAllCustomWidgetFromJsonDictionary(classname, widget, customJsonDict);
        }
        else
        {
            CCLOG("Widget or WidgetReader doesn't exists!!!  Please check your protocol buffers file.");
        }
    }
    CC_SAFE_DELETE(widgetPropertiesReader);
    
    if (widget)
    {
        float rotationSkewX = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_X);
        float rotationSkewY = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_Y);
        float skewx         = DICTOOL->getFloatValue_json(json, SKEW_X);
        float skewy         = DICTOOL->getFloatValue_json(json, SKEW_Y);
        if(rotationSkewX != 0)
            widget->setRotationSkewX(rotationSkewX);
        if(rotationSkewY != 0)
            widget->setRotationSkewY(rotationSkewY);
        if(skewx != 0)
            widget->setSkewX(skewx);
        if(skewy != 0)
            widget->setSkewY(skewy);
        
        int actionTag = DICTOOL->getIntValue_json(json, ACTION_TAG);
        widget->setUserObject(ActionTimelineData::create(actionTag));
    }
    
    return widget;
}

Component* CSLoader::loadComponent(const rapidjson::Value &json)
{
    Component* component = nullptr;
    
    std::string componentType = DICTOOL->getStringValue_json(json, COMPONENT_TYPE);
    
    ComponentCreateFunc func = _componentFuncs[componentType];
    
    if (func != nullptr)
    {
        component = func(json);
    }
    
    return component;
}

Component* CSLoader::loadComAudio(const rapidjson::Value &json)
{
    ComAudio* audio = ComAudio::create();
    
    const char* name = DICTOOL->getStringValue_json(json, COMPONENT_NAME);
    bool enabled = DICTOOL->getBooleanValue_json(json, COMPONENT_ENABLED);
    
    audio->setName(name);
    audio->setEnabled(enabled);
    
    const char* filePath = DICTOOL->getStringValue_json(json, COMPONENT_AUDIO_FILE_PATH);
    bool loop = DICTOOL->getBooleanValue_json(json, COMPONENT_LOOP);
    
    audio->setFile(filePath);
    audio->setLoop(loop);
    
    
    return audio;
}

Node* CSLoader::createNodeWithFlatBuffersFile(const std::string &filename)
{
    Node* node = nodeWithFlatBuffersFile(filename);
    
    _rootNode = nullptr;
    
    return node;
}

Node* CSLoader::nodeWithFlatBuffersFile(const std::string &fileName)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    
    CC_ASSERT(FileUtils::getInstance()->isFileExist(fullPath));
    
    Data buf = FileUtils::getInstance()->getDataFromFile(fullPath);
    
    auto csparsebinary = GetCSParseBinary(buf.getBytes());
    
    
    auto csBuildId = csparsebinary->version();
    if (csBuildId)
    {
        CCASSERT(strcmp(_csBuildID.c_str(), csBuildId->c_str()) == 0,
            String::createWithFormat("%s%s%s%s%s%s%s%s%s%s",
            "The reader build id of your Cocos exported file(",
            csBuildId->c_str(),
            ") and the reader build id in your Cocos2d-x(",
            _csBuildID.c_str(),
            ") are not match.\n",
            "Please get the correct reader(build id ",
            csBuildId->c_str(), 
            ")from ",
            "http://www.cocos2d-x.org/filedown/cocos-reader",
            " and replace it in your Cocos2d-x")->getCString());
    }

    // decode plist
    auto textures = csparsebinary->textures();
    int textureSize = csparsebinary->textures()->size();
    CCLOG("textureSize = %d", textureSize);
    for (int i = 0; i < textureSize; ++i)
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(textures->Get(i)->c_str());        
    }
       
    Node* node = nodeWithFlatBuffers(csparsebinary->nodeTree());
    
    return node;
}

Node* CSLoader::nodeWithFlatBuffers(const flatbuffers::NodeTree *nodetree)
{
    Node* node = nullptr;
    
    std::string classname = nodetree->classname()->c_str();
    CCLOG("classname = %s", classname.c_str());
    
    auto options = nodetree->options();
    
    if (classname == "ProjectNode")
    {
        auto reader = ProjectNodeReader::getInstance();
        auto projectNodeOptions = (ProjectNodeOptions*)options->data();
        std::string filePath = projectNodeOptions->fileName()->c_str();
        CCLOG("filePath = %s", filePath.c_str());
        if (filePath != "" && FileUtils::getInstance()->isFileExist(filePath))
        {
            
            node = createNodeWithFlatBuffersFile(filePath);
            reader->setPropsWithFlatBuffers(node, options->data());
            
            cocostudio::timeline::ActionTimeline* action = cocostudio::timeline::ActionTimelineCache::getInstance()->createActionWithFlatBuffersFile(filePath);
            if (action)
            {
                node->runAction(action);
                action->gotoFrameAndPause(0);
            }
            
        }
    }
    else if (classname == "SimpleAudio")
    {
        node = Node::create();
        auto reader = ComAudioReader::getInstance();
        Component* component = reader->createComAudioWithFlatBuffers(options->data());
        if (component)
        {
            node->addComponent(component);
            reader->setPropsWithFlatBuffers(node, options->data());
        }
    }
    else
    {
        std::string customClassName = nodetree->customClassName()->c_str();
        if (customClassName != "")
        {
            classname = customClassName;
        }
        std::string readername = getGUIClassName(classname);
        readername.append("Reader");
        
        NodeReaderProtocol* reader = dynamic_cast<NodeReaderProtocol*>(ObjectFactory::getInstance()->createObject(readername));
        node = reader->createNodeWithFlatBuffers(options->data());
        
        Widget* widget = dynamic_cast<Widget*>(node);
        if (widget)
        {
            std::string callbackName = widget->getCallbackName();
            std::string callbackType = widget->getCallbackType();
            
            bindCallback(callbackName, callbackType, widget, _rootNode);
        }
        
        if (_rootNode == nullptr)
        {
            _rootNode = node;
        }
//        _loadingNodeParentHierarchy.push_back(node);
    }
    
    // If node is invalid, there is no necessity to process children of node.
    if (!node)
    {
        return nullptr;
    }
    
    auto children = nodetree->children();
    int size = children->size();
    CCLOG("size = %d", size);
    for (int i = 0; i < size; ++i)
    {
        auto subNodeTree = children->Get(i);
        Node* child = nodeWithFlatBuffers(subNodeTree);
        CCLOG("child = %p", child);
        if (child)
        {
            PageView* pageView = dynamic_cast<PageView*>(node);
            ListView* listView = dynamic_cast<ListView*>(node);
            if (pageView)
            {
                Layout* layout = dynamic_cast<Layout*>(child);
                if (layout)
                {
                    pageView->addPage(layout);
                }
            }
            else if (listView)
            {
                Widget* widget = dynamic_cast<Widget*>(child);
                if (widget)
                {
                    listView->pushBackCustomItem(widget);
                }
            }
            else
            {
                node->addChild(child);
            }
        }
    }
    
//    _loadingNodeParentHierarchy.pop_back();
    
    return node;
}

bool CSLoader::bindCallback(const std::string &callbackName,
                            const std::string &callbackType,
                            cocos2d::ui::Widget *sender,
                            cocos2d::Node *handler)
{
    auto callbackHandler = dynamic_cast<WidgetCallBackHandlerProtocol *>(handler);
    if (callbackHandler) //The handler can handle callback
    {
        if (callbackType == "Click")
        {
            Widget::ccWidgetClickCallback callbackFunc = callbackHandler->onLocateClickCallback(callbackName);
            if (callbackFunc)
            {
                sender->addClickEventListener(callbackFunc);
                return true;
            }
        }
        else if (callbackType == "Touch")
        {
            Widget::ccWidgetTouchCallback callbackFunc = callbackHandler->onLocateTouchCallback(callbackName);
            if (callbackFunc)
            {
                sender->addTouchEventListener(callbackFunc);
                return true;
            }
        }
        else if (callbackType == "Event")
        {
            Widget::ccWidgetEventCallback callbackFunc = callbackHandler->onLocateEventCallback(callbackName);
            if (callbackFunc)
            {
                sender->addCCSEventListener(callbackFunc);
                return true;
            }
        }
    }
    
    CCLOG("callBackName %s cannot be found", callbackName.c_str());
    
    return false;
    
}

bool CSLoader::isWidget(const std::string &type)
{
    return (type == ClassName_Panel
            || type == ClassName_Button
            || type == ClassName_CheckBox
            || type == ClassName_ImageView
            || type == ClassName_TextAtlas
            || type == ClassName_LabelAtlas
            || type == ClassName_LabelBMFont
            || type == ClassName_TextBMFont
            || type == ClassName_Text
            || type == ClassName_LoadingBar
            || type == ClassName_TextField
            || type == ClassName_Slider
            || type == ClassName_Layout
            || type == ClassName_ScrollView
            || type == ClassName_ListView
            || type == ClassName_PageView
            || type == ClassName_Widget
            || type == ClassName_Label);
    
}

bool CSLoader::isCustomWidget(const std::string &type)
{
    Widget* widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(type));
    if (widget)
    {
        CC_SAFE_DELETE(widget);
        return true;
    }
    
    return false;
}

std::string CSLoader::getGUIClassName(const std::string &name)
{
    std::string convertedClassName = name;
    if (name == "Panel")
    {
        convertedClassName = "Layout";
    }
    else if (name == "TextArea")
    {
        convertedClassName = "Text";
    }
    else if (name == "TextButton")
    {
        convertedClassName = "Button";
    }
    else if (name == "Label")
    {
        convertedClassName = "Text";
    }
    else if (name == "LabelAtlas")
    {
        convertedClassName = "TextAtlas";
    }
    else if (name == "LabelBMFont")
    {
        convertedClassName = "TextBMFont";
    }
    
    
    return convertedClassName;
}

std::string CSLoader::getWidgetReaderClassName(Widget* widget)
{
    std::string readerName;
    
    // 1st., custom widget parse properties of parent widget with parent widget reader
    if (dynamic_cast<Button*>(widget))
    {
        readerName = "ButtonReader";
    }
    else if (dynamic_cast<CheckBox*>(widget))
    {
        readerName = "CheckBoxReader";
    }
    else if (dynamic_cast<ImageView*>(widget))
    {
        readerName = "ImageViewReader";
    }
    else if (dynamic_cast<TextAtlas*>(widget))
    {
        readerName = "TextAtlasReader";
    }
    else if (dynamic_cast<TextBMFont*>(widget))
    {
        readerName = "TextBMFontReader";
    }
    else if (dynamic_cast<Text*>(widget))
    {
        readerName = "TextReader";
    }
    else if (dynamic_cast<LoadingBar*>(widget))
    {
        readerName = "LoadingBarReader";
    }
    else if (dynamic_cast<Slider*>(widget))
    {
        readerName = "SliderReader";
    }
    else if (dynamic_cast<TextField*>(widget))
    {
        readerName = "TextFieldReader";
    }
    else if (dynamic_cast<ListView*>(widget))
    {
        readerName = "ListViewReader";
    }
    else if (dynamic_cast<PageView*>(widget))
    {
        readerName = "PageViewReader";
    }
    else if (dynamic_cast<ScrollView*>(widget))
    {
        readerName = "ScrollViewReader";
    }
    
    else if (dynamic_cast<Layout*>(widget))
    {
        readerName = "LayoutReader";
    }
    else if (dynamic_cast<Widget*>(widget))
    {
        readerName = "WidgetReader";
    }
    
    return readerName;
}

void CSLoader::registReaderObject(const std::string &className,
                                  ObjectFactory::Instance ins)
{
    ObjectFactory::TInfo t;
    t._class = className;
    t._fun = ins;
    
    ObjectFactory::getInstance()->registerType(t);
}

Node* CSLoader::createNodeWithFlatBuffersForSimulator(const std::string& filename)
{
    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
    fbs->_isSimulator = true;
    FlatBufferBuilder* builder = fbs->createFlatBuffersWithXMLFileForSimulator(filename);
    
    auto csparsebinary = GetCSParseBinary(builder->GetBufferPointer());
    
    // decode plist
    auto textures = csparsebinary->textures();
    int textureSize = csparsebinary->textures()->size();
    //    CCLOG("textureSize = %d", textureSize);
    for (int i = 0; i < textureSize; ++i)
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(textures->Get(i)->c_str());
    }
    
    auto nodeTree = csparsebinary->nodeTree();

    Node* node = nodeWithFlatBuffersForSimulator(nodeTree);
    
    _rootNode = nullptr;
    
    fbs->deleteFlatBufferBuilder();
    
    return node;
}

Node* CSLoader::nodeWithFlatBuffersForSimulator(const flatbuffers::NodeTree *nodetree)
{
    Node* node = nullptr;
    
    std::string classname = nodetree->classname()->c_str();
    CCLOG("classname = %s", classname.c_str());
    
    auto options = nodetree->options();
    
    if (classname == "ProjectNode")
    {
        auto reader = ProjectNodeReader::getInstance();
        auto projectNodeOptions = (ProjectNodeOptions*)options->data();
        std::string filePath = projectNodeOptions->fileName()->c_str();
        CCLOG("filePath = %s", filePath.c_str());
        
        if (filePath != "" && FileUtils::getInstance()->isFileExist(filePath))
        {
            node = createNodeWithFlatBuffersForSimulator(filePath);
            reader->setPropsWithFlatBuffers(node, options->data());
            
            cocostudio::timeline::ActionTimeline* action = cocostudio::timeline::ActionTimelineCache::getInstance()->createActionWithFlatBuffersForSimulator(filePath);
            if (action)
            {
                node->runAction(action);
                action->gotoFrameAndPause(0);
            }
        }
    }
    else if (classname == "SimpleAudio")
    {
        node = Node::create();
        auto reader = ComAudioReader::getInstance();
        Component* component = reader->createComAudioWithFlatBuffers(options->data());
        if (component)
        {
            node->addComponent(component);
            reader->setPropsWithFlatBuffers(node, options->data());
        }
    }
    else
    {
        std::string readername = getGUIClassName(classname);
        readername.append("Reader");
        
        NodeReaderProtocol* reader = dynamic_cast<NodeReaderProtocol*>(ObjectFactory::getInstance()->createObject(readername));
        node = reader->createNodeWithFlatBuffers(options->data());
        
        Widget* widget = dynamic_cast<Widget*>(node);
        if (widget)
        {
            std::string callbackName = widget->getCallbackName();
            std::string callbackType = widget->getCallbackType();
            
            bindCallback(callbackName, callbackType, widget, _rootNode);
        }
        
        if (_rootNode == nullptr)
        {
            _rootNode = node;
        }
//        _loadingNodeParentHierarchy.push_back(node);
    }
    
    // If node is invalid, there is no necessity to process children of node.
    if (!node)
    {
        return nullptr;
    }
    
    auto children = nodetree->children();
    int size = children->size();
    CCLOG("size = %d", size);
    for (int i = 0; i < size; ++i)
    {
        auto subNodeTree = children->Get(i);
        Node* child = nodeWithFlatBuffersForSimulator(subNodeTree);
        CCLOG("child = %p", child);
        if (child)
        {
            PageView* pageView = dynamic_cast<PageView*>(node);
            ListView* listView = dynamic_cast<ListView*>(node);
            if (pageView)
            {
                Layout* layout = dynamic_cast<Layout*>(child);
                if (layout)
                {
                    pageView->addPage(layout);
                }
            }
            else if (listView)
            {
                Widget* widget = dynamic_cast<Widget*>(child);
                if (widget)
                {
                    listView->pushBackCustomItem(widget);
                }
            }
            else
            {
                node->addChild(child);
            }
        }
        Helper::doLayout(node);
    }
    
//    _loadingNodeParentHierarchy.pop_back();
    
    return node;
}

NS_CC_END
