#ifndef _RESOURCE_HANDLE_H_
#define _RESOURCE_HANDLE_H_

struct AppResourceEntry;
class  TResourceLib;

class ResourceHandle
{
public:
    ResourceHandle();
    ~ResourceHandle();

    void setResourceEntry(const void* pResEntry);
    void release();
    const void* LoadConstRawData(int nResID, unsigned int* nLen);

private:
    TResourceLib* m_pResLib;
};

#endif
