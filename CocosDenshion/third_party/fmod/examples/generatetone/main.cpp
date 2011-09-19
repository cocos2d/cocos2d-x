/*===============================================================================================
 GenerateTone Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how simply play generated tones using FMOD::System::payDSP instead of 
 manually connecting and disconnecting DSP units.
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
    FMOD::System    *system;
    FMOD::Channel   *channel = 0;
    FMOD::DSP       *dsp     = 0;
    FMOD_RESULT      result;
    int              key;
    unsigned int     version;

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
        getch();
        return 0;
    }

    result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    /*
        Create an oscillator DSP unit for the tone.
    */
    result = system->createDSPByType(FMOD_DSP_TYPE_OSCILLATOR, &dsp);
    ERRCHECK(result);
    result = dsp->setParameter(FMOD_DSP_OSCILLATOR_RATE, 440.0f);
    ERRCHECK(result);

    printf("======================================================================\n");
    printf("GenerateTone Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("======================================================================\n\n");
    printf("\n");
    printf("Press '1' to play a sine wave\n");
    printf("Press '2' to play a square wave\n");
    printf("Press '3' to play a triangle wave\n");
    printf("Press '4' to play a saw wave\n");
    printf("Press '5' to play a white noise\n");
    printf("Press 's' to stop channel\n");
    printf("\n");
    printf("Press 'v'/'V' to change channel volume\n");
    printf("Press 'f'/'F' to change channel frequency\n");
    printf("Press '['/']' to change channel pan\n");
    printf("Press 'Esc' to quit\n");
    printf("\n");

    /*
        Main loop
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
                    result = system->playDSP(FMOD_CHANNEL_REUSE, dsp, true, &channel);

                    channel->setVolume(0.5f);
                    result = dsp->setParameter(FMOD_DSP_OSCILLATOR_TYPE, 0);
                    ERRCHECK(result);
                    channel->setPaused(false);
                    break;
                }
                case '2' :
                {
                    result = system->playDSP(FMOD_CHANNEL_REUSE, dsp, true, &channel);

                    channel->setVolume(0.125f);
                    result = dsp->setParameter(FMOD_DSP_OSCILLATOR_TYPE, 1);
                    ERRCHECK(result);
                    channel->setPaused(false);
                    break;
                }
                case '3' :
                {
                    result = system->playDSP(FMOD_CHANNEL_REUSE, dsp, true, &channel);

                    channel->setVolume(0.5f);
                    result = dsp->setParameter(FMOD_DSP_OSCILLATOR_TYPE, 2);
                    ERRCHECK(result);
                    channel->setPaused(false);
                    break;
                }
                case '4' :
                {
                    result = system->playDSP(FMOD_CHANNEL_REUSE, dsp, true, &channel);

                    channel->setVolume(0.125f);
                    result = dsp->setParameter(FMOD_DSP_OSCILLATOR_TYPE, 4);
                    ERRCHECK(result);
                    channel->setPaused(false);
                    break;
                }
                case '5' :
                {
                    result = system->playDSP(FMOD_CHANNEL_REUSE, dsp, true, &channel);

                    channel->setVolume(0.25f);
                    result = dsp->setParameter(FMOD_DSP_OSCILLATOR_TYPE, 5);
                    ERRCHECK(result);
                    channel->setPaused(false);
                    break;
                }
                case 's' :
                {
                    channel->stop();
                    break;
                }
                case 'v' :
                {
                    float volume;

                    channel->getVolume(&volume);
                    volume -= 0.1f;
                    channel->setVolume(volume);
                    break;
                }
                case 'V' :
                {
                    float volume;

                    channel->getVolume(&volume);
                    volume += 0.1f;
                    channel->setVolume(volume);
                    break;
                }
                case 'f' :
                {
                    float frequency;

                    channel->getFrequency(&frequency);
                    frequency -= 500.0f;
                    channel->setFrequency(frequency);
                    break;
                }
                case 'F' :
                {
                    float frequency;

                    channel->getFrequency(&frequency);
                    frequency += 500.0f;
                    channel->setFrequency(frequency);
                    break;
                }
                case '[' :
                {
                    float pan;

                    channel->getPan(&pan);
                    pan -= 0.1f;
                    channel->setPan(pan);
                    break;
                }
                case ']' :
                {
                    float pan;

                    channel->getPan(&pan);
                    pan += 0.1f;
                    channel->setPan(pan);
                    break;
                }
            }
        }

        system->update();

        {
            float frequency = 0, volume = 0, pan = 0;
            bool playing = false;

            if (channel)
            {
                channel->getFrequency(&frequency);
                channel->getVolume(&volume);
                channel->getPan(&pan);
                channel->isPlaying(&playing);
            }

            printf("Channel %s : Frequency %.1f Volume %.1f Pan %.1f  \r", playing ? "playing" : "stopped", frequency, volume, pan);
            fflush(stdout);
        }
        
        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = dsp->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    return 0;
}
