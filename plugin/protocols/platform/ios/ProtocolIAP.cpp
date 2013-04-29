#include "ProtocolIAP.h"

namespace cocos2d { namespace plugin {
    
bool ProtocolIAP::m_bPaying = false;

ProtocolIAP::ProtocolIAP()
: m_pListener(NULL)
{
}

ProtocolIAP::~ProtocolIAP()
{
}

bool ProtocolIAP::init()
{
    return true;
}

void ProtocolIAP::configDeveloperInfo(TIAPDeveloperInfo devInfo)
{
}

void ProtocolIAP::payForProduct(TProductInfo info)
{
}

void ProtocolIAP::setResultListener(PayResultListener* pListener)
{
    m_pListener = pListener;
}

void ProtocolIAP::onPayResult(PayResultCode ret, const char* msg)
{
    m_bPaying = false;
    if (m_pListener)
    {
        m_pListener->onPayResult(ret, msg, m_curInfo);
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
