#include "UnitTest.h"
#include "RefPtrTest.h"

// For ' < o > ' multiply test scene.

static std::function<Layer*()> createFunctions[] = {
    CL(TemplateVectorTest),
    CL(TemplateMapTest),
    CL(ValueTest),
    CL(RefPtrTest)
};

static int sceneIdx = -1;
static const int  MAX_LAYER = (sizeof(createFunctions) / sizeof(createFunctions[0]));

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* restartAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

void UnitTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());
    Director::getInstance()->replaceScene(this);
}

void UnitTestDemo::onEnter()
{
    BaseTest::onEnter();
}

void UnitTestDemo::onExit()
{
    BaseTest::onExit();
}

std::string UnitTestDemo::title() const
{
    return "UnitTest";
}

std::string UnitTestDemo::subtitle() const
{
    return "";
}

void UnitTestDemo::restartCallback(Ref* sender)
{
    auto s = new UnitTestScene();
    s->addChild( restartAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void UnitTestDemo::nextCallback(Ref* sender)
{
    auto s = new UnitTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void UnitTestDemo::backCallback(Ref* sender)
{
    auto s = new UnitTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
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
