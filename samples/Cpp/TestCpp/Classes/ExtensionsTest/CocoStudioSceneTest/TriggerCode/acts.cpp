
#include "acts.h"

using namespace cocos2d;
using namespace cocos2d::extension;


IMPLEMENT_CLASS_INFO(PlayMusic)
PlayMusic::PlayMusic(void)
:_nTag(-1)
{
}

PlayMusic::~PlayMusic(void)
{
}

bool PlayMusic::init()
{
    return true;
}

void PlayMusic::done()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCComAudio *audio = (CCComAudio*)(pNode->getComponent(_comName.c_str()));
		CC_BREAK_IF(audio == NULL);
		if (_nType == 0)
		{
			audio->playBackgroundMusic();
		}
		else if (_nType == 1)
		{
			audio->playEffect();
		}

	} while (0);
}

void PlayMusic::serialize(const rapidjson::Value &val)
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
		else if (key == "type")
		{
			_nType = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void PlayMusic::removeAll()
{
}

IMPLEMENT_CLASS_INFO(MoveTo)
MoveTo::MoveTo(void)
:_nTag(-1)
,_fDuration(0.0f)
{
}

MoveTo::~MoveTo(void)
{
}

bool MoveTo::init()
{
	return true;
}

void MoveTo::done()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCActionInterval*  actionTo = CCMoveTo::create(_fDuration, _pos);
		CC_BREAK_IF(actionTo == NULL);
		pNode->runAction(actionTo);
	} while (0);
}

void MoveTo::serialize(const rapidjson::Value &val)
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
		else if (key == "Duration")
		{
			_fDuration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "x")
		{
			_pos.x = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "y")
		{
			_pos.y = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void MoveTo::removeAll()
{
}

IMPLEMENT_CLASS_INFO(MoveBy)
MoveBy::MoveBy(void)
:_nTag(-1)
,_fDuration(0.0f)
,_bReverse(false)
{
}

MoveBy::~MoveBy(void)
{
}

bool MoveBy::init()
{
    return true;
}

void MoveBy::done()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCActionInterval*  actionBy = CCMoveBy::create(_fDuration, _pos);
		CC_BREAK_IF(actionBy == NULL);
		if (_bReverse == true)
		{
			CCActionInterval*  actionByBack = actionBy->reverse();
			pNode->runAction( CCSequence::create(actionBy, actionByBack, NULL));
		}
		else
		{
			pNode->runAction(actionBy);
		}
	} while (0);
}

void MoveBy::serialize(const rapidjson::Value &val)
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
		else if (key == "Duration")
		{
			_fDuration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "x")
		{
			_pos.x = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "y")
		{
			_pos.y = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "IsReverse")
		{
			_bReverse = (bool)(DICTOOL->getIntValue_json(subDict, "value"));
			continue;
		}
	}
}

void MoveBy::removeAll()
{
	CCLOG("MoveBy::removeAll");
}



IMPLEMENT_CLASS_INFO(RotateTo)
RotateTo::RotateTo(void)
: _nTag(-1)
, _fDuration(0.0f)
, _fDeltaAngle(0.0f)
{
}

RotateTo::~RotateTo(void)
{
}

bool RotateTo::init()
{
    return true;
}

void RotateTo::done()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCActionInterval*  actionTo = CCRotateTo::create(_fDuration, _fDeltaAngle);
		CC_BREAK_IF(actionTo == NULL);
		pNode->runAction(actionTo);
	} while (0);
}

void RotateTo::serialize(const rapidjson::Value &val)
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
		else if (key == "Duration")
		{
			_fDuration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "DeltaAngle")
		{
			_fDeltaAngle = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
	}
}

void RotateTo::removeAll()
{
	CCLOG("RotateTo::removeAll");
}



IMPLEMENT_CLASS_INFO(RotateBy)
RotateBy::RotateBy(void)
: _nTag(-1)
, _fDuration(0.0f)
, _fDeltaAngle(0.0f)
, _bReverse(false)
{
}

RotateBy::~RotateBy(void)
{
}

bool RotateBy::init()
{
    return true;
}

void RotateBy::done()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCActionInterval*  actionBy = CCRotateBy::create(_fDuration, _fDeltaAngle);
		CC_BREAK_IF(actionBy == NULL);
		if (_bReverse == true)
		{
			CCActionInterval*  actionByBack = actionBy->reverse();
			pNode->runAction( CCSequence::create(actionBy, actionByBack, NULL));
		}
		else
		{
			pNode->runAction(actionBy);
		}
	} while (0);
}

void RotateBy::serialize(const rapidjson::Value &val)
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
		else if (key == "Duration")
		{
			_fDuration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "DeltaAngle")
		{
			_fDeltaAngle = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "IsReverse")
		{
			_bReverse = (int)(DICTOOL->getIntValue_json(subDict, "value"));
			continue;
		}
	}
}

void RotateBy::removeAll()
{
	CCLOG("RotateBy::removeAll");
}



IMPLEMENT_CLASS_INFO(ScaleTo)
ScaleTo::ScaleTo(void)
: _nTag(-1)
, _fDuration(0.0f)
{
}

ScaleTo::~ScaleTo(void)
{
}

bool ScaleTo::init()
{
    return true;
}

void ScaleTo::done()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCActionInterval*  actionTo = CCScaleTo::create(_fDuration, _scale.x, _scale.y);
		CC_BREAK_IF(actionTo == NULL);
		pNode->runAction(actionTo);
	} while (0);
}

void ScaleTo::serialize(const rapidjson::Value &val)
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
		else if (key == "Duration")
		{
			_fDuration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "ScaleX")
		{
			_scale.x = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "ScaleY")
		{
			_scale.y = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
	}
}

void ScaleTo::removeAll()
{
	CCLOG("ScaleTo::removeAll");
}



IMPLEMENT_CLASS_INFO(ScaleBy)
ScaleBy::ScaleBy(void)
: _nTag(-1)
, _fDuration(0.0f)
, _bReverse(false)
{
}

ScaleBy::~ScaleBy(void)
{
}

bool ScaleBy::init()
{
    return true;
}

void ScaleBy::done()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCActionInterval*  actionBy = CCScaleBy::create(_fDuration, _scale.x, _scale.y);
		CC_BREAK_IF(actionBy == NULL);
		if (_bReverse == true)
		{
			CCActionInterval*  actionByBack = actionBy->reverse();
			pNode->runAction( CCSequence::create(actionBy, actionByBack, NULL));
		}
		else
		{
			pNode->runAction(actionBy);
		}
	} while (0);
}

void ScaleBy::serialize(const rapidjson::Value &val)
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
		else if (key == "Duration")
		{
			_fDuration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "ScaleX")
		{
			_scale.x = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "ScaleY")
		{
			_scale.y = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "IsReverse")
		{
			_bReverse = (bool)(DICTOOL->getIntValue_json(subDict, "value"));
			continue;
		}
	}
}

void ScaleBy::removeAll()
{
	CCLOG("ScaleBy::removeAll");
}



IMPLEMENT_CLASS_INFO(SkewTo)
SkewTo::SkewTo(void)
: _nTag(-1)
, _fDuration(0.0f)
{
}

SkewTo::~SkewTo(void)
{
}

bool SkewTo::init()
{
    return true;
}

void SkewTo::done()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCActionInterval*  actionTo = CCSkewTo::create(_fDuration, _skew.x, _skew.y);
		CC_BREAK_IF(actionTo == NULL);
		pNode->runAction(actionTo);
	} while (0);
}

void SkewTo::serialize(const rapidjson::Value &val)
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
		else if (key == "Duration")
		{
			_fDuration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "SkewX")
		{
			_skew.x = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "SkewY")
		{
			_skew.y = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
	}
}

void SkewTo::removeAll()
{
	CCLOG("SkewTo::removeAll");
}



IMPLEMENT_CLASS_INFO(SkewBy)
SkewBy::SkewBy(void)
: _nTag(-1)
, _fDuration(0.0f)
, _bReverse(false)
{
}

SkewBy::~SkewBy(void)
{
}

bool SkewBy::init()
{
    return true;
}

void SkewBy::done()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCActionInterval*  actionBy = CCSkewBy::create(_fDuration, _skew.x, _skew.y);
		CC_BREAK_IF(actionBy == NULL);
		if (_bReverse == true)
		{
			CCActionInterval*  actionByBack = actionBy->reverse();
			pNode->runAction( CCSequence::create(actionBy, actionByBack, NULL));
		}
		else
		{
			pNode->runAction(actionBy);
		}
	} while (0);
}

void SkewBy::serialize(const rapidjson::Value &val)
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
		else if (key == "Duration")
		{
			_fDuration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "SKewX")
		{
			_skew.x = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "SKewY")
		{
			_skew.y = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "IsReverse")
		{
			_bReverse = (bool)(DICTOOL->getIntValue_json(subDict, "value"));
		}
	}
}

void SkewBy::removeAll()
{
	CCLOG("SkewBy::removeAll");
}



IMPLEMENT_CLASS_INFO(TriggerState)
TriggerState::TriggerState(void)
:_nID(-1)
,_nState(0)
{
}

TriggerState::~TriggerState(void)
{
}

bool TriggerState::init()
{
    return true;
}

void TriggerState::done()
{
    TriggerObj *obj = TriggerMng::getInstance()->getTriggerObj(_nID);
	if (obj != NULL)
	{
		if (_nState == 0)
		{
			obj->setEnable(false);
		}
		else if (_nState == 1)
		{
			obj->setEnable(true);
		}
		else if (_nState == 2)
		{
			TriggerMng::getInstance()->removeTriggerObj(_nID);
		}
		
	}
	
}

void TriggerState::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "ID")
		{
			_nID = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "State")
		{
			_nState = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void TriggerState::removeAll()
{
	CCLOG("TriggerState::removeAll");
}

IMPLEMENT_CLASS_INFO(ArmaturePlayAction)
ArmaturePlayAction::ArmaturePlayAction(void)
: _nTag(-1)
{
}

ArmaturePlayAction::~ArmaturePlayAction(void)
{
}

bool ArmaturePlayAction::init()
{
	return true;
}

void ArmaturePlayAction::done()
{
	do 
	{
		CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
		CC_BREAK_IF(pNode == NULL);
		CCComRender *pRender = (CCComRender*)(pNode->getComponent(_ComName.c_str()));
		CC_BREAK_IF(pRender == NULL);
		CCArmature *pAr = (CCArmature *)(pRender->getNode());
		CC_BREAK_IF(pAr == NULL);
		pAr->getAnimation()->play(_aniname.c_str());
	} while (0);
}

void ArmaturePlayAction::serialize(const rapidjson::Value &val)
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
			_ComName = DICTOOL->getStringValue_json(subDict, "value");
			continue;
		}
		else if (key == "AnimationName")
		{
			_aniname = DICTOOL->getStringValue_json(subDict, "value");
			continue;
		}
	}
}

void ArmaturePlayAction::removeAll()
{
	CCLOG("ArmaturePlayAction::removeAll");
}


