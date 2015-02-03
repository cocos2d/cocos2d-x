//
//  EditBoxServiceMac.h
//  player
//

#ifndef __player__EditBoxServiceMac__
#define __player__EditBoxServiceMac__

#include "PlayerEditBoxServiceProtocol.h"


@interface EditBoxServiceImplMac : NSObject <NSTextFieldDelegate>
{
    NSTextField* textField_;
    void* editBox_;
    BOOL editState_;
    NSMutableDictionary* placeholderAttributes_;
}

@property(nonatomic, retain) NSTextField* textField;
@property(nonatomic, retain) NSMutableDictionary* placeholderAttributes;
@property(nonatomic, readonly, getter = isEditState) BOOL editState;
@property(nonatomic, assign) void* editBox;

-(id) initWithFrame: (NSRect) frameRect editBox: (void*) editBox;
-(void) doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance;
-(void) setPosition:(NSPoint) pos;
-(void) setContentSize:(NSSize) size;
-(void) visit;
-(void) openKeyboard;
-(void) closeKeyboard;

@end


PLAYER_NS_BEGIN
class PlayerEditBoxServiceMac : public PlayerEditBoxServiceProtocol
{
public:
    PlayerEditBoxServiceMac();
    virtual ~PlayerEditBoxServiceMac();
    
    // overwrite
    virtual void showSingleLineEditBox(const cocos2d::Rect &rect) ;
    virtual void showMultiLineEditBox(const cocos2d::Rect &rect)  ;
    virtual void hide() ;
    
    virtual void setText(const std::string &text);
    virtual void setFont(const std::string &name, int size);
    virtual void setFontColor(const cocos2d::Color3B &color);
    
    virtual void setFormator(int formator);
private:
    void show();
    
private:
    EditBoxServiceImplMac*  _sysEdit;
};

PLAYER_NS_END

#endif
