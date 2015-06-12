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

#ifndef __CC_EXTENTIONS_CCCOMCONTROLLER_H__
#define __CC_EXTENTIONS_CCCOMCONTROLLER_H__

#include "CCComBase.h"
#include "cocostudio/CCInputDelegate.h"
#include "cocostudio/CocosStudioExport.h"
#include "2d/CCComponent.h"

namespace cocostudio {
/** 
 * @class ComController
 * @brief @~english ComController.
 * @~chinese �߼����.
 * @details @~english you can get input and calling each frame when attach ComController component.
 * @~chinese ʵ�ֶ����߼�����������Ի�ȡ�����Լ�ÿ֡����.
*/
class CC_STUDIO_DLL ComController : public cocos2d::Component, public InputDelegate
{

    DECLARE_CLASS_COMPONENT_INFO
public:
    /**
     * @brief @~english ComController constructor.
     * @~chinese �߼�������캯����
     * @js ctor
     */
    ComController(void);
    
public:
    /**
     * @brief @~english ComController destructor.
     * @~chinese �߼��������������
     * @js NA
     * @lua NA
     */
    virtual ~ComController(void);

    /**
     * @brief @~english Initialize a ComController.
     * @~chinese ��ʼ���߼������
     * @return @~english true initialize successfully false failed to initialize.
     * @~chinese true ��ʼ���ɹ�������false��
     */
    virtual bool init() override;

    /**
     * @brief @~english Event callback that is invoked every time when Node enters the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition starts.
     * During onEnter you can't access a "sister/brother" node.
     * If you override onEnter, you shall call its parent's one, e.g., Node::onEnter().
     * @~chinese ÿ�ε�Node���롰stage��ʱ�ŵ����¼��ص���
     * ���Node���롰stage��״̬ʱ������һ��ת����transition��,��ô�¼����������ת����ʼ��ʱ�򱻵��á�
     * ��onEnter�����У��㲻�ܹ����롰sister/brother�����ýڵ㡣
     * �������д��onEnter��������Ӧ�õ������ĸ��࣬e.g., Node::onEnter().
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;

    /**
     * @brief @~english Event callback that is invoked every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
     * @~chinese ÿ�ε�Node�뿪��stage��ʱ�ŵ����¼��ص���
     * ���Node�뿪��stage��״̬ʱ������һ��ת����transition��, ��ô�¼����������ת��������ʱ�򱻵��á�
     * ��onEnter���������㲻�ܹ�����һ�����ýڵ㡣
     * �������дonExit, ��Ӧ�õ������ĸ���, e.g., Node::onExit().
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;

    /**
     * @~english Schedules the "update" method.
     *
     * It will use the order number 0. This method will be called every frame.
     * Scheduled methods with a lower order value will be called before the ones that have a higher order value.
     * Only one "update" method could be scheduled per node.
     * @~chinese ����"update"������
     *
     * �������ȼ�������0���������������ÿһ֡�������á�
     * ӵ�н�С������ֵ�ĵ��ȷ�����������ӵ�ýϴ�������ֵ�ķ���֮ǰ�����á�
     * ÿһ���ڵ�ֻ��һ"update"�ܹ�������(�㲻�ܹ���2����update��ѡ����)��
     * @lua NA
     */
    virtual void update(float delta) override;

    /** 
     * @brief @~english Returns whether or not the ComAudio is enabled.
     * @~chinese ������������Ƿ����á�
     * @return @~english Whether or not the ComAudio is enabled. 
     * @~chinese ��������Ƿ����á�
     */
    virtual bool isEnabled() const override;

    /**  
     * @brief @~english enables or disables the ComAudio.
     * @~chinese ���û�������������
     * @param enabled @~english true enable the menu ComAudio, false disabled the ComAudio. 
     * @~chinese true������������� false���������������
     */
    virtual void setEnabled(bool b) override;

    /**
     * @brief @~english Allocates and initializes a create.
     * @~chinese ���䲢�ҳ�ʼ���߼������
     * @return @~english A initialized ComController which is marked as "autorelease".
     * @~chinese һ����ʼ�����߼�������ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�)��
     */
    static ComController* create(void);
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
