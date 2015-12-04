#ifndef _CCBX_FILELOADERLOADER_H_
#define _CCBX_FILELOADERLOADER_H_

#include "CCBXNodeLoader.h"

NS_CC_BEGIN
namespace spritebuilder {

class CC_DLL FileLoader : public NodeLoader {
public:
    static FileLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    
CC_CONSTRUCTOR_ACCESS:
    FileLoader();
    ~FileLoader();

protected:
    virtual void onHandlePropTypeCCBFile(const std::string &propertyName, bool isExtraProp, NodeLoader *value) override;
    virtual void onHandlePropTypeAnimation(const std::string &propertyName, bool isExtraProp, int value) override;
    
private:
    NodeLoader *_file;
    int _sequenceId;
};

}

NS_CC_END

#endif
