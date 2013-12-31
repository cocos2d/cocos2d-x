#include "Base.h"
#include "C3DSkeleton.h"
#include "C3DBone.h"
#include "Vertex.h"

namespace cocos2d
{

C3DSkeleton::C3DSkeleton()
{
    _rootBone = nullptr;
}


C3DSkeleton::~C3DSkeleton()
{
}

void C3DSkeleton::getChild(std::map<std::string, C3DBone*>& bones,C3DNode* node)
{
    if(node->getType() == C3DNode::NodeType_Bone)
    {
        bones[node->getId()] = static_cast<C3DBone*>(node);
    }
    

    for(std::vector<C3DNode*>::const_iterator iter=node->_children.begin(); iter!=node->_children.end(); ++iter)
    {        
        getChild(bones,*iter);            
       
    }

}

C3DBone* C3DSkeleton::getBone(const std::string& name) const
{
    std::map<std::string, C3DBone*>::const_iterator iter = _bones.find(name);
    if (iter == _bones.end())
        return nullptr;
    return iter->second;
}

void C3DSkeleton::set(C3DBone* joint)
{
    if(joint == nullptr)
        return;
    _rootBone = joint;

    getChild(_bones,_rootBone);
}

C3DAnimation* C3DSkeleton::getAnimation(const std::string& name) const
{
    return _rootBone->getAnimation(name.c_str());

}

C3DSkeleton* C3DSkeleton::clone()
{
    return nullptr;
}
    
}
