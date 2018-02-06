/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "editor-support/cocostudio/WidgetReader/ArmatureNodeReader/ArmatureNodeReader.h"

#include "platform/CCFileUtils.h"
#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"
#include "editor-support/cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "editor-support/cocostudio/CSParseBinary_generated.h"
#include "editor-support/cocostudio/WidgetReader/ArmatureNodeReader/CSArmatureNode_generated.h"
#include "editor-support/cocostudio/CCArmature.h"


USING_NS_CC;
using namespace cocostudio;
using namespace flatbuffers;

IMPLEMENT_CLASS_NODE_READER_INFO(ArmatureNodeReader)

ArmatureNodeReader::ArmatureNodeReader()
{

}

ArmatureNodeReader::~ArmatureNodeReader()
{

}

static ArmatureNodeReader* _instanceArmatureNodeReader = nullptr;

ArmatureNodeReader* ArmatureNodeReader::getInstance()
{
	if (_instanceArmatureNodeReader == nullptr)
	{
		_instanceArmatureNodeReader = new (std::nothrow) ArmatureNodeReader();
	}
	return _instanceArmatureNodeReader;
}

void ArmatureNodeReader::destroyInstance()
{
    CC_SAFE_DELETE(_instanceArmatureNodeReader);
}

Offset<Table> ArmatureNodeReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
	flatbuffers::FlatBufferBuilder *builder)
{

	auto temp = NodeReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
	auto nodeOptions = *(Offset<WidgetOptions>*)(&temp);

	bool isloop = false;
	bool isAutoPlay = false;
	std::string currentAnimationName = "";

	int type = 0;
	std::string path = "";

	const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
	while (attribute)
	{
		std::string attriname = attribute->Name();
		std::string value = attribute->Value();

		if (attriname == "IsLoop")
		{
			isloop = (value == "True") ? true : false;
		}
		else if (attriname == "IsAutoPlay")
		{
			isAutoPlay = (value == "True") ? true : false;
		}		
		else if (attriname == "CurrentAnimationName")
		{
			currentAnimationName = value;			
		}

		attribute = attribute->Next();
	}

	const tinyxml2::XMLElement* child = objectData->FirstChildElement();
	while (child)
	{
		std::string attriname = child->Name();		
		if (attriname == "FileData")
		{
			attribute = child->FirstAttribute();

			while (attribute)
			{
				attriname = attribute->Name();
				std::string value = attribute->Value();

				if (attriname == "Type")
				{
					type = 0;					
				}
				else if (attriname == "Path")
				{
					path = value;					
				}

				attribute = attribute->Next();
			}
		}		

		child = child->NextSiblingElement();
	}

	auto options = CreateCSArmatureNodeOption(*builder,
		nodeOptions,
		CreateResourceItemData(*builder,
		type,
		builder->CreateString(path)),
		isloop,
		isAutoPlay,
		builder->CreateString(currentAnimationName));

	return *(Offset<Table>*)(&options);
}

void ArmatureNodeReader::setPropsWithFlatBuffers(cocos2d::Node *node,
	const flatbuffers::Table *nodeOptions)
{

	auto* custom = static_cast<Armature*>(node);
	auto options = (flatbuffers::CSArmatureNodeOption*)nodeOptions;
    
    bool fileExist = false;
    std::string errorFilePath = "";

	std::string filepath(options->fileData()->path()->c_str());    
    
    if (FileUtils::getInstance()->isFileExist(filepath))
    {
        fileExist = true;
        
        std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filepath);
        
        std::string dirpath = fullpath.substr(0, fullpath.find_last_of("/"));
        FileUtils::getInstance()->addSearchPath(dirpath);
        
        ArmatureDataManager::getInstance()->addArmatureFileInfo(fullpath);
        custom->init(getArmatureName(filepath));
        std::string currentname = options->currentAnimationName()->c_str();
        if (options->isAutoPlay())
            custom->getAnimation()->play(currentname, -1, options->isLoop());
        else
        {
            custom->getAnimation()->play(currentname);
            custom->getAnimation()->gotoAndPause(0);
        }
    }
    else
    {
        errorFilePath = filepath;
        fileExist = false;
    }
}

cocos2d::Node*  ArmatureNodeReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	auto node = Armature::create();

	// self
	auto options = (flatbuffers::CSArmatureNodeOption*)nodeOptions;
	setPropsWithFlatBuffers(node, (Table*)options);

	// super node
	auto NodeReader = NodeReader::getInstance();
	NodeReader->setPropsWithFlatBuffers(node, (Table*)options->nodeOptions());

	return node;
}



std::string ArmatureNodeReader::getArmatureName(const std::string& exporJsonPath)
{
	//FileUtils.getFileData(exporJsonPath, "r", size)   // need read armature name in exportJsonPath
	size_t end = exporJsonPath.find_last_of(".");
	size_t start = exporJsonPath.find_last_of("\\") + 1;
	size_t start1 = exporJsonPath.find_last_of("/") + 1;
	if (start < start1)
		start = start1;

	if (start == -1)
		start = 0;
	return  exporJsonPath.substr(start, end - start);
}