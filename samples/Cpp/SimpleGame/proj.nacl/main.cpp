#include "main.h"
#include "../Classes/AppDelegate.h"
#include "cocos2d.h"
#include "CCInstance.h"
#include "CCModule.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include "AL/alc.h"

USING_NS_CC;

AppDelegate g_app;

void* cocos_main(void* arg)
{
    fprintf(stderr, "in cocos_main\n");
    CocosPepperInstance* instance = (CocosPepperInstance*)arg;
    alSetPpapiInfo(instance->pp_instance(), pp::Module::Get()->get_browser_interface());
    fprintf(stderr, "calling application->run\n");
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
