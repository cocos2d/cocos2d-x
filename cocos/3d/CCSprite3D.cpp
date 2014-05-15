
#include "CCSprite3D.h"
#include "CCSprite3DDataCache.h"
#include "CCMesh.h"
#include "CCSprite3DEffect.h"

#include "CCObjLoader.h"
#include "2d/platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "2d/CCTextureCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"

//begin include shader file
#define STRINGIFY(A)  #A
#include "Textured.es2.vert.h"
#include "Colored.es2.frag.h"
//end include shader file

NS_CC_BEGIN

std::string s_attributeNames[] = {GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::ATTRIBUTE_NAME_NORMAL};

//std::map<std::string, std::vector<std::string> > __cachedSpriteTexNames;

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
    auto sprite = create(modelPath);
    if (sprite)
    {
        sprite->setTexture(texturePath);
    }
    
    return sprite;
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
    std::vector<unsigned short> indices;
    std::vector<std::string> matnames;
    for (auto it = shapes.shapes.begin(); it != shapes.shapes.end(); it++)
    {
        indices.insert(indices.end(), (*it).mesh.indices.begin(),(*it).mesh.indices.end());
        //indices.push_back((*it).mesh.indices);
        matnames.push_back(dir + (*it).material.diffuse_texname);
    }
    _mesh = Mesh::create(shapes.positions, shapes.normals, shapes.texcoords, indices);
    
    _mesh->retain();
    if (_mesh == nullptr)
        return false;
    
    _partcount = indices.size();
    
    if (matnames.size())
    {
        setTexture(matnames[0]);
    }
    genGLProgramState();
    
    //add to cache
    Sprite3DDataCache::getInstance()->addSprite3D(fullPath, _mesh, matnames.size() > 0 ? matnames[0] : "");

    return true;
}

Sprite3D::Sprite3D()
: _partcount(0)
, _mesh(nullptr)
, _effect(nullptr)
, _texture(nullptr)
, _blend(BlendFunc::DISABLE)
{
}

Sprite3D::~Sprite3D()
{
    CC_SAFE_RELEASE_NULL(_mesh);
    CC_SAFE_RELEASE_NULL(_effect);
}

bool Sprite3D::initWithFile(const std::string &path)
{
    _partcount = 0;
    
    CC_SAFE_RELEASE_NULL(_mesh);
    
    CC_SAFE_RELEASE_NULL(_texture);
    
    //find from the cache
    Mesh* mesh = Sprite3DDataCache::getInstance()->getSprite3DMesh(path);
    if (mesh)
    {
        _mesh = mesh;
        _mesh->retain();
        
        auto tex = Sprite3DDataCache::getInstance()->getSprite3DTexture(path);
        setTexture(tex);

        genGLProgramState();
        
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

void Sprite3D::genGLProgramState()
{
    auto programstate = GLProgramState::getOrCreateWithGLProgram(getDefGLProgram(_mesh->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_TEX_COORD)));
    int offset = 0;
    auto attributeCount = _mesh->getMeshVertexAttribCount();
    for (auto k = 0; k < attributeCount; k++) {
        auto meshattribute = _mesh->getMeshVertexAttribute(k);
        programstate->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib], meshattribute.size, meshattribute.type, GL_FALSE, _mesh->getVertexSizeInBytes(), (void*)offset);
        offset += meshattribute.attribSizeBytes;
    }
    
    setGLProgramState(programstate);
}

GLProgram* Sprite3D::getDefGLProgram(bool textured)
{
    if(textured)
    {
        return GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION_TEXTURE);
    }
    else
    {
        return GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION);
    }
//    static GLProgram s_defGLProgramTex;
//    static GLProgram s_defGLProgram;
//    if(textured && s_defGLProgramTex.getProgram() == 0)
//    {
//        s_defGLProgramTex.initWithByteArrays(baseVertexShader, baseTexturedFrag);
//        s_defGLProgramTex.link();
//        s_defGLProgramTex.updateUniforms();
//    }
//    
//    if(!textured && s_defGLProgram.getProgram() == 0)
//    {
//        s_defGLProgram.initWithByteArrays(baseVertexShader, baseTexturedFrag);
//        s_defGLProgram.link();
//        s_defGLProgram.updateUniforms();
//    }
//    
//    return textured ? &s_defGLProgramTex : &s_defGLProgram;
}


void Sprite3D::setTexture(const std::string& texFile)
{
    auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
    CC_SAFE_RETAIN(tex);
    CC_SAFE_RELEASE_NULL(_texture);
    _texture = tex;
}

void Sprite3D::setTexture(Texture2D* texture)
{
    CC_SAFE_RETAIN(texture);
    CC_SAFE_RELEASE_NULL(_texture);
    _texture = texture;
}

void Sprite3D::setEffect(Sprite3DEffect* effect)
{
    CC_SAFE_RETAIN(effect);
    CC_SAFE_RELEASE_NULL(_effect);
    _effect = effect;
    _effect->initEffect(this);
}

void Sprite3D::draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Sprite3D::onDraw, this, transform, transformUpdated);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

void Sprite3D::onDraw(const Mat4 &transform, bool transformUpdated)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    GL::blendFunc(_blend.src, _blend.dst);
    // ********** Base Draw *************

    Color4F color(getDisplayedColor());
    color.a = getDisplayedOpacity() / 255.0f;
    
    if (_mesh)
    {
        auto programstate = getGLProgramState();
        
        programstate->setUniformVec4("u_color", Vec4(color.r, color.g, color.b, color.a));
        GL::bindTexture2D(_texture->getName());
        
        glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVertexBuffer());
        programstate->apply(transform);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->getIndexBuffer());
        glDrawElements(_mesh->getPrimitiveType(), _mesh->getIndexCount(), _mesh->getIndexFormat(), 0);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _mesh->getIndexCount());
        
        if (_effect)
            _effect->drawSpriteEffect(transform);
    }
    
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
