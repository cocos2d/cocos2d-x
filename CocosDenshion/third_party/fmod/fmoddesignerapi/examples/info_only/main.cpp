/*===============================================================================================
 Info-only Event Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 Demonstrates usage and functionality of info-only events
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
    printf("Info-only Event Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("==============================-------=================================\n");
    printf("This demonstrates usage and functionality of info-only events.\n");
    printf("======================================================================\n\n");

    ERRCHECK(result = FMOD::EventSystem_Create(&eventsystem));
    ERRCHECK(result = eventsystem->init(64, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL));
    ERRCHECK(result = eventsystem->setMediaPath("../media/"));
    ERRCHECK(result = eventsystem->load("examples.fev", 0, 0));
    ERRCHECK(result = eventsystem->getGroup("examples/FeatureDemonstration/Basics", false, &eventgroup));

    printf("======================================================================\n");
    printf("Press 'i'        to get an info-only event\n");
    printf("Press 'e'        to get an event instance\n");
    printf("Press 'u'        to unload all event data\n");
    printf("Press '1' - '0'  to set event volume between 10%% - 100%%\n");
    printf("Press Space      to start/stop the current event\n");
    printf("Press ESC        to quit\n");
    printf("======================================================================\n");

    bool state_changed = true;

    key = 0;
    do
    {
        if (_kbhit())
        {

            key = _getch();

            if (key == 'i')
            {
                /* Get an info-only event.
                   Notes:
                   - This is the parent from which all instances of the
                     specified event are derived.
                   - This call will not allocate memory for event instances or
                     load sample data.
                   - The resulting event cannot be played, it simply allows
                     querying and setting of event properties.
                   - Any properties which are set on the info-only event will be
                     copied to all instances which are retrieved from then on.
                 */
                ERRCHECK(result = eventgroup->getEvent("BasicEventWithLooping", FMOD_EVENT_INFOONLY, &event));
                printf("getEvent(FMOD_EVENT_INFOONLY) succeeded\n");
                state_changed = true;
            }
            else if (key == 'e')
            {
                /* Get an event instance.
                   Notes:
                   - This call will allocate memory for event instances and
                     load sample data if required.
                   - The resulting event can be played.
                   - Any properties which have been set on the info-only event
                     will be copied to this instance.
                 */
                ERRCHECK(result = eventgroup->getEvent("BasicEventWithLooping", FMOD_EVENT_DEFAULT, &event));
                printf("getEvent(FMOD_EVENT_DEFAULT) succeeded\n");
                state_changed = true;
            }
            else if (key == ' ')
            {
                if (event)
                {
                    FMOD_EVENT_STATE state;

                    result = event->getState(&state);
                    if (result != FMOD_ERR_INVALID_HANDLE)
                    {
                        ERRCHECK(result);
                    }

                    if (state & FMOD_EVENT_STATE_PLAYING)
                    {
                        /* Attempt to stop the event.
                           - This will fail if the event is info-only.
                         */
                        result = event->stop();
                        if(result == FMOD_OK)
                        {
                            printf("event->stop() succeeded\n");
                            state_changed = true;
                        }
                        else
                        {
                            printf("event->stop() returned an error:\n\t(%d) %s\n", result, FMOD_ErrorString(result));
                        }
                    }
                    else
                    {
                        /* Attempt to start the event.
                           - This will fail if the event is info-only.
                         */
                        result = event->start();
                        if (result == FMOD_OK)
                        {
                            printf("event->start() succeeded\n");
                            state_changed = true;
                        }
                        else
                        {
                            printf("event->start() returned an error:\n\t(%d) %s\n", result, FMOD_ErrorString(result));
                        }
                    }
                }
            }
            else if (key >= '0' && key <= '9')
            {
                /* Attempt to set the event's volume.
                   - This will succeed on both info-only events and instances.
                   - Volume set on the info-only event will be copied to
                     all instances retrieved from now on.
                   - Volume set on an instance will only apply to that instance.
                 */
                float volume = (float)(key - '0');

                if (volume == 0)
                {
                    volume = 10.0f;
                }

                volume /= 10.0f;

                result = event->setVolume(volume);
                if (result == FMOD_OK)
                {
                    printf("event->setVolume() succeeded\n");
                    state_changed = true;
                }
                else
                {
                    printf("event->setVolume() returned an error:\n\t(%d) %s\n", result, FMOD_ErrorString(result));
                }
            }
            else if (key == 'u')
            {
                ERRCHECK(result = eventgroup->freeEventData());
                printf("Event data unloaded\n");
                state_changed = true;
            }

        }

        if (state_changed)
        {
            int memory_current, memory_max;
            ERRCHECK(result = FMOD::Memory_GetStats(&memory_current, &memory_max));

            printf("Memory usage: current = %10d, max = %10d\n", memory_current, memory_max);

            if (event)
            {
                /* Attempt to get the event's volume.
                   - This will succeed on both info-only events and instances.
                 */
                float volume;

                result = event->getVolume(&volume);
                if (result != FMOD_ERR_INVALID_HANDLE)
                {
                    ERRCHECK(result);
                    printf("Volume: %.2f\n", volume);
                }
            }

            state_changed = false;
        }

        ERRCHECK(result = eventsystem->update());
        fflush(stdout);
        Sleep(15);

    } while (key != 27);

    ERRCHECK(result = eventgroup->freeEventData());
    ERRCHECK(result = eventsystem->release());
    return 0;
}
