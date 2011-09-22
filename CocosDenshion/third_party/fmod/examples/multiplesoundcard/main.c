/*===============================================================================================
 MultipleSoundCard Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to simply load and play multiple sounds.  This is about the simplest
 use of FMOD.
 This makes FMOD decode the into memory when it loads.  If the sounds are big and possibly take
 up a lot of ram, then it would be better to use the FMOD_CREATESTREAM flag so that it is 
 streamed in realtime as it plays.
===============================================================================================*/
#include "../../api/inc/fmod.h"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"
#include <stdio.h>


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
    FMOD_SYSTEM    *systemA, *systemB;
    FMOD_SOUND     *soundA, *soundB;
    FMOD_CHANNEL   *channelA = 0, *channelB = 0;
    FMOD_RESULT     result;
    int             key, count, numdrivers, driver;
    unsigned int    version;

    /*
        Create Sound Card A
    */
    result = FMOD_System_Create(&systemA);
    ERRCHECK(result);

    result = FMOD_System_GetVersion(systemA, &version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        getch();
        return 0;
    }

    result = FMOD_System_GetNumDrivers(systemA, &numdrivers);
    ERRCHECK(result);

    printf("---------------------------------------------------------\n");    
    printf("Select soundcard A\n");
    printf("---------------------------------------------------------\n");    
    for (count=0; count < numdrivers; count++)
    {
        char name[256];

        result = FMOD_System_GetDriverInfo(systemA, count, name, 256, 0);
        ERRCHECK(result);

        printf("%d : %s\n", count + 1, name);
    }
    printf("---------------------------------------------------------\n");
    printf("Press a corresponding number or ESC to quit\n");

    do
    {
        key = getch();
        if (key == 27)
        {
            return 0;
        }
        driver = key - '1';
    } while (driver < 0 || driver >= numdrivers);

    printf("\n");

    result = FMOD_System_SetDriver(systemA, driver);
    ERRCHECK(result);

    result = FMOD_System_Init(systemA, 32, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);



    /*
        Create Sound Card B
    */
    result = FMOD_System_Create(&systemB);
    ERRCHECK(result);

    result = FMOD_System_GetVersion(systemB, &version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        getch();
        return 0;
    }

    result = FMOD_System_GetNumDrivers(systemB, &numdrivers);
    ERRCHECK(result);

    printf("---------------------------------------------------------\n");    
    printf("Select soundcard B\n");
    printf("---------------------------------------------------------\n");    
    for (count=0; count < numdrivers; count++)
    {
        char name[256];

        result = FMOD_System_GetDriverInfo(systemB, count, name, 256, 0);
        ERRCHECK(result);

        printf("%d : %s\n", count + 1, name);
    }
    printf("---------------------------------------------------------\n");
    printf("Press a corresponding number or ESC to quit\n");

    do
    {
        key = getch();
        if (key == 27)
        {
            return 0;
        }
        driver = key - '1';
    } while (driver < 0 || driver >= numdrivers);

    printf("\n");

    result = FMOD_System_SetDriver(systemB, driver);
    ERRCHECK(result);

    result = FMOD_System_Init(systemB, 32, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);


    /*
        Load 1 sample into each soundcard.
    */
    result = FMOD_System_CreateSound(systemA, "../media/drumloop.wav", FMOD_HARDWARE, 0, &soundA);
    ERRCHECK(result);
    result = FMOD_Sound_SetMode(soundA, FMOD_LOOP_OFF);
    ERRCHECK(result);

    result = FMOD_System_CreateSound(systemB, "../media/jaguar.wav", FMOD_HARDWARE, 0,&soundB);
    ERRCHECK(result);

    printf("======================================================================\n");
    printf("MultipleSoundCard Example.  Copyright (c) Firelight Technologies 2004.\n");
    printf("======================================================================\n");
    printf("\n");
    printf("Press '1' to play a sound on soundcard A\n");
    printf("Press '2' to play a sound on soundcard B\n");
    printf("Press 'Esc' to quit\n");
    printf("\n");

    /*
        Main loop.
    */
    do
    {
        int  channelsplayingA = 0;
        int  channelsplayingB = 0;

        if (kbhit())
        {
            key = getch();

            switch (key)
            {
                case '1' :
                {
                    result = FMOD_System_PlaySound(systemA, FMOD_CHANNEL_FREE, soundA, 0, &channelA);
                    ERRCHECK(result);
                    break;
                }
                case '2' :
                {
                    result = FMOD_System_PlaySound(systemB, FMOD_CHANNEL_FREE, soundB, 0, &channelB);
                    ERRCHECK(result);
                    break;
                }
            }
        }

        FMOD_System_Update(systemA);
        FMOD_System_Update(systemB);

        FMOD_System_GetChannelsPlaying(systemA, &channelsplayingA);
        FMOD_System_GetChannelsPlaying(systemB, &channelsplayingB);

        printf("Channels Playing on A %2d.   Channels Playing on B %2d.\r", channelsplayingA, channelsplayingB);

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = FMOD_Sound_Release(soundA);
    ERRCHECK(result);
    result = FMOD_System_Close(systemA);
    ERRCHECK(result);
    result = FMOD_System_Release(systemA);
    ERRCHECK(result);

    result = FMOD_Sound_Release(soundB);
    ERRCHECK(result);
    result = FMOD_System_Close(systemB);
    ERRCHECK(result);
    result = FMOD_System_Release(systemB);
    ERRCHECK(result);

    return 0;
}


