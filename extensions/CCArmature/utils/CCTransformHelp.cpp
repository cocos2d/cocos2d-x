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

#include "CCTransformHelp.h"
#include "CCUtilMath.h"

NS_CC_EXT_BEGIN

CCAffineTransform CCTransformHelp::helpMatrix1;
CCAffineTransform CCTransformHelp::helpMatrix2;

CCPoint CCTransformHelp::helpPoint1;
CCPoint CCTransformHelp::helpPoint2;

CCBaseData helpParentNode;

CCTransformHelp::CCTransformHelp()
{
}

void CCTransformHelp::transformFromParent(CCBaseData &node, const CCBaseData &parentNode)
{
    nodeToMatrix(node, helpMatrix1);
    nodeToMatrix(parentNode, helpMatrix2);

    helpMatrix2 = CCAffineTransformInvert(helpMatrix2);
    helpMatrix1 = CCAffineTransformConcat(helpMatrix1, helpMatrix2);

    matrixToNode(helpMatrix1, node);
}

void CCTransformHelp::transformToParent(CCBaseData &node, const CCBaseData &parentNode)
{

    nodeToMatrix(node, helpMatrix1);
    nodeToMatrix(parentNode, helpMatrix2);

    helpMatrix1 = CCAffineTransformConcat(helpMatrix1, helpMatrix2);

    matrixToNode(helpMatrix1, node);
}

void CCTransformHelp::transformFromParentWithoutScale(CCBaseData &node, const CCBaseData &parentNode)
{

    helpParentNode.copy(&parentNode);
    helpParentNode.scaleX = 1;
    helpParentNode.scaleY = 1;

    nodeToMatrix(node, helpMatrix1);
    nodeToMatrix(helpParentNode, helpMatrix2);

    helpMatrix2 = CCAffineTransformInvert(helpMatrix2);
    helpMatrix1 = CCAffineTransformConcat(helpMatrix1, helpMatrix2);

    matrixToNode(helpMatrix1, node);
}

void CCTransformHelp::transformToParentWithoutScale(CCBaseData &node, const CCBaseData &parentNode)
{

    helpParentNode.copy(&parentNode);
    helpParentNode.scaleX = 1;
    helpParentNode.scaleY = 1;

    nodeToMatrix(node, helpMatrix1);
    nodeToMatrix(helpParentNode, helpMatrix2);

    helpMatrix1 = CCAffineTransformConcat(helpMatrix1, helpMatrix2);

    matrixToNode(helpMatrix1, node);
}

void CCTransformHelp::nodeToMatrix(const CCBaseData &node, CCAffineTransform &matrix)
{
    matrix.a = node.scaleX * cos(node.skewY);
    matrix.b = node.scaleX * sin(node.skewY);
    matrix.c = node.scaleY * sin(node.skewX);
    matrix.d = node.scaleY * cos(node.skewX);

    matrix.tx = node.x;
    matrix.ty = node.y;
}

void CCTransformHelp::matrixToNode(const CCAffineTransform &matrix, CCBaseData &node)
{
    /*
     *  In as3 language, there is a function called "deltaTransformPoint", it calculate a point used give Transform
     *  but not used the tx, ty value. we simulate the function here
     */
    helpPoint1.x = 0;
    helpPoint1.y = 1;
    helpPoint1 = CCPointApplyAffineTransform(helpPoint1, matrix);
    helpPoint1.x -= matrix.tx;
    helpPoint1.y -= matrix.ty;

    helpPoint2.x = 1;
    helpPoint2.y = 0;
    helpPoint2 = CCPointApplyAffineTransform(helpPoint2, matrix);
    helpPoint2.x -= matrix.tx;
    helpPoint2.y -= matrix.ty;

    node.skewX = -(atan2f(helpPoint1.y, helpPoint1.x) - 1.5707964f);
    node.skewY = atan2f(helpPoint2.y, helpPoint2.x);
	node.scaleX = sqrt(matrix.a * matrix.a + matrix.b * matrix.b);
	node.scaleY = sqrt(matrix.c * matrix.c + matrix.d * matrix.d);
    node.x = matrix.tx;
    node.y = matrix.ty;
}

void CCTransformHelp::nodeConcat(CCBaseData &target, CCBaseData &source)
{
    target.x += source.x;
    target.y += source.y;
    target.skewX += source.skewX;
    target.skewY += source.skewY;
    target.scaleX += source.scaleX;
    target.scaleY += source.scaleY;
}

NS_CC_EXT_END
