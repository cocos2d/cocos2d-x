#ifndef COLOR_PSA_H_
#define COLOR_PSA_H_

#include "C3DVector4.h"

#include "C3DParticleSystemCommon.h"

namespace cocos3d
{


class C3DElementNode;
class C3DParticleSystem;

/**
Defines a color at special time
*/
class C3DTint
{
public:
	C3DTint(float time,const C3DVector4& color)
	{
		_time = time;
		_color = color;
	}
	float _time;
	C3DVector4 _color;
};

/**
Defines a particle action that the particle color varying over time 
*/
class C3DTintPSA : public C3DBaseParticleAction
{
public:
	
	/**
     * Constructor & Destructor
     */
	C3DTintPSA(C3DParticleSystem* system);
	virtual ~C3DTintPSA();
	
	/**
     * load & save Tint particle action
     */
	virtual	void load(C3DElementNode* properties);
	virtual void save(C3DElementNode* properties);

	/**
     * change particle color over time
     */
	virtual void action(long elapsedTime);

	/**
     * add tint, change to color at specific time
     */
	void addTint( float time, const C3DVector4 &color );

	/**
     * clear tint
     */
	void clearAllTints( void );

	
	/**
     * get & set period of tint
     */
	void setPeriod(float fperiod) { _period = fperiod; }
	float getPeriod() const { return _period; }

	/**
     * get tint vector
     */
	const std::vector<C3DTint*>& getTints() const { return _tints; }

	/**
     * remove tint by index
     */
	void removeTint(int index);
    
	/**
     * clone method
     */
    virtual C3DBaseParticleAction* clone(C3DParticleSystem* system) const;

protected:
	/**
     * query index for specific time
     */
	int determineIndex(float time) const;

private:
	std::vector<C3DTint*> _tints;
	float _period;


};

}

#endif
