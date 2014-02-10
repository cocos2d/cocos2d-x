#include <string>
#include <vector>
using namespace std;

string getProjSearchPath()
{
	extern std::string getPackageNameJNI();
	string searchPath = "/mnt/sdcard/";
	searchPath += getPackageNameJNI();
	return searchPath;
}

vector<string> getSearchPath()
{
	extern std::string getPackageNameJNI();
	vector<string> searchPathArray;
	searchPathArray.push_back(getProjSearchPath());
	return searchPathArray;
}

string getDotWaitFilePath()
{
	extern std::string getPackageNameJNI();
	string searchPath = getPackageNameJNI();
	string dotwaitFile = "/mnt/sdcard/";
	dotwaitFile += searchPath;
	dotwaitFile += "/.wait";
	return dotwaitFile;
}
