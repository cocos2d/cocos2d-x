#ifndef __UNIT_TEST__
#define __UNIT_TEST__

#include "../BaseTest.h"

DEFINE_TEST_SUITE(UnitTests);

class UnitTestDemo : public TestCase
{
public:
    virtual std::string title() const override;
};

//-------------------------------------

class TemplateVectorTest : public UnitTestDemo
{
public:
    CREATE_FUNC(TemplateVectorTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    void constFunc(const cocos2d::Vector<Node*>& vec) const;
};

class TemplateMapTest : public UnitTestDemo
{
public:
    CREATE_FUNC(TemplateMapTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    void constFunc(const cocos2d::Map<std::string, cocos2d::Node*>& map) const;
};

class ValueTest : public UnitTestDemo
{
public:
    CREATE_FUNC(ValueTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    void constFunc(const cocos2d::Value& value) const;
};

class UTFConversionTest : public UnitTestDemo
{
public:
    CREATE_FUNC(UTFConversionTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class MathUtilTest : public UnitTestDemo
{
public:
    CREATE_FUNC(MathUtilTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

#endif /* __UNIT_TEST__ */
