
#ifndef __CCSPRITE3D_H__
#define __CCSPRITE3D_H__

#include <vector>
#include "base/CCVector.h"

#include "base/ccTypes.h"
#include "2d/CCNode.h"
#include "2d/CCProtocols.h"

#include "renderer/CCMeshCommand.h"

NS_CC_BEGIN

class GLProgramState;
class Mesh;
class Texture2D;
//class Sprite3DEffect;

class Sprite3D : public Node, public BlendProtocol
{
public:
    //create sprite3D
    static Sprite3D* create(const std::string &modelPath);
    //support only one texture, override texture using given texturePath
    static Sprite3D* create(const std::string &modelPath, const std::string &texturePath);
    
    //set texture
    void setTexture(const std::string& texFile);
    void setTexture(Texture2D* texture);

    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    virtual const BlendFunc &getBlendFunc() const override;
    
    Mesh* getMesh() const { return _mesh; }
    
protected:
    Sprite3D();
    virtual ~Sprite3D();
    bool initWithFile(const std::string &path);
    
    //.mtl file should at the same directory with the same name if exist
    bool loadFromObj(const std::string& path);

    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
    
    virtual GLProgram* getDefGLProgram(bool textured = true);
    
    void genGLProgramState();

    Mesh              *_mesh;
    
    MeshCommand        _meshCommand;
    
    int               _partcount;
    
    Texture2D*        _texture;
    //Vector<Texture2D*>    _textures;
    
    BlendFunc _blend;
    
};

extern std::string s_attributeNames[];

NS_CC_END
#endif // __SPRITE3D_H_
