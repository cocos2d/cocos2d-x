#ifndef _TextureAtlasEncryption_TEST_H_
#define _TextureAtlasEncryption_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include <string>

class TextureAtlasEncryptionDemo : public Layer
{
public:
    virtual std::string title() const;
    virtual std::string subtitle() const;
    virtual void onEnter();

protected:
    std::string    _title;
};

class TextureAtlasEncryptionTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
