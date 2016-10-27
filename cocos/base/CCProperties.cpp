/**
 Copyright 2013 BlackBerry Inc.
 Copyright (c) 2015 Chukong Technologies

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Original file from GamePlay3D: http://gameplay3d.org

 This file was modified to fit the cocos2d-x project
 */


#include "base/CCProperties.h"

#include <string.h>

#include "platform/CCPlatformMacros.h"
#include "platform/CCFileUtils.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "math/Mat4.h"
#include "math/Quaternion.h"
#include "base/ccUTF8.h"
#include "base/CCData.h"

USING_NS_CC;

// Utility functions (shared with SceneLoader).
/** @script{ignore} */
void calculateNamespacePath(const std::string& urlString, std::string& fileString, std::vector<std::string>& namespacePath);
/** @script{ignore} */
Properties* getPropertiesFromNamespacePath(Properties* properties, const std::vector<std::string>& namespacePath);

Properties::Properties()
: _variables(nullptr), _dirPath(nullptr), _parent(nullptr), _dataIdx(nullptr), _data(nullptr)
{
    _properties.reserve(32);
}

Properties::Properties(const Properties& copy)
    : _namespace(copy._namespace), _id(copy._id), _parentID(copy._parentID), _properties(copy._properties),
      _variables(nullptr), _dirPath(nullptr), _parent(copy._parent),
      _dataIdx(copy._dataIdx), _data(copy._data)
{
    setDirectoryPath(copy._dirPath);

    for (const auto space: copy._namespaces)
    {
        _namespaces.push_back(new (std::nothrow) Properties(*space));
    }
    rewind();
}

Properties::Properties(Data* data, ssize_t* dataIdx)
    : _variables(NULL), _dirPath(NULL), _parent(NULL), _dataIdx(dataIdx), _data(data)
{
    readProperties();
    rewind();
}

Properties::Properties(Data* data, ssize_t* dataIdx, const std::string& name, const char* id, const char* parentID, Properties* parent)
    : _namespace(name), _variables(NULL), _dirPath(NULL), _parent(parent), _dataIdx(dataIdx), _data(data)
{
    if (id)
    {
        _id = id;
    }
    if (parentID)
    {
        _parentID = parentID;
    }
    readProperties();
    rewind();
}

Properties* Properties::createNonRefCounted(const std::string& url)
{
    if (url.size() == 0)
    {
        CCLOGERROR("Attempting to create a Properties object from an empty URL!");
        return nullptr;
    }

    // Calculate the file and full namespace path from the specified url.
    std::string urlString = url;
    std::string fileString;
    std::vector<std::string> namespacePath;
    calculateNamespacePath(urlString, fileString, namespacePath);


    // data will be released automatically when 'data' goes out of scope
    // so we pass data as weak pointer
    auto data = FileUtils::getInstance()->getDataFromFile(fileString);
    ssize_t dataIdx = 0;
    Properties* properties = new (std::nothrow) Properties(&data, &dataIdx);
    properties->resolveInheritance();

    // Get the specified properties object.
    Properties* p = getPropertiesFromNamespacePath(properties, namespacePath);
    if (!p)
    {
        CCLOGWARN("Failed to load properties from url '%s'.", url.c_str());
        CC_SAFE_DELETE(properties);
        return nullptr;
    }

    // If the loaded properties object is not the root namespace,
    // then we have to clone it and delete the root namespace
    // so that we don't leak memory.
    if (p != properties)
    {
        p = p->clone();
        CC_SAFE_DELETE(properties);
    }
    // XXX
//    p->setDirectoryPath(FileSystem::getDirectoryName(fileString));
    p->setDirectoryPath("");
    return p;
}

static bool isVariable(const char* str, char* outName, size_t outSize)
{
    size_t len = strlen(str);
    if (len > 3 && str[0] == '$' && str[1] == '{' && str[len - 1] == '}')
    {
        size_t size = len - 3;
        if (size > (outSize - 1))
            size = outSize - 1;
        strncpy(outName, str + 2, len - 3);
        outName[len - 3] = 0;
        return true;
    }

    return false;
}

void Properties::readProperties()
{
    CCASSERT(_data->getSize() >0, "Invalid data");

    char line[2048];
    char variable[256];
    int c;
    char* name;
    char* value;
    char* parentID;
    char* rc;
    char* rcc;
    char* rccc;
    bool comment = false;

    while (true)
    {
        // Skip whitespace at the start of lines
        skipWhiteSpace();

        // Stop when we have reached the end of the file.
        if (eof())
            break;

        // Read the next line.
        rc = readLine(line, 2048);
        if (rc == NULL)
        {
            CCLOGERROR("Error reading line from file.");
            return;
        }

        // Ignore comments
        if (comment)
        {
            // Check for end of multi-line comment at either start or end of line
            if (strncmp(line, "*/", 2) == 0)
                comment = false;
            else
            {
                trimWhiteSpace(line);
                const auto len = strlen(line);
                if (len >= 2 && strncmp(line + (len - 2), "*/", 2) == 0)
                    comment = false;
            }
        }
        else if (strncmp(line, "/*", 2) == 0)
        {
            // Start of multi-line comment (must be at start of line)
            comment = true;
        }
        else if (strncmp(line, "//", 2) != 0)
        {
            // If an '=' appears on this line, parse it as a name/value pair.
            // Note: strchr() has to be called before strtok(), or a backup of line has to be kept.
            rc = strchr(line, '=');
            if (rc != NULL)
            {
                // First token should be the property name.
                name = strtok(line, "=");
                if (name == NULL)
                {
                    CCLOGERROR("Error parsing properties file: attribute without name.");
                    return;
                }

                // Remove white-space from name.
                name = trimWhiteSpace(name);

                // Scan for next token, the property's value.
                value = strtok(NULL, "");
                if (value == NULL)
                {
                    CCLOGERROR("Error parsing properties file: attribute with name ('%s') but no value.", name);
                    return;
                }

                // Remove white-space from value.
                value = trimWhiteSpace(value);

                // Is this a variable assignment?
                if (isVariable(name, variable, 256))
                {
                    setVariable(variable, value);
                }
                else
                {
                    // Normal name/value pair
                    _properties.push_back(Property(name, value));
                }
            }
            else
            {
                parentID = NULL;

                // Get the last character on the line (ignoring whitespace).
                const char* lineEnd = trimWhiteSpace(line) + (strlen(trimWhiteSpace(line)) - 1);

                // This line might begin or end a namespace,
                // or it might be a key/value pair without '='.

                // Check for '{' on same line.
                rc = strchr(line, '{');

                // Check for inheritance: ':'
                rcc = strchr(line, ':');

                // Check for '}' on same line.
                rccc = strchr(line, '}');
            
                // Get the name of the namespace.
                name = strtok(line, " \t\n{");
                name = trimWhiteSpace(name);
                if (name == NULL)
                {
                    CCLOGERROR("Error parsing properties file: failed to determine a valid token for line '%s'.", line);
                    return;
                }
                else if (name[0] == '}')
                {
                    // End of namespace.
                    return;
                }

                // Get its ID if it has one.
                value = strtok(NULL, ":{");
                value = trimWhiteSpace(value);

                // Get its parent ID if it has one.
                if (rcc != NULL)
                {
                    parentID = strtok(NULL, "{");
                    parentID = trimWhiteSpace(parentID);
                }

                if (value != NULL && value[0] == '{')
                {
                    // If the namespace ends on this line, seek back to right before the '}' character.
                    if (rccc && rccc == lineEnd)
                    {
                        if (seekFromCurrent(-1) == false)
                        {
                            CCLOGERROR("Failed to seek back to before a '}' character in properties file.");
                            return;
                        }
                        while (readChar() != '}')
                        {
                            if (seekFromCurrent(-2) == false)
                            {
                                CCLOGERROR("Failed to seek back to before a '}' character in properties file.");
                                return;
                            }
                        }
                        if (seekFromCurrent(-1) == false)
                        {
                            CCLOGERROR("Failed to seek back to before a '}' character in properties file.");
                            return;
                        }
                    }

                    // New namespace without an ID.
                    Properties* space = new (std::nothrow) Properties(_data, _dataIdx, name, NULL, parentID, this);
                    _namespaces.push_back(space);

                    // If the namespace ends on this line, seek to right after the '}' character.
                    if (rccc && rccc == lineEnd)
                    {
                        if (seekFromCurrent(1) == false)
                        {
                            CCLOGERROR("Failed to seek to immediately after a '}' character in properties file.");
                            return;
                        }
                    }
                }
                else
                {
                    // If '{' appears on the same line.
                    if (rc != NULL)
                    {
                        // If the namespace ends on this line, seek back to right before the '}' character.
                        if (rccc && rccc == lineEnd)
                        {
                            if (seekFromCurrent(-1) == false)
                            {
                                CCLOGERROR("Failed to seek back to before a '}' character in properties file.");
                                return;
                            }
                            while (readChar() != '}')
                            {
                                if (seekFromCurrent(-2) == false)
                                {
                                    CCLOGERROR("Failed to seek back to before a '}' character in properties file.");
                                    return;
                                }
                            }
                            if (seekFromCurrent(-1) == false)
                            {
                                CCLOGERROR("Failed to seek back to before a '}' character in properties file.");
                                return;
                            }
                        }

                        // Create new namespace.
                        Properties* space = new (std::nothrow) Properties(_data, _dataIdx, name, value, parentID, this);
                        _namespaces.push_back(space);

                        // If the namespace ends on this line, seek to right after the '}' character.
                        if (rccc && rccc == lineEnd)
                        {
                            if (seekFromCurrent(1) == false)
                            {
                                CCLOGERROR("Failed to seek to immediately after a '}' character in properties file.");
                                return;
                            }
                        }
                    }
                    else
                    {
                        // Find out if the next line starts with "{"
                        skipWhiteSpace();
                        c = readChar();
                        if (c == '{')
                        {
                            // Create new namespace.
                            Properties* space = new (std::nothrow) Properties(_data, _dataIdx, name, value, parentID, this);
                            _namespaces.push_back(space);
                        }
                        else
                        {
                            // Back up from fgetc()
                            if (seekFromCurrent(-1) == false)
                                CCLOGERROR("Failed to seek backwards a single character after testing if the next line starts with '{'.");

                            // Store "name value" as a name/value pair, or even just "name".
                            if (value != NULL)
                            {
                                _properties.push_back(Property(name, value));
                            }
                            else
                            {
                                _properties.push_back(Property(name, ""));
                            }
                        }
                    }
                }
            }
        }
    }
}

Properties::~Properties()
{
    CC_SAFE_DELETE(_dirPath);
    for (size_t i = 0, count = _namespaces.size(); i < count; ++i)
    {
        CC_SAFE_DELETE(_namespaces[i]);
    }

    CC_SAFE_DELETE(_variables);
}

//
// Stream simulation
//
signed char Properties::readChar()
{
    if (eof())
        return EOF;
    return _data->_bytes[(*_dataIdx)++];
}

char* Properties::readLine(char* output, int num)
{
    if (eof())
        return nullptr;

    // little optimization: avoid unneeded dereferences
    const ssize_t dataIdx = *_dataIdx;
    int i;

    for (i=0; i<num && dataIdx+i < _data->_size; i++)
    {
        auto c = _data->_bytes[dataIdx+i];
        if (c == '\n')
            break;
        output[i] = c;
    }

    output[i] = '\0';

    // restore value
    *_dataIdx = dataIdx+i;

    return output;
}

bool Properties::seekFromCurrent(int offset)
{
    (*_dataIdx) += offset;

    return (!eof() && *_dataIdx >= 0);
}

bool Properties::eof()
{
    return (*_dataIdx >= _data->_size);
}

void Properties::skipWhiteSpace()
{
    signed char c;
    do
    {
        c = readChar();
    } while (isspace(c) && c != EOF);

    // If we are not at the end of the file, then since we found a
    // non-whitespace character, we put the cursor back in front of it.
    if (c != EOF)
    {
        if (seekFromCurrent(-1) == false)
        {
            CCLOGERROR("Failed to seek backwards one character after skipping whitespace.");
        }
    }
}

char* Properties::trimWhiteSpace(char *str)
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

void Properties::resolveInheritance(const char* id)
{
    // Namespaces can be defined like so:
    // "name id : parentID { }"
    // This method merges data from the parent namespace into the child.

    // Get a top-level namespace.
    Properties* derived;
    if (id)
    {
        derived = getNamespace(id);
    }
    else
    {
        derived = getNextNamespace();
    }
    while (derived)
    {
        // If the namespace has a parent ID, find the parent.
        if (!derived->_parentID.empty())
        {
            Properties* parent = getNamespace(derived->_parentID.c_str());
            if (parent)
            {
                resolveInheritance(parent->getId());

                // Copy the child.
                Properties* overrides = new (std::nothrow) Properties(*derived);

                // Delete the child's data.
                for (size_t i = 0, count = derived->_namespaces.size(); i < count; i++)
                {
                    CC_SAFE_DELETE(derived->_namespaces[i]);
                }

                // Copy data from the parent into the child.
                derived->_properties = parent->_properties;
                derived->_namespaces = std::vector<Properties*>();
                std::vector<Properties*>::const_iterator itt;
                for (const auto space: parent->_namespaces)
                {
                    derived->_namespaces.push_back(new (std::nothrow) Properties(*space));
                }
                derived->rewind();

                // Take the original copy of the child and override the data copied from the parent.
                derived->mergeWith(overrides);

                // Delete the child copy.
                CC_SAFE_DELETE(overrides);
            }
        }

        // Resolve inheritance within this namespace.
        derived->resolveInheritance();

        // Get the next top-level namespace and check again.
        if (!id)
        {
            derived = getNextNamespace();
        }
        else
        {
            derived = NULL;
        }
    }
}

void Properties::mergeWith(Properties* overrides)
{
    CCASSERT(overrides, "Invalid overrides");

    // Overwrite or add each property found in child.
    overrides->rewind();
    const char* name = overrides->getNextProperty();
    while (name)
    {
        this->setString(name, overrides->getString());
        name = overrides->getNextProperty();
    }
    this->_propertiesItr = this->_properties.end();

    // Merge all common nested namespaces, add new ones.
    Properties* overridesNamespace = overrides->getNextNamespace();
    while (overridesNamespace)
    {
        bool merged = false;

        rewind();
        Properties* derivedNamespace = getNextNamespace();
        while (derivedNamespace)
        {
            if (strcmp(derivedNamespace->getNamespace(), overridesNamespace->getNamespace()) == 0 &&
                strcmp(derivedNamespace->getId(), overridesNamespace->getId()) == 0)
            {   
                derivedNamespace->mergeWith(overridesNamespace);
                merged = true;
            }

            derivedNamespace = getNextNamespace();
        }

        if (!merged)
        {
            // Add this new namespace.
            Properties* newNamespace = new (std::nothrow) Properties(*overridesNamespace);

            this->_namespaces.push_back(newNamespace);
            this->_namespacesItr = this->_namespaces.end();
        }

        overridesNamespace = overrides->getNextNamespace();
    }
}

const char* Properties::getNextProperty()
{
    if (_propertiesItr == _properties.end())
    {
        // Restart from the beginning
        _propertiesItr = _properties.begin();
    }
    else
    {
        // Move to the next property
        ++_propertiesItr;
    }

    return _propertiesItr == _properties.end() ? NULL : _propertiesItr->name.c_str();
}

Properties* Properties::getNextNamespace()
{
    if (_namespacesItr == _namespaces.end())
    {
        // Restart from the beginning
        _namespacesItr = _namespaces.begin();
    }
    else
    {
        ++_namespacesItr;
    }

    if (_namespacesItr != _namespaces.end())
    {
        Properties* ns = *_namespacesItr;
        return ns;
    }

    return nullptr;
}

void Properties::rewind()
{
    _propertiesItr = _properties.end();
    _namespacesItr = _namespaces.end();
}

Properties* Properties::getNamespace(const char* id, bool searchNames, bool recurse) const
{
    CCASSERT(id, "invalid id");

    for (const auto& it : _namespaces)
    {
        Properties* p = it;
        if (strcmp(searchNames ? p->_namespace.c_str() : p->_id.c_str(), id) == 0)
            return p;
        
        if (recurse)
        {
            // Search recursively.
            p = p->getNamespace(id, searchNames, true);
            if (p)
                return p;
        }
    }

    return nullptr;
}

const char* Properties::getNamespace() const
{
    return _namespace.c_str();
}

const char* Properties::getId() const
{
    return _id.c_str();
}

bool Properties::exists(const char* name) const
{
    if (name == NULL)
        return false;

    for (const auto& itr : _properties)
    {
        if (itr.name == name)
            return true;
    }

    return false;
}

static bool isStringNumeric(const char* str)
{
    CCASSERT(str, "invalid str");

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

Properties::Type Properties::getType(const char* name) const
{
    const char* value = getString(name);
    if (!value)
    {
        return Properties::NONE;
    }

    // Parse the value to determine the format
    unsigned int commaCount = 0;
    char* valuePtr = const_cast<char*>(value);
    while ((valuePtr = strchr(valuePtr, ',')))
    {
        valuePtr++;
        commaCount++;
    }

    switch (commaCount)
    {
    case 0:
        return isStringNumeric(value) ? Properties::NUMBER : Properties::STRING;
    case 1:
        return Properties::VECTOR2;
    case 2:
        return Properties::VECTOR3;
    case 3:
        return Properties::VECTOR4;
    case 15:
        return Properties::MATRIX;
    default:
        return Properties::STRING;
    }
}

const char* Properties::getString(const char* name, const char* defaultValue) const
{
    char variable[256];
    const char* value = NULL;

    if (name)
    {
        // If 'name' is a variable, return the variable value
        if (isVariable(name, variable, 256))
        {
            return getVariable(variable, defaultValue);
        }

        for (const auto& itr : _properties)
        {
            if (itr.name == name)
            {
                value = itr.value.c_str();
                break;
            }
        }
    }
    else
    {
        // No name provided - get the value at the current iterator position
        if (_propertiesItr != _properties.end())
        {
            value = _propertiesItr->value.c_str();
        }
    }

    if (value)
    {
        // If the value references a variable, return the variable value
        if (isVariable(value, variable, 256))
            return getVariable(variable, defaultValue);

        return value;
    }

    return defaultValue;
}

bool Properties::setString(const char* name, const char* value)
{
    if (name)
    {
        for (auto& itr : _properties)
        {
            if (itr.name == name)
            {
                // Update the first property that matches this name
                itr.value = value ? value : "";
                return true;
            }
        }

        // There is no property with this name, so add one
        _properties.push_back(Property(name, value ? value : ""));
    }
    else
    {
        // If there's a current property, set its value
        if (_propertiesItr == _properties.end())
            return false;

        _propertiesItr->value = value ? value : "";
    }

    return true;
}

bool Properties::getBool(const char* name, bool defaultValue) const
{
    const char* valueString = getString(name);
    if (valueString)
    {
        return (strcmp(valueString, "true") == 0);
    }

    return defaultValue;
}

int Properties::getInt(const char* name) const
{
    const char* valueString = getString(name);
    if (valueString)
    {
        int value;
        int scanned;
        scanned = sscanf(valueString, "%d", &value);
        if (scanned != 1)
        {
            CCLOGERROR("Error attempting to parse property '%s' as an integer.", name);
            return 0;
        }
        return value;
    }

    return 0;
}

float Properties::getFloat(const char* name) const
{
    const char* valueString = getString(name);
    if (valueString)
    {
        float value;
        int scanned;
        scanned = sscanf(valueString, "%f", &value);
        if (scanned != 1)
        {
            CCLOGERROR("Error attempting to parse property '%s' as a float.", name);
            return 0.0f;
        }
        return value;
    }

    return 0.0f;
}

long Properties::getLong(const char* name) const
{
    const char* valueString = getString(name);
    if (valueString)
    {
        long value;
        int scanned;
        scanned = sscanf(valueString, "%ld", &value);
        if (scanned != 1)
        {
            CCLOGERROR("Error attempting to parse property '%s' as a long integer.", name);
            return 0L;
        }
        return value;
    }

    return 0L;
}

bool Properties::getMat4(const char* name, Mat4* out) const
{
    CCASSERT(out, "Invalid out");

    const char* valueString = getString(name);
    if (valueString)
    {
        float m[16];
        int scanned;
        scanned = sscanf(valueString, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
                &m[0], &m[1], &m[2], &m[3], &m[4], &m[5], &m[6], &m[7],
                &m[8], &m[9], &m[10], &m[11], &m[12], &m[13], &m[14], &m[15]);

        if (scanned != 16)
        {
            CCLOGERROR("Error attempting to parse property '%s' as a matrix.", name);
            out->setIdentity();
            return false;
        }

        out->set(m);
        return true;
    }

    out->setIdentity();
    return false;
}

bool Properties::getVec2(const char* name, Vec2* out) const
{
    return parseVec2(getString(name), out);
}

bool Properties::getVec3(const char* name, Vec3* out) const
{
    return parseVec3(getString(name), out);
}

bool Properties::getVec4(const char* name, Vec4* out) const
{
    return parseVec4(getString(name), out);
}

bool Properties::getQuaternionFromAxisAngle(const char* name, Quaternion* out) const
{
    return parseAxisAngle(getString(name), out);
}

bool Properties::getColor(const char* name, Vec3* out) const
{
    return parseColor(getString(name), out);
}

bool Properties::getColor(const char* name, Vec4* out) const
{
    return parseColor(getString(name), out);
}

bool Properties::getPath(const char* name, std::string* path) const
{
    CCASSERT(name && path, "Invalid name or path");
    const char* valueString = getString(name);
    if (valueString)
    {
        if (FileUtils::getInstance()->isFileExist(valueString))
        {
            path->assign(valueString);
            return true;
        }
        else
        {
            const Properties* prop = this;
            while (prop != NULL)
            {
                // Search for the file path relative to the bundle file
                const std::string* dirPath = prop->_dirPath;
                if (dirPath != NULL && !dirPath->empty())
                {
                    std::string relativePath = *dirPath;
                    relativePath.append(valueString);
                    if (FileUtils::getInstance()->isFileExist(relativePath))
                    {
                        path->assign(relativePath);
                        return true;
                    }
                }
                prop = prop->_parent;
            }
        }
    }
    return false;
}

const char* Properties::getVariable(const char* name, const char* defaultValue) const
{
    if (name == NULL)
        return defaultValue;

    // Search for variable in this Properties object
    if (_variables)
    {
        for (size_t i = 0, count = _variables->size(); i < count; ++i)
        {
            Property& prop = (*_variables)[i];
            if (prop.name == name)
                return prop.value.c_str();
        }
    }

    // Search for variable in parent Properties
    return _parent ? _parent->getVariable(name, defaultValue) : defaultValue;
}

void Properties::setVariable(const char* name, const char* value)
{
    CCASSERT(name, "Invalid name");

    Property* prop = NULL;

    // Search for variable in this Properties object and parents
    Properties* current = const_cast<Properties*>(this);
    while (current)
    {
        if (current->_variables)
        {
            for (size_t i = 0, count = current->_variables->size(); i < count; ++i)
            {
                Property* p = &(*current->_variables)[i];
                if (p->name == name)
                {
                    prop = p;
                    break;
                }
            }
        }
        current = current->_parent;
    }

    if (prop)
    {
        // Found an existing property, set it
        prop->value = value ? value : "";
    }
    else
    {
        // Add a new variable with this name
        if (!_variables)
            _variables = new (std::nothrow) std::vector<Property>();
        _variables->push_back(Property(name, value ? value : ""));
    }
}

Properties* Properties::clone()
{
    Properties* p = new (std::nothrow) Properties();
    
    p->_namespace = _namespace;
    p->_id = _id;
    p->_parentID = _parentID;
    p->_properties = _properties;
    p->_propertiesItr = p->_properties.end();
    p->setDirectoryPath(_dirPath);

    for (size_t i = 0, count = _namespaces.size(); i < count; i++)
    {
        CCASSERT(_namespaces[i], "Invalid namespace");
        Properties* child = _namespaces[i]->clone();
        p->_namespaces.push_back(child);
        child->_parent = p;
    }
    p->_namespacesItr = p->_namespaces.end();

    return p;
}

void Properties::setDirectoryPath(const std::string* path)
{
    if (path)
    {
        setDirectoryPath(*path);
    }
    else
    {
        CC_SAFE_DELETE(_dirPath);
    }
}

void Properties::setDirectoryPath(const std::string& path)
{
    if (_dirPath == NULL)
    {
        _dirPath = new (std::nothrow) std::string(path);
    }
    else
    {
        _dirPath->assign(path);
    }
}

void calculateNamespacePath(const std::string& urlString, std::string& fileString, std::vector<std::string>& namespacePath)
{
    // If the url references a specific namespace within the file,
    // calculate the full namespace path to the final namespace.
    size_t loc = urlString.rfind("#");
    if (loc != std::string::npos)
    {
        fileString = urlString.substr(0, loc);
        std::string namespacePathString = urlString.substr(loc + 1);
        while ((loc = namespacePathString.find("/")) != std::string::npos)
        {
            namespacePath.push_back(namespacePathString.substr(0, loc));
            namespacePathString = namespacePathString.substr(loc + 1);
        }
        namespacePath.push_back(namespacePathString);
    }
    else
    {
        fileString = urlString;
    }
}

Properties* getPropertiesFromNamespacePath(Properties* properties, const std::vector<std::string>& namespacePath)
{
    // If the url references a specific namespace within the file,
    // return the specified namespace or notify the user if it cannot be found.
    if (namespacePath.size() > 0)
    {
        size_t size = namespacePath.size();
        properties->rewind();
        Properties* iter = properties->getNextNamespace();
        for (size_t i = 0; i < size; )
        {
            while (true)
            {
                if (iter == NULL)
                {
                    CCLOGWARN("Failed to load properties object from url.");
                    return nullptr;
                }

                if (strcmp(iter->getId(), namespacePath[i].c_str()) == 0)
                {
                    if (i != size - 1)
                    {
                        properties = iter->getNextNamespace();
                        iter = properties;
                    }
                    else
                        properties = iter;

                    i++;
                    break;
                }
                
                iter = properties->getNextNamespace();
            }
        }

        return properties;
    }
    else
        return properties;
}

bool Properties::parseVec2(const char* str, Vec2* out)
{
    if (str)
    {
        float x, y;
        if (sscanf(str, "%f,%f", &x, &y) == 2)
        {
            if (out)
                out->set(x, y);
            return true;
        }
        else
        {
            CCLOGWARN("Error attempting to parse property as a two-dimensional vector: %s", str);
        }
    }

    if (out)
        out->set(0.0f, 0.0f);
    return false;
}

bool Properties::parseVec3(const char* str, Vec3* out)
{
    if (str)
    {
        float x, y, z;
        if (sscanf(str, "%f,%f,%f", &x, &y, &z) == 3)
        {
            if (out)
                out->set(x, y, z);
            return true;
        }
        else
        {
            CCLOGWARN("Error attempting to parse property as a three-dimensional vector: %s", str);
        }
    }

    if (out)
        out->set(0.0f, 0.0f, 0.0f);
    return false;
}

bool Properties::parseVec4(const char* str, Vec4* out)
{
    if (str)
    {
        float x, y, z, w;
        if (sscanf(str, "%f,%f,%f,%f", &x, &y, &z, &w) == 4)
        {
            if (out)
                out->set(x, y, z, w);
            return true;
        }
        else
        {
            CCLOGWARN("Error attempting to parse property as a four-dimensional vector: %s", str);
        }
    }

    if (out)
        out->set(0.0f, 0.0f, 0.0f, 0.0f);
    return false;
}

bool Properties::parseAxisAngle(const char* str, Quaternion* out)
{
    if (str)
    {
        float x, y, z, theta;
        if (sscanf(str, "%f,%f,%f,%f", &x, &y, &z, &theta) == 4)
        {
            if (out)
                out->set(Vec3(x, y, z), MATH_DEG_TO_RAD(theta));
            return true;
        }
        else
        {
            CCLOGWARN("Error attempting to parse property as an axis-angle rotation: %s", str);
        }
    }

    if (out)
        out->set(0.0f, 0.0f, 0.0f, 1.0f);
    return false;
}

bool Properties::parseColor(const char* str, Vec3* out)
{
    if (str)
    {
        if (strlen(str) == 7 && str[0] == '#')
        {
            // Read the string into an int as hex.
            unsigned int color;
            if (sscanf(str + 1, "%x", &color) == 1)
            {
                if (out)
                    out->set(Vec3::fromColor(color));
                return true;
            }
            else
            {
                // Invalid format
                CCLOGWARN("Error attempting to parse property as an RGB color: %s", str);
            }
        }
        else
        {
            // Not a color string.
            CCLOGWARN("Error attempting to parse property as an RGB color (not specified as a color string): %s", str);
        }
    }

    if (out)
        out->set(0.0f, 0.0f, 0.0f);
    return false;
}

bool Properties::parseColor(const char* str, Vec4* out)
{
    if (str)
    {
        if (strlen(str) == 9 && str[0] == '#')
        {
            // Read the string into an int as hex.
            unsigned int color;
            if (sscanf(str + 1, "%x", &color) == 1)
            {
                if (out)
                    out->set(Vec4::fromColor(color));
                return true;
            }
            else
            {
                // Invalid format
                CCLOGWARN("Error attempting to parse property as an RGBA color: %s", str);
            }
        }
        else
        {
            // Not a color string.
            CCLOGWARN("Error attempting to parse property as an RGBA color (not specified as a color string): %s", str);
        }
    }

    if (out)
        out->set(0.0f, 0.0f, 0.0f, 0.0f);
    return false;
}



