

#ifndef  _RUNTIME_CONFIG_H_
#define  _RUNTIME_CONFIG_H_

#include "CCScheduler.h"
using namespace cocos2d;

class  RuntimeConfig:public Object 
{
public:
	static RuntimeConfig* getInstance();
	void setSearchPath();
	void waitConnect();
private:
	void updateConnect(float delta);
    RuntimeConfig();
    virtual ~RuntimeConfig();
	Scheduler *_scheduler;
	char szwaitFile[512];
};

#endif // _RUNTIME_CONFIG_H_

