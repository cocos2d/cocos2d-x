#include "Base.h"
#include "cocos3d.h"
#include "cocos2d.h"
#include "C3DStat.h"

namespace cocos3d
{

    C3DStat::C3DStat():_nTriangleDraw(0), _nTriangleTotal(0), _nDrawCall(0), _bStart(false), _bEnable(true)
    {
     
    }
    
    C3DStat::~C3DStat()
    {
        
    }

    C3DStat* C3DStat::getInstance()
    {
        static C3DStat instance;
        
        return &instance;
    }
    
void C3DStat::beginStat()
    {
        _nTriangleDraw = 0;
        _nTriangleTotal = 0;
        _nDrawCall = 0;
        _bStart = _bEnable;
    }
void C3DStat::endStat()
    {
        _bStart = false;
    }
    
void C3DStat::setStatEnable(bool bEnable)
    {
        if (_bEnable == bEnable)
            return;
        
        _bEnable = bEnable; 
    }
  

////////////////////////////////Implement of C3DStatRender//////////////////////////////////////////
C3DStatRender::C3DStatRender(cocos2d::CCNode* parent, float statfont):_parent(parent), _fontSize(statfont), _UpdateInterval(200), _UpdateIntervalAcc(0)
{
	_TriangleDrawLabel = cocos2d::CCLabelTTF::create("draw triangles: ", "Arial", _fontSize);
	_TriangleTotalLabel = cocos2d::CCLabelTTF::create("total triangles: ", "Arial", _fontSize);
	_DrawCallLabel = cocos2d::CCLabelTTF::create("draw call: ", "Arial", _fontSize);

	_parent->addChild(_TriangleDrawLabel);
	_parent->addChild(_TriangleTotalLabel);
	_parent->addChild(_DrawCallLabel);

	_TriangleDrawLabel->retain();
	_TriangleTotalLabel->retain();
	_DrawCallLabel->retain();

	cocos2d::CCSize size = _parent->getContentSize();
	setStatLabelPos(cocos2d::CCPoint(size.width - _fontSize * 10, size.height - _fontSize * 3));
}
C3DStatRender::~C3DStatRender()
{
	SAFE_RELEASE(_DrawCallLabel);
	SAFE_RELEASE(_TriangleTotalLabel);
	SAFE_RELEASE(_TriangleDrawLabel);
}

void C3DStatRender::setStatLabelPos(const cocos2d::CCPoint& point)
{
	cocos2d::CCPoint pt = point;        
	_DrawCallLabel->setPosition(pt);
	pt.y += _fontSize;
	_TriangleDrawLabel->setPosition(pt);
	pt.y += _fontSize;
	_TriangleTotalLabel->setPosition(pt);
}

void C3DStatRender::setStatFont(float fontsize)
{
	_fontSize = fontsize;

	_TriangleDrawLabel->setFontSize(fontsize);
	_TriangleTotalLabel->setFontSize(fontsize);
	_DrawCallLabel->setFontSize(fontsize);
}

void C3DStatRender::update(long elapsedTime)
{
	C3DStat* statInstance = C3DStat::getInstance();
	if (!statInstance->isStatEnable())
	{
		if (_TriangleDrawLabel->isVisible())
		{
			_TriangleDrawLabel->setVisible(false);
			_TriangleTotalLabel->setVisible(false);
			_DrawCallLabel->setVisible(false);
		}
		return;
	}

	if (!_TriangleDrawLabel->isVisible())
	{
		_TriangleDrawLabel->setVisible(true);
		_TriangleTotalLabel->setVisible(true);
		_DrawCallLabel->setVisible(true);
	}

	_UpdateIntervalAcc += elapsedTime;
	if (_UpdateIntervalAcc >= _UpdateInterval)
	{
		_UpdateIntervalAcc = 0;

		char str[128];
		sprintf(str, "draw call: %d", statInstance->getDrawCall());
		_DrawCallLabel->setString(str);
		sprintf(str, "draw triangles: %d", statInstance->getTriangleDraw());
		_TriangleDrawLabel->setString(str);
		sprintf(str, "total triangles: %d", statInstance->getTriangleTotal());
		_TriangleTotalLabel->setString(str);


	}
}

}
