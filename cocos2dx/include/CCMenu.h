/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
#ifndef __CCMENU_H_
#define __CCMENU_H_

#include "CCMenuItem.h"
#include "CCLayer.h"

namespace cocos2d{

	typedef enum  
	{
        kCCMenuStateWaiting,
        kCCMenuStateTrackingTouch
    } tCCMenuState;

    enum {
        //* priority used by the menu
        kCCMenuTouchPriority = -128,
    };

	/** @brief A CCMenu
	* 
	* Features and Limitation:
	*  - You can add MenuItem objects in runtime using addChild:
	*  - But the only accecpted children are MenuItem objects
	*/
	class CC_DLL CCMenu : public CCLayer, public CCRGBAProtocol
	{
		/** Color: conforms with CCRGBAProtocol protocol */
		CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
		/** Opacity: conforms with CCRGBAProtocol protocol */
		CC_PROPERTY(GLubyte, m_cOpacity, Opacity);
	public:
		CCMenu()
			: m_cOpacity(0)
			, m_pSelectedItem(NULL)
		{}
		virtual ~CCMenu(){}

                /** creates an empty CCMenu */
                static CCMenu* node();

                /** creates a CCMenu with it's items */
                static CCMenu* menuWithItems(CCMenuItem* item, ...);

		/** creates a CCMenu with it's item, then use addChild() to add 
		  * other items. It is used for script, it can't init with undetermined
		  * number of variables.
		*/
		static CCMenu*menuWithItem(CCMenuItem* item);

		/** initializes a CCMenu with it's items */
		bool initWithItems(CCMenuItem* item, va_list args);

		/** align items vertically */
		void alignItemsVertically();
		/** align items vertically with padding
		@since v0.7.2
		*/
		void alignItemsVerticallyWithPadding(float padding);

		/** align items horizontally */
		void alignItemsHorizontally();
		/** align items horizontally with padding
		@since v0.7.2
		*/
		void alignItemsHorizontallyWithPadding(float padding);

		/** align items in rows of columns */
		void alignItemsInColumns(unsigned int columns, ...);
		void alignItemsInColumns(unsigned int columns, va_list args);

		/** align items in columns of rows */
		void alignItemsInRows(unsigned int rows, ...);
		void alignItemsInRows(unsigned int rows, va_list args);

		//super methods
		virtual void addChild(CCNode * child, int zOrder);
		virtual void addChild(CCNode * child, int zOrder, int tag);
		virtual void registerWithTouchDispatcher();

        /**
        @brief For phone event handle functions
        */
		virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
		virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
		virtual void ccTouchCancelled(CCTouch *touch, CCEvent* event);
		virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

        /**
        @since v0.99.5
        override onExit
        */
        virtual void onExit();

		virtual void setIsOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
	    virtual bool getIsOpacityModifyRGB(void) { return false;}

	protected:
		CCMenuItem* itemForTouch(CCTouch * touch);
		tCCMenuState m_eState;
		CCMenuItem *m_pSelectedItem;		
	};
}

#endif//__CCMENU_H_
