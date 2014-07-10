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
                node->addChild(child);
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

    if (classname == "Panel")
    {
        classname = "Layout";
    }
    else if (classname == "TextArea")
    {
        classname = "Text";
    }
    else if (classname == "TextButton")
    {
        classname = "Button";
    }
    else if (classname == "Label")
    {
        classname = "Text";
    }
    else if (classname == "LabelAtlas")
    {
        classname = "TextAtlas";
    }
    else if (classname == "LabelBMFont")
    {
        classname = "TextBMFont";
    }

    std::string readerName = classname;
    readerName.append("Reader");
    
    Widget*               widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(classname));
    widget->retain();

    WidgetReaderProtocol* reader = dynamic_cast<WidgetReaderProtocol*>(ObjectFactory::getInstance()->createObject(readerName));

    WidgetPropertiesReader0300* guiReader = new WidgetPropertiesReader0300();
    guiReader->setPropsForAllWidgetFromJsonDictionary(reader, widget, json);
    CC_SAFE_DELETE(guiReader);
    
    int actionTag = DICTOOL->getIntValue_json(json, ACTION_TAG);
    widget->setUserObject(ActionTimelineData::create(actionTag));
    
    return widget;
}

}
}
