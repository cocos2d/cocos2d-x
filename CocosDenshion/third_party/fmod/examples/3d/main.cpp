/*===============================================================================================
 3d Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to basic 3d positioning
===============================================================================================*/
#include "../../api/inc/fmod.hpp"
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
    FMOD::System    *system;
    FMOD::Sound     *sound1, *sound2, *sound3;
    FMOD::Channel   *channel1 = 0, *channel2 = 0, *channel3 = 0;
    FMOD_RESULT      result;
    int              key;
    bool             listenerflag = true;
    FMOD_VECTOR      listenerpos  = { 0.0f, 0.0f, 0.0f };
    unsigned int     version;

    printf("===============================================================\n");
    printf("3d Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("===============================================================\n\n");
    printf("This example plays 2 3D sounds in software.  Optionally you can\n");
    printf("play a 2D software sound as well.\n");
    printf("Hardware sounds are not supported on Linux\n");
    printf("===============================================================\n\n");

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

    result = system->init(10, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    /*
        Load some sounds
    */
    
    result = system->createSound("../media/drumloop.wav", FMOD_SOFTWARE | FMOD_3D, 0, &sound1);
    ERRCHECK(result);
    result = sound1->set3DMinMaxDistance(4.0f, 10000.0f);
    ERRCHECK(result);
    result = sound1->setMode(FMOD_LOOP_NORMAL);
    ERRCHECK(result);

    result = system->createSound("../media/jaguar.wav", FMOD_SOFTWARE | FMOD_3D, 0, &sound2);
    ERRCHECK(result);
    result = sound2->set3DMinMaxDistance(4.0f, 10000.0f);
    ERRCHECK(result);
    result = sound2->setMode(FMOD_LOOP_NORMAL);
    ERRCHECK(result);

    result = system->createSound("../media/swish.wav", FMOD_SOFTWARE | FMOD_2D, 0, &sound3);
    ERRCHECK(result);

    /*
        Play sounds at certain positions
    */
    {
        FMOD_VECTOR pos = { -10.0f, -0.0f, 0.0f };
        FMOD_VECTOR vel = {   0.0f,  0.0f, 0.0f };

        result = system->playSound(FMOD_CHANNEL_FREE, sound1, true, &channel1);
        ERRCHECK(result);
        result = channel1->set3DAttributes(&pos, &vel);
        ERRCHECK(result);
        result = channel1->setPaused(false);
        ERRCHECK(result);
    }

    {
        FMOD_VECTOR pos = { 15.0f, -0.0f, -0.0f };
        FMOD_VECTOR vel = {  0.0f,  0.0f,  0.0f };

        result = system->playSound(FMOD_CHANNEL_FREE, sound2, true, &channel2);
        ERRCHECK(result);
        result = channel2->set3DAttributes(&pos, &vel);
        ERRCHECK(result);
        result = channel2->setPaused(false);
        ERRCHECK(result);
    }

    /*
        Display help
    */
    {
        int numchannels = 0;

        result = system->getHardwareChannels(&numchannels);
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
                bool paused;
                channel1->getPaused(&paused);
                channel1->setPaused(!paused);
            }

            if (key == '2') 
            {
                bool paused;
                channel2->getPaused(&paused);
                channel2->setPaused(!paused);
            }

            if (key == '3') 
            {
                result = system->playSound(FMOD_CHANNEL_FREE, sound3, false, &channel3);
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

            result = system->set3DListenerAttributes(0, &listenerpos, &vel, &forward, &up);
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

        system->update();

        Sleep(INTERFACE_UPDATETIME - 1);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = sound1->release();
    ERRCHECK(result);
    result = sound2->release();
    ERRCHECK(result);
    result = sound3->release();
    ERRCHECK(result);

    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    return 0;
}
