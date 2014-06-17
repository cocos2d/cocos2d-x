#ifndef __CONS_H__
#define __CONS_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ExtensionMacros.h"


class TimeElapsed : public cocos2d::extension::BaseTriggerCondition
{
    DECLARE_CLASS_INFO
public:
     TimeElapsed(void);
     virtual ~TimeElapsed(void);

     virtual bool init();
     virtual bool detect();
	 virtual void serialize(const rapidjson::Value &val);
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
     virtual void removeAll();
	 virtual void update(float dt);
private:
	 float _fTotalTime;
	 float _fTmpTime;
	 cocos2d::CCScheduler *_pScheduler;
	 bool _bSuc;
};


class ArmatureActionState : public cocos2d::extension::BaseTriggerCondition
{
    DECLARE_CLASS_INFO
public:
     ArmatureActionState(void);
     virtual ~ArmatureActionState(void);

     virtual bool init();
     virtual bool detect();
	 virtual void serialize(const rapidjson::Value &val);
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
     virtual void removeAll();
	 void animationEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
private:
	 int _nTag;
	 std::string _comName;
	 std::string _aniname;
	 int _nState;
	 bool _bSuc;
};


class NodeInRect : public cocos2d::extension::BaseTriggerCondition
{
    DECLARE_CLASS_INFO
public:
     NodeInRect(void);
     virtual ~NodeInRect(void);

     virtual bool init();
     virtual bool detect();
	 virtual void serialize(const rapidjson::Value &val);
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
     virtual void removeAll();
private:
	int  _nTag;
	cocos2d::CCPoint _origin;
	cocos2d::CCSize  _size;
};

class NodeVisible : public cocos2d::extension::BaseTriggerCondition
{
    DECLARE_CLASS_INFO
public:
     NodeVisible(void);
     virtual ~NodeVisible(void);

     virtual bool init();
     virtual bool detect();
	 virtual void serialize(const rapidjson::Value &val);
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
     virtual void removeAll();
private:
	int  _nTag;
	bool _bVisible;
};


#endif
