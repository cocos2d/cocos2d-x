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

#include "fcntl.h"
#include "sys/stat.h"

USING_NS_CC;

AppDelegate g_app;

#ifdef OLD_NACL_MOUNTS
#include "nacl-mounts/base/UrlLoaderJob.h"
void downloadFiles(MainThreadRunner* runner, const char** filenames, int num_files)
{
    CCLOG("Downloading %d files...", num_files);
    for (int i = 0; i < num_files; i++)
    {
        std::vector<char> data;
        const char* filename = filenames[i];
        std::string url = "Resources/";
        url += filename;

        CCLOG("Downloading: %s -> %s", url.c_str(), filename);
        UrlLoaderJob *job = new UrlLoaderJob;
        job->set_url(url);
        job->set_dst(&data);
        runner->RunJob(job);
        CCLOG("Got %d bytes", data.size());

        CCLOG("Writing file: %s", filename);
        int fd = open(filename, O_CREAT | O_WRONLY);
        if (fd == -1)
        {
            CCLOG("Error writing file: %s", filename);
            continue;
        }
        write(fd, &data[0], data.size());
        close(fd);
    }
}
#endif

void* cocos_main(void* arg)
{
    CocosPepperInstance* instance = (CocosPepperInstance*)arg;
    fprintf(stderr, "in cocos_main\n");

    alSetPpapiInfo(instance->pp_instance(), pp::Module::Get()->get_browser_interface());

#ifdef OLD_NACL_MOUNTS
    // TODO(sbc): remove this hack an replace with some kind of URL mount
    mkdir("hd", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("sd", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("fonts", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    const char* filenames[] = { "hd/CloseNormal.png",
                                "sd/CloseNormal.png",
                                "hd/CloseSelected.png",
                                "sd/CloseSelected.png",
                                "hd/Target.png",
                                "sd/Target.png",
                                "hd/Player.png",
                                "sd/Player.png",
                                "hd/Projectile.png",
                                "sd/Projectile.png",
                                "pew-pew-lei.wav",
                                "fonts/Marker Felt.ttf" };

    downloadFiles(instance->m_runner, filenames, sizeof(filenames)/sizeof(char*));
#endif

    fprintf(stderr, "calling application->run\n");
    int rtn = CCApplication::sharedApplication()->run();
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
