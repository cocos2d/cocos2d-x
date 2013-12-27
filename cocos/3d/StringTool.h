#ifndef STRINGTOOL_H_
#define STRINGTOOL_H_

#include <cctype>
#include <string>
#include <vector>
#include <sstream>

namespace cocos2d
{

/**
 * StringTool is an interface for the string operating.
 */
class StringTool
{
public:

	/**
     * Constructor.
     */
	 StringTool();

	 /**
     * Destructor.
     */
    ~StringTool();

	/**
     * Splits string by given string.
     */
	static std::vector<std::string> StringSplitByString(const std::string &str, const std::string &strKey, int IgnoreCase = true);

	/**
     * Splits string by given char.
     */
	static std::vector<std::string> StringSplitByChar(const std::string &str, char cKey, int IgnoreCase = true);

	/**
     * get file by given file path.
     */
	static std::string getFileName(const std::string& filepath);

	/**
     * get file by given file path.
     */
	static std::string getFileName(const std::string& filepath,const std::string& expName);

	/**
     * get file by given file path.
     */
	static std::string getFilePath(const std::string& filename);
    
	/**
    * convert string and other type
	*/
    template<typename T>
    static std::string toString(const T& x);
    
	/**
    * convert other type from string
	*/
    template<typename T>
    static void fromString(const std::string& str, T& x);
    
    static std::string toString(bool b);
    static void fromString(const std::string& str, bool& b);

public:
	


};

/**
* convert to string from other type
*/
template<typename T>
inline std::string StringTool::toString(const T& x)
{
    std::ostringstream stream;
    stream << x;
    return stream.str();
}

/**
* convert to other type from string
*/
template<typename T>
inline void StringTool::fromString(const std::string& str, T& x)
{
    std::istringstream stream(str);
    stream >> x;
}


}

#endif
