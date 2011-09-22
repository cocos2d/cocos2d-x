/*=============================================================================
 Programmer Selected Sound Definition Example
 Copyright (c), Firelight Technologies Pty, Ltd 2007-2011.

 Demonstrates how to use the "programmer selected sound definition" feature of
 the FMOD event system
=============================================================================*/
#include "../../../examples/common/wincompat.h"

#include "../../api/inc/fmod_event.hpp"
#include "../../../api/inc/fmod_errors.h"

const char   *MEDIA_PATH = "../media/";

static int g_sounddef_entry_index = 0;


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
    switch (type)
    {
        case FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_SELECTINDEX :
        {
            char *name = (char *)param1;                    // [in]  (char *) name of sound definition
            int *index = (int *)param2;                     // [out] (int *) the sounddef entry index to use

            *index = (g_sounddef_entry_index < *index) ? g_sounddef_entry_index : *index - 1;
            printf("FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_SELECTINDEX '%s': %d\n", name, *index);

            break;
        }
    }

    return FMOD_OK;
}


int main(int argc, char *argv[])
{
    FMOD_RESULT        result;
    FMOD::EventSystem *eventsystem;
    FMOD::EventGroup  *eventgroup;
    FMOD::Event       *event;
    int                key;

    ERRCHECK(result = FMOD::EventSystem_Create(&eventsystem));
    ERRCHECK(result = eventsystem->init(64, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL));
    ERRCHECK(result = eventsystem->setMediaPath((char *)MEDIA_PATH));
    ERRCHECK(result = eventsystem->load("examples.fev", 0, 0));
    ERRCHECK(result = eventsystem->getGroup("examples/FeatureDemonstration/SequencingAndStitching", FMOD_EVENT_DEFAULT, &eventgroup));

    printf("======================================================================\n");
    printf("Programmer Selected Sound Definition.\n");
    printf("Copyright (c) Firelight Technologies 2006-2011.\n");
    printf("----------------------------------------------------------------------\n");
    printf("Press 'Space' to start the 'Programmer Selected' event\n");
    printf("Press '>'     to increase sound definition entry index\n");
    printf("Press '<'     to decrease sound definition entry index\n");
    printf("Press 'Esc'   to quit\n");
    printf("======================================================================\n");
    printf("Sound definition entry index = %d\n", g_sounddef_entry_index);

    key = 0;
    do
    {
        if (_kbhit())
        {
            key = _getch();

            switch(key)
            {
                case ' ' :
                    ERRCHECK(result = eventgroup->getEvent("ProgrammerSelected", FMOD_EVENT_DEFAULT, &event));
                    ERRCHECK(result = event->setCallback(eventcallback, 0));
                    ERRCHECK(result = event->start());
                    break;

                case '>' :
                    ++g_sounddef_entry_index;
                    printf("Sound definition entry index = %d\n", g_sounddef_entry_index);
                    break;

                case '<' :
                    --g_sounddef_entry_index;
                    g_sounddef_entry_index = (g_sounddef_entry_index < 0) ? 0 : g_sounddef_entry_index;
                    printf("Sound definition entry index = %d\n", g_sounddef_entry_index);
                    break;
            }
        }

        ERRCHECK(result = eventsystem->update());
        fflush(stdout);
        Sleep(10);

    } while (key != 27);

    ERRCHECK(result = eventsystem->unload());
    ERRCHECK(result = eventsystem->release());
    return 0;
}
