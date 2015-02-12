#include "Sprite3DReader.h"

#include "CSSprite3D_generated.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "cocostudio/FlatBuffersSerialize.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"


USING_NS_CC;
using namespace ui;
using namespace flatbuffers;

namespace cocostudio
{

	IMPLEMENT_CLASS_NODE_READER_INFO(Sprite3DReader)
	static Sprite3DReader* instanceSprite3DReader = nullptr;

	Sprite3DReader::Sprite3DReader()
	{
	}


	Sprite3DReader::~Sprite3DReader()
	{
	}

	Sprite3DReader* Sprite3DReader::getInstance()
	{
		if (!instanceSprite3DReader)
		{
			instanceSprite3DReader = new (std::nothrow) Sprite3DReader();
		}
		return instanceSprite3DReader;
	}

	void Sprite3DReader::purge()
	{
		CC_SAFE_DELETE(instanceSprite3DReader);
	}

	cocos2d::Node* Sprite3DReader::createNodeWithFlatBuffers(const flatbuffers::Table *sprite3dOptions)
	{
		Sprite3D* sprite3d = nullptr;

		auto options = (Sprite3DOptions*)sprite3dOptions;
		auto fileNameData = options->fileNameData();

		bool isRunAction3D = options->runAction3DState() != 0;
		bool fileExist = false;
		std::string errorFilePath = "";
		std::string path = fileNameData->path()->c_str();
		int resourceType = fileNameData->resourceType();
		switch (resourceType)
		{
		case 0:
		{
			if (FileUtils::getInstance()->isFileExist(path))
			{
				fileExist = true;
			}
			else
			{
				errorFilePath = path;
				fileExist = false;
			}
			break;
		}

		default:
			break;
		}
		if (fileExist)
		{
			sprite3d = Sprite3D::create(path);
			if (sprite3d)
			{
				animation = Animation3D::create(path);
				if (isRunAction3D)
				{
					Animate3D* animate = Animate3D::create(animation);
					Action* sprite3dAction = RepeatForever::create(animate);
					sprite3d->runAction(sprite3dAction);
				}
				else
				{
					sprite3d->stopAllActions();
				}
				setPropsWithFlatBuffers(sprite3d, (Table*)sprite3dOptions);

			}
		}
		else
		{
			Node* node = Node::create();
			setPropsWithFlatBuffers(node, (Table*)sprite3dOptions);
			auto label = Label::create();
			label->setString(__String::createWithFormat("%s missed", errorFilePath.c_str())->getCString());
			node->addChild(label);
			return node;
		}

		return sprite3d;
	}

	void Sprite3DReader::setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* sprite3dOptions)
	{
		auto options = (Sprite3DOptions*)sprite3dOptions;
	
		auto nodeReader = NodeReader::getInstance();
		nodeReader->setPropsWithFlatBuffers(node, (Table*)(options->nodeOptions()));

	}

	Offset<Table> Sprite3DReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData, flatbuffers::FlatBufferBuilder *builder)
	{
		auto temp = NodeReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
		auto nodeOptions = *(Offset<WidgetOptions>*)(&temp);

		bool isRunAction3D = false;
		std::string fileResourcePath = "";
		std::string fileResourcePlistFile = "";
		int fileResourceType = 0;

		// attributes
		const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
		while (attribute)
		{
			std::string name = attribute->Name();
			std::string value = attribute->Value();
			if (name == "RunAction3D")
			{
				isRunAction3D = (value == "True") ? true : false;
			}
			attribute = attribute->Next();
		}

		// child elements
		const tinyxml2::XMLElement* child = objectData->FirstChildElement();
		while (child)
		{
			std::string name = child->Name();
			if (name == "FileData")
			{
				attribute = child->FirstAttribute();

				while (attribute)
				{
					name = attribute->Name();
					std::string value = attribute->Value();

					if (name == "Path")
					{
						fileResourcePath = value;
					}
					else if (name == "Type")
					{
						fileResourceType = getResourceType(value);
					}

					attribute = attribute->Next();
				}
			}
			child = child->NextSiblingElement();
		}

		auto options = CreateSprite3DOptions(*builder,
			nodeOptions,
			CreateResourceData(*builder,
			builder->CreateString(fileResourcePath),
			builder->CreateString(fileResourcePlistFile),
			fileResourceType),
			isRunAction3D
			);

		return *(Offset<Table>*)(&options);

	}

	int Sprite3DReader::getResourceType(std::string key)
	{
		if (key == "Normal" || key == "Default")
		{
			return 	0;
		}

		FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
		if (fbs->_isSimulator)
		{
			if (key == "MarkedSubImage")
			{
				return 0;
			}
		}
		return 1;
	}
}
