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

#include "CocoStudio.h"

namespace cocos2d {
class EventDispatcher;
class EventListener;
}

namespace cocostudio {

class TriggerObj;

 /** 
 @���� ArmatureMovementDispatcher
 @���� Armature����״̬�¼��ַ���
 @ϸ�� ��Armature������״̬���͸��������������ж������ж��붯������
 @�� ������
 */
class CC_STUDIO_DLL ArmatureMovementDispatcher : public cocos2d::Ref
{
public:
	ArmatureMovementDispatcher(void);
	~ArmatureMovementDispatcher(void);
public:
    /**
    @���� Ϊ���������������¼��ص�
    @���� pTarget ����������ָ��
    @���� mecf �ص�����
    @���� ��
    */
    void addAnimationEventCallBack(cocos2d::Ref*pTarget, SEL_MovementEventCallFunc mecf);
    /**
    @���� �Ƴ������������¼��ص�
    @���� pTarget ����������ָ��
    @���� mecf �ص�����
    @���� ��
    */
    void removeAnnimationEventCallBack(cocos2d::Ref*pTarget, SEL_MovementEventCallFunc mecf);
    /**
    @���� �ṩ��Armature�����¼��ص��ķ���
    @���� armature Armatureָ��
    @���� movementType �ƶ��¼�����
    @���� movementID ����ID
    @���� ��
    */
    void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    
private:
	std::unordered_map<cocos2d::Ref*, SEL_MovementEventCallFunc> *_mapEventAnimation;

};

 /** 
 @���� TriggerMng
 @���� ������ϵͳ������
 @ϸ�� �������cocos studio 1.x�༭���������ݹ����������������¼��ַ����������д���������������
 @�� ������
 */
class CC_STUDIO_DLL TriggerMng
{
public:
    /**
    @���� TriggerMng���캯��
    */
    TriggerMng(void);
    /**
    @���� TriggerMng��������
    */
    virtual ~TriggerMng(void);

public:
    /**
    @���� ��ȡTriggerMng����ָ��
    @���� TriggerMng����ָ��
    */
    static TriggerMng* getInstance();
    /**
    @���� ����TriggerMng����ָ��
    @���� ��
    */
    static void destroyInstance();
    /**
    @���� ����TriggerMng�汾
    @���� TriggerMng�汾���ַ���
    */
    static const char* triggerMngVersion();
    
public:
    /**
    @���� ����cocos studio 1.x������json���󣬹���������ϵͳ
    @���� root cocos studio 1.x������json����
    @���� ��
    */
    void parse(const rapidjson::Value &root);
    /**
    @���� ����cocos studio 1.x�����Ķ��������ݣ�����������ϵͳ
    @���� cocoLoader cocos studio 1.x�������������ݼ���������
    @���� cocoNode cocos studio 1.x��������������node����
    @���� ��
    */
    void parse(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode);
    /**
    @���� �Ƴ����д�����
    @���� ��
    */
    void removeAll(void);
    /**
    @���� ���ݴ������¼�id,��ȡ�󶨵����id�ϵ����д�����
    @���� event �������¼�id
    @���� �󶨵��¼�id�����д�����
    */
    cocos2d::Vector<TriggerObj*>* get(unsigned int event) const;
   /**
    @���� ���ݴ�����id,��ȡ������
    @���� id ������id
    @���� ��ȡ������
    */
    TriggerObj* getTriggerObj(unsigned int id) const;
    /**
    @���� ���ݴ�����ָ�룬�Ƴ�������
    @���� Obj ������ָ��
    @���� true�ɹ��Ƴ�������false
    */
    bool removeTriggerObj(TriggerObj *Obj);
    /**
    @���� ���ݴ�����id���Ƴ�������
    @���� id ������id
    @���� true�ɹ��Ƴ�������false
    */
    bool removeTriggerObj(unsigned int id);
    /**
    @���� �Ƿ�Ϊû�д�����
    @���� true û�д�����������false
    */
    bool isEmpty(void) const;

    /**
    @���� Ϊ�����������Armature�¼��ص����Ӷ���Armature���¼�����������������Ҳ���Ի��
    @���� pAr Armature
    @���� pTarget ����������ָ��
    @���� mecf �ص�����
    @���� ��
    */
    void addArmatureMovementCallBack(Armature *pAr, cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);
    /**
    @���� �Ƴ�����Armature�Ĵ����������¼��ص�
    @���� pAr Armature
    @���� pTarget ����������ָ��
    @���� mecf �ص�����
    @���� ��
    */
    void removeArmatureMovementCallBack(Armature *pAr, cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);
    /**
    @���� �Ƴ��󶨵�ָ��Armature�Ĵ������¼��ص�
    @���� pAr Armature
    @���� ��
    */
    void removeArmatureAllMovementCallBack(Armature *pAr);
    /**
    @���� �Ƴ��󶨵�����Armature�Ĵ������¼��ص�
    @���� pAr Armature
    @���� ��
    */
    void removeAllArmatureMovementCallBack();
    /**
    @���� �ַ��������¼�
    @���� tEvent �������¼�
    @���� ��
    */
    void dispatchEvent(cocos2d::EventCustom* tEvent);
    /**
    @���� �Ƴ��������¼�������
    @���� listener ������������
    @���� ��
    */
    void removeEventListener(cocos2d::EventListener* listener);
   /**
    @���� ���Ӵ������¼������������ƶ��������ȼ�
    @���� listener ������������
    @���� fixedPriority �������������������ȼ�
    @���� ��
    */
    void addEventListenerWithFixedPriority(cocos2d::EventListener* listener, int fixedPriority);
private:
    /**
    @���� ����cocos studio 1.x�����Ķ����ƶ���ת��Ϊjson��������lua����
    @���� document json����
    @���� pCocoLoader cocos studio 1.x�������������ݼ���������
    @���� pCocoNode cocos studio 1.x��������������node����
    @���� ��
    */
    void buildJson(rapidjson::Document &document, cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode);

private:
    static TriggerMng *_sharedTriggerMng;
    std::unordered_map<unsigned int, TriggerObj*> _triggerObjs;
    std::unordered_map<Armature*, ArmatureMovementDispatcher*> *_movementDispatches;
    cocos2d::EventDispatcher* _eventDispatcher;  ///< event dispatcher used to dispatch all kinds of events
};

}

#endif
