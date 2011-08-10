/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011 Zynga Inc.

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

#include <string>
#include "CCAction.h"
#include "selector_protocol.h"

namespace cocos2d {

	/** 
	@brief Instant actions are immediate actions. They don't have a duration like
	the CCIntervalAction actions.
	*/ 
	class CC_DLL CCActionInstant : public CCFiniteTimeAction //<NSCopying>
	{
	public:
		CCActionInstant();
		virtual ~CCActionInstant(){}
		// CCAction methods
		virtual CCObject* copyWithZone(CCZone *pZone);
		virtual bool isDone(void);
		virtual void step(ccTime dt);
		virtual void update(ccTime time);
		//CCFiniteTimeAction method
		virtual CCFiniteTimeAction * reverse(void);
	};

	/** @brief Show the node
	*/
	class CC_DLL CCShow : public CCActionInstant
	{
	public:
		CCShow(){}
		virtual ~CCShow(){}
		//super methods
		virtual void startWithTarget(CCNode *pTarget);
		virtual CCFiniteTimeAction * reverse(void);
	public:
		//override static method
		/** Allocates and initializes the action */
		static CCShow * action();
	};

	/** 
	@brief Hide the node
	*/
	class CC_DLL CCHide : public CCActionInstant
	{
	public:
		CCHide(){}
		virtual ~CCHide(){}
		//super methods
		virtual void startWithTarget(CCNode *pTarget);
		virtual CCFiniteTimeAction * reverse(void);
	public:
		//override static method
		/** Allocates and initializes the action */
		static CCHide * action();
	};

	/** @brief Toggles the visibility of a node
	*/
	class CC_DLL CCToggleVisibility : public CCActionInstant
	{
	public:
		CCToggleVisibility(){}
		virtual ~CCToggleVisibility(){}
		//super method
		virtual void startWithTarget(CCNode *pTarget);
	public:
		//override static method
		/** Allocates and initializes the action */
		static CCToggleVisibility * action();
	};

	/** 
	@brief Flips the sprite horizontally
	@since v0.99.0
	*/
	class CC_DLL CCFlipX : public CCActionInstant
	{
	public:
		CCFlipX()
			:m_bFlipX(false)
		{}
		virtual ~CCFlipX(){}

		/** create the action */
		static CCFlipX * actionWithFlipX(bool x);
		/** init the action */
		bool initWithFlipX(bool x);
		//super methods
		virtual void startWithTarget(CCNode *pTarget);
		virtual CCFiniteTimeAction * reverse(void);
		virtual CCObject* copyWithZone(CCZone *pZone);

	protected:
		bool	m_bFlipX;
	};

	/** 
	@brief Flips the sprite vertically
	@since v0.99.0
	*/
	class CC_DLL CCFlipY : public CCActionInstant
	{
	public:
		CCFlipY()
			:m_bFlipY(false)
		{}
		virtual ~CCFlipY(){}
		
		/** create the action */
		static CCFlipY * actionWithFlipY(bool y);
		/** init the action */
		bool initWithFlipY(bool y);
		//super methods
		virtual void startWithTarget(CCNode *pTarget);
		virtual CCFiniteTimeAction * reverse(void);
		virtual CCObject* copyWithZone(CCZone *pZone);

	protected:
		bool	m_bFlipY;
	};

	/** @brief Places the node in a certain position
	*/
	class CC_DLL CCPlace : public CCActionInstant //<NSCopying>
	{
	public:
		CCPlace(){}
		virtual ~CCPlace(){}
		/** creates a Place action with a position */
		static CCPlace * actionWithPosition(CCPoint pos);
		/** Initializes a Place action with a position */
		bool initWithPosition(CCPoint pos);
		//super methods
		virtual void startWithTarget(CCNode *pTarget);
		virtual CCObject* copyWithZone(CCZone *pZone);
	protected:
		CCPoint m_tPosition;
	};

	/** @brief Calls a 'callback'
	*/
	class CC_DLL CCCallFunc : public CCActionInstant //<NSCopying>
	{
	public:
		CCCallFunc()
            : m_pSelectorTarget(NULL)
            , m_pCallFunc(NULL)
			, m_scriptFuncName("")
        {
		}
		virtual ~CCCallFunc()
		{
			if (m_pSelectorTarget)
			{
				m_pSelectorTarget->selectorProtocolRelease();
			}
		}
		/** creates the action with the callback 

		typedef void (SelectorProtocol::*SEL_CallFunc)();
		*/
		static CCCallFunc * actionWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFunc selector);
		static CCCallFunc* actionWithScriptFuncName(const char* pszFuncName);
		/** initializes the action with the callback 
		
		typedef void (SelectorProtocol::*SEL_CallFunc)();
		*/
		virtual bool initWithTarget(SelectorProtocol* pSelectorTarget);
		virtual bool initWithScriptFuncName(const char* pszFuncName);
		/** executes the callback */
		virtual void execute();
		//super methods
		virtual void startWithTarget(CCNode *pTarget);
		CCObject * copyWithZone(cocos2d::CCZone *pZone);

		void registerScriptFunction(const char* pszFunctionName);

		inline SelectorProtocol* getTargetCallback()
		{
			return m_pSelectorTarget;
		}

		inline void setTargetCallback(SelectorProtocol* pSel)
		{
			if (pSel != m_pSelectorTarget)
			{
				if (m_pSelectorTarget)
				{
					m_pSelectorTarget->selectorProtocolRelease();
				}
				
				m_pSelectorTarget = pSel;

				if (m_pSelectorTarget)
				{
					m_pSelectorTarget->selectorProtocolRetain();
				}				
			}
		}

	protected:
		/** Target that will be called */
		SelectorProtocol*   m_pSelectorTarget;
		/** the script function name to call back */
		std::string         m_scriptFuncName;

		union
		{
			SEL_CallFunc	m_pCallFunc;
			SEL_CallFuncN	m_pCallFuncN;
			SEL_CallFuncND	m_pCallFuncND;
            SEL_CallFuncO   m_pCallFuncO;
		};
	};

	/** 
	@brief Calls a 'callback' with the node as the first argument
	N means Node
	*/
	class CC_DLL CCCallFuncN : public CCCallFunc
	{
	public:
		CCCallFuncN(){}
		virtual ~CCCallFuncN(){}
		/** creates the action with the callback 

		typedef void (SelectorProtocol::*SEL_CallFuncN)(CCNode*);
		*/
		static CCCallFuncN * actionWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncN selector);
		static CCCallFuncN* actionWithScriptFuncName(const char* pszFuncName);
		/** initializes the action with the callback 

		typedef void (SelectorProtocol::*SEL_CallFuncN)(CCNode*);
		*/
		virtual bool initWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncN selector);
		// super methods
		virtual CCObject* copyWithZone(CCZone *pZone);
		virtual void execute();
	};


	/** 
	@brief Calls a 'callback' with the node as the first argument and the 2nd argument is data
	* ND means: Node and Data. Data is void *, so it could be anything.
	*/
	class CC_DLL CCCallFuncND : public CCCallFuncN
	{
	public:

		/** creates the action with the callback and the data to pass as an argument */
		static CCCallFuncND * actionWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncND selector, void* d);
		static CCCallFuncND* actionWithScriptFuncName(const char* pszFuncName, void *d);
		/** initializes the action with the callback and the data to pass as an argument */
		virtual bool initWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncND selector, void* d);
		// super methods
		virtual CCObject* copyWithZone(CCZone *pZone);
		virtual void execute();

	protected:
		void			*m_pData;
	};


    /**
    @brief Calls a 'callback' with an object as the first argument.
    O means Object.
    @since v0.99.5
    */
    class CC_DLL CCCallFuncO : public CCCallFunc
    {
    public:
        CCCallFuncO();
        virtual ~CCCallFuncO();
        /** creates the action with the callback 

        typedef void (SelectorProtocol::*SEL_CallFuncO)(CCObject*);
        */
        static CCCallFuncO * actionWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncO selector, CCObject* pObject);
		static CCCallFuncO* actionWithScriptFuncName(const char* pszFuncName);
        /** initializes the action with the callback 

        typedef void (SelectorProtocol::*SEL_CallFuncO)(CCObject*);
        */
        virtual bool initWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncO selector, CCObject* pObject);
        // super methods
        virtual CCObject* copyWithZone(CCZone *pZone);
        virtual void execute();

		inline CCObject* getObject()
		{
			return m_pObject;
		}

		inline void setObject(CCObject* pObj)
		{
			if (pObj != m_pObject)
			{
				CC_SAFE_RELEASE(m_pObject);
				m_pObject = pObj;
				CC_SAFE_RETAIN(m_pObject);
			}
		}

    protected:
		/** object to be passed as argument */
        CCObject* m_pObject;
    };

}

#endif //__CCINSTANT_ACTION_H__
