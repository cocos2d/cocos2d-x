/*===============================================================================================
 Load Event Data Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 Demonstrates basic loading and unloading of event data per event
===============================================================================================*/
#include "../../../examples/common/wincompat.h"

#include "../../api/inc/fmod_event.hpp"
#include "../../../api/inc/fmod_errors.h"


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
    FMOD::Event          *event = 0;
    FMOD_RESULT           result;
    int                   key;

    printf("======================================================================\n");
    printf("Load Event Data Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("==============================-------=================================\n");
    printf("This demonstrates loading and unloading of event data per event and\n");
    printf("per group.\n");
    printf("======================================================================\n\n");

    ERRCHECK(result = FMOD::EventSystem_Create(&eventsystem));
    ERRCHECK(result = eventsystem->init(64, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL));
    ERRCHECK(result = eventsystem->setMediaPath("../media/"));
    ERRCHECK(result = eventsystem->load("examples.fev", 0, 0));
    ERRCHECK(result = eventsystem->getGroup("examples/FeatureDemonstration/Basics", false, &eventgroup));

    printf("======================================================================\n");
    printf("Press 'e'        to load event data\n");
    printf("Press 'E'        to unload event data\n");
    printf("Press 'g'        to load group data\n");
    printf("Press 'G'        to unload group data\n");
    printf("Press ESC        to quit\n");
    printf("======================================================================\n");

    bool memory_changed = true;

    key = 0;
    do
    {
        if (_kbhit())
        {

            key = _getch();

            if (key == 'e')
            {
                ERRCHECK(result = eventgroup->getEvent("SimpleEvent", FMOD_EVENT_DEFAULT, &event));
                printf("Event data loaded\n");
                memory_changed = true;
            }
            else if (key == 'E')
            {
                if (event)
                {
                    result = eventgroup->freeEventData(event);
                    if (result != FMOD_ERR_INVALID_HANDLE)
                    {
                        ERRCHECK(result);
                        printf("Event data unloaded\n");
                        memory_changed = true;
                    }
                    event = 0;
                }
            }
            else if (key == 'g')
            {
                ERRCHECK(result = eventgroup->loadEventData());
                printf("Event group data loaded\n");
                memory_changed = true;
            }
            else if (key == 'G')
            {
                ERRCHECK(result = eventgroup->freeEventData());
                printf("Event group data unloaded\n");
                memory_changed = true;
            }

        }

        if (memory_changed)
        {
            int memory_current, memory_max;
            ERRCHECK(result = FMOD::Memory_GetStats(&memory_current, &memory_max));

            printf("Memory usage: current = %10d, max = %10d\n", memory_current, memory_max);
            memory_changed = false;
        }

        ERRCHECK(result = eventsystem->update());
        fflush(stdout);
        Sleep(15);

    } while (key != 27);

    ERRCHECK(result = eventgroup->freeEventData());
    ERRCHECK(result = eventsystem->release());
    return 0;
}
