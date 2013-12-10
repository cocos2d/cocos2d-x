//
//  EffectCamera.cpp
//  cocos2dx
//
//  Created by YangWenXin on 13-12-9.
//  Copyright (c) 2013 cocos2d-x. All rights reserved.
//

#include "EffectCamera.h"
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

EffectCamera::EffectCamera() {
    init();
}

bool EffectCamera::init() {
    _originalX = 0;
    _originalY = 0;
    _originalAnchorPointX = 0.5;
    _originalAnchorPointY = 0.5;
    _originalWidth = 0;
    _originalHeight = 0;
    
    _currentOffsetX = 0;
    _currentOffsetY = 0;
    _currentScaleX = 1;
    _currentScaleY = 1;
    _currrentRotation = 0;
    
    _targetOffsetX = 0;
    _targetOffsetY = 0;
    _targetRotation = 0;
    _targetScaleX = 1;
    _targetScaleY = 1;
    
    _checkOffset = false;
    
    _isShaking = false;
    
    kmMat4Identity(&_transformMatrix);
    kmMat4Identity(&_mTranslate);
    kmMat4Identity(&_mScale);
    kmMat4Identity(&_mRotation);
    kmMat4Identity(&_mTemp);

    return true;
}

EffectCamera::~EffectCamera() {
    
}

void EffectCamera::initWithParams(float originalX, float originalY, float originalAnchorPointX, float originalAnchorPointY, float originalWidth, float originalHeight, bool checkOffset) {
    _originalX = originalX;
    _originalY = originalY;
    _originalAnchorPointX = originalAnchorPointX;
    _originalAnchorPointY = originalAnchorPointY;
    _originalWidth = originalWidth;
    _originalHeight = originalHeight;
    _checkOffset = checkOffset;
}

void EffectCamera::visit() {
    _dirtyR = false;
    _dirtyS = false;
    _dirtyT = false;
    if (_isShaking) {
        if (_duration > 0) {
            srand((unsigned)time(NULL));
            _currentOffsetX = _targetOffsetX + rand()%((int)_peak+1);
            _currentOffsetY = _targetOffsetY + rand()%((int)_peak+1);
            _peak -= _peakReduceGap;
            _duration--;
        }
        else {
            _isShaking = false;
            _currentOffsetX = _targetOffsetX;
            _currentOffsetY = _targetOffsetY;
        }
        _dirtyT = true;
    }
    else {
        // translate
        adjustGap(_currentOffsetX, _targetOffsetX, GAP_TRANSLATE, _dirtyT);
        adjustGap(_currentOffsetY, _targetOffsetY, GAP_TRANSLATE, _dirtyT);
        // scale
        adjustGap(_currentScaleX, _targetScaleX, GAP_SCALE, _dirtyS);
        adjustGap(_currentScaleY, _targetScaleY, GAP_SCALE, _dirtyS);
        // rotation
        adjustGap(_currrentRotation, _targetRotation, GAP_ROTATION, _dirtyR);
    }
    if (_dirtyT || _dirtyR || _dirtyS) {
        kmMat4Translation(&_mTranslate, _currentOffsetX, _currentOffsetY, 0);
        kmMat4Scaling(&_mScale, _currentScaleX, _currentScaleY, 0);
        kmMat4RotationZ(&_mRotation, _currrentRotation);
        if (!_dirtyR) {
            kmMat4Multiply(&_transformMatrix, &_mTranslate, &_mScale);
        }
        else {
            kmMat4Multiply(&_mTemp, &_mTranslate, &_mScale);
            kmMat4Multiply(&_transformMatrix, &_mTemp, &_mRotation);
        }
    }
    kmGLMultMatrix(&_transformMatrix);
}

void EffectCamera::adjustGap(float &src, float &dst, const float &gap, bool &dirty) {
    if (src != dst) {
        dirty = true;
        if (fabsf(src - dst) <= gap) {
            src = dst;
        }
        else if (src < dst) {
            src += gap;
        }
        else {
            src -= gap;
        }
    }
}

void EffectCamera::scrollTo(float offsetX, float offsetY) {
    _targetOffsetX = offsetX;
    _targetOffsetY = offsetY;
}

void EffectCamera::scrollToInc(float incOffsetX, float incOffsetY) {
    _targetOffsetX += incOffsetX;
    _targetOffsetY += incOffsetY;
}

void EffectCamera::scaleTo(float scaleX, float scaleY) {
    _targetScaleX = scaleX;
    _targetScaleY = scaleY;
}

void EffectCamera::scaleToInc(float incScaleX, float incScaleY) {
    _targetScaleX += incScaleX;
    _targetScaleY += incScaleY;
}

void EffectCamera::rotateTo(float rotation) {
    _targetRotation = rotation;
}

void EffectCamera::rotateToInc(float incRotation) {
    _targetRotation += incRotation;
}

void EffectCamera::shake(float peak, int duration) {
    _isShaking = true;
    _peak = peak;
    _duration = duration;
    _peakReduceGap = _peak/_duration;
}

void EffectCamera::reset() {
    _peak = 0;
    _duration = 0;
    _isShaking = false;
}

NS_CC_END