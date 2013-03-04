#include "main.h"
#include "../Classes/AppDelegate.h"
#include "cocos2d.h"
#include "CCInstance.h"
#include "CCModule.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <AL/alc.h>


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
            assert("error writing file");
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
    fprintf(stderr, "in cocos_main %p\n", instance);

    alSetPpapiInfo(instance->pp_instance(), pp::Module::Get()->get_browser_interface());

#ifdef OLD_NACL_MOUNTS
    // TODO(sbc): remove this hack an replace with some kind of URL mount
    const char* dirnames[] = { "Images", "extensions", "fonts", "ccb",
                               "zwoptex", "Particles", "Shaders", "TileMaps" };

    for (size_t i = 0; i < sizeof(dirnames)/sizeof(char*); i++)
        mkdir(dirnames[i], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    const char* filenames[] = { "Images/grossini.png",
                                "Images/close.png",
                                "Images/ball.png",
                                "Images/paddle.png",
                                "Images/grossinis_sister1.png",
                                "Images/grossinis_sister2.png",
                                "Images/grossini_dance_01.png",
                                "Images/background1.png",
                                "Images/background2.png",
                                "Images/background3.png",
                                "Images/f1.png",
                                "Images/f2.png",
                                "Images/r1.png",
                                "Images/r2.png",
                                "Images/b1.png",
                                "Images/b2.png",
                                "Images/blocks.png",
                                "Images/Icon.png",
                                "Images/streak.png",
                                "Images/fire.png",
                                "Images/white-512x512.png",
                                "Images/test_1021x1024_rgb888.pvr.gz",
                                "Images/test_1021x1024.png",
                                "Images/grossini_dance_atlas.png",
                                "Images/powered.png",
                                "Images/background.png",
                                "TileMaps/levelmap.tga",
                                "TileMaps/tiles.png",
                                "fps_images.png",
                                "Shaders/example_Monjori.vsh",
                                "Shaders/example_Monjori.fsh",
                                "Shaders/example_Mandelbrot.vsh",
                                "Shaders/example_Mandelbrot.fsh",
                                "Shaders/example_Julia.vsh",
                                "Shaders/example_Julia.fsh",
                                "Shaders/example_Plasma.vsh",
                                "Shaders/example_Plasma.fsh",
                                "Shaders/example_Heart.vsh",
                                "Shaders/example_Heart.fsh",
                                "Shaders/example_Flower.vsh",
                                "Shaders/example_Flower.fsh",
                                "Shaders/example_Blur.fsh",
                                "Shaders/example_HorizontalColor.vsh",
                                "Shaders/example_HorizontalColor.fsh",
                                "Particles/SmallSun.plist",
                                "Particles/LavaFlow.plist",
                                "fonts/arial.ttf",
                                "fonts/west_england-64.fnt",
                                "fonts/west_england-64.png",
                                "fonts/Thonburi.ttf",
                                "fonts/Marker Felt.ttf",
                                "ccb/HelloCocosBuilder.ccbi",
                                "ccb/burst.png",
                                "effect1.wav",
                                "background.mp3",
                                "extensions/sliderTrack.png",
                                "extensions/sliderProgress.png",
                                "extensions/sliderThumb.png",
                                "extensions/background.png",
                                "extensions/ribbon.png",
                                "zwoptex/grossini.plist",
                                "zwoptex/grossini.png" };

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
