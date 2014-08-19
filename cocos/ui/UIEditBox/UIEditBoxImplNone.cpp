#include "UIEditBox.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID ) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS ) && (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC) && (CC_TARGET_PLATFORM != CC_PLATFORM_TIZEN)

NS_CC_BEGIN

namespace ui {

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return NULL;
}

}

NS_CC_END

#endif /* #if (..) */
