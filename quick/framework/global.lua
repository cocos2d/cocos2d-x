--------------------------------
-- @module global

--------------------------------
-- 定义一个作废的接口
-- @function [parent=#global] DEPRECATED

--------------------------------
-- 显示作废信息
-- @function [parent=#global] PRINT_DEPRECATED

--------------------------------
-- 打印调试信息
-- @function [parent=#global] printLog
-- @param string tag 调试信息的 tag
-- @param string fmt 调试信息格式
-- @param mixed ... 更多参数

--------------------------------
-- 输出 tag 为 ERR 的调试信息
-- @function [parent=#global] printError
-- @param string fmt 调试信息格式
-- @param mixed ... 更多参数

--------------------------------
-- 输出 tag 为 INFO 的调试信息
-- @function [parent=#global] printInfo
-- @param string fmt 调试信息格式
-- @param mixed ... 更多参数

--------------------------------
-- 输出值的内容
-- @function [parent=#global] dump
-- @param mixed value 要输出的值
-- @param string desciption 输出内容前的文字描述
-- @parma [integer nesting] 输出时的嵌套层级，默认为 3

--------------------------------
-- 输出格式化字符串
-- @function [parent=#global] printf
-- @param string fmt 输出格式
-- @param mixed ... 更多参数

--------------------------------
-- 检查并尝试转换为数值，如果无法转换则返回 0
-- @function [parent=#global] checknumber
-- @param mixed value 要检查的值
-- @param integer base 进制，默认为十进制
-- @return number#number ret (return value: number) 

--------------------------------
-- 检查并尝试转换为整数，如果无法转换则返回 0
-- @function [parent=#global] checkint
-- @param mixed value 要检查的值
-- @return integer#integer ret (return value: int) 

--------------------------------
-- 检查并尝试转换为布尔值，除了 nil 和 false，其他任何值都会返回 true
-- @function [parent=#global] checkbool
-- @param mixed value 要检查的值
-- @return boolean#boolean ret (return value: bool) 

--------------------------------
-- 检查值是否是一个表格，如果不是则返回一个空表格
-- @function [parent=#global] checktable
-- @param mixed value 要检查的值
-- @return table#table ret (return value: table) 

--------------------------------
-- 如果表格中指定 key 的值为 nil，或者输入值不是表格，返回 false，否则返回 true
-- @function [parent=#global] isset
-- @param table hashtable 要检查的表格
-- @param mixed key 要检查的键名
-- @return boolean#boolean ret (return value: bool) 

--------------------------------
-- 深度克隆一个值
-- @function [parent=#global] clone
-- @param mixed object 要克隆的值
-- @return mixed#mixed ret (return value: mixed) 

--------------------------------
-- 创建一个类
-- @function [parent=#global] class
-- @param string classname 类名
-- @param [mixed super] 父类或者创建对象实例的函数
-- @return table#table ret (return value: table) 

--------------------------------
-- 如果对象是指定类或其子类的实例，返回 true，否则返回 false
-- @function [parent=#global] iskindof
-- @param mixed obj 要检查的对象
-- @param string classname 类名
-- @return boolean#boolean ret (return value: bool) 

--------------------------------
-- 载入一个模块
-- @function [parent=#global] import
-- @param string moduleName 要载入的模块的名字
-- @param string currentModuleName 当前模块名
-- @return module#module 

--------------------------------
-- 将 Lua 对象及其方法包装为一个匿名函数
-- @function [parent=#global] handler
-- @param mixed obj Lua 对象
-- @param function method 对象方法
-- @return function#function ret (return value: function) 

--------------------------------
-- JSON 编码与解码
-- @function [parent=#global] safeLoad

--------------------------------
-- 私有方法
-- @function [parent=#global] checkArguments

return nil
