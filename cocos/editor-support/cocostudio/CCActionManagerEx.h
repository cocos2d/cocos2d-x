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

#ifndef __ActionMANAGER_H__
#define __ActionMANAGER_H__

#include "cocostudio/CCActionObject.h"
#include "cocostudio/DictionaryHelper.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {
    
class CocoLoader;
struct stExpCocoNode;

class CC_STUDIO_DLL ActionManagerEx:public cocos2d::Ref
{
public:

	/**
    * @~english Default constructor.
    * @~chinese 默认构造函数.
    * @js ctor
	*/
	ActionManagerEx();

	/**
    * @~english Default destructor.
    * @~chinese 默认析构函数.
    * @js NA
	* @lua NA
	*/
	virtual ~ActionManagerEx();

	/**
	* @~english Gets the static instance of ActionManager.
    * @~chinese 获取ActionManager的静态实例.
    * @js getInstance
	* @lua getInstance
	*/
	static ActionManagerEx* getInstance();

	/**
	* @~english Destroy ActionManager static instance.
    * @~chinese 释放ActionManager的静态实例.
    * @js purge
	* @lua destroyActionManager
	*/
	static void destroyInstance();

	/**
	* @~english Gets an ActionObject with a name.
    * @~chinese 通过名称获取动作对象.
    *
	* @param jsonName  @~english UI file name @~chinese UI描述文件名称
	*
	* @param actionName  @~english action name in the UI file. @~chinese 描述文件中的动作名称
	*
	* @return  @~english ActionObject which named as the param name. @chinese 符合参数名称的动作对象
	*/
	ActionObject* getActionByName(const char* jsonName, const char* actionName);

	/**
	* @~english Play an Action with a name.
    * @~chinese 播放指定名称的动作.
    *
	* @param jsonName   @~english UI file name @~chinese UI描述文件名称
	*
	* @param actionName  @~english action name in the UI file. @~chinese UI描述文件中保存的动作名称.
	*
	* @return  @~english ActionObject which named as the param name. @chinese 符合参数名称的动作对象
	*/
	ActionObject* playActionByName(const char* jsonName,const char* actionName);

	/**
    * @~english Play an Action with a name.
    * @~chinese 播放指定名称的动作.
    *
	* @param jsonName  @~english UI file name @~chinese UI描述文件名称
	*
	* @param actionName  @~english action name in the UI file. @~chinese UI描述文件中保存的动作名称.
	*
	* @param func  @~english ui action call back @~chinese UI动作回调函数
    *
<<<<<<< HEAD
    * @return  @~english ActionObject which named as the param name. @chinese 符合参数名称的动作对象
=======
    * @param actionName  action name in the UIfile.
    *
    * @return  ActionObject which named as the param name
>>>>>>> e6022b2a925b6d21249df71fc76a250ce05d579d
    */
	ActionObject* playActionByName(const char* jsonName,const char* actionName, cocos2d::CallFunc* func);

	/**
	* Stop an Action with a name.
    * @~chinese 停止播放指定名称的动作.
    *
	* @param jsonName  @~english UI file name @~chinese UI描述文件名称
	*
	* @param actionName  @~english action name in the UI file. @~chinese UI描述文件中保存的动作名称.
	*
    * @return  @~english ActionObject which named as the param name. @chinese 符合参数名称的动作对象
    */
	ActionObject* stopActionByName(const char* jsonName,const char* actionName);

	/**
    * @~english init properties with json dictionary
    * @~chinese 使用json字典初始化属性值
    */
	void initWithDictionary(const char* jsonName,const rapidjson::Value &dic, Ref* root);
    /**
    * @~english init properties with binary file
    * @~chinese 使用二进制数据初始化属性值
    */
    void initWithBinary(const char* file, Ref* root, CocoLoader* cocoLoader, stExpCocoNode*	pCocoNode);

	/**
	* @~english Release all actions.
	* @~chinese 释放全部动作.
	*/
	void releaseActions();

protected:
	std::unordered_map<std::string, cocos2d::Vector<ActionObject*>> _actionDic;
};

}

#endif
