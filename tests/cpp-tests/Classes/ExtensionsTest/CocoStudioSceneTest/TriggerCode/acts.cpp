
#include "acts.h"

using namespace cocos2d;
using namespace cocostudio;


IMPLEMENT_CLASS_INFO(PlayMusic)
PlayMusic::PlayMusic(void)
:_tag(-1)
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
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ComAudio *audio = (ComAudio*)(node->getComponent(_comName.c_str()));
		CC_BREAK_IF(audio == nullptr);
		if (_type == 0)
		{
			audio->playBackgroundMusic();
		}
		else if (_type == 1)
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
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "componentName")
		{
			_comName = DICTOOL->getStringValue_json(subDict, "value");
			continue;
		}
		else if (key == "type")
		{
			_type = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void PlayMusic::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = nullptr;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != nullptr)
			{
				_tag = atoi(str);//DICTOOL->getIntValue_json(subDict, "value");
			}
		}
		else if (key == "componentName")
		{
			if (str != nullptr)
			{
				_comName = str; //DICTOOL->getStringValue_json(subDict, "value");
			}

		}
		else if (key == "type")
		{
			if (str != nullptr)
			{
				_type = atoi(str); //DICTOOL->getIntValue_json(subDict, "value");
			}
		}
	}
}

void PlayMusic::removeAll()
{
}

IMPLEMENT_CLASS_INFO(TMoveTo)
TMoveTo::TMoveTo(void)
:_tag(-1)
,_duration(0.0f)
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
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionTo = MoveTo::create(_duration, _pos);
		CC_BREAK_IF(actionTo == nullptr);
		node->runAction(actionTo);
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
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
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

void TMoveTo::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = nullptr;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != nullptr)
			{
				_tag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != nullptr)
			{
				_duration = utils::atof(str);
			}

		}
		else if (key == "x")
		{
			if (str != nullptr)
			{
				_pos.x = utils::atof(str);
			}
		}
		else if (key == "y")
		{
			if (str != nullptr)
			{
				_pos.y = atoi(str);
			}
		}
	}
}
void TMoveTo::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}

IMPLEMENT_CLASS_INFO(TMoveBy)
TMoveBy::TMoveBy(void)
:_tag(-1)
,_duration(0.0f)
,_reverse(false)
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
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionBy = MoveBy::create(_duration, _pos);
		CC_BREAK_IF(actionBy == nullptr);
		if (_reverse == true)
		{
			ActionInterval*  actionByBack = actionBy->reverse();
			node->runAction( CCSequence::create(actionBy, actionByBack, nullptr));
		}
		else
		{
			node->runAction(actionBy);
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
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
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
			_reverse = DICTOOL->getIntValue_json(subDict, "value") ? true : false;
			continue;
		}
	}
}

void TMoveBy::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = nullptr;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != nullptr)
			{
				_tag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != nullptr)
			{
				_duration = utils::atof(str);
			}

		}
		else if (key == "x")
		{
			if (str != nullptr)
			{
				_pos.x = utils::atof(str);
			}
		}
		else if (key == "y")
		{
			if (str != nullptr)
			{
				_pos.y = utils::atof(str);
			}
		}
		else if (key == "IsReverse")
		{
			if (str != nullptr)
			{
				_reverse = atoi(str)!=0?true:false; //DICTOOL->getIntValue_json(subDict, "value") != 0? true: false;
			}
		}
	}
}
void TMoveBy::removeAll()
{
    Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TRotateTo)
TRotateTo::TRotateTo(void)
: _tag(-1)
, _duration(0.0f)
, _deltaAngle(0.0f)
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
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionTo = RotateTo::create(_duration, _deltaAngle);
		CC_BREAK_IF(actionTo == nullptr);
		node->runAction(actionTo);
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
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "DeltaAngle")
		{
			_deltaAngle = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
	}
}

void TRotateTo::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = nullptr;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != nullptr)
			{
				_tag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != nullptr)
			{
				_duration = utils::atof(str);
			}

		}
		else if (key == "DeltaAngle")
		{
			if (str != nullptr)
			{
				_deltaAngle = utils::atof(str);
			}
		}
	}
}
void TRotateTo::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TRotateBy)
TRotateBy::TRotateBy(void)
: _tag(-1)
, _duration(0.0f)
, _deltaAngle(0.0f)
, _reverse(false)
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
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionBy = RotateBy::create(_duration, _deltaAngle);
		CC_BREAK_IF(actionBy == nullptr);
		if (_reverse == true)
		{
			ActionInterval*  actionByBack = actionBy->reverse();
			node->runAction( Sequence::create(actionBy, actionByBack, nullptr));
		}
		else
		{
			node->runAction(actionBy);
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
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "DeltaAngle")
		{
			_deltaAngle = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "IsReverse")
		{
			_reverse = (DICTOOL->getIntValue_json(subDict, "value")) ? true : false;
			continue;
		}
	}
}

void TRotateBy::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = nullptr;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != nullptr)
			{
				_tag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != nullptr)
			{
				_duration = utils::atof(str);
			}

		}
		else if (key == "DeltaAngle")
		{
			if (str != nullptr)
			{
				_deltaAngle = utils::atof(str);
			}
		}
		else if (key == "IsReverse")
		{
			if (str != nullptr)
			{
				_reverse = atoi(str)!=0?true:false;
			}
		}
	}
}
void TRotateBy::removeAll()
{
    Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TScaleTo)
TScaleTo::TScaleTo(void)
: _tag(-1)
, _duration(0.0f)
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
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionTo = ScaleTo::create(_duration, _scale.x, _scale.y);
		CC_BREAK_IF(actionTo == nullptr);
		node->runAction(actionTo);
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
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
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

void TScaleTo::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = nullptr;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != nullptr)
			{
				_tag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != nullptr)
			{
				_duration = utils::atof(str);
			}

		}
		else if (key == "ScaleX")
		{
			if (str != nullptr)
			{
				_scale.x = utils::atof(str);
			}
		}
		else if (key == "ScaleY")
		{
			if (str != nullptr)
			{
				_scale.y = utils::atof(str);
			}
		}
	}
}
void TScaleTo::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TScaleBy)
TScaleBy::TScaleBy(void)
: _tag(-1)
, _duration(0.0f)
, _reverse(false)
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
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionBy = ScaleBy::create(_duration, _scale.x, _scale.y);
		CC_BREAK_IF(actionBy == nullptr);
		if (_reverse == true)
		{
			ActionInterval*  actionByBack = actionBy->reverse();
			node->runAction(Sequence::create(actionBy, actionByBack, nullptr));
		}
		else
		{
			node->runAction(actionBy);
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
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
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
			_reverse = (DICTOOL->getIntValue_json(subDict, "value")) ? true : false;
			continue;
		}
	}
}

void TScaleBy::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = nullptr;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != nullptr)
			{
				_tag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != nullptr)
			{
				_duration = utils::atof(str);
			}

		}
		else if (key == "ScaleX")
		{
			if (str != nullptr)
			{
				_scale.x = utils::atof(str);
			}
		}
		else if (key == "ScaleY")
		{
			if (str != nullptr)
			{
				_scale.y = utils::atof(str);
			}
		}
		else if (key == "IsReverse")
		{
			if (str != nullptr)
			{
				_reverse = atoi(str)!=0?true:false; //DICTOOL->getIntValue_json(subDict, "value")!= 0? true:false;
			}
			continue;
		}
	}
}
void TScaleBy::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TSkewTo)
TSkewTo::TSkewTo(void)
: _tag(-1)
, _duration(0.0f)
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
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionTo = SkewTo::create(_duration, _skew.x, _skew.y);
		CC_BREAK_IF(actionTo == nullptr);
		node->runAction(actionTo);
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
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
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

void TSkewTo::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = nullptr;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != nullptr)
			{
				_tag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != nullptr)
			{
				_duration = utils::atof(str);
			}

		}
		else if (key == "SkewX")
		{
			if (str != nullptr)
			{
				_skew.x = utils::atof(str);
			}
		}
		else if (key == "SkewY")
		{
			if (str != nullptr)
			{
				_skew.y = utils::atof(str);
			}
		}
	}
}
void TSkewTo::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TSkewBy)
TSkewBy::TSkewBy(void)
: _tag(-1)
, _duration(0.0f)
, _reverse(false)
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
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionBy = SkewBy::create(_duration, _skew.x, _skew.y);
		CC_BREAK_IF(actionBy == nullptr);
		if (_reverse == true)
		{
			ActionInterval*  actionByBack = actionBy->reverse();
			node->runAction(Sequence::create(actionBy, actionByBack, nullptr));
		}
		else
		{
			node->runAction(actionBy);
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
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
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
			_reverse = DICTOOL->getIntValue_json(subDict, "value") ? true : false;
		}
	}
}

void TSkewBy::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = nullptr;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != nullptr)
			{
				_tag = atoi(str);
			}
		}
		else if (key == "Duration")
		{
			if (str != nullptr)
			{
				_duration = utils::atof(str);
			}

		}
		else if (key == "SkewX")
		{
			if (str != nullptr)
			{
				_skew.x = utils::atof(str);
			}
		}
		else if (key == "SkewY")
		{
			if (str != nullptr)
			{
				_skew.y = utils::atof(str);
			}
		}
		else if (key == "IsReverse")
		{
			_reverse = atoi(str)!=0?true:false; //DICTOOL->getIntValue_json(subDict, "value")!= 0? true:false;
		}
	}
}
void TSkewBy::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TriggerState)
TriggerState::TriggerState(void)
{
    _id = -1;
    _state = 0;
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
    TriggerObj *obj = TriggerMng::getInstance()->getTriggerObj(_id);
	if (obj != nullptr)
	{
		if (_state == 0)
		{
			obj->setEnabled(false);
		}
		else if (_state == 1)
		{
			obj->setEnabled(true);
		}
		else if (_state == 2)
		{
			TriggerMng::getInstance()->removeTriggerObj(_id);
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
			_id = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "State")
		{
			_state = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void TriggerState::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = nullptr;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "ID")
		{
			if (str != nullptr)
			{
				_id = atoi(str);
			}
		}
		else if (key == "State")
		{
			if (str != nullptr)
			{
				_state = atoi(str); 
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
: _tag(-1)
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
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ComRender *pRender = (ComRender*)(node->getComponent(_comName.c_str()));
		CC_BREAK_IF(pRender == nullptr);
		Armature *pAr = (Armature *)(pRender->getNode());
		CC_BREAK_IF(pAr == nullptr);
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
			_tag = DICTOOL->getIntValue_json(subDict, "value");
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

void ArmaturePlayAction::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
	int length = pCocoNode->GetChildNum();
	int count = 0;
	stExpCocoNode *pDataItemsArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string key;
	const char *str = nullptr;
	for (int i = 0; i < length; ++i)
	{
		count = pDataItemsArray[i].GetChildNum();
		stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
		key = pDataItemArray[0].GetValue(pCocoLoader);
		str = pDataItemArray[1].GetValue(pCocoLoader);
		if (key == "Tag")
		{
			if (str != nullptr)
			{
				_tag = atoi(str);//DICTOOL->getIntValue_json(subDict, "value");
			}
		}
		else if (key == "componentName")
		{
			if (str != nullptr)
			{
				_comName = str; //DICTOOL->getStringValue_json(subDict, "value");
			}

		}
		else if (key == "AnimationName")
		{
			if (str != nullptr)
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


