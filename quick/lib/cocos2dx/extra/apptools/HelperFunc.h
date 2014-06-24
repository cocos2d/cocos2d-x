#ifndef Cocos2Dx_ZJF_HelperFunc_h
#define Cocos2Dx_ZJF_HelperFunc_h

NS_CC_BEGIN

class CZHelperFunc
{
public:
    static int getFileData(const char *pPathFile);
    static unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);

private:

};

NS_CC_END

#endif //Cocos2Dx_ZJF_HelperFunc_h
