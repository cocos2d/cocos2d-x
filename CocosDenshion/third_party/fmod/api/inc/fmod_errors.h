/*$ preserve start $*/

/* ============================================================================================== */
/* FMOD Ex - Error string header file. Copyright (c), Firelight Technologies Pty, Ltd. 2004-2011. */
/*                                                                                                */
/* Use this header if you want to store or display a string version / english explanation of      */
/* the FMOD error codes.                                                                          */
/*                                                                                                */
/* ============================================================================================== */

#ifndef _FMOD_ERRORS_H
#define _FMOD_ERRORS_H

#include "fmod.h"

#ifdef __GNUC__ 
static const char *FMOD_ErrorString(FMOD_RESULT errcode) __attribute__((unused));
#endif

static const char *FMOD_ErrorString(FMOD_RESULT errcode)
{
    switch (errcode)
    {
/*$ preserve end $*/
        case FMOD_ERR_ALREADYLOCKED:          return "Tried to call lock a second time before unlock was called. ";
        case FMOD_ERR_BADCOMMAND:             return "Tried to call a function on a data type that does not allow this type of functionality (ie calling Sound::lock on a streaming sound). ";
        case FMOD_ERR_CDDA_DRIVERS:           return "Neither NTSCSI nor ASPI could be initialised. ";
        case FMOD_ERR_CDDA_INIT:              return "An error occurred while initialising the CDDA subsystem. ";
        case FMOD_ERR_CDDA_INVALID_DEVICE:    return "Couldn't find the specified device. ";
        case FMOD_ERR_CDDA_NOAUDIO:           return "No audio tracks on the specified disc. ";
        case FMOD_ERR_CDDA_NODEVICES:         return "No CD/DVD devices were found. ";
        case FMOD_ERR_CDDA_NODISC:            return "No disc present in the specified drive. ";
        case FMOD_ERR_CDDA_READ:              return "A CDDA read error occurred. ";
        case FMOD_ERR_CHANNEL_ALLOC:          return "Error trying to allocate a channel. ";
        case FMOD_ERR_CHANNEL_STOLEN:         return "The specified channel has been reused to play another sound. ";
        case FMOD_ERR_COM:                    return "A Win32 COM related error occured. COM failed to initialize or a QueryInterface failed meaning a Windows codec or driver was not installed properly. ";
        case FMOD_ERR_DMA:                    return "DMA Failure.  See debug output for more information. ";
        case FMOD_ERR_DSP_CONNECTION:         return "DSP connection error.  Connection possibly caused a cyclic dependancy.  Or tried to connect a tree too many units deep (more than 128). ";
        case FMOD_ERR_DSP_FORMAT:             return "DSP Format error.  A DSP unit may have attempted to connect to this network with the wrong format. ";
        case FMOD_ERR_DSP_NOTFOUND:           return "DSP connection error.  Couldn't find the DSP unit specified. ";
        case FMOD_ERR_DSP_RUNNING:            return "DSP error.  Cannot perform this operation while the network is in the middle of running.  This will most likely happen if a connection or disconnection is attempted in a DSP callback. ";
        case FMOD_ERR_DSP_TOOMANYCONNECTIONS: return "DSP connection error.  The unit being connected to or disconnected should only have 1 input or output. ";
        case FMOD_ERR_EVENT_ALREADY_LOADED:   return "The specified project has already been loaded. Having multiple copies of the same project loaded simultaneously is forbidden. ";
        case FMOD_ERR_EVENT_FAILED:           return "An Event failed to be retrieved, most likely due to 'just fail' being specified as the max playbacks behavior. ";
        case FMOD_ERR_EVENT_GUIDCONFLICT:     return "An event with the same GUID already exists. ";
        case FMOD_ERR_EVENT_INFOONLY:         return "Can't execute this command on an EVENT_INFOONLY event. ";
        case FMOD_ERR_EVENT_INTERNAL:         return "An error occured that wasn't supposed to.  See debug log for reason. ";
        case FMOD_ERR_EVENT_MAXSTREAMS:       return "Event failed because 'Max streams' was hit when FMOD_EVENT_INIT_FAIL_ON_MAXSTREAMS was specified. ";
        case FMOD_ERR_EVENT_MISMATCH:         return "FSB mismatches the FEV it was compiled with, the stream/sample mode it was meant to be created with was different, or the FEV was built for a different platform. ";
        case FMOD_ERR_EVENT_NAMECONFLICT:     return "A category with the same name already exists. ";
        case FMOD_ERR_EVENT_NEEDSSIMPLE:      return "Tried to call a function on a complex event that's only supported by simple events. ";
        case FMOD_ERR_EVENT_NOTFOUND:         return "The requested event, event group, event category or event property could not be found. ";
        case FMOD_ERR_FILE_BAD:               return "Error loading file. ";
        case FMOD_ERR_FILE_COULDNOTSEEK:      return "Couldn't perform seek operation.  This is a limitation of the medium (ie netstreams) or the file format. ";
        case FMOD_ERR_FILE_DISKEJECTED:       return "Media was ejected while reading. ";
        case FMOD_ERR_FILE_EOF:               return "End of file unexpectedly reached while trying to read essential data (truncated data?). ";
        case FMOD_ERR_FILE_NOTFOUND:          return "File not found. ";
        case FMOD_ERR_FILE_UNWANTED:          return "Unwanted file access occured. ";
        case FMOD_ERR_FORMAT:                 return "Unsupported file or audio format. ";
        case FMOD_ERR_HTTP:                   return "A HTTP error occurred. This is a catch-all for HTTP errors not listed elsewhere. ";
        case FMOD_ERR_HTTP_ACCESS:            return "The specified resource requires authentication or is forbidden. ";
        case FMOD_ERR_HTTP_PROXY_AUTH:        return "Proxy authentication is required to access the specified resource. ";
        case FMOD_ERR_HTTP_SERVER_ERROR:      return "A HTTP server error occurred. ";
        case FMOD_ERR_HTTP_TIMEOUT:           return "The HTTP request timed out. ";
        case FMOD_ERR_INITIALIZATION:         return "FMOD was not initialized correctly to support this function. ";
        case FMOD_ERR_INITIALIZED:            return "Cannot call this command after System::init. ";
        case FMOD_ERR_INTERNAL:               return "An error occured that wasn't supposed to.  Contact support. ";
        case FMOD_ERR_INVALID_ADDRESS:        return "On Xbox 360, this memory address passed to FMOD must be physical, (ie allocated with XPhysicalAlloc.) ";
        case FMOD_ERR_INVALID_FLOAT:          return "Value passed in was a NaN, Inf or denormalized float. ";
        case FMOD_ERR_INVALID_HANDLE:         return "An invalid object handle was used. ";
        case FMOD_ERR_INVALID_PARAM:          return "An invalid parameter was passed to this function. ";
        case FMOD_ERR_INVALID_POSITION:       return "An invalid seek position was passed to this function. ";
        case FMOD_ERR_INVALID_SPEAKER:        return "An invalid speaker was passed to this function based on the current speaker mode. ";
        case FMOD_ERR_INVALID_SYNCPOINT:      return "The syncpoint did not come from this sound handle. ";
        case FMOD_ERR_INVALID_VECTOR:         return "The vectors passed in are not unit length, or perpendicular. ";
        case FMOD_ERR_MAXAUDIBLE:             return "Reached maximum audible playback count for this sound's soundgroup. ";
        case FMOD_ERR_MEMORY:                 return "Not enough memory or resources. ";
        case FMOD_ERR_MEMORY_CANTPOINT:       return "Can't use FMOD_OPENMEMORY_POINT on non PCM source data, or non mp3/xma/adpcm data if FMOD_CREATECOMPRESSEDSAMPLE was used. ";
        case FMOD_ERR_MEMORY_SRAM:            return "Not enough memory or resources on console sound ram. ";
        case FMOD_ERR_MUSIC_NOCALLBACK:       return "The music callback is required, but it has not been set. ";
        case FMOD_ERR_MUSIC_NOTFOUND:         return "The requested music entity could not be found. ";
        case FMOD_ERR_MUSIC_UNINITIALIZED:    return "Music system is not initialized probably because no music data is loaded. ";
        case FMOD_ERR_NEEDS2D:                return "Tried to call a command on a 3d sound when the command was meant for 2d sound. ";
        case FMOD_ERR_NEEDS3D:                return "Tried to call a command on a 2d sound when the command was meant for 3d sound. ";
        case FMOD_ERR_NEEDSHARDWARE:          return "Tried to use a feature that requires hardware support.  (ie trying to play a GCADPCM compressed sound in software on Wii). ";
        case FMOD_ERR_NEEDSSOFTWARE:          return "Tried to use a feature that requires the software engine.  Software engine has either been turned off, or command was executed on a hardware channel which does not support this feature. ";
        case FMOD_ERR_NET_CONNECT:            return "Couldn't connect to the specified host. ";
        case FMOD_ERR_NET_SOCKET_ERROR:       return "A socket error occurred.  This is a catch-all for socket-related errors not listed elsewhere. ";
        case FMOD_ERR_NET_URL:                return "The specified URL couldn't be resolved. ";
        case FMOD_ERR_NET_WOULD_BLOCK:        return "Operation on a non-blocking socket could not complete immediately. ";
        case FMOD_ERR_NOTREADY:               return "Operation could not be performed because specified sound/DSP connection is not ready. ";
        case FMOD_ERR_OUTPUT_ALLOCATED:       return "Error initializing output device, but more specifically, the output device is already in use and cannot be reused. ";
        case FMOD_ERR_OUTPUT_CREATEBUFFER:    return "Error creating hardware sound buffer. ";
        case FMOD_ERR_OUTPUT_DRIVERCALL:      return "A call to a standard soundcard driver failed, which could possibly mean a bug in the driver or resources were missing or exhausted. ";
        case FMOD_ERR_OUTPUT_ENUMERATION:     return "Error enumerating the available driver list. List may be inconsistent due to a recent device addition or removal. ";
        case FMOD_ERR_OUTPUT_FORMAT:          return "Soundcard does not support the minimum features needed for this soundsystem (16bit stereo output). ";
        case FMOD_ERR_OUTPUT_INIT:            return "Error initializing output device. ";
        case FMOD_ERR_OUTPUT_NOHARDWARE:      return "FMOD_HARDWARE was specified but the sound card does not have the resources necessary to play it. ";
        case FMOD_ERR_OUTPUT_NOSOFTWARE:      return "Attempted to create a software sound but no software channels were specified in System::init. ";
        case FMOD_ERR_PAN:                    return "Panning only works with mono or stereo sound sources. ";
        case FMOD_ERR_PLUGIN:                 return "An unspecified error has been returned from a 3rd party plugin. ";
        case FMOD_ERR_PLUGIN_INSTANCES:       return "The number of allowed instances of a plugin has been exceeded. ";
        case FMOD_ERR_PLUGIN_MISSING:         return "A requested output, dsp unit type or codec was not available. ";
        case FMOD_ERR_PLUGIN_RESOURCE:        return "A resource that the plugin requires cannot be found. (ie the DLS file for MIDI playback) ";
        case FMOD_ERR_PRELOADED:              return "The specified sound is still in use by the event system, call EventSystem::unloadFSB before trying to release it. ";
        case FMOD_ERR_PROGRAMMERSOUND:        return "The specified sound is still in use by the event system, wait for the event which is using it finish with it. ";
        case FMOD_ERR_RECORD:                 return "An error occured trying to initialize the recording device. ";
        case FMOD_ERR_REVERB_INSTANCE:        return "Specified instance in FMOD_REVERB_PROPERTIES couldn't be set. Most likely because it is an invalid instance number or the reverb doesnt exist. ";
        case FMOD_ERR_SUBSOUNDS:              return "The error occured because the sound referenced contains subsounds when it shouldn't have, or it doesn't contain subsounds when it should have.  The operation may also not be able to be performed on a parent sound, or a parent sound was played without setting up a sentence first. ";
        case FMOD_ERR_SUBSOUND_ALLOCATED:     return "This subsound is already being used by another sound, you cannot have more than one parent to a sound.  Null out the other parent's entry first. ";
        case FMOD_ERR_SUBSOUND_CANTMOVE:      return "Shared subsounds cannot be replaced or moved from their parent stream, such as when the parent stream is an FSB file. ";
        case FMOD_ERR_SUBSOUND_MODE:          return "The subsound's mode bits do not match with the parent sound's mode bits.  See documentation for function that it was called with. ";
        case FMOD_ERR_TAGNOTFOUND:            return "The specified tag could not be found or there are no tags. ";
        case FMOD_ERR_TOOMANYCHANNELS:        return "The sound created exceeds the allowable input channel count.  This can be increased using the maxinputchannels parameter in System::setSoftwareFormat. ";
        case FMOD_ERR_UNIMPLEMENTED:          return "Something in FMOD hasn't been implemented when it should be! contact support! ";
        case FMOD_ERR_UNINITIALIZED:          return "This command failed because System::init or System::setDriver was not called. ";
        case FMOD_ERR_UNSUPPORTED:            return "A command issued was not supported by this object.  Possibly a plugin without certain callbacks specified. ";
        case FMOD_ERR_UPDATE:                 return "An error caused by System::update occured. ";
        case FMOD_ERR_VERSION:                return "The version number of this file format is not supported. ";
        case FMOD_OK:                         return "No errors.";
        default :                             return "Unknown error.";
/*$ preserve start $*/
    };
}

#endif
/*$ preserve end $*/
