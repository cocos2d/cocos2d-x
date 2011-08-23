/*===============================================================================================
 Effects Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 Demonstrates basic usage of event effects
===============================================================================================*/
#include "../../../examples/common/wincompat.h"

#include "../../api/inc/fmod_event.hpp"
#include "../../../api/inc/fmod_errors.h"

const float UPDATE_INTERVAL = 100.0f;


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
    FMOD::EventSystem    *eventsystem;
    FMOD::Event          *event;
    FMOD::EventParameter *param00;
    FMOD_RESULT           result;
    int                   key;
    float                 param00_val, param00_min, param00_max, param00_increment;

    printf("======================================================================\n");
    printf("Effects Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("==============================-------=================================\n");
    printf("This demonstrates the use of FMOD event effects. It simply plays an\n");
    printf("event with effects applied and allows the user to adjust the parameters.\n");
    printf("======================================================================\n\n");

    ERRCHECK(result = FMOD::EventSystem_Create(&eventsystem));
    ERRCHECK(result = eventsystem->init(64, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL));
    ERRCHECK(result = eventsystem->setMediaPath("../media/"));
    ERRCHECK(result = eventsystem->load("examples.fev", 0, 0));
    ERRCHECK(result = eventsystem->getEvent("examples/FeatureDemonstration/Effects/PropertyAutomationEffectEnvelope", FMOD_EVENT_DEFAULT, &event));
    ERRCHECK(result = event->getParameter("param00", &param00));
    ERRCHECK(result = param00->getRange(&param00_min, &param00_max));
    ERRCHECK(result = param00->setValue(0.0f));
    ERRCHECK(result = event->start());

    printf("======================================================================\n");
    printf("Press '<' or ',' to decrease param00\n");
    printf("Press '>' or '.' to increase param00\n");
    printf("Press ESC        to quit\n");
    printf("======================================================================\n");

    param00_increment = (param00_max - param00_min) / UPDATE_INTERVAL;
    ERRCHECK(result = param00->getValue(&param00_val));

    key = 0;
    do
    {
        if (_kbhit())
        {
            key = _getch();

            if (key == '<' || key == ',')
            {
                param00_val -= param00_increment;
                if (param00_val < param00_min)
                {
                    param00_val = param00_min;
                }

                ERRCHECK(result = param00->setValue(param00_val));
            }
            else if (key == '>' || key == '.')
            {
                param00_val += param00_increment;
                if (param00_val > param00_max)
                {
                    param00_val = param00_max;
                }

                ERRCHECK(result = param00->setValue(param00_val));
            }
        }

        ERRCHECK(result = eventsystem->update());
        Sleep(15);

        printf("param00 = %.4f         \r", param00_val);
        fflush(stdout);

    } while (key != 27);

    ERRCHECK(result = eventsystem->release());
    return 0;
}
