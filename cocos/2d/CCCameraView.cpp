#include "CCCameraView.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"

NS_CC_BEGIN

CameraView::CameraView() :
_camera(nullptr)
{

	_pushProj.func = [this]{
		Mat4 projMatrix;
		_camera->getProjectionMatrix(projMatrix);
		Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
		Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, projMatrix);
	};

	_popProj.func = [this]{
		Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	};
}

CameraView::~CameraView()
{}

void CameraView::visit(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated)
{
	if (_camera)
	{
		Director::getInstance()->getRenderer()->addCommand(&_pushProj);
	}

	Node::visit(renderer, parentTransform, parentTransformUpdated);

	if (_camera)
	{
		Director::getInstance()->getRenderer()->addCommand(&_popProj);
	}
}
NS_CC_END