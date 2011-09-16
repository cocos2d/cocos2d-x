/*===============================================================================================
 Load from memory example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example is simply a variant of the play sound example, but it loads the data into memory
 then uses the 'load from memory' feature of System::createSound.
===============================================================================================*/
#include "../../api/inc/fmod.hpp"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"
#include <stdio.h>
#include <string.h>

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

void LoadFileIntoMemory(const char *name, void **buff, int *length)
{
    FILE *fp = fopen(name, "rb");
    
    fseek(fp, 0, SEEK_END);
    *length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    *buff = malloc(*length);
    fread(*buff, *length, 1, fp);
    
    fclose(fp);
}

int main(int argc, char *argv[])
{
    FMOD::System     *system;
    FMOD::Sound      *sound1, *sound2, *sound3;
    FMOD::Channel    *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    void             *buff = 0;
    int               length = 0;
    FMOD_CREATESOUNDEXINFO exinfo;

    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return 0;
    }

    result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    LoadFileIntoMemory("../media/drumloop.wav", &buff, &length);
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.length = length;

    result = system->createSound((const char *)buff, FMOD_HARDWARE | FMOD_OPENMEMORY, &exinfo, &sound1);
    ERRCHECK(result);
    
    result = sound1->setMode(FMOD_LOOP_OFF);
    ERRCHECK(result);   

    free(buff); // don't need the original memory any more.  Note!  If loading as a stream, the memory must stay active so do not free it!
     
    LoadFileIntoMemory("../media/jaguar.wav", &buff, &length);
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.length = length;    
   
    result = system->createSound((const char *)buff, FMOD_SOFTWARE | FMOD_OPENMEMORY, &exinfo, &sound2);
    ERRCHECK(result);

    free(buff); // don't need the original memory any more.  Note!  If loading as a stream, the memory must stay active so do not free it!
    
    LoadFileIntoMemory("../media/swish.wav", &buff, &length);
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.length = length;    

    result = system->createSound((const char *)buff, FMOD_HARDWARE | FMOD_OPENMEMORY, &exinfo, &sound3);
    ERRCHECK(result);

    free(buff); // don't need the original memory any more.  Note!  If loading as a stream, the memory must stay active so do not free it!

    printf("==========================================================================\n");
    printf("Load from memory example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("==========================================================================\n");
    printf("\n");
    printf("Press '1' to play a mono sound using hardware mixing\n");
    printf("Press '2' to play a mono sound using software mixing\n");
    printf("Press '3' to play a stereo sound using hardware mixing\n");
    printf("Press 'Esc' to quit\n");
    printf("\n");

    /*
        Main loop.
    */
    do
    {
        if (kbhit())
        {
            key = getch();

            switch (key)
            {
                case '1' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound1, false, &channel);
                    ERRCHECK(result);
                    break;
                }
                case '2' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound2, false, &channel);
                    ERRCHECK(result);
                    break;
                }
                case '3' :
                {
                    result = system->playSound(FMOD_CHANNEL_FREE, sound3, false, &channel);
                    ERRCHECK(result);
                    break;
                }
            }
        }

        system->update();

        {
            unsigned int ms = 0;
            unsigned int lenms = 0;
            bool         playing = 0;
            bool         paused = 0;
            int          channelsplaying = 0;

            if (channel)
            {
                FMOD::Sound *currentsound = 0;

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
            }

            system->getChannelsPlaying(&channelsplaying);

            printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s : Channels Playing %2d\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped", channelsplaying);
            fflush(stdout);
        }

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = sound1->release();
    ERRCHECK(result);
    result = sound2->release();
    ERRCHECK(result);
    result = sound3->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    return 0;
}


