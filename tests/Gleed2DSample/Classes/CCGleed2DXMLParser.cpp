#include <map>
#include <sstream>
#include "CCGleed2DXMLParser.h"
#include "CCGleed2DLevel.h"
#include "ccMacros.h"
#include "platform/CCFileUtils.h"
#include "ZipUtils.h"
#include "base64.h"

using namespace std;

NS_CC_BEGIN
static const char* valueForKey(const char *key, std::map<std::string, std::string>* dict)
{
	if (dict)
	{
		std::map<std::string, std::string>::iterator it = dict->find(key);
		return it!=dict->end() ? it->second.c_str() : "";
	}
	return "";
}
Gleed2DItem::Gleed2DItem()
	:Name(""),
	Visible(true),
	Position(0,0),
    _itemType(0)
{
	
}

Gleed2DItem::~Gleed2DItem()
{
	if(CustomProperties->count())
	{
		Array * keys=CustomProperties->allKeys();
		int num=keys->count();
		for(int i=0;i<num;i++)
		{
			std::string key=((String*)(keys->getObjectAtIndex(i)))->getCString();
			Gleed2DCustomProperty * delProp=(Gleed2DCustomProperty *)CustomProperties->objectForKey(key);
			CC_SAFE_RELEASE(delProp);
		}
	}
	CC_SAFE_RELEASE(CustomProperties);
}
Gleed2DTextureItem::Gleed2DTextureItem()
	:Rotation(0),
	Scale(1,1),
	TintColor(255,255,255,255),
	FlipHorizontally(false),
	FlipVertically(false),
	texture_filename(""),
	Origin(0,0)
{
	_itemType=GLEED2D_ITEM_TEXTURE;
}
Gleed2DTextureItem::~Gleed2DTextureItem()
{
	if(CustomProperties->count())
	{
		Array * keys=CustomProperties->allKeys();
		int num=keys->count();
		for(int i=0;i<num;i++)
		{
			std::string key=((String*)(keys->getObjectAtIndex(i)))->getCString();
			Gleed2DCustomProperty * delProp=(Gleed2DCustomProperty *)CustomProperties->objectForKey(key);
			CC_SAFE_RELEASE(delProp);
		}
	}
}

Gleed2DRectangleItem::Gleed2DRectangleItem()
	:Width(0),
	Height(0),
	FillColor(255,255,255,255)
{
	_itemType=GLEED2D_ITEM_RECTANGLE;
}
Gleed2DRectangleItem::~Gleed2DRectangleItem()
{
	if(CustomProperties->count())
	{
		Array * keys=CustomProperties->allKeys();
		int num=keys->count();
		for(int i=0;i<num;i++)
		{
			std::string key=((String*)(keys->getObjectAtIndex(i)))->getCString();
			Gleed2DCustomProperty * delProp=(Gleed2DCustomProperty *)CustomProperties->objectForKey(key);
			CC_SAFE_RELEASE(delProp);
		}
	}
}
Gleed2DCircleItem::Gleed2DCircleItem()
	:Radius(0),
	FillColor(255,255,255,255)
{
	_itemType=GLEED2D_ITEM_CIRCLE;
}
Gleed2DCircleItem::~Gleed2DCircleItem()
{
	if(CustomProperties->count())
	{
		Array * keys=CustomProperties->allKeys();
		int num=keys->count();
		for(int i=0;i<num;i++)
		{
			std::string key=((String*)(keys->getObjectAtIndex(i)))->getCString();
			Gleed2DCustomProperty * delProp=(Gleed2DCustomProperty *)CustomProperties->objectForKey(key);
			CC_SAFE_RELEASE(delProp);
		}
	}
}
Gleed2DPathItem::Gleed2DPathItem()
	:IsPolygon(false),
	LineWidth(0),
	LineColor(255,255,255,255)
{
	_itemType=GLEED2D_ITEM_PATH;
	LocalPoints.clear();
    WorldPoints.clear();
}
Gleed2DPathItem::~Gleed2DPathItem()
{
	if(CustomProperties->count())
	{
		Array * keys=CustomProperties->allKeys();
		int num=keys->count();
		for(int i=0;i<num;i++)
		{
			std::string key=((String*)(keys->getObjectAtIndex(i)))->getCString();
			Gleed2DCustomProperty * delProp=(Gleed2DCustomProperty *)CustomProperties->objectForKey(key);
			CC_SAFE_RELEASE(delProp);
		}
	}
}

Gleed2DCustomProperty::Gleed2DCustomProperty()
	:name(""),
	value(),
	type(""),
	description("")
{

}
Gleed2DCustomProperty::Gleed2DCustomProperty(std::string n, Gleed2DCustomPropertyValue v, std::string t, std::string d)
{
	name = n;
	value = v;
	type = t;
	description = d;
}
Gleed2DCustomProperty::~Gleed2DCustomProperty()
{
}
Gleed2DLayerInfo::Gleed2DLayerInfo()
	:Name(""),
	Visible(true),
	ScrollSpeed(1,1)
{
	Items=Array::create();
	CC_SAFE_RETAIN(Items);
}
Gleed2DLayerInfo::~Gleed2DLayerInfo()
{
	int num=Items->count();
	for(int i=0;i<num;i++)
	{
		Gleed2DItem * delItem=(Gleed2DItem*)Items->getObjectAtIndex(i);
		CC_SAFE_RELEASE(delItem);
	}
	CC_SAFE_RELEASE(Items);
}
Gleed2DItem * Gleed2DLayerInfo::getGleed2DItemByName(const char * name)
{
	int numItem=Items->count();
	Gleed2DItem * curItem=NULL;
	for(int i=0;i<numItem;i++)
	{
		curItem=(Gleed2DItem *)(Items->getObjectAtIndex(i));
		if(curItem->Name.compare(name)==0)
		{
			return curItem;
		}
	}
	return NULL;
}
Gleed2DLevelInfo::Gleed2DLevelInfo()
	:Name(""),
	Visible(true),
	_currentPoint(0,0),
	_currentColor(255,255,255,255),
	_currentLayer(NULL),
	_currentItem(NULL),
	_currentProperty(NULL)
{
	Gleed2DLayerInfos=Array::create();
	CC_SAFE_RETAIN(Gleed2DLayerInfos);
	CustomProperties =Dictionary::create();
	CC_SAFE_RETAIN(CustomProperties);
	_currentPointVector.clear();
}
Gleed2DLevelInfo * Gleed2DLevelInfo::create(const std::string& xmlFile)
{
	Gleed2DLevelInfo *pRet = new Gleed2DLevelInfo();
	if(pRet->initWithXMLFile(xmlFile))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
bool Gleed2DLevelInfo::initWithXMLFile(const std::string& xmlFile)
{
	return parseXMLFile(xmlFile);
}
bool Gleed2DLevelInfo::parseXMLFile(const std::string& xmlFilename)
{
	SAXParser parser;

	if (false == parser.init("UTF-8") )
	{
		return false;
	}

	parser.setDelegator(this);
	return parser.parse(FileUtils::getInstance()->fullPathForFilename(xmlFilename).c_str());
}
Gleed2DLevelInfo::~Gleed2DLevelInfo()
{
	int num=Gleed2DLayerInfos->count();
	for(int i=0;i<num;i++)
	{
		Gleed2DLayerInfo * delLayer=(Gleed2DLayerInfo *)Gleed2DLayerInfos->getObjectAtIndex(i);
		CC_SAFE_RELEASE(delLayer);
	}
	
	if(CustomProperties->count())
	{
		Array * keys=CustomProperties->allKeys();
		num=keys->count();
		for(int i=0;i<num;i++)
		{
			std::string key=((String*)(keys->getObjectAtIndex(i)))->getCString();
			Gleed2DCustomProperty * delProp=(Gleed2DCustomProperty *)CustomProperties->objectForKey(key);
			CC_SAFE_RELEASE(delProp);
		}
	}
	CC_SAFE_RELEASE(Gleed2DLayerInfos);
	CC_SAFE_RELEASE(CustomProperties);
}

Gleed2DLayerInfo * Gleed2DLevelInfo::getGleed2DLayerInfoByName(const char * name)
{
	int numLayer=Gleed2DLayerInfos->count();
	Gleed2DLayerInfo * curLayer=NULL;
	for(int i=0;i<numLayer;i++)
	{
		curLayer=(Gleed2DLayerInfo *)(Gleed2DLayerInfos->getObjectAtIndex(i));
		if(curLayer->Name.compare(name)==0)
		{
			return curLayer;
		}
	}
	return NULL;
}

Gleed2DItem * Gleed2DLevelInfo::getGleed2DItemByName(const char * name)
{
	int numLayer=Gleed2DLayerInfos->count();
	Gleed2DLayerInfo * curLayer=NULL;
	Gleed2DItem * item=NULL;
	for(int i=0;i<numLayer;i++)
	{
		curLayer=(Gleed2DLayerInfo *)(Gleed2DLayerInfos->getObjectAtIndex(i));
	    item=curLayer->getGleed2DItemByName(name);
		if(item)
		{
			return item;
		}
	}
	return NULL;
}

void Gleed2DLevelInfo::startElement(void *ctx, const char *name, const char **atts)
{
	CC_UNUSED_PARAM(ctx);
	Gleed2DLevelInfo * pLevelInfo = this;
	std::string elementName = (char*)name;
	std::map<std::string, std::string> *attributeDict = new std::map<std::string, std::string>();
	if (atts && atts[0])
	{
		for(int i = 0; atts[i]; i += 2) 
		{
			std::string key = (char*)atts[i];
			std::string value = (char*)atts[i+1];
			attributeDict->insert(pair<std::string, std::string>(key, value));
		}
	}
    if (elementName == "Height")
	{

	}
	else if (elementName == "Width")
	{

	}
	else if (elementName == "FillColor")
	{

	}
	else if (elementName == "Radius")
	{

	}
	else if (elementName == "LineColor")
	{

	}
	else if (elementName == "LineWidth")
	{

	}
	else if (elementName == "IsPolygon")
	{

	}
	else if (elementName == "WorldPoints")
	{

	}
	else if (elementName == "Vector2")
	{

	}
	else if (elementName == "LocalPoints")
	{

	}
	else if (elementName == "Origin")
	{

	}
	else if (elementName == "asset_name")
	{

	}
	else if (elementName == "texture_filename")
	{

	}
	else if (elementName == "FlipVertically")
	{

	}
	else if (elementName == "FlipHorizontally")
	{

	}
	else if (elementName == "PackedValue")
	{

	}
	else if (elementName == "A")
	{

	}
	else if (elementName == "B")
	{

	}
	else if (elementName == "G")
	{

	}
	else if (elementName == "R")
	{

	}
	else if (elementName == "TintColor")
	{

	}
	else if (elementName == "Scale")
	{

	}
	else if (elementName == "Rotation")
	{

	}
	else if (elementName == "boolean")
	{
		
	}
	else if (elementName == "Color")
	{
		
	}
	else if (elementName == "Property")
	{
		_currentProperty=new Gleed2DCustomProperty();

		_currentProperty->description=valueForKey("Description",attributeDict);
		_currentProperty->type=valueForKey("Type",attributeDict);
		_currentProperty->name=valueForKey("Name",attributeDict);
		if(_currentItem)
		{
			_currentItem->CustomProperties->setObject(_currentProperty,_currentProperty->name);
		}
		else
		{
			pLevelInfo->CustomProperties->setObject(_currentProperty,_currentProperty->name);
		}
	}
	else if (elementName == "CusttomProperties")
	{

	}
	else if (elementName == "Y")
	{

	}
	else if (elementName == "X")
	{

	}
	else if (elementName == "Position")
	{

	}
	else if (elementName == "Item")
	{
		std::string itemType=valueForKey("xsi:type", attributeDict);
		_currentItem=NULL;
		if(itemType=="TextureItem")
		{
 			_currentItem=new Gleed2DTextureItem();
		}
		else if(itemType=="CircleItem")
		{
			_currentItem=new Gleed2DCircleItem();
		}
		else if(itemType=="RectangleItem")
		{
			_currentItem=new Gleed2DRectangleItem();
		}
		else if(itemType=="PathItem")
		{
			_currentItem=new Gleed2DPathItem();
		}
		CCASSERT( _currentItem!=NULL, "GLEED2DXML: Not supported Item type" );
		//CC_SAFE_RETAIN(_currentItem);
		_currentItem->Name=valueForKey("Name", attributeDict);
		std::string strVisible=valueForKey("Visible", attributeDict);
		_currentItem->Visible=(strVisible=="true");
		_currentLayer->Items->addObject(_currentItem);
	}
	else if (elementName == "Items")
	{
		
	}
	else if (elementName == "ScrollSpeed")
	{

	}
	else if (elementName == "Layer")
	{
		_currentLayer=new Gleed2DLayerInfo();
		_currentLayer->Name= valueForKey("Name", attributeDict);
		std::string strVisible=valueForKey("Visible", attributeDict);
		_currentLayer->Visible= strVisible=="true";
		Gleed2DLayerInfos->addObject(_currentLayer);
	}
	else if (elementName == "Layers")
	{
		
	}

	else if (elementName == "Version")
	{

	}
	else if (elementName == "CameraPosition")
	{

	}
	else if (elementName == "ContentRootFolder")
	{

	}
	else if (elementName == "NextItemNumber")
	{

	}
	else if (elementName == "EditorRelated")
	{

	}
	else if (elementName == "Level")
	{

	}

	if (attributeDict)
	{
		attributeDict->clear();
		delete attributeDict;
	}
}
void Gleed2DLevelInfo::endElement(void *ctx, const char *name)
{
	CC_UNUSED_PARAM(ctx);
	Gleed2DLevelInfo * pLevelInfo = this;
	std::string elementName = (char*)name;

	int len = 0;

    if (elementName == "Y")
	{
		String *strValue=String::create(_currentString);
		_currentPoint.y=strValue->floatValue();
	}
	else if (elementName == "X")
	{
		String *strValue=String::create(_currentString);
		_currentPoint.x=strValue->floatValue();
	}
	else if (elementName == "A")
	{
		String *strValue=String::create(_currentString);
		_currentColor.a=strValue->uintValue();
	}
	else if (elementName == "B")
	{
		String *strValue=String::create(_currentString);
		_currentColor.b=strValue->uintValue();
	}
	else if (elementName == "G")
	{
		String *strValue=String::create(_currentString);
		_currentColor.g=strValue->uintValue();
	}
	else if (elementName == "R")
	{
		String *strValue=String::create(_currentString);
		_currentColor.r=strValue->uintValue();
	}
	else if (elementName == "Position")
	{
		_currentItem->Position=_currentPoint;
	}
	else if (elementName == "Height")
	{
		String *strValue=String::create(_currentString);
		((Gleed2DRectangleItem *)_currentItem)->Height=strValue->floatValue();
	}
	else if (elementName == "Width")
	{
		String *strValue=String::create(_currentString);
		((Gleed2DRectangleItem *)_currentItem)->Width=strValue->floatValue();
	}
	else if (elementName == "FillColor")
	{
		switch (_currentItem->_itemType)
		{
		case GLEED2D_ITEM_CIRCLE:
			{
				((Gleed2DCircleItem *)_currentItem)->FillColor=_currentColor;
			}break;
		case GLEED2D_ITEM_RECTANGLE:
			{
				((Gleed2DRectangleItem *)_currentItem)->FillColor=_currentColor;
			}break;
		default:
			break;
		}
	}
	else if (elementName == "Radius")
	{
		String *strValue=String::create(_currentString);
		((Gleed2DCircleItem *)_currentItem)->Radius=strValue->floatValue();
	}
	else if (elementName == "LineColor")
	{
		((Gleed2DPathItem *)_currentItem)->LineColor=_currentColor;
	}
	else if (elementName == "LineWidth")
	{
		String *strValue=String::create(_currentString);
		((Gleed2DPathItem *)_currentItem)->LineWidth=strValue->floatValue();
	}
	else if (elementName == "IsPolygon")
	{
		((Gleed2DPathItem *)_currentItem)->IsPolygon=(_currentString=="true");
	}
	else if (elementName == "Vector2")
	{
		if(_currentProperty)
		{
			_currentProperty->value.vectorValue=_currentPoint;
		}
		else
		{
            _currentPointVector.push_back(_currentPoint);
		}
	}
	else if (elementName == "WorldPoints")
	{
		((Gleed2DPathItem *)_currentItem)->WorldPoints=_currentPointVector;
		_currentPointVector.clear();
	}
	else if (elementName == "LocalPoints")
	{
        ((Gleed2DPathItem *)_currentItem)->LocalPoints=_currentPointVector;
		_currentPointVector.clear();
	}
	else if (elementName == "Origin")
	{
		((Gleed2DTextureItem *)_currentItem)->Origin=_currentPoint;
	}
	else if (elementName == "asset_name")
	{
		
	}
	else if (elementName == "texture_filename")
	{
		((Gleed2DTextureItem *)_currentItem)->texture_filename=_currentString;
	}
	else if (elementName == "FlipVertically")
	{
		((Gleed2DTextureItem *)_currentItem)->FlipVertically=(_currentString=="true");
	}
	else if (elementName == "FlipHorizontally")
	{
		((Gleed2DTextureItem *)_currentItem)->FlipHorizontally=(_currentString=="true");
	}
	else if (elementName == "PackedValue")
	{

	}
	else if (elementName == "TintColor")
	{
		((Gleed2DTextureItem *)_currentItem)->TintColor=_currentColor;
	}
	else if (elementName == "Scale")
	{
		((Gleed2DTextureItem *)_currentItem)->Scale=_currentPoint;
	}
	else if (elementName == "Rotation")
	{
		String *strValue=String::create(_currentString);
		((Gleed2DTextureItem *)_currentItem)->Rotation=strValue->floatValue();
	}
	else if (elementName == "boolean")
	{
		_currentProperty->value.boolValue=(_currentString=="true");
	}
	else if (elementName == "Color")
	{
		_currentProperty->value.colorValue=_currentColor;
	}
	else if (elementName == "Property")
	{
		if(_currentProperty&&_currentProperty->type=="Item")
		{
			_currentProperty->value.itemName=_currentString;
		}
		_currentProperty=NULL;
	}
	else if (elementName == "CusttomProperties")
	{
		
	}
	else if (elementName == "Item")
	{
		_currentItem=NULL;
	}
	else if (elementName == "Items")
	{

	}
	else if (elementName == "ScrollSpeed")
	{
		_currentLayer->ScrollSpeed=_currentPoint;
	}
	else if (elementName == "Layer")
	{
         _currentLayer=NULL;
	}
	else if (elementName == "Layers")
	{
		
	}
	else if (elementName == "Version")
	{

	}
	else if (elementName == "CameraPosition")
	{

	}
	else if (elementName == "ContentRootFolder")
	{

	}
	else if (elementName == "NextItemNumber")
	{

	}
	else if (elementName == "EditorRelated")
	{

	}
	else if (elementName == "Level")
	{

	}
}
void Gleed2DLevelInfo::textHandler(void *ctx, const char *ch, int len)
{
	CC_UNUSED_PARAM(ctx);
	Gleed2DLevelInfo *pLevelInfo = this;
	std::string pText((char*)ch,0,len);
	_currentString=pText;
}
NS_CC_END