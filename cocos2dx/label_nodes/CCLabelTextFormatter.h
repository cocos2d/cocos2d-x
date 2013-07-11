//
//  CCLabelTextFormatter.h
//  TestNewStringStuff
//
//  Created by Carlo Morgantini on 6/27/13.
//
//

#ifndef __CCLabelTextFormatter__
#define __CCLabelTextFormatter__

#include "CClabelTextFormatProtocol.h"

NS_CC_BEGIN

class LabelTextFormatter
{
public:
    
    static bool multilineText(LabelTextFormatProtocol *theLabel);
    static bool alignText(LabelTextFormatProtocol *theLabel);
    static bool createStringSprites(LabelTextFormatProtocol *theLabel);

};

NS_CC_END

#endif
