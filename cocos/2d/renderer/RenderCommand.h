//
// Created by NiTe Luo on 10/31/13.
//



#ifndef __CCRENDERCOMMAND_H_
#define __CCRENDERCOMMAND_H_

#include "CCPlatformMacros.h"
#include <stdint.h>
#include "ccTypes.h"
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

class RenderCommandID
{
public:
    virtual int64_t generateID() = 0;
    inline int64_t getID() { return _id; }

protected:
    int64_t _id;

};

class RenderCommand
{
public:

    RenderCommand();
    void setKeyData(int viewport, bool isTranslucent, bool isCommand, int32_t depth);
    void setMaterialData( GLuint textureID, GLuint shaderID, BlendFunc blendType);
    void setQuadData(kmMat4* transform, V3F_C4B_T2F_Quad quad);

    void generateID();

    /**
    * Get Render Command Id
    */
    inline int64_t getID() { return _renderCommandId; }
    inline bool isTranslucent() { return _isTranslucent; }
    inline bool isCommand() { return _isCommand; }
    inline int32_t getMaterialID() { return _materialID; }

    inline GLuint getTextureID() { return _textureID; }
    inline kmMat4* getTransform() { return &_transform; }
    inline V3F_C4B_T2F_Quad* getQuad() { return &_quad; }
    inline GLuint getShaderID() { return _shaderID; }
    inline BlendFunc getBlendType() { return _blendType; }

protected:
    void printID();

protected:
    //Generated IDs
    int64_t _renderCommandId; /// used for sorting render commands
    int32_t _materialID;

    //Key Data
    int _viewport;          /// Which view port it belongs to
    bool _isTranslucent;    /// Is it translucent, if it is we will have to render it
    bool _isCommand;
    int32_t _depth;
    //Maternal
    GLuint _textureID;
    GLuint _shaderID;
    BlendFunc _blendType;

    kmMat4 _transform;
    V3F_C4B_T2F_Quad _quad;
};

NS_CC_END

#endif //__CCRENDERCOMMAND_H_
