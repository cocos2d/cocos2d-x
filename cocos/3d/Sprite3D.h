/*
 *
 * SkyboxNode is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SkyboxNode is distributed WITHOUT ANY WARRANTY; See the
 * GNU General Public License for more details.
 *
 * Note: The 'cocos2d for iPhone' license also applies if used in conjunction
 * with the Cocos2D framework.
 */

#ifndef __SPRITE3D_H_
#define __SPRITE3D_H_

#include <vector>
#include "base/CCVector.h"

#include "base/ccTypes.h"
#include "2d/CCNode.h"

#include "renderer/CCCustomCommand.h"


NS_CC_BEGIN

class GLProgramState;
class Mesh;
class Texture2D;
class Sprite3DEffect;

class Sprite3D : public Node
{
public:
    static Sprite3D* create(const std::string &modelPath);
    
    int           getMeshPartCount() const;
    
    
    Mesh* getMesh() { return _model; }
    
    void setTexture(const std::string& texFile);
    

protected:
    Sprite3D();
    virtual ~Sprite3D();
    bool init(const std::string &path);
    
    //.mtl file should at the same directory with the same name if exist
    bool loadFromObj(const std::string& path);

    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;

    void onDraw(const Matrix &transform, bool transformUpdated);
    
    static GLProgram* getDefGLProgram(bool textured = true);
    

    CustomCommand     _customCommand;
    Mesh              *_model;
    
    int               _partcount;
    
    GLProgramState**   _programState;
    
    Vector<Texture2D*>    _textures;
    
    //Sprite3DEffect*     _effect;
    
    std::string       _path;
    

    static GLProgram* s_defGLProgramTex;
    static GLProgram* s_defGLProgram;
};

NS_CC_END
#endif // __SPRITE3D_H_
