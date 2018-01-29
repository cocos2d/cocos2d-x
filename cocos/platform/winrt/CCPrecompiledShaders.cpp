/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "platform/winrt/CCPrecompiledShaders.h"
#include "platform/winrt/CCWinRTUtils.h"
#include "renderer/CCGLProgram.h"
#include "platform/winrt/sha1.h"

using namespace Windows::Graphics::Display;
using namespace Windows::Storage;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
using namespace concurrency;

NS_CC_BEGIN

// singleton stuff
static CCPrecompiledShaders *s_pPrecompiledShaders = nullptr;

#define SHADER_NAME_PREFIX "s_"


CCPrecompiledShaders* CCPrecompiledShaders::getInstance(void)
{
    if (!s_pPrecompiledShaders)
    {
        s_pPrecompiledShaders = new CCPrecompiledShaders();
    }

    return s_pPrecompiledShaders;
}

CCPrecompiledShaders::CCPrecompiledShaders(void) 
    : m_isDirty(false)
{
    Init();
}

void CCPrecompiledShaders::Init(void)
{
    m_programs.clear();
    m_precompiledPrograms.clear();

    // add existing precompiled programs to dictionary
    loadPrecompiledPrograms();
}

CCPrecompiledShaders::~CCPrecompiledShaders(void)
{
}

static std::string computeHash(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray) 
{
    SHA1Context sha;
    int err;
    err = SHA1Reset(&sha);
    std::string result = "";
    uint8_t hash[SHA1HashSize];
    char hashString[SHA1HashSize * 2 + 1];

    if(!err)
    {
        err = SHA1Input(&sha,(const unsigned char *) vShaderByteArray,static_cast<unsigned int>(strlen(vShaderByteArray)));
    }
    if(!err)
    {
        err = SHA1Input(&sha,(const unsigned char *) fShaderByteArray, static_cast<unsigned int>(strlen(fShaderByteArray)));
    }
    if(!err)
    {
        char* shader_version = (char*) glGetString(GL_SHADING_LANGUAGE_VERSION);
        err = SHA1Input(&sha,(const unsigned char *) shader_version, static_cast<unsigned int>(strlen(shader_version)));
    }
    if(!err)
    {
        err = SHA1Result(&sha, hash);
    }
    if(!err)
    {
        SHA1ConvertMessageToString(hash, hashString);
        result = hashString;
    }

    return result;
}

std::string CCPrecompiledShaders::addShaders(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray)
{
    return computeHash(vShaderByteArray, fShaderByteArray);
}


void CCPrecompiledShaders::loadPrecompiledPrograms()
{
    m_precompiledPrograms.clear();
#if defined(PRECOMPILED_SHADERS)
    for(int i = 0; i < s_numPrograms; i++)
    {
        PrecompiledProgram* p = new PrecompiledProgram();
        p->key = s_programKeys[i];
        p->program = s_programs[i];
        p->length = s_programLengths[i];
        m_precompiledPrograms[s_programKeys[i]] = p;
    }
#endif
}

void CCPrecompiledShaders::addPrecompiledProgram(const char* key, const unsigned char* program, int programLength)
{
    std::string id = key;
    PrecompiledProgram* p = nullptr;
    auto it = m_precompiledPrograms.find(id);
    if (it != m_precompiledPrograms.end())
    {
        p = it->second;
    }
    else
    {
        p = new PrecompiledProgram();
        m_precompiledPrograms[id] = p;
    }
    p->key = key;
    p->program = program;
    p->length = programLength;
}

bool CCPrecompiledShaders::loadProgram(GLuint program, const GLchar* vShaderByteArray, const GLchar* fShaderByteArray)
{
    std::string id = computeHash(vShaderByteArray, fShaderByteArray);

    auto it = m_precompiledPrograms.find(id);
    if(it == m_precompiledPrograms.end())
        return false;

    glProgramBinaryOES(program, GL_PROGRAM_BINARY_ANGLE, (const GLvoid*) it->second->program, it->second->length);

    return true;
}

bool CCPrecompiledShaders::addProgram(GLuint program, const std::string& id)
{
    int length;

    auto it = m_programs.find(id);
    if(it != m_programs.end())
        return true;

    auto it2 = m_precompiledPrograms.find(id);
    if(it2 == m_precompiledPrograms.end())
        m_isDirty = true;

    CompiledProgram* p = new CompiledProgram();

    glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH_OES, &length);
    p->program.reserve(length);
    p->length = length;
    p->key = id;
    GLenum binaryFormat;
    glGetProgramBinaryOES(program, length, NULL, &binaryFormat, p->program.data());
    m_programs[id] = p;

    return true;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

void CCPrecompiledShaders::savePrecompiledPrograms(Windows::Storage::StorageFolder^ folder)
{
    Platform::String ^fileName = L"precompiledshaders.h";

    auto saveTask = create_task(folder->CreateFileAsync(fileName, CreationCollisionOption::ReplaceExisting));

    saveTask.then([this](StorageFile^ file)
    {
        InMemoryRandomAccessStream^ memoryStream = ref new InMemoryRandomAccessStream(); 
        DataWriter^ dataWriter = ref new DataWriter(memoryStream); 

        Platform::String^ programLengths = "const int s_programLengths[] = {";
        Platform::String^ programs = "const unsigned char* s_programs[] = {";
        Platform::String^ programKeys = "const char* s_programKeys[] = {";

        int numPrograms = 0;

        dataWriter->WriteString(L"#define PRECOMPILED_SHADERS\n\n");


        for (auto& iter : m_programs)
        {
            CompiledProgram* p = (CompiledProgram*)iter.second;
            Platform::String^ keyName = PlatformStringFromString(p->key);
            Platform::String^ programName = SHADER_NAME_PREFIX + keyName;

            dataWriter->WriteString("const unsigned char ");
            dataWriter->WriteString(programName);
            dataWriter->WriteString("[] = {\n");

            char temp[32];
            unsigned char* buffer = p->program.data();

            for(int i = 0; i < p->length - 1; i++)
            {
                if(i % 8 == 0)
                    dataWriter->WriteString("\n");
                sprintf_s(temp, "%3i, ", buffer[i]);
                dataWriter->WriteString(PlatformStringFromString(temp));
            }
            if((p->length - 1) % 8 == 0)
                dataWriter->WriteString("\n");
            sprintf_s(temp, "%3i, ", buffer[p->length - 1]);
            dataWriter->WriteString(PlatformStringFromString(temp));
            dataWriter->WriteString("\n};\n\n");

            if(numPrograms != 0)
            {
                programLengths += (",");
                programs += (",");
                programKeys += (",");
            }
            programLengths += p->length;
            programs += programName;
            programKeys += "\"" + keyName + "\"";
            numPrograms++;
        }

        programLengths += "};\n";
        programs += "};\n";
        programKeys += "};\n";

        Platform::String^ n = ref new Platform::String(L"const int s_numPrograms = ");
        n += numPrograms;
        n += ";\n";

        dataWriter->WriteString(n);
        dataWriter->WriteString(programLengths);
        dataWriter->WriteString(programs);
        dataWriter->WriteString(programKeys);

        return FileIO::WriteBufferAsync(file, dataWriter->DetachBuffer());
   });  

}

void CCPrecompiledShaders::savePrecompiledShaders()
{
    if(!m_isDirty)
        return;


    FolderPicker^ folderPicker = ref new FolderPicker();
    folderPicker->SuggestedStartLocation = PickerLocationId::Desktop;
    folderPicker->FileTypeFilter->Append(".h");

    auto saveTask = create_task(folderPicker->PickSingleFolderAsync());
    saveTask.then([this](StorageFolder^ folder)
    {
        if(folder != nullptr)
        {
            savePrecompiledPrograms(folder);
            m_isDirty = false;
       }
	});
}
#endif



NS_CC_END


