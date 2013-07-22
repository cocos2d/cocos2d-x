#include "main.h"
#include "../Classes/AppDelegate.h"
#include "cocos2d.h"
#include "CCInstance.h"
#include "CCModule.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

AppDelegate g_app;

void* cocos_main(void* arg)
{
    fprintf(stderr, "in cocos_main\n");
    int rtn = Application::getInstance()->run();
    fprintf(stderr, "app run returned: %d\n", rtn);
    return NULL;
}

namespace pp
{

Module* CreateModule()
{
  return new CocosPepperModule();
}

}
