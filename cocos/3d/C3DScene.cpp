#include "Base.h"
#include "C3DScene.h"
#include "C3DVector3.h"
#include "C3DRenderNode.h"
#include "C3DCamera.h"

#include "C3DLight.h"
#include "C3DSprite.h"
#include "C3DStaticObj.h"
#include "C3DBatchModel.h"
#include "C3DMaterial.h"
#include "MaterialParameter.h"
#include "C3DRenderChannel.h"
#include "C3DVertexFormat.h"

#include "C3DLayer.h"
#include "C3DBatchMesh.h"
#include "Vertex.h"

#include "C3DStat.h"
#include "C3DShadowMap.h"
#include "C3DRenderSystem.h"
#include "C3DViewport.h"
#include "C3DPostProcess.h"
#include "C3DGeoWireRender.h"

namespace cocos3d
{
    
C3DNode* C3DScene::findNode(const char* strId)
    {
        return C3DNode::findNode(strId, true);
    }
    
void C3DScene::removeAllNode()
    {
		SAFE_RELEASE(_activeLight);
		SAFE_RELEASE(_activeCamera);
		SAFE_RELEASE(_activeShadowMap);
		SAFE_RELEASE(_activePostProcess);

        removeAllChildren();

        size_t i;
        for (i = 0; i < _lights.size(); i++) {
            SAFE_RELEASE(_lights[i]);
        }
        _lights.clear();

        for (i = 0; i < _cameras.size(); i++) {
            SAFE_RELEASE(_cameras[i]);
        }
        _cameras.clear();

		for (i = 0; i < _shadowMaps.size(); i++) {
            SAFE_RELEASE(_shadowMaps[i]);
        }
        _shadowMaps.clear();

		for (i = 0; i < _postProcesss.size(); i++) {
            SAFE_RELEASE(_postProcesss[i]);
        }
        _postProcesss.clear();

    }
    
    
C3DScene::C3DScene(const char* str) : C3DNode(str)
{
	_ambientColor = new C3DVector3();

	_showBoundingBox = false;
	_showPosAxis = false;
	_showScaleAxis = false;

	_showLightPos = false;

	_activeCamera = NULL;
	_activeLight = NULL;
     
    
    _defDepthZ = 0.5f;
    _inShadowPass = false;
    _activeShadowMap = NULL;
	_activePostProcess = NULL;

    _layer = NULL;
	_geoWireRender = NULL;
    setScene(this);
}


C3DScene::~C3DScene()
{
	SAFE_RELEASE(_activeCamera);
	SAFE_RELEASE(_activeLight);
		
	SAFE_DELETE(_ambientColor);

    removeAllNode();
    

	SAFE_DELETE(_geoWireRender);
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

 C3DLight* C3DScene::getLight(int index) 
	{
		if(index < (int)_lights.size())
			return _lights[index]; 
		else
			return NULL;
	}

void C3DScene::setViewAspectRatio(float aspectRatio)
{
	if(getActiveCamera() != NULL)
	{
		getActiveCamera()->setAspectRatio(aspectRatio);
	}
	
}


const C3DVector3* C3DScene::getAmbientColor() const
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

void C3DScene::showLight(bool show)
{
	_showLightPos = show;
}

void C3DScene::drawLights()
{
	for (std::vector<C3DLight*>::iterator iter = _lights.begin(); iter != _lights.end(); ++iter)
	{
		C3DLight* light = *iter;
		C3DVector3 pos =light->getTranslationWorld();
		C3DVector4 color;
		if (light->getLightType() == C3DLight::DIRECTIONAL)
			color = C3DVector4(1,0,0,1);
		else if (light->getLightType() == C3DLight::POINT)
			color = C3DVector4(0,1,0,1);
		else if (light->getLightType() == C3DLight::SPOT)
			color = C3DVector4(0,0,1,1);

		C3DVector3 offsetX(0.2f, 0.0f, 0.0f);
		C3DVector3 offsetY(0.0f, 0.2f, 0.0f);
		C3DVector3 offsetZ(0.0f, 0.0f, 0.2f);
		C3DGeoWireRender* render = getGeoWireRender();
		render->add3DLine(pos + offsetX, pos - offsetX, color);
		render->add3DLine(pos + offsetY, pos - offsetY, color);
		render->add3DLine(pos + offsetZ, pos - offsetZ, color);
	}
}

C3DGeoWireRender* C3DScene::getGeoWireRender()
{
	if (_geoWireRender == NULL)
	{
		_geoWireRender = new C3DGeoWireRender();
		C3DNode* node = C3DNode::create("geowirerender");
		this->addChild(node);
		_geoWireRender->init(node);
	}
	return _geoWireRender;
}


void C3DScene::drawDebug()
{	
    for (size_t i = 0; i < _children.size(); i++) 
	{
        _children[i]->drawDebug();
		
    }

	// show lights
	if (_showLightPos)
		drawLights();

	if (_geoWireRender)
		_geoWireRender->flush();

}

void C3DScene::preDraw()
{
    C3DStat::getInstance()->beginStat();
    
	C3DRenderSystem::getInstance()->getRenderChannelManager()->clearChannelItems();

    if (_activeShadowMap && _activeShadowMap->active())
    {
        _inShadowPass = true;

        _activeShadowMap->beginDraw();
        //draw scene

        bool bStatEnable = C3DStat::getInstance()->isStatEnable();        

		for (size_t i = 0; i < _children.size(); ++i) 
		{
			C3DNode* node = _children[i];
			if(node->active())
			{			
				node->draw();

				if (bStatEnable)
					C3DStat::getInstance()->incTriangleTotal(node->getTriangleCount());

			}
		}

        _activeShadowMap->endDraw();

        _inShadowPass = false;
    }


	//....posteffect start ....
	if (_activePostProcess && _activePostProcess->active())
    {
        _activePostProcess->beginDraw();		       
    }
	//....posteffect end.......

}

void C3DScene::draw()
{
	//	C3DNode::draw();

	bool bStatEnable = C3DStat::getInstance()->isStatEnable(); 
	size_t i;
	for (i = 0; i < _children.size(); ++i) 
	{
		C3DNode* node = _children[i];
		if(node->active())
		{			
			node->draw();

			if (bStatEnable)
				C3DStat::getInstance()->incTriangleTotal(node->getTriangleCount());

		}

	}


        
}
    
void C3DScene::drawCameraAndLight()
{
    // to do.. draw cameras and lights
}

void C3DScene::postDraw()
{
	C3DRenderSystem::getInstance()->getRenderChannelManager()->draw();
	
    C3DStat::getInstance()->endStat();

	//....posteffect start ....
	if (_activePostProcess && _activePostProcess->active())
    { 
        _activePostProcess->endDraw();   

		_activePostProcess->draw();
    }
	//....posteffect end.......
}
    
// update routine
void C3DScene::update(long elapsedTime)
{
    //update children then
   // C3DNode::update(elapsedTime);

	size_t i;
    for (i = 0; i < _children.size(); ++i) 
	{
		C3DNode* node = _children[i];
		if(node->active())
			node->update(elapsedTime);
    }

	if (_geoWireRender)
		_geoWireRender->begin();
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
	case C3DNode::NodeType_Light:
		{
			bool found = false;
			for (std::vector<C3DLight*>::iterator iter=_lights.begin(); iter!=_lights.end(); ++iter)
			{
				if (*iter == node)
				{
					found = true;
					break;
				}
			}
			if (found == false)
			{
				_lights.push_back((C3DLight*)node);
				node->retain();
			}
			else
			{
				assert(false && "Duplicated light node!");
			}
		}
		break;
    case C3DNode::NodeType_ShadowMap:
        {
            bool found = false;
            for (std::vector<C3DShadowMap*>::iterator iter=_shadowMaps.begin(); iter!=_shadowMaps.end(); ++iter)
            {
                if (*iter == node)
                {
                    found = true;
                    break;
                }
            }
            if (found == false)
            {
                _shadowMaps.push_back((C3DShadowMap*)node);
                node->retain();
            }
            else
            {
                assert(false && "Duplicated shadow map node!");
            }
        }
        break;
	 case C3DNode::NodeType_PostProcess:
        {
            bool found = false;
            for (std::vector<C3DPostProcess*>::iterator iter=_postProcesss.begin(); iter!=_postProcesss.end(); ++iter)
            {
                if (*iter == node)
                {
                    found = true;
                    break;
                }
            }
            if (found == false)
            {
                _postProcesss.push_back((C3DPostProcess*)node);
                node->retain();
            }
            else
            {
                assert(false && "Duplicated posteffect node!");
            }
        }
        break;

	default:
		break;
	}

	for (size_t i = 0; i < node->_children.size(); i++)
	{
	//	addNodeToRenderList(node->_children[i]);
	}
	
}

void C3DScene::removeNodeFromRenderList(C3DNode* node)
{
    node->setScene(NULL);
	for (size_t i = 0; i < node->_children.size(); i++)
	{
	//	removeNodeFromRenderList(node->_children[i]);
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
	case C3DNode::NodeType_Light:
		{
			std::vector<C3DLight*>::iterator it = find(_lights.begin(), _lights.end(), (C3DLight*)node);
			if (it != _lights.end())
			{
				_lights.erase(it);
				node->release();
			}
			else
			{
				assert(false && "unrefereed node");
			}
			break;
		}
    case C3DNode::NodeType_ShadowMap:
        {
            std::vector<C3DShadowMap*>::iterator it = find(_shadowMaps.begin(), _shadowMaps.end(), (C3DShadowMap*)node);
            if (it != _shadowMaps.end())
            {
                _shadowMaps.erase(it);
                node->release();
            }
            else
            {
                assert(false && "unrefereed node");
            }
            break;
        }	
	case C3DNode::NodeType_PostProcess:
        {
            std::vector<C3DPostProcess*>::iterator it = find(_postProcesss.begin(), _postProcesss.end(), (C3DPostProcess*)node);
            if (it != _postProcesss.end())
            {
                _postProcesss.erase(it);
                node->release();
            }
            else
            {
                assert(false && "unrefereed node");
            }
            break;
        }	
    
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

const C3DMatrix& C3DScene::getViewProjectionMatrix() const
{
    if (_inShadowPass)
    {
        CCAssert(_activeShadowMap, "active shadow map!");
        return _activeShadowMap->getViewProjectionMatrix();
    }
    else 
    {
        if (_activeCamera)
            return _activeCamera->getViewProjectionMatrix();
        else
            return C3DMatrix::identity();
    }
}

C3DShadowMap* C3DScene::getActiveShadowMap() const
{
    return _activeShadowMap;
}

C3DShadowMap* C3DScene::setActiveShadowMap(int index)
{
    C3DShadowMap* sm;
    if (index >= 0 && index < (int)_shadowMaps.size())
        sm = _shadowMaps[index];
    else
        sm = NULL;

    if (sm != _activeShadowMap)
    {
        SAFE_RELEASE(_activeShadowMap);
        _activeShadowMap = sm;
        _activeShadowMap->retain();
    }

    return _activeShadowMap;
}

int C3DScene::GetShadowMapCount() const
{
    return (int)_shadowMaps.size();
}

C3DPostProcess* C3DScene::getActivePostProcess() const
{
    return _activePostProcess;
}

C3DPostProcess* C3DScene::setActivePostProcess(int index)
{
    C3DPostProcess* pp;
    if (index >= 0 && index < (int)_postProcesss.size())
        pp = _postProcesss[index];
    else
        pp = NULL;

	if(pp == NULL)
	{
		SAFE_RELEASE(_activePostProcess);
	}
    else if (pp != _activePostProcess)
    {
        SAFE_RELEASE(_activePostProcess);
        _activePostProcess = pp;
        _activePostProcess->retain();
    }

    return _activePostProcess;
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


}
