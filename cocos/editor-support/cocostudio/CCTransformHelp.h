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

#ifndef __CCTRANSFORMHELP_H__
#define __CCTRANSFORMHELP_H__

#include "editor-support/cocostudio/CCArmatureDefine.h"
#include "editor-support/cocostudio/CCDatas.h"
#include "editor-support/cocostudio/CocosStudioExport.h"

namespace cocostudio {

/*
 * use to calculate the matrix of node from parent node
 * @js NA
 * @lua NA
 */
class CC_STUDIO_DLL TransformHelp
{
public:
    TransformHelp();

    static void transformFromParent(BaseData &node, const BaseData &parentNode);
    static void transformToParent(BaseData &node, const BaseData &parentNode);

    static void transformFromParentWithoutScale(BaseData &node, const BaseData &parentNode);
    static void transformToParentWithoutScale(BaseData &node, const BaseData &parentNode);

    static void nodeToMatrix(const BaseData &_node, cocos2d::AffineTransform &_matrix);
    static void nodeToMatrix(const BaseData &node, cocos2d::Mat4 &matrix);
    static void matrixToNode(const cocos2d::AffineTransform &_matrix, BaseData &_node);
    static void matrixToNode(const cocos2d::Mat4 &_matrix, BaseData &_node);

    static void nodeConcat(BaseData &target, BaseData &source);
    static void nodeSub(BaseData &target, BaseData &source);
public:
    static cocos2d::AffineTransform helpMatrix1;
    static cocos2d::AffineTransform helpMatrix2;

    static cocos2d::Vec2 helpPoint1;
    static cocos2d::Vec2 helpPoint2;
};

}

#endif /*__CCTRANSFORMHELP_H__*/
