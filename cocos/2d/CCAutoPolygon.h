/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef COCOS_2D_CCAUTOPOLYGON_H__
#define COCOS_2D_CCAUTOPOLYGON_H__

#include <string>
#include <vector>
#include "platform/CCImage.h"
#include "renderer/CCTrianglesCommand.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

/**@~english
 * PolygonInfo is an object holding the required data to display Sprites。
 * It can be a simple as a triangle, or as complex as a whole 3D mesh
 * @~chinese 
 * PolygonInfo（多边形信息）是一个保存了精灵所需的数据的对象。
 * 它可以是一个简单的三角形,或者是一整个复杂3d网格。
 */
class CC_DLL PolygonInfo
{
public:
    /// @name Creators
    /// @{
    /**@~english
     * Creates an empty Polygon info
     * @~chinese 
     * 创建一个空Polygon info
     * @memberof @~english PolygonInfo
     * @~chinese PolygonInfo
     * @return @~english PolygonInfo object
     * @~chinese PolygonInfo对象
     */
    PolygonInfo():
    isVertsOwner(true),
    rect(cocos2d::Rect::ZERO),
    filename("")
    {
        triangles.verts = nullptr;
        triangles.indices = nullptr;
        triangles.vertCount = 0;
        triangles.indexCount = 0;
    };
    
    /**@~english
     * Create an Polygoninfo from the data of another Polygoninfo
     * @~chinese 
     * 从另一个polygoninfo数据创建一个Polygoninfo，拷贝构造函数（深拷贝）。
     * @param other @~english another PolygonInfo to be copied
     * @~chinese 待拷贝的另一个PolygonInfo
     * @return @~english duplicate of the other PolygonInfo
     * @~chinese 从待拷贝的PolygonInfo拷贝出的PolygonInfo
     */
    PolygonInfo(const PolygonInfo& other);
    //  end of creators group
    /// @}
    
    /**@~english
     * Copy the member of the other PolygonInfo
     * @~chinese 
     * 把另一个polygoninfo数据拷贝到当前PolygonInfo，重载赋值操作符（深拷贝）。
     * @param other  @~english another PolygonInfo to be copied
     * @~chinese 待拷贝的另一个PolygonInfo
     */
    PolygonInfo& operator= (const PolygonInfo &other);
    ~PolygonInfo();
    
    /**@~english
     * set the data to be a pointer to a quad
     * the member verts will not be released when this PolygonInfo destructs
     * as the verts memory are managed by other objects
     * @~chinese 
     * 将数据设置为一个指向quad的指针。
     * 除非析构，否则顶点将不会被释放。
     * 顶点内存是由其他对象维护的。
     * @param quad  @~english a pointer to the V3F_C4B_T2F_Quad object
     * @~chinese 一个指向V3F_C4B_T2F_Quad对象的指针
     */
    void setQuad(V3F_C4B_T2F_Quad *quad);

    /**@~english
     * get vertex count
     * @~chinese 
     * 获取顶点数量
     * @return @~english number of vertices
     * @~chinese 数量的顶点
     */
    const unsigned int getVertCount() const;
    
    /**@~english
     * get triangles count
     * @~chinese 
     * 获取三角形数量
     * @return @~english number of triangles
     * @~chinese 三角形的数量
     */
    const unsigned int getTriaglesCount() const;
    
    /**@~english
     * get sum of all triangle area size
     * @~chinese 
     * 获取所有三角形面积大小的总和
     * @return @~english sum of all triangle area size
     * @~chinese 所有三角形面积大小总和
     */
    const float getArea() const;
    
    Rect rect;
    std::string filename;
    TrianglesCommand::Triangles triangles;
    
protected:
    bool isVertsOwner;
    
private:
    void releaseVertsAndIndices();
};


/**@~english
 * AutoPolygon is a helper Object
 * AutoPolygon's purpose is to process an image into 2d polygon mesh in runtime
 * It has functions for each step in the process, from tracing all the points, to triangulation
 * the result can be then passed to Sprite::create() to create a Polygon Sprite
 * @~chinese 
 * AutoPolygon是一个辅助类
 * AutoPolygon的目的是在运行时将一个图片处理成2d多边形mesh。
 * 在这个过程中，每一步都有对应的方法，从点跟踪到三角化。
 * 结果可以然后传递给Sprite::create()来创建一个多边形精灵。
 */

class CC_DLL AutoPolygon
{
public:
    /**@~english
     * create an AutoPolygon and initialize it with an image file
     * the image must be a 32bit PNG for current version 3.7
     * @~chinese 
     * 使用指定的图像文件创建并初始化一个AutoPolygon
     * 在当前版本(v3.7)中图像必须是32位PNG格式。
     * @param filename @~english a path to image file, e.g., "scene1/monster.png".
     * @~chinese 图像文件的路径,例如"scene1/monster.png"。
     * @return @~english  an AutoPolygon object;
     * @~chinese 一个AutoPolygon对象;
     */
    AutoPolygon(const std::string &filename);
    
    /**@~english
     * Destructor of AutoPolygon.
     * @~chinese 
     * AutoPolygon的析构函数。
     */
    ~AutoPolygon();
    
    /**@~english
     * trace all the points along the outline of the image, 
     * @~chinese 
     * 跟踪图片轮廓上所有的点。
     * @warning @~english must create AutoPolygon with filename to use this function
     * @~chinese 必须指定图片文件名并使用这个函数来创建AutoPolygon。
     * @param   rect    @~english a texture rect for specify an area of the image, use Rect::Zero for the size of the image, default to Rect::Zero
     * @~chinese 纹理矩形图像的一个指定区域,使用Rect::Zero为图像的大小,默认为Rect::Zero
     * @param   threshold   @~english the value when alpha is greater than this value will be counted as opaque, default to 0.0
     * @~chinese 当透明度大于这个值将被视为不透明,默认为0.0
     * @return @~english  a vector of vec2 of all the points found in clockwise order
     * @~chinese 一个存储所有点的vector，点的顺序是按顺时针方向存储。
     * @code
     * auto ap = AutoPolygon("grossini.png");
     * std::vector<Vec2> points = ap.trace();//default to size of the image and threshold 0.0
     * @endcode
     */
     std::vector<Vec2> trace(const cocos2d::Rect& rect, const float& threshold = 0.0);
    
    /**@~english
     * reduce the ammount of points so its faster for GPU to process and draw
     * based on Ramer-Douglas-Puecker algorithm
     * @~chinese 
     * 减少点数量，以加快GPU处理和绘制的速度
     * 基于Ramer-Douglas-Puecker算法
     * @param   points  @~english a vector of Vec2 points as input
     * @~chinese 输入点vector
     * @param   rect    @~english a texture rect for specify an area of the image to avoid over reduction
     * @~chinese 一个指定图像的纹理点矩形区域，以避免超出规格
     * @param   epsilon @~english the perpendicular distance where points smaller than this value will be discarded
     * @~chinese 如果点的垂直距离小于该值，那么这个点将被丢弃
     * @return @~english  a vector of Vec2 of the remaining points in clockwise order
     * @~chinese 一个存储剩余的点的vector，按顺时针方向存储。
     * @code
     * auto ap = AutoPolygon();
     * std::vector<Vec2> reduced = ap.reduce(inputPoints, rect);//default epsilon is 2
     * @endcode
     */
    std::vector<Vec2> reduce(const std::vector<Vec2>& points, const Rect& rect, const float& epsilon = 2.0);
    
    /**@~english
     * expand the points along their edge, useful after you reduce the points that cuts into the sprite
     * using ClipperLib
     * @~chinese 
     * 扩展点的边缘，用于处理你在优化完点数量后可能裁剪到精灵的情况。
     * 使用ClipperLib
     * @param   points  @~english a vector of Vec2 points as input
     * @~chinese 输入点vector。
     * @param   rect    @~english a texture rect for specify an area of the image, the expanded points will be clamped in this rect, ultimately resulting in a quad if the expansion is too great
     * @~chinese 指定一个纹理矩形图像的区域,扩展完的点将夹在这个矩形内，避免最终扩展点过大。
     * @param   epsilon @~english the distance which the edges will expand
     * @~chinese 边缘扩展点距离
     * @return @~english  a vector of Vec2 as the result of the expansion
     * @~chinese 一个用于存储扩展完点的vector。
     * @code
     * auto ap = AutoPolygon();
     * std::vector<Vec2> expanded = ap.expand(inputPoints, rect, 2.0);
     * @endcode
     */
    std::vector<Vec2> expand(const std::vector<Vec2>& points, const Rect& rect, const float& epsilon);
    
    /**@~english
     * Triangulate the input points into triangles for rendering
     * using poly2tri
     * @~chinese 
     * 对输入点进行三角化，以便渲染。
     * 使用poly2tri
     * @warning @~english points must be closed loop, cannot have 2 points sharing the same position and cannot intersect itself
     * @~chinese 点必须是闭环,不能有两个点共享相同的位置,也不能相交。
     * @param   points  @~english a vector of vec2 points as input
     * @~chinese 输入点vector
     * @return @~english  a Triangles object with points and indices
     * @~chinese 一个带有点和索引点Triangle对象
     * @code
     * auto ap = AutoPolygon();
     * TrianglesCommand::Triangles myPolygons = ap.triangulate(myPoints);
     * @endcode
     */
    TrianglesCommand::Triangles triangulate(const std::vector<Vec2>& points);
    
    /**@~english
     * calculate the UV coordinates for each points based on a texture rect
     * @~chinese 
     * 基于纹理矩形计算每个点的UV坐标
     * @warning @~english This method requires the AutoPolygon object to know the texture file dimension
     * @~chinese 这种方法要求AutoPolygon对象知道纹理文件尺寸
     * @param   rect    @~english a texture rect to specify where to map the UV
     * @~chinese 一个指定点纹理矩形用于映射UV
     * @param   verts   @~english a pointer to the verts array, served both as input and output verts
     * @~chinese 一个指向顶点数组的指针,作为输入和输出顶点数组
     * @param   count   @~english the count for the verts array
     * @~chinese 顶的点数量
     * @code
     * auto ap = AutoPolygon("grossini.png");
     * TrianglesCommand::Triangles myPolygons = ap.triangulate(myPoints);
     * ap.calculateUV(rect, myPolygons.verts, 20);
     * @endcode
     */
    void calculateUV(const Rect& rect, V3F_C4B_T2F* verts, const ssize_t& count);
    
    /**@~english
     * a helper function, packing trace, reduce, expand, triangulate and calculate uv in one function
     * @~chinese 
     * 一个辅助函数,包含了点跟踪,优化,边缘扩大,三角化和UV计算。
     * @param   rect    @~english texture rect, use Rect::ZERO for the size of the texture, default is Rect::ZERO
     * @~chinese 纹理矩形,使用Rect::ZERO作为纹理的大小,默认是Rect::ZERO
     * @param   epsilon @~english the value used to reduce and expand, default to 2.0
     * @~chinese 用于优化和边缘扩展点值，默认是2.0
     * @param   threshold   @~english the value where bigger than the threshold will be counted as opaque, used in trace
     * @~chinese 所有透明度大于阈值的点将被视为不透明,用于点跟踪
     * @return @~english  a PolygonInfo, to use with sprite
     * @~chinese PolygonInfo,给精灵使用
     * @code
     * auto ap = AutoPolygon("grossini.png");
     * PolygonInfo myInfo = ap.generateTriangles();//use all default values
     * auto sp1 = Sprite::create(myInfo);
     * polygonInfo myInfo2 = ap.generateTriangles(Rect::ZERO, 5.0, 0.1);//ap can be reused to generate another set of PolygonInfo with different settings
     * auto sp2 = Sprite::create(myInfo2);
     * @endcode
     */
    PolygonInfo generateTriangles(const Rect& rect = Rect::ZERO, const float& epsilon = 2.0, const float& threshold = 0.05);
    
    /**@~english
     * a helper function, packing autoPolygon creation, trace, reduce, expand, triangulate and calculate uv in one function
     * @~chinese 
     * 一个辅助函数,包含了点跟踪,优化,边缘扩大,三角化和UV计算。
     * @warning @~english if you want to repetitively generate polygons, consider create an AutoPolygon object, and use generateTriangles function, as it only reads the file once
     * @~chinese 如果你想重复生成多边形,考虑只创建一个AutoPolygon对象,并使用generateTriangles函数,因为它只读取文件一次
     * @param   filename     @~english A path to image file, e.g., "scene1/monster.png".
     * @~chinese 图像文件的路径,例如"scene1/monster.png"。
     * @param   rect    @~english texture rect, use Rect::ZERO for the size of the texture, default is Rect::ZERO
     * @~chinese 纹理矩形,使用Rect::ZERO作为纹理的大小,默认是Rect::ZERO
     * @param   epsilon @~english the value used to reduce and expand, default to 2.0
     * @~chinese 用于优化和边缘扩展点值，默认是2.0
     * @param   threshold   @~english the value where bigger than the threshold will be counted as opaque, used in trace
     * @~chinese 所有透明度大于阈值的点将被视为不透明,用于点跟踪
     * @return @~english  a PolygonInfo, to use with sprite
     * @~chinese PolygonInfo,给精灵使用
     * @code
     * auto sp = Sprite::create(AutoPolygon::generatePolygon("grossini.png"));
     * @endcode
     */
    static PolygonInfo generatePolygon(const std::string& filename, const Rect& rect = Rect::ZERO, const float epsilon = 2.0, const float threshold = 0.05);
protected:
    Vec2 findFirstNoneTransparentPixel(const Rect& rect, const float& threshold);
    std::vector<cocos2d::Vec2> marchSquare(const Rect& rect, const Vec2& first, const float& threshold);
    unsigned int getSquareValue(const unsigned int& x, const unsigned int& y, const Rect& rect, const float& threshold);

    unsigned char getAlphaByIndex(const unsigned int& i);
    unsigned char getAlphaByPos(const Vec2& pos);

    int getIndexFromPos(const unsigned int& x, const unsigned int& y){return y*_width+x;};
    cocos2d::Vec2 getPosFromIndex(const unsigned int& i){return cocos2d::Vec2(i%_width, i/_width);};

    std::vector<cocos2d::Vec2> rdp(std::vector<cocos2d::Vec2> v, const float& optimization);
    float perpendicularDistance(const cocos2d::Vec2& i, const cocos2d::Vec2& start, const cocos2d::Vec2& end);

    //real rect is the size that is in scale with the texture file
    Rect getRealRect(const Rect& rect);
    
    Image* _image;
    unsigned char * _data;
    std::string _filename;
    unsigned int _width;
    unsigned int _height;
    float _scaleFactor;
    unsigned int _threshold;
};

NS_CC_END

#endif // #ifndef COCOS_2D_CCAUTOPOLYGON_H__
