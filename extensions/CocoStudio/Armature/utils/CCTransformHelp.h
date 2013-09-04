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

NS_CC_EXT_BEGIN

/*
 * use to calculate the matrix of node from parent node
 */
class  CCTransformHelp
{
public:
    CCTransformHelp();

    static void transformFromParent(CCBaseData &node, const CCBaseData &parentNode);
    static void transformToParent(CCBaseData &node, const CCBaseData &parentNode);

    static void transformFromParentWithoutScale(CCBaseData &node, const CCBaseData &parentNode);
    static void transformToParentWithoutScale(CCBaseData &node, const CCBaseData &parentNode);

    static void nodeToMatrix(const CCBaseData &_node, CCAffineTransform &_matrix);
    static void matrixToNode(const CCAffineTransform &_matrix, CCBaseData &_node);

    static void nodeConcat(CCBaseData &target, CCBaseData &source);
    static void nodeSub(CCBaseData &target, CCBaseData &source);
public:
    static CCAffineTransform helpMatrix1;
    static CCAffineTransform helpMatrix2;

    static CCPoint helpPoint1;
    static CCPoint helpPoint2;
};

NS_CC_EXT_END

#endif /*__CCTRANSFORMHELP_H__*/
