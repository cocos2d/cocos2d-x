#ifndef __ACTIONS_H__
#define __ACTIONS_H__

#include "cocos2d.h"
#include "cocostudio/TriggerBase.h"


class  PlayMusic: public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     PlayMusic(void);
     virtual ~PlayMusic(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	 int  _tag;
	 std::string _comName;
	 int  _type;
};

class  TMoveTo: public cocostudio::BaseTriggerAction
{
	DECLARE_CLASS_INFO
public:
	TMoveTo(void);
	virtual ~TMoveTo(void);

	virtual bool init();
	virtual void done();
	virtual void serialize(const rapidjson::Value &val);
	virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Vector2 _pos;
};


class TMoveBy : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TMoveBy(void);
     virtual ~TMoveBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Vector2 _pos;
	bool _reverse;
};


class TRotateTo : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TRotateTo(void);
     virtual ~TRotateTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	float _deltaAngle;
};


class TRotateBy : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TRotateBy(void);
     virtual ~TRotateBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	float _deltaAngle;
	bool _reverse;
};


class TScaleTo : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TScaleTo(void);
     virtual ~TScaleTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Vector2 _scale;
};


class TScaleBy : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TScaleBy(void);
     virtual ~TScaleBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Vector2 _scale;
	bool _reverse;

};


class TSkewTo : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TSkewTo(void);
     virtual ~TSkewTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Vector2 _skew;
};


class TSkewBy : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TSkewBy(void);
     virtual ~TSkewBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Vector2 _skew;
	bool _reverse;
};


class TriggerState : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TriggerState(void);
     virtual ~TriggerState(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _id;
	int _state;
};

class ArmaturePlayAction : public cocostudio::BaseTriggerAction
{
	DECLARE_CLASS_INFO
public:
	ArmaturePlayAction(void);
	virtual ~ArmaturePlayAction(void);

	virtual bool init();
	virtual void done();
	virtual void serialize(const rapidjson::Value &val);
	virtual void removeAll();
private:
	int _tag;
	std::string _ComName;
	std::string _aniname;
};

#endif
