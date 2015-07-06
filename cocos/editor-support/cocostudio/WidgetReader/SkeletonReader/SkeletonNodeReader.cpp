#include "tinyxml2/tinyxml2.h"
#include "flatbuffers/flatbuffers.h"
#include "cocostudio/WidgetReader/SkeletonReader/CSBoneBinary_generated.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/WidgetReader/SkeletonReader/SkeletonNodeReader.h"
#include "cocostudio/ActionTimeline/CCSkeletonNode.h"

USING_NS_CC;
USING_NS_TIMELINE;
using namespace cocostudio;
using namespace flatbuffers;

IMPLEMENT_CLASS_NODE_READER_INFO(SkeletonNodeReader)

SkeletonNodeReader::SkeletonNodeReader()
{

}

SkeletonNodeReader::~SkeletonNodeReader()
{

}

static SkeletonNodeReader* _instanceSkeletonNodeReader = nullptr;

SkeletonNodeReader* SkeletonNodeReader::getInstance()
{
    if (_instanceSkeletonNodeReader == nullptr)
    {
        _instanceSkeletonNodeReader = new (std::nothrow) SkeletonNodeReader();
    }
    return _instanceSkeletonNodeReader;
}

void SkeletonNodeReader::destroyInstance()
{
    CC_SAFE_DELETE(_instanceSkeletonNodeReader);
}

cocos2d::Node*  SkeletonNodeReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
    auto bone = SkeletonNode::create();

    // self options
    auto options = (flatbuffers::BoneOptions*)nodeOptions;
    setPropsWithFlatBuffers(bone, (Table*)options);

    // super options (node)
    auto nodeReader = NodeReader::getInstance();
    nodeReader->setPropsWithFlatBuffers(bone, (Table*)options->nodeOptions());

    return bone;
}
