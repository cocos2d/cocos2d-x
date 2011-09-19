/*===============================================================================================
 User Created Sound Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how create a sound with data filled by the user.
 It shows a user created static sample, followed by a user created stream.
 The former allocates all memory needed for the sound and is played back as a static sample, 
 while the latter streams the data in chunks as it plays, using far less memory.
===============================================================================================*/
#include "../../api/inc/fmod.hpp"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"
#include <math.h>
#include <string.h>

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

FMOD_RESULT F_CALLBACK pcmreadcallback(FMOD_SOUND *sound, void *data, unsigned int datalen)
{
    unsigned int  count;
    static float  t1 = 0, t2 = 0;        // time
    static float  v1 = 0, v2 = 0;        // velocity
    signed short *stereo16bitbuffer = (signed short *)data;

    for (count=0; count<datalen>>2; count++)        // >>2 = 16bit stereo (4 bytes per sample)
    {
        *stereo16bitbuffer++ = (signed short)(sin(t1) * 32767.0f);    // left channel
        *stereo16bitbuffer++ = (signed short)(sin(t2) * 32767.0f);    // right channel

        t1 += 0.01f   + v1;
        t2 += 0.0142f + v2;
        v1 += (float)(sin(t1) * 0.002f);
        v2 += (float)(sin(t2) * 0.002f);
    }

    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK pcmsetposcallback(FMOD_SOUND *sound, int subsound, unsigned int position, FMOD_TIMEUNIT postype)
{
    /*
        This is useful if the user calls Sound::setPosition and you want to seek your data accordingly.
    */
    return FMOD_OK;
}


int main(int argc, char *argv[])
{
    FMOD::System           *system;
    FMOD::Sound            *sound;
    FMOD::Channel          *channel = 0;
    FMOD_RESULT             result;
    FMOD_MODE               mode = FMOD_2D | FMOD_OPENUSER | FMOD_LOOP_NORMAL | FMOD_HARDWARE;
    int                     key;
    int                     channels = 2;
    FMOD_CREATESOUNDEXINFO  createsoundexinfo;
    unsigned int            version;

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
        
    printf("============================================================================\n");
    printf("User Created Sound Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("============================================================================\n");
    printf("Sound played here is generated in realtime.  It will either play as a stream\n");
    printf("which means it is continually filled as it is playing, or it will play as a \n");
    printf("static sample, which means it is filled once as the sound is created, then  \n");
    printf("when played it will just play that short loop of data.                      \n");
    printf("============================================================================\n");
    printf("\n");

    do
    {
        printf("Press 1 to play as a runtime decoded stream. (will carry on infinitely)\n");
        printf("Press 2 to play as a static in memory sample. (loops a short block of data)\n");
        printf("Press Esc to quit.\n\n");
        key = getch();

    } while (key != 27 && key != '1' && key != '2');

    if (key == 27)
    {
        return 0;
    }
    else if (key == '1')
    {
        mode |= FMOD_CREATESTREAM;
    }

    memset(&createsoundexinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    createsoundexinfo.cbsize            = sizeof(FMOD_CREATESOUNDEXINFO);              /* required. */
    createsoundexinfo.decodebuffersize  = 44100;                                       /* Chunk size of stream update in samples.  This will be the amount of data passed to the user callback. */
    createsoundexinfo.length            = 44100 * channels * sizeof(signed short) * 5; /* Length of PCM data in bytes of whole song (for Sound::getLength) */
    createsoundexinfo.numchannels       = channels;                                    /* Number of channels in the sound. */
    createsoundexinfo.defaultfrequency  = 44100;                                       /* Default playback rate of sound. */
    createsoundexinfo.format            = FMOD_SOUND_FORMAT_PCM16;                     /* Data format of sound. */
    createsoundexinfo.pcmreadcallback   = pcmreadcallback;                             /* User callback for reading. */
    createsoundexinfo.pcmsetposcallback = pcmsetposcallback;                           /* User callback for seeking. */

    result = system->createSound(0, mode, &createsoundexinfo, &sound);
    ERRCHECK(result);

    printf("Press space to pause, Esc to quit\n");
    printf("\n");

    /*
        Play the sound.
    */

    result = system->playSound(FMOD_CHANNEL_FREE, sound, 0, &channel);
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
                    bool paused;
                    channel->getPaused(&paused);
                    channel->setPaused(!paused);
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

            channel->isPlaying(&playing);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }

            result = channel->getPaused(&paused);
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

            printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped");
            fflush(stdout);
        }

        Sleep(20);

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


