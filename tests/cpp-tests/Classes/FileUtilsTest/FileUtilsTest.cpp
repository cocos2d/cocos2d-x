#include "FileUtilsTest.h"

USING_NS_CC;

FileUtilsTests::FileUtilsTests()
{
    ADD_TEST_CASE(TestResolutionDirectories);
    ADD_TEST_CASE(TestSearchPath);
    ADD_TEST_CASE(TestFilenameLookup);
    ADD_TEST_CASE(TestIsFileExist);
    ADD_TEST_CASE(TestFileFuncs);
    ADD_TEST_CASE(TestDirectoryFuncs);
    ADD_TEST_CASE(TextWritePlist);
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
    label->setPosition(winSize.width/2, winSize.height/3);
    
    auto loadDict = __Dictionary::createWithContentsOfFile(fullPath.c_str());
    auto loadDictInDict = (__Dictionary*)loadDict->objectForKey("dictInDict, Hello World");
    auto boolValue = (__String*)loadDictInDict->objectForKey("bool");
    log("%s",boolValue->getCString());
    auto floatValue = (__String*)loadDictInDict->objectForKey("float");
    log("%s",floatValue->getCString());
    auto intValue = (__String*)loadDictInDict->objectForKey("integer");
    log("%s",intValue->getCString());
    auto doubleValue = (__String*)loadDictInDict->objectForKey("double");
    log("%s",doubleValue->getCString());

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
