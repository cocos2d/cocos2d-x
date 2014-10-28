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
#include "CCActionTimelineCache.h"
#include "CCActionTimeline.h"
#include "../CCSGUIReader.h"
#include "../../cocos/ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "cocostudio/CSParseBinary.pb.h"
#include "tinyxml2/tinyxml2.h"

#include <fstream>

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocostudio::timeline;

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
, _recordProtocolBuffersPath(false)
, _protocolBuffersPath("")
, _monoCocos2dxVersion("")
{
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
        return load->createNodeFromProtocolBuffers(filename);
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
        return cache->createActionFromProtocolBuffers(filename);
    }
    else if (suffix == "json" || suffix == "ExportJson")
    {
        return cache->createActionFromJson(filename);
    }
    
    return nullptr;
}

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
    node->retain();
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
    
    node->retain();
    
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
    
    sprite->retain();
    
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
    particle->retain();
    
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
        widget->retain();
        
        WidgetReaderProtocol* reader = dynamic_cast<WidgetReaderProtocol*>(ObjectFactory::getInstance()->createObject(readerName));
        
        widgetPropertiesReader->setPropsForAllWidgetFromJsonDictionary(reader, widget, json);
    }
    else if (isCustomWidget(classname))
    {
        widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(classname));
        widget->retain();
        
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

Node* CSLoader::createNodeFromProtocolBuffers(const std::string &filename)
{
    if(_recordProtocolBuffersPath)
    {
        std::string protocolBuffersPath = filename.substr(0, filename.find_last_of('/') + 1);
        CCLOG("protocolBuffersPath = %s", protocolBuffersPath.c_str());
        GUIReader::getInstance()->setFilePath(protocolBuffersPath);
        
        _protocolBuffersPath = protocolBuffersPath;
    }
    else
    {
        GUIReader::getInstance()->setFilePath("");
        _protocolBuffersPath = "";
    }
    
    cocos2d::Node* node = nodeFromProtocolBuffersFile(filename);
    
    return node;
}

Node* CSLoader::nodeFromProtocolBuffersFile(const std::string &fileName)
{
    std::string path = fileName;
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName.c_str());
    Data content = FileUtils::getInstance()->getDataFromFile(fullPath);
    protocolbuffers::CSParseBinary gpbwp;
    if (!gpbwp.ParseFromArray(content.getBytes(), (int)content.getSize()))
    {
        return NULL;
    }
    
    // decode plist
    int textureSize = gpbwp.textures_size();
    CCLOG("textureSize = %d", textureSize);
    for (int i = 0; i < textureSize; ++i)
    {
        std::string plist = gpbwp.textures(i);
        CCLOG("plist = %s", plist.c_str());
        std::string png = gpbwp.texturespng(i);
        CCLOG("png = %s", png.c_str());
        plist = _protocolBuffersPath + plist;
        png = _protocolBuffersPath + png;
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist.c_str(), png.c_str());
    }
    int fileDesignWidth = gpbwp.designwidth();
    int fileDesignHeight = gpbwp.designheight();
    if (fileDesignWidth <= 0 || fileDesignHeight <= 0)
    {
        CCLOG("Read design size error!\n");
        Size winSize = Director::getInstance()->getWinSize();
        GUIReader::getInstance()->storeFileDesignSize(fileName.c_str(), winSize);
    }
    else
    {
        GUIReader::getInstance()->storeFileDesignSize(fileName.c_str(),
                                                      Size(fileDesignWidth, fileDesignHeight));
    }
    
    protocolbuffers::NodeTree rootNodeTree = gpbwp.nodetree();
    Node* node = nodeFromProtocolBuffers(rootNodeTree);
    
    return node;
}

Node* CSLoader::nodeFromProtocolBuffers(const protocolbuffers::NodeTree &nodetree)
{
    Node* node = nullptr;
    
    std::string classname = nodetree.classname();
    CCLOG("classname = %s", classname.c_str());
    
    protocolbuffers::WidgetOptions curOptions;
    
    if (classname == "Node")
    {
        node = Node::create();
        const protocolbuffers::WidgetOptions& options = nodetree.widgetoptions();
        setPropsForNodeFromProtocolBuffers(node, options);
        
        curOptions = options;
    }
    else if (classname == "SingleNode")
    {
        node = Node::create();
        const protocolbuffers::WidgetOptions& options = nodetree.widgetoptions();
        setPropsForSingleNodeFromProtocolBuffers(node, options);
        
        curOptions = options;
    }
    else if (classname == "Sprite")
    {
        node = CCSprite::create();
        const protocolbuffers::WidgetOptions& nodeOptions = nodetree.widgetoptions();
        const protocolbuffers::SpriteOptions& options = nodetree.spriteoptions();
        setPropsForSpriteFromProtocolBuffers(node, options, nodeOptions);
        
        curOptions = nodeOptions;
    }
    else if (classname == "ProjectNode")
    {
        const protocolbuffers::WidgetOptions& nodeOptions = nodetree.widgetoptions();
        const protocolbuffers::ProjectNodeOptions& options = nodetree.projectnodeoptions();
        
        std::string filePath = options.filename();
        CCLOG("filePath = %s", filePath.c_str());
		if(filePath != "")
		{
            node = createNodeFromProtocolBuffers(_protocolBuffersPath + filePath);
            setPropsForProjectNodeFromProtocolBuffers(node, options, nodeOptions);
            
            cocostudio::timeline::ActionTimeline* action = cocostudio::timeline::ActionTimelineCache::getInstance()->createActionFromProtocolBuffers(_protocolBuffersPath + filePath);
            if(action)
            {
                node->runAction(action);
                action->gotoFrameAndPlay(0);
            }
		}
     
        curOptions = nodeOptions;
    }
    else if (classname == "Particle")
    {        
        const protocolbuffers::WidgetOptions& nodeOptions = nodetree.widgetoptions();
        const protocolbuffers::ParticleSystemOptions& options = nodetree.particlesystemoptions();
		node = createParticleFromProtocolBuffers(options, nodeOptions);        
        
        curOptions = nodeOptions;
    }
    else if (classname == "GameMap")
    {		
        const protocolbuffers::WidgetOptions& nodeOptions = nodetree.widgetoptions();
        const protocolbuffers::TMXTiledMapOptions& options = nodetree.tmxtiledmapoptions();
		node = createTMXTiledMapFromProtocolBuffers(options, nodeOptions);
        
        curOptions = nodeOptions;
    }
	else if (classname == "SimpleAudio")
	{
        node = Node::create();
        const protocolbuffers::WidgetOptions& options = nodetree.widgetoptions();
        setPropsForSimpleAudioFromProtocolBuffers(node, options);                

		curOptions = options;
	}
    else if (isWidget(classname))
    {
        std::string guiClassName = getGUIClassName(classname);
        std::string readerName = guiClassName;
        readerName.append("Reader");
        
        Widget*               widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(guiClassName));
        widget->retain();
        
        WidgetReaderProtocol* reader = dynamic_cast<WidgetReaderProtocol*>(ObjectFactory::getInstance()->createObject(readerName));
        reader->setPropsFromProtocolBuffers(widget, nodetree);
        
        const protocolbuffers::WidgetOptions& widgetOptions = nodetree.widgetoptions();
        int actionTag = widgetOptions.actiontag();
        widget->setUserObject(ActionTimelineData::create(actionTag));
        
        node = widget;
    }
    else if (isCustomWidget(classname))
    {
        Widget*               widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(classname));
        widget->retain();
        
        //
        // 1st., custom widget parse properties of parent widget with parent widget reader
        std::string readerName = getWidgetReaderClassName(widget);
        WidgetReaderProtocol* reader = dynamic_cast<WidgetReaderProtocol*>(ObjectFactory::getInstance()->createObject(readerName));
        if (reader && widget)
        {
            WidgetPropertiesReader0300* widgetPropertiesReader = new WidgetPropertiesReader0300();
            widgetPropertiesReader->setPropsForAllWidgetFromProtocolBuffers(reader, widget, nodetree);
            
            // 2nd., custom widget parse with custom reader
            const protocolbuffers::WidgetOptions& widgetOptions = nodetree.widgetoptions();
            const char* customProperty = widgetOptions.customproperty().c_str();
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
        //
        
        const protocolbuffers::WidgetOptions& widgetOptions = nodetree.widgetoptions();
        int actionTag = widgetOptions.actiontag();
        widget->setUserObject(ActionTimelineData::create(actionTag));
        
        node = widget;
    }
    
    // component
    int componentSize = curOptions.componentoptions_size();
    for (int i = 0; i < componentSize; ++i)
    {
        
        const protocolbuffers::ComponentOptions& componentOptions = curOptions.componentoptions(i);
        Component* component = createComponentFromProtocolBuffers(componentOptions);
        
        if (component)
        {
            node->addComponent(component);
        }
    }
    
    int size = nodetree.children_size();
    CCLOG("size = %d", size);
    for (int i = 0; i < size; ++i)
    {
        protocolbuffers::NodeTree subNodeTree = nodetree.children(i);
        Node* child = nodeFromProtocolBuffers(subNodeTree);
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
    
    return node;
}

void CSLoader::setPropsForNodeFromProtocolBuffers(cocos2d::Node *node,
                                                    const protocolbuffers::WidgetOptions &nodeOptions)
{
    const protocolbuffers::WidgetOptions& options = nodeOptions;
    
    std::string name = options.name();
    float x             = options.x();
    float y             = options.y();
    float scalex        = options.scalex();
    float scaley        = options.scaley();
    float rotation      = options.rotation();
    float rotationSkewX      = options.has_rotationskewx() ? options.rotationskewx() : 0.0f;
    float rotationSkewY      = options.has_rotationskewy() ? options.rotationskewy() : 0.0f;
    float anchorx       = options.has_anchorpointx() ? options.anchorpointx() : 0.0f;
    float anchory       = options.has_anchorpointy() ? options.anchorpointy() : 0.0f;
    int zorder		    = options.zorder();
    int tag             = options.tag();
    int actionTag       = options.actiontag();
    bool visible        = options.visible();
    
    node->setName(name);
    
    if(x != 0 || y != 0)
        node->setPosition(Point(x, y));
    if(scalex != 1)
        node->setScaleX(scalex);
    if(scaley != 1)
        node->setScaleY(scaley);
    if (rotation != 0)
        node->setRotation(rotation);
    if (rotationSkewX != 0)
        node->setRotationSkewX(rotationSkewX);
    if (rotationSkewY != 0)
        node->setRotationSkewY(rotationSkewY);
    if(anchorx != 0.5f || anchory != 0.5f)
        node->setAnchorPoint(Point(anchorx, anchory));
    if(zorder != 0)
        node->setLocalZOrder(zorder);
    if(visible != true)
        node->setVisible(visible);
    
    node->setTag(tag);
    node->setUserObject(ActionTimelineData::create(actionTag));
    
    node->setCascadeColorEnabled(true);
    node->setCascadeOpacityEnabled(true);
    
}

void CSLoader::setPropsForSingleNodeFromProtocolBuffers(cocos2d::Node *node,
                                                        const protocolbuffers::WidgetOptions &nodeOptions)
{
    setPropsForNodeFromProtocolBuffers(node, nodeOptions);
}

void CSLoader::setPropsForSpriteFromProtocolBuffers(cocos2d::Node *node,
                                                      const protocolbuffers::SpriteOptions &spriteOptions,
                                                      const protocolbuffers::WidgetOptions &nodeOptions)
{
    Sprite *sprite = static_cast<Sprite*>(node);
    const protocolbuffers::SpriteOptions& options = spriteOptions;
    
    const protocolbuffers::ResourceData& fileNameData = options.filenamedata();
    int resourceType = fileNameData.resourcetype();
    switch (resourceType)
    {
        case 0:
        {
            std::string path = _protocolBuffersPath + fileNameData.path();
			if (path != "")
			{
				sprite->setTexture(path);
			}
            break;
        }
            
        case 1:
        {
            std::string path = fileNameData.path();
			if (path != "")
			{
				sprite->setSpriteFrame(path);
			}
            break;
        }
            
        default:
            break;
    }
    
    /*
     const char* filePath = options.filename().c_str();
     CCLOG("filePath = %s", filePath);
     Sprite *sprite = static_cast<Sprite*>(node);
     
     if(filePath != nullptr && strcmp(filePath, "") != 0)
     {
     std::string path = filePath;
     
     SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(path);
     if(!spriteFrame)
     {
     path = _protocolBuffersPath + path;
     sprite->setTexture(path);
     }
     else
     {
     sprite->setSpriteFrame(spriteFrame);
     }
     }
     else
     {
     CCLOG("filePath is empty. Create a sprite with no texture");
     }
     */
    
    sprite->retain();
    
    setPropsForNodeFromProtocolBuffers(sprite, nodeOptions);
    
    GLubyte alpha       = (GLubyte)nodeOptions.has_alpha() ? nodeOptions.alpha() : 255;
    GLubyte red         = (GLubyte)nodeOptions.has_colorr() ? nodeOptions.colorr() : 255;
    GLubyte green       = (GLubyte)nodeOptions.has_colorg() ? nodeOptions.colorg() : 255;
    GLubyte blue        = (GLubyte)nodeOptions.has_colorb() ? nodeOptions.colorb() : 255;
    
    if (alpha != 255)
    {
        sprite->setOpacity(alpha);
    }
    if (red != 255 || green != 255 || blue != 255)
    {
        sprite->setColor(Color3B(red, green, blue));
    }
    
	bool flipX   = spriteOptions.flippedx();
    bool flipY   = spriteOptions.flippedy();
    
    if(flipX != false)
        sprite->setFlippedX(flipX);
    if(flipY != false)
        sprite->setFlippedY(flipY);
}

cocos2d::Node* CSLoader::createParticleFromProtocolBuffers(const protocolbuffers::ParticleSystemOptions& particleSystemOptions,
												 const protocolbuffers::WidgetOptions& nodeOptions)
{
	Node* node = nullptr;

	const protocolbuffers::ParticleSystemOptions& options = particleSystemOptions;
    
    /*
    const std::string& filePath = options.plistfile();
    int num = options.totalparticles();
     */            
    
    const protocolbuffers::ResourceData& fileNameData = options.filenamedata();
    int resourceType = fileNameData.resourcetype();
    switch (resourceType)
    {
        case 0:
        {

            std::string path = _protocolBuffersPath + fileNameData.path();
			if (path != "")
			{
				node = ParticleSystemQuad::create(path);				
			}            
            break;
        }
            
        default:
            break;
    }
    
	if (node)
	{
		setPropsForNodeFromProtocolBuffers(node, nodeOptions);
	}    

	return node;
}

cocos2d::Node* CSLoader::createTMXTiledMapFromProtocolBuffers(const protocolbuffers::TMXTiledMapOptions& tmxTiledMapOptions,
														const protocolbuffers::WidgetOptions& nodeOptions)
{
	Node* node = nullptr;
	const protocolbuffers::TMXTiledMapOptions& options = tmxTiledMapOptions;

	const protocolbuffers::ResourceData& fileNameData = options.filenamedata();
    int resourceType = fileNameData.resourcetype();
    switch (resourceType)
    {
        case 0:
        {
            std::string path = _protocolBuffersPath + fileNameData.path();
            const char* tmxFile = path.c_str();
            
            if (tmxFile && strcmp("", tmxFile) != 0)
            {
                node = TMXTiledMap::create(tmxFile);
            }
            break;
        }
            
        default:
            break;
    }
    
	if (node)
	{
		setPropsForNodeFromProtocolBuffers(node, nodeOptions);
	}

	return node;
}

void CSLoader::setPropsForProjectNodeFromProtocolBuffers(cocos2d::Node *node,
                                                           const protocolbuffers::ProjectNodeOptions &projectNodeOptions,
                                                           const protocolbuffers::WidgetOptions &nodeOptions)
{
    setPropsForNodeFromProtocolBuffers(node, nodeOptions);
}

void CSLoader::setPropsForSimpleAudioFromProtocolBuffers(cocos2d::Node *node,
                                                         const protocolbuffers::WidgetOptions &nodeOptions)
{
    setPropsForNodeFromProtocolBuffers(node, nodeOptions);
}

Component* CSLoader::createComponentFromProtocolBuffers(const protocolbuffers::ComponentOptions &componentOptions)
{
    Component* component = nullptr;
    
    std::string componentType = componentOptions.type();
    
    if (componentType == "ComAudio")
    {
        component = ComAudio::create();
        const protocolbuffers::ComAudioOptions& options = componentOptions.comaudiooptions();
        setPropsForComAudioFromProtocolBuffers(component, options);
    }
    
    return component;
}

void CSLoader::setPropsForComponentFromProtocolBuffers(cocos2d::Component *component,
                                                         const protocolbuffers::ComponentOptions &componentOptions)
{
    std::string componentType = componentOptions.type();
    
    if (componentType == "ComAudio")
    {
        component = ComAudio::create();
        const protocolbuffers::ComAudioOptions& options = componentOptions.comaudiooptions();
        setPropsForComAudioFromProtocolBuffers(component, options);
    }
}

void CSLoader::setPropsForComAudioFromProtocolBuffers(cocos2d::Component *component,
                                                        const protocolbuffers::ComAudioOptions &comAudioOptions)
{
    const protocolbuffers::ComAudioOptions& options = comAudioOptions;
    ComAudio* audio = static_cast<ComAudio*>(component);
    
    const protocolbuffers::ResourceData& fileNameData = options.filenamedata();
    int resourceType = fileNameData.resourcetype();
    switch (resourceType)
    {
        case 0:
        {
            std::string path = _protocolBuffersPath + fileNameData.path();
            audio->setFile(path.c_str());
            break;
        }
            
        default:
            break;
    }
    
    bool loop = options.loop();
    audio->setLoop(loop);
    
    audio->setName(options.name());
    audio->setLoop(options.loop());
}

Node* CSLoader::createNodeFromXML(const std::string &filename)
{
    if(_recordXMLPath)
    {
        std::string xmlPath = filename.substr(0, filename.find_last_of('/') + 1);
        CCLOG("xmlPath = %s", xmlPath.c_str());
        GUIReader::getInstance()->setFilePath(xmlPath);
        
        _xmlPath = xmlPath;
    }
    else
    {
        GUIReader::getInstance()->setFilePath("");
        _xmlPath = "";
    }
    
    cocos2d::Node* node = nodeFromXMLFile(filename);
    
    return node;
}

Node* CSLoader::nodeFromXMLFile(const std::string &fileName)
{
    Node* node = nullptr;
    
    // xml read
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(fileName).c_str();
    ssize_t size;
    std::string content =(char*)FileUtils::getInstance()->getFileData(fullpath, "r", &size);
    
    // xml parse
    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
    document->Parse(content.c_str());
    
    const tinyxml2::XMLElement* rootElement = document->RootElement();// Root
    CCLOG("rootElement name = %s", rootElement->Name());
    
    
    const tinyxml2::XMLElement* element = rootElement->FirstChildElement();
    
    bool createEnabled = false;
    std::string rootType = "";
    
    while (element)
    {
        CCLOG("entity name = %s", element->Name());
        
        if (strcmp("Content", element->Name()) == 0)
        {
            const tinyxml2::XMLAttribute* attribute = element->FirstAttribute();
            
            if (!attribute)
            {
                createEnabled = true;
                rootType = "NodeObjectData";
            }
            //
        }
        
        if (createEnabled)
        {
            break;
        }
        
        const tinyxml2::XMLElement* child = element->FirstChildElement();
        if (child)
        {
            element = child;
        }
        else
        {
            element = element->NextSiblingElement();
        }
    }
    
    
    // create
    if (createEnabled)
    {
        protocolbuffers::CSParseBinary protobuf;
        
        const tinyxml2::XMLElement* child = element->FirstChildElement();
        
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "ObjectData") // nodeTree
            {
                const tinyxml2::XMLElement* objectData = child;
                node = nodeFromXML(objectData, rootType);
            }
            
            child = child->NextSiblingElement();
        }
    }
    
    return node;
}

Node* CSLoader::nodeFromXML(const tinyxml2::XMLElement *objectData, const std::string &classType)
{
    Node* node = nullptr;
    
    std::string classname = classType.substr(0, classType.find("ObjectData"));
    CCLOG("classname = %s", classname.c_str());
    
    if (classname == "Node")
    {
        node = Node::create();
        setPropsForNodeFromXML(node, objectData);
    }
    else if (classname == "SingleNode")
    {
        node = Node::create();
        setPropsForSingleNodeFromXML(node, objectData);
    }
    else if (classname == "Sprite")
    {
        node = Sprite::create();
        setPropsForSpriteFromXML(node, objectData);
    }
    else if (classname == "GameMap")
    {
        node = createTMXTiledMapFromXML(objectData);
    }
    else if (classname == "Particle")
    {
        node = createParticleFromXML(objectData);
    }
    else if (classname == "ProjectNode")
    {
        // FileData
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "FileData")
            {
                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        node = createNodeFromXML(_xmlPath + value);
                        setPropsForProjectNodeFromXML(node, objectData);
                        
                        cocostudio::timeline::ActionTimeline* action = cocostudio::timeline::ActionTimelineCache::getInstance()->createActionFromXML(_xmlPath + value);
                        if(action)
                        {
                            node->runAction(action);
                            action->gotoFrameAndPlay(0);
                        }
                        
                        break;
                    }
                    
                    attribute = attribute->Next();
                }
                
                break;
            }
            
            child = child->NextSiblingElement();
        }
    }
    else if (classname == "SimpleAudio")
    {
        // process as component options
        node = Node::create();
        setPropsForSimpleAudioFromXML(node, objectData);
        
        Component* component = createComponentFromXML(objectData, "ComAudio");
        
        if (component)
        {
            node->addComponent(component);
        }
    }
    else if (isWidget(classname))
    {
        std::string guiClassName = getGUIClassName(classname);
        std::string readerName = guiClassName;
        readerName.append("Reader");
        
        Widget*               widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(guiClassName));
        widget->retain();
        
        WidgetReaderProtocol* reader = dynamic_cast<WidgetReaderProtocol*>(ObjectFactory::getInstance()->createObject(readerName));
        reader->setPropsFromXML(widget, objectData);
        
        node = widget;
    }
    
    
    // children
    bool containChildrenElement = false;
    objectData = objectData->FirstChildElement();
    
    while (objectData)
    {
        CCLOG("objectData name = %s", objectData->Name());
        
        if (strcmp("Children", objectData->Name()) == 0)
        {
            containChildrenElement = true;
            break;
        }
        
        objectData = objectData->NextSiblingElement();
    }
    
    if (containChildrenElement)
    {
        objectData = objectData->FirstChildElement();
        CCLOG("element name = %s", objectData->Name());
        
        while (objectData)
        {
            const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
            bool bHasType = false;
            
            while (attribute)
            {
                std::string name = attribute->Name();
                std::string value = attribute->Value();
                
                if (name == "ctype")
                {
                    bHasType = true;
                    Node* child = nodeFromXML(objectData, value);
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
                    
                    break;
                }
                
                attribute = attribute->Next();
            }
            
            if (!bHasType)
            {
                Node* child = nodeFromXML(objectData, "NodeObjectData");
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
            
            objectData = objectData->NextSiblingElement();
        }
    }
    //
    
    return node;
}

void CSLoader::setPropsForNodeFromXML(cocos2d::Node *node, const tinyxml2::XMLElement *nodeObjectData)
{
    node->setCascadeColorEnabled(true);
    node->setCascadeOpacityEnabled(true);
    
    node->setScale(0.0f, 0.0f);
    
    std::string name = nodeObjectData->Name();
    CCLOG("entity name = %s", name.c_str());
    
    // attributes
    const tinyxml2::XMLAttribute* attribute = nodeObjectData->FirstAttribute();
    while (attribute)
    {
        name = attribute->Name();
        std::string value = attribute->Value();
        
        if (name == "Name")
        {
            node->setName(value);
        }
        else if (name == "ActionTag")
        {
            node->setUserObject(ActionTimelineData::create(atoi(value.c_str())));
        }
        else if (name == "RotationSkewX")
        {
            node->setRotationSkewX(atof(value.c_str()));
        }
        else if (name == "RotationSkewY")
        {
            node->setRotationSkewY(atof(value.c_str()));
        }
        else if (name == "ZOrder")
        {
            node->setZOrder(atoi(value.c_str()));
        }
        else if (name == "VisibleForFrame")
        {
            node->setVisible((value == "True") ? true : false);
        }
        else if (name == "Alpha")
        {
            node->setOpacity(atoi(value.c_str()));
        }
        else if (name == "Tag")
        {
            node->setTag(atoi(value.c_str()));
        }
        
        attribute = attribute->Next();
    }
    
    const tinyxml2::XMLElement* child = nodeObjectData->FirstChildElement();
    while (child)
    {
        name = child->Name();
        if (name == "Children")
        {
            break;
        }
        else if (name == "Position")
        {
            attribute = child->FirstAttribute();
            
            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();
                
                if (name == "X")
                {
                    node->setPositionX(atof(value.c_str()));
                }
                else if (name == "Y")
                {
                    node->setPositionY(atof(value.c_str()));
                }
                
                attribute = attribute->Next();
            }
        }
        else if (name == "Scale")
        {
            attribute = child->FirstAttribute();
            
            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();
                
                if (name == "ScaleX")
                {
                    node->setScaleX(atof(value.c_str()));
                }
                else if (name == "ScaleY")
                {
                    node->setScaleY(atof(value.c_str()));
                }
                
                attribute = attribute->Next();
            }
        }
        else if (name == "AnchorPoint")
        {
            attribute = child->FirstAttribute();
            
            float anchorX = 0.0f;
            float anchorY = 0.0f;
            
            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();
                
                if (name == "ScaleX")
                {
                    anchorX = atof(value.c_str());
                }
                else if (name == "ScaleY")
                {
                    anchorY = atof(value.c_str());
                }
                
                attribute = attribute->Next();
            }
            
            node->setAnchorPoint(Vec2(anchorX, anchorY));
        }
        else if (name == "CColor")
        {
            attribute = child->FirstAttribute();
            int opacity = 255, red = 255, green = 255, blue = 255;
            
            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();
                
                if (name == "A")
                {
                    opacity = atoi(value.c_str());
                }
                else if (name == "R")
                {
                    red = atoi(value.c_str());
                }
                else if (name == "G")
                {
                    green = atoi(value.c_str());
                }
                else if (name == "B")
                {
                    blue = atoi(value.c_str());
                }
                
                attribute = attribute->Next();
            }
            
            node->setOpacity(opacity);
            node->setColor(Color3B(red, green, blue));
        }
        else if (name == "Size")
        {
            attribute = child->FirstAttribute();
            float width = 0.0f, height = 0.0f;
            
            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();
                
                if (name == "X")
                {
                    width = atof(value.c_str());
                }
                else if (name == "Y")
                {
                    height = atof(value.c_str());
                }
                
                attribute = attribute->Next();
            }
            
            node->setContentSize(Size(width, height));
        }
        
        child = child->NextSiblingElement();
    }
}

void CSLoader::setPropsForSingleNodeFromXML(cocos2d::Node *node, const tinyxml2::XMLElement *nodeObjectData)
{
    setPropsForNodeFromXML(node, nodeObjectData);
}

void CSLoader::setPropsForSpriteFromXML(cocos2d::Node *node, const tinyxml2::XMLElement *spriteObjectData)
{
    setPropsForNodeFromXML(node, spriteObjectData);
    
    Sprite* sprite = static_cast<Sprite*>(node);
    int opacity = 255;
    
    // attributes
    const tinyxml2::XMLAttribute* attribute = spriteObjectData->FirstAttribute();
    while (attribute)
    {
        std::string name = attribute->Name();
        std::string value = attribute->Value();
        
        if (name == "Alpha")
        {
            opacity = atoi(value.c_str());
        }
        else if (name == "FlipX")
        {
            sprite->setFlippedX((value == "True") ? true : false);
        }
        else if (name == "FlipY")
        {
            sprite->setFlippedY((value == "True") ? true : false);
        }
        
        attribute = attribute->Next();
    }
    
    
    // FileData
    const tinyxml2::XMLElement* child = spriteObjectData->FirstChildElement();
    while (child)
    {
        std::string name = child->Name();
        
        if (name == "FileData")
        {
            attribute = child->FirstAttribute();
            int resourceType = 0;
            std::string path = "", plistFile = "";
            
            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();
                
                if (name == "Path")
                {
                    path = value;
                }
                else if (name == "Type")
                {
                    resourceType = (value == "Normal" || value == "Default" || value == "MarkedSubImage") ? 0 : 1;
                }
                else if (name == "Plist")
                {
                    plistFile = value;
                }
                
                attribute = attribute->Next();
            }
            
            switch (resourceType)
            {
                case 0:
                {
                    if (path != "")
                    {
                        sprite->setTexture(_xmlPath + path);
                    }
                    break;
                }
                    
                case 1:
                {
                    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(_xmlPath + plistFile);
                    if (path != "")
                    {
                        sprite->setSpriteFrame(path);
                    }
                    break;
                }
                    
                default:
                    break;
            }
        }
        
        child = child->NextSiblingElement();
    }
    
    sprite->setOpacity(opacity);
}

Node* CSLoader::createParticleFromXML(const tinyxml2::XMLElement *particleObjectData)
{
	Node* node = nullptr;
    
    // child elements
    const tinyxml2::XMLElement* child = particleObjectData->FirstChildElement();
    while (child)
    {
        std::string name = child->Name();
        
        if (name == "FileData")
        {
            const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
            int resourceType = 0;
            std::string path = "", plistFile = "";
            
            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();
                
                if (name == "Path")
                {
                    path = value;
                }
                else if (name == "Type")
                {
                    resourceType = (value == "Normal" || value == "Default" || value == "MarkedSubImage") ? 0 : 1;
                }
                else if (name == "Plist")
                {
                    plistFile = value;
                }
                
                attribute = attribute->Next();
            }
            
            switch (resourceType)
            {
                case 0:
                {
                    if (path != "")
                    {
                        node = ParticleSystemQuad::create(_xmlPath + path);
                    }
                    break;
                }
                    
                default:
                    break;
            }
        }
        
        child = child->NextSiblingElement();
    }
    
	if (node)
	{
        setPropsForNodeFromXML(node, particleObjectData);
	}
    
	return node;
}

Node* CSLoader::createTMXTiledMapFromXML(const tinyxml2::XMLElement *tmxTiledMapObjectData)
{
	Node* node = nullptr;
    
    // child elements
    const tinyxml2::XMLElement* child = tmxTiledMapObjectData->FirstChildElement();
    while (child)
    {
        std::string name = child->Name();
        
        if (name == "FileData")
        {
            const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
            int resourceType = 0;
            std::string path = "", plistFile = "";
            
            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();
                
                if (name == "Path")
                {
                    path = value;
                }
                else if (name == "Type")
                {
                    resourceType = (value == "Normal" || value == "Default" || value == "MarkedSubImage") ? 0 : 1;
                }
                else if (name == "Plist")
                {
                    plistFile = value;
                }
                
                attribute = attribute->Next();
            }
            
            switch (resourceType)
            {
                case 0:
                {
					std::string tmxFile_str = _xmlPath + path;
                    const char* tmxFile = tmxFile_str.c_str();
                    
                    if (tmxFile && strcmp("", tmxFile) != 0)
                    {
                        node = TMXTiledMap::create(tmxFile);
                    }
                    break;
                }
                    
                default:
                    break;
            }
        }
        
        child = child->NextSiblingElement();
    }
    
    
	if (node)
	{
        setPropsForNodeFromXML(node, tmxTiledMapObjectData);
	}
    
	return node;
}

void CSLoader::setPropsForProjectNodeFromXML(cocos2d::Node *node, const tinyxml2::XMLElement *projectNodeObjectData)
{
    setPropsForNodeFromXML(node, projectNodeObjectData);
}

void CSLoader::setPropsForSimpleAudioFromXML(cocos2d::Node *node, const tinyxml2::XMLElement *simpleAudioObjectData)
{
    setPropsForNodeFromXML(node, simpleAudioObjectData);
}

Component* CSLoader::createComponentFromXML(const tinyxml2::XMLElement *componentObjectData,
                                            const std::string &componentType)
{
    Component* component = nullptr;
    
    if (componentType == "ComAudio")
    {
        component = ComAudio::create();
        setPropsForComAudioFromXML(component, componentObjectData);
    }
    
    return component;
}

void CSLoader::setPropsForComAudioFromXML(cocos2d::Component *component, const tinyxml2::XMLElement *comAudioObjectData)
{
    ComAudio* audio = static_cast<ComAudio*>(component);
    
    audio->setEnabled(true);
    
    const tinyxml2::XMLAttribute* attribute = comAudioObjectData->FirstAttribute();
    while (attribute)
    {
        std::string name = attribute->Name();
        std::string value = attribute->Value();
        
        if (name == "Loop")
        {
            audio->setLoop((value == "True") ? true : false);
        }
        else if (name == "Name")
        {
            audio->setName(value);
        }
        
        attribute = attribute->Next();
    }
    
    // FileData
    const tinyxml2::XMLElement* child = comAudioObjectData->FirstChildElement();
    while (child)
    {
        std::string name = child->Name();
        
        if (name == "FileData")
        {
            attribute = child->FirstAttribute();
            int resourceType = 0;
            std::string path = "", plistFile = "";
            
            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();
                
                if (name == "Path")
                {
                    path = value;
                }
                else if (name == "Type")
                {
                    resourceType = (value == "Normal" || value == "Default" || value == "MarkedSubImage") ? 0 : 1;
                }
                else if (name == "Plist")
                {
                    plistFile = value;
                }
                
                attribute = attribute->Next();
            }
            
            switch (resourceType)
            {
                case 0:
                {
                    audio->setFile((_xmlPath + path).c_str());
                    break;
                }
                    
                default:
                    break;
            }
        }
        
        child = child->NextSiblingElement();
    }
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

NS_CC_END
