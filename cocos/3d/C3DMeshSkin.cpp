#include "Base.h"
#include "C3DMeshSkin.h"
#include "C3DBone.h"
#include "BonePart.h"
#include "C3DModel.h"

// The number of rows in each palette matrix.
#define PALETTE_ROWS 3

namespace cocos3d
{

C3DMeshSkin::C3DMeshSkin()
    : _rootJoint(NULL), _matrixPalette(NULL), _model(NULL), _partCount(0), _parts(NULL), _curPartIndex(0)
{
}

C3DMeshSkin::~C3DMeshSkin()
{
	for (unsigned int i = 0; i < _partCount; ++i)
    {
		SAFE_DELETE(_parts[i]);        
    }
	SAFE_DELETE_ARRAY(_parts);

    clearJoints();

    SAFE_DELETE_ARRAY(_matrixPalette);
}

const C3DMatrix& C3DMeshSkin::getBindShape()
{
    return _bindShape;
}

void C3DMeshSkin::setBindShape(const float* matrix)
{
    _bindShape.set(matrix);
}

unsigned int C3DMeshSkin::getJointCount()
{
    return _joints.size();
}

C3DBone* C3DMeshSkin::getJoint(unsigned int index)
{
    assert(index < _joints.size());
    return _joints[index];
}

C3DBone* C3DMeshSkin::getJoint(const char* id)
{
    assert(id);

    for (unsigned int i = 0, count = _joints.size(); i < count; ++i)
    {
        C3DBone* j = _joints[i];
        if (j && j->getId() != NULL && strcmp(j->getId(), id) == 0)
        {
            return j;
        }
    }

    return NULL;
}

void C3DMeshSkin::setJointCount(unsigned int jointCount)
{
    // Erase the joints vector and release all joints
    clearJoints();

    // Resize the joints vector and initialize to NULL
    _joints.resize(jointCount);
    for (unsigned int i = 0; i < jointCount; i++)
    {
        _joints[i] = NULL;
    }

    // Rebuild the matrix palette. Each matrix is 3 rows of C3DVector4.
    SAFE_DELETE_ARRAY(_matrixPalette);

    if (jointCount > 0)
    {
        _matrixPalette = new C3DVector4[jointCount * PALETTE_ROWS];
        for (unsigned int i = 0; i < jointCount * PALETTE_ROWS; i+=PALETTE_ROWS)
        {
            _matrixPalette[i+0].set(1.0f, 0.0f, 0.0f, 0.0f);
            _matrixPalette[i+1].set(0.0f, 1.0f, 0.0f, 0.0f);
            _matrixPalette[i+2].set(0.0f, 0.0f, 1.0f, 0.0f);
        }
    }
}

void C3DMeshSkin::setJoint(C3DBone* joint, unsigned int index)
{
    assert(index < _joints.size());

    if (_joints[index])
    {
        _joints[index]->_skinCount--;
        SAFE_RELEASE(_joints[index]);
    }

    _joints[index] = joint;

    if (joint)
    {
        joint->retain();
        joint->_skinCount++;
    }
}

//C3DVector4* C3DMeshSkin::getMatrixPalette() const
//{
//    unsigned int count = _joints.size();
//    for (unsigned int i = 0; i < count; i++)
//    {
//        _joints[i]->updateJointMatrix(getBindShape(), &_matrixPalette[i * PALETTE_ROWS]);
//    }
//    return _matrixPalette;
//}

void C3DMeshSkin::setBonePartIndex(unsigned int index)
{
	_curPartIndex = index;
}

unsigned int C3DMeshSkin::getBonePartIndex() 
{
	return _curPartIndex;
}

C3DVector4* C3DMeshSkin::getMatrixPalette(unsigned int index)
{

	BonePart* part = _parts[index];
	std::vector<unsigned int>& indices = part->_indices;
	unsigned int count = indices.size();
	for (unsigned int i = 0; i < count; i++)
	{
		unsigned int boneIndex = indices[i];

	    _joints[boneIndex]->updateJointMatrix(getBindShape(), &_matrixPalette[i * PALETTE_ROWS]);
	}
	return _matrixPalette;


}

unsigned int C3DMeshSkin::getMatrixPaletteSize(unsigned int index)
{
	BonePart* part = _parts[index];
	std::vector<unsigned int>& indices = part->_indices;
	unsigned int count = indices.size();

    return count * PALETTE_ROWS;
}

C3DModel* C3DMeshSkin::getModel() const
{
    return _model;
}

C3DBone* C3DMeshSkin::getRootJoint() const
{
    return _rootJoint;
}

void C3DMeshSkin::setRootJoint(C3DBone* joint)
{
	
    if (_rootJoint && _rootJoint->getParent() && _rootJoint->getParent()->getType() == C3DNode::NodeType_Bone)
    {
		_rootJoint->getParent()->removeListener(this); 
		_rootJoint->getParent()->release();		
    }


    _rootJoint = joint;

    // If the root joint has a parent node, register for its transformChanged event
    if (_rootJoint && _rootJoint->getParent() && _rootJoint->getParent()->getType() == C3DNode::NodeType_Bone)
    {
        _rootJoint->getParent()->addListener(this, 1);
		_rootJoint->getParent()->retain();		
    }
	
}

void C3DMeshSkin::transformChanged(C3DTransform* transform, long cookie)
{
    switch (cookie)
    {
    case 1:
        // The direct parent of our joint hierarchy has changed.
        // Dirty the bounding volume for our model's node. This special
        // case allows us to have much tighter bounding volumes for
        // skinned meshes by only considering local skin/joint transformations
        // during bounding volume computation instead of fully resolved
        // joint transformations.
        if (_model && _model->getNode())
        {
            _model->getNode()->setBoundsDirty();
        }
        break;
    }
}

int C3DMeshSkin::getJointIndex(C3DBone* joint)
{
    for (unsigned int i = 0, count = _joints.size(); i < count; ++i)
    {
        if (_joints[i] == joint)
        {
            return (int)i;
        }
    }

    return -1;
}

void C3DMeshSkin::clearJoints()
{
    setRootJoint(NULL);

    for (unsigned int i = 0, count = _joints.size(); i < count; ++i)
    {
        SAFE_RELEASE(_joints[i]);
    }
    _joints.clear();
}

BonePart* C3DMeshSkin::addPart(unsigned int batchID, unsigned int offsetVertexIndex, unsigned int numVertexIndex)
{

    BonePart* part = BonePart::create(this, batchID, offsetVertexIndex, numVertexIndex);
    if (part)
    {
        // Increase size of part array and copy old subets into it.
        BonePart** oldParts = _parts;
        _parts = new BonePart*[_partCount + 1];
        for (unsigned int i = 0; i < _partCount; ++i)
        {
            _parts[i] = oldParts[i];
        }

        // Add new part to array.
        _parts[_partCount++] = part;

        // Delete old part array.
        SAFE_DELETE_ARRAY(oldParts);
    }

    return part;
}
    
void C3DMeshSkin::copyFrom(C3DMeshSkin* skin, C3DNode::CloneContext& context)
{
	
    _bindShape = skin->_bindShape;
    
    std::map<const C3DNode*, C3DNode*>::iterator it = context.cloneMap.find(skin->_rootJoint);
    C3DBone* rootbone = NULL;
    if (it == context.cloneMap.end())
        rootbone = (C3DBone*)skin->_rootJoint->clone(context);
    else
        rootbone = (C3DBone*)it->second;
    
    setJointCount(skin->getJointCount());
    setRootJoint(rootbone);
    
    size_t i;
    for (i = 0; i < skin->_joints.size(); i++) 
	{
        std::string strid = skin->_joints[i]->getId();
      //  strid += context.idSuffix;
        
       //C3DBone* bone = (strid == rootbone->getId() ? rootbone : (C3DBone*)rootbone->findNode(strid.c_str()));
		//C3DBone* bone = (C3DBone*)context.cloneMap[skin->_joints[i]];

		///....		
			std::map<const C3DNode*, C3DNode*>::iterator itr = context.cloneMap.find(skin->_joints[i]);

            C3DBone* bone = NULL;
			if (itr != context.cloneMap.end())
			{
                bone = static_cast<C3DBone*>(itr->second);
			}
			else
			{
				C3DBone* newNode = static_cast<C3DBone*>(skin->_joints[i]->clone(context));
				if (newNode)
				{
					context.cloneMap[skin->_joints[i]] = newNode;
                    bone = newNode;
				}
			}
		//.....

        setJoint(bone, i);
        //bone->release();
    }
    
    
    for (i = 0; i < skin->_partCount; i++) {
        addPart(skin->_parts[i]->_batchID, skin->_parts[i]->_offsetVertexIndex, skin->_parts[i]->_numVertexIndex);
        _parts[i]->setIndexData(&skin->_parts[i]->_indices[0], skin->_parts[i]->_indices.size());
    }
    setBonePartIndex(skin->getBonePartIndex());
    
}

}
