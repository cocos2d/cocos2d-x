/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2014      Jacky Tsang (zengrong.net)

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

#ifndef __CCFILTERED_SPRITE_H__
#define __CCFILTERED_SPRITE_H__

#include "cocos2d.h"
#include "filters/filters/CCFilter.h"

USING_NS_CC;

NS_CC_EXT_BEGIN

class FilteredSprite : public Sprite
{
public:

	FilteredSprite();
	~FilteredSprite();

    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	virtual Filter* getFilter(unsigned int $index = 0);
	virtual void setFilter(Filter* $pFilter)=0;

	virtual Vector<Filter*>& getFilters();
	virtual void setFilters(Vector<Filter*>& $pFilters);

    virtual void clearFilter() = 0;

protected:
	virtual void drawFilter()=0;
	virtual bool updateFilters()=0;
	Vector<Filter*> _pFilters;
};

class FilteredSpriteWithOne : public FilteredSprite
{
public:
	static FilteredSpriteWithOne* create();
	static FilteredSpriteWithOne* create(const char* $pszFileName);
	static FilteredSpriteWithOne* create(const char* $pszFileName, const Rect& $rect);

    static FilteredSpriteWithOne* createWithTexture(Texture2D* $pTexture);
    static FilteredSpriteWithOne* createWithTexture(Texture2D* $pTexture, const Rect& $rect);
	static FilteredSpriteWithOne* createWithSpriteFrame(SpriteFrame* $pSpriteFrame);
	static FilteredSpriteWithOne* createWithSpriteFrameName(const char* $pszSpriteFrameName);

	virtual Filter* getFilter(unsigned int $index = 0);
	virtual void setFilters(Vector<Filter*>& $pFilters);
	virtual void setFilter(Filter* $pFilter);
    virtual void clearFilter();

protected:
	virtual void drawFilter();
	virtual bool updateFilters();
};

class FilteredSpriteWithMulti : public FilteredSprite
{
public:
	static FilteredSpriteWithMulti* create();
	static FilteredSpriteWithMulti* create(const char* $pszFileName);
	static FilteredSpriteWithMulti* create(const char* $pszFileName, const Rect& $rect);

	static FilteredSpriteWithMulti* createWithTexture(Texture2D* $pTexture);
	static FilteredSpriteWithMulti* createWithTexture(Texture2D* $pTexture, const Rect& rect);

	static FilteredSpriteWithMulti* createWithSpriteFrame(SpriteFrame* $pSpriteFrame);

	static FilteredSpriteWithMulti* createWithSpriteFrameName(const char* $pszSpriteFrameName);

	virtual void setFilter(Filter* $pFilter);
    virtual void clearFilter();

	FilteredSpriteWithMulti();
	~FilteredSpriteWithMulti();

	// ts = Temporary Storage
	Texture2D* getTSTexture();
	void setTSTexture(Texture2D* $texture);
	SpriteFrame* getTSFrame();
	void setTSFrame(SpriteFrame* $frame);

	Rect getTSRect();
	void setTSRect(const Rect& $rect);
    
    virtual void update(float delta) override;

protected:
	virtual void drawFilter();
	virtual bool updateFilters();
private:
	Texture2D* _pTexture;
	SpriteFrame* _pFrame;
	Rect _rect;
    
    FilteredSprite* _pFilterSpiteCompound;
    RenderTexture* _pRenderTextureCompound;
    Texture2D* _pTextureCompound;
    int _filterIdxCompound;
};

NS_CC_EXT_END

#endif /* __CCFILTERED_SPRITE_H__ */