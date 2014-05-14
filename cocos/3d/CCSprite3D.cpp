
#include "CCSprite3D.h"
#include "CCMeshCache.h"
#include "CCMesh.h"

#include "CCObjLoader.h"
#include "2d/platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "2d/CCTextureCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"

//begin include shader file
#define STRINGIFY(A)  #A
#include "Textured.es2.vert.h"
#include "Textured.es2.frag.h"
#include "Colored.es2.frag.h"
//end include shader file

NS_CC_BEGIN

std::map<std::string, std::vector<std::string> > __cachedSpriteTexNames;

Sprite3D* Sprite3D::create(const std::string &modelPath)
{
    if (modelPath.length() < 4)
        CCASSERT(false, "improper name specified when creating Sprite3D");
    
    auto sprite = new Sprite3D();
    if (sprite && sprite->initWithFile(modelPath))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite3D* Sprite3D::create(const std::string &modelPath, const std::string &texturePath)
{
    if (modelPath.length() < 4)
        CCASSERT(false, "improper name specified when creating Sprite3D");
    
    auto sprite = new Sprite3D();
    if (sprite && sprite->initWithFile(modelPath))
    {
        sprite->setTexture(texturePath);
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

// Sprite3D* Sprite3D::create(Mesh* mesh, const std::string& texturePath)
// {
//     CCASSERT(nullptr != mesh, "Could not create a Sprite3D from a null Mesh");
//     auto sprite = new Sprite3D();
//     if(sprite)
//     {
//         sprite->_mesh = mesh;
//         sprite->_mesh->retain();
//         sprite->setTexture(texturePath);
//         sprite->autorelease();
//         return sprite;
//     }
//     CC_SAFE_DELETE(sprite);
//     return nullptr;
// }

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
    for (auto it = shapes.shapes.begin(); it != shapes.shapes.end(); it++)
    {
        indices.push_back((*it).mesh.indices);
        matnames.push_back(dir + (*it).material.diffuse_texname);
    }
    _mesh = Mesh::create(shapes.positions, shapes.normals, shapes.texcoords, indices);
    
    _mesh->retain();
    if (_mesh == nullptr)
        return false;
    
    _partcount = indices.size();
    
    
    for (auto it = 0; it != matnames.size(); it++)
    {
        if (!matnames[it].empty())
        {
            auto tex = Director::getInstance()->getTextureCache()->addImage(matnames[it]);
            if (tex) _textures.pushBack(tex);
        }
        
    }
    
    for (int i = 0; i < _mesh->getMeshPartCount(); i++)
    {
        auto programstate = GLProgramState::getOrCreate(getDefGLProgram(_mesh->getAttribFlag() & GL::VERTEX_ATTRIB_FLAG_TEX_COORD));
        _programState.pushBack(programstate);
        
        programstate->setVertexAttribPointer("a_position", 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        programstate->setVertexAttribPointer("a_texCoord", 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    }
    
    //add to cache
    __cachedSpriteTexNames[fullPath] = matnames;
    MeshCache::getInstance()->addMesh(fullPath, _mesh);
    
    _path = fullPath;

    return true;
}

Sprite3D::Sprite3D()
: _partcount(0)
, _mesh(nullptr)
, _blend(BlendFunc::DISABLE)
{
}

Sprite3D::~Sprite3D()
{
    CC_SAFE_RELEASE_NULL(_mesh);
}

bool Sprite3D::initWithFile(const std::string &path)
{
    _partcount = 0;
    
    CC_SAFE_RELEASE_NULL(_mesh);
    _programState.clear();
    _textures.clear();
    
    //find from the cache
    Mesh* mesh = MeshCache::getInstance()->getMesh(path);
    if (mesh)
    {
        _mesh = mesh;
        _mesh->retain();
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);

        _partcount = mesh->getMeshPartCount();
        
        auto matnames = __cachedSpriteTexNames[fullPath];
        for (auto it = 0; it != matnames.size(); it++)
        {
            auto tex = Director::getInstance()->getTextureCache()->addImage(matnames[it]);
            if (tex) _textures.pushBack(tex);
        }
        
        for (int i = 0; i < _mesh->getMeshPartCount(); i++)
        {
            auto programstate = GLProgramState::getOrCreate(getDefGLProgram(mesh->getAttribFlag() & GL::VERTEX_ATTRIB_FLAG_TEX_COORD));
            _programState.pushBack(programstate);
            
            programstate->setVertexAttribPointer("a_position", 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            programstate->setVertexAttribPointer("a_texCoord", 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        }
        
        _path = fullPath;
        return true;
    }
    else
    {
        //load from file
        std::string ext = path.substr(path.length() - 4, 4);
        if (ext != ".obj" || !loadFromObj(path))
        {
                return false;
        }
        return true;
    }
}

GLProgram* Sprite3D::getDefGLProgram(bool textured)
{
    static GLProgram s_defGLProgramTex;
    static GLProgram s_defGLProgram;
    if(textured && s_defGLProgramTex.getProgram() == 0)
    {
        s_defGLProgramTex.initWithByteArrays(baseVertexShader, baseTexturedFrag);
        s_defGLProgramTex.link();
        s_defGLProgramTex.updateUniforms();
    }
    
    if(!textured && s_defGLProgram.getProgram() == 0)
    {
        s_defGLProgram.initWithByteArrays(baseVertexShader, baseTexturedFrag);
        s_defGLProgram.link();
        s_defGLProgram.updateUniforms();
    }
    
    return textured ? &s_defGLProgramTex : &s_defGLProgram;
}


void Sprite3D::setTexture(const std::string& texFile)
{
    auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
    if (_textures.empty())
        _textures.pushBack(tex);
    else
        _textures.replace(0, tex);
}
//
//void Sprite3D::setEffect(Sprite3DEffect* effect)
//{
//    CC_SAFE_RETAIN(effect);
//    CC_SAFE_RELEASE_NULL(_effect);
//    _effect = effect;
//    _effect->init(this);
//}

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
    GL::blendFunc(_blend.src, _blend.dst);
    // ********** Base Draw *************

    Color4F color(getDisplayedColor());
    color.a = getDisplayedOpacity() / 255.0f;
    
    if (_mesh)
    {
        for (int i = 0; i < _mesh->getMeshPartCount(); i++)
        {
            auto meshPart = _mesh->getMeshPart(i);
            auto programstate = _programState.at(i);
            //size_t offset = 0;//(size_t)_mesh->getVertexPointer();
            
            
            programstate->setUniformVec4("u_color", Vector4(color.r, color.g, color.b, color.a));
            if (_textures.at(i))
            {
                GL::bindTexture2D(_textures.at(i)->getName());
            }
            
            glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVertexBuffer());
            programstate->apply(transform);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPart->getIndexBuffer());
            glDrawElements(meshPart->getPrimitiveType(), meshPart->getIndexCount(), meshPart->getIndexFormat(), 0);
        }
    }
    
//    if (_partMaterials && _mesh)
//    {
//        
//        for (int i = 0; i < _mesh->getMeshPartCount(); i++) {
//            auto material = getMeshMaterial(i);
//            material->getProgram()->use();
//            material->getProgram()->setUniformsForBuiltins(transform);
//
//            material->setColor(Vector4(color.r, color.g, color.b, color.a));
//            material->bind();
//            
//            MeshPart* meshPart = _mesh->getMeshPart(i);
//            
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPart->getIndexBuffer());
//            glDrawElements(meshPart->getPrimitiveType(), meshPart->getIndexCount(), meshPart->getIndexFormat(), 0);
//            
//            material->unbind();
//            
//            //effect draw
//            if (_effect) {
//
//                _effect->getProgram()->use();
//                _effect->getProgram()->setUniformsForBuiltins(transform);
//                
//                _effect->setColor(Vector4(color.r, color.g, color.b, color.a));
//                _effect->bind();
//                
//                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPart->getIndexBuffer());
//                glDrawElements(meshPart->getPrimitiveType(), meshPart->getIndexCount(), meshPart->getIndexFormat(), 0);
//                
//                _effect->unbind();
//            }
//            
//            CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, meshPart->getIndexCount());
//        }
//        
//    }
    
    glDisable(GL_DEPTH_TEST);
    
}

void Sprite3D::setBlendFunc(const BlendFunc &blendFunc)
{
    if(_blend.src != blendFunc.src || _blend.dst != blendFunc.dst)
    {
        _blend = blendFunc;
    }
}

const BlendFunc& Sprite3D::getBlendFunc() const
{
    return _blend;
}


NS_CC_END
