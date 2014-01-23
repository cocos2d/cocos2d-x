
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
	return searchPathArray;
}

string getDotWaitFilePath()
{
	string dotwaitFile;
    dotwaitFile = getJsSearchPath();
    dotwaitFile += "/.wait";
}

