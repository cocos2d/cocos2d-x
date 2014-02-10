#include "Base.h"
#include "C3DScene.h"
#include "Vector3.h"
#include "C3DRenderNode.h"
#include "C3DCamera.h"

#include "C3DSprite.h"
#include "C3DStaticObj.h"

#include "C3DMaterial.h"
#include "MaterialParameter.h"
#include "C3DVertexFormat.h"

#include "C3DLayer.h"
#include "Vertex.h"

#include "C3DRenderSystem.h"
#include "C3DViewport.h"

NS_CC_BEGIN
    
C3DNode* C3DScene::findNode(const char* strId)
{
    return C3DNode::findNode(strId, true);
}
    
void C3DScene::removeAllNode()
{
    
    SAFE_RELEASE(_activeCamera);
    
    removeAllChildren();

    size_t i;
   

    for (i = 0; i < _cameras.size(); i++) {
        SAFE_RELEASE(_cameras[i]);
    }
    _cameras.clear();
            

    for (i = 0; i < _postDrawNode.size(); i++) {
        SAFE_RELEASE(_postDrawNode[i]);
    }
    _postDrawNode.clear();
        
}
   
    
C3DScene::C3DScene(const char* str) 
:C3DNode(str)
{
    _ambientColor = new Vector3();

    _showBoundingBox = false;
    
    _activeCamera = NULL;
        
    _defDepthZ = 0.5f;
    _inShadowPass = false;
   
    _layer = NULL;
    
    setScene(this);
        
}


C3DScene::~C3DScene()
{
    SAFE_RELEASE(_activeCamera);
    
        
    SAFE_DELETE(_ambientColor);

    removeAllNode();    
    
}

C3DScene* C3DScene::createScene(C3DLayer* layer)
{
    C3DScene* scene = new C3DScene();
    scene->_layer = layer;

    return scene;
}


C3DCamera* C3DScene::getActiveCamera() const
{
    return _activeCamera;
}
    
//set active camera by index
bool C3DScene::setActiveCamera(int index)
{
    if (index < getCameraCount() )
    {            
        if (_activeCamera != _cameras[index])
        {
            if (_activeCamera)
            _activeCamera->release();
            _activeCamera = _cameras[index];
            _activeCamera->retain();
                                
            _activeCamera->setAspectRatio((float)C3DRenderSystem::getInstance()->getViewport()->width/(float)C3DRenderSystem::getInstance()->getViewport()->height);
                            
        }
            
        return true;
    }
    return false;
}

//get number of cameras in the scene
int C3DScene::getCameraCount() const
{
    return (int)_cameras.size();
}


void C3DScene::setViewAspectRatio(float aspectRatio)
{
    if(getActiveCamera() != NULL)
    {
        getActiveCamera()->setAspectRatio(aspectRatio);
    }
    
}


const Vector3* C3DScene::getAmbientColor() const
{
    return _ambientColor;
}

void C3DScene::setAmbientColor(float red, float green, float blue)
{
    _ambientColor->set(red, green, blue);
}

void C3DScene::showBoundingBox(bool show)
{
    _showBoundingBox = show;
}


void C3DScene::drawDebug()
{    
    for (size_t i = 0; i < _children.size(); i++) 
    {
        _children[i]->drawDebug();
    }    
}


void C3DScene::draw()
{
    
    size_t i;
    for (i = 0; i < _children.size(); ++i) 
    {
        C3DNode* node = _children[i];
        if(node->active())
        {            
            node->draw();            

        }
    }
}
 
    
// update routine
void C3DScene::update(long elapsedTime)
{
    size_t i;
    for (i = 0; i < _children.size(); ++i) 
    {
        C3DNode* node = _children[i];
        if(node->active())
            node->update(elapsedTime);
    }
    
    
}
   

C3DNode::Type C3DScene::getType() const
{
    return C3DNode::NodeType_Scene;
}

void C3DScene::addNodeToRenderList(C3DNode* node)
{
    node->setScene(this);

    C3DNode::Type type = node->getType();
    switch (type) 
    {

    case C3DNode::NodeType_Camera:
        {
            bool found = false;
            for (std::vector<C3DCamera*>::iterator iter=_cameras.begin(); iter!=_cameras.end(); ++iter)
            {
                if (*iter == node)
                {
                    found = true;
                    break;
                }
            }
            if (found == false)
            {
                _cameras.push_back((C3DCamera*)node);
                node->retain();
            }
            else
            {
                assert(false && "Duplicated camera node!");
            }
        }

        break; 
     

    default:
        break;
    }

    for (size_t i = 0; i < node->_children.size(); i++)
    {
    //    addNodeToRenderList(node->_children[i]);
    }
    
}

void C3DScene::removeNodeFromRenderList(C3DNode* node)
{
   // node->setScene(NULL);
    for (size_t i = 0; i < node->_children.size(); i++)
    {
    //    removeNodeFromRenderList(node->_children[i]);
    }

    C3DNode::Type type = node->getType();
    switch (type) 
    {
    
    case C3DNode::NodeType_Camera:
        {
            if ( _activeCamera == node)
            {
                assert(false && "removing active camera");
            }
            std::vector<C3DCamera*>::iterator it = find(_cameras.begin(), _cameras.end(), (C3DCamera*)node);
            if (it != _cameras.end())
            {
                _cameras.erase(it);
                node->release();
            }
            else
            {
                assert(false && "unrefereed node");
            }
        }

        break;
    
    default:
        break;
    }
}

void C3DScene::onChildChanged(ChangeEvent eventType, C3DNode* child)
{
    switch (eventType)
    {
    case C3DNode::ADD:
        addNodeToRenderList(child);
        break;
    case C3DNode::REMOVE:
        removeNodeFromRenderList(child);
        break;
    }
}

const Matrix& C3DScene::getViewProjectionMatrix() const
{     
    if (_activeCamera)
        return _activeCamera->getViewProjectionMatrix();
    else
        return Matrix::identity();
}


C3DLayer* C3DScene::getLayer() const
{
    return _layer;
}

void C3DScene::setLayer(C3DLayer* layer)
{
    if (layer != _layer)
    {
        SAFE_RELEASE(_layer);
        _layer = layer;
        if (layer)
        {
            layer->retain();
        }
    }
}

void C3DScene::addChild(C3DNode* child)
{
    C3DNode::addChild(child);
}

void C3DScene::removeChild(C3DNode* child)
{
    C3DNode::removeChild(child);
}

NS_CC_END
