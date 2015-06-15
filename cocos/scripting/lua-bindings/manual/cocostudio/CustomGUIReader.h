#ifndef COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_CUSTOM_GUI_READER_H
#define COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_CUSTOM_GUI_READER_H

#include "cocostudio/WidgetReader/WidgetReader.h"

USING_NS_CC;

 /**
  * @addtogroup lua
  * @{
  */
namespace cocostudio
{
  /**
   * @~english
   * The CustomGUIReader is extended for the cocostudio::GUIReader to create the CustomGuiReader for the Lua.It make the developer can create Custom Widget in the Lua conveniently. 
   *
   * @~chinese
   * CustomGUIReader做为cocostudio::GUIReader扩展，可以使开发者在Lua层更方便的地创建自定义Widget。
   * @js NA
   */
    class CustomGUIReader : public Ref
    {
    public:
        /**@~english
         * Constructor of CustomGUIReader.
         * @~chinese 
         * CustomGUIReader的构造函数。
         * @lua NA
         */
        CustomGUIReader();
        /**@~english
         * Destructor of CustomGUIReader.
         * @~chinese 
         * CustomGUIReader的析构函数。
         * @lua NA
         */
        virtual ~CustomGUIReader();

        /**@~english
         * Create a CustomGUIReader object by the className, createFunc, setPropsFunc.
         *
         * @~chinese 
         * 通过className, createFunc, setPropsFunc创建一个CustomGUIReader对象。
         * 
         * @param className @~english The name of Custom Widget.
         * @~chinese 自定义Widget的名称。
         * @param createFunc @~english The reference id corresponding to the Lua function.
         * @~chinese 对应Lua函数的reference id。
         * @param setPropsFunc @~english The reference id corresponding to the Lua function.
         * @~chinese 对应Lua函数的reference id。
         * 
         * @return @~english a CustomGUIReader object.
         * @~chinese CustomGUIReader对象。
         */
        static CustomGUIReader* create(std::string &className, int createFunc, int setPropsFunc);

        /**@~english
         * Init a CustomGUIReader object by the className, createFunc, setPropsFunc.
         *
         * @~chinese 
         * 通过className, createFunc, setPropsFunc初始化CustomGUIReader对象。
         * 
         * @param className @~english The name of Custom widget.
         * @~chinese 自定义Widget的名称。
         * @param createFunc @~english The reference id corresponding to the Lua function.
         * @~chinese 对应Lua函数的reference id。
         * @param setPropsFunc @~english The reference id corresponding to the Lua function.
         * @~chinese 对应Lua函数的reference id。
         * 
         * @lua NA
         */
        void init(std::string &className, int createFunc, int setPropsFunc);

        /**@~english
         * Create a ref object by calling the Lua function that _createFunc corresponding to.
         *
         * @~chinese 
         * 通过调用_createFunc对应的Lua函数创建一个Ref对象。
         * 
         * @return @~english a Ref object.
         * @~chinese 一个Ref对象。
         * @lua NA
         */
        Ref* createInstance();

        /**@~english
         * Set properties of the Custom Widget named classtype by passing classType,the customOptions and the widget into the Lua stack as the parameters of Lua function that _setPropsFunc corresponding to.
         *
         * @~chinese 
         * 通过将classType，widget以及customOptions压入Lua栈作为Lua函数的参数，来设置名为classtype的自定义Widget的属性。
         * 
         * @param classType @~english The name of Custom Widget.
         * @~chinese 自定义Widget的名字。
         * @param classType @~english The customizable widget.
         * @~chinese 自定义Widget对象。
         * @param customOptions @~english The custom properties would be convered to the string. 
         * @~chinese 将被转化为字符串的自定义属性。
         * 
         * @lua NA
         */
        void setCustomProps(const std::string &classType, cocos2d::Ref *widget, const rapidjson::Value &customOptions);

    private:
        std::string _className;
        int _createFunc;
        int _setPropsFunc;
    };
}
// end group
/// @}



#endif
