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

Node *FileLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    if(!_file)
        return nullptr;
    
    Node *ret = _file->createNode(parentSize, mainScale, additionalScale, owner, nullptr, nullptr, rootOwner, nullptr, nullptr, true);
    return ret;
}

FileLoader::FileLoader()
    :_file(nullptr)
    ,_sequenceId(-2)
{
    
}
    
FileLoader::~FileLoader()
{
}
    
void FileLoader::onHandlePropTypeCCBFile(const std::string &propertyName, bool isExtraProp, const std::pair<std::string, NodeLoader*> &value)
{
    if(propertyName == PROPERTY_CCBFILE) {
        _filePath = value.first;
        _file = value.second;
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
    
class FileLoaderHackAcces : public NodeLoader
{
public:
    void callOnNodeLoaded(Node *node) const {
        onNodeLoaded(node);
    }
};
    
void FileLoader::onNodeLoaded(Node *node) const
{
    CCBAnimationManager *manager = CCBAnimationManager::fromNode(node);
    if(manager)
    {
        switch (_sequenceId) {
            case -2:
                manager->runAnimationsForSequenceIdTweenDuration(manager->getAutoPlaySequenceId(), 0.0f);
                break;
                
            case -1:
                break;
                
            default:
                manager->runAnimationsForSequenceIdTweenDuration(_sequenceId, 0.0f);
                break;
        }
    }
    static_cast<FileLoaderHackAcces*>(_file.get())->callOnNodeLoaded(node);
    NodeLoader::onNodeLoaded(node);
}

}

NS_CC_END
