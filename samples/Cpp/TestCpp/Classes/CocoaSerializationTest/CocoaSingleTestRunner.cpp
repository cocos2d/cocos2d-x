#include "CocoaSingleTestRunner.h"
#include "CocoaDataEqualityChecker.h"

USING_NS_CC;

////////////////////////////////////////////////////////////////////////////////

class Utils
{
public:
    static std::string getInPath(const std::string &resourceName);
    static std::string getOutPath(const std::string &resourceName);
    static bool readDictionary(const std::string &path, CCDictionary *&placeholder);
    static bool writeResourceOnDisk(const std::string &resource);
    static bool writeDictionary(CCDictionary *dictionary, const std::string &path);
    static bool compareDictionaries(CCDictionary *in, CCDictionary *out);
    static bool checkFileExists(const std::string &path);
    static bool printDictionary(const std::string &description, CCDictionary *dictionary);
};

////////////////////////////////////////////////////////////////////////////////

bool runCocoaSerializationTestCase(const std::string &resourcePath)
{
    const std::string pathIn = Utils::getInPath(resourcePath);
    const std::string pathOut = Utils::getOutPath(resourcePath);
    CCDictionary *in = NULL;
    CCDictionary *out = NULL;

    bool ok = Utils::writeResourceOnDisk(resourcePath)
            && Utils::checkFileExists(pathIn)
            && Utils::readDictionary(pathIn, in)
            && Utils::printDictionary("dict from resources", in)
            && Utils::writeDictionary(in, pathOut)
            && Utils::checkFileExists(pathOut)
            && Utils::readDictionary(pathOut, out)
            && Utils::printDictionary("final dict", out)
            && Utils::compareDictionaries(in, out);

    return ok;
}

////////////////////////////////////////////////////////////////////////////////

bool Utils::writeResourceOnDisk(const std::string &resource)
{
    const std::string readPath = resource;

    unsigned long size = 0;
    unsigned char *data = CCFileUtils::sharedFileUtils()->getFileData(readPath.c_str(), "r", &size);
    const std::string writePath = getInPath(resource);

    if (FILE *out = fopen(writePath.c_str(), "w")) {
        unsigned long count = fwrite(data, sizeof(unsigned char), size, out);
        fclose(out);
        if (size != count) {
            CCLOG("Write failed for path '%s'.", writePath.c_str());
            return false;
        }
    } else {
        CCLOG("Cannot open path '%s' for writing.", writePath.c_str());
        return false;
    }
    return true;
}

bool Utils::readDictionary(const std::string &path, CCDictionary *&placeholder)
{
    CCDictionary *ret = CCDictionary::createWithContentsOfFile(path.c_str());
    if (!ret) {
        CCLOG("Cannot read dictionary at path '%s'.", path.c_str());
        return false;
    }
    placeholder = ret;
    return true;
}

bool Utils::writeDictionary(CCDictionary *dictionary, const std::string &path)
{
    const bool success = dictionary->writeToFile(path.c_str());
    if (!success) {
        CCPrettyPrinter printer;
        dictionary->acceptVisitor(printer);
        CCLOG("Cannot write dictionary."
              "-------------------------------------\n"
              "Path:\n"
              "%s\n"
              "-------------------------------------\n"
              "Dictionary:\n"
              "%s\n"
              "-------------------------------------\n",
              path.c_str(),
              printer.getResult().c_str());
        return false;
    }
    return true;
}

bool Utils::compareDictionaries(CCDictionary *in, CCDictionary *out)
{
    DataEqualityChecker checker;
    if (!checker.check(in, out)) {
        std::string accessTrace;
        for (int i = 0, n = checker.trace().size(); i < n; ++i) {
            accessTrace += checker.trace()[i];
            accessTrace += ";\n";
        }
        CCLOG("Dictionaries are not equal."
              "-------------------------------------\n"
              "Input dictionary print:\n"
              "%s\n"
              "-------------------------------------\n"
              "Output dictionary print:\n"
              "%s\n"
              "-------------------------------------\n"
              "Access trace:\n"
              "%s\n"
              "-------------------------------------",
              checker.printedLHS().c_str(),
              checker.printedRHS().c_str(),
              accessTrace.c_str());
        return false;
    }
    return true;
}

bool Utils::checkFileExists(const std::string &path)
{
    if (!CCFileUtils::sharedFileUtils()->isFileExist(path)) {
        CCLOG("File not exists at path '%s'", path.c_str());
        return false;
    }
    return true;
}

bool Utils::printDictionary(const std::string &description, CCDictionary *dictionary)
{
    CCPrettyPrinter printer;
    dictionary->acceptVisitor(printer);
    CCLOG("-------------------------\n"
          "Printed %s:\n"
          "%s"
          "-------------------------\n",
          description.c_str(),
          printer.getResult().c_str());
    return true;
}

std::string Utils::getInPath(const std::string &resourceName)
{
    std::string normalizedName = resourceName;
    for (size_t i = 0, n = normalizedName.size(); i < n; ++i)
        if (normalizedName[i] == '/')
            normalizedName[i] = '_';
    return CCFileUtils::sharedFileUtils()->getWritablePath() + normalizedName + ".in";
}

std::string Utils::getOutPath(const std::string &resourceName)
{
    std::string normalizedName = resourceName;
    for (size_t i = 0, n = normalizedName.size(); i < n; ++i)
        if (normalizedName[i] == '/')
            normalizedName[i] = '_';
    return CCFileUtils::sharedFileUtils()->getWritablePath() + normalizedName + ".out";
}
