/*===============================================================================================
 3d Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to basic 3d positioning
===============================================================================================*/
#include "../../api/inc/fmod.h"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"
#include <stdio.h>
#include <math.h>


const int INTERFACE_UPDATETIME = 50;        // 50ms update for interface


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
    FMOD_SYSTEM     *system;
    FMOD_SOUND      *sound1, *sound2, *sound3;
    FMOD_CHANNEL    *channel1 = 0, *channel2 = 0, *channel3 = 0;
    FMOD_RESULT      result;
    int              key;
    int              listenerflag = TRUE;
    FMOD_VECTOR      listenerpos  = { 0.0f, 0.0f, 0.0f }; 
    unsigned int     version;

    printf("===============================================================\n");
    printf("3d Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("===============================================================\n");
    printf("This example plays 2 3D sounds in software.  Optionally you can\n");
    printf("play a 2D software sound as well.\n");
    printf("Hardware sounds are not supported on Linux\n");
    printf("===============================================================\n\n");

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

    result = FMOD_System_Init(system, 10, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);

    /*
        Load some sounds
    */
    result = FMOD_System_CreateSound(system, "../media/drumloop.wav", FMOD_SOFTWARE | FMOD_3D, 0, &sound1);
    ERRCHECK(result);
    result = FMOD_Sound_Set3DMinMaxDistance(sound1, 4.0f, 10000.0f);
    ERRCHECK(result);
    result = FMOD_Sound_SetMode(sound1, FMOD_LOOP_NORMAL);
    ERRCHECK(result);

    result = FMOD_System_CreateSound(system, "../media/jaguar.wav", FMOD_SOFTWARE | FMOD_3D, 0, &sound2);
    ERRCHECK(result);
    result = FMOD_Sound_Set3DMinMaxDistance(sound2, 4.0f, 10000.0f);
    ERRCHECK(result);
    result = FMOD_Sound_SetMode(sound2, FMOD_LOOP_NORMAL);
    ERRCHECK(result);

    result = FMOD_System_CreateSound(system, "../media/swish.wav", FMOD_SOFTWARE | FMOD_2D, 0, &sound3);
    ERRCHECK(result);

    /*
        Play sounds at certain positions
    */
    {
        FMOD_VECTOR pos = { -10.0f, -0.0f, 0.0f };
        FMOD_VECTOR vel = {   0.0f,  0.0f, 0.0f };

        result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound1, TRUE, &channel1);
        ERRCHECK(result);
        result = FMOD_Channel_Set3DAttributes(channel1, &pos, &vel);
        ERRCHECK(result);
        result = FMOD_Channel_SetPaused(channel1, FALSE);
        ERRCHECK(result);
    }

    {
        FMOD_VECTOR pos = { 15.0f, -0.0f, -0.0f };
        FMOD_VECTOR vel = {  0.0f,  0.0f,  0.0f };

        result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound2, TRUE, &channel2);
        ERRCHECK(result);
        result = FMOD_Channel_Set3DAttributes(channel2, &pos, &vel);
        ERRCHECK(result);
        result = FMOD_Channel_SetPaused(channel2, FALSE);
        ERRCHECK(result);
    }

    /*
        Display help
    */
    {
        int numchannels;

        result = FMOD_System_GetHardwareChannels(system, &numchannels);
        ERRCHECK(result);
    
        printf("Hardware channels : %d\n", numchannels);
    }

    printf("=========================================================================\n");
    printf("Press 1        Pause/Unpause 16bit 3D sound at any time\n");
    printf("      2        Pause/Unpause 8bit 3D sound at any time\n");
    printf("      3        Play 16bit STEREO 2D sound at any time\n");
    printf("      <        Move listener left (in still mode)\n");
    printf("      >        Move listener right (in still mode)\n");
    printf("      SPACE    Stop/Start listener automatic movement\n");
    printf("      ESC      Quit\n");
    printf("=========================================================================\n");

    /*
        Main loop
    */
    do
    {
        if (kbhit())
        {
            key = getch();

            if (key == '1') 
            {
                int paused;
                FMOD_Channel_GetPaused(channel1, &paused);
                FMOD_Channel_SetPaused(channel1, !paused);
            }

            if (key == '2') 
            {
                int paused;
                FMOD_Channel_GetPaused(channel2, &paused);
                FMOD_Channel_SetPaused(channel2, !paused);
            }

            if (key == '3') 
            {
                result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound3, FALSE, &channel3);
                ERRCHECK(result);
            }

            if (key == ' ')
            {
                listenerflag = !listenerflag;
            }

            if (!listenerflag)
            {
                if (key == '<') 
                {
                    listenerpos.x -= 1.0f;
                    if (listenerpos.x < -35)
                    {
                        listenerpos.x = -35;
                    }
                }
                if (key == '>') 
                {
                    listenerpos.x += 1.0f;
                    if (listenerpos.x > 30)
                    {
                        listenerpos.x = 30;
                    }
                }
            }
        }

        // ==========================================================================================
        // UPDATE THE LISTENER
        // ==========================================================================================
        {
            static float t = 0;
            static FMOD_VECTOR lastpos = { 0.0f, 0.0f, 0.0f };
            FMOD_VECTOR forward        = { 0.0f, 0.0f, 1.0f };
            FMOD_VECTOR up             = { 0.0f, 1.0f, 0.0f };
            FMOD_VECTOR vel;

            if (listenerflag)
            {
                listenerpos.x = ((float)sin(t * 0.05f) * 33.0f); // left right pingpong
            }

            // ********* NOTE ******* READ NEXT COMMENT!!!!!
            // vel = how far we moved last FRAME (m/f), then time compensate it to SECONDS (m/s).
            vel.x = (listenerpos.x - lastpos.x) * (1000 / INTERFACE_UPDATETIME);
            vel.y = (listenerpos.y - lastpos.y) * (1000 / INTERFACE_UPDATETIME);
            vel.z = (listenerpos.z - lastpos.z) * (1000 / INTERFACE_UPDATETIME);

            // store pos for next time
            lastpos = listenerpos;

            result = FMOD_System_Set3DListenerAttributes(system, 0, &listenerpos, &vel, &forward, &up);
            ERRCHECK(result);

            t += (30 * (1.0f / (float)INTERFACE_UPDATETIME));    // t is just a time value .. it increments in 30m/s steps in this example

            // print out a small visual display
            {
                char s[80];

                sprintf(s, "|.......................<1>......................<2>....................|");
                
                s[(int)(listenerpos.x) + 35] = 'L';                
                printf("%s\r", s);
                fflush(stdout);
            }            
        }

        FMOD_System_Update(system);

        Sleep(INTERFACE_UPDATETIME - 1);

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
