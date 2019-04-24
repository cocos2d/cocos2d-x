/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "UnitTest.h"
#include "RefPtrTest.h"
#include "ui/UIHelper.h"
#include "network/Uri.h"
#include "base/ccUtils.h"

USING_NS_CC;
using namespace cocos2d::network;

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

#define EXPECT_EQ(a, b) assert((a) == (b))
#define EXPECT_NE(a, b) assert((a) != (b))
#define EXPECT_TRUE(a) assert(a)
#define EXPECT_FALSE(a) assert(!(a))

// For ' < o > ' multiply test scene.

UnitTests::UnitTests()
{
    ADD_TEST_CASE(TemplateVectorTest);
    ADD_TEST_CASE(TemplateMapTest);
    ADD_TEST_CASE(ValueTest);
    ADD_TEST_CASE(RefPtrTest);
    ADD_TEST_CASE(UTFConversionTest);
    ADD_TEST_CASE(UIHelperSubStringTest);
    ADD_TEST_CASE(ParseIntegerListTest);
    ADD_TEST_CASE(ParseUriTest);
    ADD_TEST_CASE(ResizableBufferAdapterTest);
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
    CCASSERT(vec.empty(), "vec should be empty.");
    CCASSERT(vec.capacity() == 0, "vec.capacity should be 0.");
    CCASSERT(vec.size() == 0, "vec.size should be 0.");
    CCASSERT(vec.max_size() > 0, "vec.max_size should > 0.");

    auto node1 = Node::create();
    node1->setTag(1);
    vec.pushBack(node1);
    CCASSERT(node1->getReferenceCount() == 2, "node1->getReferenceCount should be 2.");

    auto node2 = Node::create();
    node2->setTag(2);
    vec.pushBack(node2);
    CCASSERT(vec.getIndex(node1) == 0, "node1 should at index 0 in vec.");
    CCASSERT(vec.getIndex(node2) == 1, "node2 should at index 1 in vec.");

    auto node3 = Node::create();
    node3->setTag(3);
    vec.insert(1, node3);
    CCASSERT(vec.at(0)->getTag() == 1, "The element at 0, tag should be 1.");
    CCASSERT(vec.at(1)->getTag() == 3, "The element at 1, tag should be 3.");
    CCASSERT(vec.at(2)->getTag() == 2, "The element at 2, tag should be 2.");

    // Test copy constructor
    Vector<Node*> vec2(vec);
    CCASSERT(vec2.size() == vec.size(), "vec2 and vec should have equal size.");
    ssize_t size = vec.size();
    for (ssize_t i = 0; i < size; ++i)
    {
        CCASSERT(vec2.at(i) == vec.at(i), "The element at the same index in vec2 and vec2 should be equal.");
        CCASSERT(vec.at(i)->getReferenceCount() == 3, "The reference count of element in vec is 3. ");
        CCASSERT(vec2.at(i)->getReferenceCount() == 3, "The reference count of element in vec2 is 3. ");
    }

    // Test copy assignment operator
    Vector<Node*> vec3;
    vec3 = vec2;
    CCASSERT(vec3.size() == vec2.size(), "vec3 and vec2 should have equal size.");
    size = vec3.size();
    for (ssize_t i = 0; i < size; ++i)
    {
        CCASSERT(vec3.at(i) == vec2.at(i), "The element at the same index in vec3 and vec2 should be equal.");
        CCASSERT(vec3.at(i)->getReferenceCount() == 4, "The reference count of element in vec3 is 4. ");
        CCASSERT(vec2.at(i)->getReferenceCount() == 4, "The reference count of element in vec2 is 4. ");
        CCASSERT(vec.at(i)->getReferenceCount() == 4, "The reference count of element in vec is 4. ");
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
        CCASSERT(child->getReferenceCount() == 2, "child's reference count should be 2.");
    }

    // Test init Vector<T> with capacity
    Vector<Node*> vec5(10);
    CCASSERT(vec5.capacity() == 10, "vec5's capacity should be 10.");
    vec5.reserve(20);
    CCASSERT(vec5.capacity() == 20, "vec5's capacity should be 20.");

    CCASSERT(vec5.size() == 0, "vec5's size should be 0.");
    CCASSERT(vec5.empty(), "vec5 is empty now.");

    auto toRemovedNode = Node::create();
    vec5.pushBack(toRemovedNode);
    CCASSERT(toRemovedNode->getReferenceCount() == 2, "toRemovedNode's reference count is 2.");

    // Test move assignment operator
    vec5 = createVector();
    CCASSERT(toRemovedNode->getReferenceCount() == 1, "toRemovedNode's reference count is 1.");
    CCASSERT(vec5.size() == 20, "size should be 20");

    for (const auto& child : vec5)
    {
        CCASSERT(child->getReferenceCount() == 2, "child's reference count is 2.");
    }

    // Test Vector<T>::find
    CCASSERT(vec.find(node3) == (vec.begin() + 1), "node3 is the 2nd element in vec.");
    CCASSERT(std::find(std::begin(vec), std::end(vec), node2) == (vec.begin() + 2), "node2 is the 3rd element in vec.");

    CCASSERT(vec.front()->getTag() == 1, "vec's front element's tag is 1.");
    CCASSERT(vec.back()->getTag() == 2, "vec's back element's tag is 2.");

    CCASSERT(vec.getRandomObject(), "vec getRandomObject should return true.");
    CCASSERT(!vec.contains(Node::create()), "vec doesn't contain a empty Node instance.");
    CCASSERT(vec.contains(node1), "vec contains node1.");
    CCASSERT(vec.contains(node2), "vec contains node2.");
    CCASSERT(vec.contains(node3), "vec contains node3.");
    CCASSERT(vec.equals(vec2), "vec is equal to vec2.");
    CCASSERT(vec.equals(vec3), "vec is equal to vec3.");

    // Insert
    vec5.insert(2, node1);
    CCASSERT(vec5.at(2)->getTag() == 1, "vec5's 3rd element's tag is 1.");
    CCASSERT(vec5.size() == 21, "vec5's size is 21.");
    vec5.back()->setTag(100);
    vec5.popBack();
    CCASSERT(vec5.size() == 20, "vec5's size is 20.");
    CCASSERT(vec5.back()->getTag() != 100, "the back element of vec5's tag is 100.");

    // Erase and clear
    Vector<Node*> vec6 = createVector();
    Vector<Node*> vec7 = vec6;  // Copy for check

    CCASSERT(vec6.size() == 20, "vec6's size is 20.");
    vec6.erase(vec6.begin() + 1);  //
    CCASSERT(vec6.size() == 19, "vec6's size is 19.");
    CCASSERT((*(vec6.begin() + 1))->getTag() == 1002, "The 2rd element in vec6's tag is 1002.");
    vec6.erase(vec6.begin() + 2, vec6.begin() + 10);
    CCASSERT(vec6.size() == 11, "vec6's size is 11.");
    CCASSERT(vec6.at(0)->getTag() == 1000, "vec6's first element's tag is 1000.");
    CCASSERT(vec6.at(1)->getTag() == 1002, "vec6's second element's tag is 1002.");
    CCASSERT(vec6.at(2)->getTag() == 1011, "vec6's third element's tag is 1011.");
    CCASSERT(vec6.at(3)->getTag() == 1012, "vec6's fouth element's tag is 1012.");
    vec6.erase(3);
    CCASSERT(vec6.at(3)->getTag() == 1013, "vec6's 4th element's tag is 1013.");
    vec6.eraseObject(vec6.at(2));
    CCASSERT(vec6.at(2)->getTag() == 1013, "vec6's 3rd element's tag is 1013.");
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
        CCASSERT(objA->getReferenceCount() == 4, "objA's reference count is 4.");
    }
    CCASSERT(objA->getReferenceCount() == 1, "objA's reference count is 1.");
    
    {
        Vector<Node*> array1;
        // push back objA 3 times
        array1.pushBack(objA); // retain count is 2
        array1.pushBack(objA); // retain count is 3
        array1.pushBack(objA); // retain count is 4
        CCASSERT(objA->getReferenceCount() == 4, "objA's reference count is 4.");
        array1.eraseObject(objA, true); // Remove all occurrences in the Vector.
        CCASSERT(objA->getReferenceCount() == 1, "objA's reference count is 1.");
        
        array1.pushBack(objA); // retain count is 2
        array1.pushBack(objA); // retain count is 3
        array1.pushBack(objA); // retain count is 4
        
        array1.eraseObject(objA, false);
        CCASSERT(objA->getReferenceCount() == 3, "objA's reference count is 3."); // Only remove the first occurrence in the Vector.
    }

    // Check the retain count in vec7
    CCASSERT(vec7.size() == 20, "vec7's size is 20.");
    for (const auto& child : vec7)
    {
        CCASSERT(child->getReferenceCount() == 2, "child's reference count is 2.");
    }

    // Sort
    Vector<Node*> vecForSort = createVector();
    std::sort(vecForSort.begin(), vecForSort.end(), [](Node* a, Node* b){
        return a->getTag() >= b->getTag();
    });

    for (int i = 0; i < 20; ++i)
    {
        CCASSERT(vecForSort.at(i)->getTag() - 1000 == (19 - i), "vecForSort's element's tag is invalid.");
    }

    // Reverse
    vecForSort.reverse();
    for (int i = 0; i < 20; ++i)
    {
        CCASSERT(vecForSort.at(i)->getTag() - 1000 == i, "vecForSort's element's tag is invalid.");
    }

    // Swap
    Vector<Node*> vecForSwap = createVector();
    vecForSwap.swap(2, 4);
    CCASSERT(vecForSwap.at(2)->getTag() == 1004, "vecForSwap's 3nd element's tag is 1004.");
    CCASSERT(vecForSwap.at(4)->getTag() == 1002, "vecForSwap's 5rd element's tag is 1002.");
    vecForSwap.swap(vecForSwap.at(2), vecForSwap.at(4));
    CCASSERT(vecForSwap.at(2)->getTag() == 1002, "vecForSwap's 3rd element's tag is 1002.");
    CCASSERT(vecForSwap.at(4)->getTag() == 1004, "vecForSwap's 5rd element's tag is 1004.");

    // shrinkToFit
    Vector<Node*> vecForShrink = createVector();
    vecForShrink.reserve(100);
    CCASSERT(vecForShrink.capacity() == 100, "vecForShrink's capacity is 100.");
    vecForShrink.pushBack(Node::create());
    vecForShrink.shrinkToFit();
    CCASSERT(vecForShrink.capacity() == 21, "vecForShrink's capacity is 21.");

    // get random object
    // Set the seed by time
    std::srand((unsigned)time(nullptr));
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
    CCASSERT(vecSelfAssign.size() == 20, "vecSelfAssign's size is 20.");

    for (const auto& child : vecSelfAssign)
    {
        CCASSERT(child->getReferenceCount() == 2, "child's reference count is 2.");
    }

    vecSelfAssign = std::move(vecSelfAssign);
    CCASSERT(vecSelfAssign.size() == 20, "vecSelfAssign's size is 20.");

    for (const auto& child : vecSelfAssign)
    {
        CCASSERT(child->getReferenceCount() == 2, "child's reference count is 2.");
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
    CCASSERT(map1.empty(), "map1 is empty.");
    CCASSERT(map1.size() == 0, "map1's size is 0.");
    CCASSERT(map1.keys().empty(), "map1's keys are empty.");
    CCASSERT(map1.keys(Node::create()).empty(), "map1's keys don't contain a empty Node.");

    // Move constructor
    Map<std::string, Node*> map2 = createMap();
    for (const auto& e : map2)
    {
        CCASSERT(e.second->getReferenceCount() == 2, "e.second element's reference count is 2.");
    }

    // Copy constructor
    Map<std::string, Node*> map3(map2);
    for (const auto& e : map3)
    {
        CCASSERT(e.second->getReferenceCount() == 3, "e.second's reference count is 3.");
    }

    // Move assignment operator
    Map<std::string, Node*> map4;
    auto unusedNode = Node::create();
    map4.insert("unused",unusedNode);
    map4 = createMap();
    CCASSERT(unusedNode->getReferenceCount() == 1, "unusedNode's reference count is 1.");
    for (const auto& e : map4)
    {
        CCASSERT(e.second->getReferenceCount() == 2, "e.second's reference count is 2.");
    }

    // Copy assignment operator
    Map<std::string, Node*> map5;
    map5 = map4;
    for (const auto& e : map5)
    {
        CCASSERT(e.second->getReferenceCount() == 3, "e.second's reference count is 3.");
    }

    // Check size
    CCASSERT(map4.size() == map5.size(), "map4's size is equal to map5.size.");

    for (const auto& e : map4)
    {
        CCASSERT(e.second == map5.find(e.first)->second, "e.second can't be found in map5.");
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
    CCASSERT(nodeToFind->second->getTag() == 1010, "nodeToFind's tag value is 1010.");

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

    CCASSERT(node1->getReferenceCount() == 2, "node1's reference count is 2.");
    CCASSERT(node2->getReferenceCount() == 2, "node2's reference count is 2.");
    CCASSERT(node3->getReferenceCount() == 2, "node3's reference count is 2.");
    CCASSERT(map6.at("insert01") == node1, "The element at insert01 is equal to node1.");
    CCASSERT(map6.at("insert02") == node2, "The element at insert02 is equal to node2.");
    CCASSERT(map6.at("insert03") == node3, "The element at insert03 is equal to node3.");

    // erase
    Map<std::string, Node*> mapForErase = createMap();
    mapForErase.erase(mapForErase.find("9"));
    CCASSERT(mapForErase.find("9") == mapForErase.end(), "9 is already removed.");
    CCASSERT(mapForErase.size() == 19, "mapForErase's size is 19.");

    mapForErase.erase("7");
    CCASSERT(mapForErase.find("7") == mapForErase.end(), "7 is already removed.");
    CCASSERT(mapForErase.size() == 18, "mapForErase's size is 18.");

    std::vector<std::string> itemsToRemove;
    itemsToRemove.push_back("2");
    itemsToRemove.push_back("3");
    itemsToRemove.push_back("4");
    mapForErase.erase(itemsToRemove);
    CCASSERT(mapForErase.size() == 15, "mapForErase's size is 15.");

    // clear
    Map<std::string, Node*> mapForClear = createMap();
    auto mapForClearCopy = mapForClear;
    mapForClear.clear();

    for (const auto& e : mapForClearCopy)
    {
        CCASSERT(e.second->getReferenceCount() == 2, "e.second's reference count is 2.");
    }

    // get random object
    // Set the seed by time
    std::srand((unsigned)time(nullptr));
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
    CCASSERT(mapForSelfAssign.size() == 20, "mapForSelfAssign's size is 20.");

    for (const auto& e : mapForSelfAssign)
    {
        CCASSERT(e.second->getReferenceCount() == 2, "e.second's reference count is 2.");
    }

    mapForSelfAssign = std::move(mapForSelfAssign);
    CCASSERT(mapForSelfAssign.size() == 20, "mapForSelfAssign's size is 20.");

    for (const auto& e : mapForSelfAssign)
    {
        CCASSERT(e.second->getReferenceCount() == 2, "e.second's reference's count is 2.");
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
    CCASSERT(v1.getType() == Value::Type::NONE, "v1's value type should be VALUE::Type::NONE.");
    CCASSERT(v1.isNull(), "v1 is null.");
    
    Value v2(100);
    CCASSERT(v2.getType() == Value::Type::INTEGER, "v2's value type should be VALUE::Type::INTEGER.");
    CCASSERT(!v2.isNull(), "v2 is not null.");
    
    Value v3(101.4f);
    CCASSERT(v3.getType() == Value::Type::FLOAT, "v3's value type should be VALUE::Type::FLOAT.");
    CCASSERT(!v3.isNull(), "v3 is not null.");
    
    Value v4(106.1);
    CCASSERT(v4.getType() == Value::Type::DOUBLE, "v4's value type should be VALUE::Type::DOUBLE.");
    CCASSERT(!v4.isNull(), "v4 is not null.");
    
    unsigned char byte = 50;
    Value v5(byte);
    CCASSERT(v5.getType() == Value::Type::BYTE, "v5's value type should be Value::Type::BTYE.");
    CCASSERT(!v5.isNull(), "v5 is not null.");
    
    Value v6(true);
    CCASSERT(v6.getType() == Value::Type::BOOLEAN, "v6's value type is Value::Type::BOOLEAN.");
    CCASSERT(!v6.isNull(), "v6 is not null.");
    
    Value v7("string");
    CCASSERT(v7.getType() == Value::Type::STRING, "v7's value type is Value::type::STRING.");
    CCASSERT(!v7.isNull(), "v7 is not null.");
    
    Value v8(std::string("string2"));
    CCASSERT(v8.getType() == Value::Type::STRING, "v8's value type is Value::Type::STRING.");
    CCASSERT(!v8.isNull(), "v8 is not null.");

    auto createValueVector = [&](){
        ValueVector ret;
        ret.push_back(v1);
        ret.push_back(v2);
        ret.push_back(v3);
        return ret;
    };
    
    
    Value v9(createValueVector());
    CCASSERT(v9.getType() == Value::Type::VECTOR, "v9's value type is Value::Type::VECTOR.");
    CCASSERT(!v9.isNull(), "v9 is not null.");

    auto createValueMap = [&](){
        ValueMap ret;
        ret["aaa"] = v1;
        ret["bbb"] = v2;
        ret["ccc"] = v3;
        return ret;
    };
    
    Value v10(createValueMap());
    CCASSERT(v10.getType() == Value::Type::MAP, "v10's value type is Value::Type::MAP.");
    CCASSERT(!v10.isNull(), "v10 is not null.");
    
    auto createValueMapIntKey = [&](){
        ValueMapIntKey ret;
        ret[111] = v1;
        ret[222] = v2;
        ret[333] = v3;
        return ret;
    };
    
    Value v11(createValueMapIntKey());
    CCASSERT(v11.getType() == Value::Type::INT_KEY_MAP, "v11's value type is Value::Type::INT_KEY_MAP.");
    CCASSERT(!v11.isNull(), "v11 is not null.");
}

std::string ValueTest::subtitle() const
{
    return "Value Test, should not crash";
}

void ValueTest::constFunc(const Value& /*value*/) const
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

// UIHelperSubStringTest

void UIHelperSubStringTest::onEnter()
{
    UnitTestDemo::onEnter();

    using cocos2d::ui::Helper;
    {
        // Trivial case
        std::string source = "abcdefghij";
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 2) == "ab");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 2, 2) == "cd");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 4, 2) == "ef");
    }
    {
        // Empty string
        std::string source = "";

        // OK
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 1) == "");

        // Error: These cases cause "out of range" error
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 1) == "");
    }
    {
        // Ascii
        std::string source = "abc";

        // OK
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 2, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 3, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 3) == "abc");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 4) == "abc");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 2) == "bc");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 3) == "bc");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 2, 1) == "c");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 2, 2) == "c");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 3, 1) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 3, 2) == "");

        // Error: These cases cause "out of range" error
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 4, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 4, 1) == "");
    }
    {
        // CJK characters
        std::string source = "这里是中文测试例";

        // OK
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 7, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 8, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 8, 1) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 1) == "\xe8\xbf\x99");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 4) == "\xe8\xbf\x99\xe9\x87\x8c\xe6\x98\xaf\xe4\xb8\xad");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 8) == "\xe8\xbf\x99\xe9\x87\x8c\xe6\x98\xaf\xe4\xb8\xad\xe6\x96\x87\xe6\xb5\x8b\xe8\xaf\x95\xe4\xbe\x8b");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 100) == "\xe8\xbf\x99\xe9\x87\x8c\xe6\x98\xaf\xe4\xb8\xad\xe6\x96\x87\xe6\xb5\x8b\xe8\xaf\x95\xe4\xbe\x8b");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 2, 5) == "\xe6\x98\xaf\xe4\xb8\xad\xe6\x96\x87\xe6\xb5\x8b\xe8\xaf\x95");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 6, 2) == "\xe8\xaf\x95\xe4\xbe\x8b");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 6, 100) == "\xe8\xaf\x95\xe4\xbe\x8b");

        // Error: These cases cause "out of range" error
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 9, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 9, 1) == "");
    }
    {
        // Redundant UTF-8 sequence for Directory traversal attack (1)
        std::string source = "\xC0\xAF";

        // Error: Can't convert string to correct encoding such as UTF-32
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 1) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 1) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 2) == "");
    }
    {
        // Redundant UTF-8 sequence for Directory traversal attack (2)
        std::string source = "\xE0\x80\xAF";

        // Error: Can't convert string to correct encoding such as UTF-32
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 1) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 1) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 3) == "");
    }
    {
        // Redundant UTF-8 sequence for Directory traversal attack (3)
        std::string source = "\xF0\x80\x80\xAF";

        // Error: Can't convert string to correct encoding such as UTF-32
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 1) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 0) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 1, 1) == "");
        CC_ASSERT(Helper::getSubStringOfUTF8String(source, 0, 4) == "");
    }
}

std::string UIHelperSubStringTest::subtitle() const
{
    return "ui::Helper::getSubStringOfUTF8String Test";
}

// ParseIntegerListTest
void ParseIntegerListTest::onEnter() {
    UnitTestDemo::onEnter();

    {
        using cocos2d::utils::parseIntegerList;

        std::vector<int> res1{};
        EXPECT_EQ(res1, parseIntegerList(""));

        std::vector<int> res2{1};
        EXPECT_EQ(res2, parseIntegerList("1"));

        std::vector<int> res3{1, 2};
        EXPECT_EQ(res3, parseIntegerList("1 2"));

        std::vector<int> res4{2, 4, 3, 1, 4, 2, 0, 4, 1, 0, 4, 5};
        EXPECT_EQ(res4, parseIntegerList("2 4 3 1 4 2 0 4 1 0 4 5"));

        std::vector<int> res5{73, 48, 57, 117, 27, 117, 29, 77, 14, 62, 26, 7, 55, 2};
        EXPECT_EQ(res5, parseIntegerList("73 48 57 117 27 117 29 77 14 62 26 7 55 2"));
    }
}

std::string ParseIntegerListTest::subtitle() const
{
    return "utils::parseIntegerList Test";
}

// ParseUriTest
void ParseUriTest::onEnter()
{
    UnitTestDemo::onEnter();

    {
        std::string s("http://www.facebook.com/hello/world?query#fragment");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("www.facebook.com", u.getHost());
        EXPECT_EQ(0, u.getPort());
        EXPECT_EQ("www.facebook.com", u.getAuthority());
        EXPECT_EQ("/hello/world", u.getPath());
        EXPECT_EQ("query", u.getQuery());
        EXPECT_EQ("fragment", u.getFragment());
        EXPECT_EQ(s, u.toString());  // canonical
    }

    {
        std::string s("http://www.facebook.com:8080/hello/world?query#fragment");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("www.facebook.com", u.getHost());
        EXPECT_EQ(8080, u.getPort());
        EXPECT_EQ("www.facebook.com:8080", u.getAuthority());
        EXPECT_EQ("/hello/world", u.getPath());
        EXPECT_EQ("query", u.getQuery());
        EXPECT_EQ("fragment", u.getFragment());
        EXPECT_EQ(s, u.toString());  // canonical
    }

    {
        std::string s("http://127.0.0.1:8080/hello/world?query#fragment");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("127.0.0.1", u.getHost());
        EXPECT_EQ(8080, u.getPort());
        EXPECT_EQ("127.0.0.1:8080", u.getAuthority());
        EXPECT_EQ("/hello/world", u.getPath());
        EXPECT_EQ("query", u.getQuery());
        EXPECT_EQ("fragment", u.getFragment());
        EXPECT_EQ(s, u.toString());  // canonical
    }

    {
        std::string s("http://[::1]:8080/hello/world?query#fragment");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("[::1]", u.getHost());
        EXPECT_EQ("::1", u.getHostName());
        EXPECT_EQ(8080, u.getPort());
        EXPECT_EQ("[::1]:8080", u.getAuthority());
        EXPECT_EQ("/hello/world", u.getPath());
        EXPECT_EQ("query", u.getQuery());
        EXPECT_EQ("fragment", u.getFragment());
        EXPECT_EQ(s, u.toString());  // canonical
    }

    {
        std::string s("http://[2401:db00:20:7004:face:0:29:0]:8080/hello/world?query");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("[2401:db00:20:7004:face:0:29:0]", u.getHost());
        EXPECT_EQ("2401:db00:20:7004:face:0:29:0", u.getHostName());
        EXPECT_EQ(8080, u.getPort());
        EXPECT_EQ("[2401:db00:20:7004:face:0:29:0]:8080", u.getAuthority());
        EXPECT_EQ("/hello/world", u.getPath());
        EXPECT_EQ("query", u.getQuery());
        EXPECT_EQ("", u.getFragment());
        EXPECT_EQ(s, u.toString());  // canonical
    }

    {
        std::string s("http://[2401:db00:20:7004:face:0:29:0]/hello/world?query");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("[2401:db00:20:7004:face:0:29:0]", u.getHost());
        EXPECT_EQ("2401:db00:20:7004:face:0:29:0", u.getHostName());
        EXPECT_EQ(0, u.getPort());
        EXPECT_EQ("[2401:db00:20:7004:face:0:29:0]", u.getAuthority());
        EXPECT_EQ("/hello/world", u.getPath());
        EXPECT_EQ("query", u.getQuery());
        EXPECT_EQ("", u.getFragment());
        EXPECT_EQ(s, u.toString());  // canonical
    }

    {
        std::string s("http://user:pass@host.com/");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("user", u.getUserName());
        EXPECT_EQ("pass", u.getPassword());
        EXPECT_EQ("host.com", u.getHost());
        EXPECT_EQ(0, u.getPort());
        EXPECT_EQ("user:pass@host.com", u.getAuthority());
        EXPECT_EQ("/", u.getPath());
        EXPECT_EQ("", u.getQuery());
        EXPECT_EQ("", u.getFragment());
        EXPECT_EQ(s, u.toString());
    }

    {
        std::string s("http://user@host.com/");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("user", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("host.com", u.getHost());
        EXPECT_EQ(0, u.getPort());
        EXPECT_EQ("user@host.com", u.getAuthority());
        EXPECT_EQ("/", u.getPath());
        EXPECT_EQ("", u.getQuery());
        EXPECT_EQ("", u.getFragment());
        EXPECT_EQ(s, u.toString());
    }

    {
        std::string s("http://user:@host.com/");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("user", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("host.com", u.getHost());
        EXPECT_EQ(0, u.getPort());
        EXPECT_EQ("user@host.com", u.getAuthority());
        EXPECT_EQ("/", u.getPath());
        EXPECT_EQ("", u.getQuery());
        EXPECT_EQ("", u.getFragment());
        EXPECT_EQ("http://user@host.com/", u.toString());
    }

    {
        std::string s("http://:pass@host.com/");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("", u.getUserName());
        EXPECT_EQ("pass", u.getPassword());
        EXPECT_EQ("host.com", u.getHost());
        EXPECT_EQ(0, u.getPort());
        EXPECT_EQ(":pass@host.com", u.getAuthority());
        EXPECT_EQ("/", u.getPath());
        EXPECT_EQ("", u.getQuery());
        EXPECT_EQ("", u.getFragment());
        EXPECT_EQ(s, u.toString());
    }

    {
        std::string s("http://@host.com/");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("host.com", u.getHost());
        EXPECT_EQ(0, u.getPort());
        EXPECT_EQ("host.com", u.getAuthority());
        EXPECT_EQ("/", u.getPath());
        EXPECT_EQ("", u.getQuery());
        EXPECT_EQ("", u.getFragment());
        EXPECT_EQ("http://host.com/", u.toString());
    }

    {
        std::string s("http://:@host.com/");
        Uri u = Uri::parse(s);
        EXPECT_EQ("http", u.getScheme());
        EXPECT_EQ("", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("host.com", u.getHost());
        EXPECT_EQ(0, u.getPort());
        EXPECT_EQ("host.com", u.getAuthority());
        EXPECT_EQ("/", u.getPath());
        EXPECT_EQ("", u.getQuery());
        EXPECT_EQ("", u.getFragment());
        EXPECT_EQ("http://host.com/", u.toString());
    }

    {
        std::string s("file:///etc/motd");
        Uri u = Uri::parse(s);
        EXPECT_EQ("file", u.getScheme());
        EXPECT_EQ("", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("", u.getHost());
        EXPECT_EQ(0, u.getPort());
        EXPECT_EQ("", u.getAuthority());
        EXPECT_EQ("/etc/motd", u.getPath());
        EXPECT_EQ("", u.getQuery());
        EXPECT_EQ("", u.getFragment());
        EXPECT_EQ(s, u.toString());
    }

    {
        std::string s("file://etc/motd");
        Uri u = Uri::parse(s);
        EXPECT_EQ("file", u.getScheme());
        EXPECT_EQ("", u.getUserName());
        EXPECT_EQ("", u.getPassword());
        EXPECT_EQ("etc", u.getHost());
        EXPECT_EQ(0, u.getPort());
        EXPECT_EQ("etc", u.getAuthority());
        EXPECT_EQ("/motd", u.getPath());
        EXPECT_EQ("", u.getQuery());
        EXPECT_EQ("", u.getFragment());
        EXPECT_EQ(s, u.toString());
    }

    {
        // test query parameters
        std::string s("http://localhost?&key1=foo&key2=&key3&=bar&=bar=&");
        Uri u = Uri::parse(s);
        auto paramsList = u.getQueryParams();
        std::map<std::string, std::string> params;
        for (auto& param : paramsList) {
            params[param.first] = param.second;
        }
        EXPECT_EQ(3, params.size());
        EXPECT_EQ("foo", params["key1"]);
        EXPECT_NE(params.end(), params.find("key2"));
        EXPECT_EQ("", params["key2"]);
        EXPECT_NE(params.end(), params.find("key3"));
        EXPECT_EQ("", params["key3"]);
    }

    {
        // test query parameters
        std::string s("http://localhost?&&&&&&&&&&&&&&&");
        Uri u = Uri::parse(s);
        auto params = u.getQueryParams();
        EXPECT_TRUE(params.empty());
    }

    {
        // test query parameters
        std::string s("http://localhost?&=invalid_key&key2&key3=foo");
        Uri u = Uri::parse(s);
        auto paramsList = u.getQueryParams();
        std::map<std::string, std::string> params;
        for (auto& param : paramsList) {
            params[param.first] = param.second;
        }
        EXPECT_EQ(2, params.size());
        EXPECT_NE(params.end(), params.find("key2"));
        EXPECT_EQ("", params["key2"]);
        EXPECT_EQ("foo", params["key3"]);
    }

    {
        // test query parameters
        std::string s("http://localhost?&key1=====&&=key2&key3=");
        Uri u = Uri::parse(s);
        auto paramsList = u.getQueryParams();
        std::map<std::string, std::string> params;
        for (auto& param : paramsList) {
            params[param.first] = param.second;
        }
        EXPECT_EQ(1, params.size());
        EXPECT_NE(params.end(), params.find("key3"));
        EXPECT_EQ("", params["key3"]);
    }

    {
        // test query parameters
        std::string s("ws://localhost:90?key1=foo=bar&key2=foobar&");
        Uri u = Uri::parse(s);
        auto paramsList = u.getQueryParams();
        std::map<std::string, std::string> params;
        for (auto& param : paramsList) {
            params[param.first] = param.second;
        }
        EXPECT_EQ(1, params.size());
        EXPECT_EQ("foobar", params["key2"]);

        // copy constructor
        {
            Uri v(u);
            u = v = u;
            EXPECT_TRUE(v.isValid());
            EXPECT_EQ("ws", v.getScheme());
            EXPECT_EQ("localhost", v.getHost());
            EXPECT_EQ("localhost", v.getHostName());
            EXPECT_EQ("", v.getPath());
            EXPECT_EQ(90, v.getPort());
            EXPECT_EQ("", v.getFragment());
            EXPECT_EQ("key1=foo=bar&key2=foobar&", v.getQuery());
            EXPECT_EQ(u, v);
        }

        // copy assign operator
        {
            Uri v;
            v = u;
            EXPECT_TRUE(v.isValid());
            EXPECT_EQ("ws", v.getScheme());
            EXPECT_EQ("localhost", v.getHost());
            EXPECT_EQ("localhost", v.getHostName());
            EXPECT_EQ("", v.getPath());
            EXPECT_EQ(90, v.getPort());
            EXPECT_EQ("", v.getFragment());
            EXPECT_EQ("key1=foo=bar&key2=foobar&", v.getQuery());
            EXPECT_EQ(u, v);
        }

        // Self move assignment
        {
            u = u;
            EXPECT_TRUE(u.isValid());
        }

        // Self move assignment
        {
            u = std::move(u);
            EXPECT_TRUE(u.isValid());
        }

        // move constructor
        {
            Uri v = std::move(u);
            EXPECT_FALSE(u.isValid());
            EXPECT_TRUE(v.isValid());
            EXPECT_EQ("ws", v.getScheme());
            EXPECT_EQ("localhost", v.getHost());
            EXPECT_EQ("localhost", v.getHostName());
            EXPECT_EQ("", v.getPath());
            EXPECT_EQ(90, v.getPort());
            EXPECT_EQ("", v.getFragment());
            EXPECT_EQ("key1=foo=bar&key2=foobar&", v.getQuery());
            u = std::move(v);
        }

        // copy assign operator
        {
            Uri v;
            v = std::move(u);
            EXPECT_FALSE(u.isValid());
            EXPECT_TRUE(v.isValid());
            EXPECT_EQ("ws", v.getScheme());
            EXPECT_EQ("localhost", v.getHost());
            EXPECT_EQ("localhost", v.getHostName());
            EXPECT_EQ("", v.getPath());
            EXPECT_EQ(90, v.getPort());
            EXPECT_EQ("", v.getFragment());
            EXPECT_EQ("key1=foo=bar&key2=foobar&", v.getQuery());
            u = v;
        }
    }

    {
        std::string s("2http://www.facebook.com");

        Uri u = Uri::parse(s);
        EXPECT_FALSE(u.isValid());
    }

    {
        std::string s("www[facebook]com");

        Uri u = Uri::parse("http://" + s);
        EXPECT_FALSE(u.isValid());
    }

    {
        std::string s("http://[::1:8080/hello/world?query#fragment");
        Uri u = Uri::parse(s);
        EXPECT_FALSE(u.isValid());
    }

    {
        std::string s("http://::1]:8080/hello/world?query#fragment");

        Uri u = Uri::parse(s);
        EXPECT_FALSE(u.isValid());
    }

    {
        std::string s("http://::1:8080/hello/world?query#fragment");
        Uri u = Uri::parse(s);
        EXPECT_FALSE(u.isValid());
    }

    {
        std::string s("http://2401:db00:20:7004:face:0:29:0/hello/world?query");
        Uri u = Uri::parse(s);
        EXPECT_FALSE(u.isValid());
    }

    {
        Uri http = Uri::parse("http://google.com");
        Uri https = Uri::parse("https://www.google.com:90");
        Uri query = Uri::parse("http://google.com:8080/foo/bar?foo=bar");
        Uri localhost = Uri::parse("http://localhost:8080");
        Uri ipv6 = Uri::parse("https://[2001:0db8:85a3:0042:1000:8a2e:0370:7334]");
        Uri ipv6short = Uri::parse("http://[2001:db8:85a3:42:1000:8a2e:370:7334]");
        Uri ipv6port = Uri::parse("http://[2001:db8:85a3:42:1000:8a2e:370:7334]:90");
        Uri ipv6abbrev = Uri::parse("http://[2001::7334:a:90]");
        Uri ipv6http = Uri::parse("http://[2001::7334:a]:90");
        Uri ipv6query = Uri::parse("http://[2001::7334:a]:90/foo/bar?foo=bar");

        EXPECT_EQ(http.getScheme(), "http");
        EXPECT_EQ(http.getPort(), 0);
        EXPECT_EQ(http.getHost(), "google.com");
        EXPECT_EQ(https.getScheme(), "https");
        EXPECT_EQ(https.getPort(), 90);
        EXPECT_EQ(https.getHost(), "www.google.com");
        EXPECT_EQ(query.getPort(), 8080);
        EXPECT_EQ(query.getPathEtc(), "/foo/bar?foo=bar");
        EXPECT_EQ(localhost.getScheme(), "http");
        EXPECT_EQ(localhost.getHost(), "localhost");
        EXPECT_EQ(localhost.getPort(), 8080);
        EXPECT_EQ(ipv6.getScheme(), "https");
        EXPECT_EQ(ipv6.getHostName(), "2001:0db8:85a3:0042:1000:8a2e:0370:7334");
        EXPECT_EQ(ipv6.getPort(), 0);
        EXPECT_EQ(ipv6short.getScheme(), "http");
        EXPECT_EQ(ipv6short.getHostName(), "2001:db8:85a3:42:1000:8a2e:370:7334");
        EXPECT_EQ(ipv6short.getPort(), 0);
        EXPECT_EQ(ipv6port.getScheme(), "http");
        EXPECT_EQ(ipv6port.getHostName(), "2001:db8:85a3:42:1000:8a2e:370:7334");
        EXPECT_EQ(ipv6port.getPort(), 90);
        EXPECT_EQ(ipv6abbrev.getScheme(), "http");
        EXPECT_EQ(ipv6abbrev.getHostName(), "2001::7334:a:90");
        EXPECT_EQ(ipv6abbrev.getPort(), 0);
        EXPECT_EQ(ipv6http.getScheme(), "http");
        EXPECT_EQ(ipv6http.getPort(), 90);
        EXPECT_EQ(ipv6http.getHostName(), "2001::7334:a");
        EXPECT_EQ(ipv6query.getScheme(), "http");
        EXPECT_EQ(ipv6query.getPort(), 90);
        EXPECT_EQ(ipv6query.getHostName(), "2001::7334:a");
        EXPECT_EQ(ipv6query.getPathEtc(), "/foo/bar?foo=bar");
    }

    {
        Uri u0 = Uri::parse("http://localhost:84/foo.html?&q=123");
        Uri u1 = Uri::parse("https://localhost:82/foo.html?&q=1");
        Uri u2 = Uri::parse("ws://localhost/foo");
        Uri u3 = Uri::parse("localhost/foo");
        Uri u4 = Uri::parse("localhost:8080");
        Uri u5 = Uri::parse("bb://localhost?&foo=12:4&ccc=13");
        Uri u6 = Uri::parse("cc://localhost:91?&foo=321&bbb=1");

        EXPECT_EQ(u0.getScheme(), "http");
        EXPECT_EQ(u0.getHost(), "localhost");
        EXPECT_EQ(u0.getPort(), 84);
        EXPECT_EQ(u0.getPath(), "/foo.html");
        EXPECT_EQ(u0.getPathEtc(), "/foo.html?&q=123");

        EXPECT_EQ(u1.getScheme(), "https");
        EXPECT_EQ(u1.getHost(), "localhost");
        EXPECT_EQ(u1.getPort(), 82);
        EXPECT_EQ(u1.getPathEtc(), "/foo.html?&q=1");

        EXPECT_EQ(u2.getScheme(), "ws");
        EXPECT_EQ(u2.getHost(), "localhost");
        EXPECT_EQ(u2.getPort(), 0);
        EXPECT_EQ(u2.getPath(), "/foo");

        EXPECT_EQ(u3.getScheme(), "");
        EXPECT_EQ(u3.getHost(), "localhost");
        EXPECT_EQ(u3.getPort(), 0);
        EXPECT_EQ(u3.getPath(), "/foo");

        EXPECT_EQ(u4.getScheme(), "");
        EXPECT_EQ(u4.getHost(), "localhost");
        EXPECT_EQ(u4.getPort(), 8080);
        EXPECT_EQ(u4.getPath(), "");
        EXPECT_EQ(u4.getPathEtc(), "");

        EXPECT_EQ(u5.getScheme(), "bb");
        EXPECT_EQ(u5.getHost(), "localhost");
        EXPECT_EQ(u5.getPort(), 0);
        EXPECT_EQ(u5.getPath(), "");
        EXPECT_EQ(u5.getPathEtc(), "?&foo=12:4&ccc=13");
        EXPECT_EQ(u5.getQuery(), "&foo=12:4&ccc=13");

        EXPECT_EQ(u6.getScheme(), "cc");
        EXPECT_EQ(u6.getHost(), "localhost");
        EXPECT_EQ(u6.getPort(), 91);
        EXPECT_EQ(u6.getPath(), "");
        EXPECT_EQ(u6.getPathEtc(), "?&foo=321&bbb=1");
        EXPECT_EQ(u6.getQuery(), "&foo=321&bbb=1");
    }

}

std::string ParseUriTest::subtitle() const
{
    return "Uri::parse Test";
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

// ResizableBufferAdapterTest

void ResizableBufferAdapterTest::onEnter()
{
    UnitTestDemo::onEnter();

    Data data;
    ResizableBufferAdapter<Data> buffer(&data);

    FileUtils::getInstance()->getContents("effect1.wav", &buffer);
    EXPECT_EQ(data.getSize(), 10026);

    FileUtils::getInstance()->getContents("effect2.ogg", &buffer);
    EXPECT_EQ(data.getSize(), 4278);

    FileUtils::getInstance()->getContents("effect1.wav", &buffer);
    EXPECT_EQ(data.getSize(), 10026);
}

std::string ResizableBufferAdapterTest::subtitle() const
{
    return "ResiziableBufferAdapter<Data> Test";
}


