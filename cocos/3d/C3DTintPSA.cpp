#include "Base.h"
#include "C3DTintPSA.h"
#include "C3DParticleSystem.h"
#include <vector>

#include "C3DElementNode.h"

namespace cocos3d
{

C3DTintPSA::C3DTintPSA(C3DParticleSystem* system) :   
     C3DBaseParticleAction(system),_period( 1.0f )  
{
   
}

C3DTintPSA::~C3DTintPSA()
{   
	this->clearAllTints();
   
}

void C3DTintPSA::save(C3DElementNode* tintPSANode)
{
	tintPSANode->empty();

	C3DBaseParticleAction::save(tintPSANode);

	tintPSANode->setElement("period",&_period);
	
	C3DElementNode* node = C3DElementNode::createEmptyNode("Tints", "Tints");
	tintPSANode->addChildNode(node);

	for (size_t i = 0; i < _tints.size(); i++)
	{
		C3DElementNode* tint = C3DElementNode::createEmptyNode("Tint", "Tint");
		tint->setElement("time", &(_tints[i]->_time));
		tint->setElement("color", &(_tints[i]->_color));
		node->addChildNode(tint);
	}
}

void C3DTintPSA::load(C3DElementNode* tintPSANode)
{
	C3DBaseParticleAction::load(tintPSANode);
	
	_period = tintPSANode->getElement("period",&_period);

	C3DElementNode* tintNodes = tintPSANode->getNextChild();
    if (!tintNodes || strcmp(tintNodes->getNodeType(), "Tints") != 0)
    {
        LOG_ERROR("Error loading ParticleEmitter: No 'sprite' namespace found");
        return ;
    }
	else
	{		
		tintNodes->rewind();
		C3DElementNode* tintNode = NULL;
		C3DBaseParticleAction* action = NULL;
		while ((tintNode = tintNodes->getNextChild()))
		{
			if (strcmp(tintNode->getNodeType(), "Tint") == 0)
			{	
				float time = tintNode->getElement("time",(float*)0);
				C3DVector4 color;
				tintNode->getElement("color", &color);
				this->addTint(time,color);
				
			}
			
		}
	}	
    
}

void C3DTintPSA::addTint( float time, const C3DVector4 &color )
{
	size_t i;
	C3DTint* tint = new C3DTint(time,color);
	for (i = 0; i < _tints.size(); i++)
	{
		if (_tints[i]->_time > time)
			break;
	}
	
	_tints.insert(_tints.begin() + i, tint);

	if ( time > _period )
	{
		_period = time;
	}
}

/**
 *	This method removes all tint values from the particles.
 */
void C3DTintPSA::clearAllTints( void )
{
	for( std::vector<C3DTint*>::iterator iter=_tints.begin(); iter!=_tints.end(); ++iter )
	{
		SAFE_DELETE(*iter);
	}
	_tints.clear();
	_period = 0.0f;
}

void C3DTintPSA::removeTint(int index)
{
	if (index < (int)_tints.size())
	{
		SAFE_DELETE(_tints[index]);
	}
	_tints.erase(_tints.begin() + index);
}

int C3DTintPSA::determineIndex(float time) const
{
    unsigned int min = 0;
	unsigned int max = _tints.size() - 1;
    unsigned int mid = 0;

    do 
    {
		if (min == max)
			return min;

        mid = (min + max) >> 1;
		
        if (time >= _tints[mid]->_time && time <= _tints[mid + 1]->_time)
            return mid;
        else if (time < _tints[mid]->_time)
            max = mid - 1;
        else
            min = mid + 1;
    } while (min <= max);
    
    return -1;
}

void C3DTintPSA::action(long elapsedTime)
{    
	if (_tints.size() == 0)
		return;

    // Calculate the time passed since last update.
    float elapsedSecs = (float)elapsedTime / 1000.0f;
	C3DParticle**& _particles = _system->_particles;
	int& _validParticleCount = _system->_validParticleCount;
	C3DVector4 color;
    float weight = 1.0f / (float)_system->_numTintAction; 
	for (int i = 0; i < _validParticleCount; ++i)
    {
		C3DParticle*& p = _particles[i];
		int index = this->determineIndex(p->_age);

		C3DTint* from = _tints[index];
		C3DVector4 color;
		if (index >= (int)_tints.size() - 1)
		{
			color = from->_color;
		}
		else
		{
			C3DTint* to = _tints[index + 1];
			float scale = (to->_time - from->_time);
			float t = (scale == 0.0f ? 0.0f : (p->_age - from->_time) / scale);
			color = from->_color + (to->_color - from->_color) * t;
		}
		color *= weight;
		p->_color += color; 
		
    }

}
    
C3DBaseParticleAction* C3DTintPSA::clone(C3DParticleSystem* system) const
{
    C3DTintPSA* psa = new C3DTintPSA(system);
    psa->copyFrom(this);
    
    psa->_period = _period;
    for (size_t i = 0; i < _tints.size(); i++) {
        C3DTint* tint = new C3DTint(_tints[i]->_time, _tints[i]->_color);
        psa->_tints.push_back(tint);
    }
    
    return psa;
}

}