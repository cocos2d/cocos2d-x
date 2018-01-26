#ifndef __cocos2d_tests__Bug_14327__
#define __cocos2d_tests__Bug_14327__

#include "BugsTest.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

class Bug14327Layer : public BugsTestBase, public cocos2d::ui::EditBoxDelegate
{
public:
    CREATE_FUNC(Bug14327Layer);

    virtual bool init() override;

    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox) override;
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox) override;
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text) override;
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox) override;

protected:
    virtual void update(float dt) override;

private:
    time_t _removeTime;
    cocos2d::Label *_TTFShowTime;
    cocos2d::ui::EditBox* _edit;
};

#endif

#endif /* defined(__cocos2d_tests__Bug_14327__) */
