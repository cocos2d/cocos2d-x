
#ifndef __CC_EXTENSION_CCSTORE_PRODUCT_H_
#define __CC_EXTENSION_CCSTORE_PRODUCT_H_

#include "cocos2dx_extra.h"
#include "cocos2d.h"

NS_CC_EXTRA_BEGIN

#pragma mark -
#pragma mark StoreProduct

class StoreProduct : public cocos2d::Ref
{
public:
    static StoreProduct* productWithId(const char* productIdentifier,
                                         const char* localizedTitle,
                                         const char* localizedDescription,
                                         float price,
                                         const char* priceLocale);
    
    const std::string& getProductIdentifier(void)
    {
        return m_productIdentifier;
    }
    
    const std::string& getLocalizedTitle(void)
    {
        return m_localizedTitle;
    }
    
    const std::string& getLocalizedDescription(void)
    {
        return m_localizedDescription;
    }
    
    float getPrice(void)
    {
        return m_price;
    }
    
    const std::string& getPriceLocale(void)
    {
        return m_priceLocale;
    }
    
private:
    StoreProduct(void) {}
    bool initWithId(const char* productIdentifier,
                    const char* localizedTitle,
                    const char* localizedDescription,
                    float price,
                    const char* priceLocale);
    
    std::string m_productIdentifier;
    std::string m_localizedTitle;
    std::string m_localizedDescription;
    float       m_price;
    std::string m_priceLocale;
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCSTORE_PRODUCT_H_
