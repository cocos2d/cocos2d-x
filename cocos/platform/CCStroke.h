#ifndef COCOS2D_STROKE_H
#define COCOS2D_STROKE_H

namespace cocos2d
{
    struct FontStroke;
    
    void drawStroke
    ( unsigned char*& src, int& width, int& height, const FontStroke& stroke );
}

#endif
