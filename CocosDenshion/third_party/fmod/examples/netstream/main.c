/*===============================================================================================
 NetStream Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to play streaming audio from the internet
===============================================================================================*/
#include "../../api/inc/fmod.h"
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
    FMOD_SYSTEM     *system;
    FMOD_SOUND      *sound;
    FMOD_CHANNEL    *channel = 0;
    FMOD_RESULT      result;
    int              key;
    unsigned int     version;

    printf("===================================================================\n");
    printf("NetStream Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("===================================================================\n\n");

    if (argc < 2)
    {
        printf("Usage:   netstream <url>\n");
        printf("Example: netstream http://www.fmod.org/stream.mp3\n\n");
        return -1;
    }

    /*
        Create a System object and initialize.
    */
    result = FMOD_System_Create(&system);
    ERRCHECK(result);

    result = FMOD_System_GetVersion(system,&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return 0;
    }

    result = FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);

    /*
        Bump up the file buffer size a little bit for netstreams (to account for lag).  Decode buffer is left at default.
    */
    result = FMOD_System_SetStreamBufferSize(system, 64*1024, FMOD_TIMEUNIT_RAWBYTES);
    ERRCHECK(result);

    result = FMOD_System_CreateSound(system, argv[1], FMOD_HARDWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_NONBLOCKING,  0, &sound);
    ERRCHECK(result);

    printf("Press space to pause, Esc to quit\n\n");

    /*
        Main loop
    */
    do
    {
        unsigned int    ms = 0, percent = 0;
        int             playing = FALSE;
        int             paused = FALSE;
        int             starving = FALSE;
        FMOD_OPENSTATE  openstate;

        if (!channel)
        {
            result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, FALSE, &channel);
        }

        if (kbhit())
        {
            key = getch();

            switch (key)
            {
                case ' ' :
                {
                    if (channel)
                    {
                        int paused;
                        FMOD_Channel_GetPaused(channel, &paused);
                        FMOD_Channel_SetPaused(channel, !paused);
                    }
                    break;
                }
            }
        }

        FMOD_System_Update(system);

        if (channel)
        {
            for (;;)
            {
                FMOD_TAG tag;
                if (FMOD_Sound_GetTag(sound, 0, -1, &tag) != FMOD_OK)
                {
                    break;
                }
                if (tag.datatype == FMOD_TAGDATATYPE_STRING)
                {
                    printf("%s = %s (%d bytes)\n", tag.name, tag.data, tag.datalen);
                }
            }
            result = FMOD_Channel_GetPaused(channel, &paused);
            ERRCHECK(result);
            result = FMOD_Channel_IsPlaying(channel, &playing);
            ERRCHECK(result);
            result = FMOD_Channel_GetPosition(channel, &ms, FMOD_TIMEUNIT_MS);
            ERRCHECK(result);
        }

        result = FMOD_Sound_GetOpenState(sound, &openstate, &percent, &starving, 0);
        ERRCHECK(result);

        printf("Time %02d:%02d:%02d : %s : (%3d%%%) %s     \r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, openstate == FMOD_OPENSTATE_BUFFERING ? "Buffering..." : openstate == FMOD_OPENSTATE_CONNECTING ? "Connecting..." : paused ? "Paused       " : playing ? "Playing      " : "Stopped      ", percent, starving ? "STARVING" : "        ");

        Sleep(10);

    } while (key != 27);

    printf("\n");

    printf("Shutting down.\n");

    /*
        If we pressed escape before it is ready, wait for it to finish opening before we release it.
    */
    do
    {
        FMOD_OPENSTATE openstate;

        result = FMOD_Sound_GetOpenState(sound, &openstate, 0, 0, 0);
        ERRCHECK(result);

        if (openstate == FMOD_OPENSTATE_READY)
        {
            break;
        }

        printf("Waiting for sound to finish opening before trying to release it....\r");

        Sleep(10);
    } while (1);

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
