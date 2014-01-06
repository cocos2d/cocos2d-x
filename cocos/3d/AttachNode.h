#ifndef ATTACHNODE_H_
#define ATTACHNODE_H_

#include <vector>
#include "CCPlatformMacros.h"

NS_CC_BEGIN

class C3DNode;
class C3DSprite;

/**
*Defines a logic attach point.one 
*/
class AttachNode
{
public:
    
    friend class C3DRenderNode;
	   
    AttachNode( C3DNode* pNode, C3DNode* pOwner );

    ~AttachNode(); 	

	C3DNode* node(){ return _node;}
	
	void attach( C3DNode* pAttachment );

    bool detach( C3DNode* pAttachment );

	void update(long elapsedTime);

	void draw();

private:

	C3DNode* _owner;
	C3DNode* _node;
	std::vector<C3DNode*> _attachments;		
};

NS_CC_END

#endif // ATTACHNODE_H_
