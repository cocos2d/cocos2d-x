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

#ifndef __CC_EXTENTIONS_CCCOMATTRIBUTE_H__
#define __CC_EXTENTIONS_CCCOMATTRIBUTE_H__

#include "CCComBase.h"
#include "2d/CCComponent.h"
#include "base/CCValue.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

/** 
 * @class ComAttribute
 * @brief @~english ComAttribute.
 * @~chinese �Զ����������.
 * @details @~english Store and access data by key-value, and load exporting data of cocos studio 1.x Scene Editor.
 * @~chinese ��key-value��ֵ�Է�ʽ�洢���ȡ����, ����cocos studio 1.x�����༭������������.
*/
class CC_STUDIO_DLL ComAttribute : public cocos2d::Component
{
    DECLARE_CLASS_COMPONENT_INFO
public:
    /**
     * @brief @~english ComAttribute constructor.
     * @~chinese �Զ������Թ��캯����
     * @js ctor
     */
    ComAttribute(void);
    /**
     * @brief @~english ComAttribute destructor.
     * @~chinese �Զ�����������������
     * @js NA
     * @lua NA
     */
    virtual ~ComAttribute(void);
    
public:
    /**
     * @brief @~english Allocates and initializes a ComAttribute.
     * @~chinese ���䲢�ҳ�ʼ���Զ��������
     * @return @~english A initialized ComAttribute which is marked as "autorelease".
     * @~chinese һ����ʼ�����Զ���������ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�)��
     */
    static ComAttribute* create(void);

    /**
     * @brief @~english Initialize a ComAttribute.
     * @~chinese ��ʼ���Զ��������
     * @return @~english true initialize successfully false failed to initialize.
     * @~chinese true ��ʼ���ɹ�������false��
     */
    virtual bool init() override;

    /**
     * @brief @~english Deserialization export data of cocos studio 1.x scene editor.
     * @~chinese �����л�cocos studio 1.x �����༭�����������ݡ�
     * @param r @~english SerData object point.
     * @~chinese SerData����ָ�롣
     * @return @~english true deserialize successfully false failed to deserialize.
     * @~chinese true �����л��ɹ�������false��
     */
    virtual bool serialize(void* r) override;

    /**
     * @brief @~english Set int value for key.
     * @~chinese ����������ΪΪkey������Ϊint����ֵ��
     * @param key @~english the key to set.
     * @~chinese ��Ҫ���õ�key��
     * @param value @~english a int value to set to the key.
     * @~chinese ����Ϊint����ֵ��
     */
    void setInt(const std::string& key, int value);

    /**
     * @brief @~english Set float value for key.
     * @~chinese ����������ΪΪkey������Ϊfloat����ֵ��
     * @param key @~english the key to set.
     * @~chinese ��Ҫ���õ�key��
     * @param value @~english a float value to set to the key.
     * @~chinese ����Ϊfloat����ֵ��
     */
    void setFloat(const std::string& key, float value);

    /**
     * @brief @~english Set bool value for key.
     * @~chinese ����������ΪΪkey������Ϊbool����ֵ��
     * @param key @~english the key to set.
     * @~chinese ��Ҫ���õ�key��
     * @param value @~english a bool value to set to the key.
     * @~chinese ����Ϊbool����ֵ��
     */
    void setBool(const std::string& key, bool value);

    /**
     * @brief @~english Set string value for key.
     * @~chinese ����������ΪΪkey������Ϊstring����ֵ��
     * @param key @~english the key to set.
     * @~chinese ��Ҫ���õ�key��
     * @param value @~english a string value to set to the key.
     * @~chinese ����Ϊstring����ֵ��
     */
    void setString(const std::string& key, const std::string& value);

    /**
     * @brief @~english Get int value by key, if the key doesn't exist, will return passed default value.
     * @~chinese ��ȡָ�� key ������ֵ����� key �����ڣ��򷵻�ָ���� def��
     * @param key @~english the key to get value.
     * @~chinese ��Ҫ��ȡ��key��
     * @param def @~english The default value to return if the key doesn't exist.
     * @~chinese ���ص�Ĭ��ֵ�����key�����ڣ��򷵻ش�ֵ��
     * @return @~english int value of the key.
     * @~chinese key������ֵ��
     */
    int getInt(const std::string& key, int def = 0) const;

    /**
     * @brief @~english Get float value by key, if the key doesn't exist, will return passed default value.
     * @~chinese ��ȡָ�� key ���ַ�������� key �����ڣ��򷵻�ָ���� def��
     * @param key @~english the key to get value.
     * @~chinese ��Ҫ��ȡ��key��
     * @param def @~english the default value to return if the key doesn't exist.
     * @~chinese ���ص�Ĭ��ֵ�����key�����ڣ��򷵻ش�ֵ��
     * @return @~english float value of the key.
     * @~chinese key��floatֵ��
     */
    float getFloat(const std::string& key, float def = 0.0f) const;

    /**
     * @brief @~english Get bool value by key, if the key doesn't exist, will return passed default value.
     * @~chinese ��ȡָ�� key ���ַ�������� key �����ڣ��򷵻�ָ���� def��
     * @param key @~english the key to get value.
     * @~chinese ��Ҫ��ȡ��key��
     * @param def @~english the default value to return if the key doesn't exist.
     * @~chinese ���ص�Ĭ��ֵ�����key�����ڣ��򷵻ش�ֵ��
     * @return @~english bool value of the key.
     * @~chinese key��boolֵ��
     */
    bool getBool(const std::string& key, bool def = false) const;

    /**
     * @brief @~english Get string value by key, if the key doesn't exist, will return passed default value.
     * @~chinese ��ȡָ�� key ���ַ�������� key �����ڣ��򷵻�ָ���� def��
     * @param key @~english the key to get value.
     * @~chinese ��Ҫ��ȡ��key��
     * @param def @~english the default value to return if the key doesn't exist.
     * @~chinese ���ص�Ĭ��ֵ�����key�����ڣ��򷵻ش�ֵ��
     * @return @~english string value of the key.
     * @~chinese key��stringֵ��
     */
    std::string getString(const std::string& key, const std::string& def = "") const;

     /**
     * @brief @~english Parse export json data of cocos studio 1.x Scene Editor and assign to _doc.
     * @~chinese ����cocos studio 1.x �����༭������json���ݣ��ж�json����Ч�ԣ���json����_doc��ֵ��
     * @param jsonFile @~english json file path.
     * @~chinese json·����
     * @return @~english true parse successfully, false failed to parse.
     * @~chinese true �����ɹ�������false��
     */
    bool parse(const std::string &jsonFile);
private:
   cocos2d::ValueMap _dict;
   rapidjson::Document _doc;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
