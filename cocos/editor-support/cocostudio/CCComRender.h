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

#ifndef __CC_EXTENTIONS_CCCOMRENDER_H__
#define __CC_EXTENTIONS_CCCOMRENDER_H__

#include "CCComBase.h"
#include "2d/CCComponent.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

/** 
 * @class ComRender
 * @brief @~english ComRender.
 * @~chinese ��Ⱦ���.
 * @details @~english Package render the target object of cocos2d-x, to ensure consistency component implementation.
 * @~chinese ��Ⱦ��� ��װ���ص��������Ⱦ����,ȷ�����ʵ�ֵ�һ����.
*/
class CC_STUDIO_DLL ComRender : public cocos2d::Component
{
    DECLARE_CLASS_COMPONENT_INFO
CC_CONSTRUCTOR_ACCESS:
    /**
     * @brief @~english ComRender constructor.
     * @~chinese ��Ⱦ������캯����
     * @js ctor
     */
    ComRender(void);

    /**
    @���� ��Ⱦ������캯��
    @���� node ��װ��Ⱦ����ָ��
    @���� comName ��Ⱦ�������
    */
    /**
     * @brief @~english ComRender constructor.
     * @~chinese ��Ⱦ������캯����
     * @param node @~english Node point 
     * @~chinese ��Ⱦ����ָ��
     * @param comName @~english component name 
     * @~chinese �������
     * @js ctor
     */
    ComRender(cocos2d::Node *node, const char *comName);

    /**
     * @brief @~english ComRender destructor.
     * @~chinese ��Ⱦ�������������
     * @js NA
     * @lua NA
     */
    virtual ~ComRender(void);
    
public:
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
     * @brief @~english deserialization export data of cocos studio 1.x scene editor.
     * @~chinese �����л�cocos studio 1.x �����༭�����������ݡ�
     * @param r @~english SerData object point.
     * @~chinese SerData����ָ�롣
     * @return @~english true deserialize successfully false failed to deserialize.
     * @~chinese true �����л��ɹ�������false��
     */
    virtual bool serialize(void* r) override;

    /**
     * @brief @~english get Node point.
     * @~chinese ��ȡ��Ⱦ����ָ�롣
     */
    virtual cocos2d::Node* getNode();

    /**
     * @brief @~english set Node point.
     * @~chinese ������Ⱦ�����װ����Ⱦ����ָ�롣
     */
    virtual void setNode(cocos2d::Node *node);

    /**
     * @brief @~english Allocates and initializes a ComRender.
     * @~chinese ���䲢�ҳ�ʼ����Ⱦ�����
     * @return @~english A initialized ComRender which is marked as "autorelease".
     * @~chinese һ����ʼ�����Զ���������ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�)��
     */
    static ComRender* create(void);

    /**
     * @brief @~english Allocates and initializes a ComRender.
     * @~chinese ���䲢�ҳ�ʼ����Ⱦ�����
     * @param node @~english Node point 
     * @~chinese ��Ⱦ����ָ��
     * @param comName @~english component name 
     * @~chinese �������
     * @return @~english A initialized ComRender which is marked as "autorelease".
     * @~chinese һ����ʼ�����Զ���������ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�)��
     */
    static ComRender* create(cocos2d::Node *node, const char *comName);
private:
     /**
     * @brief @~english Parse export json data of cocos studio 1.x Scene Editor and assign to doc.
     * @~chinese ����cocos studio 1.x �����༭������json���ݣ��ж�json����Ч�ԣ���json����doc��ֵ��
     * @param fileName @~english json file path.
     * @~chinese json·����
     * @param doc @~english json data object
     * @~chinese json���ݶ���
     * @return @~english true parse successfully, false failed to parse.
     * @~chinese true �����ɹ�������false��
     */
    bool readJson(const std::string &fileName, rapidjson::Document &doc);

private:
    cocos2d::Node *_render;
};

}
#endif  // __FUNDATION__CCCOMPONENT_H__
