//
// Created by NiTe Luo on 11/6/13.
//



#ifndef _CC_QUADCOMMAND_H_
#define _CC_QUADCOMMAND_H_

#include "RenderCommand.h"

NS_CC_BEGIN


class QuadCommand : public RenderCommand
{
public:
    QuadCommand(int viewport, int32_t depth, GLuint textureID, GLuint shaderID, BlendFunc blendType, kmMat4 transform, V3F_C4B_T2F_Quad quad);

    // +----------+----------+-----+-----------------------------------+
    // |          |          |     |                |                  |
    // | ViewPort | Transluc | Cmd |      Depth     |  Material ID     |
    // |   3 bits |    1 bit |  1  |    24 bits     |      24 bit2     |
    // +----------+----------+-----+----------------+------------------+
    virtual int64_t generateID();

    //TODO use material to decide if it is translucent
    inline bool isTranslucent() { return true; }
    inline bool isCommand() { return false; }
    inline int32_t getMaterialID() { return _materialID; }

    inline GLuint getTextureID() { return _textureID; }
    inline kmMat4* getTransform() { return &_transform; }
    inline V3F_C4B_T2F_Quad* getQuad() { return &_quad; }
    inline GLuint getShaderID() { return _shaderID; }
    inline BlendFunc getBlendType() { return _blendType; }

protected:
    int32_t _materialID;

    //Key Data
    int _viewport;          /// Which view port it belongs to
    //TODO use material to determine if it's translucent
    int32_t _depth;
    //Maternal
    GLuint _textureID;
    GLuint _shaderID;
    BlendFunc _blendType;

    kmMat4 _transform;
    V3F_C4B_T2F_Quad _quad;
};

NS_CC_END

#endif //_CC_QUADCOMMAND_H_
