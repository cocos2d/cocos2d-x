#ifndef ELEMENTNODE_H_
#define ELEMENTNODE_H_

#include <map>
#include "StringTool.h"
namespace cocos2d
{

class Matrix;
class Vector2;
class Vector3;
class Vector4;
class Quaternion;
class Stream;

/**
 * ElementNode is an interface for reading and writing element.
 */
class  ElementNode
{
public:

    enum ElementType
    {
        NONE,
        STRING,
        NUMBER,
        VECTOR2,
        VECTOR3,
        VECTOR4,
        MATRIX
    };

/**
     * Creates ElementNode.
     */
    static ElementNode* create(const char* fileName);

/**
     * Creates empty ElementNode.
     */
static ElementNode* createEmptyNode(const char* name, const char* nodetype);

/**
     * Adds child ElementNode.
     */
void addChildNode(ElementNode* child);

/**
     * Delete child ElementNode.
     */
void delChildNode(const char* name, const char* nodetype);

/**
     * Destructor.
     */
    ~ElementNode();

/**
     * Get next element from current iterator.
     */
    const char* getNextElement(char** value = nullptr);

/**
     * Get next child from current iterator.
     */
    ElementNode* getNextChild();

/**
     * Get childs count.
     */
int getChildCount() const { return (int)_childs.size(); }

/**
 * Moves the iterator to the start.
 */
    void rewind();

/**
 * Gets child ElementNode by specified name.
 */
    ElementNode* getChild(const char* chileName) const;

/**
 * Gets child ElementNode by specified index.
 */
ElementNode* getChild(int index) const { return _childs[index]; }

/**
 * Gets node type.
 */
const char* getNodeType() const;

/**
 * Gets node name.
 */
    const char* getNodeName() const;

/**
 * Gets node flag.
 */
const char* getElementFlag(const char* flagName);

/**
 * Sets node flag.
 */
    void setElementFlag(const char* flagName, const char* flag);

/**
 * Gets the element type by specified name.
 */
    ElementType getElementType(const char* elementName = nullptr) const;
 
/**
 * Gets the element value by specified name.
 */
    const char* getElement(const char* name = nullptr) const;

    /**
 * template function to get element value by specified name.
 */
    template<typename T>
    T getElement(const char* name, T* out) const
    {
        T r = (T)0;
        const char* valueString = getElement(name);
        if (valueString)
        {
            StringTool::fromString(valueString, r);
            if (out)
                *out = r;
        }
        return r;
    }

/**
 * template function to set element value by specified name.
 */
template<typename T>
void setElement(const char* name, T* value)
{
size_t i;
for (i = 0; i < _elements.size(); i++)
{
if (_elements[i].key == name)
{
_elements[i].value = StringTool::toString(*value);
break;
}
}
if (i >= _elements.size())
_elements.push_back(KeyValue(name, StringTool::toString(*value)));
}

/**
 * set element value by specified name.
 */
    void setElement(const char* name, const char* value)
    {
        size_t i;
        for (i = 0; i < _elements.size(); i++)
        {
            if (_elements[i].key == name)
            {
                _elements[i].value =value;
                break;
            }
        }
        if (i >= _elements.size())
            _elements.push_back(KeyValue(name, value));
    }

/**
* Clears all child and element.
*/
void empty();

/**
* Writes ElementNode to file.
*/
    bool writeToFile(const char* fileName);
    
/**
* Gets element count.
*/
    int getElementCount() const;
private:
/**
     * Constructor.
     */
    ElementNode();

/**
     * Constructor.
     */
    ElementNode(Stream* stream);

/**
     * Constructor.
     */
    ElementNode(Stream* stream, const char* nodeType, const char* id = nullptr);

/**
     * read contents from the stream.
     */
void readContents(Stream* stream, char* name, char* id);

/**
     * read element from the stream.
     */
    void read(Stream* stream);

/**
     * write element by the stream.
     */
void write(Stream* stream, const std::string& indent);

/**
     * read flag from the stream.
     */
    void readFlag(Stream* stream);

/**
     * Defines structure to describe the element value.
     */
    struct KeyValue
    {
        std::string key;
        std::string value;
        
        KeyValue(const std::string& k, const std::string& v) : key(k), value(v){}
    };
    
    std::string _nodeType;
    std::string _nodeName;
   
    std::vector<KeyValue> _elements;
    std::vector<KeyValue>::const_iterator _elementsItr;
    std::vector<ElementNode*> _childs;
    std::vector<ElementNode*>::const_iterator _childsItr;

std::vector<KeyValue> _flags;
std::vector<KeyValue>::const_iterator _flagsItr;
};

}

#endif