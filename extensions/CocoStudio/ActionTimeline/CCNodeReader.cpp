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
#include "CCFrame.h"
#include "../Reader/GUIReader.h"
#include "../GUI/BaseClasses/UIWidget.h"

using namespace cocos2d;
using namespace cocos2d::extension;

NS_TIMELINE_BEGIN


static const char* ClassName_Node     = "Node";
static const char* ClassName_Sprite   = "Sprite";
static const char* ClassName_Particle = "Particle";

static const char* ClassName_Button     = "Button";
static const char* ClassName_CheckBox   = "CheckBox";
static const char* ClassName_ImageView  = "ImageView";
static const char* ClassName_LabelAtlas = "LabelAtlas";
static const char* ClassName_LabelBMFont= "LabelBMFont";
static const char* ClassName_Text       = "Text";
static const char* ClassName_LoadingBar = "LoadingBar";
static const char* ClassName_TextField  = "TextField";
static const char* ClassName_Slider     = "Slider";
static const char* ClassName_Layout     = "Layout";
static const char* ClassName_ScrollView = "ScrollView";
static const char* ClassName_ListView   = "ListView";
static const char* ClassName_PageView   = "PageView";
static const char* ClassName_Widget     = "Widget";
static const char* ClassName_Panel      = "Panel";
static const char* ClassName_Label      = "Label";



static const char* NODE        = "nodeTree";
static const char* CHILDREN    = "children";
static const char* NODETYPE    = "classname";
static const char* FILE_PATH   = "fileName";
static const char* PLIST_FILE  = "plistFile";
static const char* ACTION_TAG  = "actionTag";
static const char* TAG         = "tag";

static const char* OPTIONS     = "options";

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
static const char* FLIPX            = "flipX";
static const char* FLIPY            = "flipY";
static const char* VISIBLE          = "visible";

static const char* TEXTURES     = "textures";
static const char* TEXTURES_PNG = "texturesPng";

// NodeCreateCallFunc
NodeCreateCallFunc* NodeCreateCallFunc::create(CCObject* target, NodeCreateCallback callback)
{
    NodeCreateCallFunc* func = new NodeCreateCallFunc();
    if (func && func->init(target, callback))
    {
        func->autorelease();
        return func;
    }
    CC_SAFE_DELETE(func);
    return NULL;
}

NodeCreateCallFunc::NodeCreateCallFunc()
    : _target(NULL)
    , _callback(NULL)
{
}

NodeCreateCallFunc::~NodeCreateCallFunc()
{
    CC_SAFE_RELEASE_NULL(_target);
}

bool NodeCreateCallFunc::init(CCObject* target, NodeCreateCallback callback)
{
    if(target == NULL)
        return false;

    _target = target;
    _target->retain();
    _callback = callback;

    return true;
}

CCNode* NodeCreateCallFunc::excute(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    return (_target->*_callback)(json, parent);
}



// TimelineActionData
TimelineActionData* TimelineActionData::create(int actionTag)
{
    TimelineActionData * ret = new TimelineActionData();
    if (ret && ret->init(actionTag))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

TimelineActionData::TimelineActionData()
    : _actionTag(0)
{
}

bool TimelineActionData::init(int actionTag)
{
    _actionTag = actionTag;
    return true;
}



// NodeReader

static NodeReader* _sharedNodeReader = NULL;

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

NodeReader::~NodeReader()
{
    CC_SAFE_DELETE(_funcs);
}

void NodeReader::purge()
{
}

void NodeReader::init()
{
    _funcs = new cocos2d::CCDictionary();
    
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadSimpleNode)), ClassName_Node);
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadSprite)),     ClassName_Sprite);
    _funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadParticle)),   ClassName_Particle);


	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Button);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_CheckBox);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_ImageView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_LabelAtlas);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_LabelBMFont);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Text);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_LoadingBar);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Slider);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Layout);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_ScrollView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_ListView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_PageView);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Widget);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Panel);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_Label);
	_funcs->setObject(NodeCreateCallFunc::create(this, NodeCreateCallback_selector(NodeReader::loadWidget)),   ClassName_TextField);
	

	_guiReader = new WidgetPropertiesReader0300();
}

cocos2d::CCNode* NodeReader::createNode(const std::string& filename)
{
    if(_recordJsonPath)
    {
        std::string jsonPath = filename.substr(0, filename.find_last_of('/') + 1);
        GUIReader::shareReader()->setFilePath(jsonPath);

        _jsonPath = jsonPath;
    }
    else
    {
        GUIReader::shareReader()->setFilePath("");
        _jsonPath = "";
    }

    cocos2d::CCNode* node = loadNodeWithFile(filename);

    return node;
}

cocos2d::CCNode* NodeReader::loadNodeWithFile(const std::string& fileName)
{
    // Read content from file
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
    unsigned long size;
    const char* data = (const char*)CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "r", &size);
    std::string contentStr(data, size);

    cocos2d::CCNode* node = loadNodeWithContent(contentStr);

    // Load animation data from file
    ActionTimelineCache::getInstance()->loadAnimationActionWithContent(fileName, contentStr);

    return node;
}

cocos2d::CCNode* NodeReader::loadNodeWithContent(const std::string& content)
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
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist.c_str(), png.c_str());
    }

    // decode node tree
    const rapidjson::Value& subJson = DICTOOL->getSubDictionary_json(doc, NODE);
    return loadNode(subJson);
}

cocos2d::CCNode* NodeReader::loadNode(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    cocos2d::CCNode* node = NULL;

    std::string nodeType = DICTOOL->getStringValue_json(json, NODETYPE);

    NodeCreateCallFunc* func = static_cast<NodeCreateCallFunc*>(_funcs->objectForKey(nodeType));
    if (func != NULL)
    {
        if (isUiWidget(nodeType))
        {
            node = func->excute(json, parent);
        }
        else
        {
            const rapidjson::Value& options = DICTOOL->getSubDictionary_json(json, OPTIONS);
            node = func->excute(options, parent);
        }
    }

    if (node)
    {
        cocos2d::ui::Widget* widget = dynamic_cast<cocos2d::ui::Widget*>(node);
        if (widget)
        {
            if (!parent)
            {
                return widget;
            }
            else
            {
                cocos2d::ui::TouchGroup* group = cocos2d::ui::TouchGroup::create();
                group->setZOrder(widget->getZOrder());
                group->addWidget(widget);
                parent->addChild(group);
            }
        }
        else
        {
            int length = DICTOOL->getArrayCount_json(json, CHILDREN, 0);
            for (int i = 0; i < length; i++)
            {
                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, CHILDREN, i);
                cocos2d::CCNode* child = loadNode(dic, node);
                if (child && child->getParent() == NULL)
                {
                    node->addChild(child);
                }
            }
        }
    }
    else
    {
        CCLOG("Not supported NodeType: %s", nodeType.c_str());
    }

    return node;
}

void NodeReader::initNode(cocos2d::CCNode* node, const rapidjson::Value& json)
{
    float x             = DICTOOL->getFloatValue_json(json, X);
    float y             = DICTOOL->getFloatValue_json(json, Y);
    float scalex        = DICTOOL->getFloatValue_json(json, SCALE_X, 1);
    float scaley        = DICTOOL->getFloatValue_json(json, SCALE_Y, 1);
    float rotation      = DICTOOL->getFloatValue_json(json, ROTATION);
    float rotationSkewX = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_X);
    float rotationSkewY = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_X);
    float skewx         = DICTOOL->getFloatValue_json(json, SKEW_X);
    float skewy         = DICTOOL->getFloatValue_json(json, SKEW_Y);
    float anchorx       = DICTOOL->getFloatValue_json(json, ANCHOR_X, 0.5f);
    float anchory       = DICTOOL->getFloatValue_json(json, ANCHOR_Y, 0.5f);
    GLubyte alpha       = (GLubyte)DICTOOL->getIntValue_json(json, ALPHA, 255);
    GLubyte red         = (GLubyte)DICTOOL->getIntValue_json(json, RED, 255);
    GLubyte green       = (GLubyte)DICTOOL->getIntValue_json(json, GREEN, 255);
    GLubyte blue        = (GLubyte)DICTOOL->getIntValue_json(json, BLUE, 255);
    int zorder          = DICTOOL->getIntValue_json(json, ZORDER);
    int tag             = DICTOOL->getIntValue_json(json, TAG);
    int actionTag       = DICTOOL->getIntValue_json(json, ACTION_TAG);
    bool visible        = DICTOOL->getBooleanValue_json(json, VISIBLE);

    if(x != 0 || y != 0)
        node->setPosition(CCPoint(x, y));
    if(scalex != 1)
        node->setScaleX(scalex);
    if(scaley != 1)
        node->setScaleY(scaley);
    if (rotation != 0)
        node->setRotation(rotation);
    if(rotationSkewX != 0)
        node->setRotationX(rotationSkewX);
    if(rotationSkewY != 0)
        node->setRotationY(rotationSkewY);
    if(skewx != 0)
        node->setSkewX(skewx);
    if(skewy != 0)
        node->setSkewY(skewy);
    if(anchorx != 0.5f || anchory != 0.5f)
        node->setAnchorPoint(CCPoint(anchorx, anchory));
    if(zorder != 0)
        node->setZOrder(zorder);
    if(visible != true)
        node->setVisible(visible);

    CCRGBAProtocol *rgbaProtocaol = dynamic_cast<CCRGBAProtocol *>(node);
    if(rgbaProtocaol)
    {
        if(alpha != 255)
        {
            rgbaProtocaol->setOpacity(alpha); 
        }
        if(red != 255 || green != 255 || blue != 255)
        {
            rgbaProtocaol->setColor(ccc3(red, green, blue));
        }
    }

    node->setTag(tag);
	node->setUserObject(TimelineActionData::create(actionTag));
}


CCNode* NodeReader::loadSimpleNode(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    const char* filePath = DICTOOL->getStringValue_json(json, FILE_PATH);

    CCNode* node = NULL;
    if(filePath)
    {
        node = createNode(filePath);
    }
    else
    {
        node = CCNodeRGBA::create();
    }

    initNode(node, json);

    return node;
}

CCNode* NodeReader::loadSprite(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    const char* filePath = DICTOOL->getStringValue_json(json, FILE_PATH);

    CCSprite *sprite = NULL;

	if(filePath != NULL)
	{
        std::string path = filePath;
		CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path.c_str());
		if(!spriteFrame)
        {
            path = _jsonPath + path;
			sprite = CCSprite::create(path.c_str());
		}
		else
		{
			sprite = CCSprite::createWithSpriteFrame(spriteFrame);
		}

		if(sprite == NULL)
			CCLOG("create sprite with file name : %s  failed.", filePath);
	}
	else
	{
		sprite = CCSprite::create();
	}

    initNode(sprite, json);

    bool flipX          = DICTOOL->getBooleanValue_json(json, FLIPX);
    bool flipY          = DICTOOL->getBooleanValue_json(json, FLIPY);

    if(flipX != false)
        sprite->setFlipX(flipX);
    if(flipY != false)
        sprite->setFlipY(flipY);

    return sprite;
}

CCNode* NodeReader::loadParticle(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
	const char* filePath = DICTOOL->getStringValue_json(json, PLIST_FILE);

	CCParticleSystemQuad* particle = CCParticleSystemQuad::create(filePath);

	initNode(particle, json);

	return particle;
}

CCNode* NodeReader::loadWidget(const rapidjson::Value& json, cocos2d::CCNode* parent)
{
    WidgetPropertiesReader* pReader = new WidgetPropertiesReader0300();
    cocos2d::ui::Widget* widget = pReader->widgetFromJsonDictionary(json);

    initNode(widget, json);

    return widget;
}

bool NodeReader::isUiWidget(const std::string &type)
{    
    return (type == ClassName_Button
        || type == ClassName_CheckBox
        || type == ClassName_ImageView
        || type == ClassName_LabelAtlas
        || type == ClassName_LabelBMFont
        || type == ClassName_LoadingBar
        || type == ClassName_TextField
        || type == ClassName_Slider
        || type == ClassName_Layout
        || type == ClassName_ScrollView
        || type == ClassName_ListView        
        || type == ClassName_PageView
        || type == ClassName_Widget
        || type == ClassName_Panel
        || type == ClassName_Label);
}

NS_TIMELINE_END
