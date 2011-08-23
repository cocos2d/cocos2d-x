/*===============================================================================================
 NetStream Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to play streaming audio from the internet
===============================================================================================*/
#include "../../api/inc/fmod.hpp"
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
    FMOD::System    *system;
    FMOD::Sound     *sound;
    FMOD::Channel   *channel = 0;
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
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return 0;
    }

    result = system->init(1, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    /*
        Bump up the file buffer size a little bit for netstreams (to account for lag).  Decode buffer is left at default.
    */
    result = system->setStreamBufferSize(64*1024, FMOD_TIMEUNIT_RAWBYTES);
    ERRCHECK(result);

    result = system->createSound(argv[1], FMOD_HARDWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_NONBLOCKING,  0, &sound);
    ERRCHECK(result);

    printf("Press space to pause, Esc to quit\n\n");

    /*
        Main loop
    */
    do
    {
        unsigned int    ms = 0, percent = 0;
        bool            playing = false;
        bool            paused = false;
        bool            starving = false;
        FMOD_OPENSTATE  openstate;

        if (!channel)
        {
            result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
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
                        bool paused;
                        channel->getPaused(&paused);
                        channel->setPaused(!paused);
                    }
                    break;
                }
            }
        }

        system->update();

        if (channel)
        {
            for (;;)
            {
                FMOD_TAG tag;
                if (sound->getTag(0, -1, &tag) != FMOD_OK)
                {
                    break;
                }
                if (tag.datatype == FMOD_TAGDATATYPE_STRING)
                {
                    printf("%s = %s (%d bytes)\n", tag.name, (char *)tag.data, tag.datalen);
                }
            }

            result = channel->getPaused(&paused);
            ERRCHECK(result);
            result = channel->isPlaying(&playing);
            ERRCHECK(result);
            result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
            ERRCHECK(result);
        }

        result = sound->getOpenState(&openstate, &percent, &starving, 0);
        ERRCHECK(result);
        
        channel->setMute(starving);
        ERRCHECK(result);
            
        printf("Time %02d:%02d:%02d : %s : (%3d%%) %s     \r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, openstate == FMOD_OPENSTATE_BUFFERING ? "Buffering..." : openstate == FMOD_OPENSTATE_CONNECTING ? "Connecting..." : paused ? "Paused       " : playing ? "Playing      " : "Stopped      ", percent, starving ? "STARVING" : "        ");
        fflush(stdout);

        Sleep(10);

    } while (key != 27);

    printf("\n");

    printf("Shutting down.\n");

    if (channel)
    {
        result = channel->stop();
        ERRCHECK(result);
    }

    /*
        If we pressed escape before it is ready, wait for it to finish opening before we release it.
    */
    do
    {
        FMOD_OPENSTATE openstate;

        result = sound->getOpenState(&openstate, 0, 0, 0);
        ERRCHECK(result);

        if (openstate == FMOD_OPENSTATE_READY)
        {
            break;
        }

        printf("Waiting for sound to finish opening before trying to release it....\r");
        fflush(stdout);

        Sleep(10);
    } while (1);

    /*
        Shut down
    */
    result = sound->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    return 0;
}
