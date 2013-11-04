#ifndef MORPH_H_
#define MORPH_H_

#include <string>
#include <vector>
using namespace std;

namespace cocos3d
{

/**
 * Defines structure to describe vertex offset.
 */
struct VertexOffset
{
	unsigned int index;
	float x,y,z;

	VertexOffset(){};
};

/**
 * Defines structure to describe target morph.
 */
struct MorphTarget
{	
	unsigned int index;
	float weight;
	std::string name;
	std::vector<VertexOffset> offsets;

	/**
     * Constructor.
     */
	MorphTarget()
	{
		weight = 1.0f;		
	}

	/**
     * Destructor.
     */
	~MorphTarget()
	{

	}
};	

/**
 * Defines structure to describe morph.
 */
class Morph
{
public:
	/**
     * Constructor.
     */
    Morph();

	/**
     * Destructor.
     */
    ~Morph();

	/**
     * Gets target morph by specified name.
     */
	MorphTarget* getMorphTarget(std::string name);

	/**
     * Gets target morph by specified index.
     */
	MorphTarget* getMorphTarget(int index);
   
	/**
     * Adds a target morph.
     */
	void addMorphTarget(MorphTarget* target);

	/**
     * Clears current target vector list.
     */
	void clearCurTarget();	

	/**
     * Gets current target vector list.
     */
	std::vector<unsigned int>* getCurTargets();

	/**
     * Push target index to current target vector list.
     */
	bool pushTarget(unsigned int targetIndex);

	/**
     * Pop target index to current target vector list.
     */
	bool popTarget(unsigned int targetIndex);

private:
	std::string _meshName;
	std::vector<MorphTarget*>* _morphTargets;

	std::vector<unsigned int>* _curTargets;
  
};

}

#endif
