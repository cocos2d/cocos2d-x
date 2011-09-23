/*===============================================================================================
 ReadTags Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2011.

 This example shows how to read tags from sound files
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
    FMOD_RESULT      result;
    FMOD_TAG         tag;
    int              numtags, numtagsupdated, count;
    unsigned int     version;

    printf("==================================================================\n");
    printf("ReadTags Example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("==================================================================\n\n");

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
        getch();
        return 0;
    }

    result = FMOD_System_Init(system, 100, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);

    /*
        Open the specified file. Use FMOD_CREATESTREAM and FMOD_OPENONLY so it opens quickly
    */
    result = FMOD_System_CreateSound(system, "../media/wave.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_OPENONLY, 0, &sound);
    ERRCHECK(result);

    /*
        Read and display all tags associated with this file
    */
    for (;;)
    {
        /*
            An index of -1 means "get the first tag that's new or updated".
            If no tags are new or updated then getTag will return FMOD_ERR_TAGNOTFOUND.
            This is the first time we've read any tags so they'll all be new but after we've read them, 
            they won't be new any more.
        */
        if (FMOD_Sound_GetTag(sound, 0, -1, &tag) != FMOD_OK)
        {
            break;
        }
        if (tag.datatype == FMOD_TAGDATATYPE_STRING)
        {
            printf("%s = %s (%d bytes)\n", tag.name, tag.data, tag.datalen);
        }
        else
        {
            printf("%s = <binary> (%d bytes)\n", tag.name, tag.datalen);
        }
    }
    printf("\n");

    /*
        Read all the tags regardless of whether they're updated or not. Also show the tag type.
    */
    result = FMOD_Sound_GetNumTags(sound, &numtags, &numtagsupdated);
    ERRCHECK(result);
    for (count=0; count < numtags; count++)
    {
        result = FMOD_Sound_GetTag(sound, 0, count, &tag);
        ERRCHECK(result);

        switch (tag.type)
        {
            case FMOD_TAGTYPE_UNKNOWN :
                printf("FMOD_TAGTYPE_UNKNOWN  ");
                break;

            case FMOD_TAGTYPE_ID3V1 :
                printf("FMOD_TAGTYPE_ID3V1  ");
                break;

            case FMOD_TAGTYPE_ID3V2 :
                printf("FMOD_TAGTYPE_ID3V2  ");
                break;

            case FMOD_TAGTYPE_VORBISCOMMENT :
                printf("FMOD_TAGTYPE_VORBISCOMMENT  ");
                break;

            case FMOD_TAGTYPE_SHOUTCAST :
                printf("FMOD_TAGTYPE_SHOUTCAST  ");
                break;

            case FMOD_TAGTYPE_ICECAST :
                printf("FMOD_TAGTYPE_ICECAST  ");
                break;

            case FMOD_TAGTYPE_ASF :
                printf("FMOD_TAGTYPE_ASF  ");
                break;

            case FMOD_TAGTYPE_FMOD :
                printf("FMOD_TAGTYPE_FMOD  ");
                break;

            case FMOD_TAGTYPE_USER :
                printf("FMOD_TAGTYPE_USER  ");
                break;
        }

        if (tag.datatype == FMOD_TAGDATATYPE_STRING)
        {
            printf("%s = %s (%d bytes)\n", tag.name, tag.data, tag.datalen);
        }
        else
        {
            printf("%s = ??? (%d bytes)\n", tag.name, tag.datalen);
        }
    }
    printf("\n");

    /*
        Find a specific tag by name. Specify an index > 0 to get access to multiple tags of the same name.
    */
    result = FMOD_Sound_GetTag(sound, "ARTIST", 0, &tag);
    ERRCHECK(result);
    printf("%s = %s (%d bytes)\n", tag.name, tag.data, tag.datalen);
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
