#include <string>
#include <vector>
using namespace std;

string getJsSearchPath()
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
	searchPathArray.push_back(getJsSearchPath());
	return searchPathArray;
}
