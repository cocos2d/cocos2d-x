#ifndef _CCBX_CCBREADERPARAMS_H_
#define _CCBX_CCBREADERPARAMS_H_

#include <string>
#include <map>
#include <vector>
#include "base/CCRef.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN

namespace spritebuilder {

class CC_DLL CCBReaderParams : public cocos2d::Ref
{
public:
    
    static CCBReaderParams *create(const std::string &path);
    
    const cocos2d::Size &getDesignResolution() const { return _designResolution; }
    const float &getDesignResolutionScale() const { return _designResolutionscale; }
    
    void setLanguage(const std::string &language);
    const std::string &getLanguage() const;
    const std::string &getLocalizedString(const std::string &key) const;
    std::vector<std::string> getLanguagesList() const;
    
CC_CONSTRUCTOR_ACCESS:
    CCBReaderParams();
    ~CCBReaderParams();
    bool initWithPath(const std::string &path);
    
private:
    bool loadParams(const std::string &path);
    bool loadLocalization(const std::string &path);
    
private:
    cocos2d::Size _designResolution;
    float _designResolutionscale;
    std::string _curentLanguage;
    std::map<std::string,std::map<std::string,std::string>> _languages;
};

}

NS_CC_END

#endif
