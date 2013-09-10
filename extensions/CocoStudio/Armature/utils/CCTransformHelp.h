/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCArmatureDefine.h"
#include "../datas/CCDatas.h"

namespace cocos2d { namespace extension { namespace armature {

/*
 * use to calculate the matrix of node from parent node
 */
class  TransformHelp
{
public:
    TransformHelp();

    static void transformFromParent(BaseData &node, const BaseData &parentNode);
    static void transformToParent(BaseData &node, const BaseData &parentNode);

    static void transformFromParentWithoutScale(BaseData &node, const BaseData &parentNode);
    static void transformToParentWithoutScale(BaseData &node, const BaseData &parentNode);

    static void nodeToMatrix(const BaseData &_node, AffineTransform &_matrix);
    static void matrixToNode(const AffineTransform &_matrix, BaseData &_node);

    static void nodeConcat(BaseData &target, BaseData &source);
public:
    static AffineTransform helpMatrix1;
    static AffineTransform helpMatrix2;

    static Point helpPoint1;
    static Point helpPoint2;
};

}}} // namespace cocos2d { namespace extension { namespace armature {

#endif /*__CCTRANSFORMHELP_H__*/
