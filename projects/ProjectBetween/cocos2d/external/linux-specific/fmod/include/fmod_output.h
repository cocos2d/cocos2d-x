/* ======================================================================================================== */
/* FMOD Studio - output development header file. Copyright (c), Firelight Technologies Pty, Ltd. 2004-2015. */
/*                                                                                                          */
/* Use this header if you are wanting to develop your own output plugin to use with                         */
/* FMOD's output system.  With this header you can make your own output plugin that FMOD                    */
/* can register and use.  See the documentation and examples on how to make a working plugin.               */
/*                                                                                                          */
/* ======================================================================================================== */

#ifndef _FMOD_OUTPUT_H
#define _FMOD_OUTPUT_H

typedef struct FMOD_OUTPUT_STATE FMOD_OUTPUT_STATE;

/*
    Output callbacks
*/ 
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_GETNUMDRIVERS_CALLBACK) (FMOD_OUTPUT_STATE *output_state, int *numdrivers);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_GETDRIVERINFO_CALLBACK) (FMOD_OUTPUT_STATE *output, int id, char *name, int namelen, FMOD_GUID *guid, int *systemrate, FMOD_SPEAKERMODE *speakermode, int *speakermodechannels);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_INIT_CALLBACK)          (FMOD_OUTPUT_STATE *output_state, int selecteddriver, FMOD_INITFLAGS flags, int *outputrate, FMOD_SPEAKERMODE *speakermode, int *speakermodechannels, FMOD_SOUND_FORMAT *outputformat, int dspbufferlength, int dspnumbuffers, void *extradriverdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_START_CALLBACK)         (FMOD_OUTPUT_STATE *output_state);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_STOP_CALLBACK)          (FMOD_OUTPUT_STATE *output_state);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_CLOSE_CALLBACK)         (FMOD_OUTPUT_STATE *output_state);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_UPDATE_CALLBACK)        (FMOD_OUTPUT_STATE *output_state);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_GETHANDLE_CALLBACK)      (FMOD_OUTPUT_STATE *output_state, void **handle);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_GETPOSITION_CALLBACK)    (FMOD_OUTPUT_STATE *output_state, unsigned int *pcm);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_LOCK_CALLBACK)           (FMOD_OUTPUT_STATE *output_state, unsigned int offset, unsigned int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_UNLOCK_CALLBACK)         (FMOD_OUTPUT_STATE *output_state, void *ptr1, void *ptr2, unsigned int len1, unsigned int len2);

typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_READFROMMIXER)          (FMOD_OUTPUT_STATE *output_state, void *buffer, unsigned int length);  /* This one is called by plugin through FMOD_OUTPUT_STATE, not set by user as a callback. */


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    When creating an output, declare one of these and provide the relevant callbacks and name for FMOD to use when it opens and reads a file of this type.

    [REMARKS]
    Members marked with [in] mean the variable can be written to.  The user can set the value.<br>
    Members marked with [out] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>

    [SEE_ALSO]
    FMOD_OUTPUT_STATE
]
*/
typedef struct FMOD_OUTPUT_DESCRIPTION
{
    const char                        *name;                  /* [in] Name of the output. */
    unsigned int                       version;               /* [in] Plugin writer's version number. */
    int                                polling;               /* [in] If TRUE (non zero), this tells FMOD to start a thread and call getposition / lock / unlock for feeding data.  If 0, the output is probably callback based, so all the plugin needs to do is call readfrommixer to the appropriate pointer. */ 
    FMOD_OUTPUT_GETNUMDRIVERS_CALLBACK  getnumdrivers;         /* [in] For sound device enumeration.  This callback is to give System::getNumDrivers somthing to return. */
    FMOD_OUTPUT_GETDRIVERINFO_CALLBACK  getdriverinfo;         /* [in] For sound device enumeration.  This callback is to give System::getDriverName somthing to return. */
    FMOD_OUTPUT_INIT_CALLBACK           init;                  /* [in] Initialization function for the output device.  This is called from System::init. */
    FMOD_OUTPUT_START_CALLBACK          start;                 /* [in] Initialization function for the output device to start accepting audio data from the FMOD software mixer.  This is called from System::init. */
    FMOD_OUTPUT_STOP_CALLBACK           stop;                  /* [in] Initialization function for the output device to stop accepting audio data from FMOD the software mixer.  This is called from System::close. */
    FMOD_OUTPUT_CLOSE_CALLBACK          close;                 /* [in] Cleanup / close down function for the output device.  This is called from System::close. */
    FMOD_OUTPUT_UPDATE_CALLBACK         update;                /* [in] Update function that is called once a frame by the user.  This is called from System::update. */
    FMOD_OUTPUT_GETHANDLE_CALLBACK      gethandle;             /* [in] This is called from System::getOutputHandle.  This is just to return a pointer to the internal system device object that the system may be using.*/
    FMOD_OUTPUT_GETPOSITION_CALLBACK    getposition;           /* [in] This is called from the FMOD software mixer thread if 'polling' = true.  This returns a position value in samples so that FMOD knows where and when to fill its buffer. */
    FMOD_OUTPUT_LOCK_CALLBACK           lock;                  /* [in] This is called from the FMOD software mixer thread if 'polling' = true.  This function provides a pointer to data that FMOD can write to when software mixing. */
    FMOD_OUTPUT_UNLOCK_CALLBACK         unlock;                /* [in] This is called from the FMOD software mixer thread if 'polling' = true.  This optional function accepts the data that has been mixed and copies it or does whatever it needs to before sending it to the hardware. */
} FMOD_OUTPUT_DESCRIPTION;


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Output plugin structure that is passed into each callback.

    [REMARKS]
    Members marked with [in] mean the variable can be written to.  The user can set the value.<br>
    Members marked with [out] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>

    [SEE_ALSO]
    FMOD_OUTPUT_DESCRIPTION
]
*/
struct FMOD_OUTPUT_STATE
{
    void                      *plugindata;      /* [in] Plugin writer created data the output author wants to attach to this object. */
    FMOD_OUTPUT_READFROMMIXER  readfrommixer;   /* [out] Function to update mixer and write the result to the provided pointer.  Used from callback based output only.  Polling based output uses lock/unlock/getposition. */
};

#endif


