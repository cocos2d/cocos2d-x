/*===============================================================================================
 Effects Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to apply some of the built in software effects to sounds. 
 This example filters the global mix.  All software sounds played here would be filtered in the 
 same way.
 To filter per channel, and not have other channels affected, simply replace system->addDSP with
 channel->addDSP.
 Note in this example you don't have to add and remove units each time, you could simply add them 
 all at the start then use DSP::setActive to toggle them on and off.
===============================================================================================*/
#include "../../api/inc/fmod.hpp"
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
    FMOD::System     *system        = 0;
    FMOD::Sound      *sound         = 0;
    FMOD::Channel    *channel       = 0;
    FMOD::DSP        *dsplowpass    = 0;
    FMOD::DSP        *dsphighpass   = 0;
    FMOD::DSP        *dspecho       = 0;
    FMOD::DSP        *dspflange     = 0;
    FMOD::DSP        *dspdistortion = 0;
    FMOD::DSP        *dspchorus     = 0;
    FMOD::DSP        *dspparameq    = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;

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

    result = system->createSound("../media/drumloop.wav", FMOD_SOFTWARE, 0, &sound);
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

    result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
    ERRCHECK(result);

    /*
        Create some effects to play with.
    */
    result = system->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &dsplowpass);
    ERRCHECK(result);
    result = system->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &dsphighpass);
    ERRCHECK(result);
    result = system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dspecho);
    ERRCHECK(result);
    result = system->createDSPByType(FMOD_DSP_TYPE_FLANGE, &dspflange);
    ERRCHECK(result);
    result = system->createDSPByType(FMOD_DSP_TYPE_DISTORTION, &dspdistortion);
    ERRCHECK(result);
    result = system->createDSPByType(FMOD_DSP_TYPE_CHORUS, &dspchorus);
    ERRCHECK(result);
    result = system->createDSPByType(FMOD_DSP_TYPE_PARAMEQ, &dspparameq);
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
                    ERRCHECK(result);

                    paused = !paused;

                    result = channel->setPaused(paused);
                    ERRCHECK(result);
                    break;
                }
                case '1' :
                {
                    bool active;

                    result = dsplowpass->getActive(&active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = dsplowpass->remove();
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = system->addDSP(dsplowpass, 0);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '2' :
                {
                    bool active;

                    result = dsphighpass->getActive(&active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = dsphighpass->remove();
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = system->addDSP(dsphighpass, 0);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '3' :
                {
                    bool active;

                    result = dspecho->getActive(&active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = dspecho->remove();
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = system->addDSP(dspecho, 0);
                        ERRCHECK(result);

                        result = dspecho->setParameter(FMOD_DSP_ECHO_DELAY, 50.0f);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '4' :
                {
                    bool active;

                    result = dspflange->getActive(&active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = dspflange->remove();
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = system->addDSP(dspflange, 0);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '5' :
                {
                    bool active;

                    result = dspdistortion->getActive(&active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = dspdistortion->remove();
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = system->addDSP(dspdistortion, 0);
                        ERRCHECK(result);

                        result = dspdistortion->setParameter(FMOD_DSP_DISTORTION_LEVEL, 0.8f);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '6' :
                {
                    bool active;

                    result = dspchorus->getActive(&active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = dspchorus->remove();
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = system->addDSP(dspchorus, 0);
                        ERRCHECK(result);
                    }
                    break;
                }
                case '7' :
                {
                    bool active;

                    result = dspparameq->getActive(&active);
                    ERRCHECK(result);

                    if (active)
                    {
                        result = dspparameq->remove();
                        ERRCHECK(result);
                    }
                    else
                    {
                        result = system->addDSP(dspparameq, 0);
                        ERRCHECK(result);

                        result = dspparameq->setParameter(FMOD_DSP_PARAMEQ_CENTER, 5000.0f);
                        ERRCHECK(result);
                        result = dspparameq->setParameter(FMOD_DSP_PARAMEQ_GAIN, 0.0f);
                        ERRCHECK(result);
                    }
                    break;
                }
            }
        }

        system->update();

        {
            bool paused = 0;
            bool dsplowpass_active;
            bool dsphighpass_active;
            bool dspecho_active;
            bool dspflange_active;
            bool dspdistortion_active;
            bool dspchorus_active;
            bool dspparameq_active;

            dsplowpass   ->getActive(&dsplowpass_active);
            dsphighpass  ->getActive(&dsphighpass_active);
            dspecho      ->getActive(&dspecho_active);
            dspflange    ->getActive(&dspflange_active);
            dspdistortion->getActive(&dspdistortion_active);
            dspchorus    ->getActive(&dspchorus_active);
            dspparameq   ->getActive(&dspparameq_active);

            if (channel)
            {
                result = channel->getPaused(&paused);
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
    result = sound->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    return 0;
}


