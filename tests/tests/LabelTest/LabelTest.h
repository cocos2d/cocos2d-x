#ifndef _ATLAS_TEST_H_
#define _ATLAS_TEST_H_

#include "../testBasic.h"

class AtlasDemo : public CCLayer
{
protected:

public:
	AtlasDemo(void);
	~AtlasDemo(void);

	virtual std::string title();
	virtual std::string subtitle();
	virtual void onEnter();

	void restartCallback(CCObject* pSender);
	void nextCallback(CCObject* pSender);
	void backCallback(CCObject* pSender);
};


class Atlas1 : public AtlasDemo
{
	CCTextureAtlas*		m_textureAtlas;
public:
	Atlas1();
	~Atlas1();
	virtual std::string title();
	virtual std::string subtitle();
	virtual void draw();
};

class LabelAtlasTest : public AtlasDemo
{
	ccTime		m_time;
public:
	LabelAtlasTest();

	virtual void step(ccTime dt);

	virtual std::string title();
	virtual std::string subtitle();
};

class LabelAtlasColorTest : public AtlasDemo
{
	ccTime		m_time;
public:
	LabelAtlasColorTest();
	virtual void step(ccTime dt);
	virtual std::string title();
	virtual std::string subtitle();
};

class Atlas3 : public AtlasDemo
{
	ccTime		m_time;
public:
	Atlas3();

	virtual void step(ccTime dt);

	virtual std::string title();
	virtual std::string subtitle();
};

class Atlas4 : public AtlasDemo
{
	ccTime		m_time;
public:
	Atlas4();
	virtual void step(ccTime dt);
	virtual void draw();

	virtual std::string title();
	virtual std::string subtitle();
};

class Atlas5 : public AtlasDemo
{
public:
	Atlas5();
	virtual std::string title();
	virtual std::string subtitle();
};


class Atlas6 : public AtlasDemo
{
public:
	Atlas6();
	virtual std::string title();
	virtual std::string subtitle();
};

class AtlasBitmapColor : public AtlasDemo
{
public:
	AtlasBitmapColor();
	virtual std::string title();

	virtual std::string subtitle();
};

class AtlasFastBitmap : public AtlasDemo
{
public:
	AtlasFastBitmap();
	virtual std::string title();
	virtual std::string subtitle();
};

class BitmapFontMultiLine : public AtlasDemo
{
public:
    BitmapFontMultiLine();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelsEmpty : public AtlasDemo
{
public:
    LabelsEmpty();
    void updateStrings(ccTime dt);
    virtual std::string title();
    virtual std::string subtitle();

private:
    bool setEmpty;
};

class LabelBMFontHD : public AtlasDemo
{
public:
    LabelBMFontHD();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelAtlasHD : public AtlasDemo
{
public:
    LabelAtlasHD();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelGlyphDesigner : public AtlasDemo
{
public:
    LabelGlyphDesigner();
    virtual std::string title();
    virtual std::string subtitle();
};

class AtlasTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class LabelTTFTest : public AtlasDemo
{
public:
	LabelTTFTest();
	virtual std::string title();
	virtual std::string subtitle();
};

class LabelTTFMultiline : public AtlasDemo
{
public:
	LabelTTFMultiline();
	virtual std::string title();
	virtual std::string subtitle();
};

class LabelTTFChinese : public AtlasDemo
{
public:
	LabelTTFChinese();
	virtual std::string title();
};

class LabelBMFontChinese : public AtlasDemo
{
public:
    LabelBMFontChinese();
    virtual std::string title();
};

// we don't support linebreak mode

#endif
