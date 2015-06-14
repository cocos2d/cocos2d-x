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

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

/*
 * @~english Use to calculate the matrix of node from parent node.
 * @~chinese 用来计算节点自父节点的变换矩阵。
 * @js NA
 * @lua NA
 */
class CC_STUDIO_DLL TransformHelp
{
public:
    TransformHelp();

    /**
    * @~english Transform a node by the matrix from parent node.
    * @~chinese 通过父节点的矩阵变换子节点。
    * @param node @~english Child node.
    * @~chinese 子节点。
    * @param parentNode @~english Parent node.
    * @~chinese 父节点。
    */
    static void transformFromParent(BaseData &node, const BaseData &parentNode);
    /**
    * @~english Transform parent node by the matrix from node.
    * @~chinese 通过子节点的矩阵变换父节点。
    * @param node @~english Child node.
    * @~chinese 子节点。
    * @param parentNode @~english Parent node.
    * @~chinese 父节点。
    */
    static void transformToParent(BaseData &node, const BaseData &parentNode);

    /**
    * @~english Transform a node by the matrix from parent node without scale.
    * @~chinese 通过父节点的矩阵变换子节点，无缩放。
    * @param node @~english Child node.
    * @~chinese 子节点。
    * @param parentNode @~english Parent node.
    * @~chinese 父节点。
    */
    static void transformFromParentWithoutScale(BaseData &node, const BaseData &parentNode);
    /**
    * @~english Transform parent node by the matrix from node without scale.
    * @~chinese 通过子节点的矩阵变换父节点，无缩放。
    * @param node @~english Child node.
    * @~chinese 子节点。
    * @param parentNode @~english Parent node.
    * @~chinese 父节点。
    */
    static void transformToParentWithoutScale(BaseData &node, const BaseData &parentNode);

    /**
    * @~english Get matrix from node attribute.
    * @~chinese 获取节点属性矩阵。
    * @param _node @~english Node.
    * @~chinese 节点。
    * @param _matrix @~english Matrix.
    * @~chinese 矩阵。
    */
    static void nodeToMatrix(const BaseData &_node, cocos2d::AffineTransform &_matrix);
    /**
    * @~english Get matrix from node attribute.
    * @~chinese 获取节点属性矩阵。
    * @param node @~english Node.
    * @~chinese 节点。
    * @param matrix @~english Matrix.
    * @~chinese 矩阵。
    */
    static void nodeToMatrix(const BaseData &node, cocos2d::Mat4 &matrix);
    /**
    * @~english Set node attribute by matrix.
    * @~chinese 通过矩阵设置节点属性。
    * @param _matrix @~english Matrix.
    * @~chinese 矩阵。
    * @param _node @~english Node.
    * @~chinese 节点。
    */
    static void matrixToNode(const cocos2d::AffineTransform &_matrix, BaseData &_node);
    /**
    * @~english Set node attribute by matrix.
    * @~chinese 通过矩阵设置节点属性。
    * @param _matrix @~english Matrix.
    * @~chinese 矩阵。
    * @param _node @~english Node.
    * @~chinese 节点。
    */
    static void matrixToNode(const cocos2d::Mat4 &_matrix, BaseData &_node);

    /**
    * @~english Change target data by concat source data.
    * @~chinese 通过相加设置目标数据。
    * @param target @~english Target data.
    * @~chinese 目标数据。
    * @param source @~english Source data.
    * @~chinese 源数据。
    */
    static void nodeConcat(BaseData &target, BaseData &source);
    /**
    * @~english Change target data ay sub source data.
    * @~chinese 通过相减设置目标数据。
    * @param target @~english Target data.
    * @~chinese 目标数据。
    * @param source @~english Source data.
    * @~chinese 源数据。
    */
    static void nodeSub(BaseData &target, BaseData &source);
public:
    static cocos2d::AffineTransform helpMatrix1;
    static cocos2d::AffineTransform helpMatrix2;

    static cocos2d::Vec2 helpPoint1;
    static cocos2d::Vec2 helpPoint2;
};

}

#endif /*__CCTRANSFORMHELP_H__*/
