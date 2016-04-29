/*$ preserve start $*/

/* ================================================================================================== */
/* FMOD Studio - Common C/C++ header file. Copyright (c), Firelight Technologies Pty, Ltd. 2004-2015. */
/*                                                                                                    */
/* This header is included by fmod.hpp (C++ interface) and fmod.h (C interface) therefore is the      */
/* base header for all FMOD headers.                                                                  */
/* ================================================================================================== */

#ifndef _FMOD_COMMON_H
#define _FMOD_COMMON_H

/*
    FMOD version number.  Check this against FMOD::System::getVersion.
    0xaaaabbcc -> aaaa = major version number.  bb = minor version number.  cc = development version number.
*/

#define FMOD_VERSION    0x00010608

/*
    Compiler specific settings.
*/

#if defined(__CYGWIN32__) || defined(__MINGW32__)
    #define F_STDCALL __stdcall
    #define F_DECLSPEC __declspec
    #define F_DLLEXPORT ( dllexport )
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
    #define F_STDCALL _stdcall
    #define F_DECLSPEC __declspec
    #define F_DLLEXPORT ( dllexport )
#elif defined(__MACH__) || defined(__ANDROID__) || defined(__linux__)
    #define F_STDCALL
    #define F_DECLSPEC
    #define F_DLLEXPORT __attribute__ ((visibility("default")))
#elif defined(__ORBIS__) || defined(__psp2__)
    #define F_CDECL
    #define F_STDCALL
    #define F_DECLSPEC __declspec
    #define F_DLLEXPORT ( dllexport )
#else
    #define F_STDCALL
    #define F_DECLSPEC
    #define F_DLLEXPORT
#endif

#ifdef DLL_EXPORTS
    #define F_API F_DECLSPEC F_DLLEXPORT F_STDCALL
#else
    #define F_API F_STDCALL
#endif

#define F_CALLBACK F_STDCALL

/*
    FMOD types.
*/

typedef int                        FMOD_BOOL;
typedef struct FMOD_SYSTEM         FMOD_SYSTEM;
typedef struct FMOD_SOUND          FMOD_SOUND;
typedef struct FMOD_CHANNELCONTROL FMOD_CHANNELCONTROL;
typedef struct FMOD_CHANNEL        FMOD_CHANNEL;
typedef struct FMOD_CHANNELGROUP   FMOD_CHANNELGROUP;
typedef struct FMOD_SOUNDGROUP     FMOD_SOUNDGROUP;
typedef struct FMOD_REVERB3D       FMOD_REVERB3D;
typedef struct FMOD_DSP            FMOD_DSP;
typedef struct FMOD_DSPCONNECTION  FMOD_DSPCONNECTION;
typedef struct FMOD_POLYGON        FMOD_POLYGON;
typedef struct FMOD_GEOMETRY       FMOD_GEOMETRY;
typedef struct FMOD_SYNCPOINT      FMOD_SYNCPOINT;
typedef struct FMOD_ASYNCREADINFO  FMOD_ASYNCREADINFO;
typedef unsigned int               FMOD_MODE;
typedef unsigned int               FMOD_TIMEUNIT;
typedef unsigned int               FMOD_INITFLAGS;
typedef unsigned int               FMOD_DEBUG_FLAGS;
typedef unsigned int               FMOD_MEMORY_TYPE;
typedef unsigned int               FMOD_SYSTEM_CALLBACK_TYPE;
typedef unsigned int               FMOD_CHANNELMASK;
typedef unsigned int               FMOD_DRIVER_STATE;
typedef unsigned int               FMOD_PORT_TYPE;
typedef unsigned long long         FMOD_PORT_INDEX;

/*$ fmod result start $*/
/*
[ENUM]
[
    [DESCRIPTION]   
    error codes.  Returned from every function.

    [REMARKS]

    [SEE_ALSO]      
]
*/
typedef enum
{
    FMOD_OK,                        /* No errors. */
    FMOD_ERR_BADCOMMAND,            /* Tried to call a function on a data type that does not allow this type of functionality (ie calling Sound::lock on a streaming sound). */
    FMOD_ERR_CHANNEL_ALLOC,         /* Error trying to allocate a channel. */
    FMOD_ERR_CHANNEL_STOLEN,        /* The specified channel has been reused to play another sound. */
    FMOD_ERR_DMA,                   /* DMA Failure.  See debug output for more information. */
    FMOD_ERR_DSP_CONNECTION,        /* DSP connection error.  Connection possibly caused a cyclic dependency or connected dsps with incompatible buffer counts. */
    FMOD_ERR_DSP_DONTPROCESS,       /* DSP return code from a DSP process query callback.  Tells mixer not to call the process callback and therefore not consume CPU.  Use this to optimize the DSP graph. */
    FMOD_ERR_DSP_FORMAT,            /* DSP Format error.  A DSP unit may have attempted to connect to this network with the wrong format, or a matrix may have been set with the wrong size if the target unit has a specified channel map. */
    FMOD_ERR_DSP_INUSE,             /* DSP is already in the mixer's DSP network. It must be removed before being reinserted or released. */
    FMOD_ERR_DSP_NOTFOUND,          /* DSP connection error.  Couldn't find the DSP unit specified. */
    FMOD_ERR_DSP_RESERVED,          /* DSP operation error.  Cannot perform operation on this DSP as it is reserved by the system. */
    FMOD_ERR_DSP_SILENCE,           /* DSP return code from a DSP process query callback.  Tells mixer silence would be produced from read, so go idle and not consume CPU.  Use this to optimize the DSP graph. */
    FMOD_ERR_DSP_TYPE,              /* DSP operation cannot be performed on a DSP of this type. */
    FMOD_ERR_FILE_BAD,              /* Error loading file. */
    FMOD_ERR_FILE_COULDNOTSEEK,     /* Couldn't perform seek operation.  This is a limitation of the medium (ie netstreams) or the file format. */
    FMOD_ERR_FILE_DISKEJECTED,      /* Media was ejected while reading. */
    FMOD_ERR_FILE_EOF,              /* End of file unexpectedly reached while trying to read essential data (truncated?). */
    FMOD_ERR_FILE_ENDOFDATA,        /* End of current chunk reached while trying to read data. */
    FMOD_ERR_FILE_NOTFOUND,         /* File not found. */
    FMOD_ERR_FORMAT,                /* Unsupported file or audio format. */
    FMOD_ERR_HEADER_MISMATCH,       /* There is a version mismatch between the FMOD header and either the FMOD Studio library or the FMOD Low Level library. */
    FMOD_ERR_HTTP,                  /* A HTTP error occurred. This is a catch-all for HTTP errors not listed elsewhere. */
    FMOD_ERR_HTTP_ACCESS,           /* The specified resource requires authentication or is forbidden. */
    FMOD_ERR_HTTP_PROXY_AUTH,       /* Proxy authentication is required to access the specified resource. */
    FMOD_ERR_HTTP_SERVER_ERROR,     /* A HTTP server error occurred. */
    FMOD_ERR_HTTP_TIMEOUT,          /* The HTTP request timed out. */
    FMOD_ERR_INITIALIZATION,        /* FMOD was not initialized correctly to support this function. */
    FMOD_ERR_INITIALIZED,           /* Cannot call this command after System::init. */
    FMOD_ERR_INTERNAL,              /* An error occurred that wasn't supposed to.  Contact support. */
    FMOD_ERR_INVALID_FLOAT,         /* Value passed in was a NaN, Inf or denormalized float. */
    FMOD_ERR_INVALID_HANDLE,        /* An invalid object handle was used. */
    FMOD_ERR_INVALID_PARAM,         /* An invalid parameter was passed to this function. */
    FMOD_ERR_INVALID_POSITION,      /* An invalid seek position was passed to this function. */
    FMOD_ERR_INVALID_SPEAKER,       /* An invalid speaker was passed to this function based on the current speaker mode. */
    FMOD_ERR_INVALID_SYNCPOINT,     /* The syncpoint did not come from this sound handle. */
    FMOD_ERR_INVALID_THREAD,        /* Tried to call a function on a thread that is not supported. */
    FMOD_ERR_INVALID_VECTOR,        /* The vectors passed in are not unit length, or perpendicular. */
    FMOD_ERR_MAXAUDIBLE,            /* Reached maximum audible playback count for this sound's soundgroup. */
    FMOD_ERR_MEMORY,                /* Not enough memory or resources. */
    FMOD_ERR_MEMORY_CANTPOINT,      /* Can't use FMOD_OPENMEMORY_POINT on non PCM source data, or non mp3/xma/adpcm data if FMOD_CREATECOMPRESSEDSAMPLE was used. */
    FMOD_ERR_NEEDS3D,               /* Tried to call a command on a 2d sound when the command was meant for 3d sound. */
    FMOD_ERR_NEEDSHARDWARE,         /* Tried to use a feature that requires hardware support. */
    FMOD_ERR_NET_CONNECT,           /* Couldn't connect to the specified host. */
    FMOD_ERR_NET_SOCKET_ERROR,      /* A socket error occurred.  This is a catch-all for socket-related errors not listed elsewhere. */
    FMOD_ERR_NET_URL,               /* The specified URL couldn't be resolved. */
    FMOD_ERR_NET_WOULD_BLOCK,       /* Operation on a non-blocking socket could not complete immediately. */
    FMOD_ERR_NOTREADY,              /* Operation could not be performed because specified sound/DSP connection is not ready. */
    FMOD_ERR_OUTPUT_ALLOCATED,      /* Error initializing output device, but more specifically, the output device is already in use and cannot be reused. */
    FMOD_ERR_OUTPUT_CREATEBUFFER,   /* Error creating hardware sound buffer. */
    FMOD_ERR_OUTPUT_DRIVERCALL,     /* A call to a standard soundcard driver failed, which could possibly mean a bug in the driver or resources were missing or exhausted. */
    FMOD_ERR_OUTPUT_FORMAT,         /* Soundcard does not support the specified format. */
    FMOD_ERR_OUTPUT_INIT,           /* Error initializing output device. */
    FMOD_ERR_OUTPUT_NODRIVERS,      /* The output device has no drivers installed.  If pre-init, FMOD_OUTPUT_NOSOUND is selected as the output mode.  If post-init, the function just fails. */
    FMOD_ERR_PLUGIN,                /* An unspecified error has been returned from a plugin. */
    FMOD_ERR_PLUGIN_MISSING,        /* A requested output, dsp unit type or codec was not available. */
    FMOD_ERR_PLUGIN_RESOURCE,       /* A resource that the plugin requires cannot be found. (ie the DLS file for MIDI playback) */
    FMOD_ERR_PLUGIN_VERSION,        /* A plugin was built with an unsupported SDK version. */
    FMOD_ERR_RECORD,                /* An error occurred trying to initialize the recording device. */
    FMOD_ERR_REVERB_CHANNELGROUP,   /* Reverb properties cannot be set on this channel because a parent channelgroup owns the reverb connection. */
    FMOD_ERR_REVERB_INSTANCE,       /* Specified instance in FMOD_REVERB_PROPERTIES couldn't be set. Most likely because it is an invalid instance number or the reverb doesn't exist. */
    FMOD_ERR_SUBSOUNDS,             /* The error occurred because the sound referenced contains subsounds when it shouldn't have, or it doesn't contain subsounds when it should have.  The operation may also not be able to be performed on a parent sound. */
    FMOD_ERR_SUBSOUND_ALLOCATED,    /* This subsound is already being used by another sound, you cannot have more than one parent to a sound.  Null out the other parent's entry first. */
    FMOD_ERR_SUBSOUND_CANTMOVE,     /* Shared subsounds cannot be replaced or moved from their parent stream, such as when the parent stream is an FSB file. */
    FMOD_ERR_TAGNOTFOUND,           /* The specified tag could not be found or there are no tags. */
    FMOD_ERR_TOOMANYCHANNELS,       /* The sound created exceeds the allowable input channel count.  This can be increased using the 'maxinputchannels' parameter in System::setSoftwareFormat. */
    FMOD_ERR_TRUNCATED,             /* The retrieved string is too long to fit in the supplied buffer and has been truncated. */
    FMOD_ERR_UNIMPLEMENTED,         /* Something in FMOD hasn't been implemented when it should be! contact support! */
    FMOD_ERR_UNINITIALIZED,         /* This command failed because System::init or System::setDriver was not called. */
    FMOD_ERR_UNSUPPORTED,           /* A command issued was not supported by this object.  Possibly a plugin without certain callbacks specified. */
    FMOD_ERR_VERSION,               /* The version number of this file format is not supported. */
    FMOD_ERR_EVENT_ALREADY_LOADED,  /* The specified bank has already been loaded. */
    FMOD_ERR_EVENT_LIVEUPDATE_BUSY, /* The live update connection failed due to the game already being connected. */
    FMOD_ERR_EVENT_LIVEUPDATE_MISMATCH, /* The live update connection failed due to the game data being out of sync with the tool. */
    FMOD_ERR_EVENT_LIVEUPDATE_TIMEOUT, /* The live update connection timed out. */
    FMOD_ERR_EVENT_NOTFOUND,        /* The requested event, bus or vca could not be found. */
    FMOD_ERR_STUDIO_UNINITIALIZED,  /* The Studio::System object is not yet initialized. */
    FMOD_ERR_STUDIO_NOT_LOADED,     /* The specified resource is not loaded, so it can't be unloaded. */

    FMOD_ERR_INVALID_STRING,        /* An invalid string was passed to this function. */
    FMOD_ERR_ALREADY_LOCKED,        /* The specified resource is already locked. */
    FMOD_ERR_NOT_LOCKED,            /* The specified resource is not locked, so it can't be unlocked. */

    FMOD_RESULT_FORCEINT = 65536    /* Makes sure this enum is signed 32bit. */
} FMOD_RESULT;
/*$ fmod result end $*/


/*
[ENUM] 
[
    [DESCRIPTION]   
    Used to distinguish if a FMOD_CHANNELCONTROL parameter is actually a channel or a channelgroup.

    [REMARKS]
    Cast the FMOD_CHANNELCONTROL to an FMOD_CHANNEL/FMOD::Channel, or FMOD_CHANNELGROUP/FMOD::ChannelGroup if specific functionality is needed for either class.
    Otherwise use as FMOD_CHANNELCONTROL/FMOD::ChannelControl and use that API.

    [SEE_ALSO]      
    Channel::setCallback
    ChannelGroup::setCallback
]
*/
typedef enum
{
    FMOD_CHANNELCONTROL_CHANNEL,
    FMOD_CHANNELCONTROL_CHANNELGROUP,

    FMOD_CHANNELCONTROL_FORCEINT = 65536    /* Makes sure this enum is signed 32bit. */
} FMOD_CHANNELCONTROL_TYPE;


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Structure describing a point in 3D space.

    [REMARKS]
    FMOD uses a left handed co-ordinate system by default.<br>
    To use a right handed co-ordinate system specify FMOD_INIT_3D_RIGHTHANDED from FMOD_INITFLAGS in System::init.

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
    Structure describing a position, velocity and orientation.

    [REMARKS]

    [SEE_ALSO]
    FMOD_VECTOR
    FMOD_DSP_PARAMETER_3DATTRIBUTES
]
*/
typedef struct FMOD_3D_ATTRIBUTES
{
    FMOD_VECTOR position;
    FMOD_VECTOR velocity;
    FMOD_VECTOR forward;
    FMOD_VECTOR up;
} FMOD_3D_ATTRIBUTES;


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Structure describing a globally unique identifier.

    [REMARKS]

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

typedef void (F_CALLBACK *FMOD_FILE_ASYNCDONE)           (FMOD_ASYNCREADINFO *info, FMOD_RESULT result);

/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Structure that is passed into FMOD_FILE_ASYNCREAD_CALLBACK.  Use the information in this structure to perform

    [REMARKS]
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>
    <br>
    Instructions: write to 'buffer', and 'bytesread' <b>BEFORE</b> calling 'done'.<br>  
    As soon as done is called, FMOD will asynchronously continue internally using the data provided in this structure.<br>
    <br>
    Set result in the 'done' function pointer to the result expected from a normal file read callback.<br>
    If the read was successful, set it to FMOD_OK.<br>
    If it read some data but hit the end of the file, set it to FMOD_ERR_FILE_EOF.<br>
    If a bad error occurred, return FMOD_ERR_FILE_BAD<br>
    If a disk was ejected, return FMOD_ERR_FILE_DISKEJECTED.<br>

    [SEE_ALSO]
    FMOD_FILE_ASYNCREAD_CALLBACK
    FMOD_FILE_ASYNCCANCEL_CALLBACK
    FMOD_FILE_ASYNCDONE
]
*/
struct FMOD_ASYNCREADINFO
{
    void                 *handle;    /* [r] The file handle that was filled out in the open callback. */
    unsigned int          offset;    /* [r] Seek position, make sure you read from this file offset. */
    unsigned int          sizebytes; /* [r] how many bytes requested for read. */
    int                   priority;  /* [r] 0 = low importance.  100 = extremely important (ie 'must read now or stuttering may occur') */

    void                 *userdata;  /* [r/w] User data pointer specific to this request.  Initially 0, can be ignored or set by the user.  Not related to the file's main userdata member.  */

    void                 *buffer;    /* [w] Buffer to read file data into. */
    unsigned int          bytesread; /* [w] Fill this in before setting result code to tell FMOD how many bytes were read. */

    FMOD_FILE_ASYNCDONE   done;      /* [r] FMOD file system wake up function.  Call this when user file read is finished.  Pass result of file read as a parameter. */
};


/*
[ENUM]
[
    [DESCRIPTION]   
    These output types are used with System::setOutput / System::getOutput, to choose which output method to use.
  
    [REMARKS]
    To pass information to the driver when initializing fmod use the *extradriverdata* parameter in System::init for the following reasons.

    - FMOD_OUTPUTTYPE_WAVWRITER     - extradriverdata is a pointer to a char * file name that the wav writer will output to.
    - FMOD_OUTPUTTYPE_WAVWRITER_NRT - extradriverdata is a pointer to a char * file name that the wav writer will output to.
    - FMOD_OUTPUTTYPE_DSOUND        - extradriverdata is cast to a HWND type, so that FMOD can set the focus on the audio for a particular window.
    - FMOD_OUTPUTTYPE_PS3           - extradriverdata is a pointer to a FMOD_PS3_EXTRADRIVERDATA struct. This can be found in fmodps3.h.
    - FMOD_OUTPUTTYPE_XBOX360       - extradriverdata is a pointer to a FMOD_360_EXTRADRIVERDATA struct. This can be found in fmodxbox360.h.

    Currently these are the only FMOD drivers that take extra information.  Other unknown plugins may have different requirements.

    Note! If FMOD_OUTPUTTYPE_WAVWRITER_NRT or FMOD_OUTPUTTYPE_NOSOUND_NRT are used, and if the System::update function is being called
    very quickly (ie for a non realtime decode) it may be being called too quickly for the FMOD streamer thread to respond to.
    The result will be a skipping/stuttering output in the captured audio.

    To remedy this, disable the FMOD streamer thread, and use FMOD_INIT_STREAM_FROM_UPDATE to avoid skipping in the output stream,
    as it will lock the mixer and the streamer together in the same thread.

    [SEE_ALSO]
    System::setOutput
    System::getOutput
    System::init
    System::update
]
*/
typedef enum
{
    FMOD_OUTPUTTYPE_AUTODETECT,      /* Picks the best output mode for the platform. This is the default. */

    FMOD_OUTPUTTYPE_UNKNOWN,         /* All - 3rd party plugin, unknown. This is for use with System::getOutput only. */
    FMOD_OUTPUTTYPE_NOSOUND,         /* All - Perform all mixing but discard the final output. */
    FMOD_OUTPUTTYPE_WAVWRITER,       /* All - Writes output to a .wav file. */
    FMOD_OUTPUTTYPE_NOSOUND_NRT,     /* All - Non-realtime version of FMOD_OUTPUTTYPE_NOSOUND. User can drive mixer with System::update at whatever rate they want. */
    FMOD_OUTPUTTYPE_WAVWRITER_NRT,   /* All - Non-realtime version of FMOD_OUTPUTTYPE_WAVWRITER. User can drive mixer with System::update at whatever rate they want. */

    FMOD_OUTPUTTYPE_DSOUND,          /* Win                  - Direct Sound.                        (Default on Windows XP and below) */
    FMOD_OUTPUTTYPE_WINMM,           /* Win                  - Windows Multimedia. */
    FMOD_OUTPUTTYPE_WASAPI,          /* Win/WinStore/XboxOne - Windows Audio Session API.           (Default on Windows Vista and above, Xbox One and Windows Store Applications) */
    FMOD_OUTPUTTYPE_ASIO,            /* Win                  - Low latency ASIO 2.0. */
    FMOD_OUTPUTTYPE_PULSEAUDIO,      /* Linux                - Pulse Audio.                         (Default on Linux if available) */
    FMOD_OUTPUTTYPE_ALSA,            /* Linux                - Advanced Linux Sound Architecture.   (Default on Linux if PulseAudio isn't available) */
    FMOD_OUTPUTTYPE_COREAUDIO,       /* Mac/iOS              - Core Audio.                          (Default on Mac and iOS) */
    FMOD_OUTPUTTYPE_XBOX360,         /* Xbox 360             - XAudio.                              (Default on Xbox 360) */
    FMOD_OUTPUTTYPE_PS3,             /* PS3                  - Audio Out.                           (Default on PS3) */
    FMOD_OUTPUTTYPE_AUDIOTRACK,      /* Android              - Java Audio Track.                    (Default on Android 2.2 and below) */
    FMOD_OUTPUTTYPE_OPENSL,          /* Android              - OpenSL ES.                           (Default on Android 2.3 and above) */
    FMOD_OUTPUTTYPE_WIIU,            /* Wii U                - AX.                                  (Default on Wii U) */
    FMOD_OUTPUTTYPE_AUDIOOUT,        /* PS4/PSVita           - Audio Out.                           (Default on PS4 and PS Vita) */

    FMOD_OUTPUTTYPE_MAX,             /* Maximum number of output types supported. */
    FMOD_OUTPUTTYPE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_OUTPUTTYPE;


/*
[ENUM]
[
    [DESCRIPTION]
    Specify the destination of log output when using the logging version of FMOD.

    [REMARKS]
    TTY destination can vary depending on platform, common examples include the
    Visual Studio / Xcode output window, stderr and LogCat.

    [SEE_ALSO]
    FMOD_Debug_Initialize
]
*/
typedef enum
{
    FMOD_DEBUG_MODE_TTY,             /* Default log location per platform, i.e. Visual Studio output window, stderr, LogCat, etc */
    FMOD_DEBUG_MODE_FILE,            /* Write log to specified file path */
    FMOD_DEBUG_MODE_CALLBACK,        /* Call specified callback with log information */

    FMOD_DEBUG_MODE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_DEBUG_MODE;


/*
[DEFINE]
[
    [NAME]
    FMOD_DEBUG_FLAGS

    [DESCRIPTION]
    Specify the requested information to be output when using the logging version of FMOD.

    [REMARKS]

    [SEE_ALSO]
    FMOD_Debug_Initialize
]
*/
#define FMOD_DEBUG_LEVEL_NONE           0x00000000    /* Disable all messages */
#define FMOD_DEBUG_LEVEL_ERROR          0x00000001    /* Enable only error messages. */
#define FMOD_DEBUG_LEVEL_WARNING        0x00000002    /* Enable warning and error messages. */
#define FMOD_DEBUG_LEVEL_LOG            0x00000004    /* Enable informational, warning and error messages (default). */
#define FMOD_DEBUG_TYPE_MEMORY          0x00000100    /* Verbose logging for memory operations, only use this if you are debugging a memory related issue. */
#define FMOD_DEBUG_TYPE_FILE            0x00000200    /* Verbose logging for file access, only use this if you are debugging a file related issue. */
#define FMOD_DEBUG_TYPE_CODEC           0x00000400    /* Verbose logging for codec initialization, only use this if you are debugging a codec related issue. */
#define FMOD_DEBUG_TYPE_TRACE           0x00000800    /* Verbose logging for internal errors, use this for tracking the origin of error codes. */
#define FMOD_DEBUG_DISPLAY_TIMESTAMPS   0x00010000    /* Display the time stamp of the log message in milliseconds. */
#define FMOD_DEBUG_DISPLAY_LINENUMBERS  0x00020000    /* Display the source code file and line number for where the message originated. */
#define FMOD_DEBUG_DISPLAY_THREAD       0x00040000    /* Display the thread ID of the calling function that generated the message. */
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

    [SEE_ALSO]
    FMOD_MEMORY_ALLOC_CALLBACK
    FMOD_MEMORY_REALLOC_CALLBACK
    FMOD_MEMORY_FREE_CALLBACK
    Memory_Initialize
]
*/
#define FMOD_MEMORY_NORMAL             0x00000000       /* Standard memory. */
#define FMOD_MEMORY_STREAM_FILE        0x00000001       /* Stream file buffer, size controllable with System::setStreamBufferSize. */
#define FMOD_MEMORY_STREAM_DECODE      0x00000002       /* Stream decode buffer, size controllable with FMOD_CREATESOUNDEXINFO::decodebuffersize. */
#define FMOD_MEMORY_SAMPLEDATA         0x00000004       /* Sample data buffer.  Raw audio data, usually PCM/MPEG/ADPCM/XMA data. */
#define FMOD_MEMORY_DSP_BUFFER         0x00000008       /* DSP memory block allocated when more than 1 output exists on a DSP node. */
#define FMOD_MEMORY_PLUGIN             0x00000010       /* Memory allocated by a third party plugin. */
#define FMOD_MEMORY_XBOX360_PHYSICAL   0x00100000       /* Requires XPhysicalAlloc / XPhysicalFree. */
#define FMOD_MEMORY_PERSISTENT         0x00200000       /* Persistent memory. Memory will be freed when System::release is called. */
#define FMOD_MEMORY_SECONDARY          0x00400000       /* Secondary memory. Allocation should be in secondary memory. For example RSX on the PS3. */
#define FMOD_MEMORY_ALL                0xFFFFFFFF
/* [DEFINE_END] */


/*
[ENUM]
[
    [DESCRIPTION]   
    These are speaker types defined for use with the System::setSoftwareFormat command.

    [REMARKS]
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
    Channel::setPan and Channel::setPanLevels do not work.<br>
    Speaker levels must be manually set with Channel::setPanMatrix.<br>
    <br>
    FMOD_SPEAKERMODE_MONO<br>
    ---------------------<br>
    This mode is for a 1 speaker arrangement.<br>
    Panning does not work in this speaker mode.<br>
    Mono, stereo and multichannel sounds have each sound channel played on the one speaker unity.<br>
    Mix behavior for multichannel sounds can be set with Channel::setPanMatrix.<br>
    Channel::setPanLevels does not work.<br>
    <br>
    FMOD_SPEAKERMODE_STEREO<br>
    -----------------------<br>
    This mode is for 2 speaker arrangements that have a left and right speaker.<br>
    <li>Mono sounds default to an even distribution between left and right.  They can be panned with Channel::setPan.<br>
    <li>Stereo sounds default to the middle, or full left in the left speaker and full right in the right speaker.  
    <li>They can be cross faded with Channel::setPan.<br>
    <li>Multichannel sounds have each sound channel played on each speaker at unity.<br>
    <li>Mix behavior for multichannel sounds can be set with Channel::setPanMatrix.<br>
    <li>Channel::setPanLevels works but only front left and right parameters are used, the rest are ignored.<br>
    <br>
    FMOD_SPEAKERMODE_QUAD<br>
    ------------------------<br>
    This mode is for 4 speaker arrangements that have a front left, front right, surround left and a surround right speaker.<br>
    <li>Mono sounds default to an even distribution between front left and front right.  They can be panned with Channel::setPan.<br>
    <li>Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.<br>
    <li>They can be cross faded with Channel::setPan.<br>
    <li>Multichannel sounds default to all of their sound channels being played on each speaker in order of input.<br>
    <li>Mix behavior for multichannel sounds can be set with Channel::setPanMatrix.<br>
    <li>Channel::setPanLevels works but rear left, rear right, center and lfe are ignored.<br>
    <br>
    FMOD_SPEAKERMODE_SURROUND<br>
    ------------------------<br>
    This mode is for 5 speaker arrangements that have a left/right/center/surround left/surround right.<br>
    <li>Mono sounds default to the center speaker.  They can be panned with Channel::setPan.<br>
    <li>Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.  
    <li>They can be cross faded with Channel::setPan.<br>
    <li>Multichannel sounds default to all of their sound channels being played on each speaker in order of input.  
    <li>Mix behavior for multichannel sounds can be set with Channel::setPanMatrix.<br>
    <li>Channel::setPanLevels works but rear left / rear right are ignored.<br>
    <br>
    FMOD_SPEAKERMODE_5POINT1<br>
    ---------------------------------------------------------<br>
    This mode is for 5.1 speaker arrangements that have a left/right/center/surround left/surround right and a subwoofer speaker.<br>
    <li>Mono sounds default to the center speaker.  They can be panned with Channel::setPan.<br>
    <li>Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.  
    <li>They can be cross faded with Channel::setPan.<br>
    <li>Multichannel sounds default to all of their sound channels being played on each speaker in order of input.  
    <li>Mix behavior for multichannel sounds can be set with Channel::setPanMatrix.<br>
    <li>Channel::setPanLevels works but rear left / rear right are ignored.<br>
    <br>
    FMOD_SPEAKERMODE_7POINT1<br>
    ------------------------<br>
    This mode is for 7.1 speaker arrangements that have a left/right/center/surround left/surround right/rear left/rear right 
    and a subwoofer speaker.<br>
    <li>Mono sounds default to the center speaker.  They can be panned with Channel::setPan.<br>
    <li>Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.  
    <li>They can be cross faded with Channel::setPan.<br>
    <li>Multichannel sounds default to all of their sound channels being played on each speaker in order of input.  
    <li>Mix behavior for multichannel sounds can be set with Channel::setPanMatrix.<br>
    <li>Channel::setPanLevels works and every parameter is used to set the balance of a sound in any speaker.<br>
    <br>

    [SEE_ALSO]
    System::setSoftwareFormat
    System::getSoftwareFormat
    DSP::setChannelFormat
]
*/
typedef enum
{
    FMOD_SPEAKERMODE_DEFAULT,          /* Default speaker mode based on operating system/output mode.  Windows = control panel setting, Xbox = 5.1, PS3 = 7.1 etc. */
    FMOD_SPEAKERMODE_RAW,              /* There is no specific speakermode.  Sound channels are mapped in order of input to output.  Use System::setSoftwareFormat to specify speaker count. See remarks for more information. */
    FMOD_SPEAKERMODE_MONO,             /* The speakers are monaural. */
    FMOD_SPEAKERMODE_STEREO,           /* The speakers are stereo. */
    FMOD_SPEAKERMODE_QUAD,             /* 4 speaker setup.    This includes front left, front right, surround left, surround right.  */
    FMOD_SPEAKERMODE_SURROUND,         /* 5 speaker setup.    This includes front left, front right, center, surround left, surround right. */
    FMOD_SPEAKERMODE_5POINT1,          /* 5.1 speaker setup.  This includes front left, front right, center, surround left, surround right and an LFE speaker. */
    FMOD_SPEAKERMODE_7POINT1,          /* 7.1 speaker setup.  This includes front left, front right, center, surround left, surround right, back left, back right and an LFE speaker. */
    
    FMOD_SPEAKERMODE_MAX,              /* Maximum number of speaker modes supported. */
    FMOD_SPEAKERMODE_FORCEINT = 65536  /* Makes sure this enum is signed 32bit. */
} FMOD_SPEAKERMODE;


/*
[DEFINE]
[
    [NAME]
    FMOD_MAX_CHANNEL_WIDTH

    [DESCRIPTION]   
    The maximum number of channels per frame of audio supported by audio files, buffers, connections and DSPs. <br>

    [REMARKS]

    [SEE_ALSO]
    FMOD_CHANNELORDER
    FMOD_CREATESOUNDEXINFO
    System::setSoftwareFormat
    System::getDefaultMixMatrix
    ChannelControl::setMixMatrix
    ChannelControl::getMixMatrix
    FMOD::DSP::setChannelFormat
]
*/
#define FMOD_MAX_CHANNEL_WIDTH 32
/* [DEFINE_END] */

/*
[DEFINE]
[
    [NAME]
    FMOD_MAX_LISTENERS

    [DESCRIPTION]
    The maximum number of listeners supported.

    [REMARKS]

    [SEE_ALSO]
    System::set3DNumListeners
    System::set3DListenerAttributes
    System::get3DListenerAttributes
]
*/
#define FMOD_MAX_LISTENERS 5
/* [DEFINE_END] */


/*
[ENUM]
[
    [DESCRIPTION]
    Assigns an enumeration for a speaker index.

    [REMARKS]

    [SEE_ALSO]
    System::setSpeakerPosition
    System::getSpeakerPosition
]
*/
typedef enum
{
    FMOD_SPEAKER_FRONT_LEFT,
    FMOD_SPEAKER_FRONT_RIGHT,
    FMOD_SPEAKER_FRONT_CENTER,
    FMOD_SPEAKER_LOW_FREQUENCY,
    FMOD_SPEAKER_SURROUND_LEFT,
    FMOD_SPEAKER_SURROUND_RIGHT,
    FMOD_SPEAKER_BACK_LEFT,
    FMOD_SPEAKER_BACK_RIGHT,

    FMOD_SPEAKER_MAX,               /* Maximum number of speaker types supported. */
    FMOD_SPEAKER_FORCEINT = 65536   /* Makes sure this enum is signed 32bit. */
} FMOD_SPEAKER;


/*
[DEFINE]
[
    [NAME]
    FMOD_CHANNELMASK

    [DESCRIPTION]   
    These are bitfields to describe for a certain number of channels in a signal, which channels are being represented.<br>
    For example, a signal could be 1 channel, but contain the LFE channel only.<br>

    [REMARKS]
    FMOD_CHANNELMASK_BACK_CENTER is not represented as an output speaker in fmod - but it is encountered in input formats and is down or upmixed appropriately to the nearest speakers.<br>

    [SEE_ALSO]
    DSP::setChannelFormat
    DSP::getChannelFormat
    FMOD_SPEAKERMODE
]
*/
#define FMOD_CHANNELMASK_FRONT_LEFT             0x00000001
#define FMOD_CHANNELMASK_FRONT_RIGHT            0x00000002
#define FMOD_CHANNELMASK_FRONT_CENTER           0x00000004
#define FMOD_CHANNELMASK_LOW_FREQUENCY          0x00000008
#define FMOD_CHANNELMASK_SURROUND_LEFT          0x00000010
#define FMOD_CHANNELMASK_SURROUND_RIGHT         0x00000020
#define FMOD_CHANNELMASK_BACK_LEFT              0x00000040
#define FMOD_CHANNELMASK_BACK_RIGHT             0x00000080
#define FMOD_CHANNELMASK_BACK_CENTER            0x00000100

#define FMOD_CHANNELMASK_MONO                    (FMOD_CHANNELMASK_FRONT_LEFT)
#define FMOD_CHANNELMASK_STEREO                  (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT)
#define FMOD_CHANNELMASK_LRC                     (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER)
#define FMOD_CHANNELMASK_QUAD                    (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_SURROUND_LEFT | FMOD_CHANNELMASK_SURROUND_RIGHT)
#define FMOD_CHANNELMASK_SURROUND                (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER | FMOD_CHANNELMASK_SURROUND_LEFT | FMOD_CHANNELMASK_SURROUND_RIGHT)
#define FMOD_CHANNELMASK_5POINT1                 (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER | FMOD_CHANNELMASK_LOW_FREQUENCY | FMOD_CHANNELMASK_SURROUND_LEFT | FMOD_CHANNELMASK_SURROUND_RIGHT)
#define FMOD_CHANNELMASK_5POINT1_REARS           (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER | FMOD_CHANNELMASK_LOW_FREQUENCY | FMOD_CHANNELMASK_BACK_LEFT | FMOD_CHANNELMASK_BACK_RIGHT)
#define FMOD_CHANNELMASK_7POINT0                 (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER | FMOD_CHANNELMASK_SURROUND_LEFT | FMOD_CHANNELMASK_SURROUND_RIGHT | FMOD_CHANNELMASK_BACK_LEFT | FMOD_CHANNELMASK_BACK_RIGHT)
#define FMOD_CHANNELMASK_7POINT1                 (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER | FMOD_CHANNELMASK_LOW_FREQUENCY | FMOD_CHANNELMASK_SURROUND_LEFT | FMOD_CHANNELMASK_SURROUND_RIGHT | FMOD_CHANNELMASK_BACK_LEFT | FMOD_CHANNELMASK_BACK_RIGHT)
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

    [SEE_ALSO]
    FMOD_CREATESOUNDEXINFO
    FMOD_MAX_CHANNEL_WIDTH
]
*/
typedef enum FMOD_CHANNELORDER
{
    FMOD_CHANNELORDER_DEFAULT,              /* Left, Right, Center, LFE, Surround Left, Surround Right, Back Left, Back Right (see FMOD_SPEAKER enumeration)   */
    FMOD_CHANNELORDER_WAVEFORMAT,           /* Left, Right, Center, LFE, Back Left, Back Right, Surround Left, Surround Right (as per Microsoft .wav WAVEFORMAT structure master order) */
    FMOD_CHANNELORDER_PROTOOLS,             /* Left, Center, Right, Surround Left, Surround Right, LFE */
    FMOD_CHANNELORDER_ALLMONO,              /* Mono, Mono, Mono, Mono, Mono, Mono, ... (each channel all the way up to FMOD_MAX_CHANNEL_WIDTH channels are treated as if they were mono) */
    FMOD_CHANNELORDER_ALLSTEREO,            /* Left, Right, Left, Right, Left, Right, ... (each pair of channels is treated as stereo all the way up to FMOD_MAX_CHANNEL_WIDTH channels) */
    FMOD_CHANNELORDER_ALSA,                 /* Left, Right, Surround Left, Surround Right, Center, LFE (as per Linux ALSA channel order) */

    FMOD_CHANNELORDER_MAX,                  /* Maximum number of channel orderings supported. */
    FMOD_CHANNELORDER_FORCEINT = 65536      /* Makes sure this enum is signed 32bit. */
} FMOD_CHANNELORDER;


/*
[ENUM]
[
    [DESCRIPTION]   
    These are plugin types defined for use with the System::getNumPlugins, 
    System::getPluginInfo and System::unloadPlugin functions.

    [REMARKS]

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
    Initialization flags.  Use them with System::init in the *flags* parameter to change various behavior.  

    [REMARKS]
    Use System::setAdvancedSettings to adjust settings for some of the features that are enabled by these flags.

    [SEE_ALSO]
    System::init
    System::update 
    System::setAdvancedSettings
    Channel::set3DOcclusion
]
*/
#define FMOD_INIT_NORMAL                     0x00000000 /* Initialize normally */
#define FMOD_INIT_STREAM_FROM_UPDATE         0x00000001 /* No stream thread is created internally.  Streams are driven from System::update.  Mainly used with non-realtime outputs. */
#define FMOD_INIT_MIX_FROM_UPDATE            0x00000002 /* Win/PS3/Xbox 360 Only - FMOD Mixer thread is woken up to do a mix when System::update is called rather than waking periodically on its own timer. */
#define FMOD_INIT_3D_RIGHTHANDED             0x00000004 /* FMOD will treat +X as right, +Y as up and +Z as backwards (towards you). */
#define FMOD_INIT_CHANNEL_LOWPASS            0x00000100 /* All FMOD_3D based voices will add a software lowpass filter effect into the DSP chain which is automatically used when Channel::set3DOcclusion is used or the geometry API.   This also causes sounds to sound duller when the sound goes behind the listener, as a fake HRTF style effect.  Use System::setAdvancedSettings to disable or adjust cutoff frequency for this feature. */
#define FMOD_INIT_CHANNEL_DISTANCEFILTER     0x00000200 /* All FMOD_3D based voices will add a software lowpass and highpass filter effect into the DSP chain which will act as a distance-automated bandpass filter. Use System::setAdvancedSettings to adjust the center frequency. */
#define FMOD_INIT_PROFILE_ENABLE             0x00010000 /* Enable TCP/IP based host which allows FMOD Designer or FMOD Profiler to connect to it, and view memory, CPU and the DSP network graph in real-time. */
#define FMOD_INIT_VOL0_BECOMES_VIRTUAL       0x00020000 /* Any sounds that are 0 volume will go virtual and not be processed except for having their positions updated virtually.  Use System::setAdvancedSettings to adjust what volume besides zero to switch to virtual at. */
#define FMOD_INIT_GEOMETRY_USECLOSEST        0x00040000 /* With the geometry engine, only process the closest polygon rather than accumulating all polygons the sound to listener line intersects. */
#define FMOD_INIT_PREFER_DOLBY_DOWNMIX       0x00080000 /* When using FMOD_SPEAKERMODE_5POINT1 with a stereo output device, use the Dolby Pro Logic II downmix algorithm instead of the SRS Circle Surround algorithm. */
#define FMOD_INIT_THREAD_UNSAFE              0x00100000 /* Disables thread safety for API calls. Only use this if FMOD low level is being called from a single thread, and if Studio API is not being used! */
#define FMOD_INIT_PROFILE_METER_ALL          0x00200000 /* Slower, but adds level metering for every single DSP unit in the graph.  Use DSP::setMeteringEnabled to turn meters off individually. */
/* [DEFINE_END] */


/*
[ENUM]
[
    [DESCRIPTION]   
    These definitions describe the type of song being played.

    [REMARKS]

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
    FMOD_SOUND_TYPE_USER,            /* User created sound. */
    FMOD_SOUND_TYPE_WAV,             /* Microsoft WAV. */
    FMOD_SOUND_TYPE_XM,              /* FastTracker 2 XM. */
    FMOD_SOUND_TYPE_XMA,             /* Xbox360 XMA */
    FMOD_SOUND_TYPE_VAG,             /* PlayStation Portable ADPCM VAG format. */
    FMOD_SOUND_TYPE_AUDIOQUEUE,      /* iPhone hardware decoder, supports AAC, ALAC and MP3. extracodecdata is a pointer to an FMOD_AUDIOQUEUE_EXTRACODECDATA structure. */
    FMOD_SOUND_TYPE_XWMA,            /* Xbox360 XWMA */
    FMOD_SOUND_TYPE_BCWAV,           /* 3DS BCWAV container format for DSP ADPCM and PCM */
    FMOD_SOUND_TYPE_AT9,             /* PS4 / PSVita ATRAC 9 format */
    FMOD_SOUND_TYPE_VORBIS,          /* Vorbis */
    FMOD_SOUND_TYPE_MEDIA_FOUNDATION,/* Windows Store Application built in system codecs */
    FMOD_SOUND_TYPE_MEDIACODEC,      /* Android MediaCodec */
    FMOD_SOUND_TYPE_FADPCM,          /* FMOD Adaptive Differential Pulse Code Modulation */

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
    FMOD_SOUND_FORMAT_CELT,             /* Not supported. */
    FMOD_SOUND_FORMAT_AT9,              /* Compressed PSVita ATRAC9 data. */
    FMOD_SOUND_FORMAT_XWMA,             /* Compressed Xbox360 xWMA data. */
    FMOD_SOUND_FORMAT_VORBIS,           /* Compressed Vorbis data. */
    FMOD_SOUND_FORMAT_FADPCM,           /* Compressed FADPCM data. */

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
    <br>
    <b>Xbox 360 memory</b> On Xbox 360 Specifying FMOD_OPENMEMORY_POINT to a virtual memory address will cause FMOD_ERR_INVALID_ADDRESS
    to be returned.  Use physical memory only for this functionality.<br>
    <br>
    FMOD_LOWMEM is used on a sound if you want to minimize the memory overhead, by having FMOD not allocate memory for certain 
    features that are not likely to be used in a game environment.  These are :<br>
    1. Sound::getName functionality is removed.  256 bytes per sound is saved.<br>

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
#define FMOD_DEFAULT                   0x00000000  /* Default for all modes listed below. FMOD_LOOP_OFF, FMOD_2D, FMOD_3D_WORLDRELATIVE, FMOD_3D_INVERSEROLLOFF */
#define FMOD_LOOP_OFF                  0x00000001  /* For non looping sounds. (DEFAULT).  Overrides FMOD_LOOP_NORMAL / FMOD_LOOP_BIDI. */
#define FMOD_LOOP_NORMAL               0x00000002  /* For forward looping sounds. */
#define FMOD_LOOP_BIDI                 0x00000004  /* For bidirectional looping sounds. (only works on software mixed static sounds). */
#define FMOD_2D                        0x00000008  /* Ignores any 3d processing. (DEFAULT). */
#define FMOD_3D                        0x00000010  /* Makes the sound positionable in 3D.  Overrides FMOD_2D. */
#define FMOD_CREATESTREAM              0x00000080  /* Decompress at runtime, streaming from the source provided (ie from disk).  Overrides FMOD_CREATESAMPLE and FMOD_CREATECOMPRESSEDSAMPLE.  Note a stream can only be played once at a time due to a stream only having 1 stream buffer and file handle.  Open multiple streams to have them play concurrently. */
#define FMOD_CREATESAMPLE              0x00000100  /* Decompress at loadtime, decompressing or decoding whole file into memory as the target sample format (ie PCM).  Fastest for playback and most flexible.  */
#define FMOD_CREATECOMPRESSEDSAMPLE    0x00000200  /* Load MP2/MP3/IMAADPCM/Vorbis/AT9 or XMA into memory and leave it compressed.  Vorbis/AT9 encoding only supported in the FSB file format.  During playback the FMOD software mixer will decode it in realtime as a 'compressed sample'.  Overrides FMOD_CREATESAMPLE.  If the sound data is not one of the supported formats, it will behave as if it was created with FMOD_CREATESAMPLE and decode the sound into PCM. */
#define FMOD_OPENUSER                  0x00000400  /* Opens a user created static sample or stream. Use FMOD_CREATESOUNDEXINFO to specify format and/or read callbacks.  If a user created 'sample' is created with no read callback, the sample will be empty.  Use Sound::lock and Sound::unlock to place sound data into the sound if this is the case. */
#define FMOD_OPENMEMORY                0x00000800  /* "name_or_data" will be interpreted as a pointer to memory instead of filename for creating sounds.  Use FMOD_CREATESOUNDEXINFO to specify length.  If used with FMOD_CREATESAMPLE or FMOD_CREATECOMPRESSEDSAMPLE, FMOD duplicates the memory into its own buffers.  Your own buffer can be freed after open.  If used with FMOD_CREATESTREAM, FMOD will stream out of the buffer whose pointer you passed in.  In this case, your own buffer should not be freed until you have finished with and released the stream.*/
#define FMOD_OPENMEMORY_POINT          0x10000000  /* "name_or_data" will be interpreted as a pointer to memory instead of filename for creating sounds.  Use FMOD_CREATESOUNDEXINFO to specify length.  This differs to FMOD_OPENMEMORY in that it uses the memory as is, without duplicating the memory into its own buffers.  Cannot be freed after open, only after Sound::release.   Will not work if the data is compressed and FMOD_CREATECOMPRESSEDSAMPLE is not used. */
#define FMOD_OPENRAW                   0x00001000  /* Will ignore file format and treat as raw pcm.  Use FMOD_CREATESOUNDEXINFO to specify format.  Requires at least defaultfrequency, numchannels and format to be specified before it will open.  Must be little endian data. */
#define FMOD_OPENONLY                  0x00002000  /* Just open the file, dont prebuffer or read.  Good for fast opens for info, or when sound::readData is to be used. */
#define FMOD_ACCURATETIME              0x00004000  /* For System::createSound - for accurate Sound::getLength/Channel::setPosition on VBR MP3, and MOD/S3M/XM/IT/MIDI files.  Scans file first, so takes longer to open. FMOD_OPENONLY does not affect this. */
#define FMOD_MPEGSEARCH                0x00008000  /* For corrupted / bad MP3 files.  This will search all the way through the file until it hits a valid MPEG header.  Normally only searches for 4k. */
#define FMOD_NONBLOCKING               0x00010000  /* For opening sounds and getting streamed subsounds (seeking) asyncronously.  Use Sound::getOpenState to poll the state of the sound as it opens or retrieves the subsound in the background. */
#define FMOD_UNIQUE                    0x00020000  /* Unique sound, can only be played one at a time */
#define FMOD_3D_HEADRELATIVE           0x00040000  /* Make the sound's position, velocity and orientation relative to the listener. */
#define FMOD_3D_WORLDRELATIVE          0x00080000  /* Make the sound's position, velocity and orientation absolute (relative to the world). (DEFAULT) */
#define FMOD_3D_INVERSEROLLOFF         0x00100000  /* This sound will follow the inverse rolloff model where mindistance = full volume, maxdistance = where sound stops attenuating, and rolloff is fixed according to the global rolloff factor.  (DEFAULT) */
#define FMOD_3D_LINEARROLLOFF          0x00200000  /* This sound will follow a linear rolloff model where mindistance = full volume, maxdistance = silence. */
#define FMOD_3D_LINEARSQUAREROLLOFF    0x00400000  /* This sound will follow a linear-square rolloff model where mindistance = full volume, maxdistance = silence. */
#define FMOD_3D_INVERSETAPEREDROLLOFF  0x00800000  /* This sound will follow the inverse rolloff model at distances close to mindistance and a linear-square rolloff close to maxdistance. */
#define FMOD_3D_CUSTOMROLLOFF          0x04000000  /* This sound will follow a rolloff model defined by Sound::set3DCustomRolloff / Channel::set3DCustomRolloff.  */
#define FMOD_3D_IGNOREGEOMETRY         0x40000000  /* Is not affect by geometry occlusion.  If not specified in Sound::setMode, or Channel::setMode, the flag is cleared and it is affected by geometry again. */
/* Unused                              0x01000000  Used to be FMOD_UNICODE */
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
    These values are used with SoundGroup::setMaxAudibleBehavior to determine what happens when more sounds 
    are played than are specified with SoundGroup::setMaxAudible.

    [REMARKS]
    When using FMOD_SOUNDGROUP_BEHAVIOR_MUTE, SoundGroup::setMuteFadeSpeed can be used to stop a sudden transition.  
    Instead, the time specified will be used to cross fade between the sounds that go silent and the ones that become audible.

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

    FMOD_SOUNDGROUP_BEHAVIOR_MAX,               /* Maximum number of sound group behaviors. */
    FMOD_SOUNDGROUP_BEHAVIOR_FORCEINT = 65536   /* Makes sure this enum is signed 32bit. */
} FMOD_SOUNDGROUP_BEHAVIOR;


/*
[ENUM]
[
    [DESCRIPTION]   
    These callback types are used with Channel::setCallback.

    [REMARKS]
    Each callback has commanddata parameters passed as int unique to the type of callback.<br>
    See reference to FMOD_CHANNELCONTROL_CALLBACK to determine what they might mean for each type of callback.<br>
    <br>
    <b>Note!</b>  Currently the user must call System::update for these callbacks to trigger!

    [SEE_ALSO]      
    Channel::setCallback
    ChannelGroup::setCallback
    FMOD_CHANNELCONTROL_CALLBACK
    System::update
]
*/
typedef enum
{
    FMOD_CHANNELCONTROL_CALLBACK_END,                  /* Called when a sound ends. */
    FMOD_CHANNELCONTROL_CALLBACK_VIRTUALVOICE,         /* Called when a voice is swapped out or swapped in. */
    FMOD_CHANNELCONTROL_CALLBACK_SYNCPOINT,            /* Called when a syncpoint is encountered.  Can be from wav file markers. */
    FMOD_CHANNELCONTROL_CALLBACK_OCCLUSION,            /* Called when the channel has its geometry occlusion value calculated.  Can be used to clamp or change the value. */

    FMOD_CHANNELCONTROL_CALLBACK_MAX,                  /* Maximum number of callback types supported. */
    FMOD_CHANNELCONTROL_CALLBACK_FORCEINT = 65536      /* Makes sure this enum is signed 32bit. */
} FMOD_CHANNELCONTROL_CALLBACK_TYPE;


/*
[ENUM]
[
    [DESCRIPTION]   
    These enums denote special types of node within a DSP chain.

    [REMARKS]

    [SEE_ALSO]
    Channel::getDSP
    ChannelGroup::getDSP
    ChannelControl::getNumDSPs
]
*/
typedef enum
{
    FMOD_CHANNELCONTROL_DSP_HEAD = -1,          /* Head of the DSP chain.   Equivalent of index 0. */
    FMOD_CHANNELCONTROL_DSP_FADER = -2,         /* Built in fader DSP. */
    FMOD_CHANNELCONTROL_DSP_PANNER = -3,        /* Built in panner DSP. */
    FMOD_CHANNELCONTROL_DSP_TAIL = -4,          /* Tail of the DSP chain.  Equivalent of the number of dsps minus 1. */

    FMOD_CHANNELCONTROL_DSP_FORCEINT = 65536    /* Makes sure this enum is signed 32bit. */
} FMOD_CHANNELCONTROL_DSP_INDEX;

/*
[ENUM] 
[
    [DESCRIPTION]   
    Used to distinguish the instance type passed into FMOD_ERROR_CALLBACK.

    [REMARKS]
    Cast the instance of FMOD_ERROR_CALLBACK to the appropriate class indicated by this enum.

    [SEE_ALSO]      
]
*/
typedef enum
{
    FMOD_ERRORCALLBACK_INSTANCETYPE_NONE,
    FMOD_ERRORCALLBACK_INSTANCETYPE_SYSTEM,
    FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNEL,
    FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNELGROUP,
    FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNELCONTROL,
    FMOD_ERRORCALLBACK_INSTANCETYPE_SOUND,
    FMOD_ERRORCALLBACK_INSTANCETYPE_SOUNDGROUP,
    FMOD_ERRORCALLBACK_INSTANCETYPE_DSP,
    FMOD_ERRORCALLBACK_INSTANCETYPE_DSPCONNECTION,
    FMOD_ERRORCALLBACK_INSTANCETYPE_GEOMETRY,
    FMOD_ERRORCALLBACK_INSTANCETYPE_REVERB3D,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_SYSTEM,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_EVENTDESCRIPTION,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_EVENTINSTANCE,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_PARAMETERINSTANCE,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_CUEINSTANCE,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_BUS,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_VCA,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_BANK,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_COMMANDREPLAY,

    FMOD_ERRORCALLBACK_INSTANCETYPE_FORCEINT = 65536    /* Makes sure this enum is signed 32bit. */
} FMOD_ERRORCALLBACK_INSTANCETYPE;

/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Structure that is passed into FMOD_SYSTEM_CALLBACK for the FMOD_SYSTEM_CALLBACK_ERROR callback type.

    [REMARKS]
    The instance pointer will be a type corresponding to the instanceType enum.

    [SEE_ALSO]
    FMOD_ERRORCALLBACK_INSTANCETYPE
]
*/
typedef struct
{
    FMOD_RESULT                      result;                     /* Error code result */
    FMOD_ERRORCALLBACK_INSTANCETYPE  instancetype;               /* Type of instance the error occurred on */
    void                            *instance;                   /* Instance pointer */
    const char                      *functionname;               /* Function that the error occurred on */
    const char                      *functionparams;             /* Function parameters that the error ocurred on */
} FMOD_ERRORCALLBACK_INFO;

/*
[DEFINE]
[
    [NAME]
    FMOD_SYSTEM_CALLBACK_TYPE

    [DESCRIPTION]   
    These callback types are used with System::setCallback.

    [REMARKS]
    Each callback has commanddata parameters passed as void* unique to the type of callback.<br>
    See reference to FMOD_SYSTEM_CALLBACK to determine what they might mean for each type of callback.<br>
    <br>
    <b>Note!</b> Using FMOD_SYSTEM_CALLBACK_DEVICELISTCHANGED (Windows only) will disable any automated device ejection/insertion handling by FMOD.  Use this callback to control the behaviour yourself.<br>
    <br>
    <b>Note!</b> Using FMOD_SYSTEM_CALLBACK_DEVICELISTCHANGED (on Mac only) requires the application to be running an event loop which will allow external changes to device list to be detected by FMOD.<br>
    <br>
    <b>Note!</b> The 'system' object pointer will be null for FMOD_SYSTEM_CALLBACK_MEMORYALLOCATIONFAILED callback.

    [SEE_ALSO]      
    System::setCallback
    System::update
    DSP::addInput
]
*/
#define FMOD_SYSTEM_CALLBACK_DEVICELISTCHANGED      0x00000001  /* Called from System::update when the enumerated list of devices has changed. */
#define FMOD_SYSTEM_CALLBACK_DEVICELOST             0x00000002  /* Called from System::update when an output device has been lost due to control panel parameter changes and FMOD cannot automatically recover. */
#define FMOD_SYSTEM_CALLBACK_MEMORYALLOCATIONFAILED 0x00000004  /* Called directly when a memory allocation fails somewhere in FMOD.  (NOTE - 'system' will be NULL in this callback type.)*/
#define FMOD_SYSTEM_CALLBACK_THREADCREATED          0x00000008  /* Called directly when a thread is created. */
#define FMOD_SYSTEM_CALLBACK_BADDSPCONNECTION       0x00000010  /* Called when a bad connection was made with DSP::addInput. Usually called from mixer thread because that is where the connections are made.  */
#define FMOD_SYSTEM_CALLBACK_PREMIX                 0x00000020  /* Called each tick before a mix update happens. */
#define FMOD_SYSTEM_CALLBACK_POSTMIX                0x00000040  /* Called each tick after a mix update happens. */
#define FMOD_SYSTEM_CALLBACK_ERROR                  0x00000080  /* Called when each API function returns an error code, including delayed async functions. */
#define FMOD_SYSTEM_CALLBACK_MIDMIX                 0x00000100  /* Called each tick in mix update after clocks have been updated before the main mix occurs. */
#define FMOD_SYSTEM_CALLBACK_THREADDESTROYED        0x00000200  /* Called directly when a thread is destroyed. */
#define FMOD_SYSTEM_CALLBACK_PREUPDATE              0x00000400  /* Called at start of System::update function. */
#define FMOD_SYSTEM_CALLBACK_POSTUPDATE             0x00000800  /* Called at end of System::update function. */

/* [DEFINE_END] */


/* 
    FMOD Callbacks
*/
typedef FMOD_RESULT (F_CALLBACK *FMOD_DEBUG_CALLBACK)           (FMOD_DEBUG_FLAGS flags, const char *file, int line, const char *func, const char *message);

typedef FMOD_RESULT (F_CALLBACK *FMOD_SYSTEM_CALLBACK)          (FMOD_SYSTEM *system, FMOD_SYSTEM_CALLBACK_TYPE type, void *commanddata1, void *commanddata2, void *userdata);

typedef FMOD_RESULT (F_CALLBACK *FMOD_CHANNELCONTROL_CALLBACK)  (FMOD_CHANNELCONTROL *channelcontrol, FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype, void *commanddata1, void *commanddata2);

typedef FMOD_RESULT (F_CALLBACK *FMOD_SOUND_NONBLOCK_CALLBACK)  (FMOD_SOUND *sound, FMOD_RESULT result);
typedef FMOD_RESULT (F_CALLBACK *FMOD_SOUND_PCMREAD_CALLBACK)   (FMOD_SOUND *sound, void *data, unsigned int datalen);
typedef FMOD_RESULT (F_CALLBACK *FMOD_SOUND_PCMSETPOS_CALLBACK) (FMOD_SOUND *sound, int subsound, unsigned int position, FMOD_TIMEUNIT postype);

typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_OPEN_CALLBACK)       (const char *name, unsigned int *filesize, void **handle, void *userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_CLOSE_CALLBACK)      (void *handle, void *userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_READ_CALLBACK)       (void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread, void *userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_SEEK_CALLBACK)       (void *handle, unsigned int pos, void *userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_ASYNCREAD_CALLBACK)  (FMOD_ASYNCREADINFO *info, void *userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_ASYNCCANCEL_CALLBACK)(FMOD_ASYNCREADINFO *info, void *userdata);

typedef void *      (F_CALLBACK *FMOD_MEMORY_ALLOC_CALLBACK)    (unsigned int size, FMOD_MEMORY_TYPE type, const char *sourcestr);
typedef void *      (F_CALLBACK *FMOD_MEMORY_REALLOC_CALLBACK)  (void *ptr, unsigned int size, FMOD_MEMORY_TYPE type, const char *sourcestr);
typedef void        (F_CALLBACK *FMOD_MEMORY_FREE_CALLBACK)     (void *ptr, FMOD_MEMORY_TYPE type, const char *sourcestr);

typedef float       (F_CALLBACK *FMOD_3D_ROLLOFF_CALLBACK)      (FMOD_CHANNELCONTROL *channelcontrol, float distance);




/*
[ENUM]
[
    [DESCRIPTION]   
    List of interpolation types that the FMOD Studio software mixer supports.  

    [REMARKS]
    The default resampler type is FMOD_DSP_RESAMPLER_LINEAR.<br>
    Use System::setAdvancedSettings and the resamplerMethod member to tell FMOD the resampling quality you require for sample rate conversion during sound playback.

    [SEE_ALSO]      
    System::setAdvancedSettings
    System::setAdvancedSettings
    FMOD_ADVANCEDSETINGS
]
*/
typedef enum
{
    FMOD_DSP_RESAMPLER_DEFAULT,         /* Default interpolation method.  Currently equal to FMOD_DSP_RESAMPLER_LINEAR. */
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
    List of connection types between 2 DSP nodes.

    [REMARKS]
    FMOD_DSP_CONNECTION_TYPE_STANDARD<br>
    ----------------------------------<br>
    Default DSPConnection type.  Audio is mixed from the input to the output DSP's audible buffer, meaning it will be part of the audible signal.  A standard connection will execute its input DSP if it has not been executed before.<br>
    <br>
    FMOD_DSP_CONNECTION_TYPE_SIDECHAIN<br>
    ----------------------------------<br>
    Sidechain DSPConnection type.  Audio is mixed from the input to the output DSP's sidechain buffer, meaning it will NOT be part of the audible signal.  A sidechain connection will execute its input DSP if it has not been executed before.<br>
    The purpose of the seperate sidechain buffer in a DSP, is so that the DSP effect can privately access for analysis purposes.  An example of use in this case, could be a compressor which analyzes the signal, to control its own effect parameters (ie a compression level or gain).<br>
    <br>
    For the effect developer, to accept sidechain data, the sidechain data will appear in the FMOD_DSP_STATE struct which is passed into the read callback of a DSP unit.<br>
    FMOD_DSP_STATE::sidechaindata and FMOD_DSP::sidechainchannels will hold the mixed result of any sidechain data flowing into it.<br>
    <br>
    FMOD_DSP_CONNECTION_TYPE_SEND<br>
    -----------------------------<br>
    Send DSPConnection type.  Audio is mixed from the input to the output DSP's audible buffer, meaning it will be part of the audible signal.  A send connection will NOT execute its input DSP if it has not been executed before.<br>
    A send connection will only read what exists at the input's buffer at the time of executing the output DSP unit (which can be considered the 'return')<br>
    <br>
    FMOD_DSP_CONNECTION_TYPE_SEND_SIDECHAIN<br>
    ---------------------------------------<br>
    Send sidechain DSPConnection type.  Audio is mixed from the input to the output DSP's sidechain buffer, meaning it will NOT be part of the audible signal.  A send sidechain connection will NOT execute its input DSP if it has not been executed before.<br>
    A send sidechain connection will only read what exists at the input's buffer at the time of executing the output DSP unit (which can be considered the 'sidechain return').
    <br>
    For the effect developer, to accept sidechain data, the sidechain data will appear in the FMOD_DSP_STATE struct which is passed into the read callback of a DSP unit.<br>
    FMOD_DSP_STATE::sidechaindata and FMOD_DSP::sidechainchannels will hold the mixed result of any sidechain data flowing into it.

    [SEE_ALSO]      
    DSP::addInput
    DSPConnection::getType
]
*/
typedef enum
{
    FMOD_DSPCONNECTION_TYPE_STANDARD,          /* Default connection type.         Audio is mixed from the input to the output DSP's audible buffer.  */
    FMOD_DSPCONNECTION_TYPE_SIDECHAIN,         /* Sidechain connection type.       Audio is mixed from the input to the output DSP's sidechain buffer.  */
    FMOD_DSPCONNECTION_TYPE_SEND,              /* Send connection type.            Audio is mixed from the input to the output DSP's audible buffer, but the input is NOT executed, only copied from.  A standard connection or sidechain needs to make an input execute to generate data. */
    FMOD_DSPCONNECTION_TYPE_SEND_SIDECHAIN,    /* Send sidechain connection type.  Audio is mixed from the input to the output DSP's sidechain buffer, but the input is NOT executed, only copied from.  A standard connection or sidechain needs to make an input execute to generate data. */

    FMOD_DSPCONNECTION_TYPE_MAX,               /* Maximum number of DSP connection types supported. */
    FMOD_DSPCONNECTION_TYPE_FORCEINT = 65536   /* Makes sure this enum is signed 32bit. */
} FMOD_DSPCONNECTION_TYPE;


/*
[ENUM]
[
    [DESCRIPTION]   
    List of tag types that could be stored within a sound.  These include id3 tags, metadata from netstreams and vorbis/asf data.

    [REMARKS]

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
[STRUCTURE] 
[
    [DESCRIPTION]   
    Structure describing a piece of tag data.

    [REMARKS]
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>

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
[DEFINE]
[
    [NAME]
    FMOD_TIMEUNIT

    [DESCRIPTION]   
    List of time types that can be returned by Sound::getLength and used with Channel::setPosition or Channel::getPosition.

    [REMARKS]
    Do not combine flags except FMOD_TIMEUNIT_BUFFERED.

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
#define FMOD_TIMEUNIT_BUFFERED          0x10000000  /* Time value as seen by buffered stream.  This is always ahead of audible time, and is only used for processing. */
/* [DEFINE_END] */

/*
[DEFINE]
[
    [NAME]
    FMOD_PORT_INDEX

    [DESCRIPTION]       

    [REMARKS]  

    [SEE_ALSO]      
    System::AttachChannelGroupToPort
]
*/
#define FMOD_PORT_INDEX_NONE            -1ull       /* Use when a port index is not required */
/* [DEFINE_END] */


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Use this structure with System::createSound when more control is needed over loading.
    The possible reasons to use this with System::createSound are:

    - Loading a file from memory.
    - Loading a file from within another larger (possibly wad/pak) file, by giving the loader an offset and length.
    - To create a user created / non file based sound.
    - To specify a starting subsound to seek to within a multi-sample sounds (ie FSB/DLS) when created as a stream.
    - To specify which subsounds to load for multi-sample sounds (ie FSB/DLS) so that memory is saved and only a subset is actually loaded/read from disk.
    - To specify 'piggyback' read and seek callbacks for capture of sound data as fmod reads and decodes it.  Useful for ripping decoded PCM data from sounds as they are loaded / played.
    - To specify a MIDI DLS sample set file to load when opening a MIDI file.

    See below on what members to fill for each of the above types of sound you want to create.

    [REMARKS]
    This structure is optional!  Specify 0 or NULL in System::createSound if you don't need it!

    <u>Loading a file from memory.</u>

    - Create the sound using the FMOD_OPENMEMORY flag.
    - Mandatory.  Specify 'length' for the size of the memory block in bytes.
    - Other flags are optional.

    <u>Loading a file from within another larger (possibly wad/pak) file, by giving the loader an offset and length.</u>

    - Mandatory.  Specify 'fileoffset' and 'length'.
    - Other flags are optional.

    <u>To create a user created / non file based sound.</u>

    - Create the sound using the FMOD_OPENUSER flag.
    - Mandatory.  Specify 'defaultfrequency, 'numchannels' and 'format'.
    - Other flags are optional.

    <u>To specify a starting subsound to seek to and flush with, within a multi-sample stream (ie FSB/DLS).</u>

    - Mandatory.  Specify 'initialsubsound'.

    <u>To specify which subsounds to load for multi-sample sounds (ie FSB/DLS) so that memory is saved and only a subset is actually loaded/read from disk.</u>

    - Mandatory.  Specify 'inclusionlist' and 'inclusionlistnum'.

    <u>To specify 'piggyback' read and seek callbacks for capture of sound data as fmod reads and decodes it.  Useful for ripping decoded PCM data from sounds as they are loaded / played.</u>

    - Mandatory.  Specify 'pcmreadcallback' and 'pcmseekcallback'.

    <u>To specify a MIDI DLS sample set file to load when opening a MIDI file.</u>

    - Mandatory.  Specify 'dlsname'.

    Setting the 'decodebuffersize' is for cpu intensive codecs that may be causing stuttering, not file intensive codecs (ie those from CD or netstreams) which are normally 
    altered with System::setStreamBufferSize.  As an example of cpu intensive codecs, an mp3 file will take more cpu to decode than a PCM wav file.

    If you have a stuttering effect, then it is using more cpu than the decode buffer playback rate can keep up with.  Increasing the decode buffersize will most likely solve this problem.

    FSB codec.  If inclusionlist and numsubsounds are used together, this will trigger a special mode where subsounds are shuffled down to save memory.  (useful for large FSB 
    files where you only want to load 1 sound).  There will be no gaps, ie no null subsounds.  As an example, if there are 10,000 subsounds and there is an inclusionlist with only 1 entry, 
    and numsubsounds = 1, then subsound 0 will be that entry, and there will only be the memory allocated for 1 subsound.  Previously there would still be 10,000 subsound pointers and other
    associated codec entries allocated along with it multiplied by 10,000.

    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.

    [SEE_ALSO]
    System::createSound
    System::setStreamBufferSize
    FMOD_MODE
    FMOD_SOUND_FORMAT
    FMOD_SOUND_TYPE
    FMOD_CHANNELMASK
    FMOD_CHANNELORDER
    FMOD_MAX_CHANNEL_WIDTH
]
*/
typedef struct FMOD_CREATESOUNDEXINFO
{
    int                            cbsize;             /* [w] Size of this structure.  This is used so the structure can be expanded in the future and still work on older versions of FMOD Studio. */
    unsigned int                   length;             /* [w] Optional. Specify 0 to ignore. Number of bytes to load starting at 'fileoffset', or size of sound to create (if FMOD_OPENUSER is used).  Required if loading from memory.  If 0 is specified, then it will use the size of the file (unless loading from memory then an error will be returned). */
    unsigned int                   fileoffset;         /* [w] Optional. Specify 0 to ignore. Offset from start of the file to start loading from.  This is useful for loading files from inside big data files. */
    int                            numchannels;        /* [w] Optional. Specify 0 to ignore. Number of channels in a sound mandatory if FMOD_OPENUSER or FMOD_OPENRAW is used.  Can be specified up to FMOD_MAX_CHANNEL_WIDTH. */
    int                            defaultfrequency;   /* [w] Optional. Specify 0 to ignore. Default frequency of sound in Hz, mandatory if FMOD_OPENUSER or FMOD_OPENRAW is used.  Other formats use the frequency determined by the file format. */
    FMOD_SOUND_FORMAT              format;             /* [w] Optional. Specify 0 or FMOD_SOUND_FORMAT_NONE to ignore. Format of the sound, mandatory if FMOD_OPENUSER or FMOD_OPENRAW is used.  Other formats use the format determined by the file format.   */
    unsigned int                   decodebuffersize;   /* [w] Optional. Specify 0 to ignore. For streams.  This determines the size of the double buffer (in PCM samples) that a stream uses.  Use this for user created streams if you want to determine the size of the callback buffer passed to you.  Specify 0 to use FMOD's default size which is currently equivalent to 400ms of the sound format created/loaded. */
    int                            initialsubsound;    /* [w] Optional. Specify 0 to ignore. In a multi-sample file format such as .FSB/.DLS, specify the initial subsound to seek to, only if FMOD_CREATESTREAM is used. */
    int                            numsubsounds;       /* [w] Optional. Specify 0 to ignore or have no subsounds.  In a sound created with FMOD_OPENUSER, specify the number of subsounds that are accessable with Sound::getSubSound.  If not created with FMOD_OPENUSER, this will limit the number of subsounds loaded within a multi-subsound file.  If using FSB, then if FMOD_CREATESOUNDEXINFO::inclusionlist is used, this will shuffle subsounds down so that there are not any gaps.  It will mean that the indices of the sounds will be different. */
    int                           *inclusionlist;      /* [w] Optional. Specify 0 to ignore. In a multi-sample format such as .FSB/.DLS it may be desirable to specify only a subset of sounds to be loaded out of the whole file.  This is an array of subsound indices to load into memory when created. */
    int                            inclusionlistnum;   /* [w] Optional. Specify 0 to ignore. This is the number of integers contained within the inclusionlist array. */
    FMOD_SOUND_PCMREAD_CALLBACK    pcmreadcallback;    /* [w] Optional. Specify 0 to ignore. Callback to 'piggyback' on FMOD's read functions and accept or even write PCM data while FMOD is opening the sound.  Used for user sounds created with FMOD_OPENUSER or for capturing decoded data as FMOD reads it. */
    FMOD_SOUND_PCMSETPOS_CALLBACK  pcmsetposcallback;  /* [w] Optional. Specify 0 to ignore. Callback for when the user calls a seeking function such as Channel::setTime or Channel::setPosition within a multi-sample sound, and for when it is opened.*/
    FMOD_SOUND_NONBLOCK_CALLBACK   nonblockcallback;   /* [w] Optional. Specify 0 to ignore. Callback for successful completion, or error while loading a sound that used the FMOD_NONBLOCKING flag.  Also called duing seeking, when setPosition is called or a stream is restarted. */
    const char                    *dlsname;            /* [w] Optional. Specify 0 to ignore. Filename for a DLS sample set when loading a MIDI file. If not specified, on Windows it will attempt to open /windows/system32/drivers/gm.dls or /windows/system32/drivers/etc/gm.dls, on Mac it will attempt to load /System/Library/Components/CoreAudio.component/Contents/Resources/gs_instruments.dls, otherwise the MIDI will fail to open. Current DLS support is for level 1 of the specification. */
    const char                    *encryptionkey;      /* [w] Optional. Specify 0 to ignore. Key for encrypted FSB file.  Without this key an encrypted FSB file will not load. */
    int                            maxpolyphony;       /* [w] Optional. Specify 0 to ignore. For sequenced formats with dynamic channel allocation such as .MID and .IT, this specifies the maximum voice count allowed while playing.  .IT defaults to 64.  .MID defaults to 32. */
    void                          *userdata;           /* [w] Optional. Specify 0 to ignore. This is user data to be attached to the sound during creation.  Access via Sound::getUserData.  Note: This is not passed to FMOD_FILE_OPEN_CALLBACK - use fileuserdata for that. */
    FMOD_SOUND_TYPE                suggestedsoundtype; /* [w] Optional. Specify 0 or FMOD_SOUND_TYPE_UNKNOWN to ignore.  Instead of scanning all codec types, use this to speed up loading by making it jump straight to this codec. */
    FMOD_FILE_OPEN_CALLBACK        fileuseropen;       /* [w] Optional. Specify 0 to ignore. Callback for opening this file. */
    FMOD_FILE_CLOSE_CALLBACK       fileuserclose;      /* [w] Optional. Specify 0 to ignore. Callback for closing this file. */
    FMOD_FILE_READ_CALLBACK        fileuserread;       /* [w] Optional. Specify 0 to ignore. Callback for reading from this file. */
    FMOD_FILE_SEEK_CALLBACK        fileuserseek;       /* [w] Optional. Specify 0 to ignore. Callback for seeking within this file. */
    FMOD_FILE_ASYNCREAD_CALLBACK   fileuserasyncread;  /* [w] Optional. Specify 0 to ignore. Callback for seeking within this file. */
    FMOD_FILE_ASYNCCANCEL_CALLBACK fileuserasynccancel;/* [w] Optional. Specify 0 to ignore. Callback for seeking within this file. */
    void                          *fileuserdata;       /* [w] Optional. Specify 0 to ignore. User data to be passed into the file callbacks. */
    FMOD_CHANNELORDER              channelorder;       /* [w] Optional. Specify 0 to ignore. Use this to differ the way fmod maps multichannel sounds to speakers.  See FMOD_CHANNELORDER for more. */
    FMOD_CHANNELMASK               channelmask;        /* [w] Optional. Specify 0 to ignore. Use this to specify which channels map to which speakers.  See FMOD_CHANNELMASK for more. */
    FMOD_SOUNDGROUP               *initialsoundgroup;  /* [w] Optional. Specify 0 to ignore. Specify a sound group if required, to put sound in as it is created. */
    unsigned int                   initialseekposition;/* [w] Optional. Specify 0 to ignore. For streams. Specify an initial position to seek the stream to. */
    FMOD_TIMEUNIT                  initialseekpostype; /* [w] Optional. Specify 0 to ignore. For streams. Specify the time unit for the position set in initialseekposition. */
    int                            ignoresetfilesystem;/* [w] Optional. Specify 0 to ignore. Set to 1 to use fmod's built in file system. Ignores setFileSystem callbacks and also FMOD_CREATESOUNEXINFO file callbacks.  Useful for specific cases where you don't want to use your own file system but want to use fmod's file system (ie net streaming). */
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
    Note that integer values that typically range from -10,000 to 1000 are represented in decibels, 
    and are of a logarithmic scale, not linear, wheras float values are always linear.<br>
    <br>
    The numerical values listed below are the maximum, minimum and default values for each variable respectively.<br>
    <br>
    Hardware voice / Platform Specific reverb support.<br>
    WII   See FMODWII.H for hardware specific reverb functionality.<br>
    3DS   See FMOD3DS.H for hardware specific reverb functionality.<br>
    PSP   See FMODWII.H for hardware specific reverb functionality.<br>
    <br>
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>
    Members marked with [r/w] are either read or write depending on if you are using System::setReverbProperties (w) or System::getReverbProperties (r).

    [SEE_ALSO]
    System::setReverbProperties
    System::getReverbProperties
    FMOD_REVERB_PRESETS
]
*/
typedef struct FMOD_REVERB_PROPERTIES
{                                   /*       MIN    MAX     DEFAULT DESCRIPTION */
    float        DecayTime;         /* [r/w] 0.0    20000.0 1500.0  Reverberation decay time in ms                                        */
    float        EarlyDelay;        /* [r/w] 0.0    300.0   7.0     Initial reflection delay time                                         */
    float        LateDelay;         /* [r/w] 0.0    100     11.0    Late reverberation delay time relative to initial reflection          */
    float        HFReference;       /* [r/w] 20.0   20000.0 5000    Reference high frequency (hz)                                         */
    float        HFDecayRatio;      /* [r/w] 10.0   100.0   50.0    High-frequency to mid-frequency decay time ratio                      */
    float        Diffusion;         /* [r/w] 0.0    100.0   100.0   Value that controls the echo density in the late reverberation decay. */
    float        Density;           /* [r/w] 0.0    100.0   100.0   Value that controls the modal density in the late reverberation decay */
    float        LowShelfFrequency; /* [r/w] 20.0   1000.0  250.0   Reference low frequency (hz)                                          */
    float        LowShelfGain;      /* [r/w] -36.0  12.0    0.0     Relative room effect level at low frequencies                         */
    float        HighCut;           /* [r/w] 20.0   20000.0 20000.0 Relative room effect level at high frequencies                        */
    float        EarlyLateMix;      /* [r/w] 0.0    100.0   50.0    Early reflections level relative to room effect                       */
    float        WetLevel;          /* [r/w] -80.0  20.0    -6.0    Room effect level (at mid frequencies)                                */
} FMOD_REVERB_PROPERTIES;


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

    [SEE_ALSO]
    System::setReverbProperties
    System::getReverbProperties
]
*/
/*                                      Decay     LateDly    HFDecay    Densty   LoGain    E/L-Mix
                                             EarlyDly    HFRef     Diffus   LoFreq     HiCut      WetLvl */
#define FMOD_PRESET_OFF              {  1000,    7,  11, 5000, 100, 100, 100, 250, 0,    20,  96, -80.0f }
#define FMOD_PRESET_GENERIC          {  1500,    7,  11, 5000,  83, 100, 100, 250, 0, 14500,  96,  -8.0f }
#define FMOD_PRESET_PADDEDCELL       {   170,    1,   2, 5000,  10, 100, 100, 250, 0,   160,  84,  -7.8f }
#define FMOD_PRESET_ROOM             {   400,    2,   3, 5000,  83, 100, 100, 250, 0,  6050,  88,  -9.4f }
#define FMOD_PRESET_BATHROOM         {  1500,    7,  11, 5000,  54, 100,  60, 250, 0,  2900,  83,   0.5f }
#define FMOD_PRESET_LIVINGROOM       {   500,    3,   4, 5000,  10, 100, 100, 250, 0,   160,  58, -19.0f }
#define FMOD_PRESET_STONEROOM        {  2300,   12,  17, 5000,  64, 100, 100, 250, 0,  7800,  71,  -8.5f }
#define FMOD_PRESET_AUDITORIUM       {  4300,   20,  30, 5000,  59, 100, 100, 250, 0,  5850,  64, -11.7f }
#define FMOD_PRESET_CONCERTHALL      {  3900,   20,  29, 5000,  70, 100, 100, 250, 0,  5650,  80,  -9.8f }
#define FMOD_PRESET_CAVE             {  2900,   15,  22, 5000, 100, 100, 100, 250, 0, 20000,  59, -11.3f }
#define FMOD_PRESET_ARENA            {  7200,   20,  30, 5000,  33, 100, 100, 250, 0,  4500,  80,  -9.6f }
#define FMOD_PRESET_HANGAR           { 10000,   20,  30, 5000,  23, 100, 100, 250, 0,  3400,  72,  -7.4f }
#define FMOD_PRESET_CARPETTEDHALLWAY {   300,    2,  30, 5000,  10, 100, 100, 250, 0,   500,  56, -24.0f }
#define FMOD_PRESET_HALLWAY          {  1500,    7,  11, 5000,  59, 100, 100, 250, 0,  7800,  87,  -5.5f }
#define FMOD_PRESET_STONECORRIDOR    {   270,   13,  20, 5000,  79, 100, 100, 250, 0,  9000,  86,  -6.0f }
#define FMOD_PRESET_ALLEY            {  1500,    7,  11, 5000,  86, 100, 100, 250, 0,  8300,  80,  -9.8f }
#define FMOD_PRESET_FOREST           {  1500,  162,  88, 5000,  54,  79, 100, 250, 0,   760,  94, -12.3f }
#define FMOD_PRESET_CITY             {  1500,    7,  11, 5000,  67,  50, 100, 250, 0,  4050,  66, -26.0f }
#define FMOD_PRESET_MOUNTAINS        {  1500,  300, 100, 5000,  21,  27, 100, 250, 0,  1220,  82, -24.0f }
#define FMOD_PRESET_QUARRY           {  1500,   61,  25, 5000,  83, 100, 100, 250, 0,  3400, 100,  -5.0f }
#define FMOD_PRESET_PLAIN            {  1500,  179, 100, 5000,  50,  21, 100, 250, 0,  1670,  65, -28.0f }
#define FMOD_PRESET_PARKINGLOT       {  1700,    8,  12, 5000, 100, 100, 100, 250, 0, 20000,  56, -19.5f }
#define FMOD_PRESET_SEWERPIPE        {  2800,   14,  21, 5000,  14,  80,  60, 250, 0,  3400,  66,   1.2f }
#define FMOD_PRESET_UNDERWATER       {  1500,    7,  11, 5000,  10, 100, 100, 250, 0,   500,  92,   7.0f }
/* [DEFINE_END] */


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Settings for advanced features like configuring memory and cpu usage for the FMOD_CREATECOMPRESSEDSAMPLE feature.

    [REMARKS]
    maxMPEGCodecs / maxADPCMCodecs / maxXMACodecs will determine the maximum cpu usage of playing realtime samples.  Use this to lower potential excess cpu usage and also control memory usage.<br>
    <br>
    maxPCMCodecs is for use with PS3 only. It will determine the maximum number of PCM voices that can be played at once. This includes streams of any format and all sounds created
    *without* the FMOD_CREATECOMPRESSEDSAMPLE flag.
    <br>
    Memory will be allocated for codecs 'up front' (during System::init) if these values are specified as non zero.  If any are zero, it allocates memory for the codec whenever a file of the type in question is loaded.  So if maxMPEGCodecs is 0 for example, it will allocate memory for the mpeg codecs the first time an mp3 is loaded or an mp3 based .FSB file is loaded.<br>
    <br>
    Due to inefficient encoding techniques on certain .wav based ADPCM files, FMOD can can need an extra 29720 bytes per codec.  This means for lowest memory consumption.  Use FSB as it uses an optimal/small ADPCM block size.<br>
    <br>
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>
    Members marked with [r/w] are either read or write depending on if you are using System::setAdvancedSettings (w) or System::getAdvancedSettings (r).

    [SEE_ALSO]
    System::setAdvancedSettings
    System::getAdvancedSettings
    System::init
    FMOD_MODE
]
*/
typedef struct FMOD_ADVANCEDSETTINGS
{                       
    int                 cbSize;                     /* [w]   Size of this structure.  Use sizeof(FMOD_ADVANCEDSETTINGS)  NOTE: This must be set before calling System::getAdvancedSettings or System::setAdvancedSettings! */
    int                 maxMPEGCodecs;              /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_CREATECOMPRESSEDSAMPLE only.  MPEG   codecs consume 30,528 bytes per instance and this number will determine how many MPEG   channels can be played simultaneously. Default = 32. */
    int                 maxADPCMCodecs;             /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_CREATECOMPRESSEDSAMPLE only.  ADPCM  codecs consume  3,128 bytes per instance and this number will determine how many ADPCM  channels can be played simultaneously. Default = 32. */
    int                 maxXMACodecs;               /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_CREATECOMPRESSEDSAMPLE only.  XMA    codecs consume 14,836 bytes per instance and this number will determine how many XMA    channels can be played simultaneously. Default = 32. */
    int                 maxVorbisCodecs;            /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_CREATECOMPRESSEDSAMPLE only.  Vorbis codecs consume 23,256 bytes per instance and this number will determine how many Vorbis channels can be played simultaneously. Default = 32. */    
    int                 maxAT9Codecs;               /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_CREATECOMPRESSEDSAMPLE only.  AT9    codecs consume  8,720 bytes per instance and this number will determine how many AT9    channels can be played simultaneously. Default = 32. */    
    int                 maxFADPCMCodecs;            /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_CREATECOMPRESSEDSAMPLE only.  This number will determine how many FADPCM channels can be played simultaneously. Default = 32. */
    int                 maxPCMCodecs;               /* [r/w] Optional. Specify 0 to ignore. For use with PS3 only.                          PCM    codecs consume 12,672 bytes per instance and this number will determine how many streams and PCM voices can be played simultaneously. Default = 16. */
    int                 ASIONumChannels;            /* [r/w] Optional. Specify 0 to ignore. Number of channels available on the ASIO device. */
    char              **ASIOChannelList;            /* [r/w] Optional. Specify 0 to ignore. Pointer to an array of strings (number of entries defined by ASIONumChannels) with ASIO channel names. */
    FMOD_SPEAKER       *ASIOSpeakerList;            /* [r/w] Optional. Specify 0 to ignore. Pointer to a list of speakers that the ASIO channels map to.  This can be called after System::init to remap ASIO output. */
    float               HRTFMinAngle;               /* [r/w] Optional.                      For use with FMOD_INIT_HRTF_LOWPASS.  The angle range (0-360) of a 3D sound in relation to the listener, at which the HRTF function begins to have an effect. 0 = in front of the listener. 180 = from 90 degrees to the left of the listener to 90 degrees to the right. 360 = behind the listener. Default = 180.0. */
    float               HRTFMaxAngle;               /* [r/w] Optional.                      For use with FMOD_INIT_HRTF_LOWPASS.  The angle range (0-360) of a 3D sound in relation to the listener, at which the HRTF function has maximum effect. 0 = front of the listener. 180 = from 90 degrees to the left of the listener to 90 degrees to the right. 360 = behind the listener. Default = 360.0. */
    float               HRTFFreq;                   /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_INIT_HRTF_LOWPASS.  The cutoff frequency of the HRTF's lowpass filter function when at maximum effect. (i.e. at HRTFMaxAngle).  Default = 4000.0. */
    float               vol0virtualvol;             /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_INIT_VOL0_BECOMES_VIRTUAL.  If this flag is used, and the volume is below this, then the sound will become virtual.  Use this value to raise the threshold to a different point where a sound goes virtual. */
    unsigned int        defaultDecodeBufferSize;    /* [r/w] Optional. Specify 0 to ignore. For streams. This determines the default size of the double buffer (in milliseconds) that a stream uses.  Default = 400ms */
    unsigned short      profilePort;                /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_INIT_PROFILE_ENABLE.  Specify the port to listen on for connections by the profiler application. */
    unsigned int        geometryMaxFadeTime;        /* [r/w] Optional. Specify 0 to ignore. The maximum time in miliseconds it takes for a channel to fade to the new level when its occlusion changes. */
    float               distanceFilterCenterFreq;   /* [r/w] Optional. Specify 0 to ignore. For use with FMOD_INIT_DISTANCE_FILTERING.  The default center frequency in Hz for the distance filtering effect. Default = 1500.0. */
    int                 reverb3Dinstance;           /* [r/w] Optional. Specify 0 to ignore. Out of 0 to 3, 3d reverb spheres will create a phyical reverb unit on this instance slot.  See FMOD_REVERB_PROPERTIES. */
    int                 DSPBufferPoolSize;          /* [r/w] Optional. Specify 0 to ignore. Number of buffers in DSP buffer pool.  Each buffer will be DSPBlockSize * sizeof(float) * SpeakerModeChannelCount.  ie 7.1 @ 1024 DSP block size = 8 * 1024 * 4 = 32kb.  Default = 8. */
    unsigned int        stackSizeStream;            /* [r/w] Optional. Specify 0 to ignore. Specify the stack size for the FMOD Stream thread in bytes.  Useful for custom codecs that use excess stack.  Default 49,152 (48kb) */
    unsigned int        stackSizeNonBlocking;       /* [r/w] Optional. Specify 0 to ignore. Specify the stack size for the FMOD_NONBLOCKING loading thread.  Useful for custom codecs that use excess stack.  Default 65,536 (64kb) */
    unsigned int        stackSizeMixer;             /* [r/w] Optional. Specify 0 to ignore. Specify the stack size for the FMOD mixer thread.  Useful for custom dsps that use excess stack.  Default 49,152 (48kb) */
    FMOD_DSP_RESAMPLER  resamplerMethod;            /* [r/w] Optional. Specify 0 to ignore. Resampling method used with fmod's software mixer.  See FMOD_DSP_RESAMPLER for details on methods. */
    unsigned int        commandQueueSize;           /* [r/w] Optional. Specify 0 to ignore. Specify the command queue size for thread safe processing.  Default 2048 (2kb) */
    unsigned int        randomSeed;                 /* [r/w] Optional. Specify 0 to ignore. Seed value that FMOD will use to initialize its internal random number generators. */
} FMOD_ADVANCEDSETTINGS;


/*
[DEFINE] 
[
    [NAME] 
    FMOD_DRIVER_STATE

    [DESCRIPTION]
    Flags that provide additional information about a particular driver.

    [REMARKS]

    [SEE_ALSO]
    System::getRecordDriverInfo
]
*/
#define FMOD_DRIVER_STATE_CONNECTED 0x00000001  /* Device is currently plugged in. */
#define FMOD_DRIVER_STATE_DEFAULT   0x00000002  /* Device is the users preferred choice. */
/* [DEFINE_END] */


/*$ preserve start $*/

#include "fmod_codec.h"
#include "fmod_dsp.h"
#include "fmod_output.h"

#endif

/*$ preserve end $*/
