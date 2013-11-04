#include "Base.h"
#include "C3DParticleRender.h"

#include "cocos3d.h"
#include "C3DMaterial.h"
#include "C3DTexture.h"
#include "C3DEffect.h"
#include "C3DSampler.h"
#include "C3DVertexFormat.h"
#include "C3DLayer.h"
#include "C3DVertexDeclaration.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "cocos2d.h"
#include "MaterialParameter.h"
#include "C3DParticleSystem.h"
#include "C3DParticleEmitter.h"
#include "C3DBatchMesh.h"
#include "C3DBatchModel.h"

#include "Vertex.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "C3DRenderState.h"
#include "C3DParticleSystemCommon.h"
#include "C3DVector2.h"
#include "StringTool.h"

namespace cocos3d
{

C3DParticleRender::C3DParticleRender(C3DParticleSystem* system):
	_system(system), _nCapacity(0), _nParticle(0), _model(NULL), _nFrameRow(0), _nFrameCol(0), _frameCoord(NULL), _nFrameCount(0)
{
	_model = NULL;
	_spriteAnimated = false;
	_spriteLooped = false;
	_spriteFrameDurationSecs = 0.0f;
	_isVisible = true;
	_particleVs = "shaders/particle.vsh";
	_particleFs = "shaders/particle.fsh";
	_partilceTexture = "particles/notexture.png";
	_srcBlend = C3DStateBlock::BLEND_SRC_ALPHA;
	_dstBlend = C3DStateBlock::BLEND_ONE;
}

C3DParticleRender::~C3DParticleRender()
{
    CC_SAFE_DELETE(_model);

	CC_SAFE_DELETE_ARRAY(_frameCoord);
}

void C3DParticleRender::load(C3DElementNode* properties)
{
	//const char* blendingString = properties->getElement("blending");
   // TextureBlending textureBlending = getTextureBlendingFromString(blendingString);
    _nFrameCol = properties->getElement("width",(int*)0);
    _nFrameRow = properties->getElement("height",(int*)0);
    _spriteAnimated = properties->getElement("animated",(bool*)0);
    _spriteLooped = properties->getElement("looped",(bool*)0);
    _nFrameCount = properties->getElement("frameCount",(int*)0);
    _spriteFrameRandomOffset = properties->getElement("frameRandomOffset",(int*)0);
    _spriteFrameDurationSecs = properties->getElement("frameDuration",(float*)0);

	const char* vs = properties->getElement("vertexShader");
	const char* ps = properties->getElement("fragmentShader");
	const char* tex = properties->getElement("texture");
	
	if (vs)
		_particleVs = vs;
	
	if (ps)
		_particleFs = ps;

	if (tex)
		_partilceTexture = tex;

	const char* szSrcBlend = properties->getElement("srcBlend");
	
	if (szSrcBlend)
		_srcBlend = parseBlend(szSrcBlend);

	const char* szDstBlend = properties->getElement("dstBlend");
	if (szDstBlend)
		_dstBlend = parseBlend(szDstBlend);
    
    init(_system->_particleCountMax);

	if (_nFrameCol == 0)
		_nFrameCol = 1;
	if (_nFrameRow == 0)
		_nFrameRow = 1;
	if (_nFrameCount == 0)
		_nFrameCount = 1;
	initFrameCoord();
}

void C3DParticleRender::save(C3DElementNode* properties)
{
	properties->setElement("width", &_nFrameCol);
	properties->setElement("height", &_nFrameRow);
	properties->setElement("animated", &_spriteAnimated);
	properties->setElement("looped", &_spriteLooped);
	properties->setElement("frameCount", &_nFrameCount);
	properties->setElement("frameRandomOffset", &_spriteFrameRandomOffset);
	properties->setElement("frameDuration", &_spriteFrameDurationSecs);

	char* sz = const_cast<char*>(_particleVs.c_str());
	properties->setElement("vertexShader", &sz);
	sz = const_cast<char*>(_particleFs.c_str());
	properties->setElement("fragmentShader", &sz);
	sz = const_cast<char*>(_partilceTexture.c_str());
	properties->setElement("texture", &sz);
	
	const char* szSrcBlend = blendToString(_srcBlend);
	properties->setElement("srcBlend", &szSrcBlend);
	const char* szDstBlend = blendToString(_dstBlend);
	properties->setElement("dstBlend", &szDstBlend);
}

void C3DParticleRender::reloadMaterial()
{
	if (_model == NULL)
		return;

	const char* define = NULL;
	C3DMaterial* material = NULL;
	if (!_partilceTexture.empty())
	{
		C3DTexture* texture = C3DTexture::create(_partilceTexture.c_str());
		C3DSampler* sampler = new C3DSampler(texture);
		sampler->setFilterMode(Texture_Filter_LINEAR, Texture_Filter_LINEAR);
		sampler->setWrapMode(Texture_Wrap_CLAMP, Texture_Wrap_CLAMP);

		material = C3DMaterial::create(_particleVs.c_str(), _particleFs.c_str(), "USE_TEXTURE");
		material->getTechnique(0u)->getPass(0u)->getParameter("u_texture")->setValue(sampler);
		sampler->release();
	}
	else
	{
		material = C3DMaterial::create(_particleVs.c_str(), _particleFs.c_str());
	}
	
	material->getStateBlock()->setDepthTest(true);
	material->getStateBlock()->setDepthWrite(false);
	material->getStateBlock()->setBlend(true);
	
	_model->setMaterial(material);

	setParticleSrcBlend(_srcBlend);
	setParticleDstBlend(_dstBlend);
}

void C3DParticleRender::setParticleSrcBlend(C3DStateBlock::Blend blend) 
{ 
	_srcBlend = blend; 
	_model->getMaterial()->getStateBlock()->setBlendSrc(blend);
}

void C3DParticleRender::setParticleDstBlend(C3DStateBlock::Blend blend) 
{ 
	_dstBlend = blend; 
	_model->getMaterial()->getStateBlock()->setBlendDst(blend);
}
    
C3DParticleRender* C3DParticleRender::create(C3DParticleSystem* system, unsigned int capacity)
{   
    C3DParticleRender* render = new C3DParticleRender(system);
    render->init(capacity);
    //render->autorelease();
    return render;
}
    
bool C3DParticleRender::init(unsigned int capacity)
{
    CC_SAFE_DELETE(_model);    
    C3DVertexElement elements[] =
    {
        C3DVertexElement(Vertex_Usage_POSITION, 3),
        C3DVertexElement(Vertex_Usage_COLOR, 4),
        C3DVertexElement(Vertex_Usage_TEXCOORD0, 2)
    };
    C3DVertexFormat vertexformat = C3DVertexFormat(elements, 3);
    C3DBatchMesh* mesh = new C3DBatchMesh(&vertexformat, PrimitiveType_TRIANGLES, true, capacity);
    //C3DBatchMesh* mesh = new C3DBatchMesh(&vertexformat, PrimitiveType_TRIANGLE_STRIP, true, capacity);

    _model = new C3DBatchModel(_system);
    _model->setMesh(mesh);   
    reloadMaterial();
	_nCapacity = 0;
	_nParticle = 0;
		
    //...
	if (_system)
    {
        _model->getMaterial()->setNodeAutoBinding(_system);

        unsigned int techniqueCount = _model->getMaterial()->getTechniqueCount();
        for (unsigned int i = 0; i < techniqueCount; ++i)
        {
            C3DTechnique* technique = _model->getMaterial()->getTechnique(i);
            
            technique->setNodeAutoBinding(_system);

            unsigned int passCount = technique->getPassCount();
            for (unsigned int j = 0; j < passCount; ++j)
            {
                C3DPass* pass = technique->getPass(j);

                pass->setNodeAutoBinding(_system);
            }
        }
    }
	//..
	
    reSizeCapacity(capacity);

    return true;
}

void C3DParticleRender::prepareDraw()
{
    if(_model == NULL)
        return;
    
    _model->begin();
}

void C3DParticleRender::draw()
{
	if (!_isVisible || !_model)
		return;

	C3DParticle**& _particles = _system->_particles;
	int& _validParticleCount = _system->_validParticleCount;
    
    //CCLOG("%d", _validParticleCount);
    
    const C3DMatrix& cameraWorldMatrix = _system->getScene()->getActiveCamera()->getWorldMatrix();
    static C3DVector3 right;
    cameraWorldMatrix.getRightVector(&right);
    static C3DVector3 up;
    cameraWorldMatrix.getUpVector(&up);
    
    static C3DVector3 rotateAxis;
    //C3DVector3::cross(right, up, &rotateAxis);
    cameraWorldMatrix.getForwardVector(&rotateAxis);
    static C3DMatrix rotation;
    
    static C3DVector3 right2, up2;
    
    static VertexColorCoord1 vertex[4];
    static unsigned short index[6] = {0, 1, 3, 0, 3, 2};
   
    for (int i = 0; i < _validParticleCount; i++) {

        
        C3DVector3& position = _particles[i]->_position;
        float size = _particles[i]->_size;
        float angle = _particles[i]->_angle;
        
        
        right2 = right;
        up2 = up;
        
        if (angle > 1e-3f || angle < -1e-3f)
        {
            C3DMatrix::createRotation(rotateAxis, angle, &rotation, true);
            rotation.transformVector(&right2);
            rotation.transformVector(&up2);
        }
        
        C3DVector3 halfsizeright(0.5f * size * right2);
        C3DVector3 halfsizeup(0.5f * size * up2);
        vertex[0].position = position - halfsizeright - halfsizeup;
        vertex[1].position = position + halfsizeright - halfsizeup;
        vertex[2].position = position - halfsizeright + halfsizeup; 
        vertex[3].position = position + halfsizeright + halfsizeup; 
        
        int coordIdx = _particles[i]->_frame * 4;
        

        vertex[0].u = _frameCoord[coordIdx].x, vertex[0].v = _frameCoord[coordIdx].y;
        vertex[1].u = _frameCoord[coordIdx + 1].x, vertex[1].v = _frameCoord[coordIdx + 1].y;
        vertex[2].u = _frameCoord[coordIdx + 2].x, vertex[2].v = _frameCoord[coordIdx + 2].y;
        vertex[3].u = _frameCoord[coordIdx + 3].x, vertex[3].v = _frameCoord[coordIdx + 3].y;
        vertex[0].color = vertex[1].color = vertex[2].color = vertex[3].color = _particles[i]->_color;
        //add to buffer
        _model->_mesh->add(vertex, 4, index, 6);
        
        _nParticle++;
    }
}
    
void C3DParticleRender::reSizeCapacity(int nCapacity)
{
   
    CC_ASSERT(nCapacity > 0);
    if (_nCapacity == nCapacity)
        return;
    
    // one particle two triangles
    _model->_mesh->setCapacity(nCapacity + nCapacity);
    _nCapacity = nCapacity;
    
    _model->_mesh->setIndexCapacity(nCapacity * 6);
    _model->setMaterial(_model->_material);
}
   
void C3DParticleRender::flush()
{
    // Finish and draw the batch
    if (!_isVisible || _nParticle == 0  || _model == NULL)
        return;
    
    _model->draw();
    
    _model->end();
    
    _nParticle = 0;
}
    
C3DParticleRender* C3DParticleRender::clone(C3DParticleSystem* system) const
{
	C3DParticleRender* render = NULL;

	if (_model)
	{
		//C3DMaterial* material = _model->getMaterial()->clone();
		render = C3DParticleRender::create(system, _nCapacity);
	}
	else
	{
		render = new C3DParticleRender(system);
		render->_model = NULL;
		render->_nCapacity = 0;
	}

	render->setFrameCountRow(_nFrameRow);
	render->setFrameCountCol(_nFrameCol);
	render->_spriteAnimated = _spriteAnimated;
	render->_spriteLooped = _spriteLooped;
	render->_spriteFrameDurationSecs = _spriteFrameDurationSecs;

	render->_spriteFrameRandomOffset = _spriteFrameRandomOffset;

	render->_isVisible = _isVisible;

	render->_particleFs = _particleFs;
	render->_particleVs = _particleVs;
	render->_partilceTexture = _partilceTexture;
	render->_srcBlend = _srcBlend;
	render->_dstBlend = _dstBlend;
	render->reloadMaterial();

    return render;
}

void C3DParticleRender::initFrameCoord()
{
	SAFE_DELETE_ARRAY(_frameCoord);
	if (_nFrameCount)
	{
		float recipRow = 1.0f / _nFrameRow;
		float recipCol = 1.0f / _nFrameCol;
		_frameCoord = new C3DVector2[_nFrameCount * 4];
		for (int i = 0; i < _nFrameRow; i++)
		{
			for (int j = 0; j < _nFrameCol; j++)
			{
				int index = (i * _nFrameCol + j) * 4;
				_frameCoord[index].x = (j) * recipCol;
				_frameCoord[index].y = (i + 1) * recipRow;

				_frameCoord[index + 1].x = (j + 1) * recipCol;
				_frameCoord[index + 1].y = (i + 1) * recipRow;

				_frameCoord[index + 2].x = (j) * recipCol;
				_frameCoord[index + 2].y = (i) * recipRow;

				_frameCoord[index + 3].x = (j + 1) * recipCol;
				_frameCoord[index + 3].y = (i) * recipRow;

			}
		}
	}
}

void C3DParticleRender::setFrameCountRow(int nRow)
{
	if (_model && _nFrameRow != nRow)
	{
		_nFrameRow = nRow;
		_nFrameCount = _nFrameRow * _nFrameCol;
		initFrameCoord();
	}
	
}

void C3DParticleRender::setFrameCountCol(int nCol)
{
	if (_model && _nFrameCol != nCol)
	{
		_nFrameCol = nCol;
		_nFrameCount = _nFrameRow * _nFrameCol;
		initFrameCoord();
	}
	
}

}
