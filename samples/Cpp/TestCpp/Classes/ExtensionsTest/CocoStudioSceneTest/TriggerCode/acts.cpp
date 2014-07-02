
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

void PlayMusic::serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != NULL)
			{
				_nTag = atoi(str);//DICTOOL->getIntValue_json(subDict, "value");
			}
		}
		else if (key == "componentName")
		{
			if (str != NULL)
			{
				_comName = str; //DICTOOL->getStringValue_json(subDict, "value");
			}

		}
		else if (key == "type")
		{
			if (str != NULL)
			{
				_nType = atoi(str); //DICTOOL->getIntValue_json(subDict, "value");
			}
		}
	}
}

void PlayMusic::removeAll()
{
}

IMPLEMENT_CLASS_INFO(TMoveTo)
TMoveTo::TMoveTo(void)
:_nTag(-1)
,_fDuration(0.0f)
{
}

TMoveTo::~TMoveTo(void)
{
}

bool TMoveTo::init()
{
	return true;
}

void TMoveTo::done()
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

void TMoveTo::serialize(const rapidjson::Value &val)
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

void TMoveTo::serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != NULL)
			{
				_nTag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != NULL)
			{
				_fDuration = atof(str); 
			}

		}
		else if (key == "x")
		{
			if (str != NULL)
			{
				_pos.x = atof(str);
			}
		}
		else if (key == "y")
		{
			if (str != NULL)
			{
				_pos.y = atoi(str);
			}
		}
	}
}

void TMoveTo::removeAll()
{
	CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
	pNode->getActionManager()->removeAllActions();
}

IMPLEMENT_CLASS_INFO(TMoveBy)
TMoveBy::TMoveBy(void)
:_nTag(-1)
,_fDuration(0.0f)
,_bReverse(false)
{
}

TMoveBy::~TMoveBy(void)
{
}

bool TMoveBy::init()
{
    return true;
}

void TMoveBy::done()
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

void TMoveBy::serialize(const rapidjson::Value &val)
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
			_bReverse = DICTOOL->getIntValue_json(subDict, "value") != 0? true:false;
			continue;
		}
	}
}

void TMoveBy::serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != NULL)
			{
				_nTag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != NULL)
			{
				_fDuration = atof(str); 
			}

		}
		else if (key == "x")
		{
			if (str != NULL)
			{
				_pos.x = atof(str);
			}
		}
		else if (key == "y")
		{
			if (str != NULL)
			{
				_pos.y = atof(str);
			}
		}
		else if (key == "IsReverse")
		{
			if (str != NULL)
			{
				_bReverse = atoi(str)!=0?true:false; //DICTOOL->getIntValue_json(subDict, "value") != 0? true: false;
			}
		}
	}
}

void TMoveBy::removeAll()
{
	CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
	pNode->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TRotateTo)
TRotateTo::TRotateTo(void)
: _nTag(-1)
, _fDuration(0.0f)
, _fDeltaAngle(0.0f)
{
}

TRotateTo::~TRotateTo(void)
{
}

bool TRotateTo::init()
{
    return true;
}

void TRotateTo::done()
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

void TRotateTo::serialize(const rapidjson::Value &val)
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

void TRotateTo::serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != NULL)
			{
				_nTag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != NULL)
			{
				_fDuration = atof(str); 
			}

		}
		else if (key == "DeltaAngle")
		{
			if (str != NULL)
			{
				_fDeltaAngle = atof(str);
			}
		}
	}
}

void TRotateTo::removeAll()
{
	CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
	pNode->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TRotateBy)
TRotateBy::TRotateBy(void)
: _nTag(-1)
, _fDuration(0.0f)
, _fDeltaAngle(0.0f)
, _bReverse(false)
{
}

TRotateBy::~TRotateBy(void)
{
}

bool TRotateBy::init()
{
    return true;
}

void TRotateBy::done()
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

void TRotateBy::serialize(const rapidjson::Value &val)
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
			_bReverse = DICTOOL->getIntValue_json(subDict, "value")!= 0? true:false;
			continue;
		}
	}
}

void TRotateBy::serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != NULL)
			{
				_nTag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != NULL)
			{
				_fDuration = atof(str); 
			}

		}
		else if (key == "DeltaAngle")
		{
			if (str != NULL)
			{
				_fDeltaAngle = atof(str);
			}
		}
		else if (key == "IsReverse")
		{
			if (str != NULL)
			{
				_bReverse = atoi(str)!=0?true:false;
			}
		}
	}
}

void TRotateBy::removeAll()
{
	CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
	pNode->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TScaleTo)
TScaleTo::TScaleTo(void)
: _nTag(-1)
, _fDuration(0.0f)
{
}

TScaleTo::~TScaleTo(void)
{

}

bool TScaleTo::init()
{
    return true;
}

void TScaleTo::done()
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

void TScaleTo::serialize(const rapidjson::Value &val)
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

void TScaleTo::serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != NULL)
			{
				_nTag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != NULL)
			{
				_fDuration = atof(str); 
			}

		}
		else if (key == "ScaleX")
		{
			if (str != NULL)
			{
				_scale.x = atof(str);
			}
		}
		else if (key == "ScaleY")
		{
			if (str != NULL)
			{
				_scale.y = atof(str);
			}
		}
	}
}

void TScaleTo::removeAll()
{
	CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
	pNode->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TScaleBy)
TScaleBy::TScaleBy(void)
: _nTag(-1)
, _fDuration(0.0f)
, _bReverse(false)
{
}

TScaleBy::~TScaleBy(void)
{
}

bool TScaleBy::init()
{
    return true;
}

void TScaleBy::done()
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

void TScaleBy::serialize(const rapidjson::Value &val)
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
			_bReverse = DICTOOL->getIntValue_json(subDict, "value")!= 0? true:false;
			continue;
		}
	}
}

void TScaleBy::serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != NULL)
			{
				_nTag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != NULL)
			{
				_fDuration = atof(str); 
			}

		}
		else if (key == "ScaleX")
		{
			if (str != NULL)
			{
				_scale.x = atof(str);
			}
		}
		else if (key == "ScaleY")
		{
			if (str != NULL)
			{
				_scale.y = atof(str);
			}
		}
		else if (key == "IsReverse")
		{
			if (str != NULL)
			{
				_bReverse = atoi(str)!=0?true:false; //DICTOOL->getIntValue_json(subDict, "value")!= 0? true:false;
			}
			continue;
		}
	}
}

void TScaleBy::removeAll()
{
	CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
	pNode->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TSkewTo)
TSkewTo::TSkewTo(void)
: _nTag(-1)
, _fDuration(0.0f)
{
}

TSkewTo::~TSkewTo(void)
{
}

bool TSkewTo::init()
{
    return true;
}

void TSkewTo::done()
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

void TSkewTo::serialize(const rapidjson::Value &val)
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

void TSkewTo::serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != NULL)
			{
				_nTag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != NULL)
			{
				_fDuration = atof(str); 
			}

		}
		else if (key == "SkewX")
		{
			if (str != NULL)
			{
				_skew.x = atof(str);
			}
		}
		else if (key == "SkewY")
		{
			if (str != NULL)
			{
				_skew.y = atof(str);
			}
		}
	}
}

void TSkewTo::removeAll()
{
	CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
	pNode->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TSkewBy)
TSkewBy::TSkewBy(void)
: _nTag(-1)
, _fDuration(0.0f)
, _bReverse(false)
{
}

TSkewBy::~TSkewBy(void)
{
}

bool TSkewBy::init()
{
    return true;
}

void TSkewBy::done()
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

void TSkewBy::serialize(const rapidjson::Value &val)
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
			_bReverse = DICTOOL->getIntValue_json(subDict, "value")!= 0? true:false;
		}
	}
}

void TSkewBy::serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != NULL)
			{
				_nTag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != NULL)
			{
				_fDuration = atof(str); 
			}

		}
		else if (key == "SkewX")
		{
			if (str != NULL)
			{
				_skew.x = atof(str);
			}
		}
		else if (key == "SkewY")
		{
			if (str != NULL)
			{
				_skew.y = atof(str);
			}
		}
		else if (key == "IsReverse")
		{
			_bReverse = atoi(str)!=0?true:false; //DICTOOL->getIntValue_json(subDict, "value")!= 0? true:false;
		}
	}
}

void TSkewBy::removeAll()
{
	CCNode *pNode = SceneReader::sharedSceneReader()->getNodeByTag(_nTag);
	pNode->getActionManager()->removeAllActions();
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

void TriggerState::serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "ID")
		{
			if (str != NULL)
			{
				_nID = atoi(str);
			}
		}
		else if (key == "State")
		{
			if (str != NULL)
			{
				_nState = atoi(str); 
			}
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
		CCComRender *pRender = (CCComRender*)(pNode->getComponent(_comName.c_str()));
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
			_comName = DICTOOL->getStringValue_json(subDict, "value");
			continue;
		}
		else if (key == "AnimationName")
		{
			_aniname = DICTOOL->getStringValue_json(subDict, "value");
			continue;
		}
	}
}

void ArmaturePlayAction::serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != NULL)
			{
				_nTag = atoi(str);//DICTOOL->getIntValue_json(subDict, "value");
			}
		}
		else if (key == "componentName")
		{
			if (str != NULL)
			{
				_comName = str; //DICTOOL->getStringValue_json(subDict, "value");
			}

		}
		else if (key == "AnimationName")
		{
			if (str != NULL)
			{
				_aniname = str; //DICTOOL->getStringValue_json(subDict, "value");
			}
		}
	}
}

void ArmaturePlayAction::removeAll()
{
	CCLOG("ArmaturePlayAction::removeAll");
}


