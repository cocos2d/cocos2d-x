#include "FileUtilsTest.h"

static std::function<Layer*()> createFunctions[] = {
    CL(TestResolutionDirectories),
    CL(TestSearchPath),
    CL(TestFilenameLookup),
    CL(TestIsFileExist),
    CL(TextWritePlist),
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

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

void FileUtilsTestScene::runThisTest()
{
    auto layer = nextAction();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}

//  FileUtilsDemo

void FileUtilsDemo::onEnter()
{
    BaseTest::onEnter();    
}

void FileUtilsDemo::backCallback(Ref* sender)
{
    auto scene = new FileUtilsTestScene();
    auto layer = backAction();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void FileUtilsDemo::nextCallback(Ref* sender)
{
    auto scene = new FileUtilsTestScene();
    auto layer = nextAction();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void FileUtilsDemo::restartCallback(Ref* sender)
{
    auto scene = new FileUtilsTestScene();
    auto layer = restartAction();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

std::string FileUtilsDemo::title() const
{
    return "No title";
}

std::string FileUtilsDemo::subtitle() const
{
    return "";
}

// TestResolutionDirectories

void TestResolutionDirectories::onEnter()
{
    FileUtilsDemo::onEnter();
    auto sharedFileUtils = FileUtils::getInstance();

    std::string ret;
    
    sharedFileUtils->purgeCachedEntries();
    _defaultSearchPathArray = sharedFileUtils->getSearchPaths();
    std::vector<std::string> searchPaths = _defaultSearchPathArray;
    searchPaths.insert(searchPaths.begin(),   "Misc");
    sharedFileUtils->setSearchPaths(searchPaths);
    
    _defaultResolutionsOrderArray = sharedFileUtils->getSearchResolutionsOrder();
    std::vector<std::string> resolutionsOrder = _defaultResolutionsOrderArray;

    resolutionsOrder.insert(resolutionsOrder.begin(), "resources-ipadhd");
    resolutionsOrder.insert(resolutionsOrder.begin()+1, "resources-ipad");
    resolutionsOrder.insert(resolutionsOrder.begin()+2, "resources-widehd");
    resolutionsOrder.insert(resolutionsOrder.begin()+3, "resources-wide");
    resolutionsOrder.insert(resolutionsOrder.begin()+4, "resources-hd");
    resolutionsOrder.insert(resolutionsOrder.begin()+5, "resources-iphone");
    
    sharedFileUtils->setSearchResolutionsOrder(resolutionsOrder);
    
    for( int i=1; i<7; i++) {
        auto filename = String::createWithFormat("test%d.txt", i);
        ret = sharedFileUtils->fullPathForFilename(filename->getCString());
        log("%s -> %s", filename->getCString(), ret.c_str());
    }
}

void TestResolutionDirectories::onExit()
{
    auto sharedFileUtils = FileUtils::getInstance();
    
	// reset search path
	sharedFileUtils->setSearchPaths(_defaultSearchPathArray);
    sharedFileUtils->setSearchResolutionsOrder(_defaultResolutionsOrderArray);
    FileUtilsDemo::onExit();
}

std::string TestResolutionDirectories::title() const
{
    return "FileUtils: resolutions in directories";
}

std::string TestResolutionDirectories::subtitle() const
{
    return "See the console";
}

// TestSearchPath

void TestSearchPath::onEnter()
{
    FileUtilsDemo::onEnter();
    auto sharedFileUtils = FileUtils::getInstance();
    
    std::string ret;
    
    sharedFileUtils->purgeCachedEntries();
    _defaultSearchPathArray = sharedFileUtils->getSearchPaths();
    std::vector<std::string> searchPaths = _defaultSearchPathArray;
    std::string writablePath = sharedFileUtils->getWritablePath();
    std::string fileName = writablePath+"external.txt";
    char szBuf[100] = "Hello Cocos2d-x!";
    FILE* fp = fopen(fileName.c_str(), "wb");
    if (fp)
    {
        size_t ret = fwrite(szBuf, 1, strlen(szBuf), fp);
        CCASSERT(ret != 0, "fwrite function returned zero value");
        fclose(fp);
        if (ret != 0)
            log("Writing file to writable path succeed.");
    }
    
    searchPaths.insert(searchPaths.begin(), writablePath);
    searchPaths.insert(searchPaths.begin()+1,   "Misc/searchpath1");
    searchPaths.insert(searchPaths.begin()+2, "Misc/searchpath2");
    sharedFileUtils->setSearchPaths(searchPaths);
    
    _defaultResolutionsOrderArray = sharedFileUtils->getSearchResolutionsOrder();
    std::vector<std::string> resolutionsOrder = _defaultResolutionsOrderArray;
    
    resolutionsOrder.insert(resolutionsOrder.begin(), "resources-ipad");
    sharedFileUtils->setSearchResolutionsOrder(resolutionsOrder);
    
    for( int i=1; i<3; i++) {
        auto filename = String::createWithFormat("file%d.txt", i);
        ret = sharedFileUtils->fullPathForFilename(filename->getCString());
        log("%s -> %s", filename->getCString(), ret.c_str());
    }
    
    // Gets external.txt from writable path
    std::string fullPath = sharedFileUtils->fullPathForFilename("external.txt");
    log("external file path = %s", fullPath.c_str());
    if (fullPath.length() > 0)
    {
        fp = fopen(fullPath.c_str(), "rb");
        if (fp)
        {
            char szReadBuf[100] = {0};
            size_t read = fread(szReadBuf, 1, strlen(szBuf), fp);
            if (read > 0)
                log("The content of file from writable path: %s", szReadBuf);
            fclose(fp);
        }
    }
}

void TestSearchPath::onExit()
{
	FileUtils *sharedFileUtils = FileUtils::getInstance();

	// reset search path
	sharedFileUtils->setSearchPaths(_defaultSearchPathArray);
    sharedFileUtils->setSearchResolutionsOrder(_defaultResolutionsOrderArray);
    FileUtilsDemo::onExit();
}

std::string TestSearchPath::title() const
{
    return "FileUtils: search path";
}

std::string TestSearchPath::subtitle() const
{
    return "See the console";
}

// TestFilenameLookup

void TestFilenameLookup::onEnter()
{
    FileUtilsDemo::onEnter();
		
    auto sharedFileUtils = FileUtils::getInstance();

    ValueMap dict;
    dict["grossini.bmp"] = Value("Images/grossini.png");
    dict["grossini.xcf"] = Value("Images/grossini.png");
    
    sharedFileUtils->setFilenameLookupDictionary(dict);
    
    // Instead of loading carlitos.xcf, it will load grossini.png
    auto sprite = Sprite::create("grossini.xcf");
    this->addChild(sprite);
    
    auto s = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(s.width/2, s.height/2));
}

void TestFilenameLookup::onExit()
{
	
	FileUtils *sharedFileUtils = FileUtils::getInstance();
	
	// reset filename lookup
    sharedFileUtils->setFilenameLookupDictionary(ValueMap());
	
    FileUtilsDemo::onExit();
}

std::string TestFilenameLookup::title() const
{
    return "FileUtils: filename lookup";
}

// TestIsFileExist

void TestIsFileExist::onEnter()
{
    FileUtilsDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    auto sharedFileUtils = FileUtils::getInstance();
    
    Label* pTTF = nullptr;
    bool isExist = false;
    
    isExist = sharedFileUtils->isFileExist("Images/grossini.png");
    
    pTTF = Label::createWithSystemFont(isExist ? "Images/grossini.png exists" : "Images/grossini.png doesn't exist", "", 20);
    pTTF->setPosition(Vec2(s.width/2, s.height/3));
    this->addChild(pTTF);
    
    isExist = sharedFileUtils->isFileExist("Images/grossini.xcf");
    pTTF = Label::createWithSystemFont(isExist ? "Images/grossini.xcf exists" : "Images/grossini.xcf doesn't exist", "", 20);
    pTTF->setPosition(Vec2(s.width/2, s.height/3*2));
    this->addChild(pTTF);
}

void TestIsFileExist::onExit()
{
	
	FileUtils *sharedFileUtils = FileUtils::getInstance();
	
	// reset filename lookup
    sharedFileUtils->setFilenameLookupDictionary(ValueMap());
	
    FileUtilsDemo::onExit();
}

std::string TestIsFileExist::title() const
{
    return "FileUtils: check whether the file exists";
}

std::string TestIsFileExist::subtitle() const
{
    return "";
}

// TestWritePlist

void TextWritePlist::onEnter()
{
    FileUtilsDemo::onEnter();
    auto root = Dictionary::create();
    auto string = String::create("string element value");
    root->setObject(string, "string element key");
    
    auto array = Array::create();
    
    auto dictInArray = Dictionary::create();
    dictInArray->setObject(String::create("string in dictInArray value 0"), "string in dictInArray key 0");
    dictInArray->setObject(String::create("string in dictInArray value 1"), "string in dictInArray key 1");
    array->addObject(dictInArray);
    
    array->addObject(String::create("string in array"));
    
    auto arrayInArray = Array::create();
    arrayInArray->addObject(String::create("string 0 in arrayInArray"));
    arrayInArray->addObject(String::create("string 1 in arrayInArray"));
    array->addObject(arrayInArray);
    
    root->setObject(array, "array");
    
    auto dictInDict = Dictionary::create();
    dictInDict->setObject(String::create("string in dictInDict value"), "string in dictInDict key");
   
    //add boolean to the plist
    auto booleanObject = Bool::create(true);
    dictInDict->setObject(booleanObject, "bool");
    
    //add interger to the plist
    auto intObject = Integer::create(1024);
    dictInDict->setObject(intObject, "integer");
    
    //add float to the plist
    auto floatObject = Float::create(1024.1024f);
    dictInDict->setObject(floatObject, "float");
    
    //add double to the plist
    auto doubleObject = Double::create(1024.123);
    dictInDict->setObject(doubleObject, "double");
    
    
    
    root->setObject(dictInDict, "dictInDict, Hello World");
    
    // end with /
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fullPath = writablePath + "text.plist";
    if(root->writeToFile(fullPath.c_str()))
        log("see the plist file at %s", fullPath.c_str());
    else
        log("write plist file failed");
    
    auto label = Label::createWithTTF(fullPath.c_str(), "fonts/Thonburi.ttf", 6);
    this->addChild(label);
    auto winSize = Director::getInstance()->getWinSize();
    label->setPosition(Vec2(winSize.width/2, winSize.height/3));
    
    auto loadDict = __Dictionary::createWithContentsOfFile(fullPath.c_str());
    auto loadDictInDict = (__Dictionary*)loadDict->objectForKey("dictInDict, Hello World");
    auto boolValue = (__String*)loadDictInDict->objectForKey("bool");
    CCLOG("%s",boolValue->getCString());
    auto floatValue = (__String*)loadDictInDict->objectForKey("float");
    CCLOG("%s",floatValue->getCString());
    auto intValue = (__String*)loadDictInDict->objectForKey("integer");
    CCLOG("%s",intValue->getCString());
    auto doubleValue = (__String*)loadDictInDict->objectForKey("double");
    CCLOG("%s",doubleValue->getCString());

}

void TextWritePlist::onExit()
{
    FileUtilsDemo::onExit();
}

std::string TextWritePlist::title() const
{
    return "FileUtils: Dictionary to plist";
}

std::string TextWritePlist::subtitle() const
{
    std::string writablePath = FileUtils::getInstance()->getWritablePath().c_str();
    return ("See plist file at your writablePath");
}
