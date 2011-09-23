/*===============================================================================================
 ChannelGroups Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to put channels into channel groups, so that you can affect a group
 of channels at a time instead of just one channel at a time.
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
    FMOD::System       *system;
    FMOD::Sound        *sound[6];
    FMOD::Channel      *channel[6];
    FMOD::ChannelGroup *groupA, *groupB, *masterGroup;
    FMOD_RESULT         result;
    int                 key, count;
    unsigned int        version;

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

    result = system->createSound("../media/drumloop.wav", FMOD_LOOP_NORMAL, 0, &sound[0]);
    ERRCHECK(result);
    result = system->createSound("../media/jaguar.wav", FMOD_LOOP_NORMAL, 0, &sound[1]);
    ERRCHECK(result);
    result = system->createSound("../media/swish.wav", FMOD_LOOP_NORMAL, 0, &sound[2]);
    ERRCHECK(result);
    result = system->createSound("../media/c.ogg", FMOD_LOOP_NORMAL, 0, &sound[3]);
    ERRCHECK(result);
    result = system->createSound("../media/d.ogg", FMOD_LOOP_NORMAL, 0, &sound[4]);
    ERRCHECK(result);
    result = system->createSound("../media/e.ogg", FMOD_LOOP_NORMAL, 0, &sound[5]);
    ERRCHECK(result);

    result = system->createChannelGroup("Group A", &groupA);
    ERRCHECK(result);

    result = system->createChannelGroup("Group B", &groupB);
    ERRCHECK(result);

    result = system->getMasterChannelGroup(&masterGroup);
    ERRCHECK(result);

    printf("=======================================================================\n");
    printf("ChannelGroups Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("=======================================================================\n");
    printf("\n");
    printf("Group A : drumloop.wav, jaguar.wav, swish.wav\n");
    printf("Group B : c.ogg, d.ogg, e.ogg\n");
    printf("\n");
    printf("Press 'A' to mute/unmute group A\n");
    printf("Press 'B' to mute/unmute group B\n");
    printf("Press 'C' to mute/unmute group A and B (master group)\n");
    printf("Press 'Esc' to quit\n");
    printf("\n");

    /*
        Instead of being independent, set the group A and B to be children of the master group.
    */
    result = masterGroup->addGroup(groupA);
    ERRCHECK(result);

    result = masterGroup->addGroup(groupB);
    ERRCHECK(result);

    /*
        Start all the sounds!
    */
    for (count = 0; count < 6; count++)
    {
        result = system->playSound(FMOD_CHANNEL_FREE, sound[count], true, &channel[count]);
        ERRCHECK(result);
        if (count < 3)
        {
            result = channel[count]->setChannelGroup(groupA);
        }
        else
        {
            result = channel[count]->setChannelGroup(groupB);
        }
        ERRCHECK(result);
        result = channel[count]->setPaused(false);
        ERRCHECK(result);
    }   

    /*
        Change the volume of each group, just because we can!  (And makes it less noise).
    */
    result = groupA->setVolume(0.5f);
    ERRCHECK(result);
    result = groupB->setVolume(0.5f);
    ERRCHECK(result);

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
                case 'a' : 
                case 'A' : 
                {
                    static bool mute = true;

                    groupA->setMute(mute);

                    mute = !mute;
                    break;
                }
                case 'b' : 
                case 'B' : 
                {
                    static bool mute = true;

                    groupB->setMute(mute);

                    mute = !mute;
                    break;
                }
                case 'c' : 
                case 'C' : 
                {
                    static bool mute = true;

                    masterGroup->setMute(mute);

                    mute = !mute;
                    break;
                }
            }
        }

        system->update();

        {
            int  channelsplaying = 0;

            system->getChannelsPlaying(&channelsplaying);

            printf("Channels Playing %2d\r", channelsplaying);
        }

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        A little fade out. (over 2 seconds)
    */
    printf("Goodbye!\n");
    {
        float pitch = 1.0f;
        float vol = 1.0f;

        for (count = 0; count < 200; count++)
        {
            masterGroup->setPitch(pitch);
            masterGroup->setVolume(vol);

            vol   -= (1.0f / 200.0f);
            pitch -= (0.5f / 200.0f);

            Sleep(10);
        }
    }

    /*
        Shut down
    */
    for (count = 0; count < 6; count++)
    {
        result = sound[count]->release();
        ERRCHECK(result);
    }

    result = groupA->release();
    ERRCHECK(result);
    result = groupB->release();
    ERRCHECK(result);

    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    return 0;
}


