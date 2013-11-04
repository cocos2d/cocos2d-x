#include "Base.h"
#include "C3DParticleSystem.h"

#include "C3DNode.h"

#include "C3DQuaternion.h"
#include "C3DElementNode.h"
#include "C3DLayer.h"
#include "C3DParticleEmitter.h"
#include "C3DParticleSystemCommon.h"
#include "C3DParticleRender.h"
#include "C3DForcePSA.h"
#include "C3DTintPSA.h"
#include "C3DTransformPSA.h"
#include "C3DRenderChannel.h"
#include "C3DRenderSystem.h"
#include "C3DCamera.h"

#define PARTICLE_COUNT_MAX                       100
#define PARTICLE_EMISSION_RATE                   10
#define PARTICLE_EMISSION_RATE_TIME_INTERVAL     1000.0f / (float)PARTICLE_EMISSION_RATE

namespace cocos3d
{

C3DParticleSystem::C3DParticleSystem(const char* id):
         C3DNode(id),
		 _particleCountMax(1000), _validParticleCount(0)
{
	
	_emitter = new C3DParticleEmitter(this);
    _render = new C3DParticleRender(this);    
	
	_particles = NULL;
	_p = NULL; 
	_started = false;
	_numTintAction = 0;

	_state = STOP;
	_timeLast = 0;
	_timeStart = 0;
	StateChanged = NULL;
}

C3DParticleSystem::~C3DParticleSystem()
{
	for( std::vector<C3DBaseParticleAction*>::iterator iter=_actions.begin(); iter!=_actions.end(); ++iter )
	{
		SAFE_DELETE(*iter);
	}
	_actions.clear();

	SAFE_DELETE(_emitter);
	SAFE_DELETE(_render);
	
	SAFE_DELETE_ARRAY(_p);
	SAFE_DELETE_ARRAY(_particles);
    
}

C3DNode::Type C3DParticleSystem::getType() const
{
	return C3DNode::NodeType_ParticleSystem;
}

C3DParticleSystem* C3DParticleSystem::create(const char* id)
{  

	C3DParticleSystem* pRet = new C3DParticleSystem(id);

    pRet->autorelease();
    return pRet;

}

void C3DParticleSystem::save(C3DElementNode* &node)
{
	//C3DElementNode* node = C3DElementNode::createEmptyNode("particle system","Particle");
	node->setElement("particleCountMax", &_particleCountMax);
	node->setElement("timeLast", &_timeLast);
	node->setElement("timeStart", &_timeStart);

	C3DElementNode* render = C3DElementNode::createEmptyNode("particle render", "Render");
	_render->save(render);
	node->addChildNode(render);

	C3DElementNode* emiterNode = C3DElementNode::createEmptyNode("emitter", "Emitter");
	_emitter->save(emiterNode);
	node->addChildNode(emiterNode);

	C3DElementNode* actions = C3DElementNode::createEmptyNode("action", "Actions");
	node->addChildNode(actions);
	for (size_t i = 0; i < _actions.size(); i++)
	{
		C3DElementNode* action = NULL;
		if (dynamic_cast<C3DTransformPSA*>(_actions[i]))
		{
			action = C3DElementNode::createEmptyNode("TransformPSA", "TransformPSA");
		}
		else if (dynamic_cast<C3DForcePSA*>(_actions[i]))
		{
			action = C3DElementNode::createEmptyNode("ForcePSA", "ForcePSA");
		}
		else if (dynamic_cast<C3DTintPSA*>(_actions[i]))
		{
			action = C3DElementNode::createEmptyNode("TintPSA", "TintPSA");
		}
		_actions[i]->save(action);
		actions->addChildNode(action);
	}
}

bool C3DParticleSystem::save(const char* szFile)
{
	C3DElementNode* parent = C3DElementNode::createEmptyNode("", "");

	for (size_t k = 0; k < _children.size(); k++)
	{
		if (_children[k]->getType() == C3DNode::NodeType_ParticleSystem)
		{
			C3DParticleSystem* particle = (C3DParticleSystem*)_children[k];
			C3DElementNode* node = C3DElementNode::createEmptyNode("particle system","Particle");
			particle->save(node);
			parent->addChildNode(node);
		}
	}
	
	bool bRet = parent->writeToFile(szFile);
	CC_SAFE_DELETE(parent);
	return bRet;
}

bool C3DParticleSystem::load(const char* fileName)
{
    assert(fileName);

    C3DElementNode* properties = C3DElementNode::create(fileName);
    if (!properties)
    {
        LOG_ERROR_VARG("Error loading ParticleEmitter: Could not load file: %s", fileName);
        return false;
    }

	char strid[128];
	bool bRet = true;
	for (int i = 0; i < properties->getChildCount(); i++)
	{
		C3DElementNode* childprop = properties->getChild(i);
		if (childprop->getNodeType() > 0)
		{
			sprintf(strid, "child_%d", i);
			C3DParticleSystem* particle = C3DParticleSystem::create(strid);

			if(particle->load(childprop))
			{
				addChild(particle);
			}
			else
			{
				CC_ASSERT(0 && "load particle failed");
				bRet = false;
			}
		}
	}
    //bool bRet = load((strlen(properties->getNodeType()) > 0) ? properties : properties->getNextChild());
    SAFE_DELETE(properties);

	_state = STOP;
	start();

    return bRet;
}

bool C3DParticleSystem::load(C3DElementNode* psNode)
{
	_numTintAction = 0;
    if (!psNode || strcmp(psNode->getNodeType(), "Particle") != 0)
    {
        LOG_ERROR("Error loading ParticleEmitter: No 'Particle' namespace found");
        return false;
    }
	else
	{
		_particleCountMax = (int)psNode->getElement("particleCountMax",(int*)0);
		if (_particleCountMax == 0)
		{
			// Set sensible default.
			_particleCountMax = PARTICLE_COUNT_MAX;

		}

		_timeLast = (long)psNode->getElement("timeLast", (long*)0);
		_timeStart = (long)psNode->getElement("timeStart", (long*)0);

		_p = new C3DParticle[_particleCountMax];
		_particles = new C3DParticle*[_particleCountMax];		
		for(int i=0; i<_particleCountMax; ++i)
		{
			_particles[i] = _p+i;
		}
		_validParticleCount = 0;

	}

    C3DElementNode* prNode = psNode->getNextChild();
    if (!prNode || strcmp(prNode->getNodeType(), "Render") != 0 )
    {
        LOG_ERROR("Error loading ParticleEmitter: No 'sprite' namespace found");
        return false;
    }
	else
	{		
		_render->load(prNode);
	}


	C3DElementNode* emiterNode = psNode->getNextChild();
    if (!emiterNode || strcmp(emiterNode->getNodeType(), "Emitter") != 0)
    {
        LOG_ERROR("Error loading ParticleEmitter: No 'sprite' namespace found");
        return false;
    }
	else
	{		
		_emitter->load(emiterNode);
	}
		 

	C3DElementNode* actionNodes = psNode->getNextChild();
    if (!actionNodes || strcmp(actionNodes->getNodeType(), "Actions") != 0)
    {
        LOG_ERROR("Error loading ParticleEmitter: No 'sprite' namespace found");
        return false;
    }
	else
	{		
		actionNodes->rewind();
		C3DElementNode* actionNode = NULL;
		C3DBaseParticleAction* action = NULL;
		while ((actionNode = actionNodes->getNextChild()))
		{
			if (strcmp(actionNode->getNodeType(), "TransformPSA") == 0)
			{		
				action = new C3DTransformPSA(this);				
			}
			else if (strcmp(actionNode->getNodeType(), "ForcePSA") == 0)
			{		
				action = new C3DForcePSA(this);					
			}
			else if (strcmp(actionNode->getNodeType(), "TintPSA") == 0)
			{
				action = new C3DTintPSA(this);
				_numTintAction++;
			}

			if(action)
			{
				action->load(actionNode);	
				_actions.push_back(action);
			}
		}		

	}	
	return true;
}


void C3DParticleSystem::start()
{
    _started = true;
    //_timeLast = C3DLayer::getGameTime();

	if (_state != RUNNING)
	{
		_state = RUNNING;
		_timeRunning = 0L;
	}
	for (size_t i = 0; i < _children.size(); i++)
	{
		if (_children[i]->getType() == C3DNode::NodeType_ParticleSystem)
			((C3DParticleSystem*)_children[i])->start();
	}
}

void C3DParticleSystem::pause()
{
	if (_state == RUNNING)
	{
		_state = PAUSE;
		if (StateChanged)
		{
			StateChanged(this, RUNNING, PAUSE);
		}
	}

	for (size_t i = 0; i < _children.size(); i++)
	{
		if (_children[i]->getType() == C3DNode::NodeType_ParticleSystem)
			((C3DParticleSystem*)_children[i])->pause();
	}
}

void C3DParticleSystem::resume()
{
	if (_state == PAUSE)
	{
		_state = RUNNING;
		if (StateChanged)
		{
			StateChanged(this, PAUSE, RUNNING);
		}
	}
	for (size_t i = 0; i < _children.size(); i++)
	{
		if (_children[i]->getType() == C3DNode::NodeType_ParticleSystem)
			((C3DParticleSystem*)_children[i])->resume();
	}
}

void C3DParticleSystem::stop()
{
    _started = false;
	if (_state != STOP)
	{
		ParticleState old = _state;
		_state = STOP;
		if (StateChanged)
		{
			StateChanged(this, old, _state);
		}
	}
	for (size_t i = 0; i < _children.size(); i++)
	{
		if (_children[i]->getType() == C3DNode::NodeType_ParticleSystem)
			((C3DParticleSystem*)_children[i])->stop();
	}
}

bool C3DParticleSystem::isStarted() const
{
    return _started;
}

bool C3DParticleSystem::isActive() const
{	
    return true;
}


void C3DParticleSystem::update(long elapsedTime)
{
    if (!isActive())
    {
        return;
    }
	
	if (_particles)
	{
		if(_emitter && _state == RUNNING)
		{
			if (_timeRunning >= _timeStart)
				_emitter->update(elapsedTime);
			
		}

		if (_state != PAUSE)
		{
			for(std::vector<C3DBaseParticleAction*>::iterator iter =_actions.begin(); iter!=_actions.end(); ++iter)
			{
				(*iter)->action(elapsedTime);
			}
		}	
	}

	if (_state == RUNNING)
	{
		_timeRunning += elapsedTime;
		if (_timeLast != 0L)
		{
			if (_timeRunning >= _timeLast + _timeStart)
				stop();
		}
	}

	for (size_t i = 0; i < _children.size(); i++)
	{
		if (_children[i]->getType() == C3DNode::NodeType_ParticleSystem)
		{
			((C3DParticleSystem*)_children[i])->update(elapsedTime);
		}
	}
}

void C3DParticleSystem::draw()
{
    if (!isActive())
    {
        return;
    }
	bool bStat = C3DStat::getInstance()->isStatEnable();
	if (bStat)
	{
		C3DStat::getInstance()->incTriangleTotal(_validParticleCount * 2);
	}
	static C3DAABB box;
	static C3DVector3 pos;
	pos = getTranslationWorld();
	box._min = pos + C3DVector3(-1.0f, -1.0f, -1.0f);
	box._max = pos + C3DVector3(1.0f, 1.0f, 1.0f);
	if (!_scene->getActiveCamera()->isVisible(box))
		return;

	if(_particles && _render && _render->isVisible())
    {
		if (bStat)
		{
			C3DStat::getInstance()->incTriangleDraw(_validParticleCount * 2);
			C3DStat::getInstance()->incDrawCall(1);
		}

        ParticleRenderChannel* channel = (ParticleRenderChannel*)(C3DRenderSystem::getInstance()->getRenderChannelManager()->getRenderChannel("particlechannel"));
        
        float z = (getViewMatrix() * pos).z;
        channel->addItem(z, _render);
        
        //_render->prepareDraw();
		//_render->draw();
        //_render->flush();
    }
   
	for (size_t i = 0; i < _children.size(); i++)
	{
		if (_children[i]->getType() == C3DNode::NodeType_ParticleSystem)
		{
			((C3DParticleSystem*)_children[i])->draw();
		}
	}
}

void C3DParticleSystem::addAction(C3DBaseParticleAction* action)
{
	_actions.push_back(action);
	if (dynamic_cast<C3DTintPSA*>(action))
		_numTintAction++;
}

void C3DParticleSystem::removeAction(C3DBaseParticleAction* action)
{
	for (size_t i = 0; i < _actions.size(); i++)
	{
		if (_actions[i] == action)
		{
			if (dynamic_cast<C3DTintPSA*>(action))
				_numTintAction--;
			delete action;
			_actions.erase(_actions.begin() + i);
			break;
		}
	}
}
    
C3DParticleSystem* C3DParticleSystem::clone(CloneContext& context) const
{
	
   
    C3DParticleSystem* particle = new C3DParticleSystem(NULL);
    
    particle->copyFrom(this, context);	
		

	particle->autorelease();
    return particle;
}
    
void C3DParticleSystem::copyFrom(const C3DTransform* other, CloneContext& context)
{
    C3DNode::copyFrom(other, context);

	C3DParticleSystem* particle = (C3DParticleSystem*)other;

	std::string newid;
	if(particle->_parent->getType() == C3DNode::NodeType_ParticleSystem)
	{
		_id = particle->_id;
	}
	else
	{
		_id = particle->_id + context.idSuffix;
	}   

    
    _particleCountMax = particle->_particleCountMax;
    _validParticleCount = particle->_validParticleCount;
    
    _p = new C3DParticle[_particleCountMax];
    _particles = new C3DParticle*[_particleCountMax];
    for(int i=0; i<_particleCountMax; ++i)
    {
        _particles[i] = _p+i;
    }
    _validParticleCount = 0;
    
    _numTintAction = particle->_numTintAction;
    _started = particle->_started;
    
    _timeLast = particle->_timeLast;
    _timeRunning = particle->_timeRunning;
    
    SAFE_DELETE(_emitter);
    SAFE_DELETE(_render);
    
    _emitter = particle->_emitter->clone(this);
    _render = particle->_render->clone(this);
    
	for (size_t i = 0; i < particle->_actions.size(); i++) {
        _actions.push_back(particle->_actions[i]->clone(this));
    }
    
	_timeLast = particle->_timeLast; // particle system last time
	_timeRunning = particle->_timeRunning; // particle system running time
	_timeStart = particle->_timeStart; // particle system start time
	_state = particle->_state;
}

void C3DParticleSystem::setScale(float scale)
{
	//C3DTransform::setScale(scale);

	float minSize = _emitter->getSizeStartMin()*scale;
	float maxSize = _emitter->getSizeStartMax()*scale;

	_emitter->setSizeStartMin(minSize);
	_emitter->setSizeStartMax(maxSize);

	_emitter->setPosition(_emitter->getPosition() * scale);
	_emitter->setPositionVariance(_emitter->getPositionVariance() * scale);
	_emitter->setVelocity(_emitter->getVelocity() * scale);
	_emitter->setVelocityVariance(_emitter->getVelocityVariance() * scale);
	
	for (size_t i = 0; i < _children.size(); i++)
	{
		if (_children[i]->getType() == C3DNode::NodeType_ParticleSystem)
			((C3DParticleSystem*)_children[i])->setScale(scale);
	}
}

void C3DParticleSystem::setStateChangeCallBack(void (*StateChanged)(const C3DParticleSystem* particle, ParticleState oldState, ParticleState newState))
{
	this->StateChanged = StateChanged;
}

void C3DParticleSystem::setParticleCountMax(int particleCountMax)
{
	if (_particleCountMax != particleCountMax)
	{
		_particleCountMax = particleCountMax;
		SAFE_DELETE_ARRAY(_p);
		SAFE_DELETE_ARRAY(_particles);

		_p = new C3DParticle[_particleCountMax];
		_particles = new C3DParticle*[_particleCountMax];		
		for(int i=0; i<_particleCountMax; ++i)
		{
			_particles[i] = _p+i;
		}
		_validParticleCount = 0;

		_render->reSizeCapacity(_particleCountMax);
	}
	
}

}
