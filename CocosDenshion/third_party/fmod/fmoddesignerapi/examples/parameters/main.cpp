/*===============================================================================================
 Parameters Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 Demonstrates basic usage of event parameters
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
    FMOD::EventGroup     *eventgroup;
    FMOD::EventCategory  *mastercategory;
    FMOD::Event          *car;
    FMOD::EventParameter *rpm;
    FMOD::EventParameter *load;
    FMOD_RESULT           result;
    int                   key;
    float                 rpm_val, rpm_min, rpm_max, rpm_increment, load_val, load_min, load_max, load_increment;

    printf("======================================================================\n");
    printf("Parameters Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("==============================-------=================================\n");
    printf("This demonstrates the use of FMOD event parameters. It simply plays an\n");
    printf("event, retrieves the parameters and allows the user to adjust them.\n");
    printf("======================================================================\n\n");

    ERRCHECK(result = FMOD::EventSystem_Create(&eventsystem));
    ERRCHECK(result = eventsystem->init(64, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL));
    ERRCHECK(result = eventsystem->setMediaPath("../media/"));
    ERRCHECK(result = eventsystem->load("examples.fev", 0, 0));
    ERRCHECK(result = eventsystem->getGroup("examples/AdvancedTechniques", FMOD_EVENT_DEFAULT, &eventgroup));
    ERRCHECK(result = eventgroup->getEvent("car", FMOD_EVENT_DEFAULT, &car));

    ERRCHECK(result = eventsystem->getCategory("master", &mastercategory));

    ERRCHECK(result = car->getParameter("load", &load));
    ERRCHECK(result = load->getRange(&load_min, &load_max));
    ERRCHECK(result = load->setValue(load_max));

    ERRCHECK(result = car->getParameterByIndex(0, &rpm));
    ERRCHECK(result = rpm->getRange(&rpm_min, &rpm_max));
    ERRCHECK(result = rpm->setValue(1000.0f));

    ERRCHECK(result = car->start());

    printf("======================================================================\n");
    printf("Press '<' or ',' to decrease RPM\n");
    printf("Press '>' or '.' to increase RPM\n");
    printf("Press '-' or '_' to decrease load\n");
    printf("Press '+' or '=' to increase load\n");
    printf("Press ESC        to quit\n");
    printf("======================================================================\n");

    rpm_increment   = (rpm_max - rpm_min) / UPDATE_INTERVAL;
    ERRCHECK(result = rpm->getValue(&rpm_val));
    load_increment  = (load_max - load_min) / UPDATE_INTERVAL;
    ERRCHECK(result = load->getValue(&load_val));

    key = 0;
    do
    {
        if (_kbhit())
        {
            key = _getch();

            if (key == '<' || key == ',')
            {
                rpm_val -= rpm_increment;
                if (rpm_val < rpm_min)
                {
                    rpm_val = rpm_min;
                }

                ERRCHECK(result = rpm->setValue(rpm_val));
            }
            else if (key == '>' || key == '.')
            {
                rpm_val += rpm_increment;
                if (rpm_val > rpm_max)
                {
                    rpm_val = rpm_max;
                }

                ERRCHECK(result = rpm->setValue(rpm_val));
            }
            if (key == '-' || key == '_')
            {
                load_val -= load_increment;
                if (load_val < load_min)
                {
                    load_val = load_min;
                }

                ERRCHECK(result = load->setValue(load_val));
            }
            else if (key == '+' || key == '=')
            {
                load_val += load_increment;
                if (load_val > load_max)
                {
                    load_val = load_max;
                }

                ERRCHECK(result = load->setValue(load_val));
            }
            else if (key == ' ')
            {
                bool paused;

                ERRCHECK(result = mastercategory->getPaused(&paused));
                paused = !paused;
                ERRCHECK(result = mastercategory->setPaused(paused));
            }

        }

        ERRCHECK(result = eventsystem->update());
        Sleep(15);

        printf("RPM = %.4f, load = %.4f        \r", rpm_val, load_val);
        fflush(stdout);

    } while (key != 27);

    ERRCHECK(result = eventgroup->freeEventData());
    ERRCHECK(result = eventsystem->release());
    return 0;
}
