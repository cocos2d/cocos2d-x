#ifndef __ACTIONS_H__
#define __ACTIONS_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ExtensionMacros.h"


class  PlayMusic: public cocos2d::extension::BaseTriggerAction
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
	 int  _nTag;
	 std::string _comName;
	 int  _nType;
};

class  MoveTo: public cocos2d::extension::BaseTriggerAction
{
	DECLARE_CLASS_INFO
public:
	MoveTo(void);
	virtual ~MoveTo(void);

	virtual bool init();
	virtual void done();
	virtual void serialize(const rapidjson::Value &val);
	virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	cocos2d::CCPoint _pos;
};


class MoveBy : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     MoveBy(void);
     virtual ~MoveBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	cocos2d::CCPoint _pos;
	bool _bReverse;
};


class RotateTo : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     RotateTo(void);
     virtual ~RotateTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	float _fDeltaAngle;
};


class RotateBy : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     RotateBy(void);
     virtual ~RotateBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	float _fDeltaAngle;
	bool _bReverse;
};


class ScaleTo : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     ScaleTo(void);
     virtual ~ScaleTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	cocos2d::CCPoint _scale;
};


class ScaleBy : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     ScaleBy(void);
     virtual ~ScaleBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	cocos2d::CCPoint _scale;
	bool _bReverse;

};


class SkewTo : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     SkewTo(void);
     virtual ~SkewTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	cocos2d::CCPoint _skew;
};


class SkewBy : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     SkewBy(void);
     virtual ~SkewBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	cocos2d::CCPoint _skew;
	bool _bReverse;
};


class TriggerState : public cocos2d::extension::BaseTriggerAction
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
	int  _nID;
	int _nState;
};

class ArmaturePlayAction : public cocos2d::extension::BaseTriggerAction
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
	int _nTag;
	std::string _ComName;
	std::string _aniname;
};

#endif
