#include "Base.h"
#include "Vector3.h"
#include "C3DSprite.h"

#include "StringTool.h"
#include "C3DMaterial.h"
#include "C3DResourceLoader.h"
#include "C3DNode.h"

#include "C3DAnimation.h"
#include "C3DAnimationClip.h"
#include "C3DModel.h"
#include "C3DMesh.h"
#include "C3DAABB.h"
#include "C3DMeshSkin.h"
#include "C3DSkinModel.h"
#include "C3DBone.h"
#include "C3DSkeleton.h"

#include "C3DMaterial.h"
#include "MaterialParameter.h"

#include "C3DModelNode.h"


NS_CC_BEGIN

C3DSprite::C3DSprite(const char* id) 
:C3DRenderNode(id)
,C3DResource(id)
{
    _active = true;    

    _skeleton = nullptr;

    _animation = nullptr;

}


C3DSprite::~C3DSprite()
{    
    _animation = nullptr;
    SAFE_DELETE(_skeleton);
}

C3DSprite* C3DSprite::create(const char* id)
{
    C3DSprite* pRet = new C3DSprite(id);
    pRet->autorelease();
    return pRet;
}


bool C3DSprite::loadFromFile(const char* fileName,bool isLoadAll)
{
    _fileName = fileName;

    // Load mesh/scene from file
    C3DResourceLoader* bundle = C3DResourceLoader::create(_fileName.c_str());       
    if (bundle == nullptr)
        return false;
    if(isLoadAll==true)
    {  
        bundle->loadSuperModel(this);
        this->setDefaultMaterial(StringTool::getFilePath(fileName));

        getAABB();
    }
    else
    {
        bundle->loadSkeleton(this,"Bip01");
    }

    SAFE_RELEASE(bundle);

    return true;
}

bool C3DSprite::load(const std::string& fileName)
{
    _fileName = fileName;

    // Load mesh/scene from file
    C3DResourceLoader* bundle = C3DResourceLoader::create(_fileName.c_str());       
    if (bundle == nullptr)
        return false;

    bundle->loadSuperModel(this);
    this->setDefaultMaterial(StringTool::getFilePath(fileName));

    getAABB();

    SAFE_RELEASE(bundle);

    return true;
}

void C3DSprite::loadNode(const std::string& nodeName)
{
    // Load mesh/scene from file
    C3DResourceLoader* bundle = C3DResourceLoader::create(_fileName.c_str());   

    bundle->loadSuperModel(this,nodeName);
    SAFE_RELEASE(bundle);

}

void C3DSprite::loadNodes(std::list<std::string>* models)
{
    // Load mesh/scene from file
    C3DResourceLoader* bundle = C3DResourceLoader::create(_fileName.c_str());   

    bundle->loadSuperModel(this,models);
    SAFE_RELEASE(bundle);

    getAABB();
}

C3DAnimation* C3DSprite::createAnimation()
{
    // Load mesh/scene from file
    C3DResourceLoader* bundle = C3DResourceLoader::create(_fileName.c_str());   
    CCAssert(bundle, "Can not load bundle!");

    bundle->loadAnimation(this);

    SAFE_RELEASE(bundle);

    return _animation;
}

C3DAnimationClip* C3DSprite::addAnimationClip(const char* name,unsigned int startFrame,unsigned int endFrame,float repeatCount,float speed)
{    
    if( _animation == nullptr )
        _animation = createAnimation();

    if(_animation == nullptr)
        return nullptr;

    return _animation->addClip(name,startFrame,endFrame,repeatCount,speed);
}

bool C3DSprite::replaceAnimationClip(const char* name,unsigned int startFrame,unsigned int endFrame,float repeatCount,float speed)
{
    if(!_animation || !_skeleton)
        return false;

    _animation->replaceClip(name,startFrame,endFrame,repeatCount,speed);
    return true;
}


bool C3DSprite::loadMesh(const char* meshName)
{
    loadNode(meshName);
    return false;
}

void C3DSprite::update(long elapsedTime)
{
    if(_active == false)
        return;

    C3DRenderNode::update(elapsedTime);

    if(_animation != nullptr)
        _animation ->update(elapsedTime);
}


void C3DSprite::calculateBoundingBox_()
{
    C3DAABB box;

    box._min.set(99999.0f, 99999.0f, 99999.0f);
    box._max.set(-99999.0f, -99999.0f, -99999.0f);

    for(std::vector<C3DNode*>::const_iterator iter=_children.begin(); iter!=_children.end(); ++iter)
    {
        C3DNode* node = *iter;
        if(node->getType()!=C3DNode::NodeType_Model )
            continue;
        C3DModel* model = static_cast<C3DModelNode*>(node)->getModel();


        if (model)
        {
            C3DAABB worldSpaceBox(*model->getMesh()->getBoundingBox());                
            box.merge(worldSpaceBox);
        }
    }

    if (!_bbOrigin)
        _bbOrigin = new C3DAABB();
    _bbOrigin->_min = box._min;
    _bbOrigin->_max = box._max;

    if (!_bb)
        _bb = new C3DAABB();
    _bb->_min = box._min;
    _bb->_max = box._max;
}


C3DNode::Type C3DSprite::getType() const
{
    return C3DNode::NodeType_SuperModel;
}

void C3DSprite::playAnimationClip(const char* name)
{
    if( _animation == nullptr)
        return;

    _animation->play(name);
}

void C3DSprite::stopAnimationClip(const char* name)
{
    if( _animation == nullptr)
        return;

    _animation->stop(name);
}

void C3DSprite::pauseAnimationClip(const char* name)  
{
    if( _animation == nullptr)
        return;

    _animation->pause(name);
}

void C3DSprite::resumeAnimationClip(const char* name) 
{
    if( _animation == nullptr)
        return;

    _animation->resume(name);
}

bool C3DSprite::isAnimationClipPlaying(const char* clipName)
{
    return false;
}

void C3DSprite::setSkeleton(C3DBone* joint)
{
    if(_skeleton == nullptr)
        _skeleton = new C3DSkeleton();
    _skeleton->set(joint);
}

C3DBone* C3DSprite::getSkeletonRootBone()const
{
    if (_skeleton)
        return _skeleton->getRootBone();

    return nullptr;
}

C3DBone* C3DSprite::getBone(const char* name)const
{
    if (_skeleton)
        return _skeleton->getBone(name);

    return nullptr;
}

C3DAnimationClip* C3DSprite::getAnimationClip(const char* strClip)
{
    if (_animation == nullptr)
        return nullptr;

    return _animation->getClip(strClip);
}

C3DAnimationClip* C3DSprite::getCurAnimationClip()
{
    if (_animation == nullptr)
        return nullptr;

    return _animation->getCurAnimationClip();
}

int C3DSprite::getAnimationFrameCount()
{
    if( _animation == nullptr )
        createAnimation();

    _animation = _skeleton->getAnimation("movements");
    if (_animation)
        return _animation->getFrameCount();

    return 0;
}

void C3DSprite::copyFrom(const Transform* other, C3DNode::CloneContext& context)
{
    const C3DSprite* otherNode = static_cast<const C3DSprite*>(other);    

    C3DRenderNode::copyFrom(other, context);    

    C3DSkeleton* ske = otherNode->_skeleton;
    _skeleton = ske ? ske->clone() : nullptr;

    _fileName = otherNode->_fileName;

    if (otherNode->_skeleton)
    {
        C3DBone* bone = (C3DBone*)context.cloneMap[otherNode->_skeleton->getRootBone()];
        if (bone != nullptr)
        {
            setSkeleton(bone);
            _animation = _skeleton->getAnimation("movements");
        }
    }
}

C3DNode* C3DSprite::clone(C3DNode::CloneContext& context) const
{
    C3DSprite* other = new C3DSprite("");
    other->copyFrom(this, context);

    ((C3DResource*)other)->copyFrom(this);

    other->autorelease();
    return other;
}

void C3DSprite::stopAllAnimationClip()
{
    _animation->stopAll();
    _animation->update(0);
}

NS_CC_END
