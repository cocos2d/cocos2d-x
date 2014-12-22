

#ifndef __ARMATURENODEREADER_H_
#define __ARMATURENODEREADER_H_

#include "cocos2d.h"
#include "cocostudio/FlatBuffersSerialize.h"
#include "cocostudio/WidgetReader/NodeReaderProtocol.h"
#include "cocostudio/WidgetReader/NodeReaderDefine.h"


/****************************************
* reader of CSArmatureNode
* @param register reader before use it:
CSLoader* instance = CSLoader::getInstance();
instance->registReaderObject("ArmatureNodeReader", (ObjectFactory::Instance)CustomSpriteReader::getInstance);
*@param Reader's name must be CLASSNAME#Reader, CLASSNAME is the dataobject's prefix: CLASSNAME#ObjectData
*
*
*****************************************/
class ArmatureNodeReader : public cocos2d::Ref, public cocostudio::NodeReaderProtocol
{
	DECLARE_CLASS_NODE_READER_INFO

public:

	ArmatureNodeReader();
	~ArmatureNodeReader();

	static ArmatureNodeReader* getInstance();
	static void purge();

	flatbuffers::Offset<flatbuffers::Table> createOptionsWithFlatBuffers(const tinyxml2::XMLElement* objectData,
		flatbuffers::FlatBufferBuilder* builder);
	void setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* textBMFontOptions);

	//CSArmatureNode
	cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions) override;
private:
	std::string getArmatureName(const std::string& exporJsonPath);
};

#endif /* defined(__ARMATURENODEREADER_H_) */
