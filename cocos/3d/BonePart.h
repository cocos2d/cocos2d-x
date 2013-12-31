#ifndef BONEPART_H_
#define BONEPART_H_


namespace cocos2d
{
class C3DNode;
class C3DMeshSkin;

/**
 * Defines a structure of skin-mesh's bone.
 */
class BonePart
{
public:

    /**
     * Constructor.
     */
    BonePart(void);

    /**
     * Destructor.
     */
    virtual ~BonePart(void);

    /**
     * The method for creating BonePart.
     */
    static BonePart* create(C3DMeshSkin* meshSkin, unsigned int batchID,unsigned int offsetVertexIndex,unsigned int numVertexIndex);

    /**
     * Sets the index data.
     *
     * @param indexData Point to the indices memory.
     * @param indexCount The index count.
     */
    void setIndexData(void* indexData, unsigned int indexCount);

public:

    C3DMeshSkin *_meshSkin;
    unsigned int _batchID;
    unsigned int _offsetVertexIndex;
    unsigned int _numVertexIndex;
    std::vector<unsigned int> _indices;

};

}

#endif
