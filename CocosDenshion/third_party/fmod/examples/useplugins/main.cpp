/*===============================================================================================
 Use Plugins Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to use FMODEXP.DYLIB and its associated plugins.
===============================================================================================*/
#include "../../api/inc/fmod.hpp"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"


void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}


int main(int argc, char *argv[])
{
    FMOD::System     *system  = 0;
    FMOD::Sound      *sound   = 0;
    FMOD::Channel    *channel = 0;
    FMOD_RESULT       result;
    int               count;
    bool              playing = false;
    int               key;
    unsigned int      version;
    int               numoutputplugins = 0;
    unsigned int      handle  = 0;

    /*
        Global Settings
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        getch();
        return 0;
    }

    /*
        Set the source directory for all of the FMOD plugins.
    */
    result = system->setPluginPath("../../api/plugins");
    ERRCHECK(result);

    /*
        Display plugins
    */
    {
        int num;
        char name[256];

        printf("Codec plugins\n");
        printf("--------------\n");
        result = system->getNumPlugins(FMOD_PLUGINTYPE_CODEC, &num);
        ERRCHECK(result);
        for (count = 0; count < num; count++)
        {
            result = system->getPluginHandle(FMOD_PLUGINTYPE_CODEC, count, &handle);
            ERRCHECK(result);

            result = system->getPluginInfo(handle, 0, name, 256, 0);
            ERRCHECK(result);

            printf("%2d - %-30s", count + 1, name);

            if (count % 2)
            {
                printf("\n");
            }
        }
        printf("\n");
        if (count % 2)
        {
            printf("\n");
        }

        printf("DSP plugins\n");
        printf("--------------\n");
        result = system->getNumPlugins(FMOD_PLUGINTYPE_DSP, &num);
        ERRCHECK(result);
        for (count = 0; count < num; count++)
        {
            result = system->getPluginHandle(FMOD_PLUGINTYPE_DSP, count, &handle);
            ERRCHECK(result);

            result = system->getPluginInfo(handle, 0, name, 256, 0);
            ERRCHECK(result);

            printf("%2d - %-30s", count + 1, name);

            if (count % 2)
            {
                printf("\n");
            }
        }
        printf("\n");
        if (count % 2)
        {
            printf("\n");
        }

        printf("Output plugins\n");
        printf("--------------\n");
        result = system->getNumPlugins(FMOD_PLUGINTYPE_OUTPUT, &num);
        ERRCHECK(result);
        for (count = 0; count < num; count++)
        {
            result = system->getPluginHandle(FMOD_PLUGINTYPE_OUTPUT, count, &handle);
            ERRCHECK(result);

            result = system->getPluginInfo(handle, 0, name, 256, 0);
            ERRCHECK(result);

            printf("%2d - %-30s", count + 1, name);

            if (count % 2)
            {
                printf("\n");
            }
        }
        if (count % 2)
        {
            printf("\n");
        }

        numoutputplugins = num;
    }

    /*
        System initialization
    */
    printf("-----------------------------------------------------------------------\n");    // print driver names
    printf("Press a corresponding number for an OUTPUT PLUGIN to use or ESC to quit\n");

    do
    {
        key = getch();
    } while (!(key == 27 || (key >= '1' && key <= '0' + numoutputplugins)));

    if (key == 27)
    {
        return 0;
    }

    result = system->getPluginHandle(FMOD_PLUGINTYPE_OUTPUT, key - '1', &handle);
    ERRCHECK(result);

    result = system->setOutputByPlugin(handle);
    ERRCHECK(result);

    result = system->init(32, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);

    result = system->createSound("../media/wave.mp3", FMOD_SOFTWARE | FMOD_CREATESTREAM, 0, &sound);
    ERRCHECK(result);

    printf("Press a key to play sound to output device.\n");

    result = system->playSound(FMOD_CHANNEL_FREE, sound, 0, &channel);
    ERRCHECK(result);

    /*
        Main loop.
    */
    do
    {
        unsigned int ms = 0;
        unsigned int lenms = 0;
        bool         paused = false;
        int          channelsplaying = 0;
        FMOD::Sound *currentsound = 0;

        system->update();

        playing = false;

        result = channel->isPlaying(&playing);
        if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
        {
            ERRCHECK(result);
        }

        result = channel->getPaused(&paused);
        if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
        {
            ERRCHECK(result);
        }

        result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
        if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
        {
            ERRCHECK(result);
        }
       
        channel->getCurrentSound(&currentsound);
        if (currentsound)
        {
            result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }
        }

        system->getChannelsPlaying(&channelsplaying);

        printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s : Channels Playing %2d\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped", channelsplaying);
        fflush(stdout);
        Sleep(5);

        if (kbhit())
        {
            key = getch();
            if (key == 27)
            {
                break;
            }
        }

    } while (playing);

    printf("\n");

    /*
        Shut down
    */
    result = sound->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    return 0;
}


