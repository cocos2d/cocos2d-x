
#include <string>
#include <vector>
using namespace std;

string getJsSearchPath()
{
    NSString *bundlePath = [[NSBundle mainBundle] resourcePath];
    if (bundlePath != nil) {
        return [bundlePath UTF8String];
    }
    return "";
}

vector<string> getSearchPath()
{
	vector<string> searchPathArray;
    searchPathArray.push_back(getJsSearchPath());
	return searchPathArray;
}



