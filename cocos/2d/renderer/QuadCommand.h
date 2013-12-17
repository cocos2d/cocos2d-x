//
// Created by NiTe Luo on 11/6/13.
//



#ifndef _CC_QUADCOMMAND_H_
#define _CC_QUADCOMMAND_H_

#include "RenderCommand.h"
#include "CCGLProgram.h"
#include "RenderCommandPool.h"
#include "kazmath/kazmath.h"

NS_CC_BEGIN

#define CC_NO_TEXTURE 0

class QuadCommand : public RenderCommand
{
public:
    QuadCommand();
    ~QuadCommand();
    
public:
    void init(int viewport, int32_t depth, GLuint texutreID, GLProgram* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quad, int quadCount,
              const kmMat4& mv);

    // +----------+----------+-----+-----------------------------------+
    // |          |          |     |                |                  |
    // | ViewPort | Transluc |     |      Depth     |  Material ID     |
    // |   3 bits |    1 bit |     |    24 bits     |      24 bit2     |
    // +----------+----------+-----+----------------+------------------+
    virtual int64_t generateID();

    void useMaterial();

    //TODO use material to decide if it is translucent
    inline bool isTranslucent() { return true; }

    inline int32_t getMaterialID() { return _materialID; }

    inline GLuint getTextureID() { return _textureID; }

    inline V3F_C4B_T2F_Quad* getQuad() { return _quad; }

    inline int getQuadCount() { return _quadCount; }

    inline GLProgram* getShader() { return _shader; }

    inline BlendFunc getBlendType() { return _blendType; }
    
    virtual void releaseToCommandPool() override;

protected:
    int32_t _materialID;

    //Key Data
    int _viewport;          /// Which view port it belongs to

    //TODO use material to determine if it's translucent
    int32_t _depth;

    //Maternal
    GLuint _textureID;

    GLProgram* _shader;
//    GLuint _shaderID;

    BlendFunc _blendType;

    V3F_C4B_T2F_Quad* _quad;
    int _quadCount;
    int _capacity;

public:
    friend class RenderCommandPool<QuadCommand>;
    static RenderCommandPool<QuadCommand>& getCommandPool() { return _commandPool; }
protected:
    static RenderCommandPool<QuadCommand> _commandPool;
};

NS_CC_END

#endif //_CC_QUADCOMMAND_H_
