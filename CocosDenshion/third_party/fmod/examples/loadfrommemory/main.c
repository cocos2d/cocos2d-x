/*===============================================================================================
 Load from memory example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example is simply a variant of the play sound example, but it loads the data into memory
 then uses the 'load from memory' feature of System::createSound.
===============================================================================================*/
#include "../../api/inc/fmod.h"
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
    FMOD_SYSTEM      *system;
    FMOD_SOUND       *sound1, *sound2, *sound3;
    FMOD_CHANNEL     *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    void             *buff = 0;
    int               length = 0;
    FMOD_CREATESOUNDEXINFO exinfo;

    /*
        Create a System object and initialize.
    */
    result = FMOD_System_Create(&system);
    ERRCHECK(result);

    result = FMOD_System_GetVersion(system, &version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return 0;
    }

    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);

    LoadFileIntoMemory("../media/drumloop.wav", &buff, &length);
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.length = length;

    result = FMOD_System_CreateSound(system, (const char *)buff, FMOD_HARDWARE | FMOD_OPENMEMORY, &exinfo, &sound1);
    ERRCHECK(result);

    result = FMOD_Sound_SetMode(sound1, FMOD_LOOP_OFF);
    ERRCHECK(result);

    free(buff); // don't need the original memory any more.  Note!  If loading as a stream, the memory must stay active so do not free it!

    LoadFileIntoMemory("../media/jaguar.wav", &buff, &length);
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.length = length;    

    result = FMOD_System_CreateSound(system, (const char *)buff, FMOD_SOFTWARE | FMOD_OPENMEMORY, &exinfo, &sound2);
    ERRCHECK(result);

    free(buff); // don't need the original memory any more.  Note!  If loading as a stream, the memory must stay active so do not free it!

    LoadFileIntoMemory("../media/swish.wav", &buff, &length);
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.length = length;    

    result = FMOD_System_CreateSound(system, (const char *)buff, FMOD_HARDWARE | FMOD_OPENMEMORY, &exinfo, &sound3);
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
                    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound1, 0, &channel);
                    ERRCHECK(result);
                    break;
                }
                case '2' :
                {
                    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound2, 0, &channel);
                    ERRCHECK(result);
                    break;
                }
                case '3' :
                {
                    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound3, 0, &channel);
                    ERRCHECK(result);
                    break;
                }
            }
        }

        FMOD_System_Update(system);

        {
            unsigned int ms = 0;
            unsigned int lenms = 0;
            int          playing = 0;
            int          paused = 0;
            int          channelsplaying = 0;

            if (channel)
            {
                FMOD_SOUND *currentsound = 0;

                result = FMOD_Channel_IsPlaying(channel, &playing);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }

                result = FMOD_Channel_GetPaused(channel, &paused);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }

                result = FMOD_Channel_GetPosition(channel, &ms, FMOD_TIMEUNIT_MS);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }

                FMOD_Channel_GetCurrentSound(channel, &currentsound);
                if (currentsound)
                {
                    result = FMOD_Sound_GetLength(currentsound, &lenms, FMOD_TIMEUNIT_MS);
                    if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                    {
                        ERRCHECK(result);
                    }
                }
            }

            result = FMOD_Sound_GetLength(sound1, &lenms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }

            FMOD_System_GetChannelsPlaying(system, &channelsplaying);

            printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s : Channels Playing %2d\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped", channelsplaying);
            fflush(stdout);
        }

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = FMOD_Sound_Release(sound1);
    ERRCHECK(result);
    result = FMOD_Sound_Release(sound2);
    ERRCHECK(result);
    result = FMOD_Sound_Release(sound3);
    ERRCHECK(result);
    result = FMOD_System_Close(system);
    ERRCHECK(result);
    result = FMOD_System_Release(system);
    ERRCHECK(result);

    return 0;
}


