#include "UnitTest.h"
#include "RefPtrTest.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#if defined (__arm64__)
#define USE_NEON64
#define INCLUDE_NEON64
#elif defined (__ARM_NEON__)
#define USE_NEON32
#define INCLUDE_NEON32
#else
#endif
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#if defined (__arm64__) || defined (__aarch64__)
#define USE_NEON64
#define INCLUDE_NEON64
#elif defined (__ARM_NEON__)
#define INCLUDE_NEON32
#else
#endif
#else

#endif

#if defined (__SSE__)
#define USE_SSE
#define INCLUDE_SSE
#endif

#if (defined INCLUDE_NEON64) || (defined INCLUDE_NEON32) // FIXME: || (defined INCLUDE_SSE)
#define UNIT_TEST_FOR_OPTIMIZED_MATH_UTIL
#endif


// For ' < o > ' multiply test scene.

UnitTests::UnitTests()
{
    ADD_TEST_CASE(TemplateVectorTest);
    ADD_TEST_CASE(TemplateMapTest);
    ADD_TEST_CASE(ValueTest);
    ADD_TEST_CASE(RefPtrTest);
    ADD_TEST_CASE(UTFConversionTest);
#ifdef UNIT_TEST_FOR_OPTIMIZED_MATH_UTIL
    ADD_TEST_CASE(MathUtilTest);
#endif
};

std::string UnitTestDemo::title() const
{
    return "UnitTest";
}

//---------------------------------------------------------------

void TemplateVectorTest::onEnter()
{
    UnitTestDemo::onEnter();

    Vector<Node*> vec;
    CCASSERT(vec.empty(), "");
    CCASSERT(vec.capacity() == 0, "");
    CCASSERT(vec.size() == 0, "");
    CCASSERT(vec.max_size() > 0, "");

    auto node1 = Node::create();
    node1->setTag(1);
    vec.pushBack(node1);
    CCASSERT(node1->getReferenceCount() == 2, "");

    auto node2 = Node::create();
    node2->setTag(2);
    vec.pushBack(node2);
    CCASSERT(vec.getIndex(node1) == 0, "");
    CCASSERT(vec.getIndex(node2) == 1, "");

    auto node3 = Node::create();
    node3->setTag(3);
    vec.insert(1, node3);
    CCASSERT(vec.at(0)->getTag() == 1, "");
    CCASSERT(vec.at(1)->getTag() == 3, "");
    CCASSERT(vec.at(2)->getTag() == 2, "");

    // Test copy constructor
    Vector<Node*> vec2(vec);
    CCASSERT(vec2.size() == vec.size(), "");
    ssize_t size = vec.size();
    for (ssize_t i = 0; i < size; ++i)
    {
        CCASSERT(vec2.at(i) == vec.at(i), "");
        CCASSERT(vec.at(i)->getReferenceCount() == 3, "");
        CCASSERT(vec2.at(i)->getReferenceCount() == 3, "");
    }

    // Test copy assignment operator
    Vector<Node*> vec3;
    vec3 = vec2;
    CCASSERT(vec3.size() == vec2.size(), "");
    size = vec3.size();
    for (ssize_t i = 0; i < size; ++i)
    {
        CCASSERT(vec3.at(i) == vec2.at(i), "");
        CCASSERT(vec3.at(i)->getReferenceCount() == 4, "");
        CCASSERT(vec2.at(i)->getReferenceCount() == 4, "");
        CCASSERT(vec.at(i)->getReferenceCount() == 4, "");
    }

    // Test move constructor

    auto createVector = [this](){
        Vector<Node*> ret;

        for (int i = 0; i < 20; i++)
        {
            ret.pushBack(Node::create());
        }

        int j = 1000;
        for (auto& child : ret)
        {
            child->setTag(j++);
        }

        return ret;
    };

    Vector<Node*> vec4(createVector());
    for (const auto& child : vec4)
    {
        CC_UNUSED_PARAM(child);
        CCASSERT(child->getReferenceCount() == 2, "");
    }

    // Test init Vector<T> with capacity
    Vector<Node*> vec5(10);
    CCASSERT(vec5.capacity() == 10, "");
    vec5.reserve(20);
    CCASSERT(vec5.capacity() == 20, "");

    CCASSERT(vec5.size() == 0, "");
    CCASSERT(vec5.empty(), "");

    auto toRemovedNode = Node::create();
    vec5.pushBack(toRemovedNode);
    CCASSERT(toRemovedNode->getReferenceCount() == 2, "");

    // Test move assignment operator
    vec5 = createVector();
    CCASSERT(toRemovedNode->getReferenceCount() == 1, "");
    CCASSERT(vec5.size() == 20, "size should be 20");

    for (const auto& child : vec5)
    {
        CC_UNUSED_PARAM(child);
        CCASSERT(child->getReferenceCount() == 2, "");
    }

    // Test Vector<T>::find
    CCASSERT(vec.find(node3) == (vec.begin() + 1), "");
    CCASSERT(std::find(std::begin(vec), std::end(vec), node2) == (vec.begin() + 2), "");

    CCASSERT(vec.front()->getTag() == 1, "");
    CCASSERT(vec.back()->getTag() == 2, "");

    CCASSERT(vec.getRandomObject(), "");
    CCASSERT(!vec.contains(Node::create()), "");
    CCASSERT(vec.contains(node1), "");
    CCASSERT(vec.contains(node2), "");
    CCASSERT(vec.contains(node3), "");
    CCASSERT(vec.equals(vec2), "");
    CCASSERT(vec.equals(vec3), "");

    // Insert
    vec5.insert(2, node1);
    CCASSERT(vec5.at(2)->getTag() == 1, "");
    CCASSERT(vec5.size() == 21, "");
    vec5.back()->setTag(100);
    vec5.popBack();
    CCASSERT(vec5.size() == 20, "");
    CCASSERT(vec5.back()->getTag() != 100, "");

    // Erase and clear
    Vector<Node*> vec6 = createVector();
    Vector<Node*> vec7 = vec6;  // Copy for check

    CCASSERT(vec6.size() == 20, "");
    vec6.erase(vec6.begin() + 1);  //
    CCASSERT(vec6.size() == 19, "");
    CCASSERT((*(vec6.begin() + 1))->getTag() == 1002, "");
    vec6.erase(vec6.begin() + 2, vec6.begin() + 10);
    CCASSERT(vec6.size() == 11, "");
    CCASSERT(vec6.at(0)->getTag() == 1000, "");
    CCASSERT(vec6.at(1)->getTag() == 1002, "");
    CCASSERT(vec6.at(2)->getTag() == 1011, "");
    CCASSERT(vec6.at(3)->getTag() == 1012, "");
    vec6.erase(3);
    CCASSERT(vec6.at(3)->getTag() == 1013, "");
    vec6.eraseObject(vec6.at(2));
    CCASSERT(vec6.at(2)->getTag() == 1013, "");
    vec6.clear();
    
    auto objA = Node::create(); // retain count is 1
    auto objB = Node::create();
    auto objC = Node::create();
    {
        Vector<Node*> array1;
        Vector<Node*> array2;
        
        // push back objA 3 times
        array1.pushBack(objA); // retain count is 2
        array1.pushBack(objA); // retain count is 3
        array1.pushBack(objA); // retain count is 4
        
        array2.pushBack(objA); // retain count is 5
        array2.pushBack(objB);
        array2.pushBack(objC);
        
        for (auto obj : array1) {
            array2.eraseObject(obj);
        }
        CCASSERT(objA->getReferenceCount() == 4, "");
    }
    CCASSERT(objA->getReferenceCount() == 1, "");
    
    {
        Vector<Node*> array1;
        // push back objA 3 times
        array1.pushBack(objA); // retain count is 2
        array1.pushBack(objA); // retain count is 3
        array1.pushBack(objA); // retain count is 4
        CCASSERT(objA->getReferenceCount() == 4, "");
        array1.eraseObject(objA, true); // Remove all occurrences in the Vector.
        CCASSERT(objA->getReferenceCount() == 1, "");
        
        array1.pushBack(objA); // retain count is 2
        array1.pushBack(objA); // retain count is 3
        array1.pushBack(objA); // retain count is 4
        
        array1.eraseObject(objA, false);
        CCASSERT(objA->getReferenceCount() == 3, ""); // Only remove the first occurrence in the Vector.
    }

    // Check the retain count in vec7
    CCASSERT(vec7.size() == 20, "");
    for (const auto& child : vec7)
    {
        CC_UNUSED_PARAM(child);
        CCASSERT(child->getReferenceCount() == 2, "");
    }

    // Sort
    Vector<Node*> vecForSort = createVector();
    std::sort(vecForSort.begin(), vecForSort.end(), [](Node* a, Node* b){
        return a->getTag() >= b->getTag();
    });

    for (int i = 0; i < 20; ++i)
    {
        CCASSERT(vecForSort.at(i)->getTag() - 1000 == (19 - i), "");
    }

    // Reverse
    vecForSort.reverse();
    for (int i = 0; i < 20; ++i)
    {
        CCASSERT(vecForSort.at(i)->getTag() - 1000 == i, "");
    }

    // Swap
    Vector<Node*> vecForSwap = createVector();
    vecForSwap.swap(2, 4);
    CCASSERT(vecForSwap.at(2)->getTag() == 1004, "");
    CCASSERT(vecForSwap.at(4)->getTag() == 1002, "");
    vecForSwap.swap(vecForSwap.at(2), vecForSwap.at(4));
    CCASSERT(vecForSwap.at(2)->getTag() == 1002, "");
    CCASSERT(vecForSwap.at(4)->getTag() == 1004, "");

    // shrinkToFit
    Vector<Node*> vecForShrink = createVector();
    vecForShrink.reserve(100);
    CCASSERT(vecForShrink.capacity() == 100, "");
    vecForShrink.pushBack(Node::create());
    vecForShrink.shrinkToFit();
    CCASSERT(vecForShrink.capacity() == 21, "");

    // get random object
    // Set the seed by time
    srand((unsigned)time(nullptr));
    Vector<Node*> vecForRandom = createVector();
    log("<--- begin ---->");
    for (int i = 0; i < vecForRandom.size(); ++i)
    {
        log("Vector: random object tag = %d", vecForRandom.getRandomObject()->getTag());
    }
    log("<---- end  ---->");

    // Self assignment
    Vector<Node*> vecSelfAssign = createVector();
    vecSelfAssign = vecSelfAssign;
    CCASSERT(vecSelfAssign.size() == 20, "");

    for (const auto& child : vecSelfAssign)
    {
        CC_UNUSED_PARAM(child);
        CCASSERT(child->getReferenceCount() == 2, "");
    }

    vecSelfAssign = std::move(vecSelfAssign);
    CCASSERT(vecSelfAssign.size() == 20, "");

    for (const auto& child : vecSelfAssign)
    {
        CC_UNUSED_PARAM(child);
        CCASSERT(child->getReferenceCount() == 2, "");
    }

    // const at
    Vector<Node*> vecConstAt = createVector();
    constFunc(vecConstAt);
}

void TemplateVectorTest::constFunc(const Vector<Node*>& vec) const
{
    log("vec[8] = %d", vec.at(8)->getTag());
}

std::string TemplateVectorTest::subtitle() const
{
    return "Vector<T>, should not crash";
}


//---------------------------------------------------------------

void TemplateMapTest::onEnter()
{
    UnitTestDemo::onEnter();

    auto createMap = [this](){
        Map<std::string, Node*> ret;
        for (int i = 0; i < 20; ++i)
        {
            auto node = Node::create();
            node->setTag(1000 + i);
            ret.insert(StringUtils::toString(i), node);
        }

        return ret;
    };

    // Default constructor
    Map<std::string, Node*> map1;
    CCASSERT(map1.empty(), "");
    CCASSERT(map1.size() == 0, "");
    CCASSERT(map1.keys().empty(), "");
    CCASSERT(map1.keys(Node::create()).empty(), "");

    // Move constructor
    Map<std::string, Node*> map2 = createMap();
    for (const auto& e : map2)
    {
        CC_UNUSED_PARAM(e);
        CCASSERT(e.second->getReferenceCount() == 2, "");
    }

    // Copy constructor
    Map<std::string, Node*> map3(map2);
    for (const auto& e : map3)
    {
        CC_UNUSED_PARAM(e);
        CCASSERT(e.second->getReferenceCount() == 3, "");
    }

    // Move assignment operator
    Map<std::string, Node*> map4;
    auto unusedNode = Node::create();
    map4.insert("unused",unusedNode);
    map4 = createMap();
    CCASSERT(unusedNode->getReferenceCount() == 1, "");
    for (const auto& e : map4)
    {
        CC_UNUSED_PARAM(e);
        CCASSERT(e.second->getReferenceCount() == 2, "");
    }

    // Copy assignment operator
    Map<std::string, Node*> map5;
    map5 = map4;
    for (const auto& e : map5)
    {
        CC_UNUSED_PARAM(e);
        CCASSERT(e.second->getReferenceCount() == 3, "");
    }

    // Check size
    CCASSERT(map4.size() == map5.size(), "");

    for (const auto& e : map4)
    {
        CC_UNUSED_PARAM(e);
        CCASSERT(e.second == map5.find(e.first)->second, "");
    }

    // bucket_count, bucket_size(n), bucket
    log("--------------");
    log("bucket_count = %d", static_cast<int>(map4.bucketCount()));
    log("size = %d", static_cast<int>(map4.size()));
    for (int i = 0; i < map4.bucketCount(); ++i)
    {
        log("bucket_size(%d) = %d", i, static_cast<int>(map4.bucketSize(i)));
    }
    for (const auto& e : map4)
    {
        log("bucket(\"%s\"), bucket index = %d", e.first.c_str(), static_cast<int>(map4.bucket(e.first)));
    }

    log("----- all keys---------");

    // keys and at
    auto keys = map4.keys();
    for (const auto& key : keys)
    {
        log("key = %s", key.c_str());
    }

    auto node10Key = map4.at("10");
    map4.insert("100", node10Key);
    map4.insert("101", node10Key);
    map4.insert("102", node10Key);

    log("------ keys for object --------");
    auto keysForObject = map4.keys(node10Key);
    for (const auto& key : keysForObject)
    {
        log("key = %s", key.c_str());
    }
    log("--------------");

    // at in const function
    constFunc(map4);

    // find
    auto nodeToFind = map4.find("10");
    CC_UNUSED_PARAM(nodeToFind);
    CCASSERT(nodeToFind->second->getTag() == 1010, "");

    // insert
    Map<std::string, Node*> map6;
    auto node1 = Node::create();
    node1->setTag(101);
    auto node2 = Node::create();
    node2->setTag(102);
    auto node3 = Node::create();
    node3->setTag(103);
    map6.insert("insert01", node1);
    map6.insert("insert02", node2);
    map6.insert("insert03", node3);

    CCASSERT(node1->getReferenceCount() == 2, "");
    CCASSERT(node2->getReferenceCount() == 2, "");
    CCASSERT(node3->getReferenceCount() == 2, "");
    CCASSERT(map6.at("insert01") == node1, "");
    CCASSERT(map6.at("insert02") == node2, "");
    CCASSERT(map6.at("insert03") == node3, "");

    // erase
    Map<std::string, Node*> mapForErase = createMap();
    mapForErase.erase(mapForErase.find("9"));
    CCASSERT(mapForErase.find("9") == mapForErase.end(), "");
    CCASSERT(mapForErase.size() == 19, "");

    mapForErase.erase("7");
    CCASSERT(mapForErase.find("7") == mapForErase.end(), "");
    CCASSERT(mapForErase.size() == 18, "");

    std::vector<std::string> itemsToRemove;
    itemsToRemove.push_back("2");
    itemsToRemove.push_back("3");
    itemsToRemove.push_back("4");
    mapForErase.erase(itemsToRemove);
    CCASSERT(mapForErase.size() == 15, "");

    // clear
    Map<std::string, Node*> mapForClear = createMap();
    auto mapForClearCopy = mapForClear;
    mapForClear.clear();

    for (const auto& e : mapForClearCopy)
    {
        CC_UNUSED_PARAM(e);
        CCASSERT(e.second->getReferenceCount() == 2, "");
    }

    // get random object
    // Set the seed by time
    srand((unsigned)time(nullptr));
    Map<std::string, Node*> mapForRandom = createMap();
    log("<--- begin ---->");
    for (int i = 0; i < mapForRandom.size(); ++i)
    {
        log("Map: random object tag = %d", mapForRandom.getRandomObject()->getTag());
    }
    log("<---- end  ---->");

    // Self assignment
    Map<std::string, Node*> mapForSelfAssign = createMap();
    mapForSelfAssign = mapForSelfAssign;
    CCASSERT(mapForSelfAssign.size() == 20, "");

    for (const auto& e : mapForSelfAssign)
    {
        CC_UNUSED_PARAM(e);
        CCASSERT(e.second->getReferenceCount() == 2, "");
    }

    mapForSelfAssign = std::move(mapForSelfAssign);
    CCASSERT(mapForSelfAssign.size() == 20, "");

    for (const auto& e : mapForSelfAssign)
    {
        CC_UNUSED_PARAM(e);
        CCASSERT(e.second->getReferenceCount() == 2, "");
    }
}

void TemplateMapTest::constFunc(const Map<std::string, Node*>& map) const
{
    log("[%s]=(tag)%d", "0", map.at("0")->getTag());
    log("[%s]=(tag)%d", "1", map.find("1")->second->getTag());
}

std::string TemplateMapTest::subtitle() const
{
    return "Map<K, V>, should not crash";
}

//----------------------------------

void ValueTest::onEnter()
{
    UnitTestDemo::onEnter();
    
    Value v1;
    CCASSERT(v1.getType() == Value::Type::NONE, "");
    CCASSERT(v1.isNull(), "");
    
    Value v2(100);
    CCASSERT(v2.getType() == Value::Type::INTEGER, "");
    CCASSERT(!v2.isNull(), "");
    
    Value v3(101.4f);
    CCASSERT(v3.getType() == Value::Type::FLOAT, "");
    CCASSERT(!v3.isNull(), "");
    
    Value v4(106.1);
    CCASSERT(v4.getType() == Value::Type::DOUBLE, "");
    CCASSERT(!v4.isNull(), "");
    
    unsigned char byte = 50;
    Value v5(byte);
    CCASSERT(v5.getType() == Value::Type::BYTE, "");
    CCASSERT(!v5.isNull(), "");
    
    Value v6(true);
    CCASSERT(v6.getType() == Value::Type::BOOLEAN, "");
    CCASSERT(!v6.isNull(), "");
    
    Value v7("string");
    CCASSERT(v7.getType() == Value::Type::STRING, "");
    CCASSERT(!v7.isNull(), "");
    
    Value v8(std::string("string2"));
    CCASSERT(v8.getType() == Value::Type::STRING, "");
    CCASSERT(!v8.isNull(), "");

    auto createValueVector = [&](){
        ValueVector ret;
        ret.push_back(v1);
        ret.push_back(v2);
        ret.push_back(v3);
        return ret;
    };
    
    
    Value v9(createValueVector());
    CCASSERT(v9.getType() == Value::Type::VECTOR, "");
    CCASSERT(!v9.isNull(), "");

    auto createValueMap = [&](){
        ValueMap ret;
        ret["aaa"] = v1;
        ret["bbb"] = v2;
        ret["ccc"] = v3;
        return ret;
    };
    
    Value v10(createValueMap());
    CCASSERT(v10.getType() == Value::Type::MAP, "");
    CCASSERT(!v10.isNull(), "");
    
    auto createValueMapIntKey = [&](){
        ValueMapIntKey ret;
        ret[111] = v1;
        ret[222] = v2;
        ret[333] = v3;
        return ret;
    };
    
    Value v11(createValueMapIntKey());
    CCASSERT(v11.getType() == Value::Type::INT_KEY_MAP, "");
    CCASSERT(!v11.isNull(), "");
}

std::string ValueTest::subtitle() const
{
    return "Value Test, should not crash";
}

void ValueTest::constFunc(const Value& value) const
{
    
}

// UTFConversionTest

// FIXME: made as define to prevent compile warnings in release mode. Better is to be a `const static int`
#define TEST_CODE_NUM 11

static const char16_t __utf16Code[] =
{
    0x3042,
    0x3044,
    0x3046,
    0x3048,
    0x304A,
    0x3042,
    0x3044,
    0x3046,
    0x3048,
    0x304A,
    0x0041,
    0x0000,
};

// to avoid Xcode error, char => unsigned char
// If you use this table, please cast manually as (const char *).
static const unsigned char __utf8Code[] =
{
    0xE3,0x81,0x82,
    0xE3,0x81,0x84,
    0xE3,0x81,0x86,
    0xE3,0x81,0x88,
    0xE3,0x81,0x8A,
    0xE3,0x81,0x82,
    0xE3,0x81,0x84,
    0xE3,0x81,0x86,
    0xE3,0x81,0x88,
    0xE3,0x81,0x8A,
    0x41,
    0x00,
};


static const char16_t WHITE_SPACE_CODE[] =
{
    0x0009,
    0x000A,
    0x000B,
    0x000C,
    0x000D,
    0x0020,
    0x0085,
    0x00A0,
    0x1680,
    0x2000,
    0x2001,
    0x2002,
    0x2003,
    0x2004,
    0x2005,
    0x2006,
    0x2007,
    0x2008,
    0x2009,
    0x200A,
    0x2028,
    0x2029,
    0x202F,
    0x205F,
    0x3000
};

static void doUTFConversion()
{
    bool isSuccess = false;
    
    std::string originalUTF8 = (const char*)__utf8Code;
    std::u16string originalUTF16 = __utf16Code;
    
    //---------------------------
    std::string utf8Str;
    isSuccess = StringUtils::UTF16ToUTF8(originalUTF16, utf8Str);
    
    if (isSuccess)
    {
        isSuccess = memcmp(utf8Str.data(), originalUTF8.data(), originalUTF8.length()+1)==0;
    }
    
    CCASSERT(isSuccess, "StringUtils::UTF16ToUTF8 failed");
    
    //---------------------------
    std::u16string utf16Str;
    isSuccess = StringUtils::UTF8ToUTF16(originalUTF8, utf16Str);
    
    if (isSuccess)
    {
        isSuccess = memcmp(utf16Str.data(), originalUTF16.data(), originalUTF16.length()+1)==0;
    }
    
    CCASSERT(isSuccess && (utf16Str.length() == TEST_CODE_NUM), "StringUtils::UTF8ToUTF16 failed");
    
    //---------------------------
    auto vec1 = StringUtils::getChar16VectorFromUTF16String(originalUTF16);
    
    CCASSERT(vec1.size() == originalUTF16.length(), "StringUtils::getChar16VectorFromUTF16String failed");
    
    //---------------------------
    std::vector<char16_t> vec2( vec1 );
    vec2.push_back(0x2009);
    vec2.push_back(0x2009);
    vec2.push_back(0x2009);
    vec2.push_back(0x2009);
    
    std::vector<char16_t> vec3( vec2 );
    StringUtils::trimUTF16Vector(vec2);
    
    CCASSERT(vec1.size() == vec2.size(), "StringUtils::trimUTF16Vector failed");
    
    for (size_t i = 0; i < vec2.size(); i++ )
    {
        CCASSERT(vec1.at(i) == vec2.at(i), "StringUtils::trimUTF16Vector failed");
    }
    
    //---------------------------
    CCASSERT(StringUtils::getCharacterCountInUTF8String(originalUTF8) == TEST_CODE_NUM, "StringUtils::getCharacterCountInUTF8String failed");
    
    //---------------------------
    CCASSERT(StringUtils::getIndexOfLastNotChar16(vec3, 0x2009) == (vec1.size()-1), "StringUtils::getIndexOfLastNotChar16 failed");
    
    //---------------------------
    CCASSERT(originalUTF16.length() == TEST_CODE_NUM, "The length of the original utf16 string isn't equal to TEST_CODE_NUM");
    
    //---------------------------
    size_t whiteCodeNum = sizeof(WHITE_SPACE_CODE) / sizeof(WHITE_SPACE_CODE[0]);
    for( size_t i = 0; i < whiteCodeNum; i++ )
    {
        CCASSERT(StringUtils::isUnicodeSpace(WHITE_SPACE_CODE[i]), "StringUtils::isUnicodeSpace failed");
    }
    
    CCASSERT(!StringUtils::isUnicodeSpace(0xFFFF), "StringUtils::isUnicodeSpace failed");
    
    CCASSERT(!StringUtils::isCJKUnicode(0xFFFF) && StringUtils::isCJKUnicode(0x3100), "StringUtils::isCJKUnicode failed");
}

void UTFConversionTest::onEnter()
{
    UnitTestDemo::onEnter();

    for (int i = 0; i < 10000; ++i)
    {
        doUTFConversion();
    }
}

std::string UTFConversionTest::subtitle() const
{
    return "UTF8 <-> UTF16 Conversion Test, no crash";
}

// MathUtilTest

namespace UnitTest {

#ifdef INCLUDE_NEON32
#include "math/MathUtilNeon.inl"
#endif

#ifdef INCLUDE_NEON64
#include "math/MathUtilNeon64.inl"
#endif

#ifdef INCLUDE_SSE
//FIXME: #include "math/MathUtilSSE.inl"
#endif

#include "math/MathUtil.inl"

} // namespace UnitTest {

// I know the next line looks ugly, but it's a way to test MathUtil. :)
using namespace UnitTest::cocos2d;

static void __checkMathUtilResult(const char* description, const float* a1, const float* a2, int size)
{
    log("-------------checking %s ----------------------------", description);
    // Check whether the result of the optimized instruction is the same as which is implemented in C
    for (int i = 0; i < size; ++i)
    {
        bool r = fabs(a1[i] - a2[i]) < 0.00001f;//FLT_EPSILON;
        if (r)
        {
            log("Correct: a1[%d]=%f, a2[%d]=%f", i, a1[i], i, a2[i]);
        }
        else
        {
            log("Wrong: a1[%d]=%f, a2[%d]=%f", i, a1[i], i, a2[i]);
        }
        CCASSERT(r, "The optimized instruction is implemented in a wrong way, please check it!");
    }
}

void MathUtilTest::onEnter()
{
    UnitTestDemo::onEnter();
    
    const int MAT4_SIZE = 16;
    const int VEC4_SIZE = 4;
    
    const float inMat41[MAT4_SIZE] = {
        0.234023f, 2.472349f, 1.984244f, 2.23348f,
        0.634124f, 0.234975f, 6.384572f, 0.82368f,
        0.738028f, 1.845237f, 1.934721f, 1.62343f,
        0.339023f, 3.472452f, 1.324714f, 4.23852f,
    };
    
    const float inMat42[MAT4_SIZE] = {
        1.640232f, 4.472349f, 0.983244f, 1.23343f,
        2.834124f, 8.234975f, 0.082572f, 3.82464f,
        3.238028f, 2.845237f, 0.331721f, 4.62544f,
        4.539023f, 9.472452f, 3.520714f, 2.23252f,
    };
    
    const float scalar = 1.323298f;
    const float x = 0.432234f;
    const float y = 1.333229f;
    const float z = 2.535292f;
    const float w = 4.632234f;
    
    const float inVec4[VEC4_SIZE] = {2.323478f, 0.238482f, 4.223783f, 7.238238f};
    const float inVec42[VEC4_SIZE] = {0.322374f, 8.258883f, 3.293683f, 2.838337f};
    
    float outMat4Opt[MAT4_SIZE] = {0};
    float outMat4C[MAT4_SIZE] = {0};
    float outVec4Opt[VEC4_SIZE] = {0};
    float outVec4C[VEC4_SIZE] = {0};
    
    // inline static void addMatrix(const float* m, float scalar, float* dst);
    MathUtilC::addMatrix(inMat41, scalar, outMat4C);
    
#ifdef INCLUDE_NEON32
    MathUtilNeon::addMatrix(inMat41, scalar, outMat4Opt);
#endif
    
#ifdef INCLUDE_NEON64
    MathUtilNeon64::addMatrix(inMat41, scalar, outMat4Opt);
#endif
    
#ifdef INCLUDE_SSE
// FIXME:
#endif
    
    __checkMathUtilResult("inline static void addMatrix(const float* m, float scalar, float* dst);", outMat4C, outMat4Opt, MAT4_SIZE);
    // Clean
    memset(outMat4C, 0, sizeof(outMat4C));
    memset(outMat4Opt, 0, sizeof(outMat4Opt));
    
    // inline static void addMatrix(const float* m1, const float* m2, float* dst);
    MathUtilC::addMatrix(inMat41, inMat42, outMat4C);
    
#ifdef INCLUDE_NEON32
    MathUtilNeon::addMatrix(inMat41, inMat42, outMat4Opt);
#endif
    
#ifdef INCLUDE_NEON64
    MathUtilNeon64::addMatrix(inMat41, inMat42, outMat4Opt);
#endif
    
#ifdef INCLUDE_SSE
    // FIXME:
#endif
    
    __checkMathUtilResult("inline static void addMatrix(const float* m1, const float* m2, float* dst);", outMat4C, outMat4Opt, MAT4_SIZE);
    // Clean
    memset(outMat4C, 0, sizeof(outMat4C));
    memset(outMat4Opt, 0, sizeof(outMat4Opt));

    // inline static void subtractMatrix(const float* m1, const float* m2, float* dst);
    MathUtilC::subtractMatrix(inMat41, inMat42, outMat4C);
    
#ifdef INCLUDE_NEON32
    MathUtilNeon::subtractMatrix(inMat41, inMat42, outMat4Opt);
#endif
    
#ifdef INCLUDE_NEON64
    MathUtilNeon64::subtractMatrix(inMat41, inMat42, outMat4Opt);
#endif
    
#ifdef INCLUDE_SSE
    // FIXME:
#endif
    
    __checkMathUtilResult("inline static void subtractMatrix(const float* m1, const float* m2, float* dst);", outMat4C, outMat4Opt, MAT4_SIZE);
    // Clean
    memset(outMat4C, 0, sizeof(outMat4C));
    memset(outMat4Opt, 0, sizeof(outMat4Opt));
    
    // inline static void multiplyMatrix(const float* m, float scalar, float* dst);
    MathUtilC::multiplyMatrix(inMat41, scalar, outMat4C);
    
#ifdef INCLUDE_NEON32
    MathUtilNeon::multiplyMatrix(inMat41, scalar, outMat4Opt);
#endif
    
#ifdef INCLUDE_NEON64
    MathUtilNeon64::multiplyMatrix(inMat41, scalar, outMat4Opt);
#endif
    
#ifdef INCLUDE_SSE
    // FIXME:
#endif
    
    __checkMathUtilResult("inline static void multiplyMatrix(const float* m, float scalar, float* dst);", outMat4C, outMat4Opt, MAT4_SIZE);
    // Clean
    memset(outMat4C, 0, sizeof(outMat4C));
    memset(outMat4Opt, 0, sizeof(outMat4Opt));
    
    // inline static void multiplyMatrix(const float* m1, const float* m2, float* dst);
    MathUtilC::multiplyMatrix(inMat41, inMat42, outMat4C);
    
#ifdef INCLUDE_NEON32
    MathUtilNeon::multiplyMatrix(inMat41, inMat42, outMat4Opt);
#endif
    
#ifdef INCLUDE_NEON64
    MathUtilNeon64::multiplyMatrix(inMat41, inMat42, outMat4Opt);
#endif
    
#ifdef INCLUDE_SSE
    // FIXME:
#endif
    
    __checkMathUtilResult("inline static void multiplyMatrix(const float* m1, const float* m2, float* dst);", outMat4C, outMat4Opt, MAT4_SIZE);
    // Clean
    memset(outMat4C, 0, sizeof(outMat4C));
    memset(outMat4Opt, 0, sizeof(outMat4Opt));
    
    // inline static void negateMatrix(const float* m, float* dst);
    MathUtilC::negateMatrix(inMat41, outMat4C);
    
#ifdef INCLUDE_NEON32
    MathUtilNeon::negateMatrix(inMat41, outMat4Opt);
#endif
    
#ifdef INCLUDE_NEON64
    MathUtilNeon64::negateMatrix(inMat41, outMat4Opt);
#endif
    
#ifdef INCLUDE_SSE
    // FIXME:
#endif
    
    __checkMathUtilResult("inline static void negateMatrix(const float* m, float* dst);", outMat4C, outMat4Opt, MAT4_SIZE);
    // Clean
    memset(outMat4C, 0, sizeof(outMat4C));
    memset(outMat4Opt, 0, sizeof(outMat4Opt));
    
    // inline static void transposeMatrix(const float* m, float* dst);
    MathUtilC::transposeMatrix(inMat41, outMat4C);
    
#ifdef INCLUDE_NEON32
    MathUtilNeon::transposeMatrix(inMat41, outMat4Opt);
#endif
    
#ifdef INCLUDE_NEON64
    MathUtilNeon64::transposeMatrix(inMat41, outMat4Opt);
#endif
    
#ifdef INCLUDE_SSE
    // FIXME:
#endif
    
    __checkMathUtilResult("inline static void transposeMatrix(const float* m, float* dst);", outMat4C, outMat4Opt, MAT4_SIZE);
    // Clean
    memset(outMat4C, 0, sizeof(outMat4C));
    memset(outMat4Opt, 0, sizeof(outMat4Opt));
    
    // inline static void transformVec4(const float* m, float x, float y, float z, float w, float* dst);
    MathUtilC::transformVec4(inMat41, x, y, z, w, outVec4C);
    
#ifdef INCLUDE_NEON32
    MathUtilNeon::transformVec4(inMat41, x, y, z, w, outVec4Opt);
#endif
    
#ifdef INCLUDE_NEON64
    MathUtilNeon64::transformVec4(inMat41, x, y, z, w, outVec4Opt);
#endif
    
#ifdef INCLUDE_SSE
    // FIXME:
#endif
    
    __checkMathUtilResult("inline static void transformVec4(const float* m, float x, float y, float z, float w, float* dst);", outVec4C, outVec4Opt, VEC4_SIZE);
    // Clean
    memset(outVec4C, 0, sizeof(outVec4C));
    memset(outVec4Opt, 0, sizeof(outVec4Opt));
    
    // inline static void transformVec4(const float* m, const float* v, float* dst);
    MathUtilC::transformVec4(inMat41, inVec4, outVec4C);
    
#ifdef INCLUDE_NEON32
    MathUtilNeon::transformVec4(inMat41, inVec4, outVec4Opt);
#endif
    
#ifdef INCLUDE_NEON64
    MathUtilNeon64::transformVec4(inMat41, inVec4, outVec4Opt);
#endif
    
#ifdef INCLUDE_SSE
    // FIXME:
#endif
    
    __checkMathUtilResult("inline static void transformVec4(const float* m, const float* v, float* dst);", outVec4C, outVec4Opt, VEC4_SIZE);
    // Clean
    memset(outVec4C, 0, sizeof(outVec4C));
    memset(outVec4Opt, 0, sizeof(outVec4Opt));
    
    // inline static void crossVec3(const float* v1, const float* v2, float* dst);
    MathUtilC::crossVec3(inVec4, inVec42, outVec4C);
    
#ifdef INCLUDE_NEON32
    MathUtilNeon::crossVec3(inVec4, inVec42, outVec4Opt);
#endif
    
#ifdef INCLUDE_NEON64
    MathUtilNeon64::crossVec3(inVec4, inVec42, outVec4Opt);
#endif
    
#ifdef INCLUDE_SSE
    // FIXME:
#endif
    
    __checkMathUtilResult("inline static void crossVec3(const float* v1, const float* v2, float* dst);", outVec4C, outVec4Opt, VEC4_SIZE);
    // Clean
    memset(outVec4C, 0, sizeof(outVec4C));
    memset(outVec4Opt, 0, sizeof(outVec4Opt));
}

std::string MathUtilTest::subtitle() const
{
    return "MathUtilTest";
}

