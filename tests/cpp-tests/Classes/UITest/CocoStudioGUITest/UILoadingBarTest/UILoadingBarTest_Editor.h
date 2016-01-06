

#ifndef __TestCpp__UILoadingBarTest_Editor__
#define __TestCpp__UILoadingBarTest_Editor__

#include "../UIScene_Editor.h"

DEFINE_TEST_SUITE(UILoadingBarEditorTests);

class UILoadingBarTest_Editor : public UIScene_Editor
{
public:
    CREATE_FUNC(UILoadingBarTest_Editor);

    UILoadingBarTest_Editor();
    ~UILoadingBarTest_Editor();
    virtual bool init() override;
    void update(float delta)override;

    virtual void configureGUIScene() override;
protected:
    int _count;
};

#endif /* defined(__TestCpp__UILoadingBarTest_Editor__) */
