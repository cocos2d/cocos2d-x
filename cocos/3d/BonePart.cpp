#include "Base.h"
#include "BonePart.h"

#include "C3DMeshSkin.h"

namespace cocos2d
{


BonePart::BonePart():
          _meshSkin(nullptr),_batchID(0),_offsetVertexIndex(0),_numVertexIndex(0)
{
}

BonePart::~BonePart()
{
}


BonePart* BonePart::create(C3DMeshSkin* meshSkin, unsigned int batchID,unsigned int offsetVertexIndex,unsigned int numVertexIndex)
{


    BonePart* part = new BonePart();

    part->_meshSkin = meshSkin;
    part->_batchID = batchID;
    part->_offsetVertexIndex = offsetVertexIndex;
    part->_numVertexIndex = numVertexIndex;


    return part;
}



void BonePart::setIndexData(void* indexData, unsigned int indexCount)
{
    
    _indices.resize(indexCount);
    memcpy(&_indices[0],indexData,indexCount * sizeof(unsigned int));

}

}
