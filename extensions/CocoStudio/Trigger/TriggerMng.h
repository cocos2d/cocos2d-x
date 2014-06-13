/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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
#include "ExtensionMacros.h"
#include "../Json/DictionaryHelper.h"
#include "../Json/CocoLoader.h"
#include "../Armature/CCArmature.h"

NS_CC_EXT_BEGIN

class TriggerObj;

class CC_EX_DLL ArmatureMovementDispatcher : public CCObject
{
public:
	ArmatureMovementDispatcher(void);
	~ArmatureMovementDispatcher(void);
public:
	void addAnimationEventCallBack(CCObject*pTarget, SEL_MovementEventCallFunc mecf);
	void removeAnnimationEventCallBack(CCObject*pTarget, SEL_MovementEventCallFunc mecf);
	void animationEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
	std::map<CCObject*, SEL_MovementEventCallFunc> *_mapEventAnimation;

};

class CC_EX_DLL TriggerMng
{
public:
	TriggerMng(void);
	virtual ~TriggerMng(void);
	
public:
    static TriggerMng* getInstance();
    static const char* triggerMngVersion();
    void destroyInstance();
    
public:
	void parse(const rapidjson::Value &root);
	void parse(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);

	void removeAll(void);
	CCArray* get(unsigned int event) const;
	TriggerObj* getTriggerObj(unsigned int id) const;
    bool add(unsigned int event, TriggerObj *pObj);
    bool remove(unsigned int event);
	bool remove(unsigned int event, TriggerObj *pObj);
	bool removeTriggerObj(unsigned int id);
    bool isEmpty(void) const;
    void addArmatureMovementCallBack(CCArmature *pAr, CCObject *pTarget, SEL_MovementEventCallFunc mecf);
	void removeArmatureMovementCallBack(CCArmature *pAr, CCObject *pTarget, SEL_MovementEventCallFunc mecf);
	void removeArmatureAllMovementCallBack(CCArmature *pAr);
	void removeAllArmatureMovementCallBack();
private:
    void alloc(void);
	void buildJson(rapidjson::Document &document, cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
private:
    CCDictionary *_eventTriggers;
    static TriggerMng *_sharedTriggerMng;
	CCDictionary *_triggerObjs;
	std::map<CCArmature*, ArmatureMovementDispatcher*> *_movementDispatches;
};

NS_CC_EXT_END

#endif
