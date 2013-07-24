#include "OpenALDecoder.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <AL/alut.h>

#if CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN
#include <FBase.h>
#include <FBaseCol.h>
#include <FMedia.h>
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Media;
#endif

#ifndef DISABLE_VORBIS
#include <vorbis/vorbisfile.h>
#endif

#ifdef ENABLE_MPG123
#include <mpg123.h>
#endif

namespace CocosDenshion {

static int checkALError(const char *funcName)
{
    int err = alGetError();

    if (err != AL_NO_ERROR)
    {
        switch (err)
        {
            case AL_INVALID_NAME:
                fprintf(stderr, "AL_INVALID_NAME in %s\n", funcName);
                break;

            case AL_INVALID_ENUM:
                fprintf(stderr, "AL_INVALID_ENUM in %s\n", funcName);
                break;

            case AL_INVALID_VALUE:
                fprintf(stderr, "AL_INVALID_VALUE in %s\n", funcName);
                break;

            case AL_INVALID_OPERATION:
                fprintf(stderr, "AL_INVALID_OPERATION in %s\n", funcName);
                break;

            case AL_OUT_OF_MEMORY:
                fprintf(stderr, "AL_OUT_OF_MEMORY in %s\n", funcName);
                break;
        }
    }

    return err;
}

class AlutDecoder : public OpenALDecoder
{
    bool decode(OpenALFile &file, ALuint &result)
    {
        if (!file.mapToMemory())
            return false;
        result = alutCreateBufferFromFileImage(file.mappedFile, file.fileSize);
        if (AL_NONE == result)
            return false;
        return true;
    }

    bool acceptsFormat(Format format) const
    {
        return Wav == format || Raw == format;
    }
};

class DataRaii
{
public:
    char *data;
    size_t size;

    DataRaii() : data(0), size(0) {}
    ~DataRaii() { delete [] data; }
};

#ifdef ENABLE_MPG123
class Mpg123Decoder : public OpenALDecoder
{
private:
    mpg123_handle *handle;

public:
    class MpgOpenRaii
    {
    public:
        mpg123_handle *handle;

        MpgOpenRaii(mpg123_handle *handle) : handle(handle) {}
        ~MpgOpenRaii() { mpg123_close(handle); }
    };

    bool getInfo(ALenum &format, ALsizei &freq, ALsizei &size) const
    {
        int channels = 0;
        int encoding = 0;
        long rate = 0;
        if (MPG123_OK != mpg123_getformat(handle, &rate, &channels, &encoding))
            return false;
        size = mpg123_length(handle);
        if (size == MPG123_ERR)
            return false;
        freq = rate;
        if (encoding == MPG123_ENC_UNSIGNED_8) {
            if (channels == 1)
                format = AL_FORMAT_MONO8;
            else
                format = AL_FORMAT_STEREO8;
        } else {
            if (channels == 1)
                format = AL_FORMAT_MONO16;
            else
                format = AL_FORMAT_STEREO16;
        }
        return true;
    }

    bool decode(OpenALFile &file, ALuint &result)
    {
        if (MPG123_OK != mpg123_open_fd(handle, fileno(file.file)))
            return false;
        MpgOpenRaii raii(handle);
        ALenum format = AL_NONE;
        ALsizei freq = 0;
        ALsizei size = 0;
        if (!getInfo(format, freq, size))
            return false;
        DataRaii pcm;
        pcm.size = size;
        if (format == AL_FORMAT_MONO16 || format == AL_FORMAT_STEREO16)
            pcm.size *= 2;
        pcm.data = new char[pcm.size];
        size_t done = 0;
        if (MPG123_DONE != mpg123_read(handle, (unsigned char*)pcm.data, pcm.size, &done))
            return false;
        CCLOG("MP3 BUFFER SIZE: %ld, FORMAT %i.", (long)done, (int)format);
        return initALBuffer(result, format, pcm.data, done, freq);
    }

    bool acceptsFormat(Format format) const
    {
        return Mp3 == format;
    }

    Mpg123Decoder()
        : handle(mpg123_new(NULL, NULL))
    {
        if (MPG123_OK != mpg123_format(handle, 44100, MPG123_MONO | MPG123_STEREO,
                                       MPG123_ENC_UNSIGNED_8 | MPG123_ENC_SIGNED_16))
            CCLOG("ERROR (CocosDenshion): cannot set specified mpg123 format.");
    }

    ~Mpg123Decoder()
    {
        mpg123_delete(handle);
    }
};
#endif

#ifndef DISABLE_VORBIS
class VorbisDecoder : public OpenALDecoder
{
    class OggRaii
    {
    public:
        OggVorbis_File file;

        ~OggRaii() { ov_clear(&file); }
    };

public:
    bool decode(OpenALFile &file, ALuint &result)
    {
        OggRaii ogg;
        int status = ov_test(file.file, &ogg.file, 0, 0);
        if (status != 0) {
            ov_clear(&ogg.file);
            return false;
        }
        status = ov_test_open(&ogg.file);
        if (status != 0) {
            fprintf(stderr, "Could not open OGG file '%s'\n", file.debugName.c_str());
            return false;
        }
        // As vorbis documentation says, we should not fclose() file
        // after successful opening by vorbis functions.
        file.file = NULL;
        vorbis_info *info = ov_info(&ogg.file, -1);
        ALenum  format = (info->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

        DataRaii pcm;
        pcm.size = ov_pcm_total(&ogg.file, -1) * info->channels * 2;
        pcm.data = new char[pcm.size];

        size_t size = 0;
        int section = 0;
        while (size < pcm.size) {
            status = ov_read(&ogg.file, pcm.data + size, pcm.size - size, 0, 2, 1, &section);
            if (status > 0) {
                size += status;
            } else if (status < 0) {
                fprintf(stderr, "OGG file decoding stopped, file '%s'\n", file.debugName.c_str());
                return false;
            } else {
                break;
            }
        }
        if (size == 0) {
            fprintf(stderr, "Unable to read OGG data from '%s'\n", file.debugName.c_str());
			return false;
        }
        return initALBuffer(result, format, pcm.data, pcm.size, info->rate);
    }

    bool acceptsFormat(Format format) const
    {
        return Vorbis == format;
    }
};
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN
class TizenDecoder : public OpenALDecoder
{
public:
    static TizenDecoder *create(Format format)
    {
        TizenDecoder *decoder = new TizenDecoder(format);
        if (decoder && !decoder->init()) {
            delete decoder;
            decoder = NULL;
        }
        return decoder;
    }

    bool decode(OpenALFile &file, ALuint &result)
    {
        if (!file.mapToMemory())
            return false;
        ByteBuffer inputBuffer;
        inputBuffer.Construct(/*capacity*/ file.fileSize);
        inputBuffer.SetArray((const byte*)file.mappedFile, 0, file.fileSize);
        inputBuffer.Flip();
        ByteBuffer pcm;
        pcm.Construct(/*capacity*/ 2 * file.fileSize);

        AudioSampleType sampleType = AUDIO_TYPE_NONE;
        AudioChannelType channelType = AUDIO_CHANNEL_TYPE_NONE;
        int sampleRate = 0;
        if (E_SUCCESS != _decoder.Probe(inputBuffer, sampleType, channelType, sampleRate))
            return false;
        while (inputBuffer.GetRemaining()) {
            auto ret = _decoder.Decode(inputBuffer, pcm);
        	if (ret == E_OUT_OF_MEMORY) {
        		pcm.ExpandCapacity(2 * pcm.GetCapacity());
        	} else if (IsFailed(ret)) {
                AppLogTag("CocosDenshion(TizenDecoder)", "failed to decode file '%s', supported format is %s.", file.debugName.c_str(), getCodecName());
                return false;
            }
        }

        return initALBuffer(result, getALFormat(sampleType, channelType),
                            pcm.GetPointer(), pcm.GetPosition(), sampleRate);
    }

    bool acceptsFormat(Format format) const
    {
        return _format == format;
    }

private:
    TizenDecoder(Format format)
        : _format(format)
    {
    }

    bool init()
    {
        HashMap option;
        option.Construct();
        option.Add(*(new Integer(MEDIA_PROPERTY_AUDIO_CHANNEL_TYPE)), *(new Integer(AUDIO_CHANNEL_TYPE_NONE)));
        option.Add(*(new Integer(MEDIA_PROPERTY_AUDIO_SAMPLE_RATE)), *(new Integer(44100)));

        result r = _decoder.Construct(getCodecType());
        if (IsFailed(r))
            return false;
        else
            AppLogTag("CocosDenshion", "Tizen device supports audio format %s.", getCodecName());
        return true;
    }

    ALenum getALFormat(AudioSampleType sampleType, AudioChannelType channelType)
    {
        if (sampleType == AUDIO_TYPE_PCM_U8) {
            if (channelType == AUDIO_CHANNEL_TYPE_MONO)
                return AL_FORMAT_MONO8;
            return AL_FORMAT_STEREO8;
        }
        if (sampleType == AUDIO_TYPE_PCM_S16_LE) {
            if (channelType == AUDIO_CHANNEL_TYPE_MONO)
                return AL_FORMAT_MONO16;
            return AL_FORMAT_STEREO16;
        }
        AppLogTag("CocosDenshion(TizenDecoder)", "unsuppored sampleType=%d.", sampleType, channelType);
        return AL_NONE;
    }

    CodecType getCodecType() const
    {
        switch (_format) {
        case Mp3:
            return CODEC_MP3;
        case Vorbis:
            return CODEC_VORBIS;
        case Flac:
            return CODEC_FLAC;
        case Midi:
            return CODEC_MIDI;
        case Aac:
            return CODEC_AAC;
        default:
        	break;
        }
        return CODEC_UNKNOWN;
    }

    const char *getCodecName() const
    {
        switch (_format) {
        case Mp3:
            return "mp3";
        case Vorbis:
            return "vorbis";
        case Flac:
            return "flac";
        case Midi:
            return "midi";
        case Aac:
            return "aac";
        default:
        	break;
        }
        return "unknown";
    }

    Format _format;
    AudioDecoder _decoder;
};
#endif

std::vector<OpenALDecoder *> OpenALDecoder::_decoders;

void OpenALDecoder::installDecoders()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN
    addDecoder(TizenDecoder::create(Mp3));
    addDecoder(TizenDecoder::create(Vorbis));
    addDecoder(TizenDecoder::create(Flac));
    addDecoder(TizenDecoder::create(Midi));
    addDecoder(TizenDecoder::create(Aac));
#else
#if !defined(DISABLE_VORBIS)
    addDecoder(new VorbisDecoder());
#endif
#if defined(ENABLE_MPG123)
    addDecoder(new Mpg123Decoder());
#endif
#endif
    addDecoder(new AlutDecoder());
}

void OpenALDecoder::addDecoder(OpenALDecoder *decoder)
{
    if (decoder)
        _decoders.push_back(decoder);
}

bool OpenALDecoder::initALBuffer(ALuint &result, ALenum format,
                                 const ALvoid *data, ALsizei size, ALsizei freq)
{
    // Load audio data into a buffer.
    alGenBuffers(1, &result);

    if (checkALError("initALBuffer:alGenBuffers") != AL_NO_ERROR)
    {
        fprintf(stderr, "Couldn't generate OpenAL buffer\n");
        return false;
    }

    alBufferData(result, format, data, size, freq);
    checkALError("initALBuffer:alBufferData");
    return true;
}

const std::vector<OpenALDecoder *> &OpenALDecoder::getDecoders()
{
    return _decoders;
}

void OpenALFile::clear()
{
    if (mappedFile) {
        ::munmap(mappedFile, fileSize);
        mappedFile = 0;
        fileSize = 0;
    }
    if (file) {
        fclose(file);
        file = 0;
    }
}

bool OpenALFile::mapToMemory()
{
    if (!file)
        return false;
    if (mappedFile != NULL)
        return true;

    const int fd = fileno(file);
    struct stat fileStats;
    if (0 != fstat(fd, &fileStats))
        return false;
    fileSize = fileStats.st_size;
    mappedFile = ::mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mappedFile != MAP_FAILED)
        return true;
    mappedFile = NULL;
    return false;
}

} // namespace CocosDenshion
