/*===============================================================================================
 RipNetStream Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to rip streaming audio from the internet to local files, using
 System::attachFileSystem.
 
 This example also uses tags from the net stream to name the files as they are ripped.

 Some internet radio station only broadcast new tag information on fixed intervals.  This 
 means that the rip might not be exactly in line with the filenames that are produced.  
 For example if a radio station only broadcast the track name every 10 seconds, and the 
 music changed half way inbetween this period, then the first file would contain 5 seconds 
 of the new song, and the second song would be missing  the first 5 seconds of the track.
 Silence detection might help this problem, but most radio stations do not offer silence 
 between  tracks.
===============================================================================================*/
#include "../../api/inc/fmod.h"
#include "../../api/inc/fmod_errors.h"
#include "../common/wincompat.h"
#include <stdio.h>
#include <string.h>

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

FMOD_SOUND_TYPE gSoundType = FMOD_SOUND_TYPE_MPEG;
int             gFileBufferSize = 128*1024;
char            gCurrentTrackArtist[256];
char            gCurrentTrackTitle[256];
int             gUpdateFileName = FALSE;
char            gOutputFileName[1024];
FILE           *gFileHandle = 0;


/*
    File callbacks
*/
FMOD_RESULT F_CALLBACK myopen(const char *name, int unicode, unsigned int *filesize, void **handle, void **userdata)
{
    gFileHandle = fopen(gOutputFileName, "wb");
    if (!gFileHandle)
    {
        return FMOD_ERR_FILE_NOTFOUND;
    }

    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK myclose(void *handle, void *userdata)
{
    if (!gFileHandle)
    {
        return FMOD_ERR_INVALID_PARAM;
    }

    fclose(gFileHandle);

    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK myread(void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread, void *userdata)
{
    if (!gFileHandle)
    {
        return FMOD_ERR_INVALID_PARAM;
    }

    /*
        If the main thread detected a new tag name for artist / title, close the file and open a new one with the new name.
    */
    if (gUpdateFileName)
    {
        char *ext;

        gUpdateFileName = FALSE;

        fclose(gFileHandle);

        switch (gSoundType)
        {
            case FMOD_SOUND_TYPE_MPEG:       /* MP2/MP3 */
            {
                ext = ".mp3";
                break;
            }
            case FMOD_SOUND_TYPE_OGGVORBIS:  /* Ogg vorbis */
            {
                ext = ".ogg";
                break;
            }
            default:
            {
                ext = ".unknown";
                break;
            }
        }
    
        /*
            If it is the 'temp file name' then rename the file and append to it instead of starting a new file
        */
        if (!strcmp(gOutputFileName, "output.mp3"))
        {
            sprintf(gOutputFileName, "%s%s%s%s", gCurrentTrackArtist, strlen(gCurrentTrackTitle) ? " - " : "", gCurrentTrackTitle, ext);
            rename("output.mp3", gOutputFileName);
            gFileHandle = fopen(gOutputFileName, "ab+");
        }
        else
        {
            sprintf(gOutputFileName, "%s%s%s%s", gCurrentTrackArtist, strlen(gCurrentTrackTitle) ? " - " : "", gCurrentTrackTitle, ext);
            gFileHandle = fopen(gOutputFileName, "wb");
        }

        if (!gFileHandle)
        {
            return FMOD_ERR_FILE_NOTFOUND;
        }
    }

    fwrite(buffer, 1, sizebytes, gFileHandle);

    return FMOD_OK;
}


int main(int argc, char *argv[])
{
    FMOD_SYSTEM    *system;
    FMOD_SOUND     *sound;
    FMOD_CHANNEL   *channel = 0;
    FMOD_RESULT     result;
    int             key;
    unsigned int    version;

    memset(gCurrentTrackArtist, 0, 256);
    memset(gCurrentTrackTitle, 0, 256);
    strcpy(gOutputFileName, "output.mp3");   /* Start off like this then rename if a title tag comes along */

    printf("======================================================================\n");
    printf("RipNetStream Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("======================================================================\n\n");

    if (argc < 2)
    {
        printf("Usage:   ripnetstream <url>\n");
        return -1;
    }

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

    result = FMOD_System_Init(system, 100, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);

    result = FMOD_System_SetStreamBufferSize(system, gFileBufferSize, FMOD_TIMEUNIT_RAWBYTES);
    ERRCHECK(result);

    result = FMOD_System_AttachFileSystem(system, myopen, myclose, myread, 0);
    ERRCHECK(result);

    printf("Buffering...\n\n");

    result = FMOD_System_CreateSound(system, argv[1], FMOD_HARDWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_NONBLOCKING, 0, &sound);
    ERRCHECK(result);

    /*
        Main loop
    */
    do
    {
        if (sound && !channel)
        {
            result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, FALSE, &channel);
        }

        if (kbhit())
        {
            key = getch();

            switch (key)
            {
                case ' ' :
                {
                    if (channel)
                    {
                        int paused;
                        FMOD_Channel_GetPaused(channel, &paused);
                        FMOD_Channel_SetPaused(channel, !paused);
                    }
                    break;
                }
                case 'm' :
                case 'M' :
                {
                    if (channel)
                    {
                        int mute;
                        FMOD_Channel_GetMute(channel, &mute);
                        FMOD_Channel_SetMute(channel, !mute);
                    }
                    break;
                }
            }
        }

        FMOD_System_Update(system);

        if (channel)
        {
            unsigned int ms = 0;
            int          playing = FALSE;
            int          paused = FALSE;
            int          tagsupdated = 0;

            FMOD_Sound_GetNumTags(sound, 0, &tagsupdated);

            if (tagsupdated)
            {
                printf("\n");
                printf("\n");
                for (;;)
                {
                    FMOD_TAG tag;

                    if (FMOD_Sound_GetTag(sound, 0, -1, &tag) != FMOD_OK)
                    {
                        break;
                    }

                    if (tag.datatype == FMOD_TAGDATATYPE_STRING)
                    {
                        printf("[%-11s] %s (%d bytes)\n", tag.name, tag.data, tag.datalen);
                        
                        FMOD_Sound_GetFormat(sound, &gSoundType, 0, 0, 0);
                    
                        if (!strcmp(tag.name, "ARTIST"))
                        {
                            if(strncmp(gCurrentTrackArtist, (const char *)tag.data, 256))
                            {
                                strncpy(gCurrentTrackArtist, (const char *)tag.data, 256);
                                gUpdateFileName = TRUE;
                            }
                        }
                        if (!strcmp(tag.name, "TITLE"))
                        {
                            if (strncmp(gCurrentTrackTitle, (const char *)tag.data, 256))
                            {
                                strncpy(gCurrentTrackTitle, (const char *)tag.data, 256);
                                gUpdateFileName = TRUE;
                            }
                        }
                    }
                }
                printf("\n");
            }

            result = FMOD_Channel_IsPlaying(channel, &playing);
            if (result != FMOD_OK || !playing)
            {
                FMOD_Sound_Release(sound);
                sound = 0;               
                channel = 0;
            }
            else
            {
                result = FMOD_Channel_GetPaused(channel, &paused);
                result = FMOD_Channel_GetPosition(channel, &ms, FMOD_TIMEUNIT_MS);
                printf("Time %02d:%02d:%02d : %s : Press SPACE to pause. 'm' to mute. ESC to quit.\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped");
                fflush(stdout);
            }
        }

       
        if (sound)
        {
            FMOD_OPENSTATE openstate = FMOD_OPENSTATE_READY;

            FMOD_Sound_GetOpenState(sound, &openstate, 0, 0, 0);

            if (openstate == FMOD_OPENSTATE_ERROR)
            {
                FMOD_Sound_Release(sound);
                sound = 0;               
                channel = 0;
            }
        }

        if (!sound)
        {
            printf("\n");
            printf("Error occurred or stream ended.  Restarting stream..\n");
            result = FMOD_System_CreateSound(system, argv[1], FMOD_HARDWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_NONBLOCKING, 0, &sound);
            ERRCHECK(result);
            Sleep(1000);
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
