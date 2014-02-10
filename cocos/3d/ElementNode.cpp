#include "ElementNode.h"
#include "Stream.h"
#include "C3DQuaternion.h"
#include "C3DMatrix.h"
#include "Vector2.h"
#include "Stream.h"

namespace cocos2d
{

	void skipWhiteSpace(Stream* stream);
	char* trimWhiteSpace(char* str);


	void skipWhiteSpace(Stream* stream)
	{
		char c;

		do
		{
			stream->read(&c);
		} while (isspace(c) && c!=EOF);

		// If we are not at the end of the file, then since we found a
		// non-whitespace character, we put the cursor back in front of it.
		if (c != EOF)
		{
			if (stream->seek(-1, SEEK_CUR) == false)
			{
				CCAssert(0, "Failed to seek backwards one character after skipping whitespace.");
			}
		}       
	}

	char* trimWhiteSpace(char *str)
	{
		if (str == nullptr)
		{
			return str;
		}

		char *end;

		// Trim leading space.
		while (isspace(*str))
			str++;

		// All spaces?
		if (*str == 0)  
		{
			return str;
		}

		// Trim trailing space.
		end = str + strlen(str) - 1;
		while (end > str && isspace(*end))
			end--;

		// Write new null terminator.
		*(end+1) = 0;

		return str;
	}

	ElementNode::ElementNode()
	{
	}


	ElementNode::ElementNode(Stream* stream)
	{
		read(stream);
		rewind();
	}

	ElementNode::ElementNode(Stream* stream, const char* name, const char* id) : _nodeType(name)
	{
		if (id)
		{
			_nodeName = id;
		}

		read(stream);
		rewind();
	}


	void ElementNode::readContents(Stream* stream, char* name, char* id)
	{
		if (name)
		{
			_nodeType = name;
		}

		if (id)
		{
			_nodeName = id;
		}

		char line[2048];
		char c;   
		char* value;   
		char* rc;    

		while (true)
		{
			skipWhiteSpace(stream);

			// Stop when we have reached the end of the file.
			if (stream->eof())
				break;

			// Read the next line.
			rc = stream->readLine(2048,line);
			if (rc == nullptr)
			{
				//delete line;
				CCAssert(0, "Error reading line from file.");
				return;
			}

			if (strncmp(line, "//", 2) == 0) // Ignore comment, skip line.
			{
				//delete line;
				continue;
			}


			// If an '=' appears on this line, parse it as a name/value pair.
			// Note: strchr() has to be called before strtok(), or a backup of line has to be kept.
			rc = strchr(line, '=');
			if (rc != nullptr)
			{
				// There could be a '}' at the end of the line, ending a namespace.
				rc = strchr(line, '}');

				// First token should be the property name.
				name = strtok(line, " =\t");
				if (name == nullptr)
				{
					//delete line;
					CCLOG("Error parsing properties file: value without name.");
					return;
				}

				// Scan for next token, the property's value.
				value = strtok(nullptr, "=");
				if (value == nullptr)
				{
					//delete line;
					CCLOG("Error parsing properties file: name without value.");
				}

				// Remove white-space from value.
				value = trimWhiteSpace(value);

				// Store name/value pair.
				_elements.push_back(KeyValue(name, value));

				if (rc != nullptr)
				{
					//delete line;
					// End of namespace.
					return;
				}
			}
			else
			{           

				// This line might begin or end a namespace,
				// or it might be a key/value pair without '='.

				// Check for '{' on same line.
				rc = strchr(line, '{');


				// Get the name of the namespace.
				name = strtok(line, " \t\n{");
				name = trimWhiteSpace(name);
				if (name == nullptr)
				{
					//delete line;
					CCLOG("Error parsing properties file: unknown error.");
				}
				else if (name[0] == '}')
				{
					//delete line;
					// End of namespace.
					return;
				}

				// Get its ID if it has one.
				value = strtok(nullptr, "{");
				value = trimWhiteSpace(value);


				if (value != nullptr && value[0] == '{')
				{
					// New namespace without an ID.
					ElementNode* space = new ElementNode(stream, name, nullptr);
					_childs.push_back(space);
				}
				else
				{
					// If '{' appears on the same line.
					if (rc != nullptr)
					{
						// Create new namespace.
						ElementNode* space = new ElementNode(stream, name, value);
						_childs.push_back(space);
					}
					else
					{
						// Find out if the next line starts with "{"
						skipWhiteSpace(stream);
						stream->read(&c);
						//  c = readChar(stream);

						if (c == '{')
						{
							// Create new namespace.
							ElementNode* space = new ElementNode(stream, name, value);
							_childs.push_back(space);
						}
						else
						{
							// Back up from fgetc()                      
							if(stream->seek(-1,SEEK_CUR) == false)
							{
								//delete line;
								CCAssert(0, "Failed to seek backwards a single character");

								return;
							}

							// Store "name value" as a name/value pair, or even just "name".
							if (value != nullptr)
							{
								_elements.push_back(KeyValue(name, value));
							}
							else
							{
								_elements.push_back(KeyValue(name, std::string()));
							}
						}
					}
				}
			}    
		}
		rewind();
		//delete line;
	}


	ElementNode* ElementNode::create(const char* fileName)
	{
		assert(fileName);

		if (!fileName || strlen(fileName) == 0)
		{
			CCAssert(0, "Attempting to create a Properties object from an empty URL!");
			return nullptr;
		}  


		Stream* stream = StreamManager::openStream(fileName, "rb");
		if (!stream)
		{
			CCAssert(0, "Failed to open file");
			return nullptr;
		}

		ElementNode* properties = new ElementNode(stream);

		CC_SAFE_DELETE(stream);
		return properties;
	}

	void ElementNode::readFlag(Stream* stream)
	{
		char line[2048];

		char* name;
		char* value;   
		char* rc;    

		while (true)
		{
			skipWhiteSpace(stream);

			// Stop when we have reached the end of the file.
			if (stream->eof())
				break;

			// Read the next line.    

			rc = stream->readLine(2048,line);
			if (rc == nullptr)
			{
				//delete line;
				CCLOG("Error reading line from file.");
				return;
			}

			if (strncmp(line, "//", 2) == 0) // Ignore comment, skip line.
			{
				//delete line;
				continue;
			}


			// If an '=' appears on this line, parse it as a name/value pair.
			// Note: strchr() has to be called before strtok(), or a backup of line has to be kept.
			rc = strchr(line, '=');
			if (rc != nullptr)
			{
				// There could be a '}' at the end of the line, ending a namespace.
				rc = strchr(line, '>');

				// First token should be the property name.
				name = strtok(line, " =\t");
				if (name == nullptr)
				{
					//delete line;
					CCLOG("Error parsing properties file: value without name.");
					return;
				}

				// Scan for next token, the property's value.
				value = strtok(nullptr, "=");
				if (value == nullptr)
				{
					//delete line;
					CCLOG("Error parsing properties file: name without value.");
					return;
				}

				// Remove white-space from value.
				value = trimWhiteSpace(value);

				// Store name/value pair.
				_flags.push_back(KeyValue(name, value));

				if (rc != nullptr)
				{
					//delete line;
					// End of namespace.
					return;
				}
			}
			else
			{           

				// This line might begin or end a namespace,
				// or it might be a key/value pair without '='.

				// Check for '{' on same line.
				rc = strchr(line, '<');


				// Get the name of the namespace.
				name = strtok(line, " \t\n<");
				name = trimWhiteSpace(name);
				if (name == nullptr)
				{
					//delete line;
					CCLOG("Error parsing properties file: unknown error.");
					return;
				}
				else if (name[0] == '>')
				{
					//delete line;
					// End of namespace.
					return;
				}          


			}    
		}
		//delete line;

	}

	void ElementNode::read(Stream* stream)
	{
		char line[2048];
		char c;
		char* name;
		char* value;   
		char* rc;    

		while (true)
		{
			skipWhiteSpace(stream);

			// Stop when we have reached the end of the file.
			if (stream->eof())
			{

				//CC_SAFE_DELETE_ARRAY(line);
				break;
			}

			// Read the next line.
			rc = stream->readLine(2048,line);    
			if (rc == nullptr)
			{
				//CC_SAFE_DELETE_ARRAY(line);
				CCLOG("Error reading line from file.");
				return;
			}

			if (strncmp(line, "//", 2) == 0) // Ignore comment, skip line.
			{
				//CC_SAFE_DELETE_ARRAY(line);
				continue;
			}


			// If an '=' appears on this line, parse it as a name/value pair.
			// Note: strchr() has to be called before strtok(), or a backup of line has to be kept.
			rc = strchr(line, '=');
			if (rc != nullptr)
			{
				// There could be a '}' at the end of the line, ending a namespace.
				rc = strchr(line, '}');

				// First token should be the property name.
				name = strtok(line, " =\t");
				if (name == nullptr)
				{
					//CC_SAFE_DELETE_ARRAY(line);
					CCLOG("Error parsing properties file: value without name.");
					return;
				}

				// Scan for next token, the property's value.
				value = strtok(nullptr, "=");
				if (value == nullptr)
				{
					//CC_SAFE_DELETE_ARRAY(line);
					CCLOG("Error parsing properties file: name without value.");
					return;
				}

				// Remove white-space from value.
				value = trimWhiteSpace(value);

				// Store name/value pair.
				_elements.push_back(KeyValue(name, value));

				if (rc != nullptr)
				{
					//CC_SAFE_DELETE_ARRAY(line);
					// End of namespace.
					return;
				}
			}
			else
			{           

				// This line might begin or end a namespace,
				// or it might be a key/value pair without '='.

				// Check for '{' on same line.
				rc = strchr(line, '{');


				// Get the name of the namespace.
				name = strtok(line, " \t\n{");
				name = trimWhiteSpace(name);
				if (name == nullptr)
				{
					//CC_SAFE_DELETE_ARRAY(line);
					CCLOG("Error parsing properties file: unknown error.");
					return;
				}
				else if (name[0] == '}')
				{
					//CC_SAFE_DELETE_ARRAY(line);
					// End of namespace.
					return;
				}

				// Get its ID if it has one.
				value = strtok(nullptr, "{");
				value = trimWhiteSpace(value);


				if (value != nullptr && value[0] == '{')
				{
					// New namespace without an ID.
					ElementNode* space = new ElementNode(stream, name, nullptr);
					_childs.push_back(space);
				}
				else
				{
					// If '{' appears on the same line.
					if (rc != nullptr)
					{
						// Create new namespace.
						ElementNode* space = new ElementNode(stream, name, value);
						_childs.push_back(space);
					}
					else
					{
						// Find out if the next line starts with "{"
						skipWhiteSpace(stream);
						stream->read(&c);

						if(c == '<')
						{
							//read <.....>                        // Create new namespace.
							ElementNode* space = new ElementNode();
							space->readFlag(stream);

							skipWhiteSpace(stream);

							stream->read(&c);
							space->readContents(stream, name, value);

							_childs.push_back(space);
						}
						else if (c == '{')
						{
							// Create new namespace.
							ElementNode* space = new ElementNode(stream, name, value);
							_childs.push_back(space);
						}
						else
						{
							// Back up from fgetc()
							// Back up from fgetc()
							if (stream->seek(-1, SEEK_CUR) == false)
							{
								//CC_SAFE_DELETE_ARRAY(line);
								CCLOG("Failed to seek backwards a single character after testing if the next line starts with '{'.");
								return;
							}
							// Store "name value" as a name/value pair, or even just "name".
							if (value != nullptr)
							{
								_elements.push_back(KeyValue(name, value));
							}
							else
							{
								_elements.push_back(KeyValue(name, std::string()));
							}
						}
					}
				}
			}    
		}

		//CC_SAFE_DELETE_ARRAY(line);
	}

	void ElementNode::empty()
	{
		_elements.clear();
		for (size_t i = 0; i < _childs.size(); i++)
		{
			CC_SAFE_DELETE(_childs[i]);
		}
		_childs.clear();
	}

	ElementNode::~ElementNode()
	{
		unsigned int count = _childs.size();
		for (unsigned int i = 0; i < count; i++)
		{
			CC_SAFE_DELETE(_childs[i]);
		}
	}

	const char* ElementNode::getNextElement(char** value)
	{
		if (_elementsItr == _elements.end())
		{
			// Restart from the beginning
			_elementsItr = _elements.begin();
		}
		else
		{
			// Move to the next property
			_elementsItr++;
		}

		if (_elementsItr != _elements.end())
		{
			const std::string& name = _elementsItr->key;
			if (!name.empty())
			{
				if (value)
				{
					strcpy(*value, _elementsItr->value.c_str());
				}
				return name.c_str();
			}
		}

		return nullptr;
	}

	ElementNode* ElementNode::getNextChild()
	{
		if (_childsItr == _childs.end())
		{
			// Restart from the beginning
			_childsItr = _childs.begin();
		}
		else
		{
			_childsItr++;
		}

		if (_childsItr != _childs.end())
		{
			ElementNode* ns = *_childsItr;
			return ns;
		}

		return nullptr;
	}

	void ElementNode::rewind()
	{
		_elementsItr = _elements.end();
		_childsItr = _childs.end();

		_flagsItr = _flags.end();
	}

	ElementNode* ElementNode::getChild(const char* chileName) const
	{
		ElementNode* ret = nullptr;
		std::vector<ElementNode*>::const_iterator it;

		for (it = _childs.begin(); it < _childs.end(); it++)
		{
			ret = *it;
			if (strcmp(ret->_nodeName.c_str(), chileName) == 0)
			{
				return ret;
			}

			// Search recursively.
			ret = ret->getChild(chileName);
			if (ret != nullptr)
			{
				return ret;
			}
		}

		return ret;
	}

	const char* ElementNode::getNodeType() const
	{
		return _nodeType.c_str();
	}

	const char* ElementNode::getNodeName() const
	{
		return _nodeName.c_str();
	}


	const bool isStringNumeric(const char* str)
	{
		// The first character may be '-'
		if (*str == '-')
			str++;

		// The first character after the sign must be a digit
		if (!isdigit(*str))
			return false;
		str++;

		// All remaining characters must be digits, with a single decimal (.) permitted
		unsigned int decimalCount = 0;
		while (*str)
		{
			if (!isdigit(*str))
			{
				if (*str == '.' && decimalCount == 0)
				{
					// Max of 1 decimal allowed
					decimalCount++;
				}
				else
				{
					return false;
				}
			}
			str++;
		}
		return true;
	}

	ElementNode::ElementType ElementNode::getElementType(const char* elementName) const
	{
		const char* value = getElement(elementName);
		if (!value)
		{
			return ElementNode::NONE;
		}

		// Parse the value to determine the format
		unsigned int commaCount = 1;
		//unsigned int length = strlen(value);
		char* valuePtr = const_cast<char*>(value);
		while (valuePtr = strchr(valuePtr, ','))
		{
			valuePtr++;
			commaCount++;
		}

		switch (commaCount)
		{
		case 1:
			return isStringNumeric(value) ? ElementNode::NUMBER : ElementNode::STRING;
		case 2:
			return ElementNode::VECTOR2;
		case 3:
			return ElementNode::VECTOR3;
		case 4:
			return ElementNode::VECTOR4;
		case 16:
			return ElementNode::MATRIX;
		default:
			return ElementNode::STRING;
		}
	}

	const char* ElementNode::getElement(const char* name) const
	{
		if (name)
		{
			for (size_t i = 0; i < _elements.size(); ++i)
			{
				if (_elements[i].key == name)
				{
					return _elements[i].value.c_str();
				}
			}
		}
		else
		{
			if (_elementsItr != _elements.end())
			{
				return _elementsItr->value.c_str();
			}
		}

		return nullptr;
	}

	const char* ElementNode::getElementFlag(const char* flagName)
	{
		if (flagName)
		{
			for (size_t i = 0; i < _flags.size(); ++i)
			{
				if (_flags[i].key == flagName)
					return _flags[i].value.c_str();
			}
		}
		else
		{
			if (_flagsItr != _flags.end())
			{
				return _flagsItr->value.c_str();
			}
		}

		return nullptr;
	}

	ElementNode* ElementNode::createEmptyNode(const char* name, const char* nodetype)
	{
		ElementNode* node = new ElementNode();
		node->_nodeName = name;
		node->_nodeType = nodetype;
		return node;
	}

	void ElementNode::addChildNode(ElementNode* child)
	{
		_childs.push_back(child);
	}

	void ElementNode::delChildNode(const char* name, const char* nodetype)
	{
		std::vector<ElementNode*>::iterator iter = _childs.begin();
		for (; iter != _childs.end(); iter++)
		{
			if (strcmp((*iter)->getNodeName(), name) == 0 && strcmp((*iter)->getNodeType(), nodetype ) == 0)
			{
				CC_SAFE_DELETE((*iter));
				_childs.erase(iter);
				break;
			}
		}
	}

	/*
	bool ElementNode::getElement(const char* name, bool* out) const
	{
	const char* valueString = getElement(name);
	if (valueString)
	{
	return (strcmp(valueString, "true") == 0);
	}

	return false;
	}

	int ElementNode::getElement(const char* name, int* out) const
	{
	const char* valueString = getElement(name);
	if (valueString)
	{
	int value;
	int scanned;
	scanned = sscanf(valueString, "%d", &value);
	if (scanned != 1)
	{
	CCLOG("Error parsing property: %s", name);
	return 0;
	}
	return value;
	}

	return 0;
	}

	long ElementNode::getElement(const char* name, long* out) const
	{
	const char* valueString = getElement(name);
	if (valueString)
	{
	int value;
	int scanned;
	scanned = sscanf(valueString, "%ld", &value);
	if (scanned != 1)
	{
	CCLOG("Error parsing property: %s", name);
	return 0;
	}
	return value;
	}

	return 0;
	}

	float ElementNode::getElement(const char* name, float* out) const
	{
	const char* valueString = getElement(name);
	if (valueString)
	{
	float value;
	int scanned;
	scanned = sscanf(valueString, "%f", &value);
	if (scanned != 1)
	{
	CCLOG("Error parsing property: %s", name);
	return 0.0f;
	}
	return value;
	}

	return 0.0f;
	}


	bool ElementNode::getElement(const char* name, Matrix* out) const
	{
	assert(out);

	const char* valueString = getElement(name);
	if (valueString)
	{
	float m[16];
	int scanned;
	scanned = sscanf(valueString, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
	&m[0], &m[1], &m[2], &m[3], &m[4], &m[5], &m[6], &m[7],
	&m[8], &m[9], &m[10], &m[11], &m[12], &m[13], &m[14], &m[15]);

	if (scanned != 16)
	{
	CCLOG("Error parsing property: %s", name);
	out->setIdentity();
	return false;
	}

	out->set(m);
	return true;
	}

	out->setIdentity();
	return false;
	}

	bool ElementNode::getElement(const char* name, Vector2* out) const
	{
	assert(out);

	const char* valueString = getElement(name);
	if (valueString)
	{
	float x, y;
	int scanned;
	scanned = sscanf(valueString, "%f,%f", &x, &y);
	if (scanned != 2)
	{
	CCLOG("Error parsing property: %s", name);
	out->set(0.0f, 0.0f);
	return false;
	}

	out->set(x, y);
	return true;
	}

	out->set(0.0f, 0.0f);
	return false;
	}

	bool ElementNode::getElement(const char* name, Vector3* out) const
	{
	assert(out);

	const char* valueString = getElement(name);
	if (valueString)
	{
	float x, y, z;
	int scanned;
	scanned = sscanf(valueString, "%f,%f,%f", &x, &y, &z);
	if (scanned != 3)
	{
	CCLOG("Error parsing property: %s", name);
	out->set(0.0f, 0.0f, 0.0f);
	return false;
	}

	out->set(x, y, z);
	return true;
	}

	out->set(0.0f, 0.0f, 0.0f);
	return false;
	}

	bool ElementNode::getElement(const char* name, Vector4* out) const
	{
	assert(out);

	const char* valueString = getElement(name);
	if (valueString)
	{
	float x, y, z, w;
	int scanned;
	scanned = sscanf(valueString, "%f,%f,%f,%f", &x, &y, &z, &w);
	if (scanned != 4)
	{
	CCLOG("Error parsing property: %s", name);
	out->set(0.0f, 0.0f, 0.0f, 0.0f);
	return false;
	}

	out->set(x, y, z, w);
	return true;
	}

	out->set(0.0f, 0.0f, 0.0f, 0.0f);
	return false;
	}

	bool ElementNode::getElement(const char* name, Quaternion* out) const
	{
	assert(out);

	const char* valueString = getElement(name);
	if (valueString)
	{
	float x, y, z, theta;
	int scanned;
	scanned = sscanf(valueString, "%f,%f,%f,%f", &x, &y, &z, &theta);
	if (scanned != 4)
	{
	CCLOG("Error parsing property: %s", name);
	out->set(0.0f, 0.0f, 0.0f, 1.0f);
	return false;
	}

	out->set(Vector3(x, y, z), MATH_DEG_TO_RAD(theta));
	return true;
	}

	out->set(0.0f, 0.0f, 0.0f, 1.0f);
	return false;
	}
	*/

	bool ElementNode::writeToFile(const char* fileName)
	{

		assert(fileName);

		if (!fileName || strlen(fileName) == 0)
		{
			CCAssert(0, "Attempting to write a Properties object to an empty URL!");
			return false;
		}


		Stream* stream = StreamManager::openStream(fileName, "wb", StreamManager::StreamType_File);
		if (!stream)
		{
			CCAssert(0, "Failed to open file");
			return false;
		}

		write(stream, "");

		CC_SAFE_DELETE(stream);


		return true;

	}

	void ElementNode::write(Stream* stream, const std::string& indent)
	{

		assert(stream);

		std::string nextIdent = indent;
		if (!_nodeType.empty())
		{
			nextIdent += "\t";
			// write header
			stream->write(indent + _nodeType + " " + _nodeName + "\n");

			// write flags
			if (!_flags.empty())
			{
				stream->write(indent + "<\n");
				for (size_t i = 0; i < _flags.size(); ++i)
				{
					stream->write(nextIdent + _flags[i].key + " = " + _flags[i].value + "\n");
				}
				stream->write(indent + ">\n");
			}

			// write elements
			stream->write(indent + "{\n");
			for (size_t i = 0; i < _elements.size(); ++i)
			{
				stream->write(nextIdent + _elements[i].key + " = " + _elements[i].value + "\n");
			}

			if (!_childs.empty())
				stream->write("\n");
		}

		// write children
		for (size_t i = 0; i < _childs.size(); ++i)
		{
			_childs[i]->write(stream, nextIdent);
		}

		if (!_nodeType.empty())
		{
			stream->write(indent + "}\n\n");
		}
	}

	void ElementNode::setElementFlag(const char* flagName, const char* flag)
	{
		for (size_t i = 0; i < _flags.size(); i++)
		{
			if (_flags[i].key == flagName)
			{
				_flags[i].value = flag;
				return;
			}
		}

		KeyValue kv(flagName, flag);
		_flags.push_back(kv);
	}

	int ElementNode::getElementCount() const
	{
		return (int)_elements.size();
	}


}