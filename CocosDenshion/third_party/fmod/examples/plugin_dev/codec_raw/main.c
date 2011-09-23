/*===============================================================================================
 CODEC_RAW.SO
 Copyright (c), Firelight Technologies Pty, Ltd 2006-2011.

===============================================================================================*/

#include <stdio.h>

#include "../../../api/inc/fmod.h"
#include "../../../api/inc/fmod_errors.h"

FMOD_RESULT F_CALLBACK rawopen(FMOD_CODEC_STATE *codec, FMOD_MODE usermode, FMOD_CREATESOUNDEXINFO *userexinfo);
FMOD_RESULT F_CALLBACK rawclose(FMOD_CODEC_STATE *codec);
FMOD_RESULT F_CALLBACK rawread(FMOD_CODEC_STATE *codec, void *buffer, unsigned int size, unsigned int *read);
FMOD_RESULT F_CALLBACK rawsetposition(FMOD_CODEC_STATE *codec, int subsound, unsigned int position, FMOD_TIMEUNIT postype);

FMOD_CODEC_DESCRIPTION rawcodec =
{
    "FMOD Raw player plugin example",   // Name.
    0x00010000,                         // Version 0xAAAABBBB   A = major, B = minor.
    0,                                  // Don't force everything using this codec to be a stream
    FMOD_TIMEUNIT_PCMBYTES,             // The time format we would like to accept into setposition/getposition.
    &rawopen,                           // Open callback.
    &rawclose,                          // Close callback.
    &rawread,                           // Read callback.
    0,                                  // Getlength callback.  (If not specified FMOD return the length in FMOD_TIMEUNIT_PCM, FMOD_TIMEUNIT_MS or FMOD_TIMEUNIT_PCMBYTES units based on the lengthpcm member of the FMOD_CODEC structure).
    &rawsetposition,                    // Setposition callback.
    0,                                  // Getposition callback. (only used for timeunit types that are not FMOD_TIMEUNIT_PCM, FMOD_TIMEUNIT_MS and FMOD_TIMEUNIT_PCMBYTES).
    0                                   // Sound create callback (don't need it)
};


/*
    FMODGetCodecDescription is mandatory for every fmod plugin.  This is the symbol the registerplugin function searches for.
    Must be declared with F_API to make it export as stdcall.
    MUST BE EXTERN'ED AS C!  C++ functions will be mangled incorrectly and not load in fmod.
*/
#ifdef __cplusplus
extern "C" {
#endif

F_DECLSPEC F_DLLEXPORT FMOD_CODEC_DESCRIPTION * F_API FMODGetCodecDescription()
{
    return &rawcodec;
}

#ifdef __cplusplus
}
#endif


static FMOD_CODEC_WAVEFORMAT    rawwaveformat;

/*
    The actual codec code.

    Note that the callbacks uses FMOD's supplied file system callbacks.

    This is important as even though you might want to open the file yourself, you would lose the following benefits.
    1. Automatic support of memory files, CDDA based files, and HTTP/TCPIP based files.
    2. "fileoffset" / "length" support when user calls System::createSound with FMOD_CREATESOUNDEXINFO structure.
    3. Buffered file access.
    FMOD files are high level abstracts that support all sorts of 'file', they are not just disk file handles.
    If you want FMOD to use your own filesystem (and potentially lose the above benefits) use System::setFileSystem.
*/

FMOD_RESULT F_CALLBACK rawopen(FMOD_CODEC_STATE *codec, FMOD_MODE usermode, FMOD_CREATESOUNDEXINFO *userexinfo)
{          
    rawwaveformat.channels     = 2;
    rawwaveformat.format       = FMOD_SOUND_FORMAT_PCM16;
    rawwaveformat.frequency    = 44100;
    rawwaveformat.blockalign   = rawwaveformat.channels * 2;          /* 2 = 16bit pcm */
    rawwaveformat.lengthpcm    = codec->filesize / rawwaveformat.blockalign;   /* bytes converted to PCM samples */;

    codec->numsubsounds = 0;                    /* number of 'subsounds' in this sound.  For most codecs this is 0, only multi sound codecs such as FSB or CDDA have subsounds. */
    codec->waveformat   = &rawwaveformat;
    codec->plugindata   = 0;                    /* user data value */

    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK rawclose(FMOD_CODEC_STATE *codec)
{
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK rawread(FMOD_CODEC_STATE *codec, void *buffer, unsigned int size, unsigned int *read)
{
    return codec->fileread(codec->filehandle, buffer, size, read, 0);
}

FMOD_RESULT F_CALLBACK rawsetposition(FMOD_CODEC_STATE *codec, int subsound, unsigned int position, FMOD_TIMEUNIT postype)
{
    return codec->fileseek(codec->filehandle, position, 0);
}

