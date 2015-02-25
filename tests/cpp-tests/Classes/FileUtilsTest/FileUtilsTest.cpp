#include "FileUtilsTest.h"

static std::function<Layer*()> createFunctions[] = {
    CL(TestResolutionDirectories),
    CL(TestSearchPath),
    CL(TestFilenameLookup),
    CL(TestIsFileExist),
    CL(TestFileFuncs),
    CL(TestDirectoryFuncs),
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
    auto scene = new (std::nothrow) FileUtilsTestScene();
    auto layer = backAction();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void FileUtilsDemo::nextCallback(Ref* sender)
{
    auto scene = new (std::nothrow) FileUtilsTestScene();
    auto layer = nextAction();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void FileUtilsDemo::restartCallback(Ref* sender)
{
    auto scene = new (std::nothrow) FileUtilsTestScene();
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
        auto filename = StringUtils::format("test%d.txt", i);
        ret = sharedFileUtils->fullPathForFilename(filename);
        log("%s -> %s", filename.c_str(), ret.c_str());
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
        auto filename = StringUtils::format("file%d.txt", i);
        ret = sharedFileUtils->fullPathForFilename(filename);
        log("%s -> %s", filename.c_str(), ret.c_str());
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
    sprite->setPosition(s.width/2, s.height/2);
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
    
    Label* label = nullptr;
    bool isExist = false;
    
    isExist = sharedFileUtils->isFileExist("Images/grossini.png");
    
    label = Label::createWithSystemFont(isExist ? "Images/grossini.png exists" : "Images/grossini.png doesn't exist", "", 20);
    label->setPosition(s.width/2, s.height/3);
    this->addChild(label);
    
    isExist = sharedFileUtils->isFileExist("Images/grossini.xcf");
    label = Label::createWithSystemFont(isExist ? "Images/grossini.xcf exists" : "Images/grossini.xcf doesn't exist", "", 20);
    label->setPosition(s.width/2, s.height/3*2);
    this->addChild(label);
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

// TestFileFuncs

void TestFileFuncs::onEnter()
{
    FileUtilsDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    auto sharedFileUtils = FileUtils::getInstance();
    
    int x = s.width/2,
        y = s.height/5;
    Label* label = nullptr;
    
    std::string filename = "__test.test";
    std::string filename2 = "__newtest.test";
    std::string filepath = sharedFileUtils->getWritablePath() + filename;
    std::string content = "Test string content to put into created file";
    std::string msg;
    
    FILE *out = fopen(filepath.c_str(), "w");
    fputs(content.c_str(), out);
    fclose(out);
    
    // Check whether file can be created
    if (sharedFileUtils->isFileExist(filepath))
    {
        label = Label::createWithSystemFont("Test file '__test.test' created", "", 20);
        label->setPosition(x, y * 4);
        this->addChild(label);
        
        // getFileSize Test
        long size = sharedFileUtils->getFileSize(filepath);
        msg = StringUtils::format("getFileSize: Test file size equals %ld", size);
        label = Label::createWithSystemFont(msg, "", 20);
        label->setPosition(x, y * 3);
        this->addChild(label);
        
        // renameFile Test
        if (sharedFileUtils->renameFile(sharedFileUtils->getWritablePath(), filename, filename2))
        {
            label = Label::createWithSystemFont("renameFile: Test file renamed to  '__newtest.test'", "", 20);
            label->setPosition(x, y * 2);
            this->addChild(label);
            
            // removeFile Test
            filepath = sharedFileUtils->getWritablePath() + filename2;
            if (sharedFileUtils->removeFile(filepath))
            {
                label = Label::createWithSystemFont("removeFile: Test file removed", "", 20);
                label->setPosition(x, y * 1);
                this->addChild(label);
            }
            else
            {
                label = Label::createWithSystemFont("removeFile: Failed to remove test file", "", 20);
                label->setPosition(x, y * 1);
                this->addChild(label);
            }
        }
        else
        {
            label = Label::createWithSystemFont("renameFile: Failed to rename test file to  '__newtest.test', further test skipped", "", 20);
            label->setPosition(x, y * 2);
            this->addChild(label);
        }
    }
    else
    {
        label = Label::createWithSystemFont("Test file can not be created, test skipped", "", 20);
        label->setPosition(x, y * 4);
        this->addChild(label);
    }
}

std::string TestFileFuncs::title() const
{
    return "FileUtils: file control functions";
}

std::string TestFileFuncs::subtitle() const
{
    return "";
}

// TestDirectoryFuncs

void TestDirectoryFuncs::onEnter()
{
    FileUtilsDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    auto sharedFileUtils = FileUtils::getInstance();
    
    int x = s.width/2,
    y = s.height/4;
    Label* label = nullptr;
    
    std::string dir = sharedFileUtils->getWritablePath() + "__test/";
    std::string subDir = "dir1/dir2";
    std::string msg;
    bool ok;
    
    // Check whether dir can be created
    ok = sharedFileUtils->createDirectory(dir);
    if (ok && sharedFileUtils->isDirectoryExist(dir))
    {
        msg = StringUtils::format("createDirectory: Directory '__test' created");
        label = Label::createWithSystemFont(msg, "", 20);
        label->setPosition(x, y * 3);
        this->addChild(label);
        
        // Create sub directories recursively
        ok = sharedFileUtils->createDirectory(dir + subDir);
        if (ok && sharedFileUtils->isDirectoryExist(dir + subDir))
        {
            msg = StringUtils::format("createDirectory: Sub directories '%s' created", subDir.c_str());
            label = Label::createWithSystemFont(msg, "", 20);
            label->setPosition(x, y * 2);
            this->addChild(label);
        }
        else
        {
            msg = StringUtils::format("createDirectory: Failed to create sub directories '%s'", subDir.c_str());
            label = Label::createWithSystemFont(msg, "", 20);
            label->setPosition(x, y * 2);
            this->addChild(label);
        }
        
        // Remove directory
        ok = sharedFileUtils->removeDirectory(dir);
        if (ok && !sharedFileUtils->isDirectoryExist(dir))
        {
            msg = StringUtils::format("removeDirectory: Directory '__test' removed");
            label = Label::createWithSystemFont(msg, "", 20);
            label->setPosition(x, y);
            this->addChild(label);
        }
        else
        {
            msg = StringUtils::format("removeDirectory: Failed to remove directory '__test'");
            label = Label::createWithSystemFont(msg, "", 20);
            label->setPosition(x, y);
            this->addChild(label);
        }
    }
    else
    {
        msg = StringUtils::format("createDirectory: Directory '__test' can not be created");
        label = Label::createWithSystemFont(msg, "", 20);
        label->setPosition(x, y * 2);
        this->addChild(label);
    }
}

std::string TestDirectoryFuncs::title() const
{
    return "FileUtils: directory control functions";
}

std::string TestDirectoryFuncs::subtitle() const
{
    return "";
}

// TestWritePlist

void TextWritePlist::onEnter()
{
    FileUtilsDemo::onEnter();
    auto root = ValueMap();
    root["string element key"] = "string element value";
    
    auto array = ValueVector();
    
    auto dictInArray = ValueMap();
    dictInArray["string in dictInArray key 0"] = "string in dictInArray value 0";
    dictInArray["string in dictInArray key 1"] = "string in dictInArray value 1";
    array.push_back(Value(dictInArray));
    
    array.push_back(Value("string in array"));
    
    auto arrayInArray = ValueVector();
    arrayInArray.push_back(Value("string 0 in arrayInArray"));
    arrayInArray.push_back(Value("string 1 in arrayInArray"));
    array.push_back(Value(arrayInArray));
    
    root["array"] = array;
    
    auto dictInDict = ValueMap();
    dictInDict["string in dictInDict key"] = "string in dictInDict value";
   
    //add boolean to the plist
    dictInDict["bool"] = true;
    
    //add interger to the plist
    dictInDict["integer"] = 1024;
    
    //add float to the plist
    dictInDict["float"] = 1024.1024f;
    
    //add double to the plist
    dictInDict["double"] = 1024.123;
    
    root["dictInDict, Hello World"] = dictInDict;
    
    // end with /
    auto fileInstance = FileUtils::getInstance();
    std::string writablePath = fileInstance->getWritablePath();
    std::string fullPath = writablePath + "text.plist";
    if( fileInstance->writeToFile(root, fullPath))
        log("see the plist file at %s", fullPath.c_str());
    else
        log("write plist file failed");
    
    auto label = Label::createWithTTF(fullPath.c_str(), "fonts/Thonburi.ttf", 6);
    this->addChild(label);
    auto winSize = Director::getInstance()->getWinSize();
    label->setPosition(winSize.width/2, winSize.height/3);
    
    auto loadDict = fileInstance->getValueMapFromFile(fullPath);
    auto& loadDictInDict = loadDict["dictInDict, Hello World"].asValueMap();
  
    log("%s",loadDictInDict["bool"].asString().c_str());
    log("%s",loadDictInDict["float"].asString().c_str());
    log("%s",loadDictInDict["integer"].asString().c_str());
    log("%s",loadDictInDict["double"].asString().c_str());
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
