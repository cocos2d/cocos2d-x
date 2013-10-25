#ifndef ELEMENTNODE_H_
#define ELEMENTNODE_H_

#include <map>
#include "StringTool.h"
namespace cocos3d
{

class C3DMatrix;
class C3DVector2;
class C3DVector3;
class C3DVector4;
class C3DQuaternion;
class C3DStream;

/**
 * C3DElementNode is an interface for reading and writing element.
 */
class  C3DElementNode
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
    static C3DElementNode* create(const char* fileName);

	/**
     * Creates empty ElementNode.
     */
	static C3DElementNode* createEmptyNode(const char* name, const char* nodetype);

	/**
     * Adds child ElementNode.
     */
	void addChildNode(C3DElementNode* child);

	/**
     * Delete child ElementNode.
     */
	void delChildNode(const char* name, const char* nodetype);

	/**
     * Destructor.
     */
    ~C3DElementNode();

	/**
     * Get next element from current iterator.
     */
    const char* getNextElement(char** value = NULL);
	
	/**
     * Get next child from current iterator.
     */
    C3DElementNode* getNextChild();

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
    C3DElementNode* getChild(const char* chileName) const;

	/**
	 * Gets child ElementNode by specified index.
	 */
	C3DElementNode* getChild(int index) const { return _childs[index]; }

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
    ElementType getElementType(const char* elementName = NULL) const;
	 
	/**
	 * Gets the element value by specified name.
	 */
    const char* getElement(const char* name = NULL) const;

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
    C3DElementNode();

	/**
     * Constructor.
     */
    C3DElementNode(C3DStream* stream);
	
	/**
     * Constructor.
     */
    C3DElementNode(C3DStream* stream, const char* nodeType, const char* id = NULL);
	
	/**
     * read contents from the stream.
     */
	void readContents(C3DStream* stream, char* name, char* id);

	/**
     * read element from the stream.
     */
    void read(C3DStream* stream);

	/**
     * write element by the stream.
     */
	void write(C3DStream* stream, const std::string& indent);

	/**
     * read flag from the stream.
     */
    void readFlag(C3DStream* stream);

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
    std::vector<C3DElementNode*> _childs;
    std::vector<C3DElementNode*>::const_iterator _childsItr;

	std::vector<KeyValue> _flags;
	std::vector<KeyValue>::const_iterator _flagsItr;
};

}

#endif