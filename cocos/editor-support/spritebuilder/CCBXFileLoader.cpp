#include "CCBXFileLoader.h"
#include "2d/CCLayer.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_CCBFILE("ccbFile");
static const std::string PROPERTY_ANIMATION("animation");
    
FileLoader *FileLoader::create()
{
    FileLoader *ret = new FileLoader();
    ret->autorelease();
    return ret;
}

Node *FileLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    if(!_file)
        return nullptr;
    
    Node *ret = _file->createNode(parentSize, mainScale, additionalScale, owner, nullptr, nullptr, rootOwner);
    return ret;
}

FileLoader::FileLoader()
    :_file(nullptr)
    ,_sequenceId(-2)
{
    
}
    
FileLoader::~FileLoader()
{
    CC_SAFE_RELEASE(_file);
}
    
void FileLoader::onHandlePropTypeCCBFile(const std::string &propertyName, bool isExtraProp, NodeLoader *value)
{
    if(propertyName == PROPERTY_CCBFILE) {
        _file = value;
        CC_SAFE_RETAIN(_file);
    } else {
        NodeLoader::onHandlePropTypeCCBFile(propertyName, isExtraProp, value);
    }
}

void FileLoader::onHandlePropTypeAnimation(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_ANIMATION) {
        _sequenceId = value;
    } else {
        NodeLoader::onHandlePropTypeAnimation(propertyName, isExtraProp, value);
    }
}
    
void FileLoader::onLoaded()
{
    switch (_sequenceId) {
        case -2:
            break;
        default:
            if(_file)
                _file->setAutoPlaySequenceId(_sequenceId);
            break;
    }
}

}

NS_CC_END