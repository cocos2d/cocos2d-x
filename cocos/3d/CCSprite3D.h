
#ifndef __CCSPRITE3D_H__
#define __CCSPRITE3D_H__

#include <vector>
#include "base/CCVector.h"

#include "base/ccTypes.h"
#include "2d/CCNode.h"

#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class GLProgramState;
class Mesh;
class Texture2D;

class Sprite3D : public Node
{
public:
    static Sprite3D* create(const std::string &modelPath);
    static Sprite3D* create(const std::string &modelPath, const std::string &texturePath);
    //static Sprite3D* create(Mesh* mesh, const std::string& texturePath);
    //todo add if we need multitexture in the sprite3d
    //static Sprite3D* create(const std::string &modelPath, const std::vector<std::string> &texturePath);
    //static Sprite3D* create(const std::string &modelPath, const std::vector<std::string> &texturePath);

    int           getMeshPartCount() const;
    
    Mesh* getMesh() const { return _mesh; }
    
    void setTexture(const std::string& texFile);
    //void setTexture(Texture2D* texture);

protected:
    Sprite3D();
    virtual ~Sprite3D();
    bool initWithFile(const std::string &path);
    
    //.mtl file should at the same directory with the same name if exist
    bool loadFromObj(const std::string& path);

    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;

    void onDraw(const Matrix &transform, bool transformUpdated);
    
    virtual GLProgram* getDefGLProgram(bool textured = true);

    CustomCommand     _customCommand;
    Mesh              *_mesh;
    
    int               _partcount;
    
    Vector<GLProgramState*>   _programState;
    
    Vector<Texture2D*>    _textures;
    
    //Sprite3DEffect*     _effect;
    
    std::string       _path;

    
};

NS_CC_END
#endif // __SPRITE3D_H_
