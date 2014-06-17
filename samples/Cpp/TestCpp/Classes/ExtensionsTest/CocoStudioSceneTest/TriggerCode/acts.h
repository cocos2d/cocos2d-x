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
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
     virtual void removeAll();
private:
	 int  _nTag;
	 std::string _comName;
	 int  _nType;
};

class  TMoveTo: public cocos2d::extension::BaseTriggerAction
{
	DECLARE_CLASS_INFO
public:
	TMoveTo(void);
	virtual ~TMoveTo(void);

	virtual bool init();
	virtual void done();
	virtual void serialize(const rapidjson::Value &val);
	virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
	virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	cocos2d::CCPoint _pos;
};


class TMoveBy : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TMoveBy(void);
     virtual ~TMoveBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	cocos2d::CCPoint _pos;
	bool _bReverse;
};


class TRotateTo : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TRotateTo(void);
     virtual ~TRotateTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	float _fDeltaAngle;
};


class TRotateBy : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TRotateBy(void);
     virtual ~TRotateBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	float _fDeltaAngle;
	bool _bReverse;
};


class TScaleTo : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TScaleTo(void);
     virtual ~TScaleTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	cocos2d::CCPoint _scale;
};


class TScaleBy : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TScaleBy(void);
     virtual ~TScaleBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	cocos2d::CCPoint _scale;
	bool _bReverse;

};


class TSkewTo : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TSkewTo(void);
     virtual ~TSkewTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
     virtual void removeAll();
private:
	int  _nTag;
	float _fDuration;
	cocos2d::CCPoint _skew;
};


class TSkewBy : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TSkewBy(void);
     virtual ~TSkewBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
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
	 virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
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
	virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
	virtual void removeAll();
private:
	int _nTag;
	std::string _comName;
	std::string _aniname;
};

#endif
