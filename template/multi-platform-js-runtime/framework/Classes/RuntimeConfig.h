

#ifndef  _RUNTIME_CONFIG_H_
#define  _RUNTIME_CONFIG_H_

#include "CCScheduler.h"
#include <vector>
#include <string>
using namespace std;
using namespace cocos2d;

class  RuntimeConfig:public Object 
{
public:
	static RuntimeConfig* getInstance();
	void resetRuntime();
	void setSearchPath();
	void waitConnect();

private:
	void updateConnect(float delta);
    RuntimeConfig();
    virtual ~RuntimeConfig();
	Scheduler *_scheduler;
	char szwaitFile[512];
	string _searchPath;
};

#endif // _RUNTIME_CONFIG_H_

