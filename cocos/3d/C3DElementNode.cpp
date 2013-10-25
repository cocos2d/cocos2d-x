#include "Base.h"
#include "C3DElementNode.h"
#include "C3DStream.h"
#include "C3DQuaternion.h"
#include "C3DMatrix.h"
#include "C3DVector2.h"
#include "C3DStream.h"

namespace cocos3d
{

void skipWhiteSpace(C3DStream* stream);
char* trimWhiteSpace(char* str);


void skipWhiteSpace(C3DStream* stream)
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
            WARN("Failed to seek backwards one character after skipping whitespace.");
        }
	}       
}

char* trimWhiteSpace(char *str)
{
    if (str == NULL)
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

C3DElementNode::C3DElementNode()
{
}


C3DElementNode::C3DElementNode(C3DStream* stream)
{
    read(stream);
    rewind();
}

C3DElementNode::C3DElementNode(C3DStream* stream, const char* name, const char* id) : _nodeType(name)
{
    if (id)
    {
        _nodeName = id;
    }

    read(stream);
    rewind();
}


void C3DElementNode::readContents(C3DStream* stream, char* name, char* id)
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
        if (rc == NULL)
        {
			//delete line;
			WARN("Error reading line from file.");
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
        if (rc != NULL)
        {
            // There could be a '}' at the end of the line, ending a namespace.
            rc = strchr(line, '}');

            // First token should be the property name.
            name = strtok(line, " =\t");
            if (name == NULL)
            {
				//delete line;
                LOG_ERROR("Error parsing properties file: value without name.");
                return;
            }

            // Scan for next token, the property's value.
            value = strtok(NULL, "=");
            if (value == NULL)
            {
				//delete line;
                LOG_ERROR("Error parsing properties file: name without value.");
            }

            // Remove white-space from value.
            value = trimWhiteSpace(value);

            // Store name/value pair.
            _elements.push_back(KeyValue(name, value));

            if (rc != NULL)
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
            if (name == NULL)
            {
				//delete line;
                LOG_ERROR("Error parsing properties file: unknown error.");
            }
            else if (name[0] == '}')
            {
				//delete line;
                // End of namespace.
                return;
            }

            // Get its ID if it has one.
            value = strtok(NULL, "{");
            value = trimWhiteSpace(value);
            

            if (value != NULL && value[0] == '{')
            {
                // New namespace without an ID.
                C3DElementNode* space = new C3DElementNode(stream, name, NULL);
                _childs.push_back(space);
            }
            else
            {
                // If '{' appears on the same line.
                if (rc != NULL)
                {
                    // Create new namespace.
                    C3DElementNode* space = new C3DElementNode(stream, name, value);
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
                        C3DElementNode* space = new C3DElementNode(stream, name, value);
                        _childs.push_back(space);
                    }
                    else
                    {
                        // Back up from fgetc()                      
						if(stream->seek(-1,SEEK_CUR) == false)
						{
							//delete line;
							WARN("Failed to seek backwards a single character");
						
							return;
						}

                        // Store "name value" as a name/value pair, or even just "name".
                        if (value != NULL)
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


C3DElementNode* C3DElementNode::create(const char* fileName)
{
    assert(fileName);

    if (!fileName || strlen(fileName) == 0)
    {
        WARN("Attempting to create a Properties object from an empty URL!");
        return NULL;
    }  
      

	C3DStream* stream = C3DStreamManager::openStream(fileName, "rb");
    if (!stream)
    {
		WARN("Failed to open file");
        return NULL;
    }

    C3DElementNode* properties = new C3DElementNode(stream);
	
    SAFE_DELETE(stream);
    return properties;
}

void C3DElementNode::readFlag(C3DStream* stream)
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
        if (rc == NULL)
        {
			//delete line;
			LOG_ERROR("Error reading line from file.");
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
        if (rc != NULL)
        {
            // There could be a '}' at the end of the line, ending a namespace.
            rc = strchr(line, '>');

            // First token should be the property name.
            name = strtok(line, " =\t");
            if (name == NULL)
            {
				//delete line;
                LOG_ERROR("Error parsing properties file: value without name.");
                return;
            }

            // Scan for next token, the property's value.
            value = strtok(NULL, "=");
            if (value == NULL)
            {
				//delete line;
                LOG_ERROR("Error parsing properties file: name without value.");
				return;
            }

            // Remove white-space from value.
            value = trimWhiteSpace(value);

            // Store name/value pair.
            _flags.push_back(KeyValue(name, value));

            if (rc != NULL)
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
            if (name == NULL)
            {
				//delete line;
                LOG_ERROR("Error parsing properties file: unknown error.");
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

void C3DElementNode::read(C3DStream* stream)
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
			
			//SAFE_DELETE_ARRAY(line);
            break;
		}

        // Read the next line.
		 rc = stream->readLine(2048,line);    
        if (rc == NULL)
        {
			//SAFE_DELETE_ARRAY(line);
			LOG_ERROR("Error reading line from file.");
            return;
        }

		if (strncmp(line, "//", 2) == 0) // Ignore comment, skip line.
		{
			//SAFE_DELETE_ARRAY(line);
			continue;
		}
        
    
        // If an '=' appears on this line, parse it as a name/value pair.
        // Note: strchr() has to be called before strtok(), or a backup of line has to be kept.
        rc = strchr(line, '=');
        if (rc != NULL)
        {
            // There could be a '}' at the end of the line, ending a namespace.
            rc = strchr(line, '}');

            // First token should be the property name.
            name = strtok(line, " =\t");
            if (name == NULL)
            {
				//SAFE_DELETE_ARRAY(line);
                LOG_ERROR("Error parsing properties file: value without name.");
                return;
            }

            // Scan for next token, the property's value.
            value = strtok(NULL, "=");
            if (value == NULL)
            {		
				//SAFE_DELETE_ARRAY(line);
                LOG_ERROR("Error parsing properties file: name without value.");
				return;
            }

            // Remove white-space from value.
            value = trimWhiteSpace(value);

            // Store name/value pair.
            _elements.push_back(KeyValue(name, value));

            if (rc != NULL)
            {
				//SAFE_DELETE_ARRAY(line);
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
            if (name == NULL)
            {
				//SAFE_DELETE_ARRAY(line);
                LOG_ERROR("Error parsing properties file: unknown error.");
				return;
            }
            else if (name[0] == '}')
            {
				//SAFE_DELETE_ARRAY(line);
                // End of namespace.
                return;
            }

            // Get its ID if it has one.
            value = strtok(NULL, "{");
            value = trimWhiteSpace(value);
            

            if (value != NULL && value[0] == '{')
            {
                // New namespace without an ID.
                C3DElementNode* space = new C3DElementNode(stream, name, NULL);
                _childs.push_back(space);
            }
            else
            {
                // If '{' appears on the same line.
                if (rc != NULL)
                {
                    // Create new namespace.
                    C3DElementNode* space = new C3DElementNode(stream, name, value);
                    _childs.push_back(space);
                }
                else
                {
                    // Find out if the next line starts with "{"
                    skipWhiteSpace(stream);
					stream->read(&c);

					if(c == '<')
					{
						//read <.....>						                        // Create new namespace.
                        C3DElementNode* space = new C3DElementNode();
						space->readFlag(stream);

						skipWhiteSpace(stream);

						stream->read(&c);
						space->readContents(stream, name, value);
						
                        _childs.push_back(space);
					}
                    else if (c == '{')
                    {
                        // Create new namespace.
                        C3DElementNode* space = new C3DElementNode(stream, name, value);
                        _childs.push_back(space);
                    }
                    else
                    {
                        // Back up from fgetc()
						// Back up from fgetc()
                        if (stream->seek(-1, SEEK_CUR) == false)
						{
							//SAFE_DELETE_ARRAY(line);
                            LOG_ERROR("Failed to seek backwards a single character after testing if the next line starts with '{'.");
							return;
						}
                        // Store "name value" as a name/value pair, or even just "name".
                        if (value != NULL)
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

	//SAFE_DELETE_ARRAY(line);
}

void C3DElementNode::empty()
{
	_elements.clear();
	for (size_t i = 0; i < _childs.size(); i++)
	{
		SAFE_DELETE(_childs[i]);
	}
	_childs.clear();
}

C3DElementNode::~C3DElementNode()
{
    unsigned int count = _childs.size();
    for (unsigned int i = 0; i < count; i++)
    {
        SAFE_DELETE(_childs[i]);
    }
}

const char* C3DElementNode::getNextElement(char** value)
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

    return NULL;
}

C3DElementNode* C3DElementNode::getNextChild()
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
        C3DElementNode* ns = *_childsItr;
        return ns;
    }

    return NULL;
}

void C3DElementNode::rewind()
{
    _elementsItr = _elements.end();
    _childsItr = _childs.end();

	_flagsItr = _flags.end();
}

C3DElementNode* C3DElementNode::getChild(const char* chileName) const
{
    C3DElementNode* ret = NULL;
    std::vector<C3DElementNode*>::const_iterator it;
    
    for (it = _childs.begin(); it < _childs.end(); it++)
    {
        ret = *it;
        if (strcmp(ret->_nodeName.c_str(), chileName) == 0)
        {
            return ret;
        }
        
        // Search recursively.
        ret = ret->getChild(chileName);
        if (ret != NULL)
        {
            return ret;
        }
    }

    return ret;
}

const char* C3DElementNode::getNodeType() const
{
    return _nodeType.c_str();
}

const char* C3DElementNode::getNodeName() const
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

C3DElementNode::ElementType C3DElementNode::getElementType(const char* elementName) const
{
    const char* value = getElement(elementName);
    if (!value)
    {
        return C3DElementNode::NONE;
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
        return isStringNumeric(value) ? C3DElementNode::NUMBER : C3DElementNode::STRING;
    case 2:
        return C3DElementNode::VECTOR2;
    case 3:
        return C3DElementNode::VECTOR3;
    case 4:
        return C3DElementNode::VECTOR4;
    case 16:
        return C3DElementNode::MATRIX;
    default:
        return C3DElementNode::STRING;
    }
}

const char* C3DElementNode::getElement(const char* name) const
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

    return NULL;
}

const char* C3DElementNode::getElementFlag(const char* flagName)
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

    return NULL;
}

C3DElementNode* C3DElementNode::createEmptyNode(const char* name, const char* nodetype)
{
	C3DElementNode* node = new C3DElementNode();
	node->_nodeName = name;
	node->_nodeType = nodetype;
	return node;
}

void C3DElementNode::addChildNode(C3DElementNode* child)
{
	_childs.push_back(child);
}

void C3DElementNode::delChildNode(const char* name, const char* nodetype)
{
	std::vector<C3DElementNode*>::iterator iter = _childs.begin();
	for (; iter != _childs.end(); iter++)
	{
		if (strcmp((*iter)->getNodeName(), name) == 0 && strcmp((*iter)->getNodeType(), nodetype ) == 0)
		{
			SAFE_DELETE((*iter));
			_childs.erase(iter);
			break;
		}
	}
}

/*
bool C3DElementNode::getElement(const char* name, bool* out) const
{
    const char* valueString = getElement(name);
    if (valueString)
    {
        return (strcmp(valueString, "true") == 0);
    }

    return false;
}

int C3DElementNode::getElement(const char* name, int* out) const
{
    const char* valueString = getElement(name);
    if (valueString)
    {
        int value;
        int scanned;
        scanned = sscanf(valueString, "%d", &value);
        if (scanned != 1)
        {
            LOG_ERROR_VARG("Error parsing property: %s", name);
            return 0;
        }
        return value;
    }

    return 0;
}

long C3DElementNode::getElement(const char* name, long* out) const
{
    const char* valueString = getElement(name);
    if (valueString)
    {
        int value;
        int scanned;
        scanned = sscanf(valueString, "%ld", &value);
        if (scanned != 1)
        {
            LOG_ERROR_VARG("Error parsing property: %s", name);
            return 0;
        }
        return value;
    }

    return 0;
}

float C3DElementNode::getElement(const char* name, float* out) const
{
    const char* valueString = getElement(name);
    if (valueString)
    {
        float value;
        int scanned;
        scanned = sscanf(valueString, "%f", &value);
        if (scanned != 1)
        {
            LOG_ERROR_VARG("Error parsing property: %s", name);
            return 0.0f;
        }
        return value;
    }

    return 0.0f;
}


bool C3DElementNode::getElement(const char* name, C3DMatrix* out) const
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
            LOG_ERROR_VARG("Error parsing property: %s", name);
            out->setIdentity();
            return false;
        }

        out->set(m);
        return true;
    }

    out->setIdentity();
    return false;
}

bool C3DElementNode::getElement(const char* name, C3DVector2* out) const
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
            LOG_ERROR_VARG("Error parsing property: %s", name);
            out->set(0.0f, 0.0f);
            return false;
        }

        out->set(x, y);
        return true;
    }
    
    out->set(0.0f, 0.0f);
    return false;
}

bool C3DElementNode::getElement(const char* name, C3DVector3* out) const
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
            LOG_ERROR_VARG("Error parsing property: %s", name);
            out->set(0.0f, 0.0f, 0.0f);
            return false;
        }

        out->set(x, y, z);
        return true;
    }
    
    out->set(0.0f, 0.0f, 0.0f);
    return false;
}

bool C3DElementNode::getElement(const char* name, C3DVector4* out) const
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
            LOG_ERROR_VARG("Error parsing property: %s", name);
            out->set(0.0f, 0.0f, 0.0f, 0.0f);
            return false;
        }

        out->set(x, y, z, w);
        return true;
    }
    
    out->set(0.0f, 0.0f, 0.0f, 0.0f);
    return false;
}

bool C3DElementNode::getElement(const char* name, C3DQuaternion* out) const
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
            LOG_ERROR_VARG("Error parsing property: %s", name);
            out->set(0.0f, 0.0f, 0.0f, 1.0f);
            return false;
        }

        out->set(C3DVector3(x, y, z), MATH_DEG_TO_RAD(theta));
        return true;
    }
    
    out->set(0.0f, 0.0f, 0.0f, 1.0f);
    return false;
}
*/
    
bool C3DElementNode::writeToFile(const char* fileName)
{
    
    assert(fileName);
    
    if (!fileName || strlen(fileName) == 0)
    {
        WARN("Attempting to write a Properties object to an empty URL!");
        return false;
    }
    
    
	C3DStream* stream = C3DStreamManager::openStream(fileName, "wb", C3DStreamManager::StreamType_File);
    if (!stream)
    {
		WARN("Failed to open file");
        return false;
    }
    
    write(stream, "");
    
    SAFE_DELETE(stream);

    /***
    // Test code
    int len = 10;
    char* buf = new char[len];
    memset(buf, 0, len);
    C3DMemoryStream* pMemFile = C3DMemoryStream::create(buf, len);
    write(pMemFile, "");
    ****/
    
    return true;

}

void C3DElementNode::write(C3DStream* stream, const std::string& indent)
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

void C3DElementNode::setElementFlag(const char* flagName, const char* flag)
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

int C3DElementNode::getElementCount() const
{
    return (int)_elements.size();
}


}