#ifndef __UNIT_TEST__
#define __UNIT_TEST__

#include "../testBasic.h"
#include "../BaseTest.h"

class UnitTestScene : public TestScene
{
public:
    virtual void runThisTest() override;
};

class UnitTestDemo : public BaseTest
{
public:
    virtual void onEnter() override;
    virtual void onExit() override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual void restartCallback(Object* sender) override;
    virtual void nextCallback(Object* sender) override;
    virtual void backCallback(Object* sender) override;
};

//-------------------------------------

class TemplateVectorTest : public UnitTestDemo
{
public:
    CREATE_FUNC(TemplateVectorTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    void constFunc(const Vector<Node*>& vec) const;
};

class TemplateMapTest : public UnitTestDemo
{
public:
    CREATE_FUNC(TemplateMapTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    void constFunc(const Map<std::string, Node*>& map) const;
};

class ValueTest : public UnitTestDemo
{
public:
    CREATE_FUNC(ValueTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    void constFunc(const Value& value) const;
};

#endif /* __UNIT_TEST__ */
