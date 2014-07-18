//
//  EditBoxServiceMac.h
//  player
//

#ifndef __player__EditBoxServiceMac__
#define __player__EditBoxServiceMac__

#include "PlayerEditBoxServiceProtocol.h"


@interface EditBoxServiceImplMac : NSObject <NSTextFieldDelegate>
{
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
class EditBoxServiceMac : public PlayerEditBoxServiceProtocol
{
public:
    EditBoxServiceMac();
    virtual ~EditBoxServiceMac();
    
    void setPosition(int x, int y);
    void setSize(int width, int height);
    void setRect(int x, int y, int width, int height);
    void setText(std::string text);
    void setFont(const char* pFontName, int fontSize);
    void setFontColor(int r, int g, int b);
    
    // hide editbox
    void hide();
    void show();
    
private:
    EditBoxServiceImplMac*  _sysEdit;
};

PLAYER_NS_END

#endif
