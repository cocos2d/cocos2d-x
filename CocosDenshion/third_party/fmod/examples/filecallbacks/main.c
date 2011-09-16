/*===============================================================================================
 File Callbacks Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example is a modified version of the playstream example.
 It shows the correct way declare and handle fmod file callbacks with System::setFileSystem.
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


/*
    TIPS:

    1. use F_CALLBACK.  Do NOT force cast your own function to fmod's callback type.
    2. return FMOD_ERR_FILE_NOTFOUND in open as required.
    3. return number of bytes read in read callback.  Do not get the size and count 
       around the wrong way in fread for example, this would return 1 instead of the number of bytes read.

    QUESTIONS:

    1. Why does fmod seek to the end and read?  Because it is looking for ID3V1 tags.  
       Use FMOD_IGNORETAGS in FMOD_System_CreateSound / FMOD_System_CreateStream if you don't like this behaviour.
*/

FMOD_RESULT F_CALLBACK myopen(const char *name, int unicode, unsigned int *filesize, void **handle, void **userdata)
{
    if (name)
    {
        FILE *fp;

        fp = fopen(name, "rb");
        if (!fp)
        {
            return FMOD_ERR_FILE_NOTFOUND;
        }

        fseek(fp, 0, SEEK_END);
        *filesize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        *userdata = (void *)0x12345678;
        *handle = fp;
    }

    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK myclose(void *handle, void *userdata)
{
    if (!handle)
    {
        return FMOD_ERR_INVALID_PARAM;
    }

    fclose((FILE *)handle);

    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK myread(void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread, void *userdata)
{
    if (!handle)
    {
        return FMOD_ERR_INVALID_PARAM;
    }

    if (bytesread)
    {
        *bytesread = (int)fread(buffer, 1, sizebytes, (FILE *)handle);
    
        if (*bytesread < sizebytes)
        {
            return FMOD_ERR_FILE_EOF;
        }
    }

    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK myseek(void *handle, unsigned int pos, void *userdata)
{
    if (!handle)
    {
        return FMOD_ERR_INVALID_PARAM;
    }

    fseek((FILE *)handle, pos, SEEK_SET);

    return FMOD_OK;
}


int main(int argc, char *argv[])
{
    FMOD_SYSTEM      *system;
    FMOD_SOUND       *sound;
    FMOD_CHANNEL     *channel = 0;
    FMOD_RESULT       result;
    int               key;
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

    result = FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);

    result = FMOD_System_SetFileSystem(system, myopen, myclose, myread, myseek, 0, 0, 2048);
    ERRCHECK(result);

    result = FMOD_System_CreateStream(system, "../media/wave.mp3", FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
    ERRCHECK(result);

    printf("====================================================================\n");
    printf("PlayStream Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("====================================================================\n");
    printf("\n");
    printf("Press space to pause, Esc to quit\n");
    printf("\n");

    /*
        Play the sound.
    */

    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
    ERRCHECK(result);

    /*
        Main loop.
    */
    do
    {
        if (kbhit())
        {
            key = getch();

            switch (key)
            {
                case ' ' :
                {
                    int paused;
                    FMOD_Channel_GetPaused(channel, &paused);
                    FMOD_Channel_SetPaused(channel, !paused);
                    break;
                }
            }
        }

        FMOD_System_Update(system);

        if (channel)
        {
            unsigned int ms;
            unsigned int lenms;
            int          playing;
            int          paused;

            FMOD_Channel_IsPlaying(channel, &playing);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }

            result = FMOD_Channel_GetPaused(channel, &paused);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }

            result = FMOD_Channel_GetPosition(channel, &ms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }

            result = FMOD_Sound_GetLength(sound, &lenms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }

            printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped");
            fflush(stdout);
        }

        Sleep(10);

    } while (key != 27);

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


