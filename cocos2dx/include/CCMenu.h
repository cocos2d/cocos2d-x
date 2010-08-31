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
#ifndef __CCMENU_H_
#define __CCMENU_H_

#include "CCMenuItem.h"
#include "CCLayer.h"

namespace cocos2d{

	typedef enum  
	{
		kMenuStateWaiting,
		kMenuStateTrackingTouch
	} MenuState;

	/** A CCMenu
	* 
	* Features and Limitation:
	*  - You can add MenuItem objects in runtime using addChild:
	*  - But the only accecpted children are MenuItem objects
	*/
	class CCX_DLL CCMenu : public CCLayer, public CCRGBAProtocol
	{
	public:
		CCMenu(){}
		virtual ~CCMenu(){}
		/** creates a CCMenu with it's items */
		static CCMenu* menuWithItems(CCMenuItem* item, ...);

		/** initializes a CCMenu with it's items */
		CCMenu * initWithItems(CCMenuItem* item, va_list args);

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
		virtual CCNode * addChild(CCNode * child, int zOrder);
		virtual CCNode * addChild(CCNode * child, int zOrder, int tag);
		virtual void registerWithTouchDispatcher();
		virtual bool ccTouchBegan(CCTouch* touch, UIEvent* event);
		virtual void ccTouchEnded(CCTouch* touch, UIEvent* event);
		virtual void ccTouchCancelled(CCTouch *touch, UIEvent* event);
		virtual void ccTouchMoved(CCTouch* touch, UIEvent* event);
		virtual void destroy(void);
		virtual void keep(void);

		virtual void setOpacity(GLubyte opacity);
		virtual GLubyte getOpacity(void);
		virtual ccColor3B getColor(void);
		virtual void setColor(ccColor3B color);

		virtual CCRGBAProtocol* convertToRGBAProtocol() { return (CCRGBAProtocol*)this; }

	private:
		CCMenuItem* itemForTouch(CCTouch * touch);

	protected:
		MenuState m_eState;
		CCMenuItem *m_pSelectedItem;
		GLubyte m_cOpacity;
		ccColor3B m_tColor;
	};
}

#endif//__CCMENU_H_