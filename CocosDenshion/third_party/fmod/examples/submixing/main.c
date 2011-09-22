/*===============================================================================================
 Submixing Example
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
    FMOD_SOUND        *sound[5];
    FMOD_CHANNEL      *channel[5];
    FMOD_CHANNELGROUP *groupA, *groupB, *masterGroup;
    FMOD_DSP          *dspreverb, *dspflange, *dsplowpass;
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

    result = FMOD_System_CreateSound(system, "../media/drumloop.wav", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound[0]);
    ERRCHECK(result);
    result = FMOD_System_CreateSound(system, "../media/jaguar.wav", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound[1]);
    ERRCHECK(result);
    result = FMOD_System_CreateSound(system, "../media/c.ogg", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound[2]);
    ERRCHECK(result);
    result = FMOD_System_CreateSound(system, "../media/d.ogg", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound[3]);
    ERRCHECK(result);
    result = FMOD_System_CreateSound(system, "../media/e.ogg", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound[4]);
    ERRCHECK(result);

    result = FMOD_System_CreateChannelGroup(system, "Group A", &groupA);
    ERRCHECK(result);

    result = FMOD_System_CreateChannelGroup(system, "Group B", &groupB);
    ERRCHECK(result);

    result = FMOD_System_GetMasterChannelGroup(system, &masterGroup);
    ERRCHECK(result);

    result = FMOD_ChannelGroup_AddGroup(masterGroup, groupA);
    ERRCHECK(result);

    result = FMOD_ChannelGroup_AddGroup(masterGroup, groupB);
    ERRCHECK(result);

    printf("======================================================================\n");
    printf("Sub-mixing example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("======================================================================\n");
    printf("                                                       (drumloop.wav) \n");
    printf("                                                      /               \n");
    printf("                                              (groupA)                \n");
    printf("                                     (reverb)/        \\               \n");
    printf("                                    /                  (jaguar.wav)   \n");
    printf("(soundcard)--(lowpass)--(mastergroup)                                  \n");
    printf("                                    \\                  (c.ogg)        \n");
    printf("                                     (flange)         /                \n");
    printf("                                             \\(groupB)--(d.ogg)       \n");
    printf("                                                      \\               \n");
    printf("                                                       (e.ogg)        \n");
    printf("Press 'A' to mute/unmute group A\n");
    printf("Press 'B' to mute/unmute group B\n");
    printf("\n");
    printf("Press 'R' to place reverb on group A\n");
    printf("Press 'F' to place flange on group B\n");
    printf("Press 'L' to place lowpass on master group (everything)\n");
    printf("Press 'Esc' to quit\n");
    printf("\n");

    /*
        Start all the sounds!
    */
    for (count = 0; count < 5; count++)
    {
        result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound[count], TRUE, &channel[count]);
        ERRCHECK(result);
        if (count < 2)
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
        Create the DSP effects we want to apply to our submixes.
    */  
    result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_SFXREVERB, &dspreverb);
    ERRCHECK(result);

    result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_FLANGE, &dspflange);
    ERRCHECK(result);
    result = FMOD_DSP_SetParameter(dspflange, FMOD_DSP_FLANGE_RATE, 1.0f);
    ERRCHECK(result);

    result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_LOWPASS, &dsplowpass);
    ERRCHECK(result);
    result = FMOD_DSP_SetParameter(dsplowpass, FMOD_DSP_LOWPASS_CUTOFF, 500.0f);
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
                case 'r' : 
                case 'R' : 
                {
                    static int reverb = TRUE;

                    if (reverb)
                    {
                        FMOD_ChannelGroup_AddDSP(groupA, dspreverb, 0);
                    }
                    else
                    {
                        FMOD_DSP_Remove(dspreverb);
                    }

                    reverb = !reverb;
                    break;
                }
                case 'f' : 
                case 'F' : 
                {
                    static int flange = TRUE;

                    if (flange)
                    {
                        FMOD_ChannelGroup_AddDSP(groupB, dspflange, 0);
                    }
                    else
                    {
                        FMOD_DSP_Remove(dspflange);
                    }

                    flange = !flange;
                    break;
                }
                case 'l' : 
                case 'L' : 
                {
                    static int lowpass = TRUE;

                    if (lowpass)
                    {
                        FMOD_ChannelGroup_AddDSP(masterGroup, dsplowpass, 0);
                    }
                    else
                    {
                        FMOD_DSP_Remove(dsplowpass);
                    }

                    lowpass = !lowpass;
                    break;
                }
            }
        }

        FMOD_System_Update(system);

        {
            int  channelsplaying = 0;

            FMOD_System_GetChannelsPlaying(system, &channelsplaying);

            printf("Channels Playing %2d\r", channelsplaying);
            fflush(stdout);
        }

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    for (count = 0; count < 5; count++)
    {
        result = FMOD_Sound_Release(sound[count]);
        ERRCHECK(result);
    }

    result = FMOD_DSP_Release(dspreverb);
    ERRCHECK(result);
    result = FMOD_DSP_Release(dspflange);
    ERRCHECK(result);
    result = FMOD_DSP_Release(dsplowpass);
    ERRCHECK(result);

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


