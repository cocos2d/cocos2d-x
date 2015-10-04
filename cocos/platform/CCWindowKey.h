#ifndef __CCWINDOWKEY_H__
#define __CCWINDOWKEY_H__

#include <functional>

struct GLFWwindow;

NS_CC_BEGIN

//for windows, use _key, for mac, us id?
class CC_DLL WindowKey
{
public:
	WindowKey()
		: _key(nullptr)
	{}

	//ifdef this to make it platform specific.
	explicit WindowKey(GLFWwindow* key)
		: _key(key)
	{}

	bool operator==(const WindowKey& rhs)
	{
		return rhs._key == _key;
	}

	bool operator!=(const WindowKey& rhs)
	{
		return rhs._key != _key;
	}

	static const WindowKey NULLKEY;

private:
	GLFWwindow* _key;

	friend class WindowKeyHash;
	friend class WindowKeyCompare;
};

class CC_DLL WindowKeyHash
{
public:
	//hashing function
	size_t operator()(const WindowKey& val) const 
	{
		std::hash<void*> hash;
		return hash(val._key);
	}
};

class CC_DLL WindowKeyCompare
{
public:
	//equal_to function
	bool operator()(const WindowKey& _Left, const WindowKey& _Right) const
	{
		return _Left._key == _Right._key;
	}
};

NS_CC_END

#endif /* #ifndef __CCWINDOWKEY_H__ */
