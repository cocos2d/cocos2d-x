/*$ preserve start $*/

/* ============================================================================================ */
/* FMOD Ex - Main C/C++ event/data driven system header file.                                   */
/* Copyright (c), Firelight Technologies Pty, Ltd. 2004-2011.                                   */
/*                                                                                              */
/* This header is the base header for all other FMOD EventSystem headers. If you are            */
/* programming in C use this exclusively, or if you are programming C++ use this in             */
/* conjunction with FMOD_EVENT.HPP                                                              */
/* ============================================================================================ */

#ifndef __FMOD_EVENT_H__
#define __FMOD_EVENT_H__

#ifndef _FMOD_H
#include "fmod.h"
#endif

/*
    FMOD EventSystem version number.  Check this against FMOD::EventSystem::getVersion.
    0xaaaabbcc -> aaaa = major version number.  bb = minor version number.  cc = development version number.
*/

#define FMOD_EVENT_VERSION 0x00043601

/*
    FMOD event types
*/

typedef struct FMOD_EVENTSYSTEM     FMOD_EVENTSYSTEM;
typedef struct FMOD_EVENTPROJECT    FMOD_EVENTPROJECT;
typedef struct FMOD_EVENTGROUP      FMOD_EVENTGROUP;
typedef struct FMOD_EVENTCATEGORY   FMOD_EVENTCATEGORY;
typedef struct FMOD_EVENT           FMOD_EVENT;
typedef struct FMOD_EVENTPARAMETER  FMOD_EVENTPARAMETER;
typedef struct FMOD_EVENTREVERB     FMOD_EVENTREVERB;
typedef struct FMOD_EVENTQUEUE      FMOD_EVENTQUEUE;
typedef struct FMOD_EVENTQUEUEENTRY FMOD_EVENTQUEUEENTRY;
typedef struct FMOD_MUSICPROMPT     FMOD_MUSICPROMPT;
typedef struct FMOD_MUSICSYSTEM     FMOD_MUSICSYSTEM;
typedef unsigned int                FMOD_EVENT_INITFLAGS;
typedef unsigned int                FMOD_EVENT_MODE;
typedef unsigned int                FMOD_EVENT_STATE;
typedef unsigned int                FMOD_MUSIC_ID;
typedef FMOD_MUSIC_ID               FMOD_MUSIC_CUE_ID;
typedef FMOD_MUSIC_ID               FMOD_MUSIC_PARAM_ID;


/*
[DEFINE]
[
    [NAME]
    FMOD_EVENT_INITFLAGS

    [DESCRIPTION]   
    Initialization flags.  Use them with EventSystem::init in the eventflags parameter to change various behaviour.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    EventSystem::init
    EventSystem::getEventByGUID
    FMOD_EVENT_SOUNDDEFINFO
    FMOD_EVENT_CALLBACKTYPE
]
*/
#define FMOD_EVENT_INIT_NORMAL                            0x00000000 /* All platforms - Initialize normally */
#define FMOD_EVENT_INIT_USER_ASSETMANAGER                 0x00000001 /* All platforms - All wave data loading/freeing will be referred back to the programmer through the FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_CREATE/FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_RELEASE callback */
#define FMOD_EVENT_INIT_FAIL_ON_MAXSTREAMS                0x00000002 /* All platforms - Events will fail if "Max streams" was reached when playing streamed banks, instead of going virtual. */
#define FMOD_EVENT_INIT_DONTUSENAMES                      0x00000004 /* All platforms - All event/eventgroup/eventparameter/eventcategory/eventreverb names will be discarded on load. Use getXXXByIndex to access them. This may potentially save a lot of memory at runtime. */
#define FMOD_EVENT_INIT_UPPERCASE_FILENAMES               0x00000008 /* All platforms - All FSB filenames will be translated to upper case before being used. */
#define FMOD_EVENT_INIT_LOWERCASE_FILENAMES               0x00000080 /* All platforms - All FSB filenames will be translated to lower case before being used. */
#define FMOD_EVENT_INIT_SEARCH_PLUGINS                    0x00000010 /* All platforms - Search the current directory for dsp/codec plugins on EventSystem::init. */
#define FMOD_EVENT_INIT_USE_GUIDS                         0x00000020 /* All platforms - Build an event GUID table when loading FEVs so that EventSystem::getEventByGUID can be used. */
#define FMOD_EVENT_INIT_DETAILED_SOUNDDEF_INFO            0x00000040 /* All platforms - Pass an FMOD_EVENT_SOUNDDEFINFO struct to FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_SELECTINDEX callbacks rather than just the sound definition name (uses more memory for sound definition waveform names). */
#define FMOD_EVENT_INIT_RESETPARAMSTOMINIMUM              0x00000100 /* All platforms - Reset parameters to minimum value when getting an event instance instead of using the INFO_ONLY event's values. */
#define FMOD_EVENT_INIT_ELEVATION_AFFECTS_LISTENER_ANGLE  0x00000200 /* All platforms - The listener angle event parameters will be affected by elevation, and not just horizontal components. */
#define FMOD_EVENT_INIT_DONTUSELOWMEM                     0x00000400 /* All platforms - Instruct the event system to NOT use FMOD_LOWMEM when it opens .FSB files. Specify this flag if you need access to the names of individual subsounds in loaded .FSB files. Specifying this flag will make the event system use more memory. */

/* [DEFINE_END] */


/*
[DEFINE]
[
    [NAME] 
    FMOD_EVENT_MODE

    [DESCRIPTION]   
    Event data loading bitfields. Bitwise OR them together for controlling how event data is loaded.

    [REMARKS]
    FMOD_EVENT_NONBLOCKING_THREAD0-4.  This flag extends FMOD_EVENT_NONBLOCKING to allow multiple asynchronous loads to happen on different threads at the same time.<br>
    FMOD_EVENT_NONBLOCKING by itself will always execute on thread 0 by default.  Up to 5 simultaneous threads for loading at once are supported.<br>
    Only 1 flag should be specified at a time.  If multiple flags are specified an FMOD_ERR_INVALID_PARAM error will be returned.<br>
    FMOD_EVENT_NONBLOCKING_THREAD0-4 can be specified without the FMOD_EVENT_NONBLOCKING flag being used (it automatically includes it)

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    EventGroup::loadEventData
    EventGroup::getEvent
    EventGroup::getEventByIndex
]
*/
#define FMOD_EVENT_DEFAULT               0x00000000  /* FMOD_EVENT_DEFAULT specifies default loading behaviour i.e. event data for the whole group is NOT cached and the function that initiated the loading process will block until loading is complete. */
#define FMOD_EVENT_NONBLOCKING           0x00000001  /* For loading event data asynchronously. FMOD will use a thread to load the data.  Use Event::getState to find out when loading is complete. */
#define FMOD_EVENT_ERROR_ON_DISKACCESS   0x00000002  /* For EventGroup::getEvent / EventGroup::getEventByIndex.  If EventGroup::loadEventData has accidently been forgotten this flag will return an FMOD_ERR_FILE_UNWANTED if the getEvent function tries to load data. */
#define FMOD_EVENT_INFOONLY              0x00000004  /* For EventGroup::getEvent / EventGroup::getEventByIndex.  Don't allocate instances or load data, just get a handle to allow user to get information from the event. */
#define FMOD_EVENT_USERDSP               0x00000008  /* For EventGroup::getEvent / EventGroup::getEventByIndex.  Tells FMOD that you plan to add your own DSP effects to this event's ChannelGroup at runtime. Omitting this flag will yield a small memory gain. */

#define FMOD_EVENT_NONBLOCKING_THREAD0   (FMOD_EVENT_NONBLOCKING)               /* FMOD_EVENT_NONBLOCKING, execute on thread 0.  See remarks. (default) */
#define FMOD_EVENT_NONBLOCKING_THREAD1   (FMOD_EVENT_NONBLOCKING | 0x00010000)  /* FMOD_EVENT_NONBLOCKING, execute on thread 1.  See remarks. */
#define FMOD_EVENT_NONBLOCKING_THREAD2   (FMOD_EVENT_NONBLOCKING | 0x00020000)  /* FMOD_EVENT_NONBLOCKING, execute on thread 2.  See remarks. */
#define FMOD_EVENT_NONBLOCKING_THREAD3   (FMOD_EVENT_NONBLOCKING | 0x00040000)  /* FMOD_EVENT_NONBLOCKING, execute on thread 3.  See remarks. */
#define FMOD_EVENT_NONBLOCKING_THREAD4   (FMOD_EVENT_NONBLOCKING | 0x00080000)  /* FMOD_EVENT_NONBLOCKING, execute on thread 4.  See remarks. */
/* [DEFINE_END] */


/*
[DEFINE]
[
    [NAME] 
    FMOD_EVENT_STATE

    [DESCRIPTION]   
    These values describe what state an event is in.

    [REMARKS]    
    The flags below can be combined to set multiple states at once.  Use bitwise AND operations to test for these.
    An example of a combined flag set would be FMOD_EVENT_STATE_READY | FMOD_EVENT_STATE_PLAYING.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    Event::getState
    FMOD_EVENT_MODE
]
*/
#define FMOD_EVENT_STATE_READY           0x00000001  /* Event is ready to play. */
#define FMOD_EVENT_STATE_LOADING         0x00000002  /* Loading in progress. */
#define FMOD_EVENT_STATE_ERROR           0x00000004  /* Failed to open - file not found, out of memory etc.  See return value of Event::getState for what happened. */
#define FMOD_EVENT_STATE_PLAYING         0x00000008  /* Event has been started.  This will still be true even if there are no sounds active.  Event::stop must be called or the event must stop itself using a 'one shot and stop event' parameter mode. */
#define FMOD_EVENT_STATE_CHANNELSACTIVE  0x00000010  /* Event has active voices.  Use this if you want to detect if sounds are playing in the event or not. */
#define FMOD_EVENT_STATE_INFOONLY        0x00000020  /* Event was loaded with the FMOD_EVENT_INFOONLY flag. */
#define FMOD_EVENT_STATE_STARVING        0x00000040  /* Event is streaming but not being fed data in time, so may be stuttering. */
/* [DEFINE_END] */


/*
[ENUM]
[
	[DESCRIPTION]
    Property indices for Event::getPropertyByIndex.
    
	[REMARKS]        

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

	[SEE_ALSO]
    Event::getPropertyByIndex
]
*/
typedef enum
{
    FMOD_EVENTPROPERTY_NAME = 0,                        /* Type : char *    - (<b>Readonly</b>) Name of event. */
    FMOD_EVENTPROPERTY_VOLUME,                          /* Type : float     - Relative volume of event. */
    FMOD_EVENTPROPERTY_VOLUMERANDOMIZATION,             /* Type : float     - Random deviation in volume of event. */
    FMOD_EVENTPROPERTY_PITCH,                           /* Type : float     - Relative pitch of event in raw underlying units. */
    FMOD_EVENTPROPERTY_PITCH_OCTAVES,                   /* Type : float     - Relative pitch of event in octaves. */
    FMOD_EVENTPROPERTY_PITCH_SEMITONES,                 /* Type : float     - Relative pitch of event in semitones. */
    FMOD_EVENTPROPERTY_PITCH_TONES,                     /* Type : float     - Relative pitch of event in tones. */
    FMOD_EVENTPROPERTY_PITCHRANDOMIZATION,              /* Type : float     - Random deviation in pitch of event in raw underlying units. */
    FMOD_EVENTPROPERTY_PITCHRANDOMIZATION_OCTAVES,      /* Type : float     - Random deviation in pitch of event in octaves. */
    FMOD_EVENTPROPERTY_PITCHRANDOMIZATION_SEMITONES,    /* Type : float     - Random deviation in pitch of event in semitones. */
    FMOD_EVENTPROPERTY_PITCHRANDOMIZATION_TONES,        /* Type : float     - Random deviation in pitch of event in tones. */
    FMOD_EVENTPROPERTY_PRIORITY,                        /* Type : int       - Playback priority of event. */
    FMOD_EVENTPROPERTY_MAX_PLAYBACKS,                   /* Type : int       - (<b>Readonly</b>) Maximum simultaneous playbacks of event. */
    FMOD_EVENTPROPERTY_MAX_PLAYBACKS_BEHAVIOR,          /* Type : int       - 1 = steal oldest, 2 = steal newest, 3 = steal quietest, 4 = just fail, 5 = just fail if quietest. */
    FMOD_EVENTPROPERTY_MODE,                            /* Type : FMOD_MODE - Either FMOD_3D or FMOD_2D. */
    FMOD_EVENTPROPERTY_3D_IGNORE_GEOMETRY,              /* Type : int       - Ignore geometry for that event. 1 = yes,  0 = no. */
    FMOD_EVENTPROPERTY_3D_ROLLOFF,                      /* Type : FMOD_MODE - Either FMOD_3D_INVERSEROLLOFF, FMOD_3D_LINEARROLLOFF, FMOD_3D_LINEARSQUAREROLLOFF, or none for custom rolloff. */
    FMOD_EVENTPROPERTY_3D_MINDISTANCE,                  /* Type : float     - Minimum 3d distance of event. */
    FMOD_EVENTPROPERTY_3D_MAXDISTANCE,                  /* Type : float     - Maximum 3d distance of event.  Means different things depending on EVENTPROPERTY_3D_ROLLOFF. If event has custom rolloff, setting FMOD_EVENTPROPERTY_3D_MAXDISTANCE will scale the range of all distance parameters in this event e.g. set this property to 2.0 to double the range of all distance parameters, set it to 0.5 to halve the range of all distance parameters. */
    FMOD_EVENTPROPERTY_3D_POSITION,                     /* Type : FMOD_MODE - Either FMOD_3D_HEADRELATIVE or FMOD_3D_WORLDRELATIVE. */
    FMOD_EVENTPROPERTY_3D_CONEINSIDEANGLE,              /* Type : float     - Event cone inside angle.  0 to 360. */
    FMOD_EVENTPROPERTY_3D_CONEOUTSIDEANGLE,             /* Type : float     - Event cone outside angle.  0 to 360. */
    FMOD_EVENTPROPERTY_3D_CONEOUTSIDEVOLUME,            /* Type : float     - Event cone outside volume.  0 to 1.0. */
    FMOD_EVENTPROPERTY_3D_DOPPLERSCALE,                 /* Type : float     - Doppler scale where 0 = no doppler, 1.0 = normal doppler, 2.0 = double doppler etc. */
    FMOD_EVENTPROPERTY_3D_SPEAKERSPREAD,                /* Type : float     - Angle of spread for stereo/mutlichannel source. 0 to 360. */
    FMOD_EVENTPROPERTY_3D_PANLEVEL,                     /* Type : float     - 0 = sound pans according to speaker levels, 1 = sound pans according to 3D position. */
    FMOD_EVENTPROPERTY_SPEAKER_L,                       /* Type : float     - 2D event volume for front left speaker. */
    FMOD_EVENTPROPERTY_SPEAKER_C,                       /* Type : float     - 2D event volume for front center speaker. */
    FMOD_EVENTPROPERTY_SPEAKER_R,                       /* Type : float     - 2D event volume for front right speaker. */
    FMOD_EVENTPROPERTY_SPEAKER_LS,                      /* Type : float     - 2D event volume for side left speaker. */
    FMOD_EVENTPROPERTY_SPEAKER_RS,                      /* Type : float     - 2D event volume for side right speaker. */
    FMOD_EVENTPROPERTY_SPEAKER_LR,                      /* Type : float     - 2D event volume for back left speaker. */
    FMOD_EVENTPROPERTY_SPEAKER_RR,                      /* Type : float     - 2D event volume for back right speaker. */
    FMOD_EVENTPROPERTY_SPEAKER_LFE,                     /* Type : float     - 2D event volume for low frequency speaker. */
    FMOD_EVENTPROPERTY_REVERBWETLEVEL,                  /* Type : float     - Reverb gain for this event where 0 = full reverb, -60 = no reverb. */
    FMOD_EVENTPROPERTY_ONESHOT,                         /* Type : int       - Oneshot event - stops when no channels playing. 1 = yes, it's a oneshot  0 = no. it's not a oneshot. */
    FMOD_EVENTPROPERTY_FADEIN,                          /* Type : int       - Time in milliseconds over which to fade this event in when programmer starts it. 0 = no fade in. Cannot be set while the event is playing. */
    FMOD_EVENTPROPERTY_FADEOUT,                         /* Type : int       - Time in milliseconds over which to fade this event out when programmer stops it. 0 = no fade out. Cannot be set while the event is playing. */
    FMOD_EVENTPROPERTY_REVERBDRYLEVEL,                  /* Type : float     - Dry reverb gain for this event where 0 = full dry, -60 = no dry. */
    FMOD_EVENTPROPERTY_TIMEOFFSET,                      /* Type : float     - Time offset of sound start in seconds. */
    FMOD_EVENTPROPERTY_SPAWNINTENSITY,                  /* Type : float     - Multiplier for spawn frequency of all sounds in this event. */
    FMOD_EVENTPROPERTY_SPAWNINTENSITY_RANDOMIZATION,    /* Type : float     - Random deviation in spawn intensity of event. */
    FMOD_EVENTPROPERTY_WII_CONTROLLERSPEAKERS,          /* Type : int       - Wii only. Use FMOD_WII_CONTROLLER flags defined in fmodwii.h to set which Wii Controller Speaker(s) to play this event on. */
	FMOD_EVENTPROPERTY_3D_POSRANDOMIZATION_MIN,         /* Type : unsigned int   - Minimum radius of random deviation in the 3D position of event. */
	FMOD_EVENTPROPERTY_3D_POSRANDOMIZATION_MAX,         /* Type : unsigned int   - Maximum radius of random deviation in the 3D position of event. */
    FMOD_EVENTPROPERTY_EVENTTYPE,                       /* Type : int       - (<b>Readonly</b>) 0 = simple event, 1 = complex event */
    FMOD_EVENTPROPERTY_STEAL_PRIORITY,                  /* Type : int       - 0 to 10000.  How important this event is in relation to other events in the project. This event will never steal an event with a higher steal priority than this. */
    FMOD_EVENTPROPERTY_EFFECTS_AFFECT_REVERB,           /* Type : int       - 0 = default (no), 1 = yes.  Alternate routing for reverb path of an event so it goes from the layer dsp unit instead of the channel. */
    FMOD_EVENTPROPERTY_WILL_TERMINATE,                  /* Type : int       - (<b>Readonly</b>) 0 = no, 1 = yes, 2 = unknown (current event state is too complex).  Whether this event will terminate (stop playing) by itself. If called on an event instance with this_instance = true, the prediction is based on the current state of that instance. This means parameter values, keyoffs etc. come into play. */
    FMOD_EVENTPROPERTY_DSPCLOCKSTART_HI,                /* Type : unsigned int - High 32 bits of a 64 bit DSP clock value, for a start time for any sound in this event. */
    FMOD_EVENTPROPERTY_DSPCLOCKSTART_LO,                /* Type : unsigned int - Low 32 bits of a 64 bit DSP clock value, for a start time for any sound in this event. */
    FMOD_EVENTPROPERTY_3D_AUTO_DISTANCE_FILTERING,      /* Type : int       - 0 = default (no), 1 = yes. Whether to automaically apply the distance effect to sounds in this event. */
    FMOD_EVENTPROPERTY_3D_AUTO_DISTANCE_CENTRE_FREQ,    /* Type : float     - 10 to 22050. The centre frequency for the distance effect.*/
    FMOD_EVENTPROPERTY_USER_BASE                        /* User created events start from here onwards. */
} FMOD_EVENT_PROPERTY;


/*
[ENUM]
[
	[DESCRIPTION]
    Event property types.
    
	[REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

	[SEE_ALSO]
    Event::getPropertyByIndex
    Event::getPropertyInfo
]
*/
typedef enum
{
    FMOD_EVENTPROPERTY_TYPE_INT = 0,                     /* Property is an int, unsigned int or other type of equivalent sizee e.g. FMOD_MODE. */
    FMOD_EVENTPROPERTY_TYPE_FLOAT,                      /* Property is a float. */
    FMOD_EVENTPROPERTY_TYPE_STRING                      /* Property is a char *. */
} FMOD_EVENTPROPERTY_TYPE;


/*
[ENUM]
[
	[DESCRIPTION]
    Pitch units for Event::setPitch and EventCategory::setPitch.
    
	[REMARKS]        

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

	[SEE_ALSO]
    Event::setPitch
    EventCategory::setPitch
]
*/
typedef enum
{
    FMOD_EVENT_PITCHUNITS_RAW = 0,      /* Pitch is specified in raw underlying units. */
    FMOD_EVENT_PITCHUNITS_OCTAVES,      /* Pitch is specified in units of octaves. */
    FMOD_EVENT_PITCHUNITS_SEMITONES,    /* Pitch is specified in units of semitones. */
    FMOD_EVENT_PITCHUNITS_TONES         /* Pitch is specified in units of tones. */
} FMOD_EVENT_PITCHUNITS;


/*
[ENUM]
[
	[DESCRIPTION]
    Flags to pass to EventGroup::loadEventData to determine what to load at the time of calling.
    
	[REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

	[SEE_ALSO]
    EventGroup::loadEventData
]
*/
typedef enum
{
    FMOD_EVENT_RESOURCE_STREAMS_AND_SAMPLES,  /* Open all streams and load all banks into memory, under this group (recursive) */
    FMOD_EVENT_RESOURCE_STREAMS,              /* Open all streams under this group (recursive).  No samples are loaded. */
    FMOD_EVENT_RESOURCE_SAMPLES               /* Load all banks into memory, under this group (recursive).  No streams are opened. */
} FMOD_EVENT_RESOURCE;


/*
[ENUM]
[
    [DESCRIPTION]   
    These callback types are used with FMOD_EVENT_CALLBACK.

    [REMARKS]
    <b>Note!</b> Currently the user must call EventSystem::update for these callbacks to trigger!<p>

    When the event callback is called, 'param1' and 'param2' mean different things depending on the type of callback. Here is an explanation of what these parameters
    mean in what context :<p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_SYNCPOINT</b>
    <p>
    param1 = (char *) name of sync point<br>
    param2 = (unsigned int) PCM offset of sync point.<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_SYNCPOINT callback is generated from 'markers' embedded in .wav files.
    These can be created by placing 'markers' in the original source wavs using a tool such as Sound Forge or Cooledit.
    The wavs are then compiled into .FSB files when compiling the audio data using the FMOD designer tool.
    Callbacks will be automatically generated at the correct place in the timeline when these markers are encountered
    which makes it useful for synchronization, lip syncing etc.
    <p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_START</b>
    <p>
    param1 = (char *) name of sound definition being started<br>
    param2 = (int) index of wave being started inside sound definition (ie for multi wave sound definitions)<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_START callback is generated each time a sound definition is played in an event.
    This happens every time a sound definition starts due to the event parameter entering the region specified in the 
    layer created by the sound designer.
    This also happens when sounds are randomly respawned using the random respawn feature in the sound definition 
    properties in FMOD designer.
    <p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_END</b>
    <p>
    param1 = (char *) name of sound definition being stopped<br>
    param2 = (int) index of wave being stopped inside sound definition (ie for multi wave sound definitions)<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_END callback is generated when a one-shot sound definition inside an event ends, 
    or when a looping sound definition stops due to the event parameter leaving the region specified in the layer created 
    by the sound designer.
    <p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_STOLEN</b>
    <p>
    param1 = 0<br>
    param2 = 0<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_STOLEN callback is generated when a getEventXXX call needs to steal an event instance that is in use because 
    the event's "Max playbacks" has been exceeded. This callback is called before the event is stolen and before the event 
    is stopped (if it is playing). An FMOD_EVENT_CALLBACKTYPE_EVENTFINISHED callback will be generated when the stolen event is stopped i.e. <b>after</b>
    the FMOD_EVENT_CALLBACKTYPE_STOLEN. If the callback function returns FMOD_ERR_EVENT_FAILED, the event will <b>not</b>
    be stolen, and the returned value will be passed back as the return value of the getEventXXX call that triggered the steal attempt.
    <p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_EVENTFINISHED</b>
    <p>
    param1 = 0<br>
    param2 = 0<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_EVENTFINISHED callback is generated whenever an event is stopped for any reason including when the user
    calls Event::stop().
    <p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_NET_MODIFIED</b>
    <p>
    param1 = (FMOD_EVENT_PROPERTY) which property was modified<br>
    param2 = (float) the new property value<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_NET_MODIFIED callback is generated when someone has connected to your running application with 
    FMOD Designer and changed a property within this event, for example volume or pitch.
    <p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_CREATE</b>
    <p>
    param1 = (char *) name of sound definition<br>
    param2 [in] = (int *) pointer to index of sound definition entry<br>
    param2 [out] = (FMOD::Sound **) pointer to a valid lower level API FMOD Sound handle<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_CREATE callback is generated when a "programmer" sound needs to be loaded.
    <p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_RELEASE</b>
    <p>
    param1 = (char *) name of sound definition<br>
    param2 = (FMOD::Sound *) the FMOD sound handle that was previously created in FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_CREATE<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_RELEASE callback is generated when a "programmer" sound needs to be unloaded.
    <p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_INFO</b>
    <p>
    param1 = (char *) name of sound definition<br>
    param2 = (FMOD::Sound *) the FMOD sound handle that FMOD will use for this sound definition<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_INFO callback is generated when a sound definition is loaded. It can be used to find
    information about the specific sound that will be played.
    <p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_EVENTSTARTED</b>
    <p>
    param1 = 0<br>
    param2 = 0<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_EVENTSTARTED callback is generated whenever an event is started. This callback will be called before any sounds in the event have begun to play.
    <p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_SELECTINDEX</b>
    <p>
    param1 = (char *) name of sound definition if FMOD_EVENT_INIT_DETAILED_SOUNDDEF_INFO was not specified<br>
    param1 = (FMOD_EVENT_SOUNDDEFINFO *) sound definition info struct if FMOD_EVENT_INIT_DETAILED_SOUNDDEF_INFO was specified<br>
    param2 [in] = (int *) pointer to number of entries in this sound definition<br>
    *param2 [out] = (int) index of sound definition entry to select<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_SELECTINDEX callback is generated when a sound definition entry needs to be chosen from a "ProgrammerSelected" sound definition.
    <p>&nbsp;<p>

    <b>FMOD_EVENT_CALLBACKTYPE_OCCLUSION</b>
    <p>
    param1 = (float *) pointer to a floating point direct value that can be read and modified after the geometry engine has calculated it for this event's channel.<br>
    param2 = (float *) pointer to a floating point reverb value that can be read and modified after the geometry engine has calculated it for this event's channel.<br>
    <p>
    An FMOD_EVENT_CALLBACKTYPE_OCCLUSION callback is generated whenever an channel has its occlusion updated via the geometry system.
    <p>&nbsp;<p>

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    Event::setCallback
    FMOD_EVENT_CALLBACK
    FMOD_EVENT_SOUNDDEFINFO
    FMOD_EVENT_INITFLAGS
    EventSystem::update
]
*/
typedef enum
{
    FMOD_EVENT_CALLBACKTYPE_SYNCPOINT,            /* Called when a syncpoint is encountered. Can be from wav file markers. */
    FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_START,       /* Called when a sound definition inside an event is triggered. */
    FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_END,         /* Called when a sound definition inside an event ends or is stopped. */
    FMOD_EVENT_CALLBACKTYPE_STOLEN,               /* Called when a getEventXXX call steals an event instance that is in use. */
    FMOD_EVENT_CALLBACKTYPE_EVENTFINISHED,        /* Called when an event is stopped for any reason. */
    FMOD_EVENT_CALLBACKTYPE_NET_MODIFIED,         /* Called when a property of the event has been modified by a network-connected host. */
    FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_CREATE,      /* Called when a programmer sound definition entry is loaded. */
    FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_RELEASE,     /* Called when a programmer sound definition entry is unloaded. */
    FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_INFO,        /* Called when a sound definition entry is loaded. */
    FMOD_EVENT_CALLBACKTYPE_EVENTSTARTED,         /* Called when an event is started. */
    FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_SELECTINDEX, /* Called when a sound definition entry needs to be chosen from a "ProgrammerSelected" sound definition. */
    FMOD_EVENT_CALLBACKTYPE_OCCLUSION             /* Called when an event's channel is occluded with the geometry engine. */
} FMOD_EVENT_CALLBACKTYPE;


/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure containing realtime information about a wavebank.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    EventSystem::getInfo
    FMOD_EVENT_SYSTEMINFO
]
*/
typedef struct FMOD_EVENT_WAVEBANKINFO
{
    char          name[256];             /* [out] Name of this wave bank. */
    int           streamrefcnt;          /* [out] Number of stream references to this wave bank made by events in this event system. */
    int           samplerefcnt;          /* [out] Number of sample references to this wave bank made by events in this event system. */
    int           numstreams;            /* [out] Number of times this wave bank has been opened for streaming. */
    int           maxstreams;            /* [out] Maximum number of times this wave bank will be opened for streaming. */
    int           streamsinuse;          /* [out] Number of streams currently in use. */
    unsigned int  streammemory;          /* [out] Amount of memory (in bytes) used by streams. */
    unsigned int  samplememory;          /* [out] Amount of memory (in bytes) used by samples. */
    int           type;                  /* [out] 0 = stream from disk, 1 = load into memory, 2 = decompress into memory. */
} FMOD_EVENT_WAVEBANKINFO;


/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure containing realtime information about an event system.

    [REMARKS]
    On entry, numplayingevents should be set to the number of elements in the playingevents array. If the actual
    number of playing events is greater than numplayingevents then the playingevents array will be filled with
    numplayingevents entries and numplayingevents will be set to the actual number of playing events on exit.
    In short, if numplayingevents on exit > numplayingevents on entry then the playingevents array wasn't large
    enough and some events were unable to be added to the array.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    EventSystem::getInfo
    EventProject::getInfo
    FMOD_EVENT_WAVEBANKINFO
]
*/
typedef struct FMOD_EVENT_SYSTEMINFO
{
#ifdef __cplusplus
    FMOD_EVENT_SYSTEMINFO() : numevents(0), numinstances(0), maxwavebanks(0), wavebankinfo(0), numplayingevents(0), playingevents(0) {}
#endif

    int                      numevents;          /* [out] Total number of events in all event groups in this event system. */
    int                      numinstances;       /* [out] Total number of event instances in all event groups in this event system. */
    int                      maxwavebanks;       /* [in/out] Out, number of wavebanks loaded by the EventSystem.  In. Maximum size of array of wavebankinfo structures supplied by user.  Optional. */
    FMOD_EVENT_WAVEBANKINFO *wavebankinfo;       /* [in] Pointer to array FMOD_EVENT_WAVEBANKINFO structures (max size defined by maxwavebanks).  FMOD will fill these in with detailed information on each wave bank. Optional. */
    int                      numplayingevents;   /* [in/out] On entry, maximum number of entries in playingevents array. On exit, actual number of entries in playingevents array, or if playingevents is null, then it is just the number of currently playing events. Optional. */
    FMOD_EVENT             **playingevents;      /* [in/out] Pointer to an array that will be filled with the event handles of all playing events. Optional. Specify 0 if not needed. Must be used in conjunction with numplayingevents. */
    int                      numloadsqueued[5];  /* [out] Current number of sound banks queued for loading due to using FMOD_EVENT_NONBLOCKING flag.  Note there are 5 because there are 5 possible loading threads.  Add all values together for total. */
} FMOD_EVENT_SYSTEMINFO;



/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure containing realtime information about an event project.

    [REMARKS]
    On entry, numplayingevents should be set to the number of elements in the playingevents array. If the actual
    number of playing events is greater than numplayingevents then the playingevents array will be filled with
    numplayingevents entries and numplayingevents will be set to the actual number of playing events on exit.
    In short, if numplayingevents on exit > numplayingevents on entry then the playingevents array wasn't large
    enough and some events were unable to be added to the array.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    EventProject::getInfo
    EventSystem::getInfo
    FMOD_EVENT_WAVEBANKINFO
]
*/
typedef struct FMOD_EVENT_PROJECTINFO
{
#ifdef __cplusplus
    FMOD_EVENT_PROJECTINFO() : index(0), numevents(0), numinstances(0), maxwavebanks(0), wavebankinfo(0), numplayingevents(0), playingevents(0) {}
#endif

    int                      index;            /* [out] Index of the project. */
    char                     name[256];        /* [out] Name of the project. */
    int                      numevents;        /* [out] Total number of events in all event groups in this event project. */
    int                      numinstances;     /* [out] Total number of event instances in all event groups in this event project. */
    int                      maxwavebanks;     /* [in/out] Out, number of wavebanks loaded by the EventProject.  In. Maximum size of array of wavebankinfo structures supplied by user.  Optional. */
    FMOD_EVENT_WAVEBANKINFO *wavebankinfo;     /* [in] Pointer to array FMOD_EVENT_WAVEBANKINFO structures (max size defined by maxwavebanks).  FMOD will fill these in with detailed information on each wave bank. Optional. */
    int                      numplayingevents; /* [in/out] On entry, maximum number of entries in playingevents array. On exit, actual number of entries in playingevents array, or if playingevents is null, then it is just the number of currently playing events. Optional. */
    FMOD_EVENT             **playingevents;    /* [in/out] Pointer to an array that will be filled with the event handles of all playing events. Optional. Specify 0 if not needed. Must be used in conjunction with numplayingevents. */

} FMOD_EVENT_PROJECTINFO;


/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure containing extended information about an event.

    [REMARKS]
    This structure is optional!  Specify 0 or NULL in Event::getInfo if you don't need it!<br>
    This structure has members that need to be initialized before Event::getInfo is called. Always initialize this structure before calling Event::getInfo!

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    Event::getInfo
    FMOD_GUID
]
*/
typedef struct FMOD_EVENT_INFO
{
#ifdef __cplusplus
    FMOD_EVENT_INFO() : memoryused(0), positionms(0), lengthms(0), channelsplaying(0), instancesactive(0), maxwavebanks(0), wavebankinfo(0), projectid(0), systemid(0), audibility(0), numinstances(0), instances(0), guid(0) {}
#endif

    int                      memoryused;        /* This member has been deprecated. */
    int                      positionms;        /* [out] Time passed in playback of this event instance in milliseconds. */
    int                      lengthms;          /* [out] Length in milliseconds of this event. Note: lengthms will be -1 if the length of the event can't be determined i.e. if it has looping sounds. */
    int                      channelsplaying;   /* [out] Number of channels currently playing in this event instance. */
    int                      instancesactive;   /* [out] Number of event instances currently in use. */
    int                      maxwavebanks;      /* [in/out] Out, number of wavebanks refered to by this event.  In. Maximum size of array of wavebankinfo structures supplied by user.  Optional. */
    FMOD_EVENT_WAVEBANKINFO *wavebankinfo;      /* [in] Pointer to array FMOD_EVENT_WAVEBANKINFO structures (max size defined by maxwavebanks).  FMOD will fill these in with detailed information on each wave bank. Optional. */
    unsigned int             projectid;         /* [out] The runtime 'EventProject' wide unique identifier for this event. */
    unsigned int             systemid;          /* [out] The runtime 'EventSystem' wide unique identifier for this event.  This is calculated when single or multiple projects are loaded. */
    float                    audibility;        /* [out] current audibility of event. */
    int                      numinstances;      /* [in/out] On entry, maximum number of entries in instances array. On exit, actual number of entries in instances array, or if instances is null, then it is just the number of instances of this event. Optional. */
    FMOD_EVENT             **instances;         /* [in/out] Pointer to an array that will be filled with the current reference-counted event handles of all instances of this event. Optional. Specify 0 if not needed. Must be used in conjunction with numinstances. Note: Due to reference counting, the event instance handles returned here may be different between subsequent calls to this function. If you use these event handles, make sure your code is prepared for them to be invalid! */
    FMOD_GUID               *guid;              /* [out] Pointer to a structure that will be filled with the event's GUID. Optional. Specify 0 if not needed. */

} FMOD_EVENT_INFO;


/*
[ENUM]
[
    [DESCRIPTION]   
    Sound definition entry types for FMOD_EVENT_SOUNDDEFINFO.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    FMOD_EVENT_SOUNDDEFINFO
    FMOD_EVENT_CALLBACK
    FMOD_EVENT_CALLBACKTYPE
]
*/
typedef enum
{
    FMOD_EVENT_SOUNDDEF_ENTRYTYPE_WAVETABLE,           /* Waveform. */
    FMOD_EVENT_SOUNDDEF_ENTRYTYPE_OSCILLATOR,          /* Oscillator. */
    FMOD_EVENT_SOUNDDEF_ENTRYTYPE_NULL,                /* "Don't play" entry. */
    FMOD_EVENT_SOUNDDEF_ENTRYTYPE_PROGRAMMER           /* Programmer sound. */
} FMOD_EVENT_SOUNDDEF_ENTRYTYPE;


/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure containing information about a sound definition.

    [REMARKS]
    This structure is passed as the param1 argument of all 
    FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_SELECTINDEX callbacks if
    FMOD_EVENT_INIT_DETAILED_SOUNDDEF_INFO was passed to EventSystem::init.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    FMOD_EVENT_CALLBACK
    FMOD_EVENT_CALLBACKTYPE
    EventSystem::init
    FMOD_EVENT_INITFLAGS
    FMOD_EVENT_SOUNDDEF_ENTRYTYPE
]
*/
typedef struct FMOD_EVENT_SOUNDDEFINFO
{
#ifdef __cplusplus
    FMOD_EVENT_SOUNDDEFINFO() : name(0), numentries(0), entrynames(0), entrytypes(0) {}
#endif

    char                    *name;              /* The name of the sound definition. */
    int                      numentries;        /* The number of entries in the sound definition. */
    const char             **entrynames;        /* The names of the entries in the sound definition (an array of size numentries). Note that entrynames[i] will be null if entrytypes[i] is not FMOD_EVENT_SOUNDDEF_ENTRYTYPE_WAVETABLE. */
    FMOD_EVENT_SOUNDDEF_ENTRYTYPE *entrytypes;  /* The types of the entries in the sound definition (an array of size numentries). */

} FMOD_EVENT_SOUNDDEFINFO;


/*
[STRUCTURE]
[
    [DESCRIPTION]
    Use this structure with EventSystem::load when more control is needed over loading.

    [REMARKS]
    This structure is optional!  Specify 0 or NULL in EventSystem::load if you don't need it!<br>
    <br>
    Members marked with [in] mean the user sets the value before passing it to the function.<br>
    Members marked with [out] mean FMOD sets the value to be used after the function exits.<br>
    Use sounddefentrylimit to limit the number of sound definition entries - and therefore the amount of wave data - loaded for each sound definition. This feature allows the programmer to implement a "low detail" setting at runtime without needing a seperate "low detail" set of assets.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    EventSystem::load
]
*/
typedef struct FMOD_EVENT_LOADINFO
{
#ifdef __cplusplus
    FMOD_EVENT_LOADINFO() : size(0), encryptionkey(0), sounddefentrylimit(0), loadfrommemory_length(0), override_category_vals(0), sizeof_instancepool_simple(0) {}
#endif

    unsigned int  size;                         /* [in] Size of this structure.  This is used so the structure can be expanded in the future and still work on older versions of FMOD Ex. */
    char         *encryptionkey;                /* [in] Optional. Specify 0 to ignore. Key, or 'password' to decrypt a bank.  A sound designer may have encrypted the audio data to protect their sound data from 'rippers'. */
    float         sounddefentrylimit;           /* [in] Optional. Specify 0 to ignore. A value between 0 -> 1 that is multiplied with the number of sound definition entries in each sound definition in the project being loaded in order to programmatically reduce the number of sound definition entries used at runtime. */
    unsigned int  loadfrommemory_length;        /* [in] Optional. Specify 0 to ignore. Length of memory buffer pointed to by name_or_data parameter passed to EventSystem::load. If this field is non-zero then the name_or_data parameter passed to EventSystem::load will be interpreted as a pointer to a memory buffer containing the .fev data to load. If this field is zero the name_or_data parameter is interpreted as the filename of the .fev file to load. */
    FMOD_BOOL     override_category_vals;       /* [in] Optional. If this member is set to true, newly-loaded categories will impart their properties (volume, pitch etc.) to existing categories of the same name. */
    unsigned int  sizeof_instancepool_simple;   /* [in] Optional. Specify 0 to ignore. If this value is non-zero, FMOD will create an instance pool for simple events with "sizeof_instancepool_simple" entries. Note: Event instance pools currently work for simple events only. Complex events will behave as normal and not be pooled. */

} FMOD_EVENT_LOADINFO;


typedef FMOD_RESULT (F_CALLBACK *FMOD_EVENT_CALLBACK) (FMOD_EVENT *event, FMOD_EVENT_CALLBACKTYPE type, void *param1, void *param2, void *userdata);


/*
[ENUM]
[
    [DESCRIPTION]   
    These callback types are used with FMOD_EVENTQUEUE_CALLBACK.

    [REMARKS]
    <b>Note!</b> Currently the user must call EventSystem::update for these callbacks to trigger!<p>

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    EventQueue::setCallback
    FMOD_EVENTQUEUE_CALLBACK
    EventSystem::update
]
*/
typedef enum
{
    FMOD_EVENTQUEUE_CALLBACKTYPE_PREPARE,       /* Called when an entry is being prepared for playback */
    FMOD_EVENTQUEUE_CALLBACKTYPE_ABOUTTOPLAY,   /* Called when an entry is about to play */
    FMOD_EVENTQUEUE_CALLBACKTYPE_FINISHED,      /* Called when an entry has finished playing */
    FMOD_EVENTQUEUE_CALLBACKTYPE_EXPIRED        /* Called when an entry has expired before being played. See EventQueueEntry::setExpiryTime */

} FMOD_EVENTQUEUE_CALLBACKTYPE;


typedef FMOD_RESULT (F_CALLBACK *FMOD_EVENTQUEUE_CALLBACK)(FMOD_EVENTQUEUE_CALLBACKTYPE type, FMOD_EVENTQUEUE *queue, FMOD_EVENTQUEUEENTRY *entry, void *callbackuserdata);


/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure containing realtime information about the music system.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    MusicSystem::getInfo
]
*/
typedef struct FMOD_MUSIC_INFO
{
    FMOD_BOOL               starving;           /* [out] True if any streams in the music system are starving. */
    FMOD_BOOL               all_samples_loaded; /* [out] True if all non-streaming samples in the music system are loaded, false otherwise. */
} FMOD_MUSIC_INFO;


/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure used to hold information about music system entites.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    FMOD_MUSIC_ITERATOR
]
*/
typedef struct FMOD_MUSIC_ENTITY
{
	const char* name;                       /* The name of the music entity as a null terminated string. */
	FMOD_MUSIC_ID id;                       /* The ID of the music entity. */
} FMOD_MUSIC_ENTITY;


/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure used to enumerate entities in the music system.

    [REMARKS]
    The music system provides methods to initialize and advance iterators. Iterator members should never need to be set manually.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    FMOD_MUSIC_ENTITY
    MusicSystem::getCues
    MusicSystem::getParameters
]
*/
typedef struct FMOD_MUSIC_ITERATOR
{
	const FMOD_MUSIC_ENTITY* value;         /* The music entity the iterator points to. A null value indicates an invalid iterator. */
	const char* filter;                     /* The string used to filter music entities. */
} FMOD_MUSIC_ITERATOR;


/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure containing information about a music sample, for use with
    FMOD_MUSIC_CALLBACKTYPE_SEGMENT_CREATE and FMOD_MUSIC_CALLBACKTYPE_SEGMENT_RELEASE.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    FMOD_MUSIC_CALLBACK
    FMOD_MUSIC_CALLBACKTYPE
]
*/
typedef struct FMOD_MUSIC_SAMPLE_INFO
{
    unsigned int  segment_id;   /* The ID of the parent segment. */
    unsigned int  index;        /* The index of the sample within the parent segment. */
    const char   *filename;     /* The filename of the sample.<br/> <b>Note:</b> If the sample was built by a version of FMOD Designer before 4.29.09, this field will be 0. */
} FMOD_MUSIC_SAMPLE_INFO;


/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure containing information about a music segment, for use with
    FMOD_MUSIC_CALLBACKTYPE_CHANNEL_CREATED and FMOD_MUSIC_CALLBACKTYPE_CHANNEL_DESTROYED.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    FMOD_MUSIC_CALLBACK
    FMOD_MUSIC_CALLBACKTYPE
]
*/
typedef struct FMOD_MUSIC_SEGMENT_INFO
{
    unsigned int  segment_id;   /* The ID of the segment. */
    unsigned int  theme_id;     /* The ID of the parent theme. */
} FMOD_MUSIC_SEGMENT_INFO;


/*
[ENUM]
[
    [DESCRIPTION]   
    These callback types are used with FMOD_MUSIC_CALLBACK.

    [REMARKS]
    <b>Note!</b>  Currently the user must call EventSystem::update for these callbacks to trigger!<br />

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    MusicSystem::setCallback
    FMOD_MUSIC_CALLBACK
    EventSystem::update
]
*/
typedef enum
{
    FMOD_MUSIC_CALLBACKTYPE_SEGMENT_START,       /* Called when a segment is started. */
    FMOD_MUSIC_CALLBACKTYPE_SEGMENT_END,         /* Called when a segment ends. */
    FMOD_MUSIC_CALLBACKTYPE_SAMPLE_CREATE,       /* Called when a segment needs a sound created. */
    FMOD_MUSIC_CALLBACKTYPE_SAMPLE_RELEASE,      /* Called when a segment is finished with a sound. */
    FMOD_MUSIC_CALLBACKTYPE_CHANNEL_CREATED,     /* Called when a channel is created to play a segment. */
    FMOD_MUSIC_CALLBACKTYPE_CHANNEL_DESTROYED,   /* Called when a segment channel is destroyed. */
    FMOD_MUSIC_CALLBACKTYPE_RESET,               /* Called when the system is reset */
    FMOD_MUSIC_CALLBACKTYPE_BEAT                 /* Called each time a beat is passed (based on segment tempo and time signature) */
} FMOD_MUSIC_CALLBACKTYPE;


typedef FMOD_RESULT (F_CALLBACK *FMOD_MUSIC_CALLBACK) (FMOD_MUSIC_CALLBACKTYPE type, void *param1, void *param2, void *userdata);


/* ========================================================================================== */
/* FUNCTION PROTOTYPES                                                                        */
/* ========================================================================================== */

#ifdef __cplusplus
extern "C" 
{
#endif

/*
    FMOD EventSystem factory functions.  Use this to create an FMOD EventSystem Instance.  Below you will see FMOD_EventSystem_Init/Release to get started.
*/

FMOD_RESULT F_API FMOD_EventSystem_Create(FMOD_EVENTSYSTEM **eventsystem);

/*$ preserve end $*/

/*
    'EventSystem' API
*/

/*
     Initialization / system functions.
*/

FMOD_RESULT F_API FMOD_EventSystem_Init              (FMOD_EVENTSYSTEM *eventsystem, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata, FMOD_EVENT_INITFLAGS eventflags);
FMOD_RESULT F_API FMOD_EventSystem_Release           (FMOD_EVENTSYSTEM *eventsystem);
FMOD_RESULT F_API FMOD_EventSystem_Update            (FMOD_EVENTSYSTEM *eventsystem);
FMOD_RESULT F_API FMOD_EventSystem_SetMediaPath      (FMOD_EVENTSYSTEM *eventsystem, const char *path);
FMOD_RESULT F_API FMOD_EventSystem_SetPluginPath     (FMOD_EVENTSYSTEM *eventsystem, const char *path);
FMOD_RESULT F_API FMOD_EventSystem_GetVersion        (FMOD_EVENTSYSTEM *eventsystem, unsigned int *version);
FMOD_RESULT F_API FMOD_EventSystem_GetInfo           (FMOD_EVENTSYSTEM *eventsystem, FMOD_EVENT_SYSTEMINFO *info);
FMOD_RESULT F_API FMOD_EventSystem_GetSystemObject   (FMOD_EVENTSYSTEM *eventsystem, FMOD_SYSTEM **system);
FMOD_RESULT F_API FMOD_EventSystem_GetMusicSystem    (FMOD_EVENTSYSTEM *eventsystem, FMOD_MUSICSYSTEM **musicsystem);
FMOD_RESULT F_API FMOD_EventSystem_SetLanguage       (FMOD_EVENTSYSTEM *eventsystem, const char *language);
FMOD_RESULT F_API FMOD_EventSystem_GetLanguage       (FMOD_EVENTSYSTEM *eventsystem, char *language);

/*
     FEV load/unload.                                 
*/

FMOD_RESULT F_API FMOD_EventSystem_Load              (FMOD_EVENTSYSTEM *eventsystem, const char *name_or_data, FMOD_EVENT_LOADINFO *loadinfo, FMOD_EVENTPROJECT **project);
FMOD_RESULT F_API FMOD_EventSystem_Unload            (FMOD_EVENTSYSTEM *eventsystem);

/*
     Event,EventGroup,EventCategory Retrieval.        
*/

FMOD_RESULT F_API FMOD_EventSystem_GetProject        (FMOD_EVENTSYSTEM *eventsystem, const char *name, FMOD_EVENTPROJECT **project);
FMOD_RESULT F_API FMOD_EventSystem_GetProjectByIndex (FMOD_EVENTSYSTEM *eventsystem, int index, FMOD_EVENTPROJECT **project);
FMOD_RESULT F_API FMOD_EventSystem_GetNumProjects    (FMOD_EVENTSYSTEM *eventsystem, int *numprojects);
FMOD_RESULT F_API FMOD_EventSystem_GetCategory       (FMOD_EVENTSYSTEM *eventsystem, const char *name, FMOD_EVENTCATEGORY **category);
FMOD_RESULT F_API FMOD_EventSystem_GetCategoryByIndex(FMOD_EVENTSYSTEM *eventsystem, int index, FMOD_EVENTCATEGORY **category);
FMOD_RESULT F_API FMOD_EventSystem_GetMusicCategory  (FMOD_EVENTSYSTEM *eventsystem, FMOD_EVENTCATEGORY **category);
FMOD_RESULT F_API FMOD_EventSystem_GetNumCategories  (FMOD_EVENTSYSTEM *eventsystem, int *numcategories);
FMOD_RESULT F_API FMOD_EventSystem_GetGroup          (FMOD_EVENTSYSTEM *eventsystem, const char *name, FMOD_BOOL cacheevents, FMOD_EVENTGROUP **group);
FMOD_RESULT F_API FMOD_EventSystem_GetEvent          (FMOD_EVENTSYSTEM *eventsystem, const char *name, FMOD_EVENT_MODE mode, FMOD_EVENT **event);
FMOD_RESULT F_API FMOD_EventSystem_GetEventBySystemID(FMOD_EVENTSYSTEM *eventsystem, unsigned int systemid, FMOD_EVENT_MODE mode, FMOD_EVENT **event);
FMOD_RESULT F_API FMOD_EventSystem_GetEventByGUID    (FMOD_EVENTSYSTEM *eventsystem, const FMOD_GUID *guid, FMOD_EVENT_MODE mode, FMOD_EVENT **event);
FMOD_RESULT F_API FMOD_EventSystem_GetEventByGUIDString(FMOD_EVENTSYSTEM *eventsystem, const char *guid, FMOD_EVENT_MODE mode, FMOD_EVENT **event);
FMOD_RESULT F_API FMOD_EventSystem_GetNumEvents      (FMOD_EVENTSYSTEM *eventsystem, int *numevents);

/*
     Reverb interfaces.
*/

FMOD_RESULT F_API FMOD_EventSystem_SetReverbProperties(FMOD_EVENTSYSTEM *eventsystem, const FMOD_REVERB_PROPERTIES *props);
FMOD_RESULT F_API FMOD_EventSystem_GetReverbProperties(FMOD_EVENTSYSTEM *eventsystem, FMOD_REVERB_PROPERTIES *props);

FMOD_RESULT F_API FMOD_EventSystem_GetReverbPreset   (FMOD_EVENTSYSTEM *eventsystem, const char *name, FMOD_REVERB_PROPERTIES *props, int *index);
FMOD_RESULT F_API FMOD_EventSystem_GetReverbPresetByIndex(FMOD_EVENTSYSTEM *eventsystem, const int index, FMOD_REVERB_PROPERTIES *props, char **name);
FMOD_RESULT F_API FMOD_EventSystem_GetNumReverbPresets(FMOD_EVENTSYSTEM *eventsystem, int *numpresets);

FMOD_RESULT F_API FMOD_EventSystem_CreateReverb      (FMOD_EVENTSYSTEM *eventsystem, FMOD_EVENTREVERB **reverb);
FMOD_RESULT F_API FMOD_EventSystem_SetReverbAmbientProperties(FMOD_EVENTSYSTEM *eventsystem, FMOD_REVERB_PROPERTIES *props);
FMOD_RESULT F_API FMOD_EventSystem_GetReverbAmbientProperties(FMOD_EVENTSYSTEM *eventsystem, FMOD_REVERB_PROPERTIES *props);

/*
     Event queue interfaces.
*/

FMOD_RESULT F_API FMOD_EventSystem_CreateEventQueue  (FMOD_EVENTSYSTEM *eventsystem, FMOD_EVENTQUEUE **queue);
FMOD_RESULT F_API FMOD_EventSystem_CreateEventQueueEntry(FMOD_EVENTSYSTEM *eventsystem, FMOD_EVENT *event, FMOD_EVENTQUEUEENTRY **entry);

/*
     3D Listener interface.
*/

FMOD_RESULT F_API FMOD_EventSystem_Set3DNumListeners (FMOD_EVENTSYSTEM *eventsystem, int numlisteners);
FMOD_RESULT F_API FMOD_EventSystem_Get3DNumListeners (FMOD_EVENTSYSTEM *eventsystem, int *numlisteners);
FMOD_RESULT F_API FMOD_EventSystem_Set3DListenerAttributes(FMOD_EVENTSYSTEM *eventsystem, int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_EventSystem_Get3DListenerAttributes(FMOD_EVENTSYSTEM *eventsystem, int listener, FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up);

/*
     Get/set user data
*/

FMOD_RESULT F_API FMOD_EventSystem_SetUserData       (FMOD_EVENTSYSTEM *eventsystem, void *userdata);
FMOD_RESULT F_API FMOD_EventSystem_GetUserData       (FMOD_EVENTSYSTEM *eventsystem, void **userdata);

/*
     Pre-loading FSB files (from disk or from memory, use FMOD_OPENMEMORY_POINT to point to pre-loaded memory).
*/

FMOD_RESULT F_API FMOD_EventSystem_PreloadFSB        (FMOD_EVENTSYSTEM *eventsystem, const char *filename, int streaminstance, FMOD_SOUND *sound);
FMOD_RESULT F_API FMOD_EventSystem_UnloadFSB         (FMOD_EVENTSYSTEM *eventsystem, const char *filename, int streaminstance);

FMOD_RESULT F_API FMOD_EventSystem_GetMemoryInfo     (FMOD_EVENTSYSTEM *eventsystem, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'EventProject' API
*/

FMOD_RESULT F_API FMOD_EventProject_Release          (FMOD_EVENTPROJECT *eventproject);
FMOD_RESULT F_API FMOD_EventProject_GetInfo          (FMOD_EVENTPROJECT *eventproject, FMOD_EVENT_PROJECTINFO *info);
FMOD_RESULT F_API FMOD_EventProject_GetGroup         (FMOD_EVENTPROJECT *eventproject, const char *name, FMOD_BOOL cacheevents, FMOD_EVENTGROUP **group);
FMOD_RESULT F_API FMOD_EventProject_GetGroupByIndex  (FMOD_EVENTPROJECT *eventproject, int index, FMOD_BOOL cacheevents, FMOD_EVENTGROUP **group);
FMOD_RESULT F_API FMOD_EventProject_GetNumGroups     (FMOD_EVENTPROJECT *eventproject, int *numgroups);
FMOD_RESULT F_API FMOD_EventProject_GetEvent         (FMOD_EVENTPROJECT *eventproject, const char *name, FMOD_EVENT_MODE mode, FMOD_EVENT **event);
FMOD_RESULT F_API FMOD_EventProject_GetEventByProjectID(FMOD_EVENTPROJECT *eventproject, unsigned int projectid, FMOD_EVENT_MODE mode, FMOD_EVENT **event);
FMOD_RESULT F_API FMOD_EventProject_GetNumEvents     (FMOD_EVENTPROJECT *eventproject, int *numevents);
FMOD_RESULT F_API FMOD_EventProject_LoadSampleData   (FMOD_EVENTPROJECT *eventproject, int *eventid_array, int sizeof_eventid_array, char **groupname_array, int sizeof_groupname_array, FMOD_EVENT_MODE eventmode);
FMOD_RESULT F_API FMOD_EventProject_StopAllEvents    (FMOD_EVENTPROJECT *eventproject, FMOD_BOOL immediate);
FMOD_RESULT F_API FMOD_EventProject_CancelAllLoads   (FMOD_EVENTPROJECT *eventproject);
FMOD_RESULT F_API FMOD_EventProject_SetUserData      (FMOD_EVENTPROJECT *eventproject, void *userdata);
FMOD_RESULT F_API FMOD_EventProject_GetUserData      (FMOD_EVENTPROJECT *eventproject, void **userdata);

FMOD_RESULT F_API FMOD_EventProject_GetMemoryInfo    (FMOD_EVENTPROJECT *eventproject, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'EventGroup' API
*/

FMOD_RESULT F_API FMOD_EventGroup_GetInfo            (FMOD_EVENTGROUP *eventgroup, int *index, char **name);
FMOD_RESULT F_API FMOD_EventGroup_LoadEventData      (FMOD_EVENTGROUP *eventgroup, FMOD_EVENT_RESOURCE resource, FMOD_EVENT_MODE mode);
FMOD_RESULT F_API FMOD_EventGroup_FreeEventData      (FMOD_EVENTGROUP *eventgroup, FMOD_EVENT *event, FMOD_BOOL waituntilready);
FMOD_RESULT F_API FMOD_EventGroup_GetGroup           (FMOD_EVENTGROUP *eventgroup, const char *name, FMOD_BOOL cacheevents, FMOD_EVENTGROUP **group);
FMOD_RESULT F_API FMOD_EventGroup_GetGroupByIndex    (FMOD_EVENTGROUP *eventgroup, int index, FMOD_BOOL cacheevents, FMOD_EVENTGROUP **group);
FMOD_RESULT F_API FMOD_EventGroup_GetParentGroup     (FMOD_EVENTGROUP *eventgroup, FMOD_EVENTGROUP **group);
FMOD_RESULT F_API FMOD_EventGroup_GetParentProject   (FMOD_EVENTGROUP *eventgroup, FMOD_EVENTPROJECT **project);
FMOD_RESULT F_API FMOD_EventGroup_GetNumGroups       (FMOD_EVENTGROUP *eventgroup, int *numgroups);
FMOD_RESULT F_API FMOD_EventGroup_GetEvent           (FMOD_EVENTGROUP *eventgroup, const char *name, FMOD_EVENT_MODE mode, FMOD_EVENT **event);
FMOD_RESULT F_API FMOD_EventGroup_GetEventByIndex    (FMOD_EVENTGROUP *eventgroup, int index, FMOD_EVENT_MODE mode, FMOD_EVENT **event);
FMOD_RESULT F_API FMOD_EventGroup_GetNumEvents       (FMOD_EVENTGROUP *eventgroup, int *numevents);
FMOD_RESULT F_API FMOD_EventGroup_GetProperty        (FMOD_EVENTGROUP *eventgroup, const char *propertyname, void *value);
FMOD_RESULT F_API FMOD_EventGroup_GetPropertyByIndex (FMOD_EVENTGROUP *eventgroup, int propertyindex, void *value);
FMOD_RESULT F_API FMOD_EventGroup_GetNumProperties   (FMOD_EVENTGROUP *eventgroup, int *numproperties);
FMOD_RESULT F_API FMOD_EventGroup_GetState           (FMOD_EVENTGROUP *eventgroup, FMOD_EVENT_STATE *state);
FMOD_RESULT F_API FMOD_EventGroup_SetUserData        (FMOD_EVENTGROUP *eventgroup, void *userdata);
FMOD_RESULT F_API FMOD_EventGroup_GetUserData        (FMOD_EVENTGROUP *eventgroup, void **userdata);

FMOD_RESULT F_API FMOD_EventGroup_GetMemoryInfo      (FMOD_EVENTGROUP *eventgroup, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'EventCategory' API
*/

FMOD_RESULT F_API FMOD_EventCategory_GetInfo         (FMOD_EVENTCATEGORY *eventcategory, int *index, char **name);
FMOD_RESULT F_API FMOD_EventCategory_GetCategory     (FMOD_EVENTCATEGORY *eventcategory, const char *name, FMOD_EVENTCATEGORY **category);
FMOD_RESULT F_API FMOD_EventCategory_GetCategoryByIndex(FMOD_EVENTCATEGORY *eventcategory, int index, FMOD_EVENTCATEGORY **category);
FMOD_RESULT F_API FMOD_EventCategory_GetNumCategories(FMOD_EVENTCATEGORY *eventcategory, int *numcategories);
FMOD_RESULT F_API FMOD_EventCategory_GetEventByIndex (FMOD_EVENTCATEGORY *eventcategory, int index, FMOD_EVENT_MODE mode, FMOD_EVENT **event);
FMOD_RESULT F_API FMOD_EventCategory_GetNumEvents    (FMOD_EVENTCATEGORY *eventcategory, int *numevents);
FMOD_RESULT F_API FMOD_EventCategory_GetParentCategory(FMOD_EVENTCATEGORY *eventcategory, FMOD_EVENTCATEGORY **category);

FMOD_RESULT F_API FMOD_EventCategory_StopAllEvents   (FMOD_EVENTCATEGORY *eventcategory);
FMOD_RESULT F_API FMOD_EventCategory_SetVolume       (FMOD_EVENTCATEGORY *eventcategory, float volume);
FMOD_RESULT F_API FMOD_EventCategory_GetVolume       (FMOD_EVENTCATEGORY *eventcategory, float *volume);
FMOD_RESULT F_API FMOD_EventCategory_SetPitch        (FMOD_EVENTCATEGORY *eventcategory, float pitch, FMOD_EVENT_PITCHUNITS units);
FMOD_RESULT F_API FMOD_EventCategory_GetPitch        (FMOD_EVENTCATEGORY *eventcategory, float *pitch, FMOD_EVENT_PITCHUNITS units);
FMOD_RESULT F_API FMOD_EventCategory_SetPaused       (FMOD_EVENTCATEGORY *eventcategory, FMOD_BOOL paused);
FMOD_RESULT F_API FMOD_EventCategory_GetPaused       (FMOD_EVENTCATEGORY *eventcategory, FMOD_BOOL *paused);
FMOD_RESULT F_API FMOD_EventCategory_SetMute         (FMOD_EVENTCATEGORY *eventcategory, FMOD_BOOL mute);
FMOD_RESULT F_API FMOD_EventCategory_GetMute         (FMOD_EVENTCATEGORY *eventcategory, FMOD_BOOL *mute);
FMOD_RESULT F_API FMOD_EventCategory_GetChannelGroup (FMOD_EVENTCATEGORY *eventcategory, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT F_API FMOD_EventCategory_SetUserData     (FMOD_EVENTCATEGORY *eventcategory, void *userdata);
FMOD_RESULT F_API FMOD_EventCategory_GetUserData     (FMOD_EVENTCATEGORY *eventcategory, void **userdata);

FMOD_RESULT F_API FMOD_EventCategory_GetMemoryInfo   (FMOD_EVENTCATEGORY *eventcategory, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'Event' API
*/

FMOD_RESULT F_API FMOD_Event_Release                 (FMOD_EVENT *event, FMOD_BOOL freeeventdata, FMOD_BOOL waituntilready);

FMOD_RESULT F_API FMOD_Event_Start                   (FMOD_EVENT *event);
FMOD_RESULT F_API FMOD_Event_Stop                    (FMOD_EVENT *event, FMOD_BOOL immediate);

FMOD_RESULT F_API FMOD_Event_GetInfo                 (FMOD_EVENT *event, int *index, char **name, FMOD_EVENT_INFO *info);
FMOD_RESULT F_API FMOD_Event_GetState                (FMOD_EVENT *event, FMOD_EVENT_STATE *state);
FMOD_RESULT F_API FMOD_Event_GetParentGroup          (FMOD_EVENT *event, FMOD_EVENTGROUP **group);
FMOD_RESULT F_API FMOD_Event_GetChannelGroup         (FMOD_EVENT *event, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT F_API FMOD_Event_SetCallback             (FMOD_EVENT *event, FMOD_EVENT_CALLBACK callback, void *userdata);

FMOD_RESULT F_API FMOD_Event_GetParameter            (FMOD_EVENT *event, const char *name, FMOD_EVENTPARAMETER **parameter);
FMOD_RESULT F_API FMOD_Event_GetParameterByIndex     (FMOD_EVENT *event, int index, FMOD_EVENTPARAMETER **parameter);
FMOD_RESULT F_API FMOD_Event_GetNumParameters        (FMOD_EVENT *event, int *numparameters);
FMOD_RESULT F_API FMOD_Event_GetProperty             (FMOD_EVENT *event, const char *propertyname, void *value, FMOD_BOOL this_instance);
FMOD_RESULT F_API FMOD_Event_GetPropertyByIndex      (FMOD_EVENT *event, int propertyindex, void *value, FMOD_BOOL this_instance);
FMOD_RESULT F_API FMOD_Event_SetProperty             (FMOD_EVENT *event, const char *propertyname, void *value, FMOD_BOOL this_instance);
FMOD_RESULT F_API FMOD_Event_SetPropertyByIndex      (FMOD_EVENT *event, int propertyindex, void *value, FMOD_BOOL this_instance);
FMOD_RESULT F_API FMOD_Event_GetNumProperties        (FMOD_EVENT *event, int *numproperties);
FMOD_RESULT F_API FMOD_Event_GetPropertyInfo         (FMOD_EVENT *event, int *propertyindex, char **propertyname, FMOD_EVENTPROPERTY_TYPE *type);
FMOD_RESULT F_API FMOD_Event_GetCategory             (FMOD_EVENT *event, FMOD_EVENTCATEGORY **category);

FMOD_RESULT F_API FMOD_Event_SetVolume               (FMOD_EVENT *event, float volume);
FMOD_RESULT F_API FMOD_Event_GetVolume               (FMOD_EVENT *event, float *volume);
FMOD_RESULT F_API FMOD_Event_SetPitch                (FMOD_EVENT *event, float pitch, FMOD_EVENT_PITCHUNITS units);
FMOD_RESULT F_API FMOD_Event_GetPitch                (FMOD_EVENT *event, float *pitch, FMOD_EVENT_PITCHUNITS units);
FMOD_RESULT F_API FMOD_Event_SetPaused               (FMOD_EVENT *event, FMOD_BOOL paused);
FMOD_RESULT F_API FMOD_Event_GetPaused               (FMOD_EVENT *event, FMOD_BOOL *paused);
FMOD_RESULT F_API FMOD_Event_SetMute                 (FMOD_EVENT *event, FMOD_BOOL mute);
FMOD_RESULT F_API FMOD_Event_GetMute                 (FMOD_EVENT *event, FMOD_BOOL *mute);
FMOD_RESULT F_API FMOD_Event_Set3DAttributes         (FMOD_EVENT *event, const FMOD_VECTOR *position, const FMOD_VECTOR *velocity, const FMOD_VECTOR *orientation);
FMOD_RESULT F_API FMOD_Event_Get3DAttributes         (FMOD_EVENT *event, FMOD_VECTOR *position, FMOD_VECTOR *velocity, FMOD_VECTOR *orientation);
FMOD_RESULT F_API FMOD_Event_Set3DOcclusion          (FMOD_EVENT *event, float directocclusion, float reverbocclusion);
FMOD_RESULT F_API FMOD_Event_Get3DOcclusion          (FMOD_EVENT *event, float *directocclusion, float *reverbocclusion);
FMOD_RESULT F_API FMOD_Event_SetReverbProperties     (FMOD_EVENT *event, const FMOD_REVERB_CHANNELPROPERTIES *props);
FMOD_RESULT F_API FMOD_Event_GetReverbProperties     (FMOD_EVENT *event, FMOD_REVERB_CHANNELPROPERTIES *props);
FMOD_RESULT F_API FMOD_Event_SetUserData             (FMOD_EVENT *event, void *userdata);
FMOD_RESULT F_API FMOD_Event_GetUserData             (FMOD_EVENT *event, void **userdata);

FMOD_RESULT F_API FMOD_Event_GetMemoryInfo           (FMOD_EVENT *event, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'EventParameter' API
*/

FMOD_RESULT F_API FMOD_EventParameter_GetInfo        (FMOD_EVENTPARAMETER *eventparameter, int *index, char **name);
FMOD_RESULT F_API FMOD_EventParameter_GetRange       (FMOD_EVENTPARAMETER *eventparameter, float *rangemin, float *rangemax);
FMOD_RESULT F_API FMOD_EventParameter_SetValue       (FMOD_EVENTPARAMETER *eventparameter, float value);
FMOD_RESULT F_API FMOD_EventParameter_GetValue       (FMOD_EVENTPARAMETER *eventparameter, float *value);
FMOD_RESULT F_API FMOD_EventParameter_SetVelocity    (FMOD_EVENTPARAMETER *eventparameter, float value);
FMOD_RESULT F_API FMOD_EventParameter_GetVelocity    (FMOD_EVENTPARAMETER *eventparameter, float *value);
FMOD_RESULT F_API FMOD_EventParameter_SetSeekSpeed   (FMOD_EVENTPARAMETER *eventparameter, float value);
FMOD_RESULT F_API FMOD_EventParameter_GetSeekSpeed   (FMOD_EVENTPARAMETER *eventparameter, float *value);
FMOD_RESULT F_API FMOD_EventParameter_SetUserData    (FMOD_EVENTPARAMETER *eventparameter, void *userdata);
FMOD_RESULT F_API FMOD_EventParameter_GetUserData    (FMOD_EVENTPARAMETER *eventparameter, void **userdata);
FMOD_RESULT F_API FMOD_EventParameter_KeyOff         (FMOD_EVENTPARAMETER *eventparameter);

FMOD_RESULT F_API FMOD_EventParameter_GetMemoryInfo  (FMOD_EVENTPARAMETER *eventparameter, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'EventReverb' API
*/

FMOD_RESULT F_API FMOD_EventReverb_Release           (FMOD_EVENTREVERB *eventreverb);
FMOD_RESULT F_API FMOD_EventReverb_Set3DAttributes   (FMOD_EVENTREVERB *eventreverb, const FMOD_VECTOR *position, float mindistance, float maxdistance);
FMOD_RESULT F_API FMOD_EventReverb_Get3DAttributes   (FMOD_EVENTREVERB *eventreverb, FMOD_VECTOR *position, float *mindistance, float *maxdistance);
FMOD_RESULT F_API FMOD_EventReverb_SetProperties     (FMOD_EVENTREVERB *eventreverb, const FMOD_REVERB_PROPERTIES *props);
FMOD_RESULT F_API FMOD_EventReverb_GetProperties     (FMOD_EVENTREVERB *eventreverb, FMOD_REVERB_PROPERTIES *props);
FMOD_RESULT F_API FMOD_EventReverb_SetActive         (FMOD_EVENTREVERB *eventreverb, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_EventReverb_GetActive         (FMOD_EVENTREVERB *eventreverb, FMOD_BOOL *active);
FMOD_RESULT F_API FMOD_EventReverb_SetUserData       (FMOD_EVENTREVERB *eventreverb, void *userdata);
FMOD_RESULT F_API FMOD_EventReverb_GetUserData       (FMOD_EVENTREVERB *eventreverb, void **userdata);

FMOD_RESULT F_API FMOD_EventReverb_GetMemoryInfo     (FMOD_EVENTREVERB *eventreverb, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'EventQueue' API
*/

FMOD_RESULT F_API FMOD_EventQueue_Release            (FMOD_EVENTQUEUE *eventqueue);
FMOD_RESULT F_API FMOD_EventQueue_Add                (FMOD_EVENTQUEUE *eventqueue, FMOD_EVENTQUEUEENTRY *entry, FMOD_BOOL allow_duplicates);
FMOD_RESULT F_API FMOD_EventQueue_Remove             (FMOD_EVENTQUEUE *eventqueue, FMOD_EVENTQUEUEENTRY *entry);
FMOD_RESULT F_API FMOD_EventQueue_RemoveHead         (FMOD_EVENTQUEUE *eventqueue);
FMOD_RESULT F_API FMOD_EventQueue_Clear              (FMOD_EVENTQUEUE *eventqueue, FMOD_BOOL stopallevents);
FMOD_RESULT F_API FMOD_EventQueue_FindFirstEntry     (FMOD_EVENTQUEUE *eventqueue, FMOD_EVENTQUEUEENTRY **entry);
FMOD_RESULT F_API FMOD_EventQueue_FindNextEntry      (FMOD_EVENTQUEUE *eventqueue, FMOD_EVENTQUEUEENTRY **entry);
FMOD_RESULT F_API FMOD_EventQueue_SetPaused          (FMOD_EVENTQUEUE *eventqueue, FMOD_BOOL paused);
FMOD_RESULT F_API FMOD_EventQueue_GetPaused          (FMOD_EVENTQUEUE *eventqueue, FMOD_BOOL *paused);
FMOD_RESULT F_API FMOD_EventQueue_IncludeDuckingCategory(FMOD_EVENTQUEUE *eventqueue, FMOD_EVENTCATEGORY *category, float ducked_volume, float unducked_volume, unsigned int duck_time, unsigned int unduck_time);
FMOD_RESULT F_API FMOD_EventQueue_ExcludeDuckingCategory(FMOD_EVENTQUEUE *eventqueue, FMOD_EVENTCATEGORY *category);
FMOD_RESULT F_API FMOD_EventQueue_SetCallback        (FMOD_EVENTQUEUE *eventqueue, FMOD_EVENTQUEUE_CALLBACK callback, void *callbackuserdata);
FMOD_RESULT F_API FMOD_EventQueue_SetUserData        (FMOD_EVENTQUEUE *eventqueue, void *userdata);
FMOD_RESULT F_API FMOD_EventQueue_GetUserData        (FMOD_EVENTQUEUE *eventqueue, void **userdata);
FMOD_RESULT F_API FMOD_EventQueue_Dump               (FMOD_EVENTQUEUE *eventqueue);

FMOD_RESULT F_API FMOD_EventQueue_GetMemoryInfo      (FMOD_EVENTQUEUE *eventqueue, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'EventQueueEntry' API
*/

FMOD_RESULT F_API FMOD_EventQueueEntry_Release       (FMOD_EVENTQUEUEENTRY *eventqueueentry);
FMOD_RESULT F_API FMOD_EventQueueEntry_GetInfoOnlyEvent(FMOD_EVENTQUEUEENTRY *eventqueueentry, FMOD_EVENT **infoonlyevent);
FMOD_RESULT F_API FMOD_EventQueueEntry_GetRealEvent  (FMOD_EVENTQUEUEENTRY *eventqueueentry, FMOD_EVENT **realevent);
FMOD_RESULT F_API FMOD_EventQueueEntry_SetPriority   (FMOD_EVENTQUEUEENTRY *eventqueueentry, unsigned char priority);
FMOD_RESULT F_API FMOD_EventQueueEntry_GetPriority   (FMOD_EVENTQUEUEENTRY *eventqueueentry, unsigned char *priority);
FMOD_RESULT F_API FMOD_EventQueueEntry_SetExpiryTime (FMOD_EVENTQUEUEENTRY *eventqueueentry, unsigned int expirytime);
FMOD_RESULT F_API FMOD_EventQueueEntry_GetExpiryTime (FMOD_EVENTQUEUEENTRY *eventqueueentry, unsigned int *expirytime);
FMOD_RESULT F_API FMOD_EventQueueEntry_SetDelayTime  (FMOD_EVENTQUEUEENTRY *eventqueueentry, unsigned int delay);
FMOD_RESULT F_API FMOD_EventQueueEntry_GetDelayTime  (FMOD_EVENTQUEUEENTRY *eventqueueentry, unsigned int *delay);
FMOD_RESULT F_API FMOD_EventQueueEntry_SetInterrupt  (FMOD_EVENTQUEUEENTRY *eventqueueentry, FMOD_BOOL interrupt);
FMOD_RESULT F_API FMOD_EventQueueEntry_GetInterrupt  (FMOD_EVENTQUEUEENTRY *eventqueueentry, FMOD_BOOL *interrupt);
FMOD_RESULT F_API FMOD_EventQueueEntry_SetCrossfadeTime(FMOD_EVENTQUEUEENTRY *eventqueueentry, int crossfade);
FMOD_RESULT F_API FMOD_EventQueueEntry_GetCrossfadeTime(FMOD_EVENTQUEUEENTRY *eventqueueentry, int *crossfade);
FMOD_RESULT F_API FMOD_EventQueueEntry_SetUserData   (FMOD_EVENTQUEUEENTRY *eventqueueentry, void *userdata);
FMOD_RESULT F_API FMOD_EventQueueEntry_GetUserData   (FMOD_EVENTQUEUEENTRY *eventqueueentry, void **userdata);

FMOD_RESULT F_API FMOD_EventQueueEntry_GetMemoryInfo (FMOD_EVENTQUEUEENTRY *eventqueueentry, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'MusicSystem' API
*/

FMOD_RESULT F_API FMOD_MusicSystem_Reset             (FMOD_MUSICSYSTEM *musicsystem);
FMOD_RESULT F_API FMOD_MusicSystem_SetVolume         (FMOD_MUSICSYSTEM *musicsystem, float volume);
FMOD_RESULT F_API FMOD_MusicSystem_GetVolume         (FMOD_MUSICSYSTEM *musicsystem, float *volume);
FMOD_RESULT F_API FMOD_MusicSystem_SetReverbProperties(FMOD_MUSICSYSTEM *musicsystem, const FMOD_REVERB_CHANNELPROPERTIES *props);
FMOD_RESULT F_API FMOD_MusicSystem_GetReverbProperties(FMOD_MUSICSYSTEM *musicsystem, FMOD_REVERB_CHANNELPROPERTIES *props);
FMOD_RESULT F_API FMOD_MusicSystem_SetPaused         (FMOD_MUSICSYSTEM *musicsystem, FMOD_BOOL paused);
FMOD_RESULT F_API FMOD_MusicSystem_GetPaused         (FMOD_MUSICSYSTEM *musicsystem, FMOD_BOOL *paused);
FMOD_RESULT F_API FMOD_MusicSystem_SetMute           (FMOD_MUSICSYSTEM *musicsystem, FMOD_BOOL mute);
FMOD_RESULT F_API FMOD_MusicSystem_GetMute           (FMOD_MUSICSYSTEM *musicsystem, FMOD_BOOL *mute);
FMOD_RESULT F_API FMOD_MusicSystem_GetInfo           (FMOD_MUSICSYSTEM *musicsystem, FMOD_MUSIC_INFO *info);
FMOD_RESULT F_API FMOD_MusicSystem_PromptCue         (FMOD_MUSICSYSTEM *musicsystem, FMOD_MUSIC_CUE_ID id);
FMOD_RESULT F_API FMOD_MusicSystem_PrepareCue        (FMOD_MUSICSYSTEM *musicsystem, FMOD_MUSIC_CUE_ID id, FMOD_MUSICPROMPT **prompt);
FMOD_RESULT F_API FMOD_MusicSystem_GetParameterValue (FMOD_MUSICSYSTEM *musicsystem, FMOD_MUSIC_PARAM_ID id, float *parameter);
FMOD_RESULT F_API FMOD_MusicSystem_SetParameterValue (FMOD_MUSICSYSTEM *musicsystem, FMOD_MUSIC_PARAM_ID id, float parameter);

FMOD_RESULT F_API FMOD_MusicSystem_GetCues           (FMOD_MUSICSYSTEM *musicsystem, FMOD_MUSIC_ITERATOR *it, const char *filter);
FMOD_RESULT F_API FMOD_MusicSystem_GetNextCue        (FMOD_MUSICSYSTEM *musicsystem, FMOD_MUSIC_ITERATOR *it);
FMOD_RESULT F_API FMOD_MusicSystem_GetParameters     (FMOD_MUSICSYSTEM *musicsystem, FMOD_MUSIC_ITERATOR *it, const char *filter);
FMOD_RESULT F_API FMOD_MusicSystem_GetNextParameter  (FMOD_MUSICSYSTEM *musicsystem, FMOD_MUSIC_ITERATOR *it);

FMOD_RESULT F_API FMOD_MusicSystem_LoadSoundData     (FMOD_MUSICSYSTEM *musicsystem, FMOD_EVENT_RESOURCE resource, FMOD_EVENT_MODE mode);
FMOD_RESULT F_API FMOD_MusicSystem_FreeSoundData     (FMOD_MUSICSYSTEM *musicsystem, FMOD_BOOL waituntilready);

FMOD_RESULT F_API FMOD_MusicSystem_SetCallback       (FMOD_MUSICSYSTEM *musicsystem, FMOD_MUSIC_CALLBACK callback, void *userdata);

FMOD_RESULT F_API FMOD_MusicSystem_GetMemoryInfo     (FMOD_MUSICSYSTEM *musicsystem, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'MusicPrompt' API
*/

FMOD_RESULT F_API FMOD_MusicPrompt_Release           (FMOD_MUSICPROMPT *musicprompt);
FMOD_RESULT F_API FMOD_MusicPrompt_Begin             (FMOD_MUSICPROMPT *musicprompt);
FMOD_RESULT F_API FMOD_MusicPrompt_End               (FMOD_MUSICPROMPT *musicprompt);
FMOD_RESULT F_API FMOD_MusicPrompt_IsActive          (FMOD_MUSICPROMPT *musicprompt, FMOD_BOOL *active);

FMOD_RESULT F_API FMOD_MusicPrompt_GetMemoryInfo     (FMOD_MUSICPROMPT *musicprompt, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);
/*$ preserve start $*/

#ifdef __cplusplus
}
#endif


#endif

/*$ preserve end $*/
