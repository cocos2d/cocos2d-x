
#ifndef quickcocos2dx_ioapi_mem_h
#define quickcocos2dx_ioapi_mem_h

#include "ioapi.h"


namespace cocos2d {
    voidpf ZCALLBACK fopen_mem_func OF((
                                        voidpf opaque,
                                        const char* filename,
                                        int mode));

    voidpf ZCALLBACK fopen_mem_func64_32 OF((
                                        voidpf opaque,
                                        const void* filename,
                                        int mode));

    uLong ZCALLBACK fread_mem_func OF((
                                       voidpf opaque,
                                       voidpf stream,
                                       void* buf,
                                       uLong size));

    uLong ZCALLBACK fwrite_mem_func OF((
                                        voidpf opaque,
                                        voidpf stream,
                                        const void* buf,
                                        uLong size));

    long ZCALLBACK ftell_mem_func OF((
                                      voidpf opaque,
                                      voidpf stream));

    long ZCALLBACK fseek_mem_func OF((
                                      voidpf opaque,
                                      voidpf stream,
                                      uLong offset,
                                      int origin));

    int ZCALLBACK fclose_mem_func OF((
                                      voidpf opaque,
                                      voidpf stream));

    int ZCALLBACK ferror_mem_func OF((
                                      voidpf opaque,
                                      voidpf stream));

    void fill_memory_filefunc64_32 (zlib_filefunc64_32_def* pzlib_filefunc_def);


    typedef struct ourmemory_s {
        void *base; /* Base of the region of memory we're using */
        uLong size; /* Size of the region of memory we're using */
        uLong limit; /* Furthest we've written */
        uLong cur_offset; /* Current offset in the area */
    } ourmemory_t;
    
}

#endif
