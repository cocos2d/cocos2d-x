//
//  CCBXReader.h
//  cocos2d_libs
//
//  Created by Sergey on 29.10.14.
//
//

#ifndef __cocos2d_libs__CCBXReader__
#define __cocos2d_libs__CCBXReader__

#include "base/CCData.h"
#include "base/CCVector.h"
#include "base/CCRefPtr.h"

NS_CC_BEGIN

namespace spritebuilder {
    
    class NodeLoader;
    class NodeLoaderLibrary;
    class CCBSequence;
    class CCBReaderParams;
    
    NodeLoader* ParseCCBXData(const Data &data, const NodeLoaderLibrary *library, const std::string &rootPath, const CCBReaderParams* params);
    NodeLoader* ParseCCBXFile(const std::string &filename, const NodeLoaderLibrary *library, const std::string &rootPath, const CCBReaderParams* params);
}

NS_CC_END

#endif /* defined(__cocos2d_libs__CCBXReader__) */
