
#include "cons.h"

using namespace cocos2d;
using namespace cocos2d::extension;


IMPLEMENT_CLASS_INFO(TimeElapsed)

TimeElapsed::TimeElapsed(void)
:_fTotalTime(0.0f)
,_fTmpTime(0.0f)
,_pScheduler(NULL)
,_bSuc(false)
{
	_pScheduler = CCDirector::sharedDirector()->getScheduler();
	_pScheduler->retain();
}

TimeElapsed::~TimeElapsed(void)
{
	CC_SAFE_RELEASE(_pScheduler);
}

bool TimeElapsed::init()
{
	_pScheduler->scheduleSelector(schedule_selector(TimeElapsed::update), this, 0.0f , kCCRepeatForever, 0.0f, false);
    return true;
}

bool TimeElapsed::detect()
{
    return _bSuc;
}

void TimeElapsed::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "TotalTime")
		{
			_fTotalTime = DICTOOL->getFloatValue_json(subDict, "value");
		}
	}
}

void TimeElapsed::removeAll()
{
	_pScheduler->unscheduleUpdateForTarget(this);
}

void TimeElapsed::update(float dt)
{
	_fTmpTime += dt;
	if (_fTmpTime > _fTotalTime)
	{
		_fTmpTime = 0.0f;
		_bSuc = true;
	}
}

IMPLEMENT_CLASS_INFO(ArmatureActionState)
ArmatureActionState::ArmatureActionState(void)
: _nTag(-1)
, _nState(-1)
, _bSuc(false)
{
}

ArmatureActionState::~ArmatureActionState(void)
{
}

bool ArmatureActionState::init()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCComRender *pRender = (CCComRender*)(pNode->getComponent(_comName.c_str()));
		CC_BREAK_IF(pRender == NULL);
		CCArmature *pAr = (CCArmature *)(pRender->getNode());
		CC_BREAK_IF(pAr == NULL);
		TriggerMng::getInstance()->addArmatureMovementCallBack(pAr, this, movementEvent_selector(ArmatureActionState::animationEvent));
	} while (0);
	
	return true;
}

bool ArmatureActionState::detect()
{
    return _bSuc;
}

void ArmatureActionState::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_nTag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "componentName")
		{
			_comName = DICTOOL->getStringValue_json(subDict, "value");
			continue;
		}
		else if (key == "AnimationName")
		{
			_aniname = DICTOOL->getStringValue_json(subDict, "value");
			continue;
		}
		else if (key == "ActionType")
		{
			_nState = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void ArmatureActionState::removeAll()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCComRender *pRender = (CCComRender*)(pNode->getComponent(_comName.c_str()));
		CC_BREAK_IF(pRender == NULL);
		CCArmature *pAr = (CCArmature *)(pRender->getNode());
		CC_BREAK_IF(pAr == NULL);
		TriggerMng::getInstance()->removeArmatureMovementCallBack(pAr, this, movementEvent_selector(ArmatureActionState::animationEvent));
	} while (0);
}

void ArmatureActionState::animationEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID)
{
	 std::string id = movementID;
	if (movementType == _nState && id.compare(_aniname) == 0)
	{
		_bSuc = true;
	}
}

IMPLEMENT_CLASS_INFO(NodeInRect)
NodeInRect::NodeInRect(void)
:_nTag(-1)
{
}

NodeInRect::~NodeInRect(void)
{
}

bool NodeInRect::init()
{

    return true;
}

bool NodeInRect::detect()
{
	CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
	if (pNode != NULL && abs(pNode->getPositionX() - _origin.x) <= _size.width && abs(pNode->getPositionY() - _origin.y) <= _size.height)
	{
		return true;
	}
    return false;
}

void NodeInRect::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_nTag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "originX")
		{
			_origin.x = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "originY")
		{
			_origin.y = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "sizeWidth")
		{
			_size.width = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "sizeHeight")
		{
			_size.height = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void NodeInRect::removeAll()
{
	CCLOG("NodeInRect::removeAll");
}


IMPLEMENT_CLASS_INFO(NodeVisible)
NodeVisible::NodeVisible(void)
: _nTag(-1)
, _bVisible(false)
{
}

NodeVisible::~NodeVisible(void)
{
}

bool NodeVisible::init()
{
	return true;
}

bool NodeVisible::detect()
{
	CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
	if (pNode != NULL && pNode->isVisible() == _bVisible)
	{
		return true;
	}
	return false;
}

void NodeVisible::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_nTag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Visible")
		{
			_bVisible = DICTOOL->getIntValue_json(subDict, "value") != 0? true:false;
			continue;
		}
	}
}

void NodeVisible::removeAll()
{
	CCLOG("NodeVisible::removeAll");
}




