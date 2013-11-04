#include "Base.h"
#include "C3DParticleSystemCommon.h"

#include "C3DParticleSystem.h"

#include "cocos2d.h"


namespace cocos3d
{

C3DBaseParticleAction::C3DBaseParticleAction(C3DParticleSystem* system)
{
	_system = system;
	_name = NULL;
};

C3DBaseParticleAction::~C3DBaseParticleAction()
{
	_system = NULL;
	SAFE_DELETE_ARRAY(_name);
	
};

void C3DBaseParticleAction::load(C3DElementNode* psaNode)
{
	char* name = const_cast<char*>(psaNode->getElement("name"));
	size_t size = strlen(name);
	_name = new char[size+1];
    memcpy(_name,name,size);
	_name[size] = 0;
}

void C3DBaseParticleAction::save(C3DElementNode* psaNode)
{
	psaNode->setElement("name", &_name);
}
        
void C3DBaseParticleAction::copyFrom(const C3DBaseParticleAction* other)
{
    if (other->_name)
    {
        SAFE_DELETE_ARRAY(_name);
        _name = new char[strlen(other->_name) + 1];
        strcpy(_name, other->_name);
    }
}

C3DBaseParticleAction* C3DBaseParticleAction::clone(C3DParticleSystem* system) const
{
    C3DBaseParticleAction* action = new C3DBaseParticleAction(system);
    action->copyFrom(this);
    return action;
}

}
