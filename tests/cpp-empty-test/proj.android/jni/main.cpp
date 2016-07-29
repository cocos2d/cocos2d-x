#include "AppDelegate.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#include "cocos2d.h"

#define  LOG_TAG    "cpp-empty-test"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define logfunc(format,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,(format "\n"),##__VA_ARGS__)

using namespace cocos2d;

#include <assert.h>

class SimpleNode
{
public:
    SimpleNode(int z, unsigned int a)
    {
        _localZOrder = 0;
        setLocalZOrder(z);
        setOrderOfArrival(a);
    }

    int getLocalZOrder() const
    {
        return static_cast<int>(((_localZOrder >> 32) & 0xffffffff));
    }

    unsigned int getOrderOfArrival() const
    {
        return static_cast<unsigned int>((_localZOrder) & 0xffffffff);
    }

    void setLocalZOrder(int z)
    {
        _localZOrder = ((0ULL + z) << 32) | (_localZOrder & 0xffffffff);
        _o_localZOrder = z;
    }

    void setOrderOfArrival(unsigned int orderOfArrival)
    {
        _localZOrder = (_localZOrder & 0xffffffff00000000) | orderOfArrival;
        _o_orderOfArrival = orderOfArrival;
    }

    int _o_localZOrder;
    unsigned int _o_orderOfArrival;

    std::int64_t _localZOrder;
};

#if !defined(CC_64BITS)
 /*********************************/
 /** 64bits Program Sense Macros **/
 /*********************************/
#if defined(_M_X64) || defined(_WIN64) || defined(__LP64__) || defined(_LP64) || defined(__x86_64)
#define CC_64BITS 1
#else
#define CC_64BITS 0
#endif
#endif

inline bool nodeComparisonLess64(SimpleNode* n1, SimpleNode* n2)
{
#if CC_64BITS
    return (n1->_localZOrder < n2->_localZOrder);
#else
    return n1->_o_localZOrder < n2->_o_localZOrder || (n1->_o_localZOrder == n2->_o_localZOrder && n1->_o_orderOfArrival < n2->_o_orderOfArrival);
#endif
}

void runPerfromanceFunc()
{
    SimpleNode n1(0, 1);
    SimpleNode n2(1, 0);
    SimpleNode n3(-3, 500);


    assert(n3.getLocalZOrder() == -3);
    assert(n3.getOrderOfArrival() == 500);
    assert(n1._localZOrder < n2._localZOrder);
    assert(n3._localZOrder < n1._localZOrder);

    logfunc("CC_64BITS = %d", CC_64BITS);

    std::vector<SimpleNode*> vec2;
    logfunc("test program is %d bits!", sizeof(void*) << 3);

    for (auto i = 0; i < 1000000; ++i)
        vec2.push_back(new SimpleNode(2, i + 1));

    clock_t start = 0;

    for (int i = 0; i < 10; ++i) {
        start = clock();
        std::stable_sort(vec2.begin(), vec2.end(), [](const SimpleNode* n1, const SimpleNode* n2) {
            return n1->_o_localZOrder < n2->_o_localZOrder;
        });
        logfunc("std::stable_sort, test round:%d, %lf seconds used.", i + 1, (clock() - start) / (double)CLOCKS_PER_SEC);
    }

    for (int i = 0; i < 10; ++i) {
        start = clock();
        std::sort(vec2.begin(), vec2.end(), [](const SimpleNode* n1, const SimpleNode* n2) {
            return n1->_o_localZOrder < n2->_o_localZOrder || (n1->_o_localZOrder == n2->_o_localZOrder && n1->_o_orderOfArrival < n2->_o_orderOfArrival);
        });
        logfunc("std::sort, no optimize orderOfArrival storage, original implement, test round:%d, %lf seconds used.", i + 1, (clock() - start) / (double)CLOCKS_PER_SEC);
    }

    for (int i = 0; i < 10; ++i) {
        start = clock();
        std::sort(vec2.begin(), vec2.end(), [](const SimpleNode* n1, const SimpleNode* n2) {
#if CC_64BITS
    return (n1->_localZOrder < n2->_localZOrder);
#else
    return n1->_o_localZOrder < n2->_o_localZOrder || (n1->_o_localZOrder == n2->_o_localZOrder && n1->_o_orderOfArrival < n2->_o_orderOfArrival);
#endif
        });
        logfunc("std::sort(lambda expression), optimize orderOfArrival storage, test round:%d, %lf seconds used.", i + 1, (clock() - start) / (double)CLOCKS_PER_SEC);
    }
    for (int i = 0; i < 10; ++i) {
        start = clock();
        std::sort(vec2.begin(), vec2.end(), nodeComparisonLess64);
        logfunc("std::sort(inline function), optimize orderOfArrival storage, test round:%d, %lf seconds used.", i + 1, (clock() - start) / (double)CLOCKS_PER_SEC);
    }
}

void cocos_android_app_init (JNIEnv* env) {
    LOGD("cocos_android_app_init");
    cocos2d::log("call test code at cocos_android_app_init");
    runPerfromanceFunc();
    AppDelegate *pAppDelegate = new AppDelegate();
}
