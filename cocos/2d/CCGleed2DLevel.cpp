#include "CCGleed2DLevel.h"

#include "cocos2d.h"
NS_CC_BEGIN
Gleed2DLayer::Gleed2DLayer()
{

}
Gleed2DLayer::~Gleed2DLayer()
{

}
Gleed2DLayer * Gleed2DLayer::create(Gleed2DLayerInfo * layerInfo,const std::string& pngSpriteBatchFile)
{
	Gleed2DLayer *ret = new Gleed2DLayer();
	if (ret->init(layerInfo,pngSpriteBatchFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return NULL;
}
void Gleed2DLayer::draw()
{
	SpriteBatchNode::draw();

	ccDrawInit();
	int numItem=_layerInfo->Items->count();
	for(int i=0;i<numItem;i++)
	{
		Gleed2DItem * item=(Gleed2DItem *)_layerInfo->Items->getObjectAtIndex(i);
		switch (item->_itemType)
		{
		case GLEED2D_ITEM_CIRCLE:
			{
				Gleed2DCircleItem * circleItem=(Gleed2DCircleItem *)item;
				ccDrawColor4B(circleItem->FillColor.r,circleItem->FillColor.g,circleItem->FillColor.b,circleItem->FillColor.a);
				ccDrawSolidCircle(Point(circleItem->Position.x,-(circleItem->Position.y))
							      ,circleItem->Radius
								  ,0
								  ,25
					);
			}break;
		case GLEED2D_ITEM_RECTANGLE:
			{
				Gleed2DRectangleItem * rectItem=(Gleed2DRectangleItem *)item;
				ccDrawColor4B(rectItem->FillColor.r,rectItem->FillColor.g,rectItem->FillColor.b,rectItem->FillColor.a);
				ccDrawSolidRect(Point(rectItem->Position.x,-(rectItem->Position.y))
								,Point(rectItem->Position.x+rectItem->Width,-(rectItem->Position.y)-rectItem->Height)
								,Color4F(rectItem->FillColor));
			}break;
		case GLEED2D_ITEM_PATH:
			{
				Gleed2DPathItem * pathItem=(Gleed2DPathItem *)item;
				int numPoint=pathItem->WorldPoints.size()-1;
				ccDrawColor4B(pathItem->LineColor.r,pathItem->LineColor.g,pathItem->LineColor.b,pathItem->LineColor.a);
			    float old_width;
				glGetFloatv(GL_LINE_WIDTH,&old_width);
				glLineWidth(pathItem->LineWidth);
				for(int i=0;i<numPoint;i++)
				{
					ccDrawLine(Point(pathItem->WorldPoints[i].x,-(pathItem->WorldPoints[i].y))
						      ,Point(pathItem->WorldPoints[i+1].x,-(pathItem->WorldPoints[i+1].y)));
				}
				glLineWidth(old_width);
			}break;
		default:
			break;
		}
		
	}
	ccDrawFree();
}
bool Gleed2DLayer::init(Gleed2DLayerInfo * layerInfo,const std::string& pngSpriteBatchFile)
{
	if(!SpriteBatchNode::initWithFile(pngSpriteBatchFile.c_str(),29L))
	{
		return false;
	}
	_layerInfo=layerInfo;
	_layerInfo->retain();
	setVisible(layerInfo->Visible);
	int numItem=_layerInfo->Items->count();
	for(int i=0;i<numItem;i++)
	{
		Gleed2DItem * item=(Gleed2DItem *)_layerInfo->Items->getObjectAtIndex(i);
		if(item->_itemType==GLEED2D_ITEM_TEXTURE)
		{
			Gleed2DTextureItem * texItem=(Gleed2DTextureItem *)item;
			Sprite * sprite=Sprite::createWithSpriteFrameName(texItem->texture_filename.c_str());
			sprite->setAnchorPoint(Point(texItem->Origin.x/sprite->getContentSize().width,texItem->Origin.y/sprite->getContentSize().height));
			sprite->setPosition(Point(texItem->Position.x,-(texItem->Position.y)));
			sprite->setVisible(texItem->Visible);
			sprite->setScale((texItem->FlipHorizontally?-1:1)*texItem->Scale.x,
				             (texItem->FlipVertically?-1:1)*texItem->Scale.y);
			sprite->setRotation(texItem->Rotation);
			addChild(sprite);
			texItem->pUserData=sprite;
		}
	}
	return true;
}

const std::string & Gleed2DLayer::getName()
{
	return _layerInfo->Name;
}
Sprite * Gleed2DLayer::getSpriteOfTextureItem(const std::string& name)
{
	int numItem=_layerInfo->Items->count();
	for(int i=0;i<numItem;i++)
	{
		Gleed2DItem * item=(Gleed2DItem *)_layerInfo->Items->getObjectAtIndex(i);
		if(item->_itemType==GLEED2D_ITEM_TEXTURE&&item->Name==name)
		{
			return (Sprite *)item->pUserData;
		}
	}
	return NULL;
}
Gleed2DLevel::Gleed2DLevel(void)
{
}


Gleed2DLevel::~Gleed2DLevel(void)
{
}

Gleed2DLevel * Gleed2DLevel::create(const std::string& xmlFile,const std::string& plistSpriteBatchFile,const std::string& pngSpriteBatchFile)
{
	Gleed2DLevel *ret = new Gleed2DLevel();
	if (ret->initWithXMLFile(xmlFile,plistSpriteBatchFile,pngSpriteBatchFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return NULL;
}
bool Gleed2DLevel::initWithXMLFile(const std::string& xmlFilename,const std::string& plistSpriteBatchFile,const std::string& pngSpriteBatchFile)
{
	setContentSize(Size::ZERO);
	_plistSpriteBatchFile=plistSpriteBatchFile;
	_pngSpriteBatchFile=pngSpriteBatchFile;
	//load resource
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(_plistSpriteBatchFile);
	_levelInfo = Gleed2DLevelInfo::create(xmlFilename);
	_levelInfo->retain();
	buildWithLevelInfo(_levelInfo);

	return true;
}

void Gleed2DLevel::buildWithLevelInfo(Gleed2DLevelInfo * levelInfo)
{
	_arrLayer=Array::create();
	CC_SAFE_RETAIN(_arrLayer);
	int numLayer=levelInfo->Gleed2DLayerInfos->count();
	for(int i=0;i<numLayer;i++)
	{
		Gleed2DLayer * layer=Gleed2DLayer::create((Gleed2DLayerInfo*)levelInfo->Gleed2DLayerInfos->getObjectAtIndex(i),_pngSpriteBatchFile);
		_arrLayer->addObject(layer);
		addChild(layer);
		layer->release();
	}
}
Gleed2DLayer * Gleed2DLevel::getLayer(const std::string& name)
{
	int numLayer=_levelInfo->Gleed2DLayerInfos->count();
	for(int i=0;i<numLayer;i++)
	{
		Gleed2DLayer * layer=(Gleed2DLayer *)_arrLayer->getObjectAtIndex(i);
		if(layer->getName()==name)
		{
			return layer;
		}
	}
	return NULL;
}
NS_CC_END
