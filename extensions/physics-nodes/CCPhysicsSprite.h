/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __PHYSICSNODES_CCPHYSICSSPRITE_H__
#define __PHYSICSNODES_CCPHYSICSSPRITE_H__

#include "2d/CCSprite.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"

#if (CC_ENABLE_CHIPMUNK_INTEGRATION || CC_ENABLE_BOX2D_INTEGRATION)

struct cpBody;
class b2Body;

NS_CC_EXT_BEGIN

/** @class PhysicsSprite
 * @brief @~english A Sprite subclass that is bound to a physics body.
 * It works with:
 * - Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 * - Objective-Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 * - Box2d: Preprocessor macro CC_ENABLE_BOX2D_INTEGRATION should be defined
 *
 * Features and Limitations:
 * - Scale and Skew properties are ignored.
 * - Position and rotation are going to updated from the physics body
 * - If you update the rotation or position manually, the physics body will be updated
 * - You can't enble both Chipmunk support and Box2d support at the same time. Only one can be enabled at compile time
 *
 * @~chinese 一个继承于Sprite并关联了一个物理刚体的子类。
 * 可基于以下物理引擎:
 * - Chipmunk:定义CC_ENABLE_CHIPMUNK_INTEGRATION宏并设置为非零。
 * - Objective-Chipmunk：定义CC_ENABLE_CHIPMUNK_INTEGRATION宏并设置为非零。
 * - Box2d:定义CC_ENABLE_BOX2D_INTEGRATION宏并设置为非零。
 * 
 * 特性和限制:
 * — 不支持缩放和倾斜设置。
 * — 位置和旋转将更新给物理刚体。
 * — 如果你手动更新旋转或位置属性,物理刚体也将被更新。
 * — 你不能同时启用Chipmunk和Box2d的支持，在编译时只能开启对其中一个的支持。
 * @lua NA
 */
class CC_EX_DLL PhysicsSprite : public Sprite
{
public:
    /**
     *
     */
    static PhysicsSprite* create();

    /** @~english Creates a physics sprite with a texture.
     * The rect used will be the size of the texture.
     * The offset will be (0,0).
     * @~chinese 基于给定的纹理创建一个关联了物理刚体的精灵。
     * 物理刚体的大小等于给定纹理的大小，刚体相对精灵的偏移等于（0，0）。
     * 
     * @param texture @~english A pointer to a Texture2D object. 
     * @~chinese 一个Texture2D对象的指针。
     *
     * @return PhysicsSprite* @~english A initialized physics sprite which is marked as "autorelease".
     * @~chinese 一个初始化的物理精灵，这个精灵会自动被标记为“autorelease”(自动释放)。
     */
    static PhysicsSprite* createWithTexture(Texture2D *texture);

    /** @~english Creates a physics sprite with a texture and a rect.
     * The offset will be (0,0).
     * @~chinese 基于给定的纹理及矩形创建一个关联了物理刚体的精灵。。
     * 物理刚体的大小等于给定的矩形，刚体相对精灵的偏移等于（0，0）。
     * 
     * @param texture @~english A pointer to a Texture2D object. 
     * @~chinese 一个Texture2D对象的指针。
     * @param rect @~english A subrect of the texture. @~chinese 纹理的部分区域。
     *
     * @return PhysicsSprite* @~english A initialized physics sprite which is marked as "autorelease".
     * @~chinese 一个初始化的物理精灵，这个精灵会自动被标记为“autorelease”(自动释放)。
     */
    static PhysicsSprite* createWithTexture(Texture2D *texture, const Rect& rect);

    /** @~english Creates a physics sprite with an sprite frame. 
     * The rect used will be the size of the sprite frame.
     * @~chinese 基于给定的精灵帧创建一个关联了物理刚体的精灵。
     * 物理刚体的大小等于给定纹理的大小，刚体相对精灵的偏移等于（0，0）。
     * 
     * @param spriteFrame @~english A sprite frame object.
     * @~chinese 一个SpriteFrame(精灵帧)对象。
     *
     * @return PhysicsSprite* @~english A initialized physics sprite which is marked as "autorelease".
     * @~chinese 一个初始化的物理精灵，这个精灵会自动被标记为“autorelease”(自动释放)。
     */
    static PhysicsSprite* createWithSpriteFrame(SpriteFrame *spriteFrame);

    /** @~english Creates a physics sprite with an sprite frame name.
     * An SpriteFrame will be fetched from the SpriteFrameCache by name.
     * If the SpriteFrame doesn't exist it will raise an exception.
     * @~chinese 基于给定的精灵帧名称创建一个关联了物理刚体的精灵。
     * 将通过精灵帧名称从SpriteFrameCache取得一个SpriteFrame（精灵帧）。
     * 如果对应的精灵帧不存在将引发一个异常。
     * 
     * @param spriteFrameName @~english the name of sprite frame.
     * @~chinese 精灵帧名称。
     *
     * @return PhysicsSprite* @~english A initialized physics sprite which is marked as "autorelease".
     * @~chinese 一个初始化的物理精灵，这个精灵会自动被标记为“autorelease”(自动释放)。
     * @since v0.9
     */
    static PhysicsSprite* createWithSpriteFrameName(const char *spriteFrameName);

    /** @~english Creates a physics sprite with an image file path.
     * The rect used will be the size of the image.
     * The offset will be (0,0).
     * @~chinese 基于给定的图片文件路径创建一个关联了物理刚体的精灵。
     * 物理刚体的大小等于给定图片的大小，刚体相对精灵的偏移等于（0，0）。
     * 
     * @param filePath @~english an image file path. @~chinese 图片文件路径。
     *
     * @return PhysicsSprite* @~english A initialized physics sprite which is marked as "autorelease".
     * @~chinese 一个初始化的物理精灵，这个精灵会自动被标记为“autorelease”(自动释放)。
     */
    static PhysicsSprite* create(const char *filePath);

    /** @~english Creates a physics sprite with an image file path and a rect.
     * The offset will be (0,0).
     * @~chinese 基于给定的图片文件路径及矩形创建一个关联了物理刚体的精灵。
     * 物理刚体的大小等于给定矩形的大小，刚体相对精灵的偏移等于（0，0）。
     * 
     * @param filePath @~english an image file path. @~chinese 图片文件路径。
     * @param rect @~english A subrect of the image file. @~chinese 图片文件的部分区域。
     *
     * @return PhysicsSprite* @~english A initialized physics sprite which is marked as "autorelease".
     * @~chinese 一个初始化的物理精灵，这个精灵会自动被标记为“autorelease”(自动释放)。
     */
    static PhysicsSprite* create(const char *filePath, const Rect& rect);

    PhysicsSprite();

    virtual bool isDirty() const override;

    /** @~english Keep the sprite's rotation separate from the body.  
     * @~chinese 获取精灵的旋转和物理刚体的旋转是否分离。
     *
     * @return true，if the sprite's rotation separate from the body.false，other wise.
     * @~chinese 如果精灵的旋转和刚体是分离的返回true，否则返回false。
     */
    bool isIgnoreBodyRotation() const;

    /** @~english Keep the sprite's rotation separate from the body.  
     * @~chinese 设置精灵的旋转和物理刚体的旋转是否分离。
     *
     * @param bIgnoreBodyRotation @~english true if the sprite's rotation separate from the body.false，other wise.
     * @~chinese 如果设置为true，则精灵的旋转和刚体是分离的。
     */
    void setIgnoreBodyRotation(bool bIgnoreBodyRotation);

    //
    // Chipmunk specific
    //
    /** @~english Body accessor when using regular Chipmunk. 
     * @~chinese 获取精灵关联的Chipmunk刚体。
     *
     * @return @~english a physics body of Chipmunk. 
     * @~chinese 一个Chipmunk物理刚体。
     */
    cpBody* getCPBody() const;

    /** @~english Set the physics body of Chipmunk that let the sprite effect with physics. 
     * @~chinese 关联一个Chipmunk物理刚体来让这个精灵有物理世界机能。 
     *
     * @param pBody @~english a physics body of Chipmunk. 
     * @~chinese 一个Chipmunk物理刚体。
     */
    void setCPBody(cpBody *pBody);

    //
    // Box2d specific
    //
    /** @~english Body accessor when using Box2d. 
     * @~chinese 获取精灵关联的Box2d刚体。
     *
     * @return @~english a physics body of Box2d. 
     * @~chinese 一个Box2d物理刚体。
     */
    b2Body* getB2Body() const;

    /** @~english Set the physics body of Box2D that let the sprite effect with physics. 
     * @~chinese 关联一个Box2D物理刚体来让这个精灵有物理世界机能。 
     *
     * @param pBody @~english a physics body of Box2D. 
     * @~chinese 一个Box2D物理刚体。
     */
    void setB2Body(b2Body *pBody);

    float getPTMRatio() const;
    void setPTMRatio(float fPTMRatio);

    // overrides
    virtual const Vec2& getPosition() const override;
    virtual void getPosition(float* x, float* y) const override;
    virtual float getPositionX() const override;
    virtual float getPositionY() const override;
    virtual void setPosition(const Vec2 &position) override;
    virtual float getRotation() const override;
    virtual void setRotation(float fRotation) override;
    virtual void syncPhysicsTransform() const;
    virtual const Mat4& getNodeToParentTransform() const override;
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

protected:
    const Vec2& getPosFromPhysics() const;

protected:
    bool    _ignoreBodyRotation;

    // chipmunk specific
    cpBody  *_CPBody;

    // box2d specific
    b2Body  *_pB2Body;
    float   _PTMRatio;
};

NS_CC_EXT_END

#endif // CC_ENABLE_CHIPMUNK_INTEGRATION || CC_ENABLE_BOX2D_INTEGRATION

#endif // __PHYSICSNODES_CCPHYSICSSPRITE_H__
