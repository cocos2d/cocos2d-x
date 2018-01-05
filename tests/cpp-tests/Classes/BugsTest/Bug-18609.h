//
//  Bug-18609.hpp
//  cocos2d_tests
//
//  Created by peerobo on 05-01-2018.
//  https://github.com/cocos2d/cocos2d-x/issues/18609
//

#ifndef Bug_18609_hpp
#define Bug_18609_hpp

#include "BugsTest.h"
#include <ui/UIButton.h>
USING_NS_CC;

class Bug18609Layer : public BugsTestBase
{
private:
  Bug18609Layer();
  void testCallback(Ref* sender, ui::Widget::TouchEventType type);
public:
  CREATE_FUNC(Bug18609Layer);

  virtual std::string title() const override;
  virtual std::string subtitle() const override;
};


#endif /* Bug_15776_hpp */
