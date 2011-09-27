/*===============================================================================================
 Real-time stitching example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how you can create your own multi-subsound stream, then in realtime replace
 each the subsound as it plays them.  Using a looping sentence, it will seamlessly stich between
 2 subsounds in this example, and each time it switches to a new sound, it will replace the old
 one with another sound in our list.

 These sounds can go on forever as long as they are the same bitdepth (when decoded) and number
 of channels (ie mono / stereo).  The reason for this is the hardware channel cannot change 
 formats mid sentence, and using different hardware channels would mean it wouldn't be gapless.

===============================================================================================*/
#include "../../api/inc/fmod.h"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"

#include <string.h>

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

#define NUMSOUNDS 32

int main(int argc, char *argv[])
{
    FMOD_SYSTEM      *system;
    FMOD_SOUND       *sound;
    FMOD_SOUND       *subsound[2];
    FMOD_CREATESOUNDEXINFO exinfo;
    FMOD_CHANNEL     *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      subsoundid, sentenceid;
    unsigned int      version;
    const char       *soundname[NUMSOUNDS] = 
    {
        "../media/e.ogg",   /* Ma-    */
        "../media/d.ogg",   /* ry     */
        "../media/c.ogg",   /* had    */
        "../media/d.ogg",   /* a      */
        "../media/e.ogg",   /* lit-   */
        "../media/e.ogg",   /* tle    */
        "../media/e.ogg",   /* lamb,  */
        "../media/e.ogg",   /* .....  */
        "../media/d.ogg",   /* lit-   */
        "../media/d.ogg",   /* tle    */
        "../media/d.ogg",   /* lamb,  */
        "../media/d.ogg",   /* .....  */
        "../media/e.ogg",   /* lit-   */
        "../media/e.ogg",   /* tle    */
        "../media/e.ogg",   /* lamb,  */
        "../media/e.ogg",   /* .....  */

        "../media/e.ogg",   /* Ma-    */
        "../media/d.ogg",   /* ry     */
        "../media/c.ogg",   /* had    */
        "../media/d.ogg",   /* a      */
        "../media/e.ogg",   /* lit-   */
        "../media/e.ogg",   /* tle    */
        "../media/e.ogg",   /* lamb,  */
        "../media/e.ogg",   /* its    */
        "../media/d.ogg",   /* fleece */
        "../media/d.ogg",   /* was    */
        "../media/e.ogg",   /* white  */
        "../media/d.ogg",   /* as     */
        "../media/c.ogg",   /* snow.  */
        "../media/c.ogg",   /* .....  */
        "../media/c.ogg",   /* .....  */
        "../media/c.ogg",   /* .....  */
    };

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

    result = FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);

    /*
        Set up the FMOD_CREATESOUNDEXINFO structure for the user stream with room for 2 subsounds. (our subsound double buffer)
    */
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.defaultfrequency = 44100;
    exinfo.numsubsounds = 2;
    exinfo.numchannels = 1;
    exinfo.format = FMOD_SOUND_FORMAT_PCM16;

    /*
        Create the 'parent' stream that contains the substreams.  Set it to loop so that it loops between subsound 0 and 1.
    */
    result = FMOD_System_CreateStream(system, 0, FMOD_LOOP_NORMAL | FMOD_OPENUSER, &exinfo, &sound);
    ERRCHECK(result);

    /*
        Add 2 of our streams as children of the parent.  They should be the same format (ie mono/stereo and bitdepth) as the parent sound.
        When subsound 0 has finished and it is playing subsound 1, we will swap subsound 0 with a new sound, and the same for when subsound 1 has finished,
        causing a continual double buffered flip, which means continuous sound.
    */
    result = FMOD_System_CreateStream(system, soundname[0], FMOD_DEFAULT, 0, &subsound[0]);
    ERRCHECK(result);

    result = FMOD_System_CreateStream(system, soundname[1], FMOD_DEFAULT, 0, &subsound[1]);
    ERRCHECK(result);

    result = FMOD_Sound_SetSubSound(sound, 0, subsound[0]);
    ERRCHECK(result);

    result = FMOD_Sound_SetSubSound(sound, 1, subsound[1]);
    ERRCHECK(result);

    /*
        Set up the gapless sentence to contain these first 2 streams.
    */
    {
        int soundlist[2] = { 0, 1 };
     
        result = FMOD_Sound_SetSubSoundSentence(sound, soundlist, 2);
        ERRCHECK(result);
    }

    subsoundid = 0;     
    sentenceid = 2;     /* The next sound to be appeneded to the stream. */

    printf("=============================================================================\n");
    printf("Real-time stitching example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("=============================================================================\n");
    printf("\n");
    printf("Press space to pause, Esc to quit\n");
    printf("\n");

    printf("Inserted subsound %d / 2 with sound %d / %d\n", 0, 0, NUMSOUNDS);
    printf("Inserted subsound %d / 2 with sound %d / %d\n", 1, 1, NUMSOUNDS);

    /*
        Play the sound.
    */

    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, FALSE, &channel);
    ERRCHECK(result);

    /*
        Main loop.
    */
    do
    {
        unsigned int currentsubsoundid;

        if (kbhit())
        {
            key = getch();

            switch (key)
            {
                case ' ' :
                {
                    int paused;
                    FMOD_Channel_GetPaused(channel, &paused);
                    FMOD_Channel_SetPaused(channel, !paused);
                    break;
                }
            }
        }

        FMOD_System_Update(system);

        /*
            Replace the subsound that just finished with a new subsound, to create endless seamless stitching!

            Note that this polls the currently playing subsound using the FMOD_TIMEUNIT_BUFFERED flag.  
            Remember streams are decoded / buffered ahead in advance! 
            Don't use the 'audible time' which is FMOD_TIMEUNIT_SENTENCE_SUBSOUND by itself.  When streaming, sound is 
            processed ahead of time, and things like stream buffer / sentence manipulation (as done below) is required 
            to be in 'buffered time', or else there will be synchronization problems and you might end up releasing a
            sub-sound that is still playing!
        */
        result = FMOD_Channel_GetPosition(channel, &currentsubsoundid, (FMOD_TIMEUNIT)(FMOD_TIMEUNIT_SENTENCE_SUBSOUND | FMOD_TIMEUNIT_BUFFERED));
        ERRCHECK(result);

        if (currentsubsoundid != subsoundid)
        {
            /* 
                Release the sound that isn't playing any more. 
            */
            result = FMOD_Sound_Release(subsound[subsoundid]);       
            ERRCHECK(result);
   
            /* 
                Replace it with a new sound in our list.
            */
            result = FMOD_System_CreateStream(system, soundname[sentenceid], FMOD_DEFAULT, 0, &subsound[subsoundid]);
            ERRCHECK(result);

            result = FMOD_Sound_SetSubSound(sound, subsoundid, subsound[subsoundid]);
            ERRCHECK(result);

            printf("Replacing subsound %d / 2 with sound %d / %d\n", subsoundid, sentenceid, NUMSOUNDS);

            sentenceid++;
            if (sentenceid >= NUMSOUNDS)
            {
                sentenceid = 0;
            }

            subsoundid = currentsubsoundid;
        }
        
        Sleep(50);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = FMOD_Sound_Release(sound);     /* Freeing a parent subsound also frees its children. */
    ERRCHECK(result);
    result = FMOD_System_Close(system);
    ERRCHECK(result);
    result = FMOD_System_Release(system);
    ERRCHECK(result);

    return 0;
}
