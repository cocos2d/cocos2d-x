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
Misc free functions
*/

NS_CC_BEGIN
/*
ccNextPOT function is licensed under the same license that is used in Texture2D.m.
*/

/** Returns the Next Power of Two value.

Examples:
- If "value" is 15, it will return 16.
- If "value" is 16, it will return 16.
- If "value" is 17, it will return 32.
@param value The value to get next power of two.
@return Returns the next power of two value.
@since v0.99.5
*/

int ccNextPOT(int value);

class Sprite;
class Image;

namespace utils
{
    /** Capture the entire screen.
     * To ensure the snapshot is applied after everything is updated and rendered in the current frame,
     * we need to wrap the operation with a custom command which is then inserted into the tail of the render queue.
     * @param afterCaptured specify the callback function which will be invoked after the snapshot is done.
     * @param filename specify a filename where the snapshot is stored. This parameter can be either an absolute path or a simple
     * base filename ("hello.png" etc.), don't use a relative path containing directory names.("mydir/hello.png" etc.).
     * @since v3.2
     */
    CC_DLL void  captureScreen(const std::function<void(bool, const std::string&)>& afterCaptured, const std::string& filename);

    /** Capture a specific Node.
    * @param startNode specify the snapshot Node. It should be cocos2d::Scene
    * @param scale
    * @returns: return a Image, then can call saveToFile to save the image as "xxx.png or xxx.jpg".
    * @since v3.11
    * !!! remark: Caller is responsible for releasing it by calling delete.
    */
    CC_DLL Image* captureNode(Node* startNode, float scale = 1.0f);
    
    /** Find children by name, it will return all child that has the same name.
     * It supports c++ 11 regular expression. It is  a helper function of `Node::enumerateChildren()`.
     * You can refer to `Node::enumerateChildren()` for detail information.
     *
     * @param node The node to find
     * @param name The name to search for, it supports c++ 11 expression
     * @return Array of Nodes that matches the name
     * @since v3.2
     */
    CC_DLL std::vector<Node*>  findChildren(const Node &node, const std::string &name);
    
    /** Same to ::atof, but strip the string, remain 7 numbers after '.' before call atof.
     * Why we need this? Because in android c++_static, atof ( and std::atof ) is unsupported for numbers have long decimal part and contain
     * several numbers can approximate to 1 ( like 90.099998474121094 ), it will return inf. This function is used to fix this bug.
     * @param str The string be to converted to double.
     * @return Returns converted value of a string.
     */
    CC_DLL double  atof(const char* str);

    /** Get current exact time, accurate to nanoseconds.
     * @return Returns the time in seconds since the Epoch.
     */
    CC_DLL double  gettime();

    /**
     * Get current time in milliseconds, accurate to nanoseconds
     *
     * @return  Returns the time in milliseconds since the Epoch.
     */
    CC_DLL long long  getTimeInMilliseconds();

    /**
     * Calculate unionof bounding box of a node and its children.
     * @return Returns unionof bounding box of a node and its children.
     */
    CC_DLL Rect getCascadeBoundingBox(Node *node);

    /**
     * Create a sprite instance from base64 encoded image and adds the texture to the Texture Cache.

     * @return Returns an instance of sprite
     */
    CC_DLL Sprite* createSpriteFromBase64Cached(const char* base64String, const char* key);

    /**
    * Create a sprite instance from base64 encoded image.

    * @return Returns an instance of sprite
    */
    CC_DLL Sprite* createSpriteFromBase64(const char* base64String);


    /**
     * Find a child by name recursively

     * @return  Returns found node or nullptr
     */
    CC_DLL Node*  findChild(Node* levelRoot, const std::string& name);

    /**
     * Find a child by tag recursively

     * @return Returns found node or nullptr
     */
   CC_DLL Node*  findChild(Node* levelRoot, int tag);

    /**
     * Find a child by name recursively

     * @return  Returns found node or nullptr with specified type 'T'
     */
    template<typename T> inline
    T findChild(Node* levelRoot, const std::string& name)
    {
        return dynamic_cast<T>(findChild(levelRoot, name));
    }

    /**
     * Find a child by tag recursively

     * @return  Returns found node or nullptr with specified type 'T'
     */
    template<typename T> inline
    T findChild(Node* levelRoot, int tag)
    {
        return dynamic_cast<T>(findChild(levelRoot, tag));
    }
}

NS_CC_END

#endif // __SUPPORT_CC_UTILS_H__
