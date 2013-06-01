#ifndef _COCOA_SERIALIZATION_TEST_H_
#define _COCOA_SERIALIZATION_TEST_H_

#include "../testBasic.h"
#include <vector>
#include <string>

class CocoaSerializationTestScene : public TestScene
{
public:
    virtual void runThisTest();

    CocoaSerializationTestScene();

protected:
    void runNextResource(float);

private:
    std::vector<std::string> m_resources;
    size_t m_nextResource;
    int m_failures;
    CCLabelTTF *m_progress;
};

#endif
