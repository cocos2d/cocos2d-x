/*===============================================================================================
 PlayList Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to load a playlist and play the sounds in a playlist.
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
    FMOD_SYSTEM      *system   = 0;
    FMOD_SOUND       *playlist = 0;
    FMOD_SOUND       *sound    = 0;
    FMOD_CHANNEL     *channel  = 0;
    FMOD_TAG          tag;
    FMOD_RESULT       result;
    FMOD_SOUND_TYPE   soundtype;
    FMOD_BOOL         isplaylist = 0;
    char             *title = NULL;
    int               count = 0;
    int               key;
    unsigned int      version;
    char              file[128];   

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

    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    result = FMOD_System_CreateSound(system, "../media/playlist.m3u", FMOD_DEFAULT, 0, &playlist);
    ERRCHECK(result);

    result = FMOD_Sound_GetFormat(playlist, &soundtype, 0, 0, 0);
    ERRCHECK(result);

    isplaylist = (soundtype == FMOD_SOUND_TYPE_PLAYLIST);

    printf("===================================================================\n");
    printf("PlayList Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("===================================================================\n");
    printf("\n");
    printf("Press 'n'     to play next sound in playlist\n");
    printf("Press 'space' to pause/unpause current sound\n");
    printf("Press 'Esc'   to quit\n");
    printf("\n");

    if (isplaylist)
    {
        printf("PLAYLIST loaded.\n");
        /*
            Get the first song in the playlist, create the sound and then play it.
        */
        result = FMOD_Sound_GetTag(playlist, "FILE", count, &tag);
        ERRCHECK(result);

        sprintf(file, "../media/%s", (char *)tag.data);

        result = FMOD_System_CreateSound(system, file, FMOD_DEFAULT, 0, &sound);
        ERRCHECK(result);

        result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
        ERRCHECK(result);

        FMOD_Sound_GetTag(playlist, "TITLE", count, &tag);
        title = (char *)tag.data;

        count++;
    }
    else
    {
        printf("SOUND loaded.\n");

        /*
            This is just a normal sound, so just play it.
        */
        sound = playlist;

        result = FMOD_Sound_SetMode(sound, FMOD_LOOP_NORMAL);
        ERRCHECK(result);

        result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
        ERRCHECK(result);
    }

    printf("\n");

    /*
        Main loop.
    */
    do
    {
        FMOD_BOOL  isplaying = 0;

        if (channel && isplaylist)
        {
            /*
                When sound has finished playing, play the next sound in the playlist
            */

            FMOD_Channel_IsPlaying(channel, &isplaying);
            if (!isplaying)
            {
                if (sound)
                {
                    FMOD_Sound_Release(sound);

                    sound = NULL;
                }

                result = FMOD_Sound_GetTag(playlist, "FILE", count, &tag);
                if (result != FMOD_OK)
                {
                    count = 0;
                }
                else
                {
                    printf("playing next song in playlist...\n");

                    sprintf(file, "../media/%s", (char *)tag.data);

                    result = FMOD_System_CreateSound(system, file, FMOD_DEFAULT, 0, &sound);
                    ERRCHECK(result);

                    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
                    ERRCHECK(result);

                    FMOD_Sound_GetTag(playlist, "TITLE", count, &tag);
                    title = (char *)tag.data;

                    count++;
                }
            }
        }


        if (kbhit())
        {
            key = getch();

            switch (key)
            {
                case 'n' :
                {
                    /*
                        Play the next song in the playlist
                    */
                    if (channel && isplaylist)
                    {
                        FMOD_Channel_Stop(channel);
                    }

                    break;
                }
                case ' ' :
                {
                    if (channel)
                    {
                        FMOD_BOOL paused;

                        FMOD_Channel_GetPaused(channel, &paused);
                        FMOD_Channel_SetPaused(channel, !paused);
                    }
                }
            }
        }

        FMOD_System_Update(system);

        {
            unsigned int ms = 0;
            unsigned int lenms = 0;
            FMOD_BOOL    paused = 0;

            if (channel)
            {
                if (sound)
                {
                    result = FMOD_Sound_GetLength(sound, &lenms, FMOD_TIMEUNIT_MS);
                    if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                    {
                        ERRCHECK(result);
                    }
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
            }

            printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s : %s\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : "Playing ", title);
            fflush(stdout);
        }

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    if (sound)
    {
        result = FMOD_Sound_Release(sound);
        ERRCHECK(result);
    }
    if (isplaylist)
    {
        result = FMOD_Sound_Release(playlist);
        ERRCHECK(result);
    }
    result = FMOD_System_Close(system);
    ERRCHECK(result);
    result = FMOD_System_Release(system);
    ERRCHECK(result);

    return 0;
}
