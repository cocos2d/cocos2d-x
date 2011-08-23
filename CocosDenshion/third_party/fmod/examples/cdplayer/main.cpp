/*===============================================================================================
 CDPlayer Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to play CD tracks digitally and generate a CDDB query
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

int cddb_sum(int n)
{
    int	ret = 0;

    while (n > 0)
    {
        ret += (n % 10);
        n /= 10;
    }

    return ret;
}

unsigned long cddb_discid(FMOD_CDTOC *toc)
{
    int	i, t, n = 0;

    for (i = 0; i < toc->numtracks; i++)
    {
        n += cddb_sum((toc->min[i] * 60) + toc->sec[i]);
    }

    t = ((toc->min[toc->numtracks] * 60) + toc->sec[toc->numtracks]) - ((toc->min[0] * 60) + toc->sec[0]);

    return ((n % 0xff) << 24 | t << 8 | toc->numtracks);
}

void dump_cddb_query(FMOD_CDTOC *toc)
{
    int i;

    printf("cddb query %08x %d", cddb_discid(toc), toc->numtracks);

    for (i = 0; i < toc->numtracks; i++)
    {
        printf(" %d", (toc->min[i] * (60 * 75)) + (toc->sec[i] * 75) + toc->frame[i]);
    }

    printf(" %d\n", (toc->min[toc->numtracks] * 60) + toc->sec[toc->numtracks]);
}


int main(int argc, char *argv[])
{
    FMOD::System    *system;
    FMOD::Sound     *cdsound;
    FMOD::Sound     *sound;
    FMOD::Channel   *channel = 0;
    FMOD_RESULT      result;
    int              key, numtracks, currenttrack = 0;
    unsigned int     version;

    if (argc < 2)
    {
        printf("Usage: cdplayer <drivepath>\n");
        printf("Example: cdplayer /dev/cdrom\n");
        exit(-1);
    }

    printf("==================================================================\n");
    printf("CDPlayer Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("==================================================================\n\n");

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
        Bump up the file buffer size a bit from the 16k default for CDDA, because it is a slower medium.
    */
    result = system->setStreamBufferSize(64*1024, FMOD_TIMEUNIT_RAWBYTES);
    ERRCHECK(result);

    result = system->createStream(argv[1], FMOD_OPENONLY, 0, &cdsound);
    ERRCHECK(result);
    result = cdsound->getNumSubSounds(&numtracks);
    ERRCHECK(result);
    result = cdsound->getSubSound(currenttrack, &sound);
    ERRCHECK(result);

    for (;;)
    {
        FMOD_TAG tag;

        if (cdsound->getTag(0, -1, &tag) != FMOD_OK)
        {
            break;
        }
        if (tag.datatype == FMOD_TAGDATATYPE_CDTOC)
        {
            dump_cddb_query((FMOD_CDTOC *)tag.data);
        }
    }

    printf("\n========================================\n");
    printf("Press SPACE to pause\n");
    printf("      n     to skip to next track\n");
    printf("      ESC   to exit\n");
    printf("========================================\n\n");

    /*
        Print out length of entire CD.  Did you know you can also play 'cdsound' and it will play the whole CD without gaps?
    */
    {
        unsigned int lenms;

        result = cdsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
        ERRCHECK(result);

        printf("Total CD length %02d:%02d\n\n", lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100);
    }


    /*
        Play a CD track
    */
    result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
    ERRCHECK(result);

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
                case ' ' :
                {
                    bool paused;
                    channel->getPaused(&paused);
                    channel->setPaused(!paused);
                    break;
                }

                case 'n' :
                {
                    currenttrack++;
                    if (currenttrack >= numtracks)
                    {
                        currenttrack = 0;
                    }
                    result = cdsound->getSubSound(currenttrack, &sound);
                    ERRCHECK(result);
                    result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
                    ERRCHECK(result);
                    break;
                }
            }
        }

        system->update();

        if (channel)
        {
            unsigned int ms;
            unsigned int lenms;
            bool         playing;
            bool         paused;

            result = channel->getPaused(&paused);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }
            result = channel->isPlaying(&playing);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }
            result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }
            result = sound->getLength(&lenms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }

            printf("Track %d/%d : %02d:%02d:%02d/%02d:%02d:%02d : %s\r", currenttrack + 1, numtracks, ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped");
        }

        Sleep(10);

    } while (key != 27);

    printf("\n");

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
