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

#include "ccTypes.h"
#include "CCNode.h"

#include "renderer/CCCustomCommand.h"


NS_CC_BEGIN

class MeshMaterial;
class Mesh;
class Texture2D;
class Sprite3DEffect;

class Sprite3D : public Node
{
public:
    static Sprite3D* create(const std::string &modelPath);
   
    MeshMaterial* getMeshMaterial(int idx) { return _partMaterials[idx]; }
    
    int           getMeshPartCount() const;
    
    
    Mesh* getMesh() { return _model; }
    
    void setEffect(Sprite3DEffect* effect);
    

protected:
    Sprite3D();
    virtual ~Sprite3D();
    bool init(const std::string &path);
    
    //.mtl file should at the same directory with the same name if exist
    bool loadFromObj(const std::string& path);

    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;

    void onDraw(const Matrix &transform, bool transformUpdated);

    CustomCommand     _customCommand;
    Mesh              *_model;
    
    int               _partcount;
    MeshMaterial**    _partMaterials;
    
    Sprite3DEffect*     _effect;
    
    std::string       _path;
    

};

NS_CC_END
#endif // __SPRITE3D_H_
