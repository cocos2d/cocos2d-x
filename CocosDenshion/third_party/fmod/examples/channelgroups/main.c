/*===============================================================================================
 ChannelGroups Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to put channels into channel groups, so that you can affect a group
 of channels at a time instead of just one channel at a time.
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
    FMOD_SYSTEM       *system;
    FMOD_SOUND        *sound[6];
    FMOD_CHANNEL      *channel[6];
    FMOD_CHANNELGROUP *groupA, *groupB, *masterGroup;
    FMOD_RESULT        result;
    int                key, count;
    unsigned int       version;

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

    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    result = FMOD_System_CreateSound(system, "../media/drumloop.wav", FMOD_LOOP_NORMAL, 0, &sound[0]);
    ERRCHECK(result);
    result = FMOD_System_CreateSound(system, "../media/jaguar.wav", FMOD_LOOP_NORMAL, 0, &sound[1]);
    ERRCHECK(result);
    result = FMOD_System_CreateSound(system, "../media/swish.wav", FMOD_LOOP_NORMAL, 0, &sound[2]);
    ERRCHECK(result);
    result = FMOD_System_CreateSound(system, "../media/c.ogg", FMOD_LOOP_NORMAL, 0, &sound[3]);
    ERRCHECK(result);
    result = FMOD_System_CreateSound(system, "../media/d.ogg", FMOD_LOOP_NORMAL, 0, &sound[4]);
    ERRCHECK(result);
    result = FMOD_System_CreateSound(system, "../media/e.ogg", FMOD_LOOP_NORMAL, 0, &sound[5]);
    ERRCHECK(result);

    result = FMOD_System_CreateChannelGroup(system, "Group A", &groupA);
    ERRCHECK(result);

    result = FMOD_System_CreateChannelGroup(system, "Group B", &groupB);
    ERRCHECK(result);

    result = FMOD_System_GetMasterChannelGroup(system, &masterGroup);
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
    result = FMOD_ChannelGroup_AddGroup(masterGroup, groupA);
    ERRCHECK(result);

    result = FMOD_ChannelGroup_AddGroup(masterGroup, groupB);
    ERRCHECK(result);

    /*
        Start all the sounds!
    */
    for (count = 0; count < 6; count++)
    {
        result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound[count], TRUE, &channel[count]);
        ERRCHECK(result);
        if (count < 3)
        {
            result = FMOD_Channel_SetChannelGroup(channel[count], groupA);
        }
        else
        {
            result = FMOD_Channel_SetChannelGroup(channel[count], groupB);
        }
        ERRCHECK(result);
        result = FMOD_Channel_SetPaused(channel[count], FALSE);
        ERRCHECK(result);
    }

    /*
        Change the volume of each group, just because we can!  (And makes it less of a loud noise).
    */
    result = FMOD_ChannelGroup_SetVolume(groupA, 0.5f);
    ERRCHECK(result);
    result = FMOD_ChannelGroup_SetVolume(groupB, 0.5f);
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
                    static int mute = TRUE;

                    FMOD_ChannelGroup_SetMute(groupA, mute);

                    mute = !mute;
                    break;
                }
                case 'b' : 
                case 'B' : 
                {
                    static int mute = TRUE;

                    FMOD_ChannelGroup_SetMute(groupB, mute);

                    mute = !mute;
                    break;
                }
                case 'c' : 
                case 'C' : 
                {
                    static int mute = TRUE;

                    FMOD_ChannelGroup_SetMute(masterGroup, mute);

                    mute = !mute;
                    break;
                }
            }
        }

        FMOD_System_Update(system);

        {
            int  channelsplaying = 0;

            FMOD_System_GetChannelsPlaying(system, &channelsplaying);

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
            FMOD_ChannelGroup_SetPitch(masterGroup, pitch);
            FMOD_ChannelGroup_SetVolume(masterGroup, vol);

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
        result = FMOD_Sound_Release(sound[count]);
        ERRCHECK(result);
    }

    result = FMOD_ChannelGroup_Release(groupA);
    ERRCHECK(result);
    result = FMOD_ChannelGroup_Release(groupB);
    ERRCHECK(result);

    result = FMOD_System_Close(system);
    ERRCHECK(result);
    result = FMOD_System_Release(system);
    ERRCHECK(result);

    return 0;
}


