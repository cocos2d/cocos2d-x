/*===============================================================================================
 Offline Decoding Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how decode a file to PCM, without playing it.
 It writes out the data as a raw data file.
 The FMOD_System_CreateSound function uses FMOD_OPENONLY so that FMOD does not read any data 
 itself.
 If this is uses then it is up to the user to use FMOD_Sound_ReadData to get the data out of 
 the file and into the destination buffer.
===============================================================================================*/
#include "../../api/inc/fmod.h"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"
#include <stdio.h>

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}


int main(int argc, char *argv[])
{
    FMOD_SYSTEM     *system;
    FMOD_SOUND      *sound;
    FMOD_RESULT       result;
    unsigned int      version;

    /*
        Create a System object and initialize.
    */
    result = FMOD_System_Create(&system);
    ERRCHECK(result);

    result = FMOD_System_GetVersion(system, &version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return 0;
    }

    result = FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    result = FMOD_System_CreateStream(system, "../media/wave.mp3", FMOD_OPENONLY | FMOD_ACCURATETIME, 0, &sound);
    ERRCHECK(result);

    printf("==========================================================================\n");
    printf("Offline Decoding Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("==========================================================================\n");
    printf("\n");
    printf("This program will open wave.mp3 and decode it into wave.raw using the\n");
    printf("FMOD_Sound_ReadData function.\n");
    printf("\n");

    /*
        Decode the sound and write it to a .raw file.
    */
    {
        void *data;
        unsigned int length = 0, read;
        unsigned int bytesread;
        FILE *outfp;

        #define CHUNKSIZE 4096

        result = FMOD_Sound_GetLength(sound, &length, FMOD_TIMEUNIT_PCMBYTES);
        ERRCHECK(result);

        outfp = fopen("output.raw", "wb");
        if (!outfp)
        {
            printf("Error!  Could not open output.raw output file.\n");
            return 0;
        }

        data = malloc(CHUNKSIZE);
        if (!data)
        {
            printf("Error!  Failed to allocate %d bytes.\n", CHUNKSIZE);
            return 0;
        }

        bytesread = 0;
        do
        {
            result = FMOD_Sound_ReadData(sound, (char *)data, CHUNKSIZE, &read);

            fwrite((char *)data, read, 1, outfp);
                       
            bytesread += read;

            printf("writing %d bytes of %d to output.raw\r", bytesread, length);
        }
        while (result == FMOD_OK && read == CHUNKSIZE);

        /*
            Loop terminates when either 
            1. the read function returns an error.  (ie FMOD_ERR_FILE_EOF etc).
            2. the amount requested was different to the amount returned. (somehow got an EOF without the file error, maybe a non stream file format like mod/s3m/xm/it/midi).

            If 'bytesread' is bigger than 'length' then it just means that FMOD miscalculated the size, 
            but this will not usually happen if FMOD_ACCURATETIME is used.  (this will give the correct length for VBR formats)
        */

        printf("\n");

        if (outfp)
        {
            fclose(outfp);
        }
    }
        

    printf("\n");

    /*
        Shut down
    */
    result = FMOD_Sound_Release(sound);
    ERRCHECK(result);
    result = FMOD_System_Close(system);
    ERRCHECK(result);
    result = FMOD_System_Release(system);
    ERRCHECK(result);

    return 0;
}


