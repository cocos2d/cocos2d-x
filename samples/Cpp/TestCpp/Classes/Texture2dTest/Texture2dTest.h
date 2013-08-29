#ifndef __TEXTURE2D_TEST_H__
#define __TEXTURE2D_TEST_H__

#include "../testBasic.h"


class TextureDemo : public CCLayer
{
public:
    virtual ~TextureDemo();
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
};

class TextureTIFF : public TextureDemo
{
public:
    virtual std::string title();
    virtual void onEnter();
};

class TexturePNG : public TextureDemo
{
public:
    virtual std::string title();
    virtual void onEnter();
};

class TextureJPEG : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TextureWEBP : public TextureDemo
{
public:
    virtual std::string title();
    
    virtual void onEnter();
};

class TextureMipMap : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVR : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TexturePVR2BPP : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TexturePVR4BPP : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TexturePVRRGBA8888 : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TexturePVRBGRA8888 : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TexturePVRRGBA4444 : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TexturePVRRGBA4444GZ : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRRGBA4444CCZ : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRRGBA5551 : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TexturePVRRGB565 : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TexturePVRRGB888 : public TextureDemo
{
public:
    virtual std::string title();
    virtual void onEnter();
};

class TexturePVRA8 : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TexturePVRI8 : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TexturePVRAI88 : public TextureDemo
{
public:
    virtual std::string title();

    virtual void onEnter();
};

class TexturePVR2BPPv3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRII2BPPv3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVR4BPPv3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRII4BPPv3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRRGBA8888v3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRBGRA8888v3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRRGBA4444v3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRRGBA5551v3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRRGB565v3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRRGB888v3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRA8v3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRI8v3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRAI88v3 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRBadEncoding : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRMipMap : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRMipMap2 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRNonSquare : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRNPOT4444 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePVRNPOT8888 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TextureAlias : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TexturePixelFormat : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TextureBlend : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TextureAsync : public TextureDemo
{
public:
    virtual ~TextureAsync();
    void loadImages(float dt);
    void imageLoaded(CCObject* pObj);
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
private:
    int m_nImageOffset;
};

class TextureGlRepeat : public TextureDemo
{
public:
    virtual ~TextureGlRepeat();
    virtual std::string title();

    virtual void onEnter();
};

class TextureGlClamp : public TextureDemo
{
public:
    virtual ~TextureGlClamp();
    virtual std::string title();

    virtual void onEnter();
};

class TextureSizeTest : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TextureCache1 : public TextureDemo
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class TextureDrawAtPoint : public TextureDemo
{
public:
    ~TextureDrawAtPoint();
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
    virtual void draw();
private:
    CCTexture2D* m_pTex1, *m_pTex2;
};

class TextureDrawInRect : public TextureDemo
{
public:
    ~TextureDrawInRect();
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
    virtual void draw();
private:
    CCTexture2D* m_pTex1, *m_pTex2;
};

class TextureTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class TextureMemoryAlloc : public TextureDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void updateImage(CCObject *sender);
    void changeBackgroundVisible(CCObject *sender);
private:
    CCSprite *m_pBackground;
};

class TexturePVRv3Premult : public TextureDemo
{
public:
    TexturePVRv3Premult();
    
    virtual std::string title();
    virtual std::string subtitle();
    
    void transformSprite(cocos2d::CCSprite *sprite);
};

// ETC1 texture format test
class TextureETC1 : public TextureDemo
{
public:
    TextureETC1();
    
    virtual std::string title();
    virtual std::string subtitle();
};

#endif // __TEXTURE2D_TEST_H__
