
#ifndef __COCOSSTUDIOEXTENSION_H__
#define __COCOSSTUDIOEXTENSION_H__

#include "math/CCAffineTransform.h"

NS_CC_BEGIN

struct CC_DLL ResouceData
{
    int         type;
    std::string file;
    std::string plist;

    ResouceData()
    {
        type = 0;
        file = "";
        plist = "";
    }

    ResouceData(int iType, std::string sFile, std::string sPlist)
    {
        type = iType;
        file = sFile;
        plist = sPlist;
    }
};

class CC_DLL NodeExtension
{
public:
    NodeExtension();
    ~NodeExtension();

private:

};


NS_CC_END


#endif