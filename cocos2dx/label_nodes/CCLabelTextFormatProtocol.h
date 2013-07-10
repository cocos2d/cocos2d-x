//
//  CCLabelTextFormatProtocol.h
//  TestNewStringStuff
//
//  Created by Carlo Morgantini on 6/27/13.
//
//

#ifndef __CCLabelTextFormatProtocol__
#define __CCLabelTextFormatProtocol__

NS_CC_BEGIN

class CC_DLL LabelTextFormatProtocol
{
public:
    
    // sprite related stuff
    virtual cocos2d::Sprite * getSpriteChild(int ID) = 0;
    virtual cocos2d::Array  * getChildrenLetters()   = 0;
    virtual cocos2d::Sprite * getSpriteForChar(unsigned short int theChar, int spriteIndexHint) = 0;
    virtual float               getLetterPosXLeft( cocos2d::Sprite* sp )  = 0;
    virtual float               getLetterPosXRight( cocos2d::Sprite* sp ) = 0;
    
    // font related stuff
    virtual int              getCommonLineHeight() = 0;
    virtual int              getKerningForCharsPair(unsigned short first, unsigned short second) = 0;
    virtual int              getXOffsetForChar(unsigned short c) = 0;
    virtual int              getYOffsetForChar(unsigned short c) = 0;
    virtual int              getAdvanceForChar(unsigned short c, int hintPositionInString) = 0;
    virtual cocos2d::Rect    getRectForChar(unsigned short c)    = 0;
    
    // string related stuff
    virtual int                          getStringNumLines()                            = 0;
    virtual int                          getStringLenght()                              = 0;
    virtual unsigned short               getCharAtStringPosition(int position)          = 0;
    virtual unsigned short *             getUTF8String()                                = 0;
    virtual void                         assignNewUTF8String(unsigned short *newString) = 0;
    virtual cocos2d::TextAlignment       getTextAlignment()                             = 0;
    
    // label related stuff
    virtual float                        getMaxLineWidth()          = 0;
    virtual bool                         breakLineWithoutSpace()    = 0;
    virtual cocos2d::Size                getLabelContentSize()      = 0;
    virtual void                         setLabelContentSize(const Size &newSize) = 0;
    
private:
    

};

NS_CC_END

#endif 
