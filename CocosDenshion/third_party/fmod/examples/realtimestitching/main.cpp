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
#include "../../api/inc/fmod.hpp"
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
    FMOD::System     *system;
    FMOD::Sound      *sound;
    FMOD::Sound      *subsound[2];
    FMOD_CREATESOUNDEXINFO exinfo;
    FMOD::Channel    *channel = 0;
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
    result = system->createStream(0, FMOD_LOOP_NORMAL | FMOD_OPENUSER, &exinfo, &sound);
    ERRCHECK(result);

    /*
        Add 2 of our streams as children of the parent.  They should be the same format (ie mono/stereo and bitdepth) as the parent sound.
        When subsound 0 has finished and it is playing subsound 1, we will swap subsound 0 with a new sound, and the same for when subsound 1 has finished,
        causing a continual double buffered flip, which means continuous sound.
    */
    result = system->createStream(soundname[0], FMOD_DEFAULT, 0, &subsound[0]);
    ERRCHECK(result);

    result = system->createStream(soundname[1], FMOD_DEFAULT, 0, &subsound[1]);
    ERRCHECK(result);

    result = sound->setSubSound(0, subsound[0]);
    ERRCHECK(result);

    result = sound->setSubSound(1, subsound[1]);
    ERRCHECK(result);

    /*
        Set up the gapless sentence to contain these first 2 streams.
    */
    {
        int soundlist[2] = { 0, 1 };
     
        result = sound->setSubSoundSentence(soundlist, 2);
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

    result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
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
                    bool paused;
                    channel->getPaused(&paused);
                    channel->setPaused(!paused);
                    break;
                }
            }
        }

        system->update();

        /*
            Replace the subsound that just finished with a new subsound, to create endless seamless stitching!

            Note that this polls the currently playing subsound using the FMOD_TIMEUNIT_BUFFERED flag.  
            Remember streams are decoded / buffered ahead in advance! 
            Don't use the 'audible time' which is FMOD_TIMEUNIT_SENTENCE_SUBSOUND by itself.  When streaming, sound is 
            processed ahead of time, and things like stream buffer / sentence manipulation (as done below) is required 
            to be in 'buffered time', or else there will be synchronization problems and you might end up releasing a
            sub-sound that is still playing!
        */
        result = channel->getPosition(&currentsubsoundid, (FMOD_TIMEUNIT)(FMOD_TIMEUNIT_SENTENCE_SUBSOUND | FMOD_TIMEUNIT_BUFFERED));
        ERRCHECK(result);

        if (currentsubsoundid != subsoundid)
        {
            /* 
                Release the sound that isn't playing any more. 
            */
            result = subsound[subsoundid]->release();       
            ERRCHECK(result);
   
            /* 
                Replace it with a new sound in our list.
            */
            result = system->createStream(soundname[sentenceid], FMOD_DEFAULT, 0, &subsound[subsoundid]);
            ERRCHECK(result);

            result = sound->setSubSound(subsoundid, subsound[subsoundid]);
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
    result = sound->release();          /* Freeing a parent subsound also frees its children. */
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    return 0;
}
