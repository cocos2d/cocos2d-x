#ifndef __CC_GLEED2D_XML_PARSER__
#define __CC_GLEED2D_XML_PARSER__ 

#include "CCArray.h"
#include "CCDictionary.h"
#include "CCGeometry.h"
#include "ccTypes.h"
#include "platform/CCSAXParser.h"

#include <string>
#include <vector>

NS_CC_BEGIN

#define GLEED2D_ITEM_TEXTURE 1
#define GLEED2D_ITEM_RECTANGLE 2
#define GLEED2D_ITEM_CIRCLE 3
#define GLEED2D_ITEM_PATH 4

class CC_DLL Gleed2DObject:public Object
{
public:
	/// <summary>
	/// A Dictionary containing any user-defined Properties.
	/// </summary>
	Dictionary * CustomProperties;
	void * pUserData;
	Gleed2DObject()
		:pUserData(NULL)
	{
		CustomProperties = new Dictionary();
		CustomProperties->init();
	}
};
class CC_DLL Gleed2DItem:public Gleed2DObject
{
	/// <summary>
	/// The name of this item.
	/// </summary>
    public:
	std::string Name;

	/// <summary>
	/// Should this item be visible?
	/// </summary>
	bool Visible;

	/// <summary>
	/// The item's position in world space.
	/// </summary>
	Point Position;

	Gleed2DItem();

	virtual ~Gleed2DItem();
	/// <summary>
	/// Called by Level.FromFile(filename) on each Gleed2DItem after the deserialization process.
	/// Should be overriden and can be used to load anything needed by the Gleed2DItem (e.g. a texture).
	/// </summary>
	int _itemType;
};
class CC_DLL Gleed2DTextureItem : public Gleed2DItem
{
	/// <summary>
	/// The item's rotation in radians.
	/// </summary>
    public: 
	float Rotation;

	/// <summary>
	/// The item's scale factor.
	/// </summary>
	Point Scale;

	/// <summary>
	/// The color to tint the item's texture with (use white for no tint).
	/// </summary>
	Color4B TintColor;

	/// <summary>
	/// If true, the texture is flipped horizontally when drawn.
	/// </summary>
	bool FlipHorizontally;

	/// <summary>
	/// If true, the texture is flipped vertically when drawn.
	/// </summary>
	bool FlipVertically;

	/// <summary>
	/// The path to the texture's filename (including the extension) relative to ContentRootFolder.
	/// </summary>
	std::string texture_filename;

	/// <summary>
	/// The item's origin relative to the upper left corner of the texture. Usually the middle of the texture.
	/// Used for placing and rotating the texture when drawn.
	/// </summary>
	Point Origin;


	Gleed2DTextureItem();
	virtual ~Gleed2DTextureItem();
	/// <summary>
	/// Called by Level.FromFile(filename) on each Gleed2DItem after the deserialization process.
	/// Loads all assets needed by the Gleed2DTextureItem, especially the Texture2D.
	/// You must provide your own implementation. However, you can rely on all public fields being
	/// filled by the level deserialization process.
	/// </summary>
};

class CC_DLL Gleed2DRectangleItem : public Gleed2DItem
{
    public:
	float Width;
	float Height;
	Color4B FillColor;

	Gleed2DRectangleItem();
	virtual ~Gleed2DRectangleItem();
};
class CC_DLL Gleed2DCircleItem :public Gleed2DItem
{
    public:
	float Radius;
	Color4B FillColor;

	Gleed2DCircleItem();
	virtual ~Gleed2DCircleItem();
};
class CC_DLL Gleed2DPathItem :public Gleed2DItem
{
    public:
	std::vector<Point> LocalPoints;
	std::vector<Point> WorldPoints;
	bool IsPolygon;
	int LineWidth;
	Color4B LineColor;


	Gleed2DPathItem();
	virtual ~Gleed2DPathItem();
};
struct Gleed2DCustomPropertyValue{
	bool boolValue;
	std::string itemName;
	Color4B colorValue;
	Point vectorValue;
	Gleed2DCustomPropertyValue()
		:boolValue(false),
		itemName(""),
		colorValue(255,255,255,255),
		vectorValue(0,0)
	{}
};
class CC_DLL Gleed2DCustomProperty : public Object
{
    public:
	std::string name;
	Gleed2DCustomPropertyValue value;
    std::string type;
    std::string description;

	Gleed2DCustomProperty();
	Gleed2DCustomProperty(std::string n, Gleed2DCustomPropertyValue v, std::string t, std::string d);
	virtual ~Gleed2DCustomProperty();
};
class CC_DLL Gleed2DLayerInfo:public Object
{
	/// <summary>
	/// The name of the layer.
	/// </summary>
public:
	std::string Name;

	/// <summary>
	/// Should this layer be visible?
	/// </summary>
    bool Visible;

	/// <summary>
	/// The list of the items in this layer.
	/// </summary>
	Array * Items;

	/// <summary>
	/// The Scroll Speed relative to the main camera. The X and Y components are 
	/// interpreted as factors, so (1;1) means the same scrolling speed as the main camera.
	/// Enables parallax scrolling.
	/// </summary>
	Point ScrollSpeed;
	
	Gleed2DLayerInfo();
	virtual ~Gleed2DLayerInfo();
	Gleed2DItem * getGleed2DItemByName(const char * name);
};
class CC_DLL Gleed2DLevelInfo:public Gleed2DObject,public SAXDelegator
{
	/// <summary>
	/// The name of the level.
	/// </summary>
    public:
	static Gleed2DLevelInfo * create(const std::string& xmlFile);
	bool initWithXMLFile(const std::string& xmlFile);
	bool parseXMLFile(const std::string& xmlFilename);

	void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);

	Gleed2DLayerInfo * getGleed2DLayerInfoByName(const char * name);
	Gleed2DItem * getGleed2DItemByName(const char * name);

	std::string Name;

	bool Visible;

	/// <summary>
	/// A Gleed2DLevelInfo contains several Gleed2DLayerInfos. Each Gleed2DLayerInfo contains several Items.
	/// </summary>
	Array * Gleed2DLayerInfos;

	std::string _currentString;

	Gleed2DLevelInfo();
	virtual ~Gleed2DLevelInfo();
	
	/// <summary>
	/// slot used to store currently readed Gleed2d data type
	/// </summary>
	Gleed2DLayerInfo * _currentLayer;
	Gleed2DItem * _currentItem;
	Gleed2DCustomProperty * _currentProperty;
	Color4B _currentColor;
	Point _currentPoint;
    std::vector<Point> _currentPointVector;
};
NS_CC_END
#endif // !