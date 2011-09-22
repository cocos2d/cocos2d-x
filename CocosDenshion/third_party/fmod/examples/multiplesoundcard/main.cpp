/*===============================================================================================
 MultipleSoundCard Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to play sounds on 2 different sound cards from the same application.
 It creates 2 FMOD::System objects, selects a different sound device for each, then allows
 the user to play 1 sound on 1 soundcard and another sound on another soundcard.

 Note that sounds created on device A cannot be played on device B and vice versa.
 You will have to each sound separately for each sound card.  Device A might load the sound
 into its own memory so obviously device B wouldnt be able to play it.
===============================================================================================*/
#include "../../api/inc/fmod.hpp"
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
    FMOD::System     *systemA, *systemB;
    FMOD::Sound      *soundA, *soundB;
    FMOD::Channel    *channelA = 0, *channelB = 0;;
    FMOD_RESULT       result;
    int               key, count, numdrivers, driver;
    unsigned int      version;

    /*
        Create Sound Card A
    */
    result = FMOD::System_Create(&systemA);
    ERRCHECK(result);

    result = systemA->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        getch();
        return 0;
    }

    result = systemA->getNumDrivers(&numdrivers);
    ERRCHECK(result);

    printf("---------------------------------------------------------\n");    
    printf("Select soundcard A\n");
    printf("---------------------------------------------------------\n");    
    for (count=0; count < numdrivers; count++)
    {
        char name[256];

        result = systemA->getDriverInfo(count, name, 256, 0);
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

    result = systemA->setDriver(driver);
    ERRCHECK(result);

    result = systemA->init(32, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);



    /*
        Create Sound Card B
    */
    result = FMOD::System_Create(&systemB);
    ERRCHECK(result);

    result = systemB->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        getch();
        return 0;
    }

    result = systemB->getNumDrivers(&numdrivers);
    ERRCHECK(result);

    printf("---------------------------------------------------------\n");    
    printf("Select soundcard B\n");
    printf("---------------------------------------------------------\n");    
    for (count=0; count < numdrivers; count++)
    {
        char name[256];

        result = systemB->getDriverInfo(count, name, 256, 0);
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

    result = systemB->setDriver(driver);
    ERRCHECK(result);

    result = systemB->init(32, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);


    /*
        Load 1 sample into each soundcard.
    */
    result = systemA->createSound("../media/drumloop.wav", FMOD_HARDWARE, 0, &soundA);
    ERRCHECK(result);
    result = soundA->setMode(FMOD_LOOP_OFF);
    ERRCHECK(result);

    result = systemB->createSound("../media/jaguar.wav", FMOD_HARDWARE, 0, &soundB);
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
                    result = systemA->playSound(FMOD_CHANNEL_FREE, soundA, 0, &channelA);
                    ERRCHECK(result);
                    break;
                }
                case '2' :
                {
                    result = systemB->playSound(FMOD_CHANNEL_FREE, soundB, 0, &channelB);
                    ERRCHECK(result);
                    break;
                }
            }
        }

        systemA->update();
        systemB->update();

        systemA->getChannelsPlaying(&channelsplayingA);
        systemB->getChannelsPlaying(&channelsplayingB);

        printf("Channels Playing on A %2d.   Channels Playing on B %2d.\r", channelsplayingA, channelsplayingB);

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = soundA->release();
    ERRCHECK(result);
    result = systemA->close();
    ERRCHECK(result);
    result = systemA->release();
    ERRCHECK(result);

    result = soundB->release();
    ERRCHECK(result);
    result = systemB->close();
    ERRCHECK(result);
    result = systemB->release();
    ERRCHECK(result);

    return 0;
}


