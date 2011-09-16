/*===============================================================================================
 Submixing Example
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
    FMOD::Sound        *sound[5];
    FMOD::Channel      *channel[5];
    FMOD::ChannelGroup *groupA, *groupB, *masterGroup;
    FMOD::DSP          *dspreverb, *dspflange, *dsplowpass;
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

    result = system->createSound("../media/drumloop.wav", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound[0]);
    ERRCHECK(result);
    result = system->createSound("../media/jaguar.wav", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound[1]);
    ERRCHECK(result);
    result = system->createSound("../media/c.ogg", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound[2]);
    ERRCHECK(result);
    result = system->createSound("../media/d.ogg", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound[3]);
    ERRCHECK(result);
    result = system->createSound("../media/e.ogg", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound[4]);
    ERRCHECK(result);

    result = system->createChannelGroup("Group A", &groupA);
    ERRCHECK(result);

    result = system->createChannelGroup("Group B", &groupB);
    ERRCHECK(result);

    result = system->getMasterChannelGroup(&masterGroup);
    ERRCHECK(result);

    result = masterGroup->addGroup(groupA);
    ERRCHECK(result);

    result = masterGroup->addGroup(groupB);
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
        result = system->playSound(FMOD_CHANNEL_FREE, sound[count], true, &channel[count]);
        ERRCHECK(result);
        if (count < 2)
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
        Create the DSP effects we want to apply to our submixes.
    */  
    result = system->createDSPByType(FMOD_DSP_TYPE_SFXREVERB, &dspreverb);
    ERRCHECK(result);

    result = system->createDSPByType(FMOD_DSP_TYPE_FLANGE, &dspflange);
    ERRCHECK(result);
    result = dspflange->setParameter(FMOD_DSP_FLANGE_RATE, 1.0f);
    ERRCHECK(result);

    result = system->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &dsplowpass);
    ERRCHECK(result);
    result = dsplowpass->setParameter(FMOD_DSP_LOWPASS_CUTOFF, 500.0f);
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
                case 'r' : 
                case 'R' : 
                {
                    static bool reverb = true;

                    if (reverb)
                    {
                        groupA->addDSP(dspreverb, 0);
                    }
                    else
                    {
                        dspreverb->remove();
                    }

                    reverb = !reverb;
                    break;
                }
                case 'f' : 
                case 'F' : 
                {
                    static bool flange = true;

                    if (flange)
                    {
                        groupB->addDSP(dspflange, 0);
                    }
                    else
                    {
                        dspflange->remove();
                    }

                    flange = !flange;
                    break;
                }
                case 'l' : 
                case 'L' : 
                {
                    static bool lowpass = true;

                    if (lowpass)
                    {
                        masterGroup->addDSP(dsplowpass, 0);
                    }
                    else
                    {
                        dsplowpass->remove();
                    }

                    lowpass = !lowpass;
                    break;
                }
            }
        }

        system->update();

        {
            int  channelsplaying = 0;

            system->getChannelsPlaying(&channelsplaying);

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
        result = sound[count]->release();
        ERRCHECK(result);
    }

    result = dspreverb->release();
    ERRCHECK(result);
    result = dspflange->release();
    ERRCHECK(result);
    result = dsplowpass->release();
    ERRCHECK(result);

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


