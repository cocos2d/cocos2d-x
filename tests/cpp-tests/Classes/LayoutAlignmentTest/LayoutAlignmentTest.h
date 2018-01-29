#ifndef _LAYOUT_ALIGNMENT_TEST_H_
#define _LAYOUT_ALIGNMENT_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(LayoutAlignmentTests);

class LayoutAlignmentHBoxTest : public TestCase
{
public:
    CREATE_FUNC(LayoutAlignmentHBoxTest);
    LayoutAlignmentHBoxTest();
    virtual ~LayoutAlignmentHBoxTest();

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
};

class LayoutAlignmentVBoxTest : public TestCase
{
public:
    CREATE_FUNC(LayoutAlignmentVBoxTest);
    LayoutAlignmentVBoxTest();
    virtual ~LayoutAlignmentVBoxTest();

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
};

#endif
