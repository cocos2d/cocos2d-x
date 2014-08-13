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

#include "CCNodeReader.h"
#include "CCActionTimelineCache.h"
#include "CCActionTimeline.h"

#include "cocostudio/CCSGUIReader.h"

#include "../CSParseBinary.pb.h"
#include "../../cocos/ui/CocosGUI.h"

#include <fstream>

using namespace cocos2d;
using namespace ui;

namespace cocostudio {
namespace timeline{


static const char* ClassName_Node     = "Node";
static const char* ClassName_SubGraph = "SubGraph";
static const char* ClassName_Sprite   = "Sprite";
static const char* ClassName_Particle = "Particle";

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


static const char* NODE        = "nodeTree";
static const char* CHILDREN    = "children";
static const char* CLASSNAME   = "classname";
static const char* FILE_PATH   = "fileName";
static const char* PLIST_FILE  = "plistFile";
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


// NodeReader
static NodeReader* _sharedNodeReader = nullptr;

NodeReader* NodeReader::getInstance()
{
    if (! _sharedNodeReader)
    {
        _sharedNodeReader = new NodeReader();
        _sharedNodeReader->init();
    }

    return _sharedNodeReader;
}

void NodeReader::destroyInstance()
{
    CC_SAFE_DELETE(_sharedNodeReader);
}

NodeReader::NodeReader()
    : _recordJsonPath(true)
    , _jsonPath("")
    , _recordProtocolBuffersPath(true)
    , _protocolBuffersPath("")
    , _monoCocos2dxVersion("")
{
}

void NodeReader::purge()
{
}

void NodeReader::init()
{
    using namespace std::placeholders;

    _funcs.insert(Pair(ClassName_Node,      std::bind(&NodeReader::loadSimpleNode, this, _1)));
    _funcs.insert(Pair(ClassName_SubGraph,  std::bind(&NodeReader::loadSubGraph,   this, _1)));
    _funcs.insert(Pair(ClassName_Sprite,    std::bind(&NodeReader::loadSprite,     this, _1)));
    _funcs.insert(Pair(ClassName_Particle,  std::bind(&NodeReader::loadParticle,   this, _1)));
    _funcs.insert(Pair(ClassName_LabelAtlas,std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_LabelBMFont,std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Panel,     std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Button,    std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_CheckBox,  std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_ImageView, std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_TextAtlas, std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_TextBMFont,std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Text,      std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_LoadingBar,std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_TextField, std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Slider,    std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Layout,    std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_ScrollView,std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_ListView,  std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_PageView,  std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Widget,    std::bind(&NodeReader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Label,     std::bind(&NodeReader::loadWidget,   this, _1)));

}

Node* NodeReader::createNode(const std::string& filename)
{
    if(_recordJsonPath)
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

Node* NodeReader::loadNodeWithFile(const std::string& fileName)
{
    // Read content from file
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(fileName);

    Node* node = loadNodeWithContent(contentStr);

    // Load animation data from file
    ActionTimelineCache::getInstance()->loadAnimationActionWithContent(fileName, contentStr);

    return node;
}

Node* NodeReader::loadNodeWithContent(const std::string& content)
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

Node* NodeReader::loadNode(const rapidjson::Value& json)
{
    Node* node = nullptr;
    std::string nodeType = DICTOOL->getStringValue_json(json, CLASSNAME);

    NodeCreateFunc func = _funcs[nodeType];
    if (func != nullptr)
    {
        const rapidjson::Value& options = DICTOOL->getSubDictionary_json(json, OPTIONS);
        node = func(options);
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

void NodeReader::initNode(Node* node, const rapidjson::Value& json)
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

Node* NodeReader::loadSimpleNode(const rapidjson::Value& json)
{
    Node* node = Node::create();
    node->retain();
    initNode(node, json);

    return node;
}

Node* NodeReader::loadSubGraph(const rapidjson::Value& json)
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

Node* NodeReader::loadSprite(const rapidjson::Value& json)
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

Node* NodeReader::loadParticle(const rapidjson::Value& json)
{
    const char* filePath = DICTOOL->getStringValue_json(json, PLIST_FILE);
    int num = DICTOOL->getIntValue_json(json, PARTICLE_NUM);

    ParticleSystemQuad* particle = ParticleSystemQuad::create(filePath);
    particle->setTotalParticles(num);
    particle->retain();

    initNode(particle, json);

    return particle;
}

Node* NodeReader::loadWidget(const rapidjson::Value& json)
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
    
Node* NodeReader::createNodeFromProtocolBuffers(const std::string &filename)
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

Node* NodeReader::nodeFromProtocolBuffersFile(const std::string &fileName)
{
    std::string path = fileName;
    int pos = path.find_last_of('/');
    //    _protocolBuffersPath = path.substr(0, pos + 1);
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName.c_str());
    Data content = FileUtils::getInstance()->getDataFromFile(fullPath);
    protocolbuffers::CSParseBinary gpbwp;
    //    protocolbuffers::GUIProtocolBuffersProtobuf gpbwp;
    if (!gpbwp.ParseFromArray(content.getBytes(), content.getSize()))
    {
        return NULL;
    }
    /*
     CCLog("dataScale = %d", gpbwp.datascale());
     CCLog("designHeight = %d", gpbwp.designheight());
     CCLog("designWidth = %d", gpbwp.designwidth());
     CCLog("version = %s", gpbwp.version().c_str());
     */    
    
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

Node* NodeReader::nodeFromProtocolBuffers(const protocolbuffers::NodeTree &nodetree)
{
    Node* node = NULL;
    
    std::string classname = nodetree.classname();
    CCLOG("classname = %s", classname.c_str());
    
    if (classname == "Node")
    {
        node = Node::create();
        const protocolbuffers::WidgetOptions& options = nodetree.widgetoptions();
        setPropsForNodeFromProtocolBuffers(node, options);
    }
    else if (classname == "Sprite")
    {
        node = CCSprite::create();
        const protocolbuffers::WidgetOptions& nodeOptions = nodetree.widgetoptions();
        const protocolbuffers::SpriteOptions& options = nodetree.spriteoptions();
        setPropsForSpriteFromProtocolBuffers(node, options, nodeOptions);
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

void NodeReader::setPropsForNodeFromProtocolBuffers(cocos2d::Node *node,
                                                    const protocolbuffers::WidgetOptions &nodeOptions)
{
    const protocolbuffers::WidgetOptions& options = nodeOptions;
    
    float x             = options.x();
    float y             = options.y();
    float scalex        = options.scalex();
    float scaley        = options.scaley();
    float rotation      = options.rotation();
    float anchorx       = options.has_anchorpointx() ? options.anchorpointx() : 0.5f;
    float anchory       = options.has_anchorpointy() ? options.anchorpointy() : 0.5f;
    int zorder		    = options.zorder();
    int tag             = options.tag();
    int actionTag       = options.actiontag();
    bool visible        = options.visible();
    
    if(x != 0 || y != 0)
        node->setPosition(Point(x, y));
    if(scalex != 1)
        node->setScaleX(scalex);
    if(scaley != 1)
        node->setScaleY(scaley);
    if (rotation != 0)
        node->setRotation(rotation);
    if(anchorx != 0.5f || anchory != 0.5f)
        node->setAnchorPoint(Point(anchorx, anchory));
    if(zorder != 0)
        node->setLocalZOrder(zorder);
    if(visible != true)
        node->setVisible(visible);
    
    node->setTag(tag);
    node->setUserObject(ActionTimelineData::create(actionTag));
    
}

void NodeReader::setPropsForSpriteFromProtocolBuffers(cocos2d::Node *node,
                                                      const protocolbuffers::SpriteOptions &spriteOptions,
                                                      const protocolbuffers::WidgetOptions &nodeOptions)
{
    const protocolbuffers::SpriteOptions& options = spriteOptions;
    
    const char* filePath = options.filename().c_str();
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
    
    sprite->retain();
    
    setPropsForNodeFromProtocolBuffers(sprite, nodeOptions);
    
    GLubyte alpha       = (GLubyte)nodeOptions.has_opacity() ? nodeOptions.opacity() : 255;
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
    
    bool flipX          = nodeOptions.flipx();
    bool flipY          = nodeOptions.flipy();
    
    if(flipX != false)
        sprite->setFlippedX(flipX);
    if(flipY != false)
        sprite->setFlippedY(flipY);
}

bool NodeReader::isWidget(const std::string &type)
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

bool NodeReader::isCustomWidget(const std::string &type)
{
    Widget* widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(type));
    if (widget)
    {
        CC_SAFE_DELETE(widget);
        return true;
    }
    
    return false;
}

std::string NodeReader::getGUIClassName(const std::string &name)
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

std::string NodeReader::getWidgetReaderClassName(Widget* widget)
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

}
}
