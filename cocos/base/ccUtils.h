/****************************************************************************
Copyright (c) 2010      cocos2d-x.org
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
#ifndef __SUPPORT_CC_UTILS_H__
#define __SUPPORT_CC_UTILS_H__

#include <vector>
#include <string>
#include "2d/CCNode.h"
#include "base/ccMacros.h"

/** @file ccUtils.h
 * @~english Misc free functions
 * @~chinese Misc免费函数集
 */

NS_CC_BEGIN
/*
* ccNextPOT function is licensed under the same license that is used in Texture2D.m.
*/

/**
 * @~english Returns the Next Power of Two value.
 * Examples:
 * - If "value" is 15, it will return 16.
 * - If "value" is 16, it will return 16.
 * - If "value" is 17, it will return 32.
 *
 * @~chinese 返回下一个2的n次方数字
 * 例子:
 * ——如果value是15,它将返回16。
 * ——如果value是16,它将返回16。
 * ——如果value是17,它将返回32。
 *
 * @param value @~english The value to get next power of two.
 * @~chinese 需要获取到下一个2的n次方数字
 * @return @~english Returns the next power of two value.
 * @~chinese 2的n次方
 * @since v0.99.5
*/
int ccNextPOT(int value);

namespace utils
{
    /**
     * @~english Capture the entire screen.
     * To ensure the snapshot is applied after everything is updated and rendered in the current frame,
     * we need to wrap the operation with a custom command which is then inserted into the tail of the render queue.
     * @~chinese 捕获整个屏幕。
     * 确保应用快照在所有节点都更新并呈现在当前帧之后,
     * 我们需要包装操作使用一个自定义的命令然后插入到渲染队列的尾部。
     *
     * @param afterCaptured @~english specify the callback function which will be invoked after the snapshot is done.
     * @~chinese 指定快照后的回调函数。
     *
     * @param filename @~english specify a filename where the snapshot is stored. This parameter can be either an absolute path or a simple
     * base filename ("hello.png" etc.), don't use a relative path containing directory names.("mydir/hello.png" etc.).
     * @~chinese 指定一个快照存储的文件名。这个参数可以是一个绝对路径或
     * 一个简单的基本文件名("hello.png" etc.),不要使用相对路径的目录名("mydir/hello.png" etc.).
     * @since v3.2
     */
    void CC_DLL captureScreen(const std::function<void(bool, const std::string&)>& afterCaptured, const std::string& filename);
    
    /**
     * @~english Find children by name, it will return all child that has the same name.
     * It supports c++ 11 regular expression. It is  a helper function of `Node::enumerateChildren()`.
     * You can refer to `Node::enumerateChildren()` for detail information.
     *
     * @~chinese 查找子节点的name,它将返回所有的相同名字的子节点。
     * 它支持c++11正则表达式。这是一个“Node::enumerateChildren()”
     * 你可以参考 Node::enumerateChildren
     * 
     * @param node @~english The node to find
     * @~chinese 需要找的节点
     * @param name @~english The name to search for, it supports c++ 11 expression
     * @~chinese 搜索名称,支持c++ 11表达式
     *
     * @return @~english Array of Nodes that matches the name
     * @~chinese 名称相匹配的子节点数组
     * @since v3.2
     */
    std::vector<Node*> CC_DLL findChildren(const Node &node, const std::string &name);
    
    /**
     * @~english Same to ::atof, but strip the string, remain 7 numbers after '.' before call atof.
     * Why we need this? Because in android c++_static, atof ( and std::atof ) is unsupported for numbers have long decimal part and contain
     * several numbers can approximate to 1 ( like 90.099998474121094 ), it will return inf. This function is used to fix this bug.
     * @~chinese 和::atof类似,但带字符串,在调用atof之前保持小数点后7位数。
     * 为什么我们需要这个?因为在android c++ _static atof(std::atof) 是不支持的一部分比较长的数字
     * 几个数字可以近似为1( 像 90.099998474121094 ), 原来它将会返回inf. 这个函数是用来修正这个错误。
     * @param str @~english The string be to converted to double.
     * @~chinese 将字符转换为双精度数.
     * @return @~english Returns converted value of a string.
     * @~chinese 返回转换后的字符串。
     */
    double CC_DLL atof(const char* str);

    /**
     * @~english Get current exact time, accurate to nanoseconds.
     * @~chinese 得到当前确切时间,精确到纳秒。
     *
     * @return @~english Returns the time in seconds since the Epoch.
     * @~chinese 返回Epoch以来的时间间隔,以秒为单位。
     */
    double CC_DLL gettime();

    /**@~english
     * Get current time in milliseconds, accurate to nanoseconds
     * @~chinese 获取毫秒级时间
     *
     * @return @~english Returns the time in milliseconds since the Epoch.
     * @~chinese 返回从公元纪年开始的毫秒时间
     */
    long long CC_DLL getTimeInMilliseconds();

    /**
     * @~english
     * Calculate union of bounding box of a node and its children.
     * @~chinese 计算节点及其子节点的边界框。
     *
     * @return @~english Returns union of bounding box of a node and its children.
     * @~chinese 返回一个节点以及其子节点的边界框
     */
    Rect CC_DLL getCascadeBoundingBox(Node *node);
}

NS_CC_END

#endif // __SUPPORT_CC_UTILS_H__
