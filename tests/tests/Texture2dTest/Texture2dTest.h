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

class TexturePVRRaw : public TextureDemo
{
public:
    virtual std::string title();

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

class TextureTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif // __TEXTURE2D_TEST_H__
