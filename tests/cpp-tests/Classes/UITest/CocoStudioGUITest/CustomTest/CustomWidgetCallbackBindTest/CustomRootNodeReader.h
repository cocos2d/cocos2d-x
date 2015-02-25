#ifndef __cocos2d_libs__CustomRootNodeReader__
#define __cocos2d_libs__CustomRootNodeReader__

#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"


class CustomRootNodeReader : public cocostudio::NodeReader
{        
public:
    CustomRootNodeReader() {};
    ~CustomRootNodeReader() {};    

    static CustomRootNodeReader* getInstance();
    static void purge();
        
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* defined(__cocos2d_libs__CustomRootNodeReader__) */