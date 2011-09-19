/*===============================================================================================
 DSP_GAIN.SO
 Copyright (c), Firelight Technologies Pty, Ltd 2006-2011.

===============================================================================================*/

#include <stdio.h>
#include <stdlib.h>

#include "../../../api/inc/fmod.h"
#include "../../../api/inc/fmod_errors.h"

FMOD_RESULT F_CALLBACK dspcreate  (FMOD_DSP_STATE *dsp);
FMOD_RESULT F_CALLBACK dsprelease (FMOD_DSP_STATE *dsp);
FMOD_RESULT F_CALLBACK dspreset   (FMOD_DSP_STATE *dsp);
FMOD_RESULT F_CALLBACK dspread    (FMOD_DSP_STATE *dsp, float *inbuffer, float *outbuffer, unsigned int length, int inchannels, int outchannels);
FMOD_RESULT F_CALLBACK dspsetparam(FMOD_DSP_STATE *dsp, int index, float value);
FMOD_RESULT F_CALLBACK dspgetparam(FMOD_DSP_STATE *dsp, int index, float *value, char *valuestr);


/*
    DSP Parameter list.
*/
FMOD_DSP_PARAMETERDESC dspparam[1] =
{
    { 0.0f,     1.0f,   1.0, "Level",   "%",     "Gain level" },
};


FMOD_DSP_DESCRIPTION dspgaindesc =
{
    "FMOD gain example",        // name
    0x00010000,                 // version 0xAAAABBBB   A = major, B = minor.
    0,                          // 0 = we can filter whatever you throw at us.  To be most user friendly, always write a filter like this.
    dspcreate,                  //
    dsprelease,                 //
    dspreset,                   //
    dspread,                    //
    0,                          // This is for if you want to allow the plugin to seek, which doesnt really make sense in a gain filter so we'll just leave it out.
    1,                          // 1 parameter.  "level"
    dspparam,                   // pointer to the parameter list definition.
    dspsetparam,                //
    dspgetparam,                //
    0,                          // This is for if you want to pop up a dialog box to configure the plugin.  Not doing that here.
    0,                          // This is for if you want to pop up a dialog box to configure the plugin.  Not doing that here.
    0,                          // This is for if you want to pop up a dialog box to configure the plugin.  Not doing that here.
};

/*
    FMODGetDSPDescription is mandantory for every fmod plugin.  This is the symbol the registerplugin function searches for.
    Must be declared with F_API to make it export as stdcall.
    MUST BE EXTERN'ED AS C!  C++ functions will be mangled incorrectly and not load in fmod.
*/
#ifdef __cplusplus
extern "C" {
#endif

F_DECLSPEC F_DLLEXPORT FMOD_DSP_DESCRIPTION * F_API FMODGetDSPDescription()
{
    return &dspgaindesc;
}

#ifdef __cplusplus
}
#endif


typedef struct dspgain_state
{
    float gain;
} dspgain_state;


FMOD_RESULT F_CALLBACK dspcreate(FMOD_DSP_STATE *dsp)
{
    dspgain_state *state;

    /*
        If we were allocating memory for buffers etc, it would be done in this function.
    */

    state = (dspgain_state *)malloc(sizeof(dspgain_state));
    if (!state)
    {
        return FMOD_ERR_MEMORY;
    }

    state->gain = dspparam[0].defaultval;

    dsp->plugindata = state;

    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK dsprelease(FMOD_DSP_STATE *dsp)
{
    dspgain_state *state = (dspgain_state *)dsp->plugindata;

    /*
        If memory was allocated in create, it would be freed in this function.
    */

    free(state);
    
    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK dspreset(FMOD_DSP_STATE *dsp)
{
    dspgain_state *state = (dspgain_state *)dsp->plugindata;

    /*
        This isnt really needed here.  It is used to reset a filter back to it's default state.
    */

    state->gain = dspparam[0].defaultval;

    return FMOD_OK;
}


/*
    This callback does the work.  Modify data from inbuffer and send it to outbuffer.
*/
FMOD_RESULT F_CALLBACK dspread(FMOD_DSP_STATE *dsp, float *inbuffer, float *outbuffer, unsigned int length, int inchannels, int outchannels)
{
    dspgain_state *state = (dspgain_state *)dsp->plugindata;
    unsigned int count;
    int count2;
    int channels = inchannels;  // outchannels and inchannels will always be the same because this is a flexible filter.

    for (count = 0; count < length; count++)
    {
        for (count2 = 0; count2 < channels; count2++)
        {
            outbuffer[(count * channels) + count2] = inbuffer[(count * channels) + count2] * state->gain;
        }
    }

    return FMOD_OK;
}

/*
    This callback is for when the user sets a parameter.  It is automatically clamped between 0 and 1.
*/
FMOD_RESULT F_CALLBACK dspsetparam(FMOD_DSP_STATE *dsp, int index, float value)
{
    dspgain_state *state = (dspgain_state *)dsp->plugindata;

    switch (index)
    {
        case 0:
        {
            state->gain = value;
            break;
        }
    }
    return FMOD_OK;
}

/*
    This callback is for when the user gets a parameter.  The label for our only parameter is percent, 
    so when the string is requested print it out as 0 to 100.
*/
FMOD_RESULT F_CALLBACK dspgetparam(FMOD_DSP_STATE *dsp, int index, float *value, char *valuestr)
{
    dspgain_state *state = (dspgain_state *)dsp->plugindata;

    switch (index)
    {
        case 0:
        {
            *value = state->gain;
            sprintf(valuestr, "%.02f", state->gain * 100.0f);    // our units are '%', so print it out as 0 to 100.
        }
    }

    return FMOD_OK;
}

