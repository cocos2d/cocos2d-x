/*
 *
 * A menu that does not send any events, it's simply a passive container (lets the contents do their own thing) of CCNodes
 */
#ifndef __CCMENU_PASSIVE_H__
#define __CCMENU_PASSIVE_H__

#include "CCControl.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

class CCMenuPassive : public CCLayer, public CCRGBAProtocol
{
        /** Color: conforms with CCRGBAProtocol protocol */
        CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
        /** Opacity: conforms with CCRGBAProtocol protocol */
        CC_PROPERTY(GLubyte, m_cOpacity, Opacity);

public:
        /** creates an empty CCMenu 
        @deprecated: This interface will be deprecated sooner or later.
        */
        CC_DEPRECATED_ATTRIBUTE static CCMenuPassive* node();

        /** creates a CCMenu with it's items 
        @deprecated: This interface will be deprecated sooner or later.
        */
        CC_DEPRECATED_ATTRIBUTE static CCMenuPassive* menuWithItems(CCNode* item, ...);

        /** creates a CCMenu with it's item, then use addChild() to add 
          * other items. It is used for script, it can't init with undetermined
          * number of variables.
          @deprecated: This interface will be deprecated sooner or later.
        */
        CC_DEPRECATED_ATTRIBUTE static CCMenuPassive* menuWithItem(CCNode* item);

        /** creates an empty CCMenu */
        static CCMenuPassive* create();

        /** creates a CCMenu with it's items */
        static CCMenuPassive* create(CCNode* item, ...);

        /** creates a CCMenu with it's item, then use addChild() to add 
          * other items. It is used for script, it can't init with undetermined
          * number of variables.
        */
        static CCMenuPassive* createWithItem(CCNode* item);

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
        virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
        virtual bool isOpacityModifyRGB(void) { return false;}
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif