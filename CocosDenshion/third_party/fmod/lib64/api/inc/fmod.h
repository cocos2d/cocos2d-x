/*$ preserve start $*/

/* ============================================================================================ */
/* FMOD Ex - Main C/C++ header file. Copyright (c), Firelight Technologies Pty, Ltd. 2004-2011. */
/*                                                                                              */
/* This header is the base header for all other FMOD headers.  If you are programming in C      */
/* use this exclusively, or if you are programming C++ use this in conjunction with FMOD.HPP    */
/*                                                                                              */
/* ============================================================================================ */

#ifndef _FMOD_H
#define _FMOD_H

/*
    FMOD version number.  Check this against FMOD::System::getVersion.
    0xaaaabbcc -> aaaa = major version number.  bb = minor version number.  cc = development version number.
*/

#define FMOD_VERSION    0x00043800

/*
    Compiler specific settings.
*/

#if defined(__CYGWIN32__)
    #define F_CDECL __cdecl
    #define F_STDCALL __stdcall
    #define F_DECLSPEC __declspec
    #define F_DLLEXPORT ( dllexport )
#elif (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(_XBOX))
    #define F_CDECL _cdecl
    #define F_STDCALL _stdcall
    #define F_DECLSPEC __declspec
    #define F_DLLEXPORT ( dllexport )
#elif defined(__MACH__) || defined (__ANDROID__)
    #define F_CDECL
    #define F_STDCALL
    #define F_DECLSPEC
    #define F_DLLEXPORT __attribute__ ((visibility("default")))
#else
    #define F_STDCALL
    #define F_CDECL
    #define F_DECLSPEC
    #define F_DLLEXPORT
#endif

#ifdef DLL_EXPORTS
    #if defined(__MACH__) || defined(__ANDROID__) || defined(JUNGLE)
        #define F_API __attribute__ ((visibility("default")))
    #else
        #define F_API __declspec(dllexport) F_STDCALL
    #endif
#else
    #define F_API F_STDCALL
#endif

#define F_CALLBACK F_STDCALL

/*
    FMOD types.
*/

typedef int                       FMOD_BOOL;
typedef struct FMOD_SYSTEM        FMOD_SYSTEM;
typedef struct FMOD_SOUND         FMOD_SOUND;
typedef struct FMOD_CHANNEL       FMOD_CHANNEL;
typedef struct FMOD_CHANNELGROUP  FMOD_CHANNELGROUP;
typedef struct FMOD_SOUNDGROUP    FMOD_SOUNDGROUP;
typedef struct FMOD_REVERB        FMOD_REVERB;
typedef struct FMOD_DSP           FMOD_DSP;
typedef struct FMOD_DSPCONNECTION FMOD_DSPCONNECTION;
typedef struct FMOD_POLYGON		  FMOD_POLYGON;
typedef struct FMOD_GEOMETRY	  FMOD_GEOMETRY;
typedef struct FMOD_SYNCPOINT	  FMOD_SYNCPOINT;
typedef unsigned int              FMOD_MODE;
typedef unsigned int              FMOD_TIMEUNIT;
typedef unsigned int              FMOD_INITFLAGS;
typedef unsigned int              FMOD_CAPS;
typedef unsigned int              FMOD_DEBUGLEVEL;
typedef unsigned int              FMOD_MEMORY_TYPE;

/*$ fmod result start $*/
/*
[ENUM]
[
    [DESCRIPTION]   
    error codes.  Returned from every function.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
]
*/
typedef enum
{
    FMOD_OK,                        /* No errors. */
    FMOD_ERR_ALREADYLOCKED,         /* Tried to call lock a second time before unlock was called. */
    FMOD_ERR_BADCOMMAND,            /* Tried to call a function on a data type that does not allow this type of functionality (ie calling Sound::lock on a streaming sound). */
    FMOD_ERR_CDDA_DRIVERS,          /* Neither NTSCSI nor ASPI could be initialised. */
    FMOD_ERR_CDDA_INIT,             /* An error occurred while initialising the CDDA subsystem. */
    FMOD_ERR_CDDA_INVALID_DEVICE,   /* Couldn't find the specified device. */
    FMOD_ERR_CDDA_NOAUDIO,          /* No audio tracks on the specified disc. */
    FMOD_ERR_CDDA_NODEVICES,        /* No CD/DVD devices were found. */ 
    FMOD_ERR_CDDA_NODISC,           /* No disc present in the specified drive. */
    FMOD_ERR_CDDA_READ,             /* A CDDA read error occurred. */
    FMOD_ERR_CHANNEL_ALLOC,         /* Error trying to allocate a channel. */
    FMOD_ERR_CHANNEL_STOLEN,        /* The specified channel has been reused to play another sound. */
    FMOD_ERR_COM,                   /* A Win32 COM related error occured. COM failed to initialize or a QueryInterface failed meaning a Windows codec or driver was not installed properly. */
    FMOD_ERR_DMA,                   /* DMA Failure.  See debug output for more information. */
    FMOD_ERR_DSP_CONNECTION,        /* DSP connection error.  Connection possibly caused a cyclic dependancy.  Or tried to connect a tree too many units deep (more than 128). */
    FMOD_ERR_DSP_FORMAT,            /* DSP Format error.  A DSP unit may have attempted to connect to this network with the wrong format. */
    FMOD_ERR_DSP_NOTFOUND,          /* DSP connection error.  Couldn't find the DSP unit specified. */
    FMOD_ERR_DSP_RUNNING,           /* DSP error.  Cannot perform this operation while the network is in the middle of running.  This will most likely happen if a connection or disconnection is attempted in a DSP callback. */
    FMOD_ERR_DSP_TOOMANYCONNECTIONS,/* DSP connection error.  The unit being connected to or disconnected should only have 1 input or output. */
    FMOD_ERR_FILE_BAD,              /* Error loading file. */
    FMOD_ERR_FILE_COULDNOTSEEK,     /* Couldn't perform seek operation.  This is a limitation of the medium (ie netstreams) or the file format. */
    FMOD_ERR_FILE_DISKEJECTED,      /* Media was ejected while reading. */
    FMOD_ERR_FILE_EOF,              /* End of file unexpectedly reached while trying to read essential data (truncated data?). */
    FMOD_ERR_FILE_NOTFOUND,         /* File not found. */
    FMOD_ERR_FILE_UNWANTED,         /* Unwanted file access occured. */
    FMOD_ERR_FORMAT,                /* Unsupported file or audio format. */
    FMOD_ERR_HTTP,                  /* A HTTP error occurred. This is a catch-all for HTTP errors not listed elsewhere. */
    FMOD_ERR_HTTP_ACCESS,           /* The specified resource requires authentication or is forbidden. */
    FMOD_ERR_HTTP_PROXY_AUTH,       /* Proxy authentication is required to access the specified resource. */
    FMOD_ERR_HTTP_SERVER_ERROR,     /* A HTTP server error occurred. */
    FMOD_ERR_HTTP_TIMEOUT,          /* The HTTP request timed out. */
    FMOD_ERR_INITIALIZATION,        /* FMOD was not initialized correctly to support this function. */
    FMOD_ERR_INITIALIZED,           /* Cannot call this command after System::init. */
    FMOD_ERR_INTERNAL,              /* An error occured that wasn't supposed to.  Contact support. */
    FMOD_ERR_INVALID_ADDRESS,       /* On Xbox 360, this memory address passed to FMOD must be physical, (ie allocated with XPhysicalAlloc.) */
    FMOD_ERR_INVALID_FLOAT,         /* Value passed in was a NaN, Inf or denormalized float. */
    FMOD_ERR_INVALID_HANDLE,        /* An invalid object handle was used. */
    FMOD_ERR_INVALID_PARAM,         /* An invalid parameter was passed to this function. */
    FMOD_ERR_INVALID_POSITION,      /* An invalid seek position was passed to this function. */
    FMOD_ERR_INVALID_SPEAKER,       /* An invalid speaker was passed to this function based on the current speaker mode. */
    FMOD_ERR_INVALID_SYNCPOINT,     /* The syncpoint did not come from this sound handle. */
    FMOD_ERR_INVALID_VECTOR,        /* The vectors passed in are not unit length, or perpendicular. */
    FMOD_ERR_MAXAUDIBLE,            /* Reached maximum audible playback count for this sound's soundgroup. */
    FMOD_ERR_MEMORY,                /* Not enough memory or resources. */
    FMOD_ERR_MEMORY_CANTPOINT,      /* Can't use FMOD_OPENMEMORY_POINT on non PCM source data, or non mp3/xma/adpcm data if FMOD_CREATECOMPRESSEDSAMPLE was used. */
    FMOD_ERR_MEMORY_SRAM,           /* Not enough memory or resources on console sound ram. */
    FMOD_ERR_NEEDS2D,               /* Tried to call a command on a 3d sound when the command was meant for 2d sound. */
    FMOD_ERR_NEEDS3D,               /* Tried to call a command on a 2d sound when the command was meant for 3d sound. */
    FMOD_ERR_NEEDSHARDWARE,         /* Tried to use a feature that requires hardware support.  (ie trying to play a GCADPCM compressed sound in software on Wii). */
    FMOD_ERR_NEEDSSOFTWARE,         /* Tried to use a feature that requires the software engine.  Software engine has either been turned off, or command was executed on a hardware channel which does not support this feature. */
    FMOD_ERR_NET_CONNECT,           /* Couldn't connect to the specified host. */
    FMOD_ERR_NET_SOCKET_ERROR,      /* A socket error occurred.  This is a catch-all for socket-related errors not listed elsewhere. */
    FMOD_ERR_NET_URL,               /* The specified URL couldn't be resolved. */
    FMOD_ERR_NET_WOULD_BLOCK,       /* Operation on a non-blocking socket could not complete immediately. */
    FMOD_ERR_NOTREADY,              /* Operation could not be performed because specified sound/DSP connection is not ready. */
    FMOD_ERR_OUTPUT_ALLOCATED,      /* Error initializing output device, but more specifically, the output device is already in use and cannot be reused. */
    FMOD_ERR_OUTPUT_CREATEBUFFER,   /* Error creating hardware sound buffer. */
    FMOD_ERR_OUTPUT_DRIVERCALL,     /* A call to a standard soundcard driver failed, which could possibly mean a bug in the driver or resources were missing or exhausted. */
    FMOD_ERR_OUTPUT_ENUMERATION,    /* Error enumerating the available driver list. List may be inconsistent due to a recent device addition or removal. */
    FMOD_ERR_OUTPUT_FORMAT,         /* Soundcard does not support the minimum features needed for this soundsystem (16bit stereo output). */
    FMOD_ERR_OUTPUT_INIT,           /* Error initializing output device. */
    FMOD_ERR_OUTPUT_NOHARDWARE,     /* FMOD_HARDWARE was specified but the sound card does not have the resources necessary to play it. */
    FMOD_ERR_OUTPUT_NOSOFTWARE,     /* Attempted to create a software sound but no software channels were specified in System::init. */
    FMOD_ERR_PAN,                   /* Panning only works with mono or stereo sound sources. */
    FMOD_ERR_PLUGIN,                /* An unspecified error has been returned from a 3rd party plugin. */
    FMOD_ERR_PLUGIN_INSTANCES,      /* The number of allowed instances of a plugin has been exceeded. */
    FMOD_ERR_PLUGIN_MISSING,        /* A requested output, dsp unit type or codec was not available. */
    FMOD_ERR_PLUGIN_RESOURCE,       /* A resource that the plugin requires cannot be found. (ie the DLS file for MIDI playback) */
    FMOD_ERR_PRELOADED,             /* The specified sound is still in use by the event system, call EventSystem::unloadFSB before trying to release it. */
    FMOD_ERR_PROGRAMMERSOUND,       /* The specified sound is still in use by the event system, wait for the event which is using it finish with it. */
    FMOD_ERR_RECORD,                /* An error occured trying to initialize the recording device. */
    FMOD_ERR_REVERB_INSTANCE,       /* Specified instance in FMOD_REVERB_PROPERTIES couldn't be set. Most likely because it is an invalid instance number or the reverb doesnt exist. */
    FMOD_ERR_SUBSOUND_ALLOCATED,    /* This subsound is already being used by another sound, you cannot have more than one parent to a sound.  Null out the other parent's entry first. */
    FMOD_ERR_SUBSOUND_CANTMOVE,     /* Shared subsounds cannot be replaced or moved from their parent stream, such as when the parent stream is an FSB file. */
    FMOD_ERR_SUBSOUND_MODE,         /* The subsound's mode bits do not match with the parent sound's mode bits.  See documentation for function that it was called with. */
    FMOD_ERR_SUBSOUNDS,             /* The error occured because the sound referenced contains subsounds when it shouldn't have, or it doesn't contain subsounds when it should have.  The operation may also not be able to be performed on a parent sound, or a parent sound was played without setting up a sentence first. */
    FMOD_ERR_TAGNOTFOUND,           /* The specified tag could not be found or there are no tags. */
    FMOD_ERR_TOOMANYCHANNELS,       /* The sound created exceeds the allowable input channel count.  This can be increased using the maxinputchannels parameter in System::setSoftwareFormat. */
    FMOD_ERR_UNIMPLEMENTED,         /* Something in FMOD hasn't been implemented when it should be! contact support! */
    FMOD_ERR_UNINITIALIZED,         /* This command failed because System::init or System::setDriver was not called. */
    FMOD_ERR_UNSUPPORTED,           /* A command issued was not supported by this object.  Possibly a plugin without certain callbacks specified. */
    FMOD_ERR_UPDATE,                /* An error caused by System::update occured. */
    FMOD_ERR_VERSION,               /* The version number of this file format is not supported. */

    FMOD_ERR_EVENT_FAILED,          /* An Event failed to be retrieved, most likely due to 'just fail' being specified as the max playbacks behavior. */
    FMOD_ERR_EVENT_INFOONLY,        /* Can't execute this command on an EVENT_INFOONLY event. */
    FMOD_ERR_EVENT_INTERNAL,        /* An error occured that wasn't supposed to.  See debug log for reason. */
    FMOD_ERR_EVENT_MAXSTREAMS,      /* Event failed because 'Max streams' was hit when FMOD_EVENT_INIT_FAIL_ON_MAXSTREAMS was specified. */
    FMOD_ERR_EVENT_MISMATCH,        /* FSB mismatches the FEV it was compiled with, the stream/sample mode it was meant to be created with was different, or the FEV was built for a different platform. */
    FMOD_ERR_EVENT_NAMECONFLICT,    /* A category with the same name already exists. */
    FMOD_ERR_EVENT_NOTFOUND,        /* The requested event, event group, event category or event property could not be found. */
    FMOD_ERR_EVENT_NEEDSSIMPLE,     /* Tried to call a function on a complex event that's only supported by simple events. */
    FMOD_ERR_EVENT_GUIDCONFLICT,    /* An event with the same GUID already exists. */
    FMOD_ERR_EVENT_ALREADY_LOADED,  /* The specified project has already been loaded. Having multiple copies of the same project loaded simultaneously is forbidden. */

    FMOD_ERR_MUSIC_UNINITIALIZED,   /* Music system is not initialized probably because no music data is loaded. */
    FMOD_ERR_MUSIC_NOTFOUND,        /* The requested music entity could not be found. */
    FMOD_ERR_MUSIC_NOCALLBACK,      /* The music callback is required, but it has not been set. */

    FMOD_RESULT_FORCEINT = 65536    /* Makes sure this enum is signed 32bit. */
} FMOD_RESULT;
/*$ fmod result end $*/


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Structure describing a point in 3D space.

    [REMARKS]
    FMOD uses a left handed co-ordinate system by default.<br>
    To use a right handed co-ordinate system specify FMOD_INIT_3D_RIGHTHANDED from FMOD_INITFLAGS in System::init.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    System::set3DListenerAttributes
    System::get3DListenerAttributes
    Channel::set3DAttributes
    Channel::get3DAttributes
    Channel::set3DCustomRolloff
    Channel::get3DCustomRolloff
    Sound::set3DCustomRolloff
    Sound::get3DCustomRolloff
    Geometry::addPolygon
    Geometry::setPolygonVertex
    Geometry::getPolygonVertex
    Geometry::setRotation
    Geometry::getRotation
    Geometry::setPosition
    Geometry::getPosition
    Geometry::setScale
    Geometry::getScale
    FMOD_INITFLAGS
]
*/
typedef struct
{
	float x;        /* X co-ordinate in 3D space. */
    float y;        /* Y co-ordinate in 3D space. */
    float z;        /* Z co-ordinate in 3D space. */
} FMOD_VECTOR;

/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Structure describing a globally unique identifier.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    System::getDriverInfo
]
*/
typedef struct
{
    unsigned int   Data1;       /* Specifies the first 8 hexadecimal digits of the GUID */
    unsigned short Data2;       /* Specifies the first group of 4 hexadecimal digits.   */
    unsigned short Data3;       /* Specifies the second group of 4 hexadecimal digits.  */
    unsigned char  Data4[8];    /* Array of 8 bytes. The first 2 bytes contain the third group of 4 hexadecimal digits. The remaining 6 bytes contain the final 12 hexadecimal digits. */
} FMOD_GUID;

/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Structure that is passed into FMOD_FILE_ASYNCREADCALLBACK.  Use the information in this structure to perform

    [REMARKS]
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>
    <br>
    Instructions: write to 'buffer', and 'bytesread' <b>BEFORE</b> setting 'result'.<br>  
    As soon as result is set, FMOD will asynchronously continue internally using the data provided in this structure.<br>
    <br>
    Set 'result' to the result expected from a normal file read callback.<br>
    If the read was successful, set it to FMOD_OK.<br>
    If it read some data but hit the end of the file, set it to FMOD_ERR_FILE_EOF.<br>
    If a bad error occurred, return FMOD_ERR_FILE_BAD<br>
    If a disk was ejected, return FMOD_ERR_FILE_DISKEJECTED.<br>

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    FMOD_FILE_ASYNCREADCALLBACK
    FMOD_FILE_ASYNCCANCELCALLBACK
]
*/
typedef struct
{
    void           *handle;         /* [r] The file handle that was filled out in the open callback. */
    unsigned int    offset;         /* [r] Seek position, make sure you read from this file offset. */
    unsigned int    sizebytes;      /* [r] how many bytes requested for read. */
    int             priority;       /* [r] 0 = low importance.  100 = extremely important (ie 'must read now or stuttering may occur') */

    void           *buffer;         /* [w] Buffer to read file data into. */
    unsigned int    bytesread;      /* [w] Fill this in before setting result code to tell FMOD how many bytes were read. */
    FMOD_RESULT     result;         /* [r/w] Result code, FMOD_OK tells the system it is ready to consume the data.  Set this last!  Default value = FMOD_ERR_NOTREADY. */

    void           *userdata;       /* [r] User data pointer. */
} FMOD_ASYNCREADINFO;


/*
[ENUM]
[
    [DESCRIPTION]   
    These output types are used with System::setOutput / System::getOutput, to choose which output method to use.
  
    [REMARKS]
    To pass information to the driver when initializing fmod use the extradriverdata parameter in System::init for the following reasons.<br>
    <li>FMOD_OUTPUTTYPE_WAVWRITER - extradriverdata is a pointer to a char * filename that the wav writer will output to.
    <li>FMOD_OUTPUTTYPE_WAVWRITER_NRT - extradriverdata is a pointer to a char * filename that the wav writer will output to.
    <li>FMOD_OUTPUTTYPE_DSOUND - extradriverdata is a pointer to a HWND so that FMOD can set the focus on the audio for a particular window.
    <li>FMOD_OUTPUTTYPE_PS3 - extradriverdata is a pointer to a FMOD_PS3_EXTRADRIVERDATA struct. This can be found in fmodps3.h.
    <li>FMOD_OUTPUTTYPE_GC - extradriverdata is a pointer to a FMOD_GC_INFO struct. This can be found in fmodgc.h.
    <li>FMOD_OUTPUTTYPE_WII - extradriverdata is a pointer to a FMOD_WII_INFO struct. This can be found in fmodwii.h.
    <li>FMOD_OUTPUTTYPE_ALSA - extradriverdata is a pointer to a FMOD_LINUX_EXTRADRIVERDATA struct. This can be found in fmodlinux.h.<br>
    <br>
    Currently these are the only FMOD drivers that take extra information.  Other unknown plugins may have different requirements.
    <br><br>
    Note! If FMOD_OUTPUTTYPE_WAVWRITER_NRT or FMOD_OUTPUTTYPE_NOSOUND_NRT are used, and if the System::update function is being called
    very quickly (ie for a non realtime decode) it may be being called too quickly for the FMOD streamer thread to respond to.  
    The result will be a skipping/stuttering output in the captured audio.<br>
    <br>
    To remedy this, disable the FMOD Ex streamer thread, and use FMOD_INIT_STREAM_FROM_UPDATE to avoid skipping in the output stream,
    as it will lock the mixer and the streamer together in the same thread.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    System::setOutput
    System::getOutput
    System::setSoftwareFormat
    System::getSoftwareFormat
    System::init
    System::update
    FMOD_INITFLAGS
]
*/
typedef enum
{
    FMOD_OUTPUTTYPE_AUTODETECT,      /* Picks the best output mode for the platform.  This is the default. */
                                     
    FMOD_OUTPUTTYPE_UNKNOWN,         /* All             - 3rd party plugin, unknown.  This is for use with System::getOutput only. */
    FMOD_OUTPUTTYPE_NOSOUND,         /* All             - All calls in this mode succeed but make no sound. */
    FMOD_OUTPUTTYPE_WAVWRITER,       /* All             - Writes output to fmodoutput.wav by default.  Use the 'extradriverdata' parameter in System::init, by simply passing the filename as a string, to set the wav filename. */
    FMOD_OUTPUTTYPE_NOSOUND_NRT,     /* All             - Non-realtime version of FMOD_OUTPUTTYPE_NOSOUND.  User can drive mixer with System::update at whatever rate they want. */
    FMOD_OUTPUTTYPE_WAVWRITER_NRT,   /* All             - Non-realtime version of FMOD_OUTPUTTYPE_WAVWRITER.  User can drive mixer with System::update at whatever rate they want. */
                                     
    FMOD_OUTPUTTYPE_DSOUND,          /* Win32/Win64     - DirectSound output.                       (Default on Windows XP and below) */
    FMOD_OUTPUTTYPE_WINMM,           /* Win32/Win64     - Windows Multimedia output. */
    FMOD_OUTPUTTYPE_WASAPI,          /* Win32           - Windows Audio Session API.                (Default on Windows Vista and above) */
    FMOD_OUTPUTTYPE_ASIO,            /* Win32           - Low latency ASIO 2.0 driver. */
    FMOD_OUTPUTTYPE_OSS,             /* Linux/Linux64   - Open Sound System output.                 (Default on Linux, third preference) */
    FMOD_OUTPUTTYPE_ALSA,            /* Linux/Linux64   - Advanced Linux Sound Architecture output. (Default on Linux, second preference if available) */
    FMOD_OUTPUTTYPE_ESD,             /* Linux/Linux64   - Enlightment Sound Daemon output. */
    FMOD_OUTPUTTYPE_PULSEAUDIO,      /* Linux/Linux64   - PulseAudio output.                        (Default on Linux, first preference if available) */
    FMOD_OUTPUTTYPE_COREAUDIO,       /* Mac             - Macintosh CoreAudio output.               (Default on Mac) */
    FMOD_OUTPUTTYPE_XBOX360,         /* Xbox 360        - Native Xbox360 output.                    (Default on Xbox 360) */
    FMOD_OUTPUTTYPE_PSP,             /* PSP             - Native PSP output.                        (Default on PSP) */
    FMOD_OUTPUTTYPE_PS3,             /* PS3             - Native PS3 output.                        (Default on PS3) */
    FMOD_OUTPUTTYPE_NGP,             /* NGP             - Native NGP output.                        (Default on NGP) */
	FMOD_OUTPUTTYPE_WII,			 /* Wii			    - Native Wii output.                        (Default on Wii) */
    FMOD_OUTPUTTYPE_3DS,             /* 3DS             - Native 3DS output                         (Default on 3DS) */
    FMOD_OUTPUTTYPE_AUDIOTRACK,      /* Android         - Java Audio Track output.                  (Default on Android 2.2 and below) */
    FMOD_OUTPUTTYPE_OPENSL,          /* Android         - OpenSL ES output.                         (Default on Android 2.3 and above) */   
    FMOD_OUTPUTTYPE_NACL,            /* Native Client   - Native Client output.                     (Default on Native Client) */   

    FMOD_OUTPUTTYPE_MAX,             /* Maximum number of output types supported. */
    FMOD_OUTPUTTYPE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_OUTPUTTYPE;


/*
[DEFINE] 
[
    [NAME]
    FMOD_CAPS

    [DESCRIPTION]   
    Bit fields to use with System::getDriverCaps to determine the capabilities of a card / output device.

    [REMARKS]
    It is important to check FMOD_CAPS_HARDWARE_EMULATED on windows machines, to then adjust System::setDSPBufferSize to (1024, 10) to compensate for the higher latency.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    System::getDriverCaps
    System::setDSPBufferSize
]
*/
#define FMOD_CAPS_NONE                   0x00000000  /* Device has no special capabilities. */
#define FMOD_CAPS_HARDWARE               0x00000001  /* Device supports hardware mixing. */
#define FMOD_CAPS_HARDWARE_EMULATED      0x00000002  /* User has device set to 'Hardware acceleration = off' in control panel, and now extra 200ms latency is incurred. */
#define FMOD_CAPS_OUTPUT_MULTICHANNEL    0x00000004  /* Device can do multichannel output, ie greater than 2 channels. */
#define FMOD_CAPS_OUTPUT_FORMAT_PCM8     0x00000008  /* Device can output to 8bit integer PCM. */
#define FMOD_CAPS_OUTPUT_FORMAT_PCM16    0x00000010  /* Device can output to 16bit integer PCM. */
#define FMOD_CAPS_OUTPUT_FORMAT_PCM24    0x00000020  /* Device can output to 24bit integer PCM. */
#define FMOD_CAPS_OUTPUT_FORMAT_PCM32    0x00000040  /* Device can output to 32bit integer PCM. */
#define FMOD_CAPS_OUTPUT_FORMAT_PCMFLOAT 0x00000080  /* Device can output to 32bit floating point PCM. */
#define FMOD_CAPS_REVERB_LIMITED         0x00002000  /* Device supports some form of limited hardware reverb, maybe parameterless and only selectable by environment. */
/* [DEFINE_END] */

/*
[DEFINE] 
[
    [NAME]
    FMOD_DEBUGLEVEL

    [DESCRIPTION]   
    Bit fields to use with FMOD::Debug_SetLevel / FMOD::Debug_GetLevel to control the level of tty debug output with logging versions of FMOD (fmodL).

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    Debug_SetLevel 
    Debug_GetLevel
]
*/
#define FMOD_DEBUG_LEVEL_NONE           0x00000000
#define FMOD_DEBUG_LEVEL_LOG            0x00000001      /* Will display generic logging messages. */
#define FMOD_DEBUG_LEVEL_ERROR          0x00000002      /* Will display errors. */
#define FMOD_DEBUG_LEVEL_WARNING        0x00000004      /* Will display warnings that are not fatal. */
#define FMOD_DEBUG_LEVEL_HINT           0x00000008      /* Will hint to you if there is something possibly better you could be doing. */
#define FMOD_DEBUG_LEVEL_ALL            0x000000FF    
#define FMOD_DEBUG_TYPE_MEMORY          0x00000100      /* Show FMOD memory related logging messages. */
#define FMOD_DEBUG_TYPE_THREAD          0x00000200      /* Show FMOD thread related logging messages. */
#define FMOD_DEBUG_TYPE_FILE            0x00000400      /* Show FMOD file system related logging messages. */
#define FMOD_DEBUG_TYPE_NET             0x00000800      /* Show FMOD network related logging messages. */
#define FMOD_DEBUG_TYPE_EVENT           0x00001000      /* Show FMOD Event related logging messages. */
#define FMOD_DEBUG_TYPE_ALL             0x0000FFFF                      
#define FMOD_DEBUG_DISPLAY_TIMESTAMPS   0x01000000      /* Display the timestamp of the log entry in milliseconds. */
#define FMOD_DEBUG_DISPLAY_LINENUMBERS  0x02000000      /* Display the FMOD Ex source code line numbers, for debugging purposes. */
#define FMOD_DEBUG_DISPLAY_COMPRESS     0x04000000      /* If a message is repeated more than 5 times it will stop displaying it and instead display the number of times the message was logged. */
#define FMOD_DEBUG_DISPLAY_THREAD       0x08000000      /* Display the thread ID of the calling function that caused this log entry to appear. */
#define FMOD_DEBUG_DISPLAY_ALL          0x0F000000
#define FMOD_DEBUG_ALL                  0xFFFFFFFF
/* [DEFINE_END] */


/*
[DEFINE] 
[
    [NAME]
    FMOD_MEMORY_TYPE

    [DESCRIPTION]   
    Bit fields for memory allocation type being passed into FMOD memory callbacks.

    [REMARKS]
    Remember this is a bitfield.  You may get more than 1 bit set (ie physical + persistent) so do not simply switch on the types!  You must check each bit individually or clear out the bits that you do not want within the callback.<br>
    Bits can be excluded if you want during Memory_Initialize so that you never get them.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    FMOD_MEMORY_ALLOCCALLBACK
    FMOD_MEMORY_REALLOCCALLBACK
    FMOD_MEMORY_FREECALLBACK
    Memory_Initialize
    
]
*/
#define FMOD_MEMORY_NORMAL             0x00000000       /* Standard memory. */
#define FMOD_MEMORY_STREAM_FILE        0x00000001       /* Stream file buffer, size controllable with System::setStreamBufferSize. */
#define FMOD_MEMORY_STREAM_DECODE      0x00000002       /* Stream decode buffer, size controllable with FMOD_CREATESOUNDEXINFO::decodebuffersize. */
#define FMOD_MEMORY_SAMPLEDATA         0x00000004       /* Sample data buffer.  Raw audio data, usually PCM/MPEG/ADPCM/XMA data. */
#define FMOD_MEMORY_DSP_OUTPUTBUFFER   0x00000008       /* DSP memory block allocated when more than 1 output exists on a DSP node. */
#define FMOD_MEMORY_XBOX360_PHYSICAL   0x00100000       /* Requires XPhysicalAlloc / XPhysicalFree. */
#define FMOD_MEMORY_PERSISTENT         0x00200000       /* Persistent memory. Memory will be freed when System::release is called. */
#define FMOD_MEMORY_SECONDARY          0x00400000       /* Secondary memory. Allocation should be in secondary memory. For example RSX on the PS3. */
#define FMOD_MEMORY_ALL                0xFFFFFFFF
/* [DEFINE_END] */


/*
[ENUM]
[
    [DESCRIPTION]   
    These are speaker types defined for use with the System::setSpeakerMode or System::getSpeakerMode command.

    [REMARKS]
    These are important notes on speaker modes in regards to sounds created with FMOD_SOFTWARE.<br>
    Note below the phrase 'sound channels' is used.  These are the subchannels inside a sound, they are not related and 
    have nothing to do with the FMOD class "Channel".<br>
    For example a mono sound has 1 sound channel, a stereo sound has 2 sound channels, and an AC3 or 6 channel wav file have 6 "sound channels".<br>
    <br>
    FMOD_SPEAKERMODE_RAW<br>
    ---------------------<br>
    This mode is for output devices that are not specifically mono/stereo/quad/surround/5.1 or 7.1, but are multichannel.<br>
    Use System::setSoftwareFormat to specify the number of speakers you want to address, otherwise it will default to 2 (stereo).<br>
    Sound channels map to speakers sequentially, so a mono sound maps to output speaker 0, stereo sound maps to output speaker 0 & 1.<br>
    The user assumes knowledge of the speaker order.  FMOD_SPEAKER enumerations may not apply, so raw channel indices should be used.<br>
    Multichannel sounds map input channels to output channels 1:1. <br>
    Channel::setPan and Channel::setSpeakerMix do not work.<br>
    Speaker levels must be manually set with Channel::setSpeakerLevels.<br>
    <br>
    FMOD_SPEAKERMODE_MONO<br>
    ---------------------<br>
    This mode is for a 1 speaker arrangement.<br>
    Panning does not work in this speaker mode.<br>
    Mono, stereo and multichannel sounds have each sound channel played on the one speaker unity.<br>
    Mix behavior for multichannel sounds can be set with Channel::setSpeakerLevels.<br>
    Channel::setSpeakerMix does not work.<br>
    <br>
    FMOD_SPEAKERMODE_STEREO<br>
    -----------------------<br>
    This mode is for 2 speaker arrangements that have a left and right speaker.<br>
    <li>Mono sounds default to an even distribution between left and right.  They can be panned with Channel::setPan.<br>
    <li>Stereo sounds default to the middle, or full left in the left speaker and full right in the right speaker.  
    <li>They can be cross faded with Channel::setPan.<br>
    <li>Multichannel sounds have each sound channel played on each speaker at unity.<br>
    <li>Mix behavior for multichannel sounds can be set with Channel::setSpeakerLevels.<br>
    <li>Channel::setSpeakerMix works but only front left and right parameters are used, the rest are ignored.<br>
    <br>
    FMOD_SPEAKERMODE_QUAD<br>
    ------------------------<br>
    This mode is for 4 speaker arrangements that have a front left, front right, rear left and a rear right speaker.<br>
    <li>Mono sounds default to an even distribution between front left and front right.  They can be panned with Channel::setPan.<br>
    <li>Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.<br>
    <li>They can be cross faded with Channel::setPan.<br>
    <li>Multichannel sounds default to all of their sound channels being played on each speaker in order of input.<br>
    <li>Mix behavior for multichannel sounds can be set with Channel::setSpeakerLevels.<br>
    <li>Channel::setSpeakerMix works but side left, side right, center and lfe are ignored.<br>
    <br>
    FMOD_SPEAKERMODE_SURROUND<br>
    ------------------------<br>
    This mode is for 5 speaker arrangements that have a left/right/center/rear left/rear right.<br>
    <li>Mono sounds default to the center speaker.  They can be panned with Channel::setPan.<br>
    <li>Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.  
    <li>They can be cross faded with Channel::setPan.<br>
    <li>Multichannel sounds default to all of their sound channels being played on each speaker in order of input.  
    <li>Mix behavior for multichannel sounds can be set with Channel::setSpeakerLevels.<br>
    <li>Channel::setSpeakerMix works but side left / side right are ignored.<br>
    <br>
    FMOD_SPEAKERMODE_5POINT1<br>
    ------------------------<br>
    This mode is for 5.1 speaker arrangements that have a left/right/center/rear left/rear right and a subwoofer speaker.<br>
    <li>Mono sounds default to the center speaker.  They can be panned with Channel::setPan.<br>
    <li>Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.  
    <li>They can be cross faded with Channel::setPan.<br>
    <li>Multichannel sounds default to all of their sound channels being played on each speaker in order of input.  
    <li>Mix behavior for multichannel sounds can be set with Channel::setSpeakerLevels.<br>
    <li>Channel::setSpeakerMix works but side left / side right are ignored.<br>
    <br>
    FMOD_SPEAKERMODE_7POINT1<br>
    ------------------------<br>
    This mode is for 7.1 speaker arrangements that have a left/right/center/rear left/rear right/side left/side right 
    and a subwoofer speaker.<br>
    <li>Mono sounds default to the center speaker.  They can be panned with Channel::setPan.<br>
    <li>Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.  
    <li>They can be cross faded with Channel::setPan.<br>
    <li>Multichannel sounds default to all of their sound channels being played on each speaker in order of input.  
    <li>Mix behavior for multichannel sounds can be set with Channel::setSpeakerLevels.<br>
    <li>Channel::setSpeakerMix works and every parameter is used to set the balance of a sound in any speaker.<br>
    <br>
    FMOD_SPEAKERMODE_PROLOGIC<br>
    ------------------------------------------------------<br>
    This mode is for mono, stereo, 5.1 and 7.1 speaker arrangements, as it is backwards and forwards compatible with stereo, 
    but to get a surround effect a Dolby Prologic or Prologic 2 hardware decoder / amplifier is needed.<br>
    Pan behavior is the same as FMOD_SPEAKERMODE_5POINT1.<br>
    <br>
    If this function is called the numoutputchannels setting in System::setSoftwareFormat is overwritten.<br>
    <br>
    Output rate must be 44100, 48000 or 96000 for this to work otherwise FMOD_ERR_OUTPUT_INIT will be returned.<br>

    FMOD_SPEAKERMODE_MYEARS<br>
    ------------------------------------------------------<br>
    This mode is for headphones.  This will attempt to load a MyEars profile (see myears.net.au) and use it to generate
    surround sound on headphones using a personalized HRTF algorithm, for realistic 3d sound.<br>
    Pan behavior is the same as FMOD_SPEAKERMODE_7POINT1.<br>
    MyEars speaker mode will automatically be set if the speakermode is FMOD_SPEAKERMODE_STEREO and the MyEars profile exists.<br>
    If this mode is set explicitly, FMOD_INIT_DISABLE_MYEARS_AUTODETECT has no effect.<br>
    If this mode is set explicitly and the MyEars profile does not exist, FMOD_ERR_OUTPUT_DRIVERCALL will be returned.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    System::setSpeakerMode
    System::getSpeakerMode
    System::getDriverCaps
    System::setSoftwareFormat
    Channel::setSpeakerLevels
]
*/
typedef enum
{
    FMOD_SPEAKERMODE_RAW,              /* There is no specific speakermode.  Sound channels are mapped in order of input to output.  Use System::setSoftwareFormat to specify speaker count. See remarks for more information. */
    FMOD_SPEAKERMODE_MONO,             /* The speakers are monaural. */
    FMOD_SPEAKERMODE_STEREO,           /* The speakers are stereo (DEFAULT). */
    FMOD_SPEAKERMODE_QUAD,             /* 4 speaker setup.  This includes front left, front right, rear left, rear right.  */
    FMOD_SPEAKERMODE_SURROUND,         /* 5 speaker setup.  This includes front left, front right, center, rear left, rear right. */
    FMOD_SPEAKERMODE_5POINT1,          /* 5.1 speaker setup.  This includes front left, front right, center, rear left, rear right and a subwoofer. */
    FMOD_SPEAKERMODE_7POINT1,          /* 7.1 speaker setup.  This includes front left, front right, center, rear left, rear right, side left, side right and a subwoofer. */
    
    FMOD_SPEAKERMODE_PROLOGIC,         /* Stereo output, but data is encoded to be played on a Prologic 2 / CircleSurround decoder in 5.1 via an analog connection.  See remarks about limitations. */
    FMOD_SPEAKERMODE_MYEARS,           /* Stereo output, but data is encoded using personalized HRTF algorithms.  See myears.net.au */

    FMOD_SPEAKERMODE_MAX,              /* Maximum number of speaker modes supported. */
    FMOD_SPEAKERMODE_FORCEINT = 65536  /* Makes sure this enum is signed 32bit. */
} FMOD_SPEAKERMODE;


/*
[ENUM]
[
    [DESCRIPTION]   
    These are speaker types defined for use with the Channel::setSpeakerLevels command.
    It can also be used for speaker placement in the System::set3DSpeakerPosition command.

    [REMARKS]
    If you are using FMOD_SPEAKERMODE_RAW and speaker assignments are meaningless, just cast a raw integer value to this type.<br>
    For example (FMOD_SPEAKER)7 would use the 7th speaker (also the same as FMOD_SPEAKER_SIDE_RIGHT).<br>
    Values higher than this can be used if an output system has more than 8 speaker types / output channels.  15 is the current maximum.<br>
    <br>
    NOTE: On Playstation 3 in 7.1, the extra 2 speakers are not side left/side right, they are 'surround back left'/'surround back right' which
    locate the speakers behind the listener instead of to the sides like on PC.  FMOD_SPEAKER_SBL/FMOD_SPEAKER_SBR are provided to make it 
    clearer what speaker is being addressed on that platform.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    FMOD_SPEAKERMODE
    Channel::setSpeakerLevels
    Channel::getSpeakerLevels
    System::set3DSpeakerPosition
    System::get3DSpeakerPosition
]
*/
typedef enum
{
    FMOD_SPEAKER_FRONT_LEFT,
    FMOD_SPEAKER_FRONT_RIGHT,
    FMOD_SPEAKER_FRONT_CENTER,
    FMOD_SPEAKER_LOW_FREQUENCY,
    FMOD_SPEAKER_BACK_LEFT,
    FMOD_SPEAKER_BACK_RIGHT,
    FMOD_SPEAKER_SIDE_LEFT,
    FMOD_SPEAKER_SIDE_RIGHT,
    
    FMOD_SPEAKER_MAX,                                       /* Maximum number of speaker types supported. */
    FMOD_SPEAKER_MONO        = FMOD_SPEAKER_FRONT_LEFT,     /* For use with FMOD_SPEAKERMODE_MONO and Channel::SetSpeakerLevels.  Mapped to same value as FMOD_SPEAKER_FRONT_LEFT. */
    FMOD_SPEAKER_NULL        = 65535,                       /* A non speaker.  Use this with ASIO mapping to ignore a speaker. */
    FMOD_SPEAKER_SBL         = FMOD_SPEAKER_SIDE_LEFT,      /* For use with FMOD_SPEAKERMODE_7POINT1 on PS3 where the extra speakers are surround back inside of side speakers. */
    FMOD_SPEAKER_SBR         = FMOD_SPEAKER_SIDE_RIGHT,     /* For use with FMOD_SPEAKERMODE_7POINT1 on PS3 where the extra speakers are surround back inside of side speakers. */
    FMOD_SPEAKER_FORCEINT    = 65536                        /* Makes sure this enum is signed 32bit. */
} FMOD_SPEAKER;


/*
[ENUM]
[
    [DESCRIPTION]   
    These are plugin types defined for use with the System::getNumPlugins, 
    System::getPluginInfo and System::unloadPlugin functions.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    System::getNumPlugins
    System::getPluginInfo
    System::unloadPlugin
]
*/
typedef enum
{
    FMOD_PLUGINTYPE_OUTPUT,          /* The plugin type is an output module.  FMOD mixed audio will play through one of these devices */
    FMOD_PLUGINTYPE_CODEC,           /* The plugin type is a file format codec.  FMOD will use these codecs to load file formats for playback. */
    FMOD_PLUGINTYPE_DSP,             /* The plugin type is a DSP unit.  FMOD will use these plugins as part of its DSP network to apply effects to output or generate sound in realtime. */

    FMOD_PLUGINTYPE_MAX,             /* Maximum number of plugin types supported. */
    FMOD_PLUGINTYPE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_PLUGINTYPE;


/*
[DEFINE]
[
    [NAME]
    FMOD_INITFLAGS

    [DESCRIPTION]   
    Initialization flags.  Use them with System::init in the flags parameter to change various behavior.  

    [REMARKS]
    Use System::setAdvancedSettings to adjust settings for some of the features that are enabled by these flags.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    System::init
    System::update 
    System::setAdvancedSettings
    Channel::set3DOcclusion
]
*/
#define FMOD_INIT_NORMAL                     0x00000000 /* All platforms - Initialize normally */
#define FMOD_INIT_STREAM_FROM_UPDATE         0x00000001 /* All platforms - No stream thread is created internally.  Streams are driven from System::update.  Mainly used with non-realtime outputs. */
#define FMOD_INIT_3D_RIGHTHANDED             0x00000002 /* All platforms - FMOD will treat +X as right, +Y as up and +Z as backwards (towards you). */
#define FMOD_INIT_SOFTWARE_DISABLE           0x00000004 /* All platforms - Disable software mixer to save memory.  Anything created with FMOD_SOFTWARE will fail and DSP will not work. */
#define FMOD_INIT_OCCLUSION_LOWPASS          0x00000008 /* All platforms - All FMOD_SOFTWARE (and FMOD_HARDWARE on 3DS and NGP) with FMOD_3D based voices will add a software lowpass filter effect into the DSP chain which is automatically used when Channel::set3DOcclusion is used or the geometry API. */
#define FMOD_INIT_HRTF_LOWPASS               0x00000010 /* All platforms - All FMOD_SOFTWARE (and FMOD_HARDWARE on 3DS and NGP) with FMOD_3D based voices will add a software lowpass filter effect into the DSP chain which causes sounds to sound duller when the sound goes behind the listener.  Use System::setAdvancedSettings to adjust cutoff frequency. */
#define FMOD_INIT_DISTANCE_FILTERING         0x00000200 /* All platforms - All FMOD_SOFTWARE with FMOD_3D based voices will add a software lowpass and highpass filter effect into the DSP chain which will act as a distance-automated bandpass filter. Use System::setAdvancedSettings to adjust the center frequency. */
#define FMOD_INIT_SOFTWARE_REVERB_LOWMEM     0x00000040 /* All platforms - SFX reverb is run using 22/24khz delay buffers, halving the memory required. */
#define FMOD_INIT_ENABLE_PROFILE             0x00000020 /* All platforms - Enable TCP/IP based host which allows FMOD Designer or FMOD Profiler to connect to it, and view memory, CPU and the DSP network graph in real-time. */
#define FMOD_INIT_VOL0_BECOMES_VIRTUAL       0x00000080 /* All platforms - Any sounds that are 0 volume will go virtual and not be processed except for having their positions updated virtually.  Use System::setAdvancedSettings to adjust what volume besides zero to switch to virtual at. */
#define FMOD_INIT_WASAPI_EXCLUSIVE           0x00000100 /* Win32 Vista only - for WASAPI output - Enable exclusive access to hardware, lower latency at the expense of excluding other applications from accessing the audio hardware. */
#define FMOD_INIT_PS3_PREFERDTS              0x00800000 /* PS3 only - Prefer DTS over Dolby Digital if both are supported. Note: 8 and 6 channel LPCM is always preferred over both DTS and Dolby Digital. */
#define FMOD_INIT_PS3_FORCE2CHLPCM           0x01000000 /* PS3 only - Force PS3 system output mode to 2 channel LPCM. */
#define FMOD_INIT_DISABLEDOLBY               0x00100000 /* Wii / 3DS - Disable Dolby Pro Logic surround. Speakermode will be set to STEREO even if user has selected surround in the system settings. */
#define FMOD_INIT_SYSTEM_MUSICMUTENOTPAUSE   0x00200000 /* Xbox 360 / PS3 - The "music" channelgroup which by default pauses when custom 360 dashboard / PS3 BGM music is played, can be changed to mute (therefore continues playing) instead of pausing, by using this flag. */
#define FMOD_INIT_SYNCMIXERWITHUPDATE        0x00400000 /* Win32/Wii/PS3/Xbox/Xbox 360 - FMOD Mixer thread is woken up to do a mix when System::update is called rather than waking periodically on its own timer. */
#define FMOD_INIT_GEOMETRY_USECLOSEST        0x04000000 /* All platforms - With the geometry engine, only process the closest polygon rather than accumulating all polygons the sound to listener line intersects. */
#define FMOD_INIT_DISABLE_MYEARS_AUTODETECT  0x08000000 /* Win32 - Disables automatic setting of FMOD_SPEAKERMODE_STEREO to FMOD_SPEAKERMODE_MYEARS if the MyEars profile exists on the PC.  MyEars is HRTF 7.1 downmixing through headphones. */
/* [DEFINE_END] */


/*
[ENUM]
[
    [DESCRIPTION]   
    These definitions describe the type of song being played.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    Sound::getFormat
]
*/
typedef enum
{
    FMOD_SOUND_TYPE_UNKNOWN,         /* 3rd party / unknown plugin format. */
    FMOD_SOUND_TYPE_AIFF,            /* AIFF. */
    FMOD_SOUND_TYPE_ASF,             /* Microsoft Advanced Systems Format (ie WMA/ASF/WMV). */
    FMOD_SOUND_TYPE_AT3,             /* Sony ATRAC 3 format */
    FMOD_SOUND_TYPE_CDDA,            /* Digital CD audio. */
    FMOD_SOUND_TYPE_DLS,             /* Sound font / downloadable sound bank. */
    FMOD_SOUND_TYPE_FLAC,            /* FLAC lossless codec. */
    FMOD_SOUND_TYPE_FSB,             /* FMOD Sample Bank. */
    FMOD_SOUND_TYPE_GCADPCM,         /* Nintendo GameCube/Wii ADPCM */
    FMOD_SOUND_TYPE_IT,              /* Impulse Tracker. */
    FMOD_SOUND_TYPE_MIDI,            /* MIDI. extracodecdata is a pointer to an FMOD_MIDI_EXTRACODECDATA structure. */
    FMOD_SOUND_TYPE_MOD,             /* Protracker / Fasttracker MOD. */
    FMOD_SOUND_TYPE_MPEG,            /* MP2/MP3 MPEG. */
    FMOD_SOUND_TYPE_OGGVORBIS,       /* Ogg vorbis. */
    FMOD_SOUND_TYPE_PLAYLIST,        /* Information only from ASX/PLS/M3U/WAX playlists */
    FMOD_SOUND_TYPE_RAW,             /* Raw PCM data. */
    FMOD_SOUND_TYPE_S3M,             /* ScreamTracker 3. */
    FMOD_SOUND_TYPE_SF2,             /* Sound font 2 format. */
    FMOD_SOUND_TYPE_USER,            /* User created sound. */
    FMOD_SOUND_TYPE_WAV,             /* Microsoft WAV. */
    FMOD_SOUND_TYPE_XM,              /* FastTracker 2 XM. */
    FMOD_SOUND_TYPE_XMA,             /* Xbox360 XMA */
    FMOD_SOUND_TYPE_VAG,             /* PlayStation Portable ADPCM VAG format. */
    FMOD_SOUND_TYPE_AUDIOQUEUE,      /* iPhone hardware decoder, supports AAC, ALAC and MP3. extracodecdata is a pointer to an FMOD_AUDIOQUEUE_EXTRACODECDATA structure. */
    FMOD_SOUND_TYPE_XWMA,            /* Xbox360 XWMA */
    FMOD_SOUND_TYPE_BCWAV,           /* 3DS BCWAV container format for DSP ADPCM and PCM */
    FMOD_SOUND_TYPE_AT9,             /* NGP ATRAC 9 format */

    FMOD_SOUND_TYPE_MAX,             /* Maximum number of sound types supported. */
    FMOD_SOUND_TYPE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_SOUND_TYPE;


/*
[ENUM]
[
    [DESCRIPTION]   
    These definitions describe the native format of the hardware or software buffer that will be used.

    [REMARKS]
    This is the format the native hardware or software buffer will be or is created in.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    System::createSound
    Sound::getFormat
]
*/
typedef enum
{
    FMOD_SOUND_FORMAT_NONE,             /* Unitialized / unknown. */
    FMOD_SOUND_FORMAT_PCM8,             /* 8bit integer PCM data. */
    FMOD_SOUND_FORMAT_PCM16,            /* 16bit integer PCM data. */
    FMOD_SOUND_FORMAT_PCM24,            /* 24bit integer PCM data. */
    FMOD_SOUND_FORMAT_PCM32,            /* 32bit integer PCM data. */
    FMOD_SOUND_FORMAT_PCMFLOAT,         /* 32bit floating point PCM data. */
    FMOD_SOUND_FORMAT_GCADPCM,          /* Compressed Nintendo 3DS/Wii DSP data. */
    FMOD_SOUND_FORMAT_IMAADPCM,         /* Compressed IMA ADPCM data. */
    FMOD_SOUND_FORMAT_VAG,              /* Compressed PlayStation Portable ADPCM data. */
    FMOD_SOUND_FORMAT_HEVAG,            /* Compressed PSVita ADPCM data. */
    FMOD_SOUND_FORMAT_XMA,              /* Compressed Xbox360 XMA data. */
    FMOD_SOUND_FORMAT_MPEG,             /* Compressed MPEG layer 2 or 3 data. */
    FMOD_SOUND_FORMAT_CELT,             /* Compressed CELT data. */
    FMOD_SOUND_FORMAT_AT9,              /* Compressed PSVita ATRAC9 data. */
    FMOD_SOUND_FORMAT_XWMA,             /* Compressed Xbox360 xWMA data. */

    FMOD_SOUND_FORMAT_MAX,              /* Maximum number of sound formats supported. */   
    FMOD_SOUND_FORMAT_FORCEINT = 65536  /* Makes sure this enum is signed 32bit. */
} FMOD_SOUND_FORMAT;


/*
[DEFINE]
[
    [NAME] 
    FMOD_MODE

    [DESCRIPTION]   
    Sound description bitfields, bitwise OR them together for loading and describing sounds.

    [REMARKS]
    By default a sound will open as a static sound that is decompressed fully into memory to PCM. (ie equivalent of FMOD_CREATESAMPLE)<br>
    To have a sound stream instead, use FMOD_CREATESTREAM, or use the wrapper function System::createStream.<br>
    Some opening modes (ie FMOD_OPENUSER, FMOD_OPENMEMORY, FMOD_OPENMEMORY_POINT, FMOD_OPENRAW) will need extra information.<br>
    This can be provided using the FMOD_CREATESOUNDEXINFO structure.
    <br>
    Specifying FMOD_OPENMEMORY_POINT will POINT to your memory rather allocating its own sound buffers and duplicating it internally.<br>
    <b><u>This means you cannot free the memory while FMOD is using it, until after Sound::release is called.</b></u>
    With FMOD_OPENMEMORY_POINT, for PCM formats, only WAV, FSB, and RAW are supported.  For compressed formats, only those formats supported by FMOD_CREATECOMPRESSEDSAMPLE are supported.<br>
    With FMOD_OPENMEMORY_POINT and FMOD_OPENRAW or PCM, if using them together, note that you must pad the data on each side by 16 bytes.  This is so fmod can modify the ends of the data for looping/interpolation/mixing purposes.  If a wav file, you will need to insert silence, and then reset loop points to stop the playback from playing that silence.<br>
    With FMOD_OPENMEMORY_POINT, For Wii/PSP FMOD_HARDWARE supports this flag for the GCADPCM/VAG formats.  On other platforms FMOD_SOFTWARE must be used.<br>
    <br>
    <b>Xbox 360 memory</b> On Xbox 360 Specifying FMOD_OPENMEMORY_POINT to a virtual memory address will cause FMOD_ERR_INVALID_ADDRESS
    to be returned.  Use physical memory only for this functionality.<br>
    <br>
    FMOD_LOWMEM is used on a sound if you want to minimize the memory overhead, by having FMOD not allocate memory for certain 
    features that are not likely to be used in a game environment.  These are :<br>
    1. Sound::getName functionality is removed.  256 bytes per sound is saved.<br>

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    System::createSound
    System::createStream
    Sound::setMode
    Sound::getMode
    Channel::setMode
    Channel::getMode
    Sound::set3DCustomRolloff
    Channel::set3DCustomRolloff
    Sound::getOpenState
]
*/
#define FMOD_DEFAULT                   0x00000000  /* FMOD_DEFAULT is a default sound type.  Equivalent to all the defaults listed below.  FMOD_LOOP_OFF, FMOD_2D, FMOD_HARDWARE.  (Note - only Windows with a high spec soundcard, PSP, and Wii support FMOD_HARDWARE) */
#define FMOD_LOOP_OFF                  0x00000001  /* For non looping sounds. (DEFAULT).  Overrides FMOD_LOOP_NORMAL / FMOD_LOOP_BIDI. */
#define FMOD_LOOP_NORMAL               0x00000002  /* For forward looping sounds. */
#define FMOD_LOOP_BIDI                 0x00000004  /* For bidirectional looping sounds. (only works on software mixed static sounds). */
#define FMOD_2D                        0x00000008  /* Ignores any 3d processing. (DEFAULT). */
#define FMOD_3D                        0x00000010  /* Makes the sound positionable in 3D.  Overrides FMOD_2D. */
#define FMOD_HARDWARE                  0x00000020  /* Attempts to make sounds use hardware acceleration. (DEFAULT).  Note on platforms that don't support FMOD_HARDWARE (only Windows with a high spec soundcard, PSP, and Wii support FMOD_HARDWARE), this will be internally treated as FMOD_SOFTWARE. */
#define FMOD_SOFTWARE                  0x00000040  /* Makes the sound be mixed by the FMOD CPU based software mixer.  Overrides FMOD_HARDWARE.  Use this for FFT, DSP, compressed sample support, 2D multi-speaker support and other software related features. */
#define FMOD_CREATESTREAM              0x00000080  /* Decompress at runtime, streaming from the source provided (ie from disk).  Overrides FMOD_CREATESAMPLE and FMOD_CREATECOMPRESSEDSAMPLE.  Note a stream can only be played once at a time due to a stream only having 1 stream buffer and file handle.  Open multiple streams to have them play concurrently. */
#define FMOD_CREATESAMPLE              0x00000100  /* Decompress at loadtime, decompressing or decoding whole file into memory as the target sample format (ie PCM).  Fastest for FMOD_SOFTWARE based playback and most flexible.  */
#define FMOD_CREATECOMPRESSEDSAMPLE    0x00000200  /* Load MP2, MP3, IMAADPCM or XMA into memory and leave it compressed.  During playback the FMOD software mixer will decode it in realtime as a 'compressed sample'.  Can only be used in combination with FMOD_SOFTWARE.  Overrides FMOD_CREATESAMPLE.  If the sound data is not ADPCM, MPEG or XMA it will behave as if it was created with FMOD_CREATESAMPLE and decode the sound into PCM. */
#define FMOD_OPENUSER                  0x00000400  /* Opens a user created static sample or stream. Use FMOD_CREATESOUNDEXINFO to specify format and/or read callbacks.  If a user created 'sample' is created with no read callback, the sample will be empty.  Use Sound::lock and Sound::unlock to place sound data into the sound if this is the case. */
#define FMOD_OPENMEMORY                0x00000800  /* "name_or_data" will be interpreted as a pointer to memory instead of filename for creating sounds.  Use FMOD_CREATESOUNDEXINFO to specify length.  If used with FMOD_CREATESAMPLE or FMOD_CREATECOMPRESSEDSAMPLE, FMOD duplicates the memory into its own buffers.  Your own buffer can be freed after open.  If used with FMOD_CREATESTREAM, FMOD will stream out of the buffer whose pointer you passed in.  In this case, your own buffer should not be freed until you have finished with and released the stream.*/
#define FMOD_OPENMEMORY_POINT          0x10000000  /* "name_or_data" will be interpreted as a pointer to memory instead of filename for creating sounds.  Use FMOD_CREATESOUNDEXINFO to specify length.  This differs to FMOD_OPENMEMORY in that it uses the memory as is, without duplicating the memory into its own buffers.  For Wii/PSP FMOD_HARDWARE supports this flag for the GCADPCM/VAG formats.  On other platforms FMOD_SOFTWARE must be used, as sound hardware on the other platforms (ie PC) cannot access main ram.  Cannot be freed after open, only after Sound::release.   Will not work if the data is compressed and FMOD_CREATECOMPRESSEDSAMPLE is not used. */
#define FMOD_OPENRAW                   0x00001000  /* Will ignore file format and treat as raw pcm.  Use FMOD_CREATESOUNDEXINFO to specify format.  Requires at least defaultfrequency, numchannels and format to be specified before it will open.  Must be little endian data. */
#define FMOD_OPENONLY                  0x00002000  /* Just open the file, dont prebuffer or read.  Good for fast opens for info, or when sound::readData is to be used. */
#define FMOD_ACCURATETIME              0x00004000  /* For System::createSound - for accurate Sound::getLength/Channel::setPosition on VBR MP3, and MOD/S3M/XM/IT/MIDI files.  Scans file first, so takes longer to open. FMOD_OPENONLY does not affect this. */
#define FMOD_MPEGSEARCH                0x00008000  /* For corrupted / bad MP3 files.  This will search all the way through the file until it hits a valid MPEG header.  Normally only searches for 4k. */
#define FMOD_NONBLOCKING               0x00010000  /* For opening sounds and getting streamed subsounds (seeking) asyncronously.  Use Sound::getOpenState to poll the state of the sound as it opens or retrieves the subsound in the background. */
#define FMOD_UNIQUE                    0x00020000  /* Unique sound, can only be played one at a time */
#define FMOD_3D_HEADRELATIVE           0x00040000  /* Make the sound's position, velocity and orientation relative to the listener. */
#define FMOD_3D_WORLDRELATIVE          0x00080000  /* Make the sound's position, velocity and orientation absolute (relative to the world). (DEFAULT) */
#define FMOD_3D_INVERSEROLLOFF         0x00100000  /* This sound will follow the inverse rolloff model where mindistance = full volume, maxdistance = where sound stops attenuating, and rolloff is fixed according to the global rolloff factor.  (DEFAULT) */
#define FMOD_3D_LINEARROLLOFF          0x00200000  /* This sound will follow a linear rolloff model where mindistance = full volume, maxdistance = silence.  Rolloffscale is ignored. */
#define FMOD_3D_LINEARSQUAREROLLOFF    0x00400000  /* This sound will follow a linear-square rolloff model where mindistance = full volume, maxdistance = silence.  Rolloffscale is ignored. */
#define FMOD_3D_CUSTOMROLLOFF          0x04000000  /* This sound will follow a rolloff model defined by Sound::set3DCustomRolloff / Channel::set3DCustomRolloff.  */
#define FMOD_3D_IGNOREGEOMETRY         0x40000000  /* Is not affect by geometry occlusion.  If not specified in Sound::setMode, or Channel::setMode, the flag is cleared and it is affected by geometry again. */
#define FMOD_UNICODE                   0x01000000  /* Filename is double-byte unicode. */
#define FMOD_IGNORETAGS                0x02000000  /* Skips id3v2/asf/etc tag checks when opening a sound, to reduce seek/read overhead when opening files (helps with CD performance). */
#define FMOD_LOWMEM                    0x08000000  /* Removes some features from samples to give a lower memory overhead, like Sound::getName.  See remarks. */
#define FMOD_LOADSECONDARYRAM          0x20000000  /* Load sound into the secondary RAM of supported platform. On PS3, sounds will be loaded into RSX/VRAM. */
#define FMOD_VIRTUAL_PLAYFROMSTART     0x80000000  /* For sounds that start virtual (due to being quiet or low importance), instead of swapping back to audible, and playing at the correct offset according to time, this flag makes the sound play from the start. */

/* [DEFINE_END] */


/*
[ENUM]
[
    [DESCRIPTION]   
    These values describe what state a sound is in after FMOD_NONBLOCKING has been used to open it.

    [REMARKS]
    With streams, if you are using FMOD_NONBLOCKING, note that if the user calls Sound::getSubSound, a stream will go into FMOD_OPENSTATE_SEEKING state and sound related commands will return FMOD_ERR_NOTREADY.<br>
    With streams, if you are using FMOD_NONBLOCKING, note that if the user calls Channel::getPosition, a stream will go into FMOD_OPENSTATE_SETPOSITION state and sound related commands will return FMOD_ERR_NOTREADY.<br>

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    Sound::getOpenState
    FMOD_MODE
]
*/
typedef enum
{
    FMOD_OPENSTATE_READY = 0,       /* Opened and ready to play. */
    FMOD_OPENSTATE_LOADING,         /* Initial load in progress. */
    FMOD_OPENSTATE_ERROR,           /* Failed to open - file not found, out of memory etc.  See return value of Sound::getOpenState for what happened. */
    FMOD_OPENSTATE_CONNECTING,      /* Connecting to remote host (internet sounds only). */
    FMOD_OPENSTATE_BUFFERING,       /* Buffering data. */
    FMOD_OPENSTATE_SEEKING,         /* Seeking to subsound and re-flushing stream buffer. */
    FMOD_OPENSTATE_PLAYING,         /* Ready and playing, but not possible to release at this time without stalling the main thread. */
    FMOD_OPENSTATE_SETPOSITION,     /* Seeking within a stream to a different position. */

    FMOD_OPENSTATE_MAX,             /* Maximum number of open state types. */
    FMOD_OPENSTATE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_OPENSTATE;


/*
[ENUM]
[
    [DESCRIPTION]   
    These flags are used with SoundGroup::setMaxAudibleBehavior to determine what happens when more sounds 
    are played than are specified with SoundGroup::setMaxAudible.

    [REMARKS]
    When using FMOD_SOUNDGROUP_BEHAVIOR_MUTE, SoundGroup::setMuteFadeSpeed can be used to stop a sudden transition.  
    Instead, the time specified will be used to cross fade between the sounds that go silent and the ones that become audible.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    SoundGroup::setMaxAudibleBehavior
    SoundGroup::getMaxAudibleBehavior
    SoundGroup::setMaxAudible
    SoundGroup::getMaxAudible
    SoundGroup::setMuteFadeSpeed
    SoundGroup::getMuteFadeSpeed
]
*/
typedef enum 
{
    FMOD_SOUNDGROUP_BEHAVIOR_FAIL,              /* Any sound played that puts the sound count over the SoundGroup::setMaxAudible setting, will simply fail during System::playSound. */
    FMOD_SOUNDGROUP_BEHAVIOR_MUTE,              /* Any sound played that puts the sound count over the SoundGroup::setMaxAudible setting, will be silent, then if another sound in the group stops the sound that was silent before becomes audible again. */
    FMOD_SOUNDGROUP_BEHAVIOR_STEALLOWEST,       /* Any sound played that puts the sound count over the SoundGroup::setMaxAudible setting, will steal the quietest / least important sound playing in the group. */

    FMOD_SOUNDGROUP_BEHAVIOR_MAX,               /* Maximum number of open state types. */
    FMOD_SOUNDGROUP_BEHAVIOR_FORCEINT = 65536   /* Makes sure this enum is signed 32bit. */
} FMOD_SOUNDGROUP_BEHAVIOR;


/*
[ENUM]
[
    [DESCRIPTION]   
    These callback types are used with Channel::setCallback.

    [REMARKS]
    Each callback has commanddata parameters passed as int unique to the type of callback.<br>
    See reference to FMOD_CHANNEL_CALLBACK to determine what they might mean for each type of callback.<br>
    <br>
    <b>Note!</b>  Currently the user must call System::update for these callbacks to trigger!

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    Channel::setCallback
    FMOD_CHANNEL_CALLBACK
    System::update
]
*/
typedef enum
{
    FMOD_CHANNEL_CALLBACKTYPE_END,                  /* Called when a sound ends. */
    FMOD_CHANNEL_CALLBACKTYPE_VIRTUALVOICE,         /* Called when a voice is swapped out or swapped in. */
    FMOD_CHANNEL_CALLBACKTYPE_SYNCPOINT,            /* Called when a syncpoint is encountered.  Can be from wav file markers. */
    FMOD_CHANNEL_CALLBACKTYPE_OCCLUSION,            /* Called when the channel has its geometry occlusion value calculated.  Can be used to clamp or change the value. */

    FMOD_CHANNEL_CALLBACKTYPE_MAX,                  /* Maximum number of callback types supported. */
    FMOD_CHANNEL_CALLBACKTYPE_FORCEINT = 65536      /* Makes sure this enum is signed 32bit. */
} FMOD_CHANNEL_CALLBACKTYPE;


/*
[ENUM]
[
    [DESCRIPTION]   
    These callback types are used with System::setCallback.

    [REMARKS]
    Each callback has commanddata parameters passed as void* unique to the type of callback.<br>
    See reference to FMOD_SYSTEM_CALLBACK to determine what they might mean for each type of callback.<br>
    <br>
    <b>Note!</b> Using FMOD_SYSTEM_CALLBACKTYPE_DEVICELISTCHANGED (on Mac only) requires the application to be running an event loop which will allow external changes to device list to be detected by FMOD.
    <br>
    <b>Note!</b> The 'system' object pointer will be null for FMOD_SYSTEM_CALLBACKTYPE_THREADCREATED and FMOD_SYSTEM_CALLBACKTYPE_MEMORYALLOCATIONFAILED callbacks.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    System::setCallback
    FMOD_SYSTEM_CALLBACK
    System::update
    DSP::addInput
]
*/
typedef enum
{
    FMOD_SYSTEM_CALLBACKTYPE_DEVICELISTCHANGED,         /* Called from System::update when the enumerated list of devices has changed. */
    FMOD_SYSTEM_CALLBACKTYPE_DEVICELOST,                /* Called from System::update when an output device has been lost due to control panel parameter changes and FMOD cannot automatically recover. */
    FMOD_SYSTEM_CALLBACKTYPE_MEMORYALLOCATIONFAILED,    /* Called directly when a memory allocation fails somewhere in FMOD.  (NOTE - 'system' will be NULL in this callback type.)*/
    FMOD_SYSTEM_CALLBACKTYPE_THREADCREATED,             /* Called directly when a thread is created. (NOTE - 'system' will be NULL in this callback type.) */
    FMOD_SYSTEM_CALLBACKTYPE_BADDSPCONNECTION,          /* Called when a bad connection was made with DSP::addInput. Usually called from mixer thread because that is where the connections are made.  */
    FMOD_SYSTEM_CALLBACKTYPE_BADDSPLEVEL,               /* Called when too many effects were added exceeding the maximum tree depth of 128.  This is most likely caused by accidentally adding too many DSP effects. Usually called from mixer thread because that is where the connections are made.  */

    FMOD_SYSTEM_CALLBACKTYPE_MAX,                       /* Maximum number of callback types supported. */
    FMOD_SYSTEM_CALLBACKTYPE_FORCEINT = 65536           /* Makes sure this enum is signed 32bit. */
} FMOD_SYSTEM_CALLBACKTYPE;


/* 
    FMOD Callbacks
*/
typedef FMOD_RESULT (F_CALLBACK *FMOD_SYSTEM_CALLBACK)       (FMOD_SYSTEM *system, FMOD_SYSTEM_CALLBACKTYPE type, void *commanddata1, void *commanddata2);

typedef FMOD_RESULT (F_CALLBACK *FMOD_CHANNEL_CALLBACK)      (FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, void *commanddata1, void *commanddata2);

typedef FMOD_RESULT (F_CALLBACK *FMOD_SOUND_NONBLOCKCALLBACK)(FMOD_SOUND *sound, FMOD_RESULT result);
typedef FMOD_RESULT (F_CALLBACK *FMOD_SOUND_PCMREADCALLBACK)(FMOD_SOUND *sound, void *data, unsigned int datalen);
typedef FMOD_RESULT (F_CALLBACK *FMOD_SOUND_PCMSETPOSCALLBACK)(FMOD_SOUND *sound, int subsound, unsigned int position, FMOD_TIMEUNIT postype);

typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_OPENCALLBACK)     (const char *name, int unicode, unsigned int *filesize, void **handle, void **userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_CLOSECALLBACK)    (void *handle, void *userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_READCALLBACK)     (void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread, void *userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_SEEKCALLBACK)     (void *handle, unsigned int pos, void *userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_ASYNCREADCALLBACK)(FMOD_ASYNCREADINFO *info, void *userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_ASYNCCANCELCALLBACK)(void *handle, void *userdata);

typedef void *      (F_CALLBACK *FMOD_MEMORY_ALLOCCALLBACK)  (unsigned int size, FMOD_MEMORY_TYPE type, const char *sourcestr);
typedef void *      (F_CALLBACK *FMOD_MEMORY_REALLOCCALLBACK)(void *ptr, unsigned int size, FMOD_MEMORY_TYPE type, const char *sourcestr);
typedef void        (F_CALLBACK *FMOD_MEMORY_FREECALLBACK)   (void *ptr, FMOD_MEMORY_TYPE type, const char *sourcestr);

typedef float       (F_CALLBACK *FMOD_3D_ROLLOFFCALLBACK)    (FMOD_CHANNEL *channel, float distance);


/*
[ENUM]
[
    [DESCRIPTION]   
    List of windowing methods used in spectrum analysis to reduce leakage / transient signals intefering with the analysis.<br>
    This is a problem with analysis of continuous signals that only have a small portion of the signal sample (the fft window size).<br>
    Windowing the signal with a curve or triangle tapers the sides of the fft window to help alleviate this problem.

    [REMARKS]
    Cyclic signals such as a sine wave that repeat their cycle in a multiple of the window size do not need windowing.<br>
    I.e. If the sine wave repeats every 1024, 512, 256 etc samples and the FMOD fft window is 1024, then the signal would not need windowing.<br>
    Not windowing is the same as FMOD_DSP_FFT_WINDOW_RECT, which is the default.<br>
    If the cycle of the signal (ie the sine wave) is not a multiple of the window size, it will cause frequency abnormalities, so a different windowing method is needed.<br>
    <exclude>
    <br>
    FMOD_DSP_FFT_WINDOW_RECT.<br>
    <img src="..\static\rectangle.gif"></img><br>
    <br>
    FMOD_DSP_FFT_WINDOW_TRIANGLE.<br>
    <img src="..\static\triangle.gif"></img><br>
    <br>
    FMOD_DSP_FFT_WINDOW_HAMMING.<br>
    <img src="..\static\hamming.gif"></img><br>
    <br>
    FMOD_DSP_FFT_WINDOW_HANNING.<br>
    <img src="..\static\hanning.gif"></img><br>
    <br>
    FMOD_DSP_FFT_WINDOW_BLACKMAN.<br>
    <img src="..\static\blackman.gif"></img><br>
    <br>
    FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS.<br>
    <img src="..\static\blackmanharris.gif"></img>
    </exclude>
    
    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    System::getSpectrum
    Channel::getSpectrum
]
*/
typedef enum
{
    FMOD_DSP_FFT_WINDOW_RECT,            /* w[n] = 1.0                                                                                            */
    FMOD_DSP_FFT_WINDOW_TRIANGLE,        /* w[n] = TRI(2n/N)                                                                                      */
    FMOD_DSP_FFT_WINDOW_HAMMING,         /* w[n] = 0.54 - (0.46 * COS(n/N) )                                                                      */
    FMOD_DSP_FFT_WINDOW_HANNING,         /* w[n] = 0.5 *  (1.0  - COS(n/N) )                                                                      */
    FMOD_DSP_FFT_WINDOW_BLACKMAN,        /* w[n] = 0.42 - (0.5  * COS(n/N) ) + (0.08 * COS(2.0 * n/N) )                                           */
    FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS,  /* w[n] = 0.35875 - (0.48829 * COS(1.0 * n/N)) + (0.14128 * COS(2.0 * n/N)) - (0.01168 * COS(3.0 * n/N)) */
    
    FMOD_DSP_FFT_WINDOW_MAX,             /* Maximum number of FFT window types supported. */
    FMOD_DSP_FFT_WINDOW_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_DSP_FFT_WINDOW;


/*
[ENUM]
[
    [DESCRIPTION]   
    List of interpolation types that the FMOD Ex software mixer supports.  

    [REMARKS]
    The default resampler type is FMOD_DSP_RESAMPLER_LINEAR.<br>
    Use System::setSoftwareFormat to tell FMOD the resampling quality you require for FMOD_SOFTWARE based sounds.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    System::setSoftwareFormat
    System::getSoftwareFormat
]
*/
typedef enum
{
    FMOD_DSP_RESAMPLER_NOINTERP,        /* No interpolation.  High frequency aliasing hiss will be audible depending on the sample rate of the sound. */
    FMOD_DSP_RESAMPLER_LINEAR,          /* Linear interpolation (default method).  Fast and good quality, causes very slight lowpass effect on low frequency sounds. */
    FMOD_DSP_RESAMPLER_CUBIC,           /* Cubic interpolation.  Slower than linear interpolation but better quality. */
    FMOD_DSP_RESAMPLER_SPLINE,          /* 5 point spline interpolation.  Slowest resampling method but best quality. */

    FMOD_DSP_RESAMPLER_MAX,             /* Maximum number of resample methods supported. */
    FMOD_DSP_RESAMPLER_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_DSP_RESAMPLER;


/*
[ENUM]
[
    [DESCRIPTION]   
    List of tag types that could be stored within a sound.  These include id3 tags, metadata from netstreams and vorbis/asf data.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    Sound::getTag
]
*/
typedef enum
{
    FMOD_TAGTYPE_UNKNOWN = 0,
    FMOD_TAGTYPE_ID3V1,
    FMOD_TAGTYPE_ID3V2,
    FMOD_TAGTYPE_VORBISCOMMENT,
    FMOD_TAGTYPE_SHOUTCAST,
    FMOD_TAGTYPE_ICECAST,
    FMOD_TAGTYPE_ASF,
    FMOD_TAGTYPE_MIDI,
    FMOD_TAGTYPE_PLAYLIST,
    FMOD_TAGTYPE_FMOD,
    FMOD_TAGTYPE_USER,

    FMOD_TAGTYPE_MAX,               /* Maximum number of tag types supported. */
    FMOD_TAGTYPE_FORCEINT = 65536   /* Makes sure this enum is signed 32bit. */
} FMOD_TAGTYPE;


/*
[ENUM]
[
    [DESCRIPTION]   
    List of data types that can be returned by Sound::getTag

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    Sound::getTag
]
*/
typedef enum
{
    FMOD_TAGDATATYPE_BINARY = 0,
    FMOD_TAGDATATYPE_INT,
    FMOD_TAGDATATYPE_FLOAT,
    FMOD_TAGDATATYPE_STRING,
    FMOD_TAGDATATYPE_STRING_UTF16,
    FMOD_TAGDATATYPE_STRING_UTF16BE,
    FMOD_TAGDATATYPE_STRING_UTF8,
    FMOD_TAGDATATYPE_CDTOC,

    FMOD_TAGDATATYPE_MAX,               /* Maximum number of tag datatypes supported. */
    FMOD_TAGDATATYPE_FORCEINT = 65536   /* Makes sure this enum is signed 32bit. */
} FMOD_TAGDATATYPE;


/*
[ENUM]
[
    [DESCRIPTION]   
    Types of delay that can be used with Channel::setDelay / Channel::getDelay.

    [REMARKS]
    If you haven't called Channel::setDelay yet, if you call Channel::getDelay with FMOD_DELAYTYPE_DSPCLOCK_START it will return the 
    equivalent global DSP clock value to determine when a channel started, so that you can use it for other channels to sync against.<br>
    <br>
    Use System::getDSPClock to also get the current dspclock time, a base for future calls to Channel::setDelay.<br>
    <br>
    Use FMOD_64BIT_ADD or FMOD_64BIT_SUB to add a hi/lo combination together and cope with wraparound.
    <br>
    If FMOD_DELAYTYPE_END_MS is specified, the value is not treated as a 64 bit number, just the delayhi value is used and it is treated as milliseconds.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    Channel::setDelay
    Channel::getDelay
    System::getDSPClock
]
*/
typedef enum
{
    FMOD_DELAYTYPE_END_MS,              /* Delay at the end of the sound in milliseconds.  Use delayhi only.   Channel::isPlaying will remain true until this delay has passed even though the sound itself has stopped playing.*/
    FMOD_DELAYTYPE_DSPCLOCK_START,      /* Time the sound started if Channel::getDelay is used, or if Channel::setDelay is used, the sound will delay playing until this exact tick. */
    FMOD_DELAYTYPE_DSPCLOCK_END,        /* Time the sound should end. If this is non-zero, the channel will go silent at this exact tick. */
    FMOD_DELAYTYPE_DSPCLOCK_PAUSE,      /* Time the sound should pause. If this is non-zero, the channel will pause at this exact tick. */

    FMOD_DELAYTYPE_MAX,                 /* Maximum number of tag datatypes supported. */
    FMOD_DELAYTYPE_FORCEINT = 65536     /* Makes sure this enum is signed 32bit. */
} FMOD_DELAYTYPE;


#define FMOD_64BIT_ADD(_hi1, _lo1, _hi2, _lo2) _hi1 += ((_hi2) + ((((_lo1) + (_lo2)) < (_lo1)) ? 1 : 0)); (_lo1) += (_lo2);
#define FMOD_64BIT_SUB(_hi1, _lo1, _hi2, _lo2) _hi1 -= ((_hi2) + ((((_lo1) - (_lo2)) > (_lo1)) ? 1 : 0)); (_lo1) -= (_lo2);


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Structure describing a piece of tag data.

    [REMARKS]
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    Sound::getTag
    FMOD_TAGTYPE
    FMOD_TAGDATATYPE
]
*/
typedef struct FMOD_TAG
{
    FMOD_TAGTYPE      type;         /* [r] The type of this tag. */
    FMOD_TAGDATATYPE  datatype;     /* [r] The type of data that this tag contains */
    char             *name;         /* [r] The name of this tag i.e. "TITLE", "ARTIST" etc. */
    void             *data;         /* [r] Pointer to the tag data - its format is determined by the datatype member */
    unsigned int      datalen;      /* [r] Length of the data contained in this tag */
    FMOD_BOOL         updated;      /* [r] True if this tag has been updated since last being accessed with Sound::getTag */
} FMOD_TAG;


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Structure describing a CD/DVD table of contents

    [REMARKS]
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    Sound::getTag
]
*/
typedef struct FMOD_CDTOC
{
    int numtracks;                  /* [r] The number of tracks on the CD */
    int min[100];                   /* [r] The start offset of each track in minutes */
    int sec[100];                   /* [r] The start offset of each track in seconds */
    int frame[100];                 /* [r] The start offset of each track in frames */
} FMOD_CDTOC;


/*
[DEFINE]
[
    [NAME]
    FMOD_TIMEUNIT

    [DESCRIPTION]   
    List of time types that can be returned by Sound::getLength and used with Channel::setPosition or Channel::getPosition.

    [REMARKS]
    FMOD_TIMEUNIT_SENTENCE_MS, FMOD_TIMEUNIT_SENTENCE_PCM, FMOD_TIMEUNIT_SENTENCE_PCMBYTES, FMOD_TIMEUNIT_SENTENCE and FMOD_TIMEUNIT_SENTENCE_SUBSOUND are only supported by Channel functions.
    Do not combine flags except FMOD_TIMEUNIT_BUFFERED.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]      
    Sound::getLength
    Channel::setPosition
    Channel::getPosition
]
*/
#define FMOD_TIMEUNIT_MS                0x00000001  /* Milliseconds. */
#define FMOD_TIMEUNIT_PCM               0x00000002  /* PCM samples, related to milliseconds * samplerate / 1000. */
#define FMOD_TIMEUNIT_PCMBYTES          0x00000004  /* Bytes, related to PCM samples * channels * datawidth (ie 16bit = 2 bytes). */
#define FMOD_TIMEUNIT_RAWBYTES          0x00000008  /* Raw file bytes of (compressed) sound data (does not include headers).  Only used by Sound::getLength and Channel::getPosition. */
#define FMOD_TIMEUNIT_PCMFRACTION       0x00000010  /* Fractions of 1 PCM sample.  Unsigned int range 0 to 0xFFFFFFFF.  Used for sub-sample granularity for DSP purposes. */
#define FMOD_TIMEUNIT_MODORDER          0x00000100  /* MOD/S3M/XM/IT.  Order in a sequenced module format.  Use Sound::getFormat to determine the PCM format being decoded to. */
#define FMOD_TIMEUNIT_MODROW            0x00000200  /* MOD/S3M/XM/IT.  Current row in a sequenced module format.  Sound::getLength will return the number of rows in the currently playing or seeked to pattern. */
#define FMOD_TIMEUNIT_MODPATTERN        0x00000400  /* MOD/S3M/XM/IT.  Current pattern in a sequenced module format.  Sound::getLength will return the number of patterns in the song and Channel::getPosition will return the currently playing pattern. */
#define FMOD_TIMEUNIT_SENTENCE_MS       0x00010000  /* Currently playing subsound in a sentence time in milliseconds. */
#define FMOD_TIMEUNIT_SENTENCE_PCM      0x00020000  /* Currently playing subsound in a sentence time in PCM Samples, related to milliseconds * samplerate / 1000. */
#define FMOD_TIMEUNIT_SENTENCE_PCMBYTES 0x00040000  /* Currently playing subsound in a sentence time in bytes, related to PCM samples * channels * datawidth (ie 16bit = 2 bytes). */
#define FMOD_TIMEUNIT_SENTENCE          0x00080000  /* Currently playing sentence index according to the channel. */
#define FMOD_TIMEUNIT_SENTENCE_SUBSOUND 0x00100000  /* Currently playing subsound index in a sentence. */
#define FMOD_TIMEUNIT_BUFFERED          0x10000000  /* Time value as seen by buffered stream.  This is always ahead of audible time, and is only used for processing. */
/* [DEFINE_END] */


/*
[ENUM]
[
    [DESCRIPTION]
    When creating a multichannel sound, FMOD will pan them to their default speaker locations, for example a 6 channel sound will default to one channel per 5.1 output speaker.<br>
    Another example is a stereo sound.  It will default to left = front left, right = front right.<br>
    <br>
    This is for sounds that are not 'default'.  For example you might have a sound that is 6 channels but actually made up of 3 stereo pairs, that should all be located in front left, front right only.

    [REMARKS]
    For full flexibility of speaker assignments, use Channel::setSpeakerLevels.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    FMOD_CREATESOUNDEXINFO
    Channel::setSpeakerLevels
]
*/
typedef enum
{
    FMOD_SPEAKERMAPTYPE_DEFAULT,     /* This is the default, and just means FMOD decides which speakers it puts the source channels. */
    FMOD_SPEAKERMAPTYPE_ALLMONO,     /* This means the sound is made up of all mono sounds.  All voices will be panned to the front center by default in this case.  */
    FMOD_SPEAKERMAPTYPE_ALLSTEREO,   /* This means the sound is made up of all stereo sounds.  All voices will be panned to front left and front right alternating every second channel.  */
    FMOD_SPEAKERMAPTYPE_51_PROTOOLS  /* Map a 5.1 sound to use protools L C R Ls Rs LFE mapping.  Will return an error if not a 6 channel sound. */
} FMOD_SPEAKERMAPTYPE;


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Use this structure with System::createSound when more control is needed over loading.<br>
    The possible reasons to use this with System::createSound are:<br>
    <li>Loading a file from memory.
    <li>Loading a file from within another larger (possibly wad/pak) file, by giving the loader an offset and length.
    <li>To create a user created / non file based sound.
    <li>To specify a starting subsound to seek to within a multi-sample sounds (ie FSB/DLS/SF2) when created as a stream.
    <li>To specify which subsounds to load for multi-sample sounds (ie FSB/DLS/SF2) so that memory is saved and only a subset is actually loaded/read from disk.
    <li>To specify 'piggyback' read and seek callbacks for capture of sound data as fmod reads and decodes it.  Useful for ripping decoded PCM data from sounds as they are loaded / played.
    <li>To specify a MIDI DLS/SF2 sample set file to load when opening a MIDI file.
    See below on what members to fill for each of the above types of sound you want to create.

    [REMARKS]
    This structure is optional!  Specify 0 or NULL in System::createSound if you don't need it!<br>
    <br>
    <u>Loading a file from memory.</u><br>
    <li>Create the sound using the FMOD_OPENMEMORY flag.<br>
    <li>Mandatory.  Specify 'length' for the size of the memory block in bytes.
    <li>Other flags are optional.
    <br>
    <br>
    <u>Loading a file from within another larger (possibly wad/pak) file, by giving the loader an offset and length.</u><br>
    <li>Mandatory.  Specify 'fileoffset' and 'length'.
    <li>Other flags are optional.
    <br>
    <br>
    <u>To create a user created / non file based sound.</u><br>
    <li>Create the sound using the FMOD_OPENUSER flag.
    <li>Mandatory.  Specify 'defaultfrequency, 'numchannels' and 'format'.
    <li>Other flags are optional.
    <br>
    <br>
    <u>To specify a starting subsound to seek to and flush with, within a multi-sample stream (ie FSB/DLS/SF2).</u><br>
    <br>
    <li>Mandatory.  Specify 'initialsubsound'.
    <br>
    <br>
    <u>To specify which subsounds to load for multi-sample sounds (ie FSB/DLS/SF2) so that memory is saved and only a subset is actually loaded/read from disk.</u><br>
    <br>
    <li>Mandatory.  Specify 'inclusionlist' and 'inclusionlistnum'.
    <br>
    <br>
    <u>To specify 'piggyback' read and seek callbacks for capture of sound data as fmod reads and decodes it.  Useful for ripping decoded PCM data from sounds as they are loaded / played.</u><br>
    <br>
    <li>Mandatory.  Specify 'pcmreadcallback' and 'pcmseekcallback'.
    <br>
    <br>
    <u>To specify a MIDI DLS/SF2 sample set file to load when opening a MIDI file.</u><br>
    <br>
    <li>Mandatory.  Specify 'dlsname'.
    <br>
    <br>
    Setting the 'decodebuffersize' is for cpu intensive codecs that may be causing stuttering, not file intensive codecs (ie those from CD or netstreams) which are normally 
    altered with System::setStreamBufferSize.  As an example of cpu intensive codecs, an mp3 file will take more cpu to decode than a PCM wav file.<br>
    If you have a stuttering effect, then it is using more cpu than the decode buffer playback rate can keep up with.  Increasing the decode buffersize will most likely solve this problem.<br>
    <br>
    <br>
    FSB codec.  If inclusionlist and numsubsounds are used together, this will trigger a special mode where subsounds are shuffled down to save memory.  (useful for large FSB 
    files where you only want to load 1 sound).  There will be no gaps, ie no null subsounds.  As an example, if there are 10,000 subsounds and there is an inclusionlist with only 1 entry, 
    and numsubsounds = 1, then subsound 0 will be that entry, and there will only be the memory allocated for 1 subsound.  Previously there would still be 10,000 subsound pointers and other
    associated codec entries allocated along with it multiplied by 10,000.<br>
    <br>
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    System::createSound
    System::setStreamBufferSize
    FMOD_MODE
    FMOD_SOUND_FORMAT
    FMOD_SOUND_TYPE
    FMOD_SPEAKERMAPTYPE
]
*/
typedef struct FMOD_CREATESOUNDEXINFO
{
    int                            cbsize;             /* [w] Size of this structure.  This is used so the structure can be expanded in the future and still work on older versions of FMOD Ex. */
    unsigned int                   length;             /* [w] Optional. Specify 0 to ignore. Size in bytes of file to load, or sound to create (in this case only if FMOD_OPENUSER is used).  Required if loading from memory.  If 0 is specified, then it will use the size of the file (unless loading from memory then an error will be returned). */
    unsigned int                   fileoffset;         /* [w] Optional. Specify 0 to ignore. Offset from start of the file to start loading from.  This is useful for loading files from inside big data files. */
    int                            numchannels;        /* [w] Optional. Specify 0 to ignore. Number of channels in a sound mandatory if FMOD_OPENUSER or FMOD_OPENRAW is used. */
    int                            defaultfrequency;   /* [w] Optional. Specify 0 to ignore. Default frequency of sound in a sound mandatory if FMOD_OPENUSER or FMOD_OPENRAW is used.  Other formats use the frequency determined by the file format. */
    FMOD_SOUND_FORMAT              format;             /* [w] Optional. Specify 0 or FMOD_SOUND_FORMAT_NONE to ignore. Format of the sound mandatory if FMOD_OPENUSER or FMOD_OPENRAW is used.  Other formats use the format determined by the file format.   */
    unsigned int                   decodebuffersize;   /* [w] Optional. Specify 0 to ignore. For streams.  This determines the size of the double buffer (in PCM samples) that a stream uses.  Use this for user created streams if you want to determine the size of the callback buffer passed to you.  Specify 0 to use FMOD's default size which is currently equivalent to 400ms of the sound format created/loaded. */
    int                            initialsubsound;    /* [w] Optional. Specify 0 to ignore. In a multi-sample file format such as .FSB/.DLS/.SF2, specify the initial subsound to seek to, only if FMOD_CREATESTREAM is used. */
    int                            numsubsounds;       /* [w] Optional. Specify 0 to ignore or have no subsounds.  In a sound created with FMOD_OPENUSER, specify the number of subsounds that are accessable with Sound::getSubSound.  If not created with FMOD_OPENUSER, this will limit the number of subsounds loaded within a multi-subsound file.  If using FSB, then if FMOD_CREATESOUNDEXINFO::inclusionlist is used, this will shuffle subsounds down so that there are not any gaps.  It will mean that the indices of the sounds will be different. */
    int                           *inclusionlist;      /* [w] Optional. Specify 0 to ignore. In a multi-sample format such as .FSB/.DLS/.SF2 it may be desirable to specify only a subset of sounds to be loaded out of the whole file.  This is an array of subsound indices to load into memory when created. */
    int                            inclusionlistnum;   /* [w] Optional. Specify 0 to ignore. This is the number of integers contained within the inclusionlist array. */
    FMOD_SOUND_PCMREADCALLBACK     pcmreadcallback;    /* [w] Optional. Specify 0 to ignore. Callback to 'piggyback' on FMOD's read functions and accept or even write PCM data while FMOD is opening the sound.  Used for user sounds created with FMOD_OPENUSER or for capturing decoded data as FMOD reads it. */
    FMOD_SOUND_PCMSETPOSCALLBACK   pcmsetposcallback;  /* [w] Optional. Specify 0 to ignore. Callback for when the user calls a seeking function such as Channel::setTime or Channel::setPosition within a multi-sample sound, and for when it is opened.*/
    FMOD_SOUND_NONBLOCKCALLBACK    nonblockcallback;   /* [w] Optional. Specify 0 to ignore. Callback for successful completion, or error while loading a sound that used the FMOD_NONBLOCKING flag.*/
    const char                    *dlsname;            /* [w] Optional. Specify 0 to ignore. Filename for a DLS or SF2 sample set when loading a MIDI file. If not specified, on Windows it will attempt to open /windows/system32/drivers/gm.dls or /windows/system32/drivers/etc/gm.dls, on Mac it will attempt to load /System/Library/Components/CoreAudio.component/Contents/Resources/gs_instruments.dls, otherwise the MIDI will fail to open. Current DLS support is for level 1 of the specification. */
    const char                    *encryptionkey;      /* [w] Optional. Specify 0 to ignore. Key for encrypted FSB file.  Without this key an encrypted FSB file will not load. */
    int                            maxpolyphony;       /* [w] Optional. Specify 0 to ignore. For sequenced formats with dynamic channel allocation such as .MID and .IT, this specifies the maximum voice count allowed while playing.  .IT defaults to 64.  .MID defaults to 32. */
    void                          *userdata;           /* [w] Optional. Specify 0 to ignore. This is user data to be attached to the sound during creation.  Access via Sound::getUserData.  Note: This is not passed to FMOD_FILE_OPENCALLBACK, that is a different userdata that is file specific. */
    FMOD_SOUND_TYPE                suggestedsoundtype; /* [w] Optional. Specify 0 or FMOD_SOUND_TYPE_UNKNOWN to ignore.  Instead of scanning all codec types, use this to speed up loading by making it jump straight to this codec. */
    FMOD_FILE_OPENCALLBACK         useropen;           /* [w] Optional. Specify 0 to ignore. Callback for opening this file. */
    FMOD_FILE_CLOSECALLBACK        userclose;          /* [w] Optional. Specify 0 to ignore. Callback for closing this file. */
    FMOD_FILE_READCALLBACK         userread;           /* [w] Optional. Specify 0 to ignore. Callback for reading from this file. */
    FMOD_FILE_SEEKCALLBACK         userseek;           /* [w] Optional. Specify 0 to ignore. Callback for seeking within this file. */
    FMOD_FILE_ASYNCREADCALLBACK    userasyncread;      /* [w] Optional. Specify 0 to ignore. Callback for seeking within this file. */
    FMOD_FILE_ASYNCCANCELCALLBACK  userasynccancel;    /* [w] Optional. Specify 0 to ignore. Callback for seeking within this file. */
    FMOD_SPEAKERMAPTYPE            speakermap;         /* [w] Optional. Specify 0 to ignore. Use this to differ the way fmod maps multichannel sounds to speakers.  See FMOD_SPEAKERMAPTYPE for more. */
    FMOD_SOUNDGROUP               *initialsoundgroup;  /* [w] Optional. Specify 0 to ignore. Specify a sound group if required, to put sound in as it is created. */
    unsigned int                   initialseekposition;/* [w] Optional. Specify 0 to ignore. For streams. Specify an initial position to seek the stream to. */
    FMOD_TIMEUNIT                  initialseekpostype; /* [w] Optional. Specify 0 to ignore. For streams. Specify the time unit for the position set in initialseekposition. */
    int                            ignoresetfilesystem;/* [w] Optional. Specify 0 to ignore. Set to 1 to use fmod's built in file system. Ignores setFileSystem callbacks and also FMOD_CREATESOUNEXINFO file callbacks.  Useful for specific cases where you don't want to use your own file system but want to use fmod's file system (ie net streaming). */
    int                            cddaforceaspi;      /* [w] Optional. Specify 0 to ignore. For CDDA sounds only - if non-zero use ASPI instead of NTSCSI to access the specified CD/DVD device. */
    unsigned int                   audioqueuepolicy;   /* [w] Optional. Specify 0 or FMOD_AUDIOQUEUE_CODECPOLICY_DEFAULT to ignore. Policy used to determine whether hardware or software is used for decoding, see FMOD_AUDIOQUEUE_CODECPOLICY for options (iOS >= 3.0 required, otherwise only hardware is available) */ 
    unsigned int                   minmidigranularity; /* [w] Optional. Specify 0 to ignore. Allows you to set a minimum desired MIDI mixer granularity. Values smaller than 512 give greater than default accuracy at the cost of more CPU and vice versa. Specify 0 for default (512 samples). */
    int                            nonblockthreadid;   /* [w] Optional. Specify 0 to ignore. Specifies a thread index to execute non blocking load on.  Allows for up to 5 threads to be used for loading at once.  This is to avoid one load blocking another.  Maximum value = 4. */
} FMOD_CREATESOUNDEXINFO;


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Structure defining a reverb environment.<br>

    [REMARKS]
    Note the default reverb properties are the same as the FMOD_PRESET_GENERIC preset.<br>
    Note that integer values that typically range from -10,000 to 1000 are represented in 
    decibels, and are of a logarithmic scale, not linear, wheras float values are always linear.<br>
    <br>
    The numerical values listed below are the maximum, minimum and default values for each variable respectively.<br>
    <br>
    <b>SUPPORTED</b> next to each parameter means the platform the parameter can be set on.  Some platforms support all parameters and some don't.<br>
    WII   means Nintendo Wii hardware reverb (must use FMOD_HARDWARE).<br>
    PSP   means Playstation Portable hardware reverb (must use FMOD_HARDWARE).<br>
    SFX   means FMOD SFX software reverb.  This works on any platform that uses FMOD_SOFTWARE for loading sounds.<br>
    ---   means unsupported/deprecated.  Will either be removed or supported by SFX in the future.
    <br>
    Nintendo Wii Notes:<br>
    This structure supports only limited parameters, and maps them to the Wii hardware reverb as follows.<br>
    DecayTime = 'time'<br>
    ReverbDelay = 'predelay'<br>
    ModulationDepth = 'damping'<br>
    Reflections = 'coloration'<br>
    EnvDiffusion = 'crosstalk'<br>
    Room = 'mix'<br>
    <br>
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>
    Members marked with [r/w] are either read or write depending on if you are using System::setReverbProperties (w) or System::getReverbProperties (r).

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    System::setReverbProperties
    System::getReverbProperties
    FMOD_REVERB_PRESETS
    FMOD_REVERB_FLAGS
]
*/
typedef struct FMOD_REVERB_PROPERTIES
{                                   /*       MIN    MAX    DEFAULT DESCRIPTION */
    int          Instance;          /* [w]   0      3      0       Environment Instance.                                                 (SUPPORTED:SFX(4 instances) and Wii (3 instances)) */
    int          Environment;       /* [r/w] -1     25     -1      Sets all listener properties.  -1 = OFF.                              (SUPPORTED:SFX(-1 only)/PSP) */
    float        EnvDiffusion;      /* [r/w] 0.0    1.0    1.0     Environment diffusion                                                 (SUPPORTED:WII) */
    int          Room;              /* [r/w] -10000 0      -1000   Room effect level (at mid frequencies)                                (SUPPORTED:SFX/WII/PSP) */
    int          RoomHF;            /* [r/w] -10000 0      -100    Relative room effect level at high frequencies                        (SUPPORTED:SFX) */
    int          RoomLF;            /* [r/w] -10000 0      0       Relative room effect level at low frequencies                         (SUPPORTED:SFX) */
    float        DecayTime;         /* [r/w] 0.1    20.0   1.49    Reverberation decay time at mid frequencies                           (SUPPORTED:SFX/WII) */
    float        DecayHFRatio;      /* [r/w] 0.1    2.0    0.83    High-frequency to mid-frequency decay time ratio                      (SUPPORTED:SFX) */
    float        DecayLFRatio;      /* [r/w] 0.1    2.0    1.0     Low-frequency to mid-frequency decay time ratio                       (SUPPORTED:---) */
    int          Reflections;       /* [r/w] -10000 1000   -2602   Early reflections level relative to room effect                       (SUPPORTED:SFX/WII) */
    float        ReflectionsDelay;  /* [r/w] 0.0    0.3    0.007   Initial reflection delay time                                         (SUPPORTED:SFX) */
    int          Reverb;            /* [r/w] -10000 2000   200     Late reverberation level relative to room effect                      (SUPPORTED:SFX) */
    float        ReverbDelay;       /* [r/w] 0.0    0.1    0.011   Late reverberation delay time relative to initial reflection          (SUPPORTED:SFX/WII) */
    float        ModulationTime;    /* [r/w] 0.04   4.0    0.25    Modulation time                                                       (SUPPORTED:---) */
    float        ModulationDepth;   /* [r/w] 0.0    1.0    0.0     Modulation depth                                                      (SUPPORTED:WII) */
    float        HFReference;       /* [r/w] 1000.0 20000  5000.0  Reference high frequency (hz)                                         (SUPPORTED:SFX) */
    float        LFReference;       /* [r/w] 20.0   1000.0 250.0   Reference low frequency (hz)                                          (SUPPORTED:SFX) */
    float        Diffusion;         /* [r/w] 0.0    100.0  100.0   Value that controls the echo density in the late reverberation decay. (SUPPORTED:SFX) */
    float        Density;           /* [r/w] 0.0    100.0  100.0   Value that controls the modal density in the late reverberation decay (SUPPORTED:SFX) */
    unsigned int Flags;             /* [r/w] FMOD_REVERB_FLAGS - modifies the behavior of above properties                               (SUPPORTED:WII) */
} FMOD_REVERB_PROPERTIES;


/*
[DEFINE] 
[
    [NAME] 
    FMOD_REVERB_FLAGS

    [DESCRIPTION]
    Values for the Flags member of the FMOD_REVERB_PROPERTIES structure.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    FMOD_REVERB_PROPERTIES
]
*/
#define FMOD_REVERB_FLAGS_HIGHQUALITYREVERB     0x00000400 /* Wii. Use high quality reverb */
#define FMOD_REVERB_FLAGS_HIGHQUALITYDPL2REVERB 0x00000800 /* Wii. Use high quality DPL2 reverb */
#define FMOD_REVERB_FLAGS_DEFAULT               0x00000000
/* [DEFINE_END] */


/*
[DEFINE] 
[
    [NAME] 
    FMOD_REVERB_PRESETS

    [DESCRIPTION]   
    A set of predefined environment PARAMETERS.<br>
    These are used to initialize an FMOD_REVERB_PROPERTIES structure statically.<br>
    i.e.<br>
    FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_GENERIC;

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    System::setReverbProperties
]
*/
/*                                    Inst Env  Diffus  Room   RoomHF  RmLF DecTm   DecHF  DecLF   Refl  RefDel   Revb  RevDel  ModTm  ModDp   HFRef    LFRef   Diffus  Densty  FLAGS */
#define FMOD_PRESET_OFF              {  0, -1,  1.00f, -10000, -10000, 0,   1.00f,  1.00f, 1.0f,  -2602, 0.007f,   200, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f,   0.0f,   0.0f, 0x33f }
#define FMOD_PRESET_GENERIC          {  0,  0,  1.00f, -1000,  -100,   0,   1.49f,  0.83f, 1.0f,  -2602, 0.007f,   200, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_PADDEDCELL       {  0,  1,  1.00f, -1000,  -6000,  0,   0.17f,  0.10f, 1.0f,  -1204, 0.001f,   207, 0.002f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_ROOM             {  0,  2,  1.00f, -1000,  -454,   0,   0.40f,  0.83f, 1.0f,  -1646, 0.002f,    53, 0.003f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_BATHROOM         {  0,  3,  1.00f, -1000,  -1200,  0,   1.49f,  0.54f, 1.0f,   -370, 0.007f,  1030, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f,  60.0f, 0x3f }
#define FMOD_PRESET_LIVINGROOM       {  0,  4,  1.00f, -1000,  -6000,  0,   0.50f,  0.10f, 1.0f,  -1376, 0.003f, -1104, 0.004f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_STONEROOM        {  0,  5,  1.00f, -1000,  -300,   0,   2.31f,  0.64f, 1.0f,   -711, 0.012f,    83, 0.017f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_AUDITORIUM       {  0,  6,  1.00f, -1000,  -476,   0,   4.32f,  0.59f, 1.0f,   -789, 0.020f,  -289, 0.030f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_CONCERTHALL      {  0,  7,  1.00f, -1000,  -500,   0,   3.92f,  0.70f, 1.0f,  -1230, 0.020f,    -2, 0.029f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_CAVE             {  0,  8,  1.00f, -1000,  0,      0,   2.91f,  1.30f, 1.0f,   -602, 0.015f,  -302, 0.022f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x1f }
#define FMOD_PRESET_ARENA            {  0,  9,  1.00f, -1000,  -698,   0,   7.24f,  0.33f, 1.0f,  -1166, 0.020f,    16, 0.030f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_HANGAR           {  0,  10, 1.00f, -1000,  -1000,  0,   10.05f, 0.23f, 1.0f,   -602, 0.020f,   198, 0.030f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_CARPETTEDHALLWAY {  0,  11, 1.00f, -1000,  -4000,  0,   0.30f,  0.10f, 1.0f,  -1831, 0.002f, -1630, 0.030f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_HALLWAY          {  0,  12, 1.00f, -1000,  -300,   0,   1.49f,  0.59f, 1.0f,  -1219, 0.007f,   441, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_STONECORRIDOR    {  0,  13, 1.00f, -1000,  -237,   0,   2.70f,  0.79f, 1.0f,  -1214, 0.013f,   395, 0.020f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_ALLEY            {  0,  14, 0.30f, -1000,  -270,   0,   1.49f,  0.86f, 1.0f,  -1204, 0.007f,    -4, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_FOREST           {  0,  15, 0.30f, -1000,  -3300,  0,   1.49f,  0.54f, 1.0f,  -2560, 0.162f,  -229, 0.088f, 0.25f, 0.000f, 5000.0f, 250.0f,  79.0f, 100.0f, 0x3f }
#define FMOD_PRESET_CITY             {  0,  16, 0.50f, -1000,  -800,   0,   1.49f,  0.67f, 1.0f,  -2273, 0.007f, -1691, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f,  50.0f, 100.0f, 0x3f }
#define FMOD_PRESET_MOUNTAINS        {  0,  17, 0.27f, -1000,  -2500,  0,   1.49f,  0.21f, 1.0f,  -2780, 0.300f, -1434, 0.100f, 0.25f, 0.000f, 5000.0f, 250.0f,  27.0f, 100.0f, 0x1f }
#define FMOD_PRESET_QUARRY           {  0,  18, 1.00f, -1000,  -1000,  0,   1.49f,  0.83f, 1.0f, -10000, 0.061f,   500, 0.025f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_PLAIN            {  0,  19, 0.21f, -1000,  -2000,  0,   1.49f,  0.50f, 1.0f,  -2466, 0.179f, -1926, 0.100f, 0.25f, 0.000f, 5000.0f, 250.0f,  21.0f, 100.0f, 0x3f }
#define FMOD_PRESET_PARKINGLOT       {  0,  20, 1.00f, -1000,  0,      0,   1.65f,  1.50f, 1.0f,  -1363, 0.008f, -1153, 0.012f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x1f }
#define FMOD_PRESET_SEWERPIPE        {  0,  21, 0.80f, -1000,  -1000,  0,   2.81f,  0.14f, 1.0f,    429, 0.014f,  1023, 0.021f, 0.25f, 0.000f, 5000.0f, 250.0f,  80.0f,  60.0f, 0x3f }
#define FMOD_PRESET_UNDERWATER       {  0,  22, 1.00f, -1000,  -4000,  0,   1.49f,  0.10f, 1.0f,   -449, 0.007f,  1700, 0.011f, 1.18f, 0.348f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }

/* PlayStation Portable Only presets */
#define FMOD_PRESET_PSP_ROOM         {  0,  1,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
#define FMOD_PRESET_PSP_STUDIO_A     {  0,  2,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
#define FMOD_PRESET_PSP_STUDIO_B     {  0,  3,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
#define FMOD_PRESET_PSP_STUDIO_C     {  0,  4,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
#define FMOD_PRESET_PSP_HALL         {  0,  5,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
#define FMOD_PRESET_PSP_SPACE        {  0,  6,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
#define FMOD_PRESET_PSP_ECHO         {  0,  7,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
#define FMOD_PRESET_PSP_DELAY        {  0,  8,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
#define FMOD_PRESET_PSP_PIPE         {  0,  9,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
/* [DEFINE_END] */


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Structure defining the properties for a reverb source, related to a FMOD channel.<br>
    <br>
    Note the default reverb properties are the same as the FMOD_PRESET_GENERIC preset.<br>
    Note that integer values that typically range from -10,000 to 1000 are represented in 
    decibels, and are of a logarithmic scale, not linear, wheras float values are typically linear.<br>
    PORTABILITY: Each member has the platform it supports in braces ie (win32/wii).<br>
    <br>
    The numerical values listed below are the maximum, minimum and default values for each variable respectively.<br>

    [REMARKS]
    <b>SUPPORTED</b> next to each parameter means the platform the parameter can be set on.  Some platforms support all parameters and some don't.<br>
    WII   means Nintendo Wii hardware reverb (must use FMOD_HARDWARE).<br>
    PSP   means Playstation Portable hardware reverb (must use FMOD_HARDWARE).<br>
    SFX   means FMOD SFX software reverb.  This works on any platform that uses FMOD_SOFTWARE for loading sounds.<br>
    ---   means unsupported/deprecated.  Will either be removed or supported by SFX in the future.
    <br>
    <br>
    <b>'ConnectionPoint' Parameter.</b>  This parameter is for the FMOD software reverb only (known as SFX in the list above).<br>
    By default the dsp network connection for a channel and its reverb is between the 'SFX Reverb' unit, and the channel's wavetable/resampler/dspcodec/oscillator unit (the unit below the channel DSP head).  NULL can be used for this parameter to make it use this default behaviour.<br>
    This parameter allows the user to connect the SFX reverb to somewhere else internally, for example the channel DSP head, or a related channelgroup.  The event system uses this so that it can have the output of an event going to the reverb, instead of just the output of the event's channels (thereby ignoring event effects/submixes etc).<br>
    Do not use if you are unaware of DSP network connection issues.  Leave it at the default of NULL instead.<br>
    <br>
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>
    Members marked with [r/w] are either read or write depending on if you are using Channel::setReverbProperties (w) or Channel::getReverbProperties (r).

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    Channel::setReverbProperties
    Channel::getReverbProperties
    FMOD_REVERB_CHANNELFLAGS 
]
*/
typedef struct FMOD_REVERB_CHANNELPROPERTIES
{                                      /*       MIN    MAX  DEFAULT  DESCRIPTION */
    int          Direct;               /* [r/w] -10000 1000 0        Direct path level                                        (SUPPORTED:SFX) */
    int          Room;                 /* [r/w] -10000 1000 0        Room effect level                                        (SUPPORTED:SFX) */
    unsigned int Flags;                /* [r/w] FMOD_REVERB_CHANNELFLAGS - modifies the behavior of properties                (SUPPORTED:SFX) */
    FMOD_DSP    *ConnectionPoint;      /* [r/w] See remarks.         DSP network location to connect reverb for this channel. (SUPPORTED:SFX).*/
} FMOD_REVERB_CHANNELPROPERTIES;


/*
[DEFINE] 
[
    [NAME] 
    FMOD_REVERB_CHANNELFLAGS

    [DESCRIPTION]
    Values for the Flags member of the FMOD_REVERB_CHANNELPROPERTIES structure.

    [REMARKS]
    For SFX Reverb, there is support for multiple reverb environments.<br>
    Use FMOD_REVERB_CHANNELFLAGS_ENVIRONMENT0 to FMOD_REVERB_CHANNELFLAGS_ENVIRONMENT3 in the flags member 
    of FMOD_REVERB_CHANNELPROPERTIES to specify which environment instance(s) to target. <br>
    - If you do not specify any instance the first reverb instance will be used.<br>
    - If you specify more than one instance with getReverbProperties, the first instance will be used.<br>
    - If you specify more than one instance with setReverbProperties, it will set more than 1 instance at once.<br>

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    FMOD_REVERB_CHANNELPROPERTIES
]
*/
#define FMOD_REVERB_CHANNELFLAGS_INSTANCE0     0x00000010 /* SFX/Wii. Specify channel to target reverb instance 0.  Default target. */
#define FMOD_REVERB_CHANNELFLAGS_INSTANCE1     0x00000020 /* SFX/Wii. Specify channel to target reverb instance 1. */
#define FMOD_REVERB_CHANNELFLAGS_INSTANCE2     0x00000040 /* SFX/Wii. Specify channel to target reverb instance 2. */
#define FMOD_REVERB_CHANNELFLAGS_INSTANCE3     0x00000080 /* SFX. Specify channel to target reverb instance 3. */

#define FMOD_REVERB_CHANNELFLAGS_DEFAULT       FMOD_REVERB_CHANNELFLAGS_INSTANCE0
/* [DEFINE_END] */


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Settings for advanced features like configuring memory and cpu usage for the FMOD_CREATECOMPRESSEDSAMPLE feature.

    [REMARKS]
    maxMPEGcodecs / maxADPCMcodecs / maxXMAcodecs will determine the maximum cpu usage of playing realtime samples.  Use this to lower potential excess cpu usage and also control memory usage.<br>
    <br>
    maxPCMcodecs is for use with PS3 only. It will determine the maximum number of PCM voices that can be played at once. This includes streams of any format and all sounds created
    *without* the FMOD_CREATECOMPRESSEDSAMPLE flag.
    <br>
    Memory will be allocated for codecs 'up front' (during System::init) if these values are specified as non zero.  If any are zero, it allocates memory for the codec whenever a file of the type in question is loaded.  So if maxMPEGcodecs is 0 for example, it will allocate memory for the mpeg codecs the first time an mp3 is loaded or an mp3 based .FSB file is loaded.<br>
    <br>
    Due to inefficient encoding techniques on certain .wav based ADPCM files, FMOD can can need an extra 29720 bytes per codec.  This means for lowest memory consumption.  Use FSB as it uses an optimal/small ADPCM block size.<br>
    <br>
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>
    Members marked with [r/w] are either read or write depending on if you are using System::setAdvancedSettings (w) or System::getAdvancedSettings (r).

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    System::setAdvancedSettings
    System::getAdvancedSettings
    System::init
    FMOD_MODE
]
*/
typedef struct FMOD_ADVANCEDSETTINGS
{                       
    int             cbsize;                     /* [w]   Size of this structure.  Use sizeof(FMOD_ADVANCEDSETTINGS)  NOTE: This must be set before calling System::getAdvancedSettings! */
    int             maxMPEGcodecs;              /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_CREATECOMPRESSEDSAMPLE only.  Mpeg  codecs consume 21,684 bytes per instance and this number will determine how many mpeg channels can be played simultaneously.   Default = 32. */
    int             maxADPCMcodecs;             /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_CREATECOMPRESSEDSAMPLE only.  ADPCM codecs consume  2,136 bytes per instance and this number will determine how many ADPCM channels can be played simultaneously.  Default = 32. */
    int             maxXMAcodecs;               /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_CREATECOMPRESSEDSAMPLE only.  XMA   codecs consume 14,836 bytes per instance and this number will determine how many XMA channels can be played simultaneously.    Default = 32. */
    int             maxCELTcodecs;              /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_CREATECOMPRESSEDSAMPLE only.  CELT  codecs consume 11,500 bytes per instance and this number will determine how many CELT channels can be played simultaneously.   Default = 32. */    
    int             maxPCMcodecs;               /* [r/w] Optional. Specify 0 to ignore. For use with PS3 only.                          PCM   codecs consume 12,672 bytes per instance and this number will determine how many streams and PCM voices can be played simultaneously. Default = 16. */
    int             ASIONumChannels;            /* [r/w] Optional. Specify 0 to ignore. Number of channels available on the ASIO device. */
    char          **ASIOChannelList;            /* [r/w] Optional. Specify 0 to ignore. Pointer to an array of strings (number of entries defined by ASIONumChannels) with ASIO channel names. */
    FMOD_SPEAKER   *ASIOSpeakerList;            /* [r/w] Optional. Specify 0 to ignore. Pointer to a list of speakers that the ASIO channels map to.  This can be called after System::init to remap ASIO output. */
    int             max3DReverbDSPs;            /* [r/w] Optional. Specify 0 to ignore. The max number of 3d reverb DSP's in the system. (NOTE: CURRENTLY DISABLED / UNUSED) */
    float           HRTFMinAngle;               /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_INIT_HRTF_LOWPASS.  The angle range (0-360) of a 3D sound in relation to the listener, at which the HRTF function begins to have an effect. 0 = in front of the listener. 180 = from 90 degrees to the left of the listener to 90 degrees to the right. 360 = behind the listener. Default = 180.0. */
    float           HRTFMaxAngle;               /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_INIT_HRTF_LOWPASS.  The angle range (0-360) of a 3D sound in relation to the listener, at which the HRTF function has maximum effect. 0 = front of the listener. 180 = from 90 degrees to the left of the listener to 90 degrees to the right. 360 = behind the listener. Default = 360.0. */
    float           HRTFFreq;                   /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_INIT_HRTF_LOWPASS.  The cutoff frequency of the HRTF's lowpass filter function when at maximum effect. (i.e. at HRTFMaxAngle).  Default = 4000.0. */
    float           vol0virtualvol;             /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_INIT_VOL0_BECOMES_VIRTUAL.  If this flag is used, and the volume is 0.0, then the sound will become virtual.  Use this value to raise the threshold to a different point where a sound goes virtual. */
    int             eventqueuesize;             /* [r/w] Optional. Specify 0 to ignore. For use with FMOD Event system only.  Specifies the number of slots available for simultaneous non blocking loads, across all threads.  Default = 32. */
    unsigned int    defaultDecodeBufferSize;    /* [r/w] Optional. Specify 0 to ignore. For streams. This determines the default size of the double buffer (in milliseconds) that a stream uses.  Default = 400ms */
    char           *debugLogFilename;           /* [r/w] Optional. Specify 0 to ignore. Gives fmod's logging system a path/filename.  Normally the log is placed in the same directory as the executable and called fmod.log. When using System::getAdvancedSettings, provide at least 256 bytes of memory to copy into. */
    unsigned short  profileport;                /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_INIT_ENABLE_PROFILE.  Specify the port to listen on for connections by the profiler application. */
    unsigned int    geometryMaxFadeTime;        /* [r/w] Optional. Specify 0 to ignore. The maximum time in miliseconds it takes for a channel to fade to the new level when its occlusion changes. */
    unsigned int    maxSpectrumWaveDataBuffers; /* [r/w] Optional. Specify 0 to ignore. Tells System::init to allocate a pool of wavedata/spectrum buffers to prevent memory fragmentation, any additional buffers will be allocated normally. */
    unsigned int    musicSystemCacheDelay;      /* [r/w] Optional. Specify 0 to ignore. The delay the music system should allow for loading a sample from disk (in milliseconds). Default = 400 ms. */
    float           distanceFilterCenterFreq;   /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_INIT_DISTANCE_FILTERING.  The default center frequency in Hz for the distance filtering effect. Default = 1500.0. */
} FMOD_ADVANCEDSETTINGS;


/*
[ENUM]
[
    [DESCRIPTION]
    Special channel index values for FMOD functions.

    [REMARKS]
    To get 'all' of the channels, use System::getMasterChannelGroup.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox360, PlayStation Portable, PlayStation 3, Wii, iPhone, 3GS, NGP, Android

    [SEE_ALSO]
    System::playSound
    System::playDSP
    System::getChannel
    System::getMasterChannelGroup
]
*/
typedef enum
{
    FMOD_CHANNEL_FREE  = -1,      /* For a channel index, FMOD chooses a free voice using the priority system. */
    FMOD_CHANNEL_REUSE = -2       /* For a channel index, re-use the channel handle that was passed in. */
} FMOD_CHANNELINDEX;

#include "fmod_codec.h"
#include "fmod_dsp.h"
#include "fmod_memoryinfo.h"

/* ========================================================================================== */
/* FUNCTION PROTOTYPES                                                                        */
/* ========================================================================================== */

#ifdef __cplusplus
extern "C" 
{
#endif

/*
    FMOD global system functions (optional).
*/

FMOD_RESULT F_API FMOD_Memory_Initialize           (void *poolmem, int poollen, FMOD_MEMORY_ALLOCCALLBACK useralloc, FMOD_MEMORY_REALLOCCALLBACK userrealloc, FMOD_MEMORY_FREECALLBACK userfree, FMOD_MEMORY_TYPE memtypeflags);
FMOD_RESULT F_API FMOD_Memory_GetStats             (int *currentalloced, int *maxalloced, FMOD_BOOL blocking);
FMOD_RESULT F_API FMOD_Debug_SetLevel              (FMOD_DEBUGLEVEL level);
FMOD_RESULT F_API FMOD_Debug_GetLevel              (FMOD_DEBUGLEVEL *level);
FMOD_RESULT F_API FMOD_File_SetDiskBusy            (int busy);
FMOD_RESULT F_API FMOD_File_GetDiskBusy            (int *busy);

/*
    FMOD System factory functions.  Use this to create an FMOD System Instance.  below you will see FMOD_System_Init/Close to get started.
*/

FMOD_RESULT F_API FMOD_System_Create               (FMOD_SYSTEM **system); 
FMOD_RESULT F_API FMOD_System_Release              (FMOD_SYSTEM *system); 

/*$ preserve end $*/

/*
    'System' API
*/

/*
     Pre-init functions.
*/

FMOD_RESULT F_API FMOD_System_SetOutput              (FMOD_SYSTEM *system, FMOD_OUTPUTTYPE output);
FMOD_RESULT F_API FMOD_System_GetOutput              (FMOD_SYSTEM *system, FMOD_OUTPUTTYPE *output);
FMOD_RESULT F_API FMOD_System_GetNumDrivers          (FMOD_SYSTEM *system, int *numdrivers);
FMOD_RESULT F_API FMOD_System_GetDriverInfo          (FMOD_SYSTEM *system, int id, char *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT F_API FMOD_System_GetDriverInfoW         (FMOD_SYSTEM *system, int id, short *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT F_API FMOD_System_GetDriverCaps          (FMOD_SYSTEM *system, int id, FMOD_CAPS *caps, int *controlpaneloutputrate, FMOD_SPEAKERMODE *controlpanelspeakermode);
FMOD_RESULT F_API FMOD_System_SetDriver              (FMOD_SYSTEM *system, int driver);
FMOD_RESULT F_API FMOD_System_GetDriver              (FMOD_SYSTEM *system, int *driver);
FMOD_RESULT F_API FMOD_System_SetHardwareChannels    (FMOD_SYSTEM *system, int numhardwarechannels);
FMOD_RESULT F_API FMOD_System_SetSoftwareChannels    (FMOD_SYSTEM *system, int numsoftwarechannels);
FMOD_RESULT F_API FMOD_System_GetSoftwareChannels    (FMOD_SYSTEM *system, int *numsoftwarechannels);
FMOD_RESULT F_API FMOD_System_SetSoftwareFormat      (FMOD_SYSTEM *system, int samplerate, FMOD_SOUND_FORMAT format, int numoutputchannels, int maxinputchannels, FMOD_DSP_RESAMPLER resamplemethod);
FMOD_RESULT F_API FMOD_System_GetSoftwareFormat      (FMOD_SYSTEM *system, int *samplerate, FMOD_SOUND_FORMAT *format, int *numoutputchannels, int *maxinputchannels, FMOD_DSP_RESAMPLER *resamplemethod, int *bits);
FMOD_RESULT F_API FMOD_System_SetDSPBufferSize       (FMOD_SYSTEM *system, unsigned int bufferlength, int numbuffers);
FMOD_RESULT F_API FMOD_System_GetDSPBufferSize       (FMOD_SYSTEM *system, unsigned int *bufferlength, int *numbuffers);
FMOD_RESULT F_API FMOD_System_SetFileSystem          (FMOD_SYSTEM *system, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek, FMOD_FILE_ASYNCREADCALLBACK userasyncread, FMOD_FILE_ASYNCCANCELCALLBACK userasynccancel, int blockalign);
FMOD_RESULT F_API FMOD_System_AttachFileSystem       (FMOD_SYSTEM *system, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek);
FMOD_RESULT F_API FMOD_System_SetAdvancedSettings    (FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings);
FMOD_RESULT F_API FMOD_System_GetAdvancedSettings    (FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings);
FMOD_RESULT F_API FMOD_System_SetSpeakerMode         (FMOD_SYSTEM *system, FMOD_SPEAKERMODE speakermode);
FMOD_RESULT F_API FMOD_System_GetSpeakerMode         (FMOD_SYSTEM *system, FMOD_SPEAKERMODE *speakermode);
FMOD_RESULT F_API FMOD_System_SetCallback            (FMOD_SYSTEM *system, FMOD_SYSTEM_CALLBACK callback);

/*
     Plug-in support                       
*/

FMOD_RESULT F_API FMOD_System_SetPluginPath          (FMOD_SYSTEM *system, const char *path);
FMOD_RESULT F_API FMOD_System_LoadPlugin             (FMOD_SYSTEM *system, const char *filename, unsigned int *handle, unsigned int priority);
FMOD_RESULT F_API FMOD_System_UnloadPlugin           (FMOD_SYSTEM *system, unsigned int handle);
FMOD_RESULT F_API FMOD_System_GetNumPlugins          (FMOD_SYSTEM *system, FMOD_PLUGINTYPE plugintype, int *numplugins);
FMOD_RESULT F_API FMOD_System_GetPluginHandle        (FMOD_SYSTEM *system, FMOD_PLUGINTYPE plugintype, int index, unsigned int *handle);
FMOD_RESULT F_API FMOD_System_GetPluginInfo          (FMOD_SYSTEM *system, unsigned int handle, FMOD_PLUGINTYPE *plugintype, char *name, int namelen, unsigned int *version);
FMOD_RESULT F_API FMOD_System_SetOutputByPlugin      (FMOD_SYSTEM *system, unsigned int handle);
FMOD_RESULT F_API FMOD_System_GetOutputByPlugin      (FMOD_SYSTEM *system, unsigned int *handle);
FMOD_RESULT F_API FMOD_System_CreateDSPByPlugin      (FMOD_SYSTEM *system, unsigned int handle, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_System_CreateCodec            (FMOD_SYSTEM *system, FMOD_CODEC_DESCRIPTION *description, unsigned int priority);

/*
     Init/Close                            
*/

FMOD_RESULT F_API FMOD_System_Init                   (FMOD_SYSTEM *system, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);
FMOD_RESULT F_API FMOD_System_Close                  (FMOD_SYSTEM *system);

/*
     General post-init system functions    
*/

FMOD_RESULT F_API FMOD_System_Update                 (FMOD_SYSTEM *system);

FMOD_RESULT F_API FMOD_System_Set3DSettings          (FMOD_SYSTEM *system, float dopplerscale, float distancefactor, float rolloffscale);
FMOD_RESULT F_API FMOD_System_Get3DSettings          (FMOD_SYSTEM *system, float *dopplerscale, float *distancefactor, float *rolloffscale);
FMOD_RESULT F_API FMOD_System_Set3DNumListeners      (FMOD_SYSTEM *system, int numlisteners);
FMOD_RESULT F_API FMOD_System_Get3DNumListeners      (FMOD_SYSTEM *system, int *numlisteners);
FMOD_RESULT F_API FMOD_System_Set3DListenerAttributes(FMOD_SYSTEM *system, int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_System_Get3DListenerAttributes(FMOD_SYSTEM *system, int listener, FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_System_Set3DRolloffCallback   (FMOD_SYSTEM *system, FMOD_3D_ROLLOFFCALLBACK callback);
FMOD_RESULT F_API FMOD_System_Set3DSpeakerPosition   (FMOD_SYSTEM *system, FMOD_SPEAKER speaker, float x, float y, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_System_Get3DSpeakerPosition   (FMOD_SYSTEM *system, FMOD_SPEAKER speaker, float *x, float *y, FMOD_BOOL *active);

FMOD_RESULT F_API FMOD_System_SetStreamBufferSize    (FMOD_SYSTEM *system, unsigned int filebuffersize, FMOD_TIMEUNIT filebuffersizetype);
FMOD_RESULT F_API FMOD_System_GetStreamBufferSize    (FMOD_SYSTEM *system, unsigned int *filebuffersize, FMOD_TIMEUNIT *filebuffersizetype);

/*
     System information functions.        
*/

FMOD_RESULT F_API FMOD_System_GetVersion             (FMOD_SYSTEM *system, unsigned int *version);
FMOD_RESULT F_API FMOD_System_GetOutputHandle        (FMOD_SYSTEM *system, void **handle);
FMOD_RESULT F_API FMOD_System_GetChannelsPlaying     (FMOD_SYSTEM *system, int *channels);
FMOD_RESULT F_API FMOD_System_GetHardwareChannels    (FMOD_SYSTEM *system, int *numhardwarechannels);
FMOD_RESULT F_API FMOD_System_GetCPUUsage            (FMOD_SYSTEM *system, float *dsp, float *stream, float *geometry, float *update, float *total);
FMOD_RESULT F_API FMOD_System_GetSoundRAM            (FMOD_SYSTEM *system, int *currentalloced, int *maxalloced, int *total);
FMOD_RESULT F_API FMOD_System_GetNumCDROMDrives      (FMOD_SYSTEM *system, int *numdrives);
FMOD_RESULT F_API FMOD_System_GetCDROMDriveName      (FMOD_SYSTEM *system, int drive, char *drivename, int drivenamelen, char *scsiname, int scsinamelen, char *devicename, int devicenamelen);
FMOD_RESULT F_API FMOD_System_GetSpectrum            (FMOD_SYSTEM *system, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT F_API FMOD_System_GetWaveData            (FMOD_SYSTEM *system, float *wavearray, int numvalues, int channeloffset);

/*
     Sound/DSP/Channel/FX creation and retrieval.       
*/

FMOD_RESULT F_API FMOD_System_CreateSound            (FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
FMOD_RESULT F_API FMOD_System_CreateStream           (FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
FMOD_RESULT F_API FMOD_System_CreateDSP              (FMOD_SYSTEM *system, FMOD_DSP_DESCRIPTION *description, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_System_CreateDSPByType        (FMOD_SYSTEM *system, FMOD_DSP_TYPE type, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_System_CreateChannelGroup     (FMOD_SYSTEM *system, const char *name, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT F_API FMOD_System_CreateSoundGroup       (FMOD_SYSTEM *system, const char *name, FMOD_SOUNDGROUP **soundgroup);
FMOD_RESULT F_API FMOD_System_CreateReverb           (FMOD_SYSTEM *system, FMOD_REVERB **reverb);

FMOD_RESULT F_API FMOD_System_PlaySound              (FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel);
FMOD_RESULT F_API FMOD_System_PlayDSP                (FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_DSP *dsp, FMOD_BOOL paused, FMOD_CHANNEL **channel);
FMOD_RESULT F_API FMOD_System_GetChannel             (FMOD_SYSTEM *system, int channelid, FMOD_CHANNEL **channel);
FMOD_RESULT F_API FMOD_System_GetMasterChannelGroup  (FMOD_SYSTEM *system, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT F_API FMOD_System_GetMasterSoundGroup    (FMOD_SYSTEM *system, FMOD_SOUNDGROUP **soundgroup);

/*
     Reverb API                           
*/

FMOD_RESULT F_API FMOD_System_SetReverbProperties    (FMOD_SYSTEM *system, const FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT F_API FMOD_System_GetReverbProperties    (FMOD_SYSTEM *system, FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT F_API FMOD_System_SetReverbAmbientProperties(FMOD_SYSTEM *system, FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT F_API FMOD_System_GetReverbAmbientProperties(FMOD_SYSTEM *system, FMOD_REVERB_PROPERTIES *prop);

/*
     System level DSP access.
*/

FMOD_RESULT F_API FMOD_System_GetDSPHead             (FMOD_SYSTEM *system, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_System_AddDSP                 (FMOD_SYSTEM *system, FMOD_DSP *dsp, FMOD_DSPCONNECTION **connection);
FMOD_RESULT F_API FMOD_System_LockDSP                (FMOD_SYSTEM *system);
FMOD_RESULT F_API FMOD_System_UnlockDSP              (FMOD_SYSTEM *system);
FMOD_RESULT F_API FMOD_System_GetDSPClock            (FMOD_SYSTEM *system, unsigned int *hi, unsigned int *lo);

/*
     Recording API.
*/

FMOD_RESULT F_API FMOD_System_GetRecordNumDrivers    (FMOD_SYSTEM *system, int *numdrivers);
FMOD_RESULT F_API FMOD_System_GetRecordDriverInfo    (FMOD_SYSTEM *system, int id, char *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT F_API FMOD_System_GetRecordDriverInfoW   (FMOD_SYSTEM *system, int id, short *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT F_API FMOD_System_GetRecordDriverCaps    (FMOD_SYSTEM *system, int id, FMOD_CAPS *caps, int *minfrequency, int *maxfrequency);
FMOD_RESULT F_API FMOD_System_GetRecordPosition      (FMOD_SYSTEM *system, int id, unsigned int *position);

FMOD_RESULT F_API FMOD_System_RecordStart            (FMOD_SYSTEM *system, int id, FMOD_SOUND *sound, FMOD_BOOL loop);
FMOD_RESULT F_API FMOD_System_RecordStop             (FMOD_SYSTEM *system, int id);
FMOD_RESULT F_API FMOD_System_IsRecording            (FMOD_SYSTEM *system, int id, FMOD_BOOL *recording);

/*
     Geometry API.
*/

FMOD_RESULT F_API FMOD_System_CreateGeometry         (FMOD_SYSTEM *system, int maxpolygons, int maxvertices, FMOD_GEOMETRY **geometry);
FMOD_RESULT F_API FMOD_System_SetGeometrySettings    (FMOD_SYSTEM *system, float maxworldsize);
FMOD_RESULT F_API FMOD_System_GetGeometrySettings    (FMOD_SYSTEM *system, float *maxworldsize);
FMOD_RESULT F_API FMOD_System_LoadGeometry           (FMOD_SYSTEM *system, const void *data, int datasize, FMOD_GEOMETRY **geometry);
FMOD_RESULT F_API FMOD_System_GetGeometryOcclusion   (FMOD_SYSTEM *system, const FMOD_VECTOR *listener, const FMOD_VECTOR *source, float *direct, float *reverb);

/*
     Network functions.
*/

FMOD_RESULT F_API FMOD_System_SetNetworkProxy        (FMOD_SYSTEM *system, const char *proxy);
FMOD_RESULT F_API FMOD_System_GetNetworkProxy        (FMOD_SYSTEM *system, char *proxy, int proxylen);
FMOD_RESULT F_API FMOD_System_SetNetworkTimeout      (FMOD_SYSTEM *system, int timeout);
FMOD_RESULT F_API FMOD_System_GetNetworkTimeout      (FMOD_SYSTEM *system, int *timeout);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_System_SetUserData            (FMOD_SYSTEM *system, void *userdata);
FMOD_RESULT F_API FMOD_System_GetUserData            (FMOD_SYSTEM *system, void **userdata);

FMOD_RESULT F_API FMOD_System_GetMemoryInfo          (FMOD_SYSTEM *system, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'Sound' API
*/

FMOD_RESULT F_API FMOD_Sound_Release                 (FMOD_SOUND *sound);
FMOD_RESULT F_API FMOD_Sound_GetSystemObject         (FMOD_SOUND *sound, FMOD_SYSTEM **system);

/*
     Standard sound manipulation functions.                                                
*/

FMOD_RESULT F_API FMOD_Sound_Lock                    (FMOD_SOUND *sound, unsigned int offset, unsigned int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2);
FMOD_RESULT F_API FMOD_Sound_Unlock                  (FMOD_SOUND *sound, void *ptr1, void *ptr2, unsigned int len1, unsigned int len2);
FMOD_RESULT F_API FMOD_Sound_SetDefaults             (FMOD_SOUND *sound, float frequency, float volume, float pan, int priority);
FMOD_RESULT F_API FMOD_Sound_GetDefaults             (FMOD_SOUND *sound, float *frequency, float *volume, float *pan, int *priority);
FMOD_RESULT F_API FMOD_Sound_SetVariations           (FMOD_SOUND *sound, float frequencyvar, float volumevar, float panvar);
FMOD_RESULT F_API FMOD_Sound_GetVariations           (FMOD_SOUND *sound, float *frequencyvar, float *volumevar, float *panvar);
FMOD_RESULT F_API FMOD_Sound_Set3DMinMaxDistance     (FMOD_SOUND *sound, float min, float max);
FMOD_RESULT F_API FMOD_Sound_Get3DMinMaxDistance     (FMOD_SOUND *sound, float *min, float *max);
FMOD_RESULT F_API FMOD_Sound_Set3DConeSettings       (FMOD_SOUND *sound, float insideconeangle, float outsideconeangle, float outsidevolume);
FMOD_RESULT F_API FMOD_Sound_Get3DConeSettings       (FMOD_SOUND *sound, float *insideconeangle, float *outsideconeangle, float *outsidevolume);
FMOD_RESULT F_API FMOD_Sound_Set3DCustomRolloff      (FMOD_SOUND *sound, FMOD_VECTOR *points, int numpoints);
FMOD_RESULT F_API FMOD_Sound_Get3DCustomRolloff      (FMOD_SOUND *sound, FMOD_VECTOR **points, int *numpoints);
FMOD_RESULT F_API FMOD_Sound_SetSubSound             (FMOD_SOUND *sound, int index, FMOD_SOUND *subsound);
FMOD_RESULT F_API FMOD_Sound_GetSubSound             (FMOD_SOUND *sound, int index, FMOD_SOUND **subsound);
FMOD_RESULT F_API FMOD_Sound_SetSubSoundSentence     (FMOD_SOUND *sound, int *subsoundlist, int numsubsounds);
FMOD_RESULT F_API FMOD_Sound_GetName                 (FMOD_SOUND *sound, char *name, int namelen);
FMOD_RESULT F_API FMOD_Sound_GetLength               (FMOD_SOUND *sound, unsigned int *length, FMOD_TIMEUNIT lengthtype);
FMOD_RESULT F_API FMOD_Sound_GetFormat               (FMOD_SOUND *sound, FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits);
FMOD_RESULT F_API FMOD_Sound_GetNumSubSounds         (FMOD_SOUND *sound, int *numsubsounds);
FMOD_RESULT F_API FMOD_Sound_GetNumTags              (FMOD_SOUND *sound, int *numtags, int *numtagsupdated);
FMOD_RESULT F_API FMOD_Sound_GetTag                  (FMOD_SOUND *sound, const char *name, int index, FMOD_TAG *tag);
FMOD_RESULT F_API FMOD_Sound_GetOpenState            (FMOD_SOUND *sound, FMOD_OPENSTATE *openstate, unsigned int *percentbuffered, FMOD_BOOL *starving, FMOD_BOOL *diskbusy);
FMOD_RESULT F_API FMOD_Sound_ReadData                (FMOD_SOUND *sound, void *buffer, unsigned int lenbytes, unsigned int *read);
FMOD_RESULT F_API FMOD_Sound_SeekData                (FMOD_SOUND *sound, unsigned int pcm);

FMOD_RESULT F_API FMOD_Sound_SetSoundGroup           (FMOD_SOUND *sound, FMOD_SOUNDGROUP *soundgroup);
FMOD_RESULT F_API FMOD_Sound_GetSoundGroup           (FMOD_SOUND *sound, FMOD_SOUNDGROUP **soundgroup);

/*
     Synchronization point API.  These points can come from markers embedded in wav files, and can also generate channel callbacks.        
*/

FMOD_RESULT F_API FMOD_Sound_GetNumSyncPoints        (FMOD_SOUND *sound, int *numsyncpoints);
FMOD_RESULT F_API FMOD_Sound_GetSyncPoint            (FMOD_SOUND *sound, int index, FMOD_SYNCPOINT **point);
FMOD_RESULT F_API FMOD_Sound_GetSyncPointInfo        (FMOD_SOUND *sound, FMOD_SYNCPOINT *point, char *name, int namelen, unsigned int *offset, FMOD_TIMEUNIT offsettype);
FMOD_RESULT F_API FMOD_Sound_AddSyncPoint            (FMOD_SOUND *sound, unsigned int offset, FMOD_TIMEUNIT offsettype, const char *name, FMOD_SYNCPOINT **point);
FMOD_RESULT F_API FMOD_Sound_DeleteSyncPoint         (FMOD_SOUND *sound, FMOD_SYNCPOINT *point);

/*
     Functions also in Channel class but here they are the 'default' to save having to change it in Channel all the time.
*/

FMOD_RESULT F_API FMOD_Sound_SetMode                 (FMOD_SOUND *sound, FMOD_MODE mode);
FMOD_RESULT F_API FMOD_Sound_GetMode                 (FMOD_SOUND *sound, FMOD_MODE *mode);
FMOD_RESULT F_API FMOD_Sound_SetLoopCount            (FMOD_SOUND *sound, int loopcount);
FMOD_RESULT F_API FMOD_Sound_GetLoopCount            (FMOD_SOUND *sound, int *loopcount);
FMOD_RESULT F_API FMOD_Sound_SetLoopPoints           (FMOD_SOUND *sound, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT F_API FMOD_Sound_GetLoopPoints           (FMOD_SOUND *sound, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);

/*
     For MOD/S3M/XM/IT/MID sequenced formats only.
*/

FMOD_RESULT F_API FMOD_Sound_GetMusicNumChannels     (FMOD_SOUND *sound, int *numchannels);
FMOD_RESULT F_API FMOD_Sound_SetMusicChannelVolume   (FMOD_SOUND *sound, int channel, float volume);
FMOD_RESULT F_API FMOD_Sound_GetMusicChannelVolume   (FMOD_SOUND *sound, int channel, float *volume);
FMOD_RESULT F_API FMOD_Sound_SetMusicSpeed           (FMOD_SOUND *sound, float speed);
FMOD_RESULT F_API FMOD_Sound_GetMusicSpeed           (FMOD_SOUND *sound, float *speed);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_Sound_SetUserData             (FMOD_SOUND *sound, void *userdata);
FMOD_RESULT F_API FMOD_Sound_GetUserData             (FMOD_SOUND *sound, void **userdata);

FMOD_RESULT F_API FMOD_Sound_GetMemoryInfo           (FMOD_SOUND *sound, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'Channel' API
*/

FMOD_RESULT F_API FMOD_Channel_GetSystemObject       (FMOD_CHANNEL *channel, FMOD_SYSTEM **system);

FMOD_RESULT F_API FMOD_Channel_Stop                  (FMOD_CHANNEL *channel);
FMOD_RESULT F_API FMOD_Channel_SetPaused             (FMOD_CHANNEL *channel, FMOD_BOOL paused);
FMOD_RESULT F_API FMOD_Channel_GetPaused             (FMOD_CHANNEL *channel, FMOD_BOOL *paused);
FMOD_RESULT F_API FMOD_Channel_SetVolume             (FMOD_CHANNEL *channel, float volume);
FMOD_RESULT F_API FMOD_Channel_GetVolume             (FMOD_CHANNEL *channel, float *volume);
FMOD_RESULT F_API FMOD_Channel_SetFrequency          (FMOD_CHANNEL *channel, float frequency);
FMOD_RESULT F_API FMOD_Channel_GetFrequency          (FMOD_CHANNEL *channel, float *frequency);
FMOD_RESULT F_API FMOD_Channel_SetPan                (FMOD_CHANNEL *channel, float pan);
FMOD_RESULT F_API FMOD_Channel_GetPan                (FMOD_CHANNEL *channel, float *pan);
FMOD_RESULT F_API FMOD_Channel_SetDelay              (FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int delayhi, unsigned int delaylo);
FMOD_RESULT F_API FMOD_Channel_GetDelay              (FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int *delayhi, unsigned int *delaylo);
FMOD_RESULT F_API FMOD_Channel_SetSpeakerMix         (FMOD_CHANNEL *channel, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright);
FMOD_RESULT F_API FMOD_Channel_GetSpeakerMix         (FMOD_CHANNEL *channel, float *frontleft, float *frontright, float *center, float *lfe, float *backleft, float *backright, float *sideleft, float *sideright);
FMOD_RESULT F_API FMOD_Channel_SetSpeakerLevels      (FMOD_CHANNEL *channel, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT F_API FMOD_Channel_GetSpeakerLevels      (FMOD_CHANNEL *channel, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT F_API FMOD_Channel_SetInputChannelMix    (FMOD_CHANNEL *channel, float *levels, int numlevels);
FMOD_RESULT F_API FMOD_Channel_GetInputChannelMix    (FMOD_CHANNEL *channel, float *levels, int numlevels);
FMOD_RESULT F_API FMOD_Channel_SetMute               (FMOD_CHANNEL *channel, FMOD_BOOL mute);
FMOD_RESULT F_API FMOD_Channel_GetMute               (FMOD_CHANNEL *channel, FMOD_BOOL *mute);
FMOD_RESULT F_API FMOD_Channel_SetPriority           (FMOD_CHANNEL *channel, int priority);
FMOD_RESULT F_API FMOD_Channel_GetPriority           (FMOD_CHANNEL *channel, int *priority);
FMOD_RESULT F_API FMOD_Channel_SetPosition           (FMOD_CHANNEL *channel, unsigned int position, FMOD_TIMEUNIT postype);
FMOD_RESULT F_API FMOD_Channel_GetPosition           (FMOD_CHANNEL *channel, unsigned int *position, FMOD_TIMEUNIT postype);
FMOD_RESULT F_API FMOD_Channel_SetReverbProperties   (FMOD_CHANNEL *channel, const FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT F_API FMOD_Channel_GetReverbProperties   (FMOD_CHANNEL *channel, FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT F_API FMOD_Channel_SetLowPassGain        (FMOD_CHANNEL *channel, float gain);
FMOD_RESULT F_API FMOD_Channel_GetLowPassGain        (FMOD_CHANNEL *channel, float *gain);

FMOD_RESULT F_API FMOD_Channel_SetChannelGroup       (FMOD_CHANNEL *channel, FMOD_CHANNELGROUP *channelgroup);
FMOD_RESULT F_API FMOD_Channel_GetChannelGroup       (FMOD_CHANNEL *channel, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT F_API FMOD_Channel_SetCallback           (FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACK callback);

/*
     3D functionality.
*/

FMOD_RESULT F_API FMOD_Channel_Set3DAttributes       (FMOD_CHANNEL *channel, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
FMOD_RESULT F_API FMOD_Channel_Get3DAttributes       (FMOD_CHANNEL *channel, FMOD_VECTOR *pos, FMOD_VECTOR *vel);
FMOD_RESULT F_API FMOD_Channel_Set3DMinMaxDistance   (FMOD_CHANNEL *channel, float mindistance, float maxdistance);
FMOD_RESULT F_API FMOD_Channel_Get3DMinMaxDistance   (FMOD_CHANNEL *channel, float *mindistance, float *maxdistance);
FMOD_RESULT F_API FMOD_Channel_Set3DConeSettings     (FMOD_CHANNEL *channel, float insideconeangle, float outsideconeangle, float outsidevolume);
FMOD_RESULT F_API FMOD_Channel_Get3DConeSettings     (FMOD_CHANNEL *channel, float *insideconeangle, float *outsideconeangle, float *outsidevolume);
FMOD_RESULT F_API FMOD_Channel_Set3DConeOrientation  (FMOD_CHANNEL *channel, FMOD_VECTOR *orientation);
FMOD_RESULT F_API FMOD_Channel_Get3DConeOrientation  (FMOD_CHANNEL *channel, FMOD_VECTOR *orientation);
FMOD_RESULT F_API FMOD_Channel_Set3DCustomRolloff    (FMOD_CHANNEL *channel, FMOD_VECTOR *points, int numpoints);
FMOD_RESULT F_API FMOD_Channel_Get3DCustomRolloff    (FMOD_CHANNEL *channel, FMOD_VECTOR **points, int *numpoints);
FMOD_RESULT F_API FMOD_Channel_Set3DOcclusion        (FMOD_CHANNEL *channel, float directocclusion, float reverbocclusion);
FMOD_RESULT F_API FMOD_Channel_Get3DOcclusion        (FMOD_CHANNEL *channel, float *directocclusion, float *reverbocclusion);
FMOD_RESULT F_API FMOD_Channel_Set3DSpread           (FMOD_CHANNEL *channel, float angle);
FMOD_RESULT F_API FMOD_Channel_Get3DSpread           (FMOD_CHANNEL *channel, float *angle);
FMOD_RESULT F_API FMOD_Channel_Set3DPanLevel         (FMOD_CHANNEL *channel, float level);
FMOD_RESULT F_API FMOD_Channel_Get3DPanLevel         (FMOD_CHANNEL *channel, float *level);
FMOD_RESULT F_API FMOD_Channel_Set3DDopplerLevel     (FMOD_CHANNEL *channel, float level);
FMOD_RESULT F_API FMOD_Channel_Get3DDopplerLevel     (FMOD_CHANNEL *channel, float *level);
FMOD_RESULT F_API FMOD_Channel_Set3DDistanceFilter   (FMOD_CHANNEL *channel, FMOD_BOOL custom, float customLevel, float centerFreq);
FMOD_RESULT F_API FMOD_Channel_Get3DDistanceFilter   (FMOD_CHANNEL *channel, FMOD_BOOL *custom, float *customLevel, float *centerFreq);

/*
     DSP functionality only for channels playing sounds created with FMOD_SOFTWARE.
*/

FMOD_RESULT F_API FMOD_Channel_GetDSPHead            (FMOD_CHANNEL *channel, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_Channel_AddDSP                (FMOD_CHANNEL *channel, FMOD_DSP *dsp, FMOD_DSPCONNECTION **connection);

/*
     Information only functions.
*/

FMOD_RESULT F_API FMOD_Channel_IsPlaying             (FMOD_CHANNEL *channel, FMOD_BOOL *isplaying);
FMOD_RESULT F_API FMOD_Channel_IsVirtual             (FMOD_CHANNEL *channel, FMOD_BOOL *isvirtual);
FMOD_RESULT F_API FMOD_Channel_GetAudibility         (FMOD_CHANNEL *channel, float *audibility);
FMOD_RESULT F_API FMOD_Channel_GetCurrentSound       (FMOD_CHANNEL *channel, FMOD_SOUND **sound);
FMOD_RESULT F_API FMOD_Channel_GetSpectrum           (FMOD_CHANNEL *channel, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT F_API FMOD_Channel_GetWaveData           (FMOD_CHANNEL *channel, float *wavearray, int numvalues, int channeloffset);
FMOD_RESULT F_API FMOD_Channel_GetIndex              (FMOD_CHANNEL *channel, int *index);

/*
     Functions also found in Sound class but here they can be set per channel.
*/

FMOD_RESULT F_API FMOD_Channel_SetMode               (FMOD_CHANNEL *channel, FMOD_MODE mode);
FMOD_RESULT F_API FMOD_Channel_GetMode               (FMOD_CHANNEL *channel, FMOD_MODE *mode);
FMOD_RESULT F_API FMOD_Channel_SetLoopCount          (FMOD_CHANNEL *channel, int loopcount);
FMOD_RESULT F_API FMOD_Channel_GetLoopCount          (FMOD_CHANNEL *channel, int *loopcount);
FMOD_RESULT F_API FMOD_Channel_SetLoopPoints         (FMOD_CHANNEL *channel, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT F_API FMOD_Channel_GetLoopPoints         (FMOD_CHANNEL *channel, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);

/*
     Userdata set/get.                                                
*/

FMOD_RESULT F_API FMOD_Channel_SetUserData           (FMOD_CHANNEL *channel, void *userdata);
FMOD_RESULT F_API FMOD_Channel_GetUserData           (FMOD_CHANNEL *channel, void **userdata);

FMOD_RESULT F_API FMOD_Channel_GetMemoryInfo         (FMOD_CHANNEL *channel, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'ChannelGroup' API
*/

FMOD_RESULT F_API FMOD_ChannelGroup_Release          (FMOD_CHANNELGROUP *channelgroup);
FMOD_RESULT F_API FMOD_ChannelGroup_GetSystemObject  (FMOD_CHANNELGROUP *channelgroup, FMOD_SYSTEM **system);

/*
     Channelgroup scale values.  (changes attributes relative to the channels, doesn't overwrite them)
*/

FMOD_RESULT F_API FMOD_ChannelGroup_SetVolume        (FMOD_CHANNELGROUP *channelgroup, float volume);
FMOD_RESULT F_API FMOD_ChannelGroup_GetVolume        (FMOD_CHANNELGROUP *channelgroup, float *volume);
FMOD_RESULT F_API FMOD_ChannelGroup_SetPitch         (FMOD_CHANNELGROUP *channelgroup, float pitch);
FMOD_RESULT F_API FMOD_ChannelGroup_GetPitch         (FMOD_CHANNELGROUP *channelgroup, float *pitch);
FMOD_RESULT F_API FMOD_ChannelGroup_Set3DOcclusion   (FMOD_CHANNELGROUP *channelgroup, float directocclusion, float reverbocclusion);
FMOD_RESULT F_API FMOD_ChannelGroup_Get3DOcclusion   (FMOD_CHANNELGROUP *channelgroup, float *directocclusion, float *reverbocclusion);
FMOD_RESULT F_API FMOD_ChannelGroup_SetPaused        (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL paused);
FMOD_RESULT F_API FMOD_ChannelGroup_GetPaused        (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL *paused);
FMOD_RESULT F_API FMOD_ChannelGroup_SetMute          (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL mute);
FMOD_RESULT F_API FMOD_ChannelGroup_GetMute          (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL *mute);

/*
     Channelgroup override values.  (recursively overwrites whatever settings the channels had)
*/

FMOD_RESULT F_API FMOD_ChannelGroup_Stop             (FMOD_CHANNELGROUP *channelgroup);
FMOD_RESULT F_API FMOD_ChannelGroup_OverrideVolume   (FMOD_CHANNELGROUP *channelgroup, float volume);
FMOD_RESULT F_API FMOD_ChannelGroup_OverrideFrequency(FMOD_CHANNELGROUP *channelgroup, float frequency);
FMOD_RESULT F_API FMOD_ChannelGroup_OverridePan      (FMOD_CHANNELGROUP *channelgroup, float pan);
FMOD_RESULT F_API FMOD_ChannelGroup_OverrideReverbProperties(FMOD_CHANNELGROUP *channelgroup, const FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT F_API FMOD_ChannelGroup_Override3DAttributes(FMOD_CHANNELGROUP *channelgroup, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
FMOD_RESULT F_API FMOD_ChannelGroup_OverrideSpeakerMix(FMOD_CHANNELGROUP *channelgroup, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright);

/*
     Nested channel groups.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_AddGroup         (FMOD_CHANNELGROUP *channelgroup, FMOD_CHANNELGROUP *group);
FMOD_RESULT F_API FMOD_ChannelGroup_GetNumGroups     (FMOD_CHANNELGROUP *channelgroup, int *numgroups);
FMOD_RESULT F_API FMOD_ChannelGroup_GetGroup         (FMOD_CHANNELGROUP *channelgroup, int index, FMOD_CHANNELGROUP **group);
FMOD_RESULT F_API FMOD_ChannelGroup_GetParentGroup   (FMOD_CHANNELGROUP *channelgroup, FMOD_CHANNELGROUP **group);

/*
     DSP functionality only for channel groups playing sounds created with FMOD_SOFTWARE.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_GetDSPHead       (FMOD_CHANNELGROUP *channelgroup, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_ChannelGroup_AddDSP           (FMOD_CHANNELGROUP *channelgroup, FMOD_DSP *dsp, FMOD_DSPCONNECTION **connection);

/*
     Information only functions.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_GetName          (FMOD_CHANNELGROUP *channelgroup, char *name, int namelen);
FMOD_RESULT F_API FMOD_ChannelGroup_GetNumChannels   (FMOD_CHANNELGROUP *channelgroup, int *numchannels);
FMOD_RESULT F_API FMOD_ChannelGroup_GetChannel       (FMOD_CHANNELGROUP *channelgroup, int index, FMOD_CHANNEL **channel);
FMOD_RESULT F_API FMOD_ChannelGroup_GetSpectrum      (FMOD_CHANNELGROUP *channelgroup, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT F_API FMOD_ChannelGroup_GetWaveData      (FMOD_CHANNELGROUP *channelgroup, float *wavearray, int numvalues, int channeloffset);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_SetUserData      (FMOD_CHANNELGROUP *channelgroup, void *userdata);
FMOD_RESULT F_API FMOD_ChannelGroup_GetUserData      (FMOD_CHANNELGROUP *channelgroup, void **userdata);

FMOD_RESULT F_API FMOD_ChannelGroup_GetMemoryInfo    (FMOD_CHANNELGROUP *channelgroup, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'SoundGroup' API
*/

FMOD_RESULT F_API FMOD_SoundGroup_Release            (FMOD_SOUNDGROUP *soundgroup);
FMOD_RESULT F_API FMOD_SoundGroup_GetSystemObject    (FMOD_SOUNDGROUP *soundgroup, FMOD_SYSTEM **system);

/*
     SoundGroup control functions.
*/

FMOD_RESULT F_API FMOD_SoundGroup_SetMaxAudible      (FMOD_SOUNDGROUP *soundgroup, int maxaudible);
FMOD_RESULT F_API FMOD_SoundGroup_GetMaxAudible      (FMOD_SOUNDGROUP *soundgroup, int *maxaudible);
FMOD_RESULT F_API FMOD_SoundGroup_SetMaxAudibleBehavior(FMOD_SOUNDGROUP *soundgroup, FMOD_SOUNDGROUP_BEHAVIOR behavior);
FMOD_RESULT F_API FMOD_SoundGroup_GetMaxAudibleBehavior(FMOD_SOUNDGROUP *soundgroup, FMOD_SOUNDGROUP_BEHAVIOR *behavior);
FMOD_RESULT F_API FMOD_SoundGroup_SetMuteFadeSpeed   (FMOD_SOUNDGROUP *soundgroup, float speed);
FMOD_RESULT F_API FMOD_SoundGroup_GetMuteFadeSpeed   (FMOD_SOUNDGROUP *soundgroup, float *speed);
FMOD_RESULT F_API FMOD_SoundGroup_SetVolume          (FMOD_SOUNDGROUP *soundgroup, float volume);
FMOD_RESULT F_API FMOD_SoundGroup_GetVolume          (FMOD_SOUNDGROUP *soundgroup, float *volume);
FMOD_RESULT F_API FMOD_SoundGroup_Stop               (FMOD_SOUNDGROUP *soundgroup);

/*
     Information only functions.
*/

FMOD_RESULT F_API FMOD_SoundGroup_GetName            (FMOD_SOUNDGROUP *soundgroup, char *name, int namelen);
FMOD_RESULT F_API FMOD_SoundGroup_GetNumSounds       (FMOD_SOUNDGROUP *soundgroup, int *numsounds);
FMOD_RESULT F_API FMOD_SoundGroup_GetSound           (FMOD_SOUNDGROUP *soundgroup, int index, FMOD_SOUND **sound);
FMOD_RESULT F_API FMOD_SoundGroup_GetNumPlaying      (FMOD_SOUNDGROUP *soundgroup, int *numplaying);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_SoundGroup_SetUserData        (FMOD_SOUNDGROUP *soundgroup, void *userdata);
FMOD_RESULT F_API FMOD_SoundGroup_GetUserData        (FMOD_SOUNDGROUP *soundgroup, void **userdata);

FMOD_RESULT F_API FMOD_SoundGroup_GetMemoryInfo      (FMOD_SOUNDGROUP *soundgroup, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'DSP' API
*/

FMOD_RESULT F_API FMOD_DSP_Release                   (FMOD_DSP *dsp);
FMOD_RESULT F_API FMOD_DSP_GetSystemObject           (FMOD_DSP *dsp, FMOD_SYSTEM **system);

/*
     Connection / disconnection / input and output enumeration.
*/

FMOD_RESULT F_API FMOD_DSP_AddInput                  (FMOD_DSP *dsp, FMOD_DSP *target, FMOD_DSPCONNECTION **connection);
FMOD_RESULT F_API FMOD_DSP_DisconnectFrom            (FMOD_DSP *dsp, FMOD_DSP *target);
FMOD_RESULT F_API FMOD_DSP_DisconnectAll             (FMOD_DSP *dsp, FMOD_BOOL inputs, FMOD_BOOL outputs);
FMOD_RESULT F_API FMOD_DSP_Remove                    (FMOD_DSP *dsp);
FMOD_RESULT F_API FMOD_DSP_GetNumInputs              (FMOD_DSP *dsp, int *numinputs);
FMOD_RESULT F_API FMOD_DSP_GetNumOutputs             (FMOD_DSP *dsp, int *numoutputs);
FMOD_RESULT F_API FMOD_DSP_GetInput                  (FMOD_DSP *dsp, int index, FMOD_DSP **input, FMOD_DSPCONNECTION **inputconnection);
FMOD_RESULT F_API FMOD_DSP_GetOutput                 (FMOD_DSP *dsp, int index, FMOD_DSP **output, FMOD_DSPCONNECTION **outputconnection);

/*
     DSP unit control.
*/

FMOD_RESULT F_API FMOD_DSP_SetActive                 (FMOD_DSP *dsp, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_DSP_GetActive                 (FMOD_DSP *dsp, FMOD_BOOL *active);
FMOD_RESULT F_API FMOD_DSP_SetBypass                 (FMOD_DSP *dsp, FMOD_BOOL bypass);
FMOD_RESULT F_API FMOD_DSP_GetBypass                 (FMOD_DSP *dsp, FMOD_BOOL *bypass);
FMOD_RESULT F_API FMOD_DSP_SetSpeakerActive          (FMOD_DSP *dsp, FMOD_SPEAKER speaker, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_DSP_GetSpeakerActive          (FMOD_DSP *dsp, FMOD_SPEAKER speaker, FMOD_BOOL *active);
FMOD_RESULT F_API FMOD_DSP_Reset                     (FMOD_DSP *dsp);

/*
     DSP parameter control.
*/

FMOD_RESULT F_API FMOD_DSP_SetParameter              (FMOD_DSP *dsp, int index, float value);
FMOD_RESULT F_API FMOD_DSP_GetParameter              (FMOD_DSP *dsp, int index, float *value, char *valuestr, int valuestrlen);
FMOD_RESULT F_API FMOD_DSP_GetNumParameters          (FMOD_DSP *dsp, int *numparams);
FMOD_RESULT F_API FMOD_DSP_GetParameterInfo          (FMOD_DSP *dsp, int index, char *name, char *label, char *description, int descriptionlen, float *min, float *max);
FMOD_RESULT F_API FMOD_DSP_ShowConfigDialog          (FMOD_DSP *dsp, void *hwnd, FMOD_BOOL show);

/*
     DSP attributes.        
*/

FMOD_RESULT F_API FMOD_DSP_GetInfo                   (FMOD_DSP *dsp, char *name, unsigned int *version, int *channels, int *configwidth, int *configheight);
FMOD_RESULT F_API FMOD_DSP_GetType                   (FMOD_DSP *dsp, FMOD_DSP_TYPE *type);
FMOD_RESULT F_API FMOD_DSP_SetDefaults               (FMOD_DSP *dsp, float frequency, float volume, float pan, int priority);
FMOD_RESULT F_API FMOD_DSP_GetDefaults               (FMOD_DSP *dsp, float *frequency, float *volume, float *pan, int *priority);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_DSP_SetUserData               (FMOD_DSP *dsp, void *userdata);
FMOD_RESULT F_API FMOD_DSP_GetUserData               (FMOD_DSP *dsp, void **userdata);

FMOD_RESULT F_API FMOD_DSP_GetMemoryInfo             (FMOD_DSP *dsp, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'DSPConnection' API
*/

FMOD_RESULT F_API FMOD_DSPConnection_GetInput        (FMOD_DSPCONNECTION *dspconnection, FMOD_DSP **input);
FMOD_RESULT F_API FMOD_DSPConnection_GetOutput       (FMOD_DSPCONNECTION *dspconnection, FMOD_DSP **output);
FMOD_RESULT F_API FMOD_DSPConnection_SetMix          (FMOD_DSPCONNECTION *dspconnection, float volume);
FMOD_RESULT F_API FMOD_DSPConnection_GetMix          (FMOD_DSPCONNECTION *dspconnection, float *volume);
FMOD_RESULT F_API FMOD_DSPConnection_SetLevels       (FMOD_DSPCONNECTION *dspconnection, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT F_API FMOD_DSPConnection_GetLevels       (FMOD_DSPCONNECTION *dspconnection, FMOD_SPEAKER speaker, float *levels, int numlevels);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_DSPConnection_SetUserData     (FMOD_DSPCONNECTION *dspconnection, void *userdata);
FMOD_RESULT F_API FMOD_DSPConnection_GetUserData     (FMOD_DSPCONNECTION *dspconnection, void **userdata);

FMOD_RESULT F_API FMOD_DSPConnection_GetMemoryInfo   (FMOD_DSPCONNECTION *dspconnection, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'Geometry' API
*/

FMOD_RESULT F_API FMOD_Geometry_Release              (FMOD_GEOMETRY *geometry);

/*
     Polygon manipulation.
*/

FMOD_RESULT F_API FMOD_Geometry_AddPolygon           (FMOD_GEOMETRY *geometry, float directocclusion, float reverbocclusion, FMOD_BOOL doublesided, int numvertices, const FMOD_VECTOR *vertices, int *polygonindex);
FMOD_RESULT F_API FMOD_Geometry_GetNumPolygons       (FMOD_GEOMETRY *geometry, int *numpolygons);
FMOD_RESULT F_API FMOD_Geometry_GetMaxPolygons       (FMOD_GEOMETRY *geometry, int *maxpolygons, int *maxvertices);
FMOD_RESULT F_API FMOD_Geometry_GetPolygonNumVertices(FMOD_GEOMETRY *geometry, int index, int *numvertices);
FMOD_RESULT F_API FMOD_Geometry_SetPolygonVertex     (FMOD_GEOMETRY *geometry, int index, int vertexindex, const FMOD_VECTOR *vertex);
FMOD_RESULT F_API FMOD_Geometry_GetPolygonVertex     (FMOD_GEOMETRY *geometry, int index, int vertexindex, FMOD_VECTOR *vertex);
FMOD_RESULT F_API FMOD_Geometry_SetPolygonAttributes (FMOD_GEOMETRY *geometry, int index, float directocclusion, float reverbocclusion, FMOD_BOOL doublesided);
FMOD_RESULT F_API FMOD_Geometry_GetPolygonAttributes (FMOD_GEOMETRY *geometry, int index, float *directocclusion, float *reverbocclusion, FMOD_BOOL *doublesided);

/*
     Object manipulation.
*/

FMOD_RESULT F_API FMOD_Geometry_SetActive            (FMOD_GEOMETRY *geometry, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_Geometry_GetActive            (FMOD_GEOMETRY *geometry, FMOD_BOOL *active);
FMOD_RESULT F_API FMOD_Geometry_SetRotation          (FMOD_GEOMETRY *geometry, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_Geometry_GetRotation          (FMOD_GEOMETRY *geometry, FMOD_VECTOR *forward, FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_Geometry_SetPosition          (FMOD_GEOMETRY *geometry, const FMOD_VECTOR *position);
FMOD_RESULT F_API FMOD_Geometry_GetPosition          (FMOD_GEOMETRY *geometry, FMOD_VECTOR *position);
FMOD_RESULT F_API FMOD_Geometry_SetScale             (FMOD_GEOMETRY *geometry, const FMOD_VECTOR *scale);
FMOD_RESULT F_API FMOD_Geometry_GetScale             (FMOD_GEOMETRY *geometry, FMOD_VECTOR *scale);
FMOD_RESULT F_API FMOD_Geometry_Save                 (FMOD_GEOMETRY *geometry, void *data, int *datasize);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_Geometry_SetUserData          (FMOD_GEOMETRY *geometry, void *userdata);
FMOD_RESULT F_API FMOD_Geometry_GetUserData          (FMOD_GEOMETRY *geometry, void **userdata);

FMOD_RESULT F_API FMOD_Geometry_GetMemoryInfo        (FMOD_GEOMETRY *geometry, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/*
    'Reverb' API
*/

FMOD_RESULT F_API FMOD_Reverb_Release                (FMOD_REVERB *reverb);

/*
     Reverb manipulation.
*/

FMOD_RESULT F_API FMOD_Reverb_Set3DAttributes        (FMOD_REVERB *reverb, const FMOD_VECTOR *position, float mindistance, float maxdistance);
FMOD_RESULT F_API FMOD_Reverb_Get3DAttributes        (FMOD_REVERB *reverb, FMOD_VECTOR *position, float *mindistance, float *maxdistance);
FMOD_RESULT F_API FMOD_Reverb_SetProperties          (FMOD_REVERB *reverb, const FMOD_REVERB_PROPERTIES *properties);
FMOD_RESULT F_API FMOD_Reverb_GetProperties          (FMOD_REVERB *reverb, FMOD_REVERB_PROPERTIES *properties);
FMOD_RESULT F_API FMOD_Reverb_SetActive              (FMOD_REVERB *reverb, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_Reverb_GetActive              (FMOD_REVERB *reverb, FMOD_BOOL *active);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_Reverb_SetUserData            (FMOD_REVERB *reverb, void *userdata);
FMOD_RESULT F_API FMOD_Reverb_GetUserData            (FMOD_REVERB *reverb, void **userdata);

FMOD_RESULT F_API FMOD_Reverb_GetMemoryInfo          (FMOD_REVERB *reverb, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);
/*$ preserve start $*/

#ifdef __cplusplus
}
#endif

#endif

/*$ preserve end $*/
