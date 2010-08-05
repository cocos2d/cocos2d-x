/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCAction.h"
#include "selector_protocol.h"

namespace cocos2d {

	/** Instant actions are immediate actions. They don't have a duration like
	the CCIntervalAction actions.
	*/ 
	class CCX_DLL CCInstantAction : public CCFiniteTimeAction //<NSCopying>
	{
	public:
		CCInstantAction();
		virtual ~CCInstantAction(){}
		// CCAction method
		virtual NSObject* copyWithZone(NSZone *pZone);
		virtual bool isDone(void);
		virtual void step(ccTime dt);
		virtual void update(ccTime time);
		//CCFiniteTimeAction method
		virtual CCFiniteTimeAction * reverse(void);

	};

	/** Show the node
	*/
	class CCX_DLL CCShow : public CCInstantAction
	{
	public:
		CCShow(){}
		virtual ~CCShow(){}
		//super method
		virtual void startWithTarget(NSObject *pTarget);
		virtual CCFiniteTimeAction * reverse(void);
	};

	/** Hide the node
	*/
	class CCX_DLL CCHide : public CCInstantAction
	{
	public:
		CCHide(){}
		virtual ~CCHide(){}
		//super method
		virtual void startWithTarget(NSObject *pTarget);
		virtual CCFiniteTimeAction * reverse(void);
	};

	/** Toggles the visibility of a node
	*/
	class CCX_DLL CCToggleVisibility : public CCInstantAction
	{
	public:
		CCToggleVisibility(){}
		virtual ~CCToggleVisibility(){}
		//super method
		virtual void startWithTarget(NSObject *pTarget);

	};

	/** Flips the sprite horizontally
	@since v0.99.0
	*/
	class CCX_DLL CCFlipX : public CCInstantAction
	{
	public:
		CCFlipX(){}
		virtual ~CCFlipX(){}

		static CCFlipX * actionWithFlipX(bool x);
		CCFlipX * initWithFlipX(bool x);
		//super method
		virtual void startWithTarget(NSObject *pTarget);
		virtual CCFiniteTimeAction * reverse(void);
		virtual NSObject* copyWithZone(NSZone *pZone);

	protected:
		bool	m_bFlipX;
	};

	/** Flips the sprite vertically
	@since v0.99.0
	*/
	class CCX_DLL CCFlipY : public CCInstantAction
	{
	public:
		CCFlipY(){}
		virtual ~CCFlipY(){}
			
		static CCFlipY * actionWithFlipY(bool y);
		CCFlipY * initWithFlipY(bool y);
		//super method
		virtual void startWithTarget(NSObject *pTarget);
		virtual CCFiniteTimeAction * reverse(void);
		virtual NSObject* copyWithZone(NSZone *pZone);

	protected:
		bool	m_bFlipY;
	};

	/** Places the node in a certain position
	*/
	class CCX_DLL CCPlace : public CCInstantAction //<NSCopying>
	{
	public:
		CCPlace(){}
		virtual ~CCPlace(){}
		/** creates a Place action with a position */
		static CCPlace * actionWithPosition(CGPoint pos);
		/** Initializes a Place action with a position */
		CCPlace * initWithPosition(CGPoint pos);
		//super method
		virtual void startWithTarget(NSObject *pTarget);
		virtual NSObject* copyWithZone(NSZone *pZone);
	protected:
		CGPoint m_tPosition;
	};

	/** Calls a 'callback'
	*/
	class CCX_DLL CCCallFunc : public CCInstantAction //<NSCopying>
	{
	public:
		CCCallFunc()
		{
			m_pCallFunc = NULL;
			m_pSelectorTarget = NULL;
		}
		virtual ~CCCallFunc()
		{
		}
		static CCCallFunc * actionWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFunc selector);
		virtual CCCallFunc * initWithTarget(SelectorProtocol* pSelectorTarget);
		virtual void execute();
		//super method
		virtual void startWithTarget(NSObject *pTarget);
		NSObject * copyWithZone(cocos2d::NSZone *pZone);

	protected:
		SelectorProtocol*   m_pSelectorTarget;
		union
		{
			SEL_CallFunc	m_pCallFunc;
			SEL_CallFuncN	m_pCallFuncN;
			SEL_CallFuncND	m_pCallFuncND;
		};
// 		id targetCallback;
// 		SEL selector;
// 	
// 		/** creates the action with the callback */
// 		+(id) actionWithTarget: (id) t selector:(SEL) s;
// 		/** initializes the action with the callback */
// 		-(id) initWithTarget: (id) t selector:(SEL) s;
// 		/** exeuctes the callback */
// 		-(void) execute;
	};

	/** Calls a 'callback' with the node as the first argument
	N means Node
	*/
	class CCX_DLL CCCallFuncN : public CCCallFunc
	{
	public:
		CCCallFuncN(){}
		virtual ~CCCallFuncN(){}
		static CCCallFuncN * actionWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncN selector);
		// super method
		virtual void execute();
	};


	//typedef void (*CC_CALLBACK_ND)(id, SEL, id, void *);
	/** Calls a 'callback' with the node as the first argument and the 2nd argument is data
	* ND means: Node and Data. Data is void *, so it could be anything.
	*/
	class CCX_DLL CCCallFuncND : public CCCallFuncN
	{
	public:
		/** Invocation object that has the target#selector and the parameters */
		//@property (nonatomic,readwrite) CC_CALLBACK_ND callbackMethod;

		/** creates the action with the callback and the data to pass as an argument */
		static CCCallFuncND * actionWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncND selector, void* d);
		/** initializes the action with the callback and the data to pass as an argument */
		CCCallFuncND * initWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncND selector, void* d);
		// super method
		virtual NSObject* copyWithZone(NSZone *pZone);
		virtual void execute();

	protected:
		void			*m_pData;
		//CC_CALLBACK_ND	m_pfnCallbackMethod;
	};

// Blocks Support

#if NS_BLOCKS_AVAILABLE

		/** Executes a callback using a block
		*/
		@interface CCCallBlock : CCInstantAction<NSCopying>
	{
		void (^block_)();
	}

	/** creates the action with the specified block, to be used as a callback */
	+(id) actionWithBlock:(void(^)())block;

	/** initialized the action with the specified block, to be used as a callback */
	-(id) initWithBlock:(void(^)())block;

	/** executes the callback */
	-(void) execute;
	@end

		@class CCNode;

	/** Executes a callback using a block with a single CCNode parameter
	*/
	@interface CCCallBlockN : CCInstantAction<NSCopying>
	{
		void (^block_)(CCNode *);
	}

	/** creates the action with the specified block, to be used as a callback */
	+(id) actionWithBlock:(void(^)(CCNode *node))block;

	/** initialized the action with the specified block, to be used as a callback */
	-(id) initWithBlock:(void(^)(CCNode *node))block;

	/** executes the callback */
	-(void) execute;
	@end

#endif

}

#endif //__CCINSTANT_ACTION_H__