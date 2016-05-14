/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "3d/CCMesh.h"
#include "3d/CCMeshSkin.h"
#include "3d/CCSkeleton3D.h"
#include "3d/CCMeshVertexIndexData.h"
#include "2d/CCLight.h"
#include "2d/CCScene.h"
#include "base/CCEventDispatcher.h"
#include "base/CCDirector.h"
#include "base/CCConfiguration.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCPass.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCVertexAttribBinding.h"
#include "math/Mat4.h"

using namespace std;

NS_CC_BEGIN

// Helpers

//sampler uniform names, only diffuse and normal texture are supported for now
std::string s_uniformSamplerName[] =
{
    "",//NTextureData::Usage::Unknown,
    "",//NTextureData::Usage::None
    "",//NTextureData::Usage::Diffuse
    "",//NTextureData::Usage::Emissive
    "",//NTextureData::Usage::Ambient
    "",//NTextureData::Usage::Specular
    "",//NTextureData::Usage::Shininess
    "u_normalTex",//NTextureData::Usage::Normal
    "",//NTextureData::Usage::Bump
    "",//NTextureData::Usage::Transparency
    "",//NTextureData::Usage::Reflection
};

static const char          *s_dirLightUniformColorName = "u_DirLightSourceColor";
static const char          *s_dirLightUniformDirName = "u_DirLightSourceDirection";

static const char          *s_pointLightUniformColorName = "u_PointLightSourceColor";
static const char          *s_pointLightUniformPositionName = "u_PointLightSourcePosition";
static const char          *s_pointLightUniformRangeInverseName = "u_PointLightSourceRangeInverse";

static const char          *s_spotLightUniformColorName = "u_SpotLightSourceColor";
static const char          *s_spotLightUniformPositionName = "u_SpotLightSourcePosition";
static const char          *s_spotLightUniformDirName = "u_SpotLightSourceDirection";
static const char          *s_spotLightUniformInnerAngleCosName = "u_SpotLightSourceInnerAngleCos";
static const char          *s_spotLightUniformOuterAngleCosName = "u_SpotLightSourceOuterAngleCos";
static const char          *s_spotLightUniformRangeInverseName = "u_SpotLightSourceRangeInverse";

static const char          *s_ambientLightUniformColorName = "u_AmbientLightSourceColor";

// helpers
void Mesh::resetLightUniformValues()
{
    const auto& conf = Configuration::getInstance();
    int maxDirLight = conf->getMaxSupportDirLightInShader();
    int maxPointLight = conf->getMaxSupportPointLightInShader();
    int maxSpotLight = conf->getMaxSupportSpotLightInShader();

    _dirLightUniformColorValues.assign(maxDirLight, Vec3::ZERO);
    _dirLightUniformDirValues.assign(maxDirLight, Vec3::ZERO);

    _pointLightUniformColorValues.assign(maxPointLight, Vec3::ZERO);
    _pointLightUniformPositionValues.assign(maxPointLight, Vec3::ZERO);
    _pointLightUniformRangeInverseValues.assign(maxPointLight, 0.0f);

    _spotLightUniformColorValues.assign(maxSpotLight, Vec3::ZERO);
    _spotLightUniformPositionValues.assign(maxSpotLight, Vec3::ZERO);
    _spotLightUniformDirValues.assign(maxSpotLight, Vec3::ZERO);
    _spotLightUniformInnerAngleCosValues.assign(maxSpotLight, 1.0f);
    _spotLightUniformOuterAngleCosValues.assign(maxSpotLight, 0.0f);
    _spotLightUniformRangeInverseValues.assign(maxSpotLight, 0.0f);
}

//Generate a dummy texture when the texture file is missing
static Texture2D * getDummyTexture()
{
    auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("/dummyTexture");
    if(!texture)
    {
#ifdef NDEBUG
        unsigned char data[] ={0,0,0,0};//1*1 transparent picture
#else
        unsigned char data[] ={255,0,0,255};//1*1 red picture
#endif
        Image * image =new (std::nothrow) Image();
        image->initWithRawData(data,sizeof(data),1,1,sizeof(unsigned char));
        texture=Director::getInstance()->getTextureCache()->addImage(image,"/dummyTexture");
        image->release();
    }
    return texture;
}


Mesh::Mesh()
: _skin(nullptr)
, _visible(true)
, _isTransparent(false)
, _meshIndexData(nullptr)
, _material(nullptr)
, _glProgramState(nullptr)
, _blend(BlendFunc::ALPHA_NON_PREMULTIPLIED)
, _visibleChanged(nullptr)
, _blendDirty(true)
, _force2DQueue(false)
, _texFile("")
{
    
}
Mesh::~Mesh()
{
    for (auto &tex : _textures){
        CC_SAFE_RELEASE(tex.second);
    }
    CC_SAFE_RELEASE(_skin);
    CC_SAFE_RELEASE(_meshIndexData);
    CC_SAFE_RELEASE(_material);
    CC_SAFE_RELEASE(_glProgramState);
}

GLuint Mesh::getVertexBuffer() const
{
    return _meshIndexData->getVertexBuffer()->getVBO();
}

bool Mesh::hasVertexAttrib(int attrib) const
{
    return _meshIndexData->getMeshVertexData()->hasVertexAttrib(attrib);
}

ssize_t Mesh::getMeshVertexAttribCount() const
{
    return _meshIndexData->getMeshVertexData()->getMeshVertexAttribCount();
}

const MeshVertexAttrib& Mesh::getMeshVertexAttribute(int idx)
{
    return _meshIndexData->getMeshVertexData()->getMeshVertexAttrib(idx);
}

int Mesh::getVertexSizeInBytes() const
{
    return _meshIndexData->getVertexBuffer()->getSizePerVertex();
}

Mesh* Mesh::create(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const IndexArray& indices)
{
    int perVertexSizeInFloat = 0;
    std::vector<float> vertices;
    std::vector<MeshVertexAttrib> attribs;
    MeshVertexAttrib att;
    att.size = 3;
    att.type = GL_FLOAT;
    att.attribSizeBytes = att.size * sizeof(float);
    
    if (positions.size())
    {
        perVertexSizeInFloat += 3;
        att.vertexAttrib = GLProgram::VERTEX_ATTRIB_POSITION;
        attribs.push_back(att);
    }
    if (normals.size())
    {
        perVertexSizeInFloat += 3;
        att.vertexAttrib = GLProgram::VERTEX_ATTRIB_NORMAL;
        attribs.push_back(att);
    }
    if (texs.size())
    {
        perVertexSizeInFloat += 2;
        att.vertexAttrib = GLProgram::VERTEX_ATTRIB_TEX_COORD;
        att.size = 2;
        att.attribSizeBytes = att.size * sizeof(float);
        attribs.push_back(att);
    }
    
    bool hasNormal = (normals.size() != 0);
    bool hasTexCoord = (texs.size() != 0);
    //position, normal, texCoordinate into _vertexs
    size_t vertexNum = positions.size() / 3;
    for(size_t i = 0; i < vertexNum; i++)
    {
        vertices.push_back(positions[i * 3]);
        vertices.push_back(positions[i * 3 + 1]);
        vertices.push_back(positions[i * 3 + 2]);

        if (hasNormal)
        {
            vertices.push_back(normals[i * 3]);
            vertices.push_back(normals[i * 3 + 1]);
            vertices.push_back(normals[i * 3 + 2]);
        }
    
        if (hasTexCoord)
        {
            vertices.push_back(texs[i * 2]);
            vertices.push_back(texs[i * 2 + 1]);
        }
    }
    return create(vertices, perVertexSizeInFloat, indices, attribs);
}

Mesh* Mesh::create(const std::vector<float>& vertices, int perVertexSizeInFloat, const IndexArray& indices, const std::vector<MeshVertexAttrib>& attribs)
{
    MeshData meshdata;
    meshdata.attribs = attribs;
    meshdata.vertex = vertices;
    meshdata.subMeshIndices.push_back(indices);
    meshdata.subMeshIds.push_back("");
    auto meshvertexdata = MeshVertexData::create(meshdata);
    auto indexData = meshvertexdata->getMeshIndexDataByIndex(0);
    
    return create("", indexData);
}

Mesh* Mesh::create(const std::string& name, MeshIndexData* indexData, MeshSkin* skin)
{
    auto state = new (std::nothrow) Mesh();
    state->autorelease();
    state->bindMeshCommand();
    state->_name = name;
    state->setMeshIndexData(indexData);
    state->setSkin(skin);
    
    return state;
}

void Mesh::setVisible(bool visible)
{
    if (_visible != visible)
    {
        _visible = visible;
        if (_visibleChanged)
            _visibleChanged();
    }
}

bool Mesh::isVisible() const
{
    return _visible;
}

void Mesh::setTexture(const std::string& texPath)
{
    _texFile = texPath;
    auto tex = Director::getInstance()->getTextureCache()->addImage(texPath);
    setTexture(tex, NTextureData::Usage::Diffuse);
}

void Mesh::setTexture(Texture2D* tex)
{
    setTexture(tex, NTextureData::Usage::Diffuse);
}

void Mesh::setTexture(Texture2D* tex, NTextureData::Usage usage, bool cacheFileName)
{
    // Texture must be saved for future use
    // it doesn't matter if the material is already set or not
    // This functionality is added for compatibility issues
    if (tex == nullptr)
        tex = getDummyTexture();
    
    CC_SAFE_RETAIN(tex);
    CC_SAFE_RELEASE(_textures[usage]);
    _textures[usage] = tex;   
    
    if (usage == NTextureData::Usage::Diffuse){
        if (_material) {
            auto technique = _material->_currentTechnique;
            for(auto& pass: technique->_passes)
            {
                // FIXME: Ideally it should use glProgramState->setUniformTexture()
                // and set CC_Texture0 that way. But trying to it, will trigger
                // another bug
                pass->setTexture(tex);
            }
        }
        
        bindMeshCommand();
        if (cacheFileName)
            _texFile = tex->getPath();
    }
    else if (usage == NTextureData::Usage::Normal) // currently only diffuse and normal are supported
    {
        if (_material){
            auto technique = _material->_currentTechnique;
            for(auto& pass: technique->_passes)
            {
                pass->getGLProgramState()->setUniformTexture(s_uniformSamplerName[(int)usage], tex);
            }
        }
    }
}

void Mesh::setTexture(const std::string& texPath, NTextureData::Usage usage)
{
    auto tex = Director::getInstance()->getTextureCache()->addImage(texPath);
    setTexture(tex, usage);
}

Texture2D* Mesh::getTexture() const
{
    return _textures.at(NTextureData::Usage::Diffuse);
}

Texture2D* Mesh::getTexture(NTextureData::Usage usage)
{
    return _textures[usage];
}

void Mesh::setMaterial(Material* material)
{
    if (_material != material) {
        CC_SAFE_RELEASE(_material);
        _material = material;
        CC_SAFE_RETAIN(_material);
    }

    if (_material)
    {
        for (auto technique: _material->getTechniques())
        {
            for (auto pass: technique->getPasses())
            {
                auto vertexAttribBinding = VertexAttribBinding::create(_meshIndexData, pass->getGLProgramState());
                pass->setVertexAttribBinding(vertexAttribBinding);
            }
        }
    }
    // Was the texture set before teh GLProgramState ? Set it
    for(auto& tex : _textures)
        setTexture(tex.second, tex.first);
        
    
    if (_blendDirty)
        setBlendFunc(_blend);
    
    bindMeshCommand();
}

Material* Mesh::getMaterial() const
{
    return _material;
}

void Mesh::draw(Renderer* renderer, float globalZOrder, const Mat4& transform, uint32_t flags, unsigned int lightMask, const Vec4& color, bool forceDepthWrite)
{
    if (! isVisible())
        return;

    bool isTransparent = (_isTransparent || color.w < 1.f);
    float globalZ = isTransparent ? 0 : globalZOrder;
    if (isTransparent)
        flags |= Node::FLAGS_RENDER_AS_3D;

    _meshCommand.init(globalZ,
                      _material,
                      getVertexBuffer(),
                      getIndexBuffer(),
                      getPrimitiveType(),
                      getIndexFormat(),
                      getIndexCount(),
                      transform,
                      flags);


//    if (isTransparent && !forceDepthWrite)
//        _material->getStateBlock()->setDepthWrite(false);
//    else
        _material->getStateBlock()->setDepthWrite(true);


    _meshCommand.setSkipBatching(isTransparent);
    _meshCommand.setTransparent(isTransparent);
    _meshCommand.set3D(!_force2DQueue);
    _material->getStateBlock()->setBlend(_force2DQueue || isTransparent);

    // set default uniforms for Mesh
    // 'u_color' and others
    const auto scene = Director::getInstance()->getRunningScene();
    auto technique = _material->_currentTechnique;
    for(const auto pass : technique->_passes)
    {
        auto programState = pass->getGLProgramState();
        programState->setUniformVec4("u_color", color);

        if (_skin)
            programState->setUniformVec4v("u_matrixPalette", (GLsizei)_skin->getMatrixPaletteSize(), _skin->getMatrixPalette());

        if (scene && scene->getLights().size() > 0)
            setLightUniforms(pass, scene, color, lightMask);
    }

    renderer->addCommand(&_meshCommand);
}

void Mesh::setSkin(MeshSkin* skin)
{
    if (_skin != skin)
    {
        CC_SAFE_RETAIN(skin);
        CC_SAFE_RELEASE(_skin);
        _skin = skin;
        calculateAABB();
    }
}

void Mesh::setMeshIndexData(MeshIndexData* subMesh)
{
    if (_meshIndexData != subMesh)
    {
        CC_SAFE_RETAIN(subMesh);
        CC_SAFE_RELEASE(_meshIndexData);
        _meshIndexData = subMesh;
        calculateAABB();
        bindMeshCommand();
    }
}

void Mesh::setGLProgramState(GLProgramState* glProgramState)
{
    // XXX create dummy texture
    auto material = Material::createWithGLStateProgram(glProgramState);
    if (_material)
        material->setStateBlock(_material->getStateBlock());
    setMaterial(material);
}

GLProgramState* Mesh::getGLProgramState() const
{
    return _material ?
                _material->_currentTechnique->_passes.at(0)->getGLProgramState()
                : nullptr;
}

void Mesh::calculateAABB()
{
    if (_meshIndexData)
    {
        _aabb = _meshIndexData->getAABB();
        if (_skin)
        {
            //get skin root
            Bone3D* root = nullptr;
            Mat4 invBindPose;
            if (_skin->_skinBones.size())
            {
                root = _skin->_skinBones.at(0);
                while (root) {
                    auto parent = root->getParentBone();
                    bool parentInSkinBone = false;
                    for (const auto& bone : _skin->_skinBones) {
                        if (bone == parent)
                        {
                            parentInSkinBone = true;
                            break;
                        }
                    }
                    if (!parentInSkinBone)
                        break;
                    root = parent;
                }
            }
            
            if (root)
            {
                _aabb.transform(root->getWorldMat() * _skin->getInvBindPose(root));
            }
        }
    }
}

void Mesh::bindMeshCommand()
{
    if (_material && _meshIndexData)
    {
        auto pass = _material->_currentTechnique->_passes.at(0);
        auto glprogramstate = pass->getGLProgramState();
        auto texture = pass->getTexture();
        auto textureid = texture ? texture->getName() : 0;
        // XXX
//        auto blend = pass->getStateBlock()->getBlendFunc();
        auto blend = BlendFunc::ALPHA_PREMULTIPLIED;

        _meshCommand.genMaterialID(textureid, glprogramstate, _meshIndexData->getVertexBuffer()->getVBO(), _meshIndexData->getIndexBuffer()->getVBO(), blend);
        _material->getStateBlock()->setCullFace(true);
        _material->getStateBlock()->setDepthTest(true);
    }
}

void Mesh::setLightUniforms(Pass* pass, Scene* scene, const Vec4& color, unsigned int lightmask)
{
    CCASSERT(pass, "Invalid Pass");
    CCASSERT(scene, "Invalid scene");

    const auto& conf = Configuration::getInstance();
    int maxDirLight = conf->getMaxSupportDirLightInShader();
    int maxPointLight = conf->getMaxSupportPointLightInShader();
    int maxSpotLight = conf->getMaxSupportSpotLightInShader();
    auto &lights = scene->getLights();

    auto glProgramState = pass->getGLProgramState();
    auto attributes = pass->getVertexAttributeBinding()->getVertexAttribsFlags();

    if (attributes & (1 << GLProgram::VERTEX_ATTRIB_NORMAL))
    {
        resetLightUniformValues();

        GLint enabledDirLightNum = 0;
        GLint enabledPointLightNum = 0;
        GLint enabledSpotLightNum = 0;
        Vec3 ambientColor;
        for (const auto& light : lights)
        {
            bool useLight = light->isEnabled() && ((unsigned int)light->getLightFlag() & lightmask);
            if (useLight)
            {
                float intensity = light->getIntensity();
                switch (light->getLightType())
                {
                    case LightType::DIRECTIONAL:
                    {
                        if(enabledDirLightNum < maxDirLight)
                        {
                            auto dirLight = static_cast<DirectionLight *>(light);
                            Vec3 dir = dirLight->getDirectionInWorld();
                            dir.normalize();
                            const Color3B &col = dirLight->getDisplayedColor();
                            _dirLightUniformColorValues[enabledDirLightNum].set(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity);
                            _dirLightUniformDirValues[enabledDirLightNum] = dir;
                            ++enabledDirLightNum;
                        }

                    }
                        break;
                    case LightType::POINT:
                    {
                        if(enabledPointLightNum < maxPointLight)
                        {
                            auto pointLight = static_cast<PointLight *>(light);
                            Mat4 mat= pointLight->getNodeToWorldTransform();
                            const Color3B &col = pointLight->getDisplayedColor();
                            _pointLightUniformColorValues[enabledPointLightNum].set(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity);
                            _pointLightUniformPositionValues[enabledPointLightNum].set(mat.m[12], mat.m[13], mat.m[14]);
                            _pointLightUniformRangeInverseValues[enabledPointLightNum] = 1.0f / pointLight->getRange();
                            ++enabledPointLightNum;
                        }
                    }
                        break;
                    case LightType::SPOT:
                    {
                        if(enabledSpotLightNum < maxSpotLight)
                        {
                            auto spotLight = static_cast<SpotLight *>(light);
                            Vec3 dir = spotLight->getDirectionInWorld();
                            dir.normalize();
                            Mat4 mat= light->getNodeToWorldTransform();
                            const Color3B &col = spotLight->getDisplayedColor();
                            _spotLightUniformColorValues[enabledSpotLightNum].set(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity);
                            _spotLightUniformPositionValues[enabledSpotLightNum].set(mat.m[12], mat.m[13], mat.m[14]);
                            _spotLightUniformDirValues[enabledSpotLightNum] = dir;
                            _spotLightUniformInnerAngleCosValues[enabledSpotLightNum] = spotLight->getCosInnerAngle();
                            _spotLightUniformOuterAngleCosValues[enabledSpotLightNum] = spotLight->getCosOuterAngle();
                            _spotLightUniformRangeInverseValues[enabledSpotLightNum] = 1.0f / spotLight->getRange();
                            ++enabledSpotLightNum;
                        }
                    }
                        break;
                    case LightType::AMBIENT:
                    {
                        auto ambLight = static_cast<AmbientLight *>(light);
                        const Color3B &col = ambLight->getDisplayedColor();
                        ambientColor.add(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity);
                    }
                        break;
                    default:
                        break;
                }
            }
        }

        if (0 < maxDirLight)
        {
            glProgramState->setUniformVec3v(s_dirLightUniformColorName, _dirLightUniformColorValues.size(), &_dirLightUniformColorValues[0]);
            glProgramState->setUniformVec3v(s_dirLightUniformDirName, _dirLightUniformDirValues.size(), &_dirLightUniformDirValues[0]);
        }

        if (0 < maxPointLight)
        {
            glProgramState->setUniformVec3v(s_pointLightUniformColorName, _pointLightUniformColorValues.size(), &_pointLightUniformColorValues[0]);
            glProgramState->setUniformVec3v(s_pointLightUniformPositionName, _pointLightUniformPositionValues.size(), &_pointLightUniformPositionValues[0]);
            glProgramState->setUniformFloatv(s_pointLightUniformRangeInverseName, _pointLightUniformRangeInverseValues.size(), &_pointLightUniformRangeInverseValues[0]);
        }

        if (0 < maxSpotLight)
        {
            glProgramState->setUniformVec3v(s_spotLightUniformColorName, _spotLightUniformColorValues.size(), &_spotLightUniformColorValues[0]);
            glProgramState->setUniformVec3v(s_spotLightUniformPositionName, _spotLightUniformPositionValues.size(), &_spotLightUniformPositionValues[0]);
            glProgramState->setUniformVec3v(s_spotLightUniformDirName, _spotLightUniformDirValues.size(), &_spotLightUniformDirValues[0]);
            glProgramState->setUniformFloatv(s_spotLightUniformInnerAngleCosName, _spotLightUniformInnerAngleCosValues.size(), &_spotLightUniformInnerAngleCosValues[0]);
            glProgramState->setUniformFloatv(s_spotLightUniformOuterAngleCosName, _spotLightUniformOuterAngleCosValues.size(), &_spotLightUniformOuterAngleCosValues[0]);
            glProgramState->setUniformFloatv(s_spotLightUniformRangeInverseName, _spotLightUniformRangeInverseValues.size(), &_spotLightUniformRangeInverseValues[0]);
        }

        glProgramState->setUniformVec3(s_ambientLightUniformColorName, Vec3(ambientColor.x, ambientColor.y, ambientColor.z));
    }
    else // normal does not exist
    {
        Vec3 ambient(0.0f, 0.0f, 0.0f);
        bool hasAmbient = false;
        for (const auto& light : lights)
        {
            if (light->getLightType() == LightType::AMBIENT)
            {
                bool useLight = light->isEnabled() && ((unsigned int)light->getLightFlag() & lightmask);
                if (useLight)
                {
                    hasAmbient = true;
                    const Color3B &col = light->getDisplayedColor();
                    ambient.x += col.r * light->getIntensity();
                    ambient.y += col.g * light->getIntensity();
                    ambient.z += col.b * light->getIntensity();
                }
            }
        }
        if (hasAmbient)
        {
            ambient.x /= 255.f; ambient.y /= 255.f; ambient.z /= 255.f;
            //override the uniform value of u_color using the calculated color 
            glProgramState->setUniformVec4("u_color", Vec4(color.x * ambient.x, color.y * ambient.y, color.z * ambient.z, color.w));
        }
    }
}

void Mesh::setBlendFunc(const BlendFunc &blendFunc)
{
    // Blend must be saved for future use
    // it doesn't matter if the material is already set or not
    // This functionality is added for compatibility issues
    if(_blend != blendFunc)
    {
        _blendDirty = true;
        _blend = blendFunc;
    }

    if (_material) {
        _material->getStateBlock()->setBlendFunc(blendFunc);
        bindMeshCommand();
    }
}

const BlendFunc& Mesh::getBlendFunc() const
{
// return _material->_currentTechnique->_passes.at(0)->getBlendFunc();
    return _blend;
}

GLenum Mesh::getPrimitiveType() const
{
    return _meshIndexData->getPrimitiveType();
}

ssize_t Mesh::getIndexCount() const
{
    return _meshIndexData->getIndexBuffer()->getIndexNumber();
}

GLenum Mesh::getIndexFormat() const
{
    return GL_UNSIGNED_SHORT;
}

GLuint Mesh::getIndexBuffer() const
{
    return _meshIndexData->getIndexBuffer()->getVBO();
}
NS_CC_END
