/*===============================================================================================
 Effects Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to apply some of the built in software effects to sounds. 
 This example filters the global mix.  All software sounds played here would be filtered in the 
 same way.
 To filter per channel, and not have other channels affected, simply replace FMOD_System_AddDSP with
 FMOD_Channel_AddDSP.
 Note in this example you don't have to add and remove units each time, you could simply add them 
 all at the start then use FMOD_DSP_SetActive to toggle them on and off.
===============================================================================================*/
#include "../../api/inc/fmod.h"
#include "../../api/inc/fmod_dsp.h"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"


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
    FMOD_SYSTEM     *system        = 0;
    FMOD_SOUND      *sound         = 0;
    FMOD_CHANNEL    *channel       = 0;
    FMOD_DSP        *dsplowpass    = 0;
    FMOD_DSP        *dsphighpass   = 0;
    FMOD_DSP        *dspecho       = 0;
    FMOD_DSP        *dspflange     = 0;
    FMOD_DSP        *dspdistortion = 0;
    FMOD_DSP        *dspchorus     = 0;
    FMOD_DSP        *dspparameq    = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;

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

    result = FMOD_System_CreateSound(system, "../media/drumloop.wav", FMOD_SOFTWARE, 0, &sound);
    ERRCHECK(result);

    printf("=================================================================\n");
    printf("Effects Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("=================================================================\n");
    printf("\n");
    printf("Press SPACE to paused/unpause sound.\n");
    printf("Press 1 to toggle dsplowpass effect.\n");
    printf("Press 2 to toggle dsphighpass effect.\n");
    printf("Press 3 to toggle dspecho effect.\n");
    printf("Press 4 to toggle dspflange effect.\n");
    printf("Press 5 to toggle dspdistortion effect.\n");
    printf("Press 6 to toggle dspchorus effect.\n");
    printf("Press 7 to toggle dspparameq effect.\n");
    printf("Press 'Esc' to quit\n");
    printf("\n");

    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
    ERRCHECK(result);

    /*
        Create some effects to play with.
    */
    result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_LOWPASS, &dsplowpass);
    ERRCHECK(result);
    result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_HIGHPASS, &dsphighpass);
    ERRCHECK(result);
    result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_ECHO, &dspecho);
    ERRCHECK(result);
    result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_FLANGE, &dspflange);
    ERRCHECK(result);
    result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_DISTORTION, &dspdistortion);
    ERRCHECK(result);
    result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_CHORUS, &dspchorus);
    ERRCHECK(result);
    result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_PARAMEQ, &dspparameq);
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
                case ' ' :
                {
                    int paused;

                    FMOD_Channel_GetPaused(channel, &paused);
                    ERRCHECK(result);

                    paused = !paused;

                    result = FMOD_Channel_SetPaused(channel, paused);
                    ERRCHECK(result);
                    break;
                }
                case '1' :
                {
                    int active;

                    result = FMOD_DSP_GetActive(dsplowpass, &active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = FMOD_DSP_Remove(dsplowpass);
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = FMOD_System_AddDSP(system, dsplowpass, 0);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '2' :
                {
                    int active;

                    result = FMOD_DSP_GetActive(dsphighpass, &active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = FMOD_DSP_Remove(dsphighpass);
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = FMOD_System_AddDSP(system, dsphighpass, 0);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '3' :
                {
                    int active;

                    result = FMOD_DSP_GetActive(dspecho, &active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = FMOD_DSP_Remove(dspecho);
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = FMOD_System_AddDSP(system, dspecho, 0);
                        ERRCHECK(result);

                        result = FMOD_DSP_SetParameter(dspecho, FMOD_DSP_ECHO_DELAY, 50.0f);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '4' :
                {
                    int active;

                    result = FMOD_DSP_GetActive(dspflange, &active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = FMOD_DSP_Remove(dspflange);
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = FMOD_System_AddDSP(system, dspflange, 0);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '5' :
                {
                    int active;

                    result = FMOD_DSP_GetActive(dspdistortion, &active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = FMOD_DSP_Remove(dspdistortion);
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = FMOD_System_AddDSP(system, dspdistortion, 0);
                        ERRCHECK(result);

                        result = FMOD_DSP_SetParameter(dspdistortion, FMOD_DSP_DISTORTION_LEVEL, 0.8f);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '6' :
                {
                    int active;

                    result = FMOD_DSP_GetActive(dspchorus, &active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = FMOD_DSP_Remove(dspchorus);
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = FMOD_System_AddDSP(system, dspchorus, 0);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '7' :
                {
                    int active;

                    result = FMOD_DSP_GetActive(dspparameq, &active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = FMOD_DSP_Remove(dspparameq);
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = FMOD_System_AddDSP(system, dspparameq, 0);
                        ERRCHECK(result);

                        result = FMOD_DSP_SetParameter(dspparameq, FMOD_DSP_PARAMEQ_CENTER, 5000.0f);
                        ERRCHECK(result);
                        result = FMOD_DSP_SetParameter(dspparameq, FMOD_DSP_PARAMEQ_GAIN, 0.0f);
                        ERRCHECK(result);
                    }
                    break;
                }
            }
        }

        FMOD_System_Update(system);

        {
            int paused = 0;
            int dsplowpass_active;
            int dsphighpass_active;
            int dspecho_active;
            int dspflange_active;
            int dspdistortion_active;
            int dspchorus_active;
            int dspparameq_active;

            FMOD_DSP_GetActive(dsplowpass   , &dsplowpass_active);
            FMOD_DSP_GetActive(dsphighpass  , &dsphighpass_active);
            FMOD_DSP_GetActive(dspecho      , &dspecho_active);
            FMOD_DSP_GetActive(dspflange    , &dspflange_active);
            FMOD_DSP_GetActive(dspdistortion, &dspdistortion_active);
            FMOD_DSP_GetActive(dspchorus    , &dspchorus_active);
            FMOD_DSP_GetActive(dspparameq   , &dspparameq_active);

            if (channel)
            {
                result = FMOD_Channel_GetPaused(channel, &paused);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }
            }

            printf("%s : lowpass[%c] highpass[%c] echo[%c] flange[%c] dist[%c] chorus[%c] parameq[%c]\r", 
                    paused ? "Paused " : "Playing",
                    dsplowpass_active ? 'x' : ' ',
                    dsphighpass_active ? 'x' : ' ',
                    dspecho_active ? 'x' : ' ',
                    dspflange_active ? 'x' : ' ',
                    dspdistortion_active ? 'x' : ' ',
                    dspchorus_active ? 'x' : ' ',
                    dspparameq_active ? 'x' : ' ');
            fflush(stdout);
        }

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = FMOD_Sound_Release(sound);
    ERRCHECK(result);
    result = FMOD_System_Close(system);
    ERRCHECK(result);
    result = FMOD_System_Release(system);
    ERRCHECK(result);

    return 0;
}


