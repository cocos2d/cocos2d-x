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

#ifndef __TRIGGEROBJ_H__
#define __TRIGGEROBJ_H__

#include "CocoStudio.h"
#include "base/CCVector.h"

namespace cocos2d {
class EventListenerCustom;
}

namespace cocostudio {

 /** 
 @���� BaseTriggerCondition
 @���� ��������������
 @ϸ�� �����ж��Լ���cocos studio 1.x�����Ķ�������json���ݷ����л�
 @�� ������
 */
class CC_STUDIO_DLL BaseTriggerCondition : public cocos2d::Ref
{
protected:
    /**
    @���� BaseTriggerCondition���캯��
    */
    BaseTriggerCondition(void);
public:
    /**
    @���� BaseTriggerCondition��������
    */
    virtual ~BaseTriggerCondition(void);
    /**
    @���� ��ʼ������������
    @���� true ��ʼ���ɹ�������false
    */
    virtual bool init();
    /**
    @���� �����������ж�
    @���� true �����ɹ�������false
    */
    virtual bool detect();
    /**
    @���� ����cocos studio 1.x������json�������л�
    @���� val json����
    @���� ��
    */
    virtual void serialize(const rapidjson::Value &val);
    /**
    @���� ����cocos studio 1.x�����Ķ����ƶ������л�
    @���� cocoLoader cocos studio 1.x�������������ݼ���������
    @���� cocoNode cocos studio 1.x��������������node����
    @���� ��
    */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);
    /**
    @���� ������������ɾ����ʱ����ã��������������������Դ�ͷŵ�����
    @���� ��
    */
    virtual void removeAll();
};

 /** 
 @���� BaseTriggerAction
 @���� ��������������
 @ϸ�� ����ִ���Լ���cocos studio 1.x�����Ķ�������json���ݷ����л�
 @�� ������
 */
class CC_STUDIO_DLL BaseTriggerAction : public cocos2d::Ref
{
protected:
    /**
    @���� BaseTriggerAction��������
    */
    BaseTriggerAction(void);
public:
    /**
    @���� BaseTriggerAction��������
    */
    virtual ~BaseTriggerAction(void);
    /**
    @���� ��ʼ������������
    @���� true ��ʼ���ɹ�������false
    */
    virtual bool init();
    /**
    @���� ����������ִ��
    @���� ��
    */
    virtual void done();
    /**
    @���� ����cocos studio 1.x������json�������л�
    @���� val json����
    @���� ��
    */
    virtual void serialize(const rapidjson::Value &val);
    /**
    @���� ����cocos studio 1.x�����Ķ����ƶ������л�
    @���� cocoLoader cocos studio 1.x�������������ݼ���������
    @���� cocoNode cocos studio 1.x��������������node����
    @���� ��
    */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);
    /**
    @���� ������������ɾ����ʱ����ã��������������������Դ�ͷŵ�����
    @���� ��
    */
    virtual void removeAll();
};

 /** 
 @���� TriggerObj
 @���� ����������
 @ϸ�� ����������������⣬����ִ���Լ���cocos studio 1.x�����Ķ�������json���ݷ����л�
 @�� ������
 */
class CC_STUDIO_DLL TriggerObj : public cocos2d::Ref
{
public:
    /**
    @���� TriggerObj���캯��
    */
    TriggerObj(void);
    /**
    @���� TriggerObj��������
    */
    virtual ~TriggerObj(void);
    /**
    @���� ��ʼ������������
    @���� true ��ʼ���ɹ�������false
    */
    virtual bool init();
   /**
    @���� ���������� 
    @���� ����������
    */
    static TriggerObj* create(void);
    /**
    @���� �����������ж�
    @���� true �����ɹ�������false
    */
    virtual bool detect();
    /**
    @���� ����������ִ��
    @���� ��
    */
    virtual void done();
    /**
    @���� ��������ɾ����ʱ����ã��������������������Դ�ͷŵ�����
    @���� ��
    */
    virtual void removeAll();
    /**
    @���� ����cocos studio 1.x������json�������л�
    @���� val json����
    @���� ��
    */
    virtual void serialize(const rapidjson::Value &val);
    /**
    @���� ����cocos studio 1.x�����Ķ����ƶ������л�
    @���� cocoLoader cocos studio 1.x�������������ݼ���������
    @���� cocoNode cocos studio 1.x��������������node����
    @���� ��
    */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);
    /**
    @���� ��ȡ������Ψһid
    @���� ������Ψһid
    */
    unsigned int getId();
    /**
    @���� ���ô������Ƿ����
    @���� enabled trueΪ���ã�falseΪ������
    @���� ��
    */
    void setEnabled(bool enabled);
  
private:
    cocos2d::Vector<BaseTriggerCondition*> _cons;
    cocos2d::Vector<BaseTriggerAction*> _acts;
    unsigned int _id;
    bool _enabled;
    cocos2d::Vector<cocos2d::EventListenerCustom*> _listeners;
};

}

#endif


