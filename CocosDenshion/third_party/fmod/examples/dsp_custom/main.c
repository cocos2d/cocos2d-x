/*===============================================================================================
 Custom DSP Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to add a user created DSP callback to process audio data.
 A read callback is generated at runtime, and can be added anywhere in the DSP network.

===============================================================================================*/
#include "../../api/inc/fmod.h"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"
#include <stdio.h>
#include <string.h>

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}


FMOD_RESULT F_CALLBACK myDSPCallback(FMOD_DSP_STATE *dsp_state, float *inbuffer, float *outbuffer, unsigned int length, int inchannels, int outchannels) 
{ 
    unsigned int count, userdata;
    int count2;
    char name[256]; 
    FMOD_DSP *thisdsp = dsp_state->instance; 

    /* 
        This redundant call just shows using the instance parameter of FMOD_DSP_STATE and using it to 
        call a DSP information function. 
    */
    FMOD_DSP_GetInfo(thisdsp, name, 0, 0, 0, 0);

    FMOD_DSP_GetUserData(thisdsp, (void **)&userdata);

    /*
        This loop assumes inchannels = outchannels, which it will be if the DSP is created with '0' 
        as the number of channels in FMOD_DSP_DESCRIPTION.  
        Specifying an actual channel count will mean you have to take care of any number of channels coming in,
        but outputting the number of channels specified.  Generally it is best to keep the channel 
        count at 0 for maximum compatibility.
    */
    for (count = 0; count < length; count++) 
    { 
        /*
            Feel free to unroll this.
        */
        for (count2 = 0; count2 < outchannels; count2++)
        {
            /* 
                This DSP filter just halves the volume! 
                Input is modified, and sent to output.
            */
            outbuffer[(count * outchannels) + count2] = inbuffer[(count * inchannels) + count2] * 0.2f;
        }
    } 

    return FMOD_OK; 
} 


int main(int argc, char *argv[])
{
    FMOD_SYSTEM       *system;
    FMOD_SOUND        *sound;
    FMOD_CHANNEL      *channel;
    FMOD_DSP          *mydsp;
    FMOD_RESULT        result;
    int                key;
    unsigned int       version;
    float              pan = 0;

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

    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    result = FMOD_System_CreateSound(system, "../media/drumloop.wav", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound);
    ERRCHECK(result);

    printf("===============================================================================\n");
    printf("Custom DSP example. Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("===============================================================================\n");
    printf("Press 'f' to activate, deactivate user filter\n");
    printf("Press 'Esc' to quit\n");
    printf("\n");

    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, FALSE, &channel);
    ERRCHECK(result);

    /*
        Create the DSP effects.
    */  
    { 
        FMOD_DSP_DESCRIPTION  dspdesc; 

        memset(&dspdesc, 0, sizeof(FMOD_DSP_DESCRIPTION)); 

        strcpy(dspdesc.name, "My first DSP unit"); 
        dspdesc.channels     = 0;                   // 0 = whatever comes in, else specify. 
        dspdesc.read         = myDSPCallback; 
        dspdesc.userdata     = (void *)0x12345678; 

        result = FMOD_System_CreateDSP(system, &dspdesc, &mydsp); 
        ERRCHECK(result); 
    } 

    /*
        Inactive by default.
    */
    FMOD_DSP_SetBypass(mydsp, TRUE);

    /*
        Main loop.
    */
    result = FMOD_System_AddDSP(system, mydsp, 0); 


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
                case 'f' : 
                case 'F' : 
                {
                    static int active = FALSE;

                    FMOD_DSP_SetBypass(mydsp, active);

                    active = !active;
                    break;
                }
            }
        }

        FMOD_System_Update(system);

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = FMOD_Sound_Release(sound);
    ERRCHECK(result);

    result = FMOD_DSP_Release(mydsp);
    ERRCHECK(result);

    result = FMOD_System_Close(system);
    ERRCHECK(result);
    result = FMOD_System_Release(system);
    ERRCHECK(result);

    return 0;
}


