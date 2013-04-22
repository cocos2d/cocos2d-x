#include "ProtocolIAP.h"

namespace cocos2d { namespace plugin {
    
bool ProtocolIAP::m_bPaying = false;
PayResultListener* ProtocolIAP::m_pListener = NULL;
TProductInfo ProtocolIAP::m_curInfo;

ProtocolIAP::ProtocolIAP()
{
}

ProtocolIAP::~ProtocolIAP()
{
}

bool ProtocolIAP::init()
{
    return true;
}

void ProtocolIAP::initDeveloperInfo(TDeveloperInfo devInfo)
{
}

void ProtocolIAP::payForProduct(TProductInfo info)
{
}

void ProtocolIAP::setResultListener(PayResultListener* pListener)
{
    m_pListener = pListener;
}

void ProtocolIAP::payResult(EPayResult ret, const char* msg)
{
    m_bPaying = false;
    if (m_pListener)
    {
        m_pListener->payResult(ret, msg, m_curInfo);
    }

    m_curInfo.clear();
}

const char* ProtocolIAP::getSDKVersion()
{
    return "Subclass should override this interface";
}

void ProtocolIAP::setDebugMode(bool debug)
{
}

}} //namespace cocos2d { namespace plugin {
