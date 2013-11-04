#include "C3DResource.h"
#include "C3DElementNode.h"
#include "C3DResourcePool.h"
#include "StringTool.h"
namespace cocos3d 
{

C3DResource::C3DResource(): _name(""),_size(0)
{
	_checkWaitTime = 0;
	_waitTime = 10000;
	_state = State_Init;
	_cloneNum = 0;
}

C3DResource::C3DResource(const std::string& name): _name(name),_size(0)
{
	_checkWaitTime = 0;
	_waitTime = 10000;
	_state = State_Init;
	_cloneNum = 0;
	
}
	

	
C3DResource::~C3DResource() 
{ 

}

size_t C3DResource::getSize(void) const
{ 
    return _size; 
}
	    
const std::string& C3DResource::getName(void) const 
{ 
    return _name; 
}	

void C3DResource::setName(std::string& name)
{
	_name = name;
}

const C3DResource::State C3DResource::getState(void) const
{
	return _state;
}

void C3DResource::setState(C3DResource::State state)
{
	_state = state;
}


bool C3DResource::load(C3DElementNode* node)
{
	return false;
}


bool C3DResource::save(C3DElementNode* node)
{
	return false;
}


void C3DResource::update(long elapsedTime)
{
	
	switch(_state)
	{
	case C3DResource::State_Init:
		{
			if(this->retainCount()>1)
			{
				_state = State_Used;
			}
		}
		break;
	
	
	}
}

void C3DResource::copyFrom(const C3DResource* other)
{
	_cloneNum = other->_cloneNum + 1;
	if(_cloneNum != 0)
		_name = other->_name + "_" + StringTool::toString(_cloneNum);
	_size = other->_size;
	_state = C3DResource::State_Init;
	_waitTime = other->_waitTime;
}

C3DResource* C3DResource::clone() const
{
	C3DResource* other = new C3DResource("");
	
	other->_name = _name;
	other->_size = _size;
	other->_state = C3DResource::State_Init;
	other->_waitTime = _waitTime;

	other->autorelease();
	return other;
}
		

}
