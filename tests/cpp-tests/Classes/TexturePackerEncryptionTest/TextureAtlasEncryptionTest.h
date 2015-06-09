#ifndef _TextureAtlasEncryption_TEST_H_
#define _TextureAtlasEncryption_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"
#include <string>

DEFINE_TEST_SUITE(TextureAtlasEncryptionTests);

class TextureAtlasEncryptionDemo : public TestCase
{
public:
    CREATE_FUNC(TextureAtlasEncryptionDemo);

    virtual std::string title() const;
    virtual void onEnter() override;

protected:
    std::string    _title;
};

#endif
