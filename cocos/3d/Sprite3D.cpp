//
//  SkyboxNode.m
//  testar1
//
//  Created by Pasi Kettunen on 12.12.2012.
//
//

#include "cocos2d.h"
#include "Sprite3D.h"
#include "MeshCache.h"
#include "Mesh.h"
#include "MeshMaterial.h"
#include "Sprite3DEffect.h"

#include "ObjLoader.h"

NS_CC_BEGIN

std::map<std::string, std::vector<std::string> > __cachedSpriteTexNames;

Sprite3D* Sprite3D::create(const std::string &modelPath)
{
    if (modelPath.length() < 4)
        return nullptr;
    
    auto sprite = new Sprite3D;
    if (sprite->init(modelPath))
    {
        sprite->autorelease();
        return sprite;
    }
    
    return nullptr;
}

//.mtl file should at the same directory with the same name if exist
bool Sprite3D::loadFromObj(const std::string& path)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    
    //.mtl file directory
    std::string dir = "";
    int last = fullPath.rfind("/");
    if (last != -1)
        dir = fullPath.substr(0, last + 1);
    
    ObjLoader::shapes_t shapes;
    std::string errstr = ObjLoader::LoadObj(shapes, fullPath.c_str(), dir.c_str());
    if (!errstr.empty())
        return false;
    
    //convert to mesh and material
    std::vector<std::vector<unsigned short> > indices;
    std::vector<std::string> matnames;
    for (auto it = shapes.shapes.begin(); it != shapes.shapes.end(); it++) {
        indices.push_back((*it).mesh.indices);
        matnames.push_back(dir + (*it).material.diffuse_texname);
    }
    _model = Mesh::create(shapes.positions, shapes.normals, shapes.texcoords, indices);
    
    _model->retain();
    if (_model == nullptr)
        return false;
    
    

    _partcount = indices.size();
    _partMaterials = new MeshMaterial*[_partcount];
    
    for (auto it = 0; it != matnames.size(); it++) {
        auto material = MeshMaterial::create(_model);
        if (!matnames[it].empty())
        {
            material->setTexture(matnames[it]);
        }
        _partMaterials[it] = material;
        material->retain();
    }
    
    //add to cache
    __cachedSpriteTexNames[fullPath] = matnames;
    MeshCache::getInstance()->addMesh(fullPath, _model);
    
    _path = fullPath;

    return true;
}

Sprite3D::Sprite3D(): _partMaterials(nullptr), _partcount(0), _model(nullptr), _effect(nullptr)
{
}

Sprite3D::~Sprite3D()
{
    
    CC_SAFE_RELEASE_NULL(_model);
    
    for(auto i = 0; i < _partcount; i++)
        CC_SAFE_RELEASE_NULL(_partMaterials[i]);

    CC_SAFE_DELETE_ARRAY(_partMaterials);
    
    CC_SAFE_RELEASE_NULL(_effect);
}


bool Sprite3D::init(const std::string &path)
{
    for(auto i = 0; i < _partcount; i++)
        CC_SAFE_RELEASE_NULL(_partMaterials[i]);
    _partcount = 0;
    
    CC_SAFE_DELETE_ARRAY(_partMaterials);
    CC_SAFE_RELEASE_NULL(_model);
    
    //find from the cache
    Mesh* mesh = MeshCache::getInstance()->getMesh(path);
    if (mesh)
    {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
        _model = mesh;
        mesh->retain();
        _partcount = mesh->getMeshPartCount();
        _partMaterials = new MeshMaterial*[_partcount];
        
        auto matnames = __cachedSpriteTexNames[fullPath];
        for (auto it = 0; it != matnames.size(); it++) {
            auto material = MeshMaterial::create(_model);
            if (!matnames[it].empty())
            {
                material->setTexture(matnames[it]);
            }
            _partMaterials[it] = material;
            material->retain();
        }
        
        _path = fullPath;
    }
    else
    {
        //load from file
        std::string ext = path.substr(path.length() - 4, 4);
        if (ext == ".obj")
        {
            if (!loadFromObj(path))
                return false;
        }
        else
            return false;
    }
    
    
    return true;
}

void Sprite3D::setEffect(Sprite3DEffect* effect)
{
    CC_SAFE_RETAIN(effect);
    CC_SAFE_RELEASE_NULL(_effect);
    _effect = effect;
    _effect->init(this);
}

void Sprite3D::draw(Renderer *renderer, const Matrix &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Sprite3D::onDraw, this, transform, transformUpdated);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

void Sprite3D::onDraw(const Matrix &transform, bool transformUpdated)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // ********** Base Draw *************
    
    Color4F color(getDisplayedColor());
    color.a = getDisplayedOpacity() / 255.0f;
    
    if (_partMaterials && _model)
    {
        
        for (int i = 0; i < _model->getMeshPartCount(); i++) {
            auto material = getMeshMaterial(i);
            material->getProgram()->use();
            material->getProgram()->setUniformsForBuiltins(transform);

            material->setColor(Vector4(color.r, color.g, color.b, color.a));
            material->bind();
            
            MeshPart* meshPart = _model->getMeshPart(i);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPart->getIndexBuffer());
            glDrawElements(meshPart->getPrimitiveType(), meshPart->getIndexCount(), meshPart->getIndexFormat(), 0);
            
            material->unbind();
            
            //effect draw
            if (_effect) {

                _effect->getProgram()->use();
                _effect->getProgram()->setUniformsForBuiltins(transform);
                
                _effect->setColor(Vector4(color.r, color.g, color.b, color.a));
                _effect->bind();
                
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPart->getIndexBuffer());
                glDrawElements(meshPart->getPrimitiveType(), meshPart->getIndexCount(), meshPart->getIndexFormat(), 0);
                
                _effect->unbind();
            }
            
            CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, meshPart->getIndexCount());
        }
        
    }
    
    glDisable(GL_DEPTH_TEST);
    
}


NS_CC_END
