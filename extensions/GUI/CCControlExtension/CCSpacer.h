#ifndef __CCSPACER_H__
#define __CCSPACER_H__

#include "layers_scenes_transitions_nodes/CCLayer.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

class CCSpacer: public CCLayer
{
public:
    static CCSpacer* verticalSpacer(float space);
    static CCSpacer* horizontalSpacer(float space);
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif