/*
 *
 * A menu that does not send any events, it's simply a passive container (lets the contents do their own thing) of CCNodes
 */
#ifndef __CCMENU_PASSIVE_H__
#define __CCMENU_PASSIVE_H__

#include "cocos2d.h"
#include "CCControl.h"


class CCMenuPassive : public CCLayer, public CCRGBAProtocol
{
		/** Color: conforms with CCRGBAProtocol protocol */
		CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
		/** Opacity: conforms with CCRGBAProtocol protocol */
		CC_PROPERTY(GLubyte, m_cOpacity, Opacity);

public:
		/** creates an empty CCMenu */
        static CCMenuPassive* node();

        /** creates a CCMenu with it's items */
        static CCMenuPassive* menuWithItems(CCNode* item, ...);

		/** creates a CCMenu with it's item, then use addChild() to add 
		  * other items. It is used for script, it can't init with undetermined
		  * number of variables.
		*/
		static CCMenuPassive*menuWithItem(CCNode* item);

		/** initializes a CCMenu with it's items */
		bool initWithItems(CCNode* item, va_list args);

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

		//RGBA protocol
		virtual void setIsOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
	    virtual bool getIsOpacityModifyRGB(void) { return false;}
};

#endif