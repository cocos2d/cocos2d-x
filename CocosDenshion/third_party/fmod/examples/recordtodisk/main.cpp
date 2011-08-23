/*===============================================================================================
 Record to disk example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to do a streaming record to disk.
===============================================================================================*/
#include "../../api/inc/fmod.hpp"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"
#include <string.h>

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

#if defined(WIN32) || defined(__WATCOMC__) || defined(_WIN32) || defined(__WIN32__)
    #define __PACKED                         /* dummy */
#else
    #define __PACKED __attribute__((packed)) /* gcc packed */
#endif


/*
[
	[DESCRIPTION]
	Writes out the contents of a record buffer to a file.

	[PARAMETERS]
 
	[RETURN_VALUE]
	void

	[REMARKS]
]
*/
void WriteWavHeader(FILE *fp, FMOD::Sound *sound, int length)
{
    int             channels, bits;
    float           rate;

    if (!sound)
    {
        return;
    }

    fseek(fp, 0, SEEK_SET);

    sound->getFormat  (0, 0, &channels, &bits);
    sound->getDefaults(&rate, 0, 0, 0);

    {
        #if defined(WIN32) || defined(_WIN64) || defined(__WATCOMC__) || defined(_WIN32) || defined(__WIN32__)
        #pragma pack(1)
        #endif
        
        /*
            WAV Structures
        */
        typedef struct
        {
	        signed char id[4];
	        int 		size;
        } RiffChunk;
    
        struct
        {
            RiffChunk       chunk           __PACKED;
            unsigned short	wFormatTag      __PACKED;    /* format type  */
            unsigned short	nChannels       __PACKED;    /* number of channels (i.e. mono, stereo...)  */
            unsigned int	nSamplesPerSec  __PACKED;    /* sample rate  */
            unsigned int	nAvgBytesPerSec __PACKED;    /* for buffer estimation  */
            unsigned short	nBlockAlign     __PACKED;    /* block size of data  */
            unsigned short	wBitsPerSample  __PACKED;    /* number of bits per sample of mono data */
        } __PACKED FmtChunk  = { {{'f','m','t',' '}, sizeof(FmtChunk) - sizeof(RiffChunk) }, 1, channels, (int)rate, (int)rate * channels * bits / 8, 1 * channels * bits / 8, bits };

        struct
        {
            RiffChunk   chunk;
        } DataChunk = { {{'d','a','t','a'}, length } };

        struct
        {
            RiffChunk   chunk;
	        signed char rifftype[4];
        } WavHeader = { {{'R','I','F','F'}, sizeof(FmtChunk) + sizeof(RiffChunk) + length }, {'W','A','V','E'} };

        #if defined(WIN32) || defined(_WIN64) || defined(__WATCOMC__) || defined(_WIN32) || defined(__WIN32__)
        #pragma pack()
        #endif
      
        /*
            Write out the WAV header.
        */
        fwrite(&WavHeader, sizeof(WavHeader), 1, fp);
        fwrite(&FmtChunk, sizeof(FmtChunk), 1, fp);
        fwrite(&DataChunk, sizeof(DataChunk), 1, fp);
    }
}


int main(int argc, char *argv[])
{
    FMOD::System          *system  = 0;
    FMOD::Sound           *sound   = 0;
    FMOD_RESULT            result;
    FMOD_CREATESOUNDEXINFO exinfo;
    int                    key, recorddriver, numdrivers, count;
    unsigned int           version;    
    FILE                  *fp;
    unsigned int           datalength = 0, soundlength;

    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return 0;
    }

    /* 
        System initialization
    */
    printf("---------------------------------------------------------\n");    
    printf("Select OUTPUT type\n");    
    printf("---------------------------------------------------------\n");    
    printf("1 :  OSS        - Open Sound System\n");
    printf("2 :  ALSA       - Advanced Linux Sound Architecture\n");
    printf("3 :  ESD        - Enlightenment Sound Daemon\n");
    printf("4 :  PULSEAUDIO - Pulse Audio Sound Server\n");
    printf("---------------------------------------------------------\n");
    printf("Press a corresponding number or ESC to quit\n");

    do
    {
        key = getch();
    } while (key != 27 && key < '1' && key > '5');
    
    switch (key)
    {
        case '1' :  result = system->setOutput(FMOD_OUTPUTTYPE_OSS);
                    break;
        case '2' :  result = system->setOutput(FMOD_OUTPUTTYPE_ALSA);
                    break;
        case '3' :  result = system->setOutput(FMOD_OUTPUTTYPE_ESD);
                    break;
        case '4' :  result = system->setOutput(FMOD_OUTPUTTYPE_PULSEAUDIO);
                    break;                    
        default  :  return 1; 
    }  
    ERRCHECK(result);
    
    /*
        Enumerate record devices
    */

    result = system->getRecordNumDrivers(&numdrivers);
    ERRCHECK(result);

    printf("---------------------------------------------------------\n");    
    printf("Choose a RECORD driver\n");
    printf("---------------------------------------------------------\n");    
    for (count=0; count < numdrivers; count++)
    {
        char name[256];

        result = system->getRecordDriverInfo(count, name, 256, 0);
        ERRCHECK(result);

        printf("%d : %s\n", count + 1, name);
    }
    printf("---------------------------------------------------------\n");
    printf("Press a corresponding number or ESC to quit\n");

    recorddriver = 0;
    do
    {
        key = getch();
        if (key == 27)
        {
            return 0;
        }
        recorddriver = key - '1';
    } while (recorddriver < 0 || recorddriver >= numdrivers);

    printf("\n");

    result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));

    exinfo.cbsize           = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.numchannels      = 2;
    exinfo.format           = FMOD_SOUND_FORMAT_PCM16;
    exinfo.defaultfrequency = 44100;
    exinfo.length           = exinfo.defaultfrequency * sizeof(short) * exinfo.numchannels * 2;
    
    result = system->createSound(0, FMOD_2D | FMOD_SOFTWARE | FMOD_OPENUSER, &exinfo, &sound);
    ERRCHECK(result);

    printf("========================================================================\n");
    printf("Record to disk example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("========================================================================\n");
    printf("\n");
    printf("Press a key to start recording to record.wav\n");
    printf("\n");

    getch();

    result = system->recordStart(recorddriver, sound, true);
    ERRCHECK(result);

    printf("Press 'Esc' to quit\n");
    printf("\n");

    fp = fopen("record.wav", "wb");
    if (!fp)
    {
        printf("ERROR : could not open record.wav for writing.\n");
        return 1;
    }

    /*
        Write out the wav header.  As we don't know the length yet it will be 0.
    */
    WriteWavHeader(fp, sound, datalength);

    result = sound->getLength(&soundlength, FMOD_TIMEUNIT_PCM);
    ERRCHECK(result);

    /*
        Main loop.
    */
    do
    {
        static unsigned int lastrecordpos = 0;
        unsigned int recordpos = 0;

        if (kbhit())
        {
            key = getch();
        }

        system->getRecordPosition(recorddriver, &recordpos);
        ERRCHECK(result);

        if (recordpos != lastrecordpos)        
        {
            void *ptr1, *ptr2;
            int blocklength;
            unsigned int len1, len2;
            
            blocklength = (int)recordpos - (int)lastrecordpos;
            if (blocklength < 0)
            {
                blocklength += soundlength;
            }

            /*
                Lock the sound to get access to the raw data.
            */
            sound->lock(lastrecordpos * 4, blocklength * 4, &ptr1, &ptr2, &len1, &len2);   /* *4 = stereo 16bit.  1 sample = 4 bytes. */

            /*
                Write it to disk.
            */
            if (ptr1 && len1)
            {
                datalength += fwrite(ptr1, 1, len1, fp);
            }
            if (ptr2 && len2)
            {
                datalength += fwrite(ptr2, 1, len2, fp);
            }

            /*
                Unlock the sound to allow FMOD to use it again.
            */
            sound->unlock(ptr1, ptr2, len1, len2);
        }

        lastrecordpos = recordpos;

        printf("Record buffer pos = %6d : Record time = %02d:%02d\r", recordpos, datalength / exinfo.defaultfrequency / 4 / 60, (datalength / exinfo.defaultfrequency / 4) % 60);
        fflush(stdout);

        system->update();

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Write back the wav header now that we know its length.
    */
    WriteWavHeader(fp, sound, datalength);

    fclose(fp);

    /*
        Shut down
    */
    result = sound->release();
    ERRCHECK(result);

    result = system->release();
    ERRCHECK(result);

    return 0;
}


