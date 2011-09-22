/*===============================================================================================
 GenerateTone Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how simply play generated tones using FMOD_System_PlayDSP instead of 
 manually connecting and disconnecting DSP units.
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
    FMOD_SYSTEM    *system;
    FMOD_CHANNEL   *channel = 0;
    FMOD_DSP       *dsp     = 0;
    FMOD_RESULT     result;
    int             key;
    unsigned int    version;

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
        getch();
        return 0;
    }

    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);

    /*
        Create DSP units for each type of noise we want.
    */
    result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_OSCILLATOR, &dsp);
    ERRCHECK(result);
    result = FMOD_DSP_SetParameter(dsp, FMOD_DSP_OSCILLATOR_RATE, 440.0f);
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
                    result = FMOD_System_PlayDSP(system, FMOD_CHANNEL_REUSE, dsp, TRUE, &channel);
                    
                    FMOD_Channel_SetVolume(channel, 0.5f);
                    result = FMOD_DSP_SetParameter(dsp, FMOD_DSP_OSCILLATOR_TYPE, 0);
                    ERRCHECK(result);
                    FMOD_Channel_SetPaused(channel, FALSE);
                    break;
                }
                case '2' :
                {
                    result = FMOD_System_PlayDSP(system, FMOD_CHANNEL_REUSE, dsp, TRUE, &channel);
                    FMOD_Channel_SetVolume(channel, 0.125f);
                    result = FMOD_DSP_SetParameter(dsp, FMOD_DSP_OSCILLATOR_TYPE, 1);
                    ERRCHECK(result);
                    FMOD_Channel_SetPaused(channel, FALSE);
                    break;
                }
                case '3' :
                {
                    result = FMOD_System_PlayDSP(system, FMOD_CHANNEL_REUSE, dsp, TRUE, &channel);
                    FMOD_Channel_SetVolume(channel, 0.5f);
                    result = FMOD_DSP_SetParameter(dsp, FMOD_DSP_OSCILLATOR_TYPE, 2);
                    ERRCHECK(result);
                    FMOD_Channel_SetPaused(channel, FALSE);
                    break;
                }
                case '4' :
                {
                    result = FMOD_System_PlayDSP(system, FMOD_CHANNEL_REUSE, dsp, TRUE, &channel);
                    FMOD_Channel_SetVolume(channel, 0.125f);
                    result = FMOD_DSP_SetParameter(dsp, FMOD_DSP_OSCILLATOR_TYPE, 4);
                    ERRCHECK(result);
                    FMOD_Channel_SetPaused(channel, FALSE);
                    break;
                }
                case '5' :
                {
                    result = FMOD_System_PlayDSP(system, FMOD_CHANNEL_REUSE, dsp, TRUE, &channel);
                    FMOD_Channel_SetVolume(channel, 0.25f);
                    result = FMOD_DSP_SetParameter(dsp, FMOD_DSP_OSCILLATOR_TYPE, 5);
                    ERRCHECK(result);
                    FMOD_Channel_SetPaused(channel, FALSE);
                    break;
                }
                case 's' :
                {
                    FMOD_Channel_Stop(channel);
                    break;
                }
                case 'v' :
                {
                    float volume;

                    FMOD_Channel_GetVolume(channel, &volume);
                    volume -= 0.1f;
                    FMOD_Channel_SetVolume(channel, volume);
                    break;
                }
                case 'V' :
                {
                    float volume;

                    FMOD_Channel_GetVolume(channel, &volume);
                    volume += 0.1f;
                    FMOD_Channel_SetVolume(channel, volume);
                    break;
                }
                case 'f' :
                {
                    float frequency;

                    FMOD_Channel_GetFrequency(channel, &frequency);
                    frequency -= 500.0f;
                    FMOD_Channel_SetFrequency(channel, frequency);
                    break;
                }
                case 'F' :
                {
                    float frequency;

                    FMOD_Channel_GetFrequency(channel, &frequency);
                    frequency += 500.0f;
                    FMOD_Channel_SetFrequency(channel, frequency);
                    break;
                }
                case '[' :
                {
                    float pan;

                    FMOD_Channel_GetPan(channel, &pan);
                    pan -= 0.1f;
                    FMOD_Channel_SetPan(channel, pan);
                    break;
                }
                case ']' :
                {
                    float pan;

                    FMOD_Channel_GetPan(channel, &pan);
                    pan += 0.1f;
                    FMOD_Channel_SetPan(channel, pan);
                    break;
                }
            }
        }

        FMOD_System_Update(system);

        {
            float frequency = 0, volume = 0, pan = 0;
            int playing = FALSE;

            if (channel)
            {
                FMOD_Channel_GetFrequency(channel, &frequency);
                FMOD_Channel_GetVolume(channel, &volume);
                FMOD_Channel_GetPan(channel, &pan);
                FMOD_Channel_IsPlaying(channel, &playing);
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
    result = FMOD_DSP_Release(dsp);
    ERRCHECK(result);
    result = FMOD_System_Close(system);
    ERRCHECK(result);
    result = FMOD_System_Release(system);
    ERRCHECK(result);

    return 0;
}
