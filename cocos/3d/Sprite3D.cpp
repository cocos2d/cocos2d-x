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

#include "renderer/CCGLProgramState.h"

#define STRINGIFY(A)  #A
//#include "../Shaders/TexturedLighting.es2.vert.h"
#include "Textured.es2.vert.h"
#include "Textured.es2.frag.h"
#include "Colored.es2.frag.h"

#include "ObjLoader.h"

NS_CC_BEGIN

std::map<std::string, std::vector<std::string> > __cachedSpriteTexNames;

GLProgram* Sprite3D::s_defGLProgramTex = nullptr;
GLProgram* Sprite3D::s_defGLProgram = nullptr;


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
    
    _programState = new GLProgramState*[_partcount];
    
    for (auto it = 0; it != matnames.size(); it++) {
        //auto material = GLProgramState::get
        if (!matnames[it].empty())
        {
            auto tex = Director::getInstance()->getTextureCache()->addImage(matnames[it]);
            if (tex)
            _textures.pushBack(tex);
        }
        
    }
    
    for (int i = 0; i < _model->getMeshPartCount(); i++) {
        _programState[i] = GLProgramState::get(getDefGLProgram(_model->getAttribFlag() & GL::VERTEX_ATTRIB_FLAG_TEX_COORDS));
    }
    
    //add to cache
    __cachedSpriteTexNames[fullPath] = matnames;
    MeshCache::getInstance()->addMesh(fullPath, _model);
    
    _path = fullPath;

    return true;
}

Sprite3D::Sprite3D(): _programState(nullptr), _partcount(0), _model(nullptr)
{
}

Sprite3D::~Sprite3D()
{
    
    CC_SAFE_RELEASE_NULL(_model);
    
    for(auto i = 0; i < _partcount; i++)
        CC_SAFE_RELEASE_NULL(_programState[i]);

    CC_SAFE_DELETE_ARRAY(_programState);
    
}


bool Sprite3D::init(const std::string &path)
{
    for(auto i = 0; i < _partcount; i++)
        CC_SAFE_RELEASE_NULL(_programState[i]);
    _partcount = 0;
    
    CC_SAFE_DELETE_ARRAY(_programState);
    CC_SAFE_RELEASE_NULL(_model);
    
    //find from the cache
    Mesh* mesh = MeshCache::getInstance()->getMesh(path);
    if (mesh)
    {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
        _model = mesh;
        mesh->retain();
        _partcount = mesh->getMeshPartCount();
        
        _programState = new GLProgramState*[_partcount];
        
        auto matnames = __cachedSpriteTexNames[fullPath];
        for (auto it = 0; it != matnames.size(); it++) {

            auto tex = Director::getInstance()->getTextureCache()->addImage(matnames[it]);
            if (tex)
            _textures.pushBack(tex);
            
        }
        
        for (int i = 0; i < _model->getMeshPartCount(); i++) {
            _programState[i] = GLProgramState::get(getDefGLProgram(mesh->getAttribFlag() & GL::VERTEX_ATTRIB_FLAG_TEX_COORDS));
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

GLProgram* Sprite3D::getDefGLProgram(bool textured)
{
 
    if (textured && s_defGLProgramTex)
        return s_defGLProgramTex;
    
    if (!textured && s_defGLProgram)
        return s_defGLProgram;
    
    GLProgram* program = nullptr;
    if (textured)
    {
        s_defGLProgramTex = GLProgram::createWithByteArrays(baseVertexShader, baseTexturedFrag);
        program = s_defGLProgramTex;
        
    }
    else
    {
        s_defGLProgram = GLProgram::createWithByteArrays(baseVertexShader, baseColoredFrag);
        program = s_defGLProgram;
    }

    return program;
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
    // ********** Base Draw *************

    
    Color4F color(getDisplayedColor());
    color.a = getDisplayedOpacity() / 255.0f;
    
    if (_programState && _model)
    {
        for (int i = 0; i < _model->getMeshPartCount(); i++) {
            auto meshPart = _model->getMeshPart(i);
            auto programstate = _programState[i];
            programstate->setVertexAttribPointer("a_position", 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), _model->getVertexPointer());
            programstate->setVertexAttribPointer("a_texCoord", 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), ((char*)_model->getVertexPointer() + 6 * sizeof(float)));
            
            //programstate->setUniformVec4("u_color", Vector4(color.r, color.g, color.b, color.a));
            if (_textures.at(i))
            {
                GL::bindTexture2D(_textures.at(i)->getName());
            }
            programstate->apply(transform);
            
            //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPart->getIndexBuffer());
            glDrawElements(meshPart->getPrimitiveType(), meshPart->getIndexCount(), meshPart->getIndexFormat(), _model->getIndexPointer(i));
        }
    }
    
//    if (_partMaterials && _model)
//    {
//        
//        for (int i = 0; i < _model->getMeshPartCount(); i++) {
//            auto material = getMeshMaterial(i);
//            material->getProgram()->use();
//            material->getProgram()->setUniformsForBuiltins(transform);
//
//            material->setColor(Vector4(color.r, color.g, color.b, color.a));
//            material->bind();
//            
//            MeshPart* meshPart = _model->getMeshPart(i);
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


NS_CC_END
