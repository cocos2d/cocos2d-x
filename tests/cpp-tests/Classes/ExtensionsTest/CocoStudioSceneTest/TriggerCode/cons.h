#ifndef __CONS_H__
#define __CONS_H__

#include "cocos2d.h"
#include "cocostudio/TriggerBase.h"


class TimeElapsed : public cocostudio::BaseTriggerCondition
{
    DECLARE_CLASS_INFO
public:
     TimeElapsed(void);
     virtual ~TimeElapsed(void);

     virtual bool init();
     virtual bool detect();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
	 virtual void update(float dt);
private:
	 float _totalTime;
	 float _tmpTime;
	 cocos2d::Scheduler *_scheduler;
	 bool _suc;
};


class ArmatureActionState : public cocostudio::BaseTriggerCondition
{
    DECLARE_CLASS_INFO
public:
     ArmatureActionState(void);
     virtual ~ArmatureActionState(void);

     virtual bool init();
     virtual bool detect();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
	 void animationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);
private:
	 int _tag;
	 std::string _comName;
	 std::string _aniname;
	 int _state;
	 bool _suc;
};


class NodeInRect : public cocostudio::BaseTriggerCondition
{
    DECLARE_CLASS_INFO
public:
     NodeInRect(void);
     virtual ~NodeInRect(void);

     virtual bool init();
     virtual bool detect();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	cocos2d::Vec2 _origin;
	cocos2d::Size  _size;
};

class NodeVisible : public cocostudio::BaseTriggerCondition
{
    DECLARE_CLASS_INFO
public:
     NodeVisible(void);
     virtual ~NodeVisible(void);

     virtual bool init();
     virtual bool detect();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	bool _visible;
};


#endif
