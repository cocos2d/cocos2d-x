#ifndef __CC_GLEED2D_LEVEL__
#define __CC_GLEED2D_LEVEL__

#include "CCNode.h"
#include "CCSpriteBatchNode.h"
#include "CCGleed2DXMLParser.h"

NS_CC_BEGIN
class CC_DLL Gleed2DLayer:public SpriteBatchNode
{
public:
	Gleed2DLayer();
	~Gleed2DLayer();
	static Gleed2DLayer * create(Gleed2DLayerInfo * layerInfo,const std::string& pngSpriteBatchFile);
	bool init(Gleed2DLayerInfo * layerInfo,const std::string& pngSpriteBatchFile);
	const std::string & getName();
	Sprite * getSpriteOfTextureItem(const std::string& name);
	virtual void draw();
private:
	Gleed2DLayerInfo * _layerInfo;
};
class CC_DLL Gleed2DLevel:public Node
{
public:
	Gleed2DLevel(void);
	~Gleed2DLevel(void);
	static Gleed2DLevel * create(const std::string& xmlFile,const std::string& plistSpriteBatchFile,const std::string& pngSpriteBatchFile);
	bool initWithXMLFile(const std::string& xmlFilename,const std::string& plistSpriteBatchFile,const std::string& pngSpriteBatchFile);

	Gleed2DLayer * getLayer(const std::string& name);
private:
	void buildWithLevelInfo(Gleed2DLevelInfo * levelInfo);
	std::string _plistSpriteBatchFile;
	std::string _pngSpriteBatchFile;
	Gleed2DLevelInfo * _levelInfo;
	Array * _arrLayer;
};
NS_CC_END
#endif
