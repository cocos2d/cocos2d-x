/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// 
#ifndef SkOSFile_DEFINED
#define SkOSFile_DEFINED

#include "SkString.h"

#if defined(SK_BUILD_FOR_MAC) || defined(SK_BUILD_FOR_UNIX)
    #include <dirent.h>
#endif

struct SkFILE;

enum SkFILE_Flags {
    kRead_SkFILE_Flag   = 0x01,
    kWrite_SkFILE_Flag  = 0x02
};

SkFILE* sk_fopen(const char path[], SkFILE_Flags);
void    sk_fclose(SkFILE*);

size_t  sk_fgetsize(SkFILE*);
/** Return true if the file could seek back to the beginning
*/
bool    sk_frewind(SkFILE*);

size_t  sk_fread(void* buffer, size_t byteCount, SkFILE*);
size_t  sk_fwrite(const void* buffer, size_t byteCount, SkFILE*);
void    sk_fflush(SkFILE*);

int     sk_fseek( SkFILE*, size_t, int );
size_t  sk_ftell( SkFILE* );

class SkOSFile {
public:
    class Iter {
    public:
        Iter();
        Iter(const char path[], const char suffix[] = NULL);
        ~Iter();

        void reset(const char path[], const char suffix[] = NULL);
        bool next(SkString* name, bool getDir = false);

    private:
#ifdef SK_BUILD_FOR_WIN
        HANDLE      fHandle;
        uint16_t*   fPath16;
#elif defined(SK_BUILD_FOR_MAC) || defined(SK_BUILD_FOR_UNIX)
        DIR*        fDIR;
        SkString    fPath, fSuffix;
#endif
    };
};

class SkUTF16_Str {
public:
    SkUTF16_Str(const char src[]);
    ~SkUTF16_Str()
    {
        sk_free(fStr);
    }
    const uint16_t* get() const { return fStr; }

private:
    uint16_t*   fStr;
};

#endif

