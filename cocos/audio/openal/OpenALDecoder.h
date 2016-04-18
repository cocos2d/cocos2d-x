#ifndef COCOSDENSHION_OPENALLOADER_H
#define COCOSDENSHION_OPENALLOADER_H

#include <vector>
#include <string>
#include <stdio.h>
#ifdef OPENAL_PLAIN_INCLUDES
#include <al.h>
#else
#include <AL/al.h>
#endif


#if CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN
#define DISABLE_VORBIS
#endif

namespace CocosDenshion {

struct OpenALFile
{
    std::string debugName; ///< For logging.
    FILE *file;
    void *mappedFile; ///< Reserved by decoders.
    size_t fileSize; ///< Reserved by decoders.

    OpenALFile() : file(0), mappedFile(0), fileSize(0) {}
    ~OpenALFile() { clear(); }

    /// Unmaps from memory and closes file.
    void clear();
    /// Performs memory map, if was not mapped before.
    bool mapToMemory();
};

class OpenALDecoder
{
public:
    enum Format {
        Mp3 = 0,
        Vorbis,
        Wav,
        Raw,
        Flac,
        Midi,
        Aac
    };

    virtual ~OpenALDecoder() {}

    /// Returns true if such format is supported and decoding was successful.
    virtual bool decode(OpenALFile &file, ALuint &result) = 0;
    virtual bool acceptsFormat(Format format) const = 0;

    static const std::vector<OpenALDecoder *> &getDecoders();
    static void installDecoders();

protected:
    static void addDecoder(OpenALDecoder *decoder);
    bool initALBuffer(ALuint &result, ALenum format,
                      const ALvoid* data, ALsizei size, ALsizei freq);

    static std::vector<OpenALDecoder *> _decoders;
};

} // namespace CocosDenshion

#endif // COCOSDENSHION_OPENALLOADER_H
