/* ========================================================================================== */
/* FMOD Studio - C++ header file. Copyright (c), Firelight Technologies Pty, Ltd. 2004-2015.  */
/*                                                                                            */
/* Use this header in conjunction with fmod_common.h (which contains all the constants /      */
/* callbacks) to develop using C++ classes.                                                   */
/* ========================================================================================== */

#ifndef _FMOD_HPP
#define _FMOD_HPP

#include "fmod_common.h"
#include "fmod.h"

/*
    Constant and defines
*/

/*
    FMOD Namespace
*/
namespace FMOD
{
    class System;
    class Sound;
    class ChannelControl;
    class Channel;
    class ChannelGroup;
    class SoundGroup;
    class DSP;
    class DSPConnection;
    class Geometry;
    class Reverb3D;

    /*
        FMOD global system functions (optional).
    */
    inline FMOD_RESULT Memory_Initialize    (void *poolmem, int poollen, FMOD_MEMORY_ALLOC_CALLBACK useralloc, FMOD_MEMORY_REALLOC_CALLBACK userrealloc, FMOD_MEMORY_FREE_CALLBACK userfree, FMOD_MEMORY_TYPE memtypeflags = FMOD_MEMORY_ALL) { return FMOD_Memory_Initialize(poolmem, poollen, useralloc, userrealloc, userfree, memtypeflags); }
    inline FMOD_RESULT Memory_GetStats      (int *currentalloced, int *maxalloced, bool blocking = true) { return FMOD_Memory_GetStats(currentalloced, maxalloced, blocking); }
    inline FMOD_RESULT Debug_Initialize     (FMOD_DEBUG_FLAGS flags, FMOD_DEBUG_MODE mode = FMOD_DEBUG_MODE_TTY, FMOD_DEBUG_CALLBACK callback = 0, const char *filename = 0) { return FMOD_Debug_Initialize(flags, mode, callback, filename); }
    inline FMOD_RESULT File_SetDiskBusy     (int busy) { return FMOD_File_SetDiskBusy(busy); }
    inline FMOD_RESULT File_GetDiskBusy     (int *busy) { return FMOD_File_GetDiskBusy(busy); }

    /*
        FMOD System factory functions.
    */
    inline FMOD_RESULT System_Create        (System **system) { return FMOD_System_Create((FMOD_SYSTEM **)system); }

    /*
       'System' API
    */
    class System
    {
      private:

        // Constructor made private so user cannot statically instance a System class.  System_Create must be used.
        System();
        System(const System &);

      public:

        FMOD_RESULT F_API release                 ();

        // Setup functions.
        FMOD_RESULT F_API setOutput               (FMOD_OUTPUTTYPE output);
        FMOD_RESULT F_API getOutput               (FMOD_OUTPUTTYPE *output);
        FMOD_RESULT F_API getNumDrivers           (int *numdrivers);
        FMOD_RESULT F_API getDriverInfo           (int id, char *name, int namelen, FMOD_GUID *guid, int *systemrate, FMOD_SPEAKERMODE *speakermode, int *speakermodechannels);
        FMOD_RESULT F_API setDriver               (int driver);
        FMOD_RESULT F_API getDriver               (int *driver);
        FMOD_RESULT F_API setSoftwareChannels     (int numsoftwarechannels);
        FMOD_RESULT F_API getSoftwareChannels     (int *numsoftwarechannels);
        FMOD_RESULT F_API setSoftwareFormat       (int samplerate, FMOD_SPEAKERMODE speakermode, int numrawspeakers);
        FMOD_RESULT F_API getSoftwareFormat       (int *samplerate, FMOD_SPEAKERMODE *speakermode, int *numrawspeakers);
        FMOD_RESULT F_API setDSPBufferSize        (unsigned int bufferlength, int numbuffers);
        FMOD_RESULT F_API getDSPBufferSize        (unsigned int *bufferlength, int *numbuffers);
        FMOD_RESULT F_API setFileSystem           (FMOD_FILE_OPEN_CALLBACK useropen, FMOD_FILE_CLOSE_CALLBACK userclose, FMOD_FILE_READ_CALLBACK userread, FMOD_FILE_SEEK_CALLBACK userseek, FMOD_FILE_ASYNCREAD_CALLBACK userasyncread, FMOD_FILE_ASYNCCANCEL_CALLBACK userasynccancel, int blockalign);
        FMOD_RESULT F_API attachFileSystem        (FMOD_FILE_OPEN_CALLBACK useropen, FMOD_FILE_CLOSE_CALLBACK userclose, FMOD_FILE_READ_CALLBACK userread, FMOD_FILE_SEEK_CALLBACK userseek);
        FMOD_RESULT F_API setAdvancedSettings     (FMOD_ADVANCEDSETTINGS *settings);
        FMOD_RESULT F_API getAdvancedSettings     (FMOD_ADVANCEDSETTINGS *settings);
        FMOD_RESULT F_API setCallback             (FMOD_SYSTEM_CALLBACK callback, FMOD_SYSTEM_CALLBACK_TYPE callbackmask = 0xFFFFFFFF);

        // Plug-in support.
        FMOD_RESULT F_API setPluginPath           (const char *path);
        FMOD_RESULT F_API loadPlugin              (const char *filename, unsigned int *handle, unsigned int priority = 0);
        FMOD_RESULT F_API unloadPlugin            (unsigned int handle);
        FMOD_RESULT F_API getNumPlugins           (FMOD_PLUGINTYPE plugintype, int *numplugins);
        FMOD_RESULT F_API getPluginHandle         (FMOD_PLUGINTYPE plugintype, int index, unsigned int *handle);
        FMOD_RESULT F_API getPluginInfo           (unsigned int handle, FMOD_PLUGINTYPE *plugintype, char *name, int namelen, unsigned int *version);
        FMOD_RESULT F_API setOutputByPlugin       (unsigned int handle);
        FMOD_RESULT F_API getOutputByPlugin       (unsigned int *handle);
        FMOD_RESULT F_API createDSPByPlugin       (unsigned int handle, DSP **dsp);
        FMOD_RESULT F_API getDSPInfoByPlugin      (unsigned int handle, const FMOD_DSP_DESCRIPTION **description);
        FMOD_RESULT F_API registerCodec           (FMOD_CODEC_DESCRIPTION *description, unsigned int *handle, unsigned int priority = 0);
        FMOD_RESULT F_API registerDSP             (const FMOD_DSP_DESCRIPTION *description, unsigned int *handle);
        FMOD_RESULT F_API registerOutput          (const FMOD_OUTPUT_DESCRIPTION *description, unsigned int *handle);

        // Init/Close.
        FMOD_RESULT F_API init                    (int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);
        FMOD_RESULT F_API close                   ();

        // General post-init system functions.
        FMOD_RESULT F_API update                  ();        /* IMPORTANT! CALL THIS ONCE PER FRAME! */

        FMOD_RESULT F_API setSpeakerPosition      (FMOD_SPEAKER speaker, float x, float y, bool active);
        FMOD_RESULT F_API getSpeakerPosition      (FMOD_SPEAKER speaker, float *x, float *y, bool *active);
        FMOD_RESULT F_API setStreamBufferSize     (unsigned int filebuffersize, FMOD_TIMEUNIT filebuffersizetype);
        FMOD_RESULT F_API getStreamBufferSize     (unsigned int *filebuffersize, FMOD_TIMEUNIT *filebuffersizetype);
        FMOD_RESULT F_API set3DSettings           (float dopplerscale, float distancefactor, float rolloffscale);
        FMOD_RESULT F_API get3DSettings           (float *dopplerscale, float *distancefactor, float *rolloffscale);
        FMOD_RESULT F_API set3DNumListeners       (int numlisteners);
        FMOD_RESULT F_API get3DNumListeners       (int *numlisteners);
        FMOD_RESULT F_API set3DListenerAttributes (int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
        FMOD_RESULT F_API get3DListenerAttributes (int listener, FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up);
        FMOD_RESULT F_API set3DRolloffCallback    (FMOD_3D_ROLLOFF_CALLBACK callback);
        FMOD_RESULT F_API mixerSuspend            ();
        FMOD_RESULT F_API mixerResume             ();
        FMOD_RESULT F_API getDefaultMixMatrix     (FMOD_SPEAKERMODE sourcespeakermode, FMOD_SPEAKERMODE targetspeakermode, float *matrix, int matrixhop);
        FMOD_RESULT F_API getSpeakerModeChannels  (FMOD_SPEAKERMODE mode, int *channels);

        // System information functions.
        FMOD_RESULT F_API getVersion              (unsigned int *version);
        FMOD_RESULT F_API getOutputHandle         (void **handle);
        FMOD_RESULT F_API getChannelsPlaying      (int *channels);
        FMOD_RESULT F_API getCPUUsage             (float *dsp, float *stream, float *geometry, float *update, float *total);
        FMOD_RESULT F_API getSoundRAM             (int *currentalloced, int *maxalloced, int *total);

        // Sound/DSP/Channel/FX creation and retrieval.
        FMOD_RESULT F_API createSound             (const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, Sound **sound);
        FMOD_RESULT F_API createStream            (const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, Sound **sound);
        FMOD_RESULT F_API createDSP               (const FMOD_DSP_DESCRIPTION *description, DSP **dsp);
        FMOD_RESULT F_API createDSPByType         (FMOD_DSP_TYPE type, DSP **dsp);
        FMOD_RESULT F_API createChannelGroup      (const char *name, ChannelGroup **channelgroup);
        FMOD_RESULT F_API createSoundGroup        (const char *name, SoundGroup **soundgroup);
        FMOD_RESULT F_API createReverb3D          (Reverb3D **reverb);

        FMOD_RESULT F_API playSound               (Sound *sound, ChannelGroup *channelgroup, bool paused, Channel **channel);
        FMOD_RESULT F_API playDSP                 (DSP *dsp, ChannelGroup *channelgroup, bool paused, Channel **channel);
        FMOD_RESULT F_API getChannel              (int channelid, Channel **channel);
        FMOD_RESULT F_API getMasterChannelGroup   (ChannelGroup **channelgroup);
        FMOD_RESULT F_API getMasterSoundGroup     (SoundGroup **soundgroup);

        // Routing to ports.
        FMOD_RESULT F_API attachChannelGroupToPort   (FMOD_PORT_TYPE portType, FMOD_PORT_INDEX portIndex, ChannelGroup *channelgroup, bool passThru = false);
        FMOD_RESULT F_API detachChannelGroupFromPort (ChannelGroup *channelgroup);

        // Reverb API.
        FMOD_RESULT F_API setReverbProperties     (int instance, const FMOD_REVERB_PROPERTIES *prop);
        FMOD_RESULT F_API getReverbProperties     (int instance, FMOD_REVERB_PROPERTIES *prop);

        // System level DSP functionality.
        FMOD_RESULT F_API lockDSP                 ();
        FMOD_RESULT F_API unlockDSP               ();

        // Recording API.
        FMOD_RESULT F_API getRecordNumDrivers     (int *numdrivers, int *numconnected);
        FMOD_RESULT F_API getRecordDriverInfo     (int id, char *name, int namelen, FMOD_GUID *guid, int *systemrate, FMOD_SPEAKERMODE *speakermode, int *speakermodechannels, FMOD_DRIVER_STATE *state);
        FMOD_RESULT F_API getRecordPosition       (int id, unsigned int *position);
        FMOD_RESULT F_API recordStart             (int id, Sound *sound, bool loop);
        FMOD_RESULT F_API recordStop              (int id);
        FMOD_RESULT F_API isRecording             (int id, bool *recording);

        // Geometry API.
        FMOD_RESULT F_API createGeometry          (int maxpolygons, int maxvertices, Geometry **geometry);
        FMOD_RESULT F_API setGeometrySettings     (float maxworldsize);
        FMOD_RESULT F_API getGeometrySettings     (float *maxworldsize);
        FMOD_RESULT F_API loadGeometry            (const void *data, int datasize, Geometry **geometry);
        FMOD_RESULT F_API getGeometryOcclusion    (const FMOD_VECTOR *listener, const FMOD_VECTOR *source, float *direct, float *reverb);

        // Network functions.
        FMOD_RESULT F_API setNetworkProxy         (const char *proxy);
        FMOD_RESULT F_API getNetworkProxy         (char *proxy, int proxylen);
        FMOD_RESULT F_API setNetworkTimeout       (int timeout);
        FMOD_RESULT F_API getNetworkTimeout       (int *timeout);

        // Userdata set/get.
        FMOD_RESULT F_API setUserData             (void *userdata);
        FMOD_RESULT F_API getUserData             (void **userdata);
    };

    /*
        'Sound' API
    */
    class Sound
    {
      private:

        // Constructor made private so user cannot statically instance a Sound class.  Appropriate Sound creation or retrieval function must be used.
        Sound();
        Sound(const Sound &);

      public:

        FMOD_RESULT F_API release                ();
        FMOD_RESULT F_API getSystemObject        (System **system);

        // Standard sound manipulation functions.
        FMOD_RESULT F_API lock                   (unsigned int offset, unsigned int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2);
        FMOD_RESULT F_API unlock                 (void *ptr1, void *ptr2, unsigned int len1, unsigned int len2);
        FMOD_RESULT F_API setDefaults            (float frequency, int priority);
        FMOD_RESULT F_API getDefaults            (float *frequency, int *priority);
        FMOD_RESULT F_API set3DMinMaxDistance    (float min, float max);
        FMOD_RESULT F_API get3DMinMaxDistance    (float *min, float *max);
        FMOD_RESULT F_API set3DConeSettings      (float insideconeangle, float outsideconeangle, float outsidevolume);
        FMOD_RESULT F_API get3DConeSettings      (float *insideconeangle, float *outsideconeangle, float *outsidevolume);
        FMOD_RESULT F_API set3DCustomRolloff     (FMOD_VECTOR *points, int numpoints);
        FMOD_RESULT F_API get3DCustomRolloff     (FMOD_VECTOR **points, int *numpoints);
        FMOD_RESULT F_API setSubSound            (int index, Sound *subsound);
        FMOD_RESULT F_API getSubSound            (int index, Sound **subsound);
        FMOD_RESULT F_API getSubSoundParent      (Sound **parentsound);
        FMOD_RESULT F_API getName                (char *name, int namelen);
        FMOD_RESULT F_API getLength              (unsigned int *length, FMOD_TIMEUNIT lengthtype);
        FMOD_RESULT F_API getFormat              (FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits);
        FMOD_RESULT F_API getNumSubSounds        (int *numsubsounds);
        FMOD_RESULT F_API getNumTags             (int *numtags, int *numtagsupdated);
        FMOD_RESULT F_API getTag                 (const char *name, int index, FMOD_TAG *tag);
        FMOD_RESULT F_API getOpenState           (FMOD_OPENSTATE *openstate, unsigned int *percentbuffered, bool *starving, bool *diskbusy);
        FMOD_RESULT F_API readData               (void *buffer, unsigned int lenbytes, unsigned int *read);
        FMOD_RESULT F_API seekData               (unsigned int pcm);

        FMOD_RESULT F_API setSoundGroup          (SoundGroup *soundgroup);
        FMOD_RESULT F_API getSoundGroup          (SoundGroup **soundgroup);

        // Synchronization point API.  These points can come from markers embedded in wav files, and can also generate channel callbacks.
        FMOD_RESULT F_API getNumSyncPoints       (int *numsyncpoints);
        FMOD_RESULT F_API getSyncPoint           (int index, FMOD_SYNCPOINT **point);
        FMOD_RESULT F_API getSyncPointInfo       (FMOD_SYNCPOINT *point, char *name, int namelen, unsigned int *offset, FMOD_TIMEUNIT offsettype);
        FMOD_RESULT F_API addSyncPoint           (unsigned int offset, FMOD_TIMEUNIT offsettype, const char *name, FMOD_SYNCPOINT **point);
        FMOD_RESULT F_API deleteSyncPoint        (FMOD_SYNCPOINT *point);

        // Functions also in Channel class but here they are the 'default' to save having to change it in Channel all the time.
        FMOD_RESULT F_API setMode                (FMOD_MODE mode);
        FMOD_RESULT F_API getMode                (FMOD_MODE *mode);
        FMOD_RESULT F_API setLoopCount           (int loopcount);
        FMOD_RESULT F_API getLoopCount           (int *loopcount);
        FMOD_RESULT F_API setLoopPoints          (unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
        FMOD_RESULT F_API getLoopPoints          (unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);

        // For MOD/S3M/XM/IT/MID sequenced formats only.
        FMOD_RESULT F_API getMusicNumChannels    (int *numchannels);
        FMOD_RESULT F_API setMusicChannelVolume  (int channel, float volume);
        FMOD_RESULT F_API getMusicChannelVolume  (int channel, float *volume);
        FMOD_RESULT F_API setMusicSpeed          (float speed);
        FMOD_RESULT F_API getMusicSpeed          (float *speed);

        // Userdata set/get.
        FMOD_RESULT F_API setUserData            (void *userdata);
        FMOD_RESULT F_API getUserData            (void **userdata);
    };


    /*
        'ChannelControl API'.   This is a base class for Channel and ChannelGroup so they can share the same functionality.  This cannot be used or instansiated explicitly.
    */
    class ChannelControl
    {
      private:

        // Constructor made private so user cannot statically instance a Control class.
        ChannelControl();
        ChannelControl(const ChannelControl &);

      public:

        FMOD_RESULT F_API getSystemObject        (System **system);

        // General control functionality for Channels and ChannelGroups.
        FMOD_RESULT F_API stop                   ();
        FMOD_RESULT F_API setPaused              (bool paused);
        FMOD_RESULT F_API getPaused              (bool *paused);
        FMOD_RESULT F_API setVolume              (float volume);
        FMOD_RESULT F_API getVolume              (float *volume);
        FMOD_RESULT F_API setVolumeRamp          (bool ramp);
        FMOD_RESULT F_API getVolumeRamp          (bool *ramp);
        FMOD_RESULT F_API getAudibility          (float *audibility);
        FMOD_RESULT F_API setPitch               (float pitch);
        FMOD_RESULT F_API getPitch               (float *pitch);
        FMOD_RESULT F_API setMute                (bool mute);
        FMOD_RESULT F_API getMute                (bool *mute);
        FMOD_RESULT F_API setReverbProperties    (int instance, float wet);
        FMOD_RESULT F_API getReverbProperties    (int instance, float *wet);
        FMOD_RESULT F_API setLowPassGain         (float gain);
        FMOD_RESULT F_API getLowPassGain         (float *gain);
        FMOD_RESULT F_API setMode                (FMOD_MODE mode);
        FMOD_RESULT F_API getMode                (FMOD_MODE *mode);
        FMOD_RESULT F_API setCallback            (FMOD_CHANNELCONTROL_CALLBACK callback);
        FMOD_RESULT F_API isPlaying              (bool *isplaying);

        // Panning and level adjustment.
        // Note all 'set' functions alter a final matrix, this is why the only get function is getMixMatrix, to avoid other get functions returning incorrect/obsolete values.
        FMOD_RESULT F_API setPan                 (float pan);
        FMOD_RESULT F_API setMixLevelsOutput     (float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright);
        FMOD_RESULT F_API setMixLevelsInput      (float *levels, int numlevels);
        FMOD_RESULT F_API setMixMatrix           (float *matrix, int outchannels, int inchannels, int inchannel_hop = 0);
        FMOD_RESULT F_API getMixMatrix           (float *matrix, int *outchannels, int *inchannels, int inchannel_hop = 0);

        // Clock based functionality.
        FMOD_RESULT F_API getDSPClock            (unsigned long long *dspclock, unsigned long long *parentclock);
        FMOD_RESULT F_API setDelay               (unsigned long long dspclock_start, unsigned long long dspclock_end, bool stopchannels = true);
        FMOD_RESULT F_API getDelay               (unsigned long long *dspclock_start, unsigned long long *dspclock_end, bool *stopchannels = 0);
        FMOD_RESULT F_API addFadePoint           (unsigned long long dspclock, float volume);
        FMOD_RESULT F_API setFadePointRamp       (unsigned long long dspclock, float volume);
        FMOD_RESULT F_API removeFadePoints       (unsigned long long dspclock_start, unsigned long long dspclock_end);
        FMOD_RESULT F_API getFadePoints          (unsigned int *numpoints, unsigned long long *point_dspclock, float *point_volume);

        // DSP effects.
        FMOD_RESULT F_API getDSP                 (int index, DSP **dsp);
        FMOD_RESULT F_API addDSP                 (int index, DSP *dsp);
        FMOD_RESULT F_API removeDSP              (DSP *dsp);
        FMOD_RESULT F_API getNumDSPs             (int *numdsps);
        FMOD_RESULT F_API setDSPIndex            (DSP *dsp, int index);
        FMOD_RESULT F_API getDSPIndex            (DSP *dsp, int *index);
        FMOD_RESULT F_API overridePanDSP         (DSP *pan);

        // 3D functionality.
        FMOD_RESULT F_API set3DAttributes        (const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *alt_pan_pos = 0);
        FMOD_RESULT F_API get3DAttributes        (FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *alt_pan_pos = 0);
        FMOD_RESULT F_API set3DMinMaxDistance    (float mindistance, float maxdistance);
        FMOD_RESULT F_API get3DMinMaxDistance    (float *mindistance, float *maxdistance);
        FMOD_RESULT F_API set3DConeSettings      (float insideconeangle, float outsideconeangle, float outsidevolume);
        FMOD_RESULT F_API get3DConeSettings      (float *insideconeangle, float *outsideconeangle, float *outsidevolume);
        FMOD_RESULT F_API set3DConeOrientation   (FMOD_VECTOR *orientation);
        FMOD_RESULT F_API get3DConeOrientation   (FMOD_VECTOR *orientation);
        FMOD_RESULT F_API set3DCustomRolloff     (FMOD_VECTOR *points, int numpoints);
        FMOD_RESULT F_API get3DCustomRolloff     (FMOD_VECTOR **points, int *numpoints);
        FMOD_RESULT F_API set3DOcclusion         (float directocclusion, float reverbocclusion);
        FMOD_RESULT F_API get3DOcclusion         (float *directocclusion, float *reverbocclusion);
        FMOD_RESULT F_API set3DSpread            (float angle);
        FMOD_RESULT F_API get3DSpread            (float *angle);
        FMOD_RESULT F_API set3DLevel             (float level);
        FMOD_RESULT F_API get3DLevel             (float *level);
        FMOD_RESULT F_API set3DDopplerLevel      (float level);
        FMOD_RESULT F_API get3DDopplerLevel      (float *level);
        FMOD_RESULT F_API set3DDistanceFilter    (bool custom, float customLevel, float centerFreq);
        FMOD_RESULT F_API get3DDistanceFilter    (bool *custom, float *customLevel, float *centerFreq);

        // Userdata set/get.
        FMOD_RESULT F_API setUserData            (void *userdata);
        FMOD_RESULT F_API getUserData            (void **userdata);
    };

    /*
        'Channel' API.
    */
    class Channel : public ChannelControl
    {
      private:

        // Constructor made private so user cannot statically instance a Channel class.  Appropriate Channel creation or retrieval function must be used.
        Channel();
        Channel(const Channel &);

      public:

        // Channel specific control functionality.
        FMOD_RESULT F_API setFrequency           (float frequency);
        FMOD_RESULT F_API getFrequency           (float *frequency);
        FMOD_RESULT F_API setPriority            (int priority);
        FMOD_RESULT F_API getPriority            (int *priority);
        FMOD_RESULT F_API setPosition            (unsigned int position, FMOD_TIMEUNIT postype);
        FMOD_RESULT F_API getPosition            (unsigned int *position, FMOD_TIMEUNIT postype);
        FMOD_RESULT F_API setChannelGroup        (ChannelGroup *channelgroup);
        FMOD_RESULT F_API getChannelGroup        (ChannelGroup **channelgroup);
        FMOD_RESULT F_API setLoopCount           (int loopcount);
        FMOD_RESULT F_API getLoopCount           (int *loopcount);
        FMOD_RESULT F_API setLoopPoints          (unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
        FMOD_RESULT F_API getLoopPoints          (unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);

        // Information only functions.
        FMOD_RESULT F_API isVirtual              (bool *isvirtual);
        FMOD_RESULT F_API getCurrentSound        (Sound **sound);
        FMOD_RESULT F_API getIndex               (int *index);
    };

    /*
        'ChannelGroup' API
    */
    class ChannelGroup : public ChannelControl
    {
      private:

        // Constructor made private so user cannot statically instance a ChannelGroup class.  Appropriate ChannelGroup creation or retrieval function must be used.
        ChannelGroup();
        ChannelGroup(const ChannelGroup &);

      public:

        FMOD_RESULT F_API release                 ();

        // Nested channel groups.
        FMOD_RESULT F_API addGroup                (ChannelGroup *group, bool propagatedspclock = true, DSPConnection **connection = 0);
        FMOD_RESULT F_API getNumGroups            (int *numgroups);
        FMOD_RESULT F_API getGroup                (int index, ChannelGroup **group);
        FMOD_RESULT F_API getParentGroup          (ChannelGroup **group);

        // Information only functions.
        FMOD_RESULT F_API getName                 (char *name, int namelen);
        FMOD_RESULT F_API getNumChannels          (int *numchannels);
        FMOD_RESULT F_API getChannel              (int index, Channel **channel);
    };

    /*
        'SoundGroup' API
    */
    class SoundGroup
    {
      private:

        // Constructor made private so user cannot statically instance a SoundGroup class.  Appropriate SoundGroup creation or retrieval function must be used.
        SoundGroup();
        SoundGroup(const SoundGroup &);

      public:

        FMOD_RESULT F_API release                ();
        FMOD_RESULT F_API getSystemObject        (System **system);

        // SoundGroup control functions.
        FMOD_RESULT F_API setMaxAudible          (int maxaudible);
        FMOD_RESULT F_API getMaxAudible          (int *maxaudible);
        FMOD_RESULT F_API setMaxAudibleBehavior  (FMOD_SOUNDGROUP_BEHAVIOR behavior);
        FMOD_RESULT F_API getMaxAudibleBehavior  (FMOD_SOUNDGROUP_BEHAVIOR *behavior);
        FMOD_RESULT F_API setMuteFadeSpeed       (float speed);
        FMOD_RESULT F_API getMuteFadeSpeed       (float *speed);
        FMOD_RESULT F_API setVolume              (float volume);
        FMOD_RESULT F_API getVolume              (float *volume);
        FMOD_RESULT F_API stop                   ();

        // Information only functions.
        FMOD_RESULT F_API getName                (char *name, int namelen);
        FMOD_RESULT F_API getNumSounds           (int *numsounds);
        FMOD_RESULT F_API getSound               (int index, Sound **sound);
        FMOD_RESULT F_API getNumPlaying          (int *numplaying);

        // Userdata set/get.
        FMOD_RESULT F_API setUserData            (void *userdata);
        FMOD_RESULT F_API getUserData            (void **userdata);
    };

    /*
        'DSP' API
    */
    class DSP
    {
      private:

        // Constructor made private so user cannot statically instance a DSP class.  Appropriate DSP creation or retrieval function must be used.
        DSP();
        DSP(const DSP &);

      public:

        FMOD_RESULT F_API release                ();
        FMOD_RESULT F_API getSystemObject        (System **system);

        // Connection / disconnection / input and output enumeration.
        FMOD_RESULT F_API addInput               (DSP *input, DSPConnection **connection = 0, FMOD_DSPCONNECTION_TYPE type = FMOD_DSPCONNECTION_TYPE_STANDARD);
        FMOD_RESULT F_API disconnectFrom         (DSP *target, DSPConnection *connection = 0);
        FMOD_RESULT F_API disconnectAll          (bool inputs, bool outputs);
        FMOD_RESULT F_API getNumInputs           (int *numinputs);
        FMOD_RESULT F_API getNumOutputs          (int *numoutputs);
        FMOD_RESULT F_API getInput               (int index, DSP **input, DSPConnection **inputconnection);
        FMOD_RESULT F_API getOutput              (int index, DSP **output, DSPConnection **outputconnection);

        // DSP unit control.
        FMOD_RESULT F_API setActive              (bool active);
        FMOD_RESULT F_API getActive              (bool *active);
        FMOD_RESULT F_API setBypass              (bool bypass);
        FMOD_RESULT F_API getBypass              (bool *bypass);
        FMOD_RESULT F_API setWetDryMix           (float prewet, float postwet, float dry);
        FMOD_RESULT F_API getWetDryMix           (float *prewet, float *postwet, float *dry);
        FMOD_RESULT F_API setChannelFormat       (FMOD_CHANNELMASK channelmask, int numchannels, FMOD_SPEAKERMODE source_speakermode);
        FMOD_RESULT F_API getChannelFormat       (FMOD_CHANNELMASK *channelmask, int *numchannels, FMOD_SPEAKERMODE *source_speakermode);
        FMOD_RESULT F_API getOutputChannelFormat (FMOD_CHANNELMASK inmask, int inchannels, FMOD_SPEAKERMODE inspeakermode, FMOD_CHANNELMASK *outmask, int *outchannels, FMOD_SPEAKERMODE *outspeakermode);
        FMOD_RESULT F_API reset                  ();

        // DSP parameter control.
        FMOD_RESULT F_API setParameterFloat      (int index, float value);
        FMOD_RESULT F_API setParameterInt        (int index, int value);
        FMOD_RESULT F_API setParameterBool       (int index, bool value);
        FMOD_RESULT F_API setParameterData       (int index, void *data, unsigned int length);
        FMOD_RESULT F_API getParameterFloat      (int index, float *value, char *valuestr, int valuestrlen);
        FMOD_RESULT F_API getParameterInt        (int index, int *value, char *valuestr, int valuestrlen);
        FMOD_RESULT F_API getParameterBool       (int index, bool *value, char *valuestr, int valuestrlen);
        FMOD_RESULT F_API getParameterData       (int index, void **data, unsigned int *length, char *valuestr, int valuestrlen);
        FMOD_RESULT F_API getNumParameters       (int *numparams);
        FMOD_RESULT F_API getParameterInfo       (int index, FMOD_DSP_PARAMETER_DESC **desc);
        FMOD_RESULT F_API getDataParameterIndex  (int datatype, int *index);
        FMOD_RESULT F_API showConfigDialog       (void *hwnd, bool show);

        // DSP attributes.
        FMOD_RESULT F_API getInfo                (char *name, unsigned int *version, int *channels, int *configwidth, int *configheight);
        FMOD_RESULT F_API getType                (FMOD_DSP_TYPE *type);
        FMOD_RESULT F_API getIdle                (bool *idle);

        // Userdata set/get.
        FMOD_RESULT F_API setUserData            (void *userdata);
        FMOD_RESULT F_API getUserData            (void **userdata);

        // Metering.
        FMOD_RESULT F_API setMeteringEnabled     (bool inputEnabled, bool outputEnabled);
        FMOD_RESULT F_API getMeteringEnabled     (bool *inputEnabled, bool *outputEnabled);
        FMOD_RESULT F_API getMeteringInfo        (FMOD_DSP_METERING_INFO *inputInfo, FMOD_DSP_METERING_INFO *outputInfo);
    };


    /*
        'DSPConnection' API
    */
    class DSPConnection
    {
      private:

        // Constructor made private so user cannot statically instance a DSPConnection class.  Appropriate DSPConnection creation or retrieval function must be used.
        DSPConnection();
        DSPConnection(const DSPConnection &);

      public:

        FMOD_RESULT F_API getInput              (DSP **input);
        FMOD_RESULT F_API getOutput             (DSP **output);
        FMOD_RESULT F_API setMix                (float volume);
        FMOD_RESULT F_API getMix                (float *volume);
        FMOD_RESULT F_API setMixMatrix          (float *matrix, int outchannels, int inchannels, int inchannel_hop = 0);
        FMOD_RESULT F_API getMixMatrix          (float *matrix, int *outchannels, int *inchannels, int inchannel_hop = 0);
        FMOD_RESULT F_API getType               (FMOD_DSPCONNECTION_TYPE *type);

        // Userdata set/get.
        FMOD_RESULT F_API setUserData           (void *userdata);
        FMOD_RESULT F_API getUserData           (void **userdata);
    };


    /*
        'Geometry' API
    */
    class Geometry
    {
      private:

        // Constructor made private so user cannot statically instance a Geometry class.  Appropriate Geometry creation or retrieval function must be used.
        Geometry();
        Geometry(const Geometry &);

      public:

        FMOD_RESULT F_API release                ();

        // Polygon manipulation.
        FMOD_RESULT F_API addPolygon             (float directocclusion, float reverbocclusion, bool doublesided, int numvertices, const FMOD_VECTOR *vertices, int *polygonindex);
        FMOD_RESULT F_API getNumPolygons         (int *numpolygons);
        FMOD_RESULT F_API getMaxPolygons         (int *maxpolygons, int *maxvertices);
        FMOD_RESULT F_API getPolygonNumVertices  (int index, int *numvertices);
        FMOD_RESULT F_API setPolygonVertex       (int index, int vertexindex, const FMOD_VECTOR *vertex);
        FMOD_RESULT F_API getPolygonVertex       (int index, int vertexindex, FMOD_VECTOR *vertex);
        FMOD_RESULT F_API setPolygonAttributes   (int index, float directocclusion, float reverbocclusion, bool doublesided);
        FMOD_RESULT F_API getPolygonAttributes   (int index, float *directocclusion, float *reverbocclusion, bool *doublesided);

        // Object manipulation.
        FMOD_RESULT F_API setActive              (bool active);
        FMOD_RESULT F_API getActive              (bool *active);
        FMOD_RESULT F_API setRotation            (const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
        FMOD_RESULT F_API getRotation            (FMOD_VECTOR *forward, FMOD_VECTOR *up);
        FMOD_RESULT F_API setPosition            (const FMOD_VECTOR *position);
        FMOD_RESULT F_API getPosition            (FMOD_VECTOR *position);
        FMOD_RESULT F_API setScale               (const FMOD_VECTOR *scale);
        FMOD_RESULT F_API getScale               (FMOD_VECTOR *scale);
        FMOD_RESULT F_API save                   (void *data, int *datasize);

        // Userdata set/get.
        FMOD_RESULT F_API setUserData            (void *userdata);
        FMOD_RESULT F_API getUserData            (void **userdata);
    };


    /*
        'Reverb' API
    */
    class Reverb3D
    {
      private:

        // Constructor made private so user cannot statically instance a Reverb3D class.  Appropriate Reverb creation or retrieval function must be used.
        Reverb3D();
        Reverb3D(const Reverb3D &);

      public:

        FMOD_RESULT F_API release                ();

        // Reverb manipulation.
        FMOD_RESULT F_API set3DAttributes        (const FMOD_VECTOR *position, float mindistance, float maxdistance);
        FMOD_RESULT F_API get3DAttributes        (FMOD_VECTOR *position, float *mindistance,float *maxdistance);
        FMOD_RESULT F_API setProperties          (const FMOD_REVERB_PROPERTIES *properties);
        FMOD_RESULT F_API getProperties          (FMOD_REVERB_PROPERTIES *properties);
        FMOD_RESULT F_API setActive              (bool active);
        FMOD_RESULT F_API getActive              (bool *active);

        // Userdata set/get.
        FMOD_RESULT F_API setUserData            (void *userdata);
        FMOD_RESULT F_API getUserData            (void **userdata);
    };
}

#endif
