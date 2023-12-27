#ifndef MP3READER_H_
#define MP3READER_H_

typedef struct {
    size_t (*read)(void *ptr, size_t size, size_t nmemb, void *datasource);
    int (*seek)(void *datasource, int64_t offset, int whence);
    int (*close)(void *datasource);
    long (*tell)(void *datasource);
} mp3_callbacks;

class Mp3Reader {
public:
    Mp3Reader();
    bool init(mp3_callbacks *callback, void *source);
    bool getFrame(void *buffer, uint32_t *size);
    uint32_t getSampleRate() { return mSampleRate; }
    uint32_t getNumChannels() { return mNumChannels; }
    void close();
    ~Mp3Reader();

private:
    void *mSource;
    mp3_callbacks *mCallback;
    uint32_t mFixedHeader;
    off64_t mCurrentPos;
    uint32_t mSampleRate;
    uint32_t mNumChannels;
    uint32_t mBitrate;
};

int decodeMP3(mp3_callbacks *cb, void *source, std::vector<char> &pcmBuffer, int *numChannels, int *sampleRate, int *numFrames);

#endif /* MP3READER_H_ */
