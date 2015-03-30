/****************************************************************************
Copyright (c) 2014 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

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
		flatbuffers::FlatBufferBuilder* builder) override;
	void setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* textBMFontOptions) override;

	//CSArmatureNode
	cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions) override;
private:
	std::string getArmatureName(const std::string& exporJsonPath);
};

#endif /* defined(__ARMATURENODEREADER_H_) */
