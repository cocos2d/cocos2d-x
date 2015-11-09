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

#ifndef __CCINSTANT_ACTION_H__
#define __CCINSTANT_ACTION_H__

#include <functional>
#include "2d/CCAction.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** @class ActionInstant
 * @brief @~english Instant actions are immediate actions. They don't have a duration like the ActionInterval actions.
 * @~chinese 即时动作是会立即被执行的动作。他们没有持续时间动作（ActionInterval）的持续时间属性。
 **/
class CC_DLL ActionInstant : public FiniteTimeAction //<NSCopying>
{
public:
    //
    // Overrides
    //
    virtual ActionInstant* clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
    
    virtual ActionInstant * reverse() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

    virtual bool isDone() const override;
    
    virtual void step(float dt) override;
    
    virtual void update(float time) override;
};

/** @class Show
 * @brief @~english Show the node instantly.
 * @~chinese 显示动作用来立即显示一个节点。
 **/
class CC_DLL Show : public ActionInstant
{
public:
    /** @~english Allocates and initializes the action.
     *
     * @~chinese 创建并初始化动作。
     * 
     * @return @~english  An autoreleased Show object.
     * @~chinese 一个自释放的Show动作对象。
     */
    static Show * create();

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual ActionInstant* reverse() const override;
    virtual Show* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    Show(){}
    virtual ~Show(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Show);
};

/** @class Hide
 * @brief @~english Hide the node.
 * @~chinese 隐藏动作用来立即隐藏一个节点
 */
class CC_DLL Hide : public ActionInstant
{
public:
    /** @~english Allocates and initializes the action.
     *
     * @~chinese 创建并初始化动作。
     * 
     * @return @~english An autoreleased Hide object.
     * @~chinese 一个自释放的Hide动作对象。
     */
    static Hide * create();

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual ActionInstant* reverse() const override;
    virtual Hide* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    Hide(){}
    virtual ~Hide(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Hide);
};

/** @class ToggleVisibility
 * @brief @~english Toggles the visibility of a node.
 * @~chinese ToggleVisibility动作用来切换一个节点的可见性。
 */
class CC_DLL ToggleVisibility : public ActionInstant
{
public:
    /** @~english Allocates and initializes the action.
     *
     * @~chinese 创建并初始化动作。
     * 
     * @return @~english An autoreleased ToggleVisibility object.
     * @~chinese 一个自释放的ToggleVisibility动作对象。
     */
    static ToggleVisibility * create();

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual ToggleVisibility* reverse() const override;
    virtual ToggleVisibility* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    ToggleVisibility(){}
    virtual ~ToggleVisibility(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ToggleVisibility);
};

/** @class RemoveSelf
 * @brief @~english Remove the node.
 * @~chinese RemoveSelf动作用来删除执行动作的节点。
 */
class CC_DLL RemoveSelf : public ActionInstant
{
public:
    /** @~english Create the action.
     *
     * @~chinese 创建动作。
     * 
     * @param isNeedCleanUp @~english Is need to clean up, the default value is true.
     * @~chinese 是否需要清理，默认值是true。
     * @return @~english An autoreleased RemoveSelf object.
     * @~chinese 一个自释放的RemoveSelf动作对象。
     */
    static RemoveSelf * create(bool isNeedCleanUp = true);

    //
    // Override
    //
    virtual void update(float time) override;
    virtual RemoveSelf* clone() const override;
    virtual RemoveSelf* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    RemoveSelf() : _isNeedCleanUp(true){}
    virtual ~RemoveSelf(){}

    /** @~english init the action  @~chinese 初始化动作 */
    bool init(bool isNeedCleanUp);

protected:
    bool _isNeedCleanUp;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RemoveSelf);
};

/** @class FlipX
 * @brief @~english Flips the sprite horizontally.
 * @~chinese FlipX可以立即水平翻转一个精灵。
 * @since v0.99.0
 */
class CC_DLL FlipX : public ActionInstant
{
public:
    /** @~english Create the action.
     *
     * @~chinese 创建动作。
     * 
     * @param x @~english Flips the sprite horizontally if true.
     * @~chinese 如果为true则水平翻转精灵，值为false时则恢复精灵原始状态。
     * @return @~english  An autoreleased FlipX object.
     * @~chinese 一个自释放的FlipX对象。
     */
    static FlipX * create(bool x);

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual FlipX* reverse() const override;
    virtual FlipX* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipX() :_flipX(false) {}
    virtual ~FlipX() {}

    /** @~english init the action  @~chinese 初始化动作 */
    bool initWithFlipX(bool x);

protected:
    bool    _flipX;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipX);
};

/** @class FlipY
 * @brief @~english Flips the sprite vertically.
 * @~chinese FlipY可以立即垂直翻转一个精灵。
 * @since v0.99.0
 */
class CC_DLL FlipY : public ActionInstant
{
public:
    /** @~english Create the action.
     *
     * @~chinese 创建动作。
     * 
     * @param y @~english Flips the sprite vertically if true.
     * @~chinese 如果为true则垂直翻转精灵，值为false时则恢复精灵原始状态。
     * @return @~english An autoreleased FlipY object.
     * @~chinese 一个自释放的FlipY对象。
     */
    static FlipY * create(bool y);

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual FlipY* reverse() const override;
    virtual FlipY* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipY() :_flipY(false) {}
    virtual ~FlipY() {}

    /** @~english init the action  @~chinese 初始化动作 */
    bool initWithFlipY(bool y);

protected:
    bool    _flipY;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipY);
};

/** @class Place
 * @brief @~english Places the node in a certain position.
 * @~chinese Place动作可以将节点放置在特定位置。
 */
class CC_DLL Place : public ActionInstant //<NSCopying>
{
public:

    /** @~english Creates a Place action with a position.
     *
     * @~chinese 用位置参数创建一个动作。
     * 
     * @param pos  @~english A certain position.
     * @~chinese 一个特定的位置。
     * @return @~english  An autoreleased Place object.
     * @~chinese 一个自释放的Place对象。
     */
    static Place * create(const Vec2& pos);

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual Place* reverse() const override;
    virtual Place* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    Place(){}
    virtual ~Place(){}

    /** @~english Initializes a Place action with a position  @~chinese 用一个位置初始化动作 */
    bool initWithPosition(const Vec2& pos);

protected:
    Vec2 _position;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Place);
};


/** @class CallFunc
 * @brief @~english Calls a 'callback'.
 * @~chinese 调用一个回调函数。
 */
class CC_DLL CallFunc : public ActionInstant //<NSCopying>
{
public:
    /** @~english Creates the action with the callback of type `std::function<void()>`.
     * This is the preferred way to create the callback.
     * When this function bound in js or lua ,the input param will be changed.
     * In lua:local create(local funcID).
     *
     * @~chinese 用一个回调函数创建CallFunc动作，回调函数的类型是`std::function<void()>`。
     * 这是创建回调函数的首选方法。
     * 这个API绑定在js或lua中，输入参数会被改变。
     * lua: local create(local funcID).
     * 
     * @param func  @~english A callback function need to be executed.
     * @~chinese 需要被执行的回调函数。
     * @return @~english  An autoreleased CallFunc object.
     * @~chinese 一个自释放的CallFunc对象。
     */
    static CallFunc * create(const std::function<void()>& func);

    /** @~english Creates the action with the callback
     * typedef void (Ref::*SEL_CallFunc)();
     * @~chinese 用下面的函数类型创建CallFunc动作
     * typedef void (Ref::*SEL_CallFunc)();
     * @deprecated @~english Use the std::function API instead. @~chinese 使用`std::function`API替代
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static CallFunc * create(Ref* target, SEL_CallFunc selector);

public:
    /** @~english Executes the callback.
     * @~chinese 执行回调。
     */
    virtual void execute();

    /** @~english Get the selector target.
     *
     * @~chinese 获取回调函数的执行主体。
     * 
     * @return @~english The selector target.
     * @~chinese 回调函数的执行主体。
     */
    inline Ref* getTargetCallback()
    {
        return _selectorTarget;
    }

    /** @~english Set the selector target.
     *
     * @~chinese 设置回调函数的执行主体。
     * 
     * @param sel @~english The selector target.
     * @~chinese 回调函数的执行主体。
     */
    inline void setTargetCallback(Ref* sel)
    {
        if (sel != _selectorTarget)
        {
            CC_SAFE_RETAIN(sel);
            CC_SAFE_RELEASE(_selectorTarget);
            _selectorTarget = sel;
        }
    }
    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual CallFunc* reverse() const override;
    virtual CallFunc* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    CallFunc()
    : _selectorTarget(nullptr)
    , _callFunc(nullptr)
    , _function(nullptr)
    {
    }
    virtual ~CallFunc();

    /** @~english Initializes the action with the callback
     * typedef void (Ref::*SEL_CallFunc)();
     * @~chinese 用下面的函数类型初始化操CallFunc动作
     * typedef void (Ref::*SEL_CallFunc)();
     * @deprecated Use the std::function API instead.
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target);
    
    /** @~english initializes the action with the `std::function<void()>`
     * @~chinese 用`std::function<void()>`回调函数初始化动作
     * @lua NA
     */
    bool initWithFunction(const std::function<void()>& func);

protected:
    /** @~english Target that will be called  @~chinese 回调函数的执行主体 */
    Ref*   _selectorTarget;

    union
    {
        SEL_CallFunc    _callFunc;
        SEL_CallFuncN    _callFuncN;
    };
    
    /** @~english function that will be called  @~chinese 回调函数*/
    std::function<void()> _function;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(CallFunc);
};

/** @class CallFuncN
 * @brief @~english Calls a 'callback' with the node as the first argument. N means Node.
 * @~chinese 使用节点作为第一个参数调用回调函数的CallFuncN动作。N代表节点。
 * @js NA
 */
class CC_DLL CallFuncN : public CallFunc
{
public:
    /** @~english Creates the action with the callback of type `std::function<void()>`.
     * This is the preferred way to create the callback.
     *
     * @~chinese 用一个回调函数创建CallFunc动作，回调函数的类型是`std::function<void()>`。
     * 这是创建回调的首选方法。
     * 
     * @param func  @~english A callback function need to be excuted.
     * @~chinese 将会被执行的回调函数。
     * @return @~english  An autoreleased CallFuncN object.
     * @~chinese 一个自释放的CallFuncN对象。
     */
    static CallFuncN * create(const std::function<void(Node*)>& func);

    /** @~english Creates the action with the callback.
     * typedef void (Ref::*SEL_CallFuncN)(Node*);
     * @~chinese 用下面的方法创建CallFuncN动作。
     * typedef void (Ref::*SEL_CallFuncN)(Node*);
     * @deprecated Use the std::function API instead.
     */
    CC_DEPRECATED_ATTRIBUTE static CallFuncN * create(Ref* target, SEL_CallFuncN selector);

    //
    // Overrides
    //
    virtual CallFuncN* clone() const override;
    virtual void execute() override;
    
CC_CONSTRUCTOR_ACCESS:
    CallFuncN():_functionN(nullptr){}
    virtual ~CallFuncN(){}

    /** @~english initializes the action with the `std::function<void(Node*)>`  @~chinese 用`std::function<void(Node*)>`初始化动作 */
    bool initWithFunction(const std::function<void(Node*)>& func);
    
    /** @~english initializes the action with the callback
     * typedef void (Ref::*SEL_CallFuncN)(Node*);
     * @~chinese 用下面的回调类型初始化动作
     * typedef void (Ref::*SEL_CallFuncN)(Node*);
     * @deprecated Use the std::function API instead.
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target, SEL_CallFuncN selector);

protected:
    /** @~english function that will be called with the "sender" as the 1st argument  @~chinese 回调函数，将包含`sender`作为第一个参数 */
    std::function<void(Node*)> _functionN;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(CallFuncN);
};

/** @class __CCCallFuncND
 * @deprecated Please use CallFuncN instead.
 * @brief @~english Calls a 'callback' with the node as the first argument and the 2nd argument is data.
 * ND means: Node and Data. Data is void *, so it could be anything.
 * @~chinese 使用节点作为第一个参数，数据作为第二个参数来调用回调的__CCCallFuncND动作。
 * ND的意思是：节点和数据。数据类型是void *，所以它可以是任何东西。
 * @js NA
 */
class CC_DLL  __CCCallFuncND : public CallFunc
{
public:
    /** @~english Creates the action with the callback and the data to pass as an argument.
     *
     * @~chinese 以目标节点，回调函数和数据作为参数来创建动作。
     * 
     * @param target    @~english A certain target.
     * @~chinese 目标节点。
     * @param selector  @~english The callback need to be excuted.
     * @~chinese 回调函数。
     * @param d @~english Data, is void* type.
     * @~chinese 数据，类型是void *。
     * @return @~english An autoreleased __CCCallFuncND object.
     * @~chinese 一个自释放的__CCCallFuncND对象。
     */
    CC_DEPRECATED_ATTRIBUTE static __CCCallFuncND * create(Ref* target, SEL_CallFuncND selector, void* d);
    
    //
    // Overrides
    //
    virtual __CCCallFuncND* clone() const override;
    virtual void execute() override;
    
CC_CONSTRUCTOR_ACCESS:
    __CCCallFuncND() {}
    virtual ~__CCCallFuncND() {}
    
    /** @~english initializes the action with the callback and the data to pass as an argument  @~chinese 以目标节点，回调函数和数据作为参数来初始化动作 */
    bool initWithTarget(Ref* target, SEL_CallFuncND selector, void* d);

protected:
    SEL_CallFuncND _callFuncND;
    void* _data;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__CCCallFuncND);
};


/** @class __CCCallFuncO
 * @deprecated Please use CallFuncN instead.
 * @brief @~english Calls a 'callback' with an object as the first argument. O means Object.
 * @~chinese 以一个对象作为回调函数的第一个参数的__CCCallFuncO动作。O意味着对象。
 * @since v0.99.5
 * @js NA
 */

class CC_DLL __CCCallFuncO : public CallFunc
{
public:
    /** @~english Creates the action with the callback.
     * typedef void (Ref::*SEL_CallFuncO)(Ref*);
     *
     * @~chinese 使用目标节点，回调函数和对象创建动作
     * typedef void (Ref::*SEL_CallFuncO)(Ref*);
     * 
     * @param target    @~english A certain target.
     * @~chinese 一个特定的目标节点。
     * @param selector  @~english The callback need to be excuted.
     * @~chinese 回调函数。
     * @param object    @~english An object as the callback's first argument.
     * @~chinese 作为回调函数的第一个参数的对象。
     * @return @~english An autoreleased __CCCallFuncO object.
     * @~chinese 一个自释放的 __CCCallFuncO对象。
     */
    CC_DEPRECATED_ATTRIBUTE static __CCCallFuncO * create(Ref* target, SEL_CallFuncO selector, Ref* object);
    //
    // Overrides
    //
    virtual __CCCallFuncO* clone() const override;
    virtual void execute() override;
    
    Ref* getObject() const;
    void setObject(Ref* obj);
    
CC_CONSTRUCTOR_ACCESS:
    __CCCallFuncO();
    virtual ~__CCCallFuncO();

    bool initWithTarget(Ref* target, SEL_CallFuncO selector, Ref* object);
    
protected:
    Ref* _object;
    SEL_CallFuncO _callFuncO;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__CCCallFuncO);
};

// end of actions group
/// @}

NS_CC_END

#endif //__CCINSTANT_ACTION_H__
