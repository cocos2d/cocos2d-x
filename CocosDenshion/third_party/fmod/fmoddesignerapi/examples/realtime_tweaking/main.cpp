/*===============================================================================================
 Realtime Tweaking Example
 Copyright (c), Firelight Technologies Pty, Ltd 2010-2011.

 Demonstrates basic usage of FMOD's network data-driven event library (fmod_event_net.dll)
===============================================================================================*/
#include "../../../examples/common/wincompat.h"

#include "../../api/inc/fmod_event.hpp"
#include "../../api/inc/fmod_event_net.hpp"
#include "../../../api/inc/fmod_errors.h"

const char *MEDIA_PATH = "../media/";
const int   NUM_EVENTS = 3;

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

FMOD_RESULT F_CALLBACK eventcallback(FMOD_EVENT *event, FMOD_EVENT_CALLBACKTYPE type, void *param1, void *param2, void *userdata)
{
    if (type == FMOD_EVENT_CALLBACKTYPE_NET_MODIFIED)
    {
        unsigned int t = (unsigned int)param2;
        printf("%p %s %f (%d)\n", event, (unsigned int)param1 == FMOD_EVENTPROPERTY_VOLUME ? "volume" : FMOD_EVENTPROPERTY_PITCH ? "pitch" : "???", *((float *)&t), (unsigned int)userdata);
    }

    return FMOD_OK;
}

int main(int argc, char *argv[])
{
    FMOD_RESULT        result;
    FMOD::EventSystem *eventsystem;
    FMOD::EventGroup  *eventgroup;
    FMOD::Event       *event[NUM_EVENTS];
    char              *event_name[NUM_EVENTS] = {
                           "Basics/BasicEventWithLooping",
                           "SequencingAndStitching/LoopLogic",
                           "3D Events/2D-3DPanMorph"
                       };
    int                key, i, userdata = 0;

    printf("======================================================================\n");
    printf("Realtime Tweaking. Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("======================================================================\n");
    printf("This example shows how to initialize the FMOD Net Event System so that\n");
    printf("FMOD Designer can connect to your game and tweak events as they're\n");
    printf("playing.\n");
    printf("Start some events then connect to this app using the Audition menu\n");
    printf("in FMOD Designer. Load examples.fdp and change the \n");
    printf("volume of the playing events using the volume slider in the event\n");
    printf("property sheet\n");
    printf("======================================================================\n\n");

    ERRCHECK(result = FMOD::EventSystem_Create(&eventsystem));
    ERRCHECK(result = FMOD::NetEventSystem_Init(eventsystem));
    ERRCHECK(result = eventsystem->init(64, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL));
    ERRCHECK(result = eventsystem->setMediaPath((char *)MEDIA_PATH));
    ERRCHECK(result = eventsystem->load("examples.fev", 0, 0));
    ERRCHECK(result = eventsystem->getGroup("examples/FeatureDemonstration", FMOD_EVENT_DEFAULT, &eventgroup));

    for (i=0; i < NUM_EVENTS; i++)
    {
        event[i] = 0;
    }

    printf("======================================================================\n");
    printf("Press 1 - 3  to start/stop events\n");
    printf("Press ESC    to quit\n");
    printf("======================================================================\n");

    key = 0;
    do
    {
        if (_kbhit())
        {
            key = _getch();

            if ((key >= '1') && (key <= '3'))
            {
                i = (int)(key - '1');

                if (event[i])
                {
                    ERRCHECK(result = event[i]->stop());
                    event[i] = 0;
                    printf("Stopping '%s'\n", event_name[i]);
                }
                else
                {
                    ERRCHECK(result = eventgroup->getEvent(event_name[i], FMOD_EVENT_DEFAULT, &event[i]));
                    ERRCHECK(result = event[i]->setCallback(eventcallback, (void *)(userdata++)));
                    ERRCHECK(result = event[i]->start());
                    printf("Starting '%s'\n", event_name[i]);
                }
            }
        }

        ERRCHECK(result = eventsystem->update());
        ERRCHECK(result = FMOD::NetEventSystem_Update());
        Sleep(10);

    } while (key != 27);

    ERRCHECK(result = eventsystem->release());
    ERRCHECK(result = FMOD::NetEventSystem_Shutdown());
    return 0;
}

