/**
 * Simple example of a C++ class that can be binded using the
 * automatic script generator
 */

#include "simple_class.h"

SimpleNativeClass::SimpleNativeClass()
{
    // just set some fields
    m_someField = 0;
    m_someOtherField = 10;
    m_anotherMoreComplexField = NULL;
}

// empty destructor
SimpleNativeClass::~SimpleNativeClass()
{
}

// just a very simple function :)
int SimpleNativeClass::doSomeProcessing(std::string arg1, std::string arg2)
{
    return arg1.length() + arg2.length();
}

void SimpleNativeClass::setAnotherMoreComplexField(const char *str)
{
    if (m_anotherMoreComplexField) {
        free(m_anotherMoreComplexField);
    }
    size_t len = strlen(str);
    m_anotherMoreComplexField = (char *)malloc(len);
    memcpy(m_anotherMoreComplexField, str, len);
}

namespace SomeNamespace
{
AnotherClass::AnotherClass()
{
    justOneField = 1313;
    aPublicField = 1337;
}
// empty destructor
AnotherClass::~AnotherClass()
{
}

void AnotherClass::doSomethingSimple() {
    fprintf(stderr, "just doing something simple\n");
}
};
