/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __TRIGGERMNG_H__
#define __TRIGGERMNG_H__

#include "cocos2d.h"
#include "CocoStudio.h"

namespace cocostudio {

class TriggerObj;

class ArmatureMovementDispatcher : public cocos2d::Object
{
public:
	ArmatureMovementDispatcher(void);
	~ArmatureMovementDispatcher(void);
public:
	void addAnimationEventCallBack(cocos2d::Object*pTarget, SEL_MovementEventCallFunc mecf);
	void removeAnnimationEventCallBack(cocos2d::Object*pTarget, SEL_MovementEventCallFunc mecf);
	void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    
private:
	std::unordered_map<Object*, SEL_MovementEventCallFunc> *_mapEventAnimation;

};

class TriggerMng
{
public:
	TriggerMng(void);
	virtual ~TriggerMng(void);
	
public:
    static TriggerMng* getInstance();
    static void destroyInstance();
    static const char* triggerMngVersion();
    
public:
	void parse(const rapidjson::Value &root);
	void removeAll(void);
	cocos2d::Vector<TriggerObj*>* get(unsigned int event) const;
	TriggerObj* getTriggerObj(unsigned int id) const;
    bool add(unsigned int event, TriggerObj *pObj);
    bool remove(unsigned int event);
	bool remove(unsigned int event, TriggerObj *pObj);
	bool removeTriggerObj(unsigned int id);
    bool isEmpty(void) const;
    void addArmatureMovementCallBack(Armature *pAr, cocos2d::Object *pTarget, SEL_MovementEventCallFunc mecf);
	void removeArmatureMovementCallBack(Armature *pAr, cocos2d::Object *pTarget, SEL_MovementEventCallFunc mecf);
	void removeArmatureAllMovementCallBack(Armature *pAr);
	void removeAllArmatureMovementCallBack();

private:
    std::unordered_map<unsigned int, cocos2d::Vector<TriggerObj*>*> _eventTriggers;
    static TriggerMng *_sharedTriggerMng;
	std::unordered_map<unsigned int, TriggerObj*> _triggerObjs;
	std::unordered_map<Armature*, ArmatureMovementDispatcher*> *_movementDispatches;
};

}

#endif
