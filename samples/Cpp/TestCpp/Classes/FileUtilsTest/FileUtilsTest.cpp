#include "FileUtilsTest.h"


TESTLAYER_CREATE_FUNC(TestResolutionDirectories);
TESTLAYER_CREATE_FUNC(TestSearchPath);
TESTLAYER_CREATE_FUNC(TestFilenameLookup);
TESTLAYER_CREATE_FUNC(TestIsFileExist);
TESTLAYER_CREATE_FUNC(TextWritePlist);

static NEWTESTFUNC createFunctions[] = {
    CF(TestResolutionDirectories),
    CF(TestSearchPath),
    CF(TestFilenameLookup),
    CF(TestIsFileExist),
    CF(TextWritePlist),
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static Layer* restartAction()
{
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

void FileUtilsTestScene::runThisTest()
{
    Layer* pLayer = nextAction();
    addChild(pLayer);
    
    Director::sharedDirector()->replaceScene(this);
}

// #pragma mark - FileUtilsDemo

void FileUtilsDemo::onEnter()
{
    BaseTest::onEnter();    
}

void FileUtilsDemo::backCallback(Object* pSender)
{
    Scene* pScene = new FileUtilsTestScene();
    Layer* pLayer = backAction();
    
    pScene->addChild(pLayer);
    Director::sharedDirector()->replaceScene(pScene);
    pScene->release();
}

void FileUtilsDemo::nextCallback(Object* pSender)
{
    Scene* pScene = new FileUtilsTestScene();
    Layer* pLayer = nextAction();
    
    pScene->addChild(pLayer);
    Director::sharedDirector()->replaceScene(pScene);
    pScene->release();
}

void FileUtilsDemo::restartCallback(Object* pSender)
{
    Scene* pScene = new FileUtilsTestScene();
    Layer* pLayer = restartAction();
    
    pScene->addChild(pLayer);
    Director::sharedDirector()->replaceScene(pScene);
    pScene->release();
}

string FileUtilsDemo::title()
{
    return "No title";
}

string FileUtilsDemo::subtitle()
{
    return "";
}

//#pragma mark - TestResolutionDirectories

void TestResolutionDirectories::onEnter()
{
    FileUtilsDemo::onEnter();
    FileUtils *sharedFileUtils = FileUtils::sharedFileUtils();

    string ret;
    
    sharedFileUtils->purgeCachedEntries();
    _defaultSearchPathArray = sharedFileUtils->getSearchPaths();
    vector<string> searchPaths = _defaultSearchPathArray;
    searchPaths.insert(searchPaths.begin(),   "Misc");
    sharedFileUtils->setSearchPaths(searchPaths);
    
    _defaultResolutionsOrderArray = sharedFileUtils->getSearchResolutionsOrder();
    vector<string> resolutionsOrder = _defaultResolutionsOrderArray;

    resolutionsOrder.insert(resolutionsOrder.begin(), "resources-ipadhd");
    resolutionsOrder.insert(resolutionsOrder.begin()+1, "resources-ipad");
    resolutionsOrder.insert(resolutionsOrder.begin()+2, "resources-widehd");
    resolutionsOrder.insert(resolutionsOrder.begin()+3, "resources-wide");
    resolutionsOrder.insert(resolutionsOrder.begin()+4, "resources-hd");
    resolutionsOrder.insert(resolutionsOrder.begin()+5, "resources-iphone");
    
    sharedFileUtils->setSearchResolutionsOrder(resolutionsOrder);
    
    for( int i=1; i<7; i++) {
        String *filename = String::createWithFormat("test%d.txt", i);
        ret = sharedFileUtils->fullPathForFilename(filename->getCString());
        CCLog("%s -> %s", filename->getCString(), ret.c_str());
    }
}

void TestResolutionDirectories::onExit()
{
    FileUtils *sharedFileUtils = FileUtils::sharedFileUtils();
    
	// reset search path
	sharedFileUtils->setSearchPaths(_defaultSearchPathArray);
    sharedFileUtils->setSearchResolutionsOrder(_defaultResolutionsOrderArray);
    FileUtilsDemo::onExit();
}

string TestResolutionDirectories::title()
{
    return "FileUtils: resolutions in directories";
}

string TestResolutionDirectories::subtitle()
{
    return "See the console";
}

//#pragma mark - TestSearchPath

void TestSearchPath::onEnter()
{
    FileUtilsDemo::onEnter();
    FileUtils *sharedFileUtils = FileUtils::sharedFileUtils();
    
    string ret;
    
    sharedFileUtils->purgeCachedEntries();
    _defaultSearchPathArray = sharedFileUtils->getSearchPaths();
    vector<string> searchPaths = _defaultSearchPathArray;
    string writablePath = sharedFileUtils->getWritablePath();
    string fileName = writablePath+"external.txt";
    char szBuf[100] = "Hello Cocos2d-x!";
    FILE* fp = fopen(fileName.c_str(), "wb");
    if (fp)
    {
        size_t ret = fwrite(szBuf, 1, strlen(szBuf), fp);
        CCAssert(ret == 0, "fwrite function returned nonzero value");
        fclose(fp);
        if (ret == 0)
            CCLog("Writing file to writable path succeed.");
    }
    
    searchPaths.insert(searchPaths.begin(), writablePath);
    searchPaths.insert(searchPaths.begin()+1,   "Misc/searchpath1");
    searchPaths.insert(searchPaths.begin()+2, "Misc/searchpath2");
    sharedFileUtils->setSearchPaths(searchPaths);
    
    _defaultResolutionsOrderArray = sharedFileUtils->getSearchResolutionsOrder();
    vector<string> resolutionsOrder = _defaultResolutionsOrderArray;
    
    resolutionsOrder.insert(resolutionsOrder.begin(), "resources-ipad");
    sharedFileUtils->setSearchResolutionsOrder(resolutionsOrder);
    
    for( int i=1; i<3; i++) {
        String *filename = String::createWithFormat("file%d.txt", i);
        ret = sharedFileUtils->fullPathForFilename(filename->getCString());
        CCLog("%s -> %s", filename->getCString(), ret.c_str());
    }
    
    // Gets external.txt from writable path
    string fullPath = sharedFileUtils->fullPathForFilename("external.txt");
    CCLog("external file path = %s", fullPath.c_str());
    if (fullPath.length() > 0)
    {
        fp = fopen(fullPath.c_str(), "rb");
        if (fp)
        {
            char szReadBuf[100] = {0};
            int read = fread(szReadBuf, 1, strlen(szBuf), fp);
            if (read > 0)
                CCLog("The content of file from writable path: %s", szReadBuf);
            fclose(fp);
        }
    }
}

void TestSearchPath::onExit()
{
	FileUtils *sharedFileUtils = FileUtils::sharedFileUtils();

	// reset search path
	sharedFileUtils->setSearchPaths(_defaultSearchPathArray);
    sharedFileUtils->setSearchResolutionsOrder(_defaultResolutionsOrderArray);
    FileUtilsDemo::onExit();
}

string TestSearchPath::title()
{
    return "FileUtils: search path";
}

string TestSearchPath::subtitle()
{
    return "See the console";
}

//#pragma mark - TestFilenameLookup

void TestFilenameLookup::onEnter()
{
    FileUtilsDemo::onEnter();
		
    FileUtils *sharedFileUtils = FileUtils::sharedFileUtils();

    Dictionary *dict = Dictionary::create();
    dict->setObject(String::create("Images/grossini.png"), "grossini.bmp");
    dict->setObject(String::create("Images/grossini.png"), "grossini.xcf");
    
    sharedFileUtils->setFilenameLookupDictionary(dict);
    
    
    // Instead of loading carlitos.xcf, it will load grossini.png
    Sprite *sprite = Sprite::create("grossini.xcf");
    this->addChild(sprite);
    
    Size s = Director::sharedDirector()->getWinSize();
    sprite->setPosition(ccp(s.width/2, s.height/2));
}

void TestFilenameLookup::onExit()
{
	
	FileUtils *sharedFileUtils = FileUtils::sharedFileUtils();
	
	// reset filename lookup
    sharedFileUtils->setFilenameLookupDictionary(Dictionary::create());
	
    FileUtilsDemo::onExit();
}

string TestFilenameLookup::title()
{
    return "FileUtils: filename lookup";
}

string TestFilenameLookup::subtitle()
{
    return "See the console";
}

//#pragma mark - TestIsFileExist

void TestIsFileExist::onEnter()
{
    FileUtilsDemo::onEnter();
    Size s = Director::sharedDirector()->getWinSize();
    FileUtils *sharedFileUtils = FileUtils::sharedFileUtils();
    
    LabelTTF* pTTF = NULL;
    bool isExist = false;
    
    isExist = sharedFileUtils->isFileExist("Images/grossini.png");
    
    pTTF = LabelTTF::create(isExist ? "Images/grossini.png exists" : "Images/grossini.png doesn't exist", "", 20);
    pTTF->setPosition(ccp(s.width/2, s.height/3));
    this->addChild(pTTF);
    
    isExist = sharedFileUtils->isFileExist("Images/grossini.xcf");
    pTTF = LabelTTF::create(isExist ? "Images/grossini.xcf exists" : "Images/grossini.xcf doesn't exist", "", 20);
    pTTF->setPosition(ccp(s.width/2, s.height/3*2));
    this->addChild(pTTF);
}

void TestIsFileExist::onExit()
{
	
	FileUtils *sharedFileUtils = FileUtils::sharedFileUtils();
	
	// reset filename lookup
    sharedFileUtils->setFilenameLookupDictionary(Dictionary::create());
	
    FileUtilsDemo::onExit();
}

string TestIsFileExist::title()
{
    return "FileUtils: check whether the file exists";
}

string TestIsFileExist::subtitle()
{
    return "";
}

//#pragma mark - TestWritePlist

void TextWritePlist::onEnter()
{
    FileUtilsDemo::onEnter();
    Dictionary *root = Dictionary::create();
    String *string = String::create("string element value");
    root->setObject(string, "string element key");
    
    Array *array = Array::create();
    
    Dictionary *dictInArray = Dictionary::create();
    dictInArray->setObject(String::create("string in dictInArray value 0"), "string in dictInArray key 0");
    dictInArray->setObject(String::create("string in dictInArray value 1"), "string in dictInArray key 1");
    array->addObject(dictInArray);
    
    array->addObject(String::create("string in array"));
    
    Array *arrayInArray = Array::create();
    arrayInArray->addObject(String::create("string 0 in arrayInArray"));
    arrayInArray->addObject(String::create("string 1 in arrayInArray"));
    array->addObject(arrayInArray);
    
    root->setObject(array, "array");
    
    Dictionary *dictInDict = Dictionary::create();
    dictInDict->setObject(String::create("string in dictInDict value"), "string in dictInDict key");
    
    root->setObject(dictInDict, "dictInDict");
    
    // end with /
    std::string writablePath = FileUtils::sharedFileUtils()->getWritablePath();
    std::string fullPath = writablePath + "text.plist";
    if(root->writeToFile(fullPath.c_str()))
        CCLog("see the plist file at %s", fullPath.c_str());
    else
        CCLog("write plist file failed");
    
    LabelTTF *label = LabelTTF::create(fullPath.c_str(), "Thonburi", 6);
    this->addChild(label);
    Size winSize = Director::sharedDirector()->getWinSize();
    label->setPosition(ccp(winSize.width/2, winSize.height/3));
}

void TextWritePlist::onExit()
{
    FileUtilsDemo::onExit();
}

string TextWritePlist::title()
{
    return "FileUtils: Dictionary to plist";
}

string TextWritePlist::subtitle()
{
    std::string writablePath = FileUtils::sharedFileUtils()->getWritablePath().c_str();
    return ("See plist file at your writablePath");
}
