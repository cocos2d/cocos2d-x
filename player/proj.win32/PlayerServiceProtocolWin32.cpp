
#include "stdafx.h"

#include "PlayerServiceProtocolWin32.h"

PLAYER_NS_BEGIN

WCHAR *PlayerServiceProtocolWin32::utf8towide(const char *input)
{
    int size = MultiByteToWideChar(CP_UTF8, 0, input, -1, NULL, 0);
    WCHAR *out = new WCHAR[size];
    MultiByteToWideChar(CP_UTF8, 0, input, -1, out, size);
    return out;
}

char *PlayerServiceProtocolWin32::widetoutf8(WCHAR *input)
{
    int size = WideCharToMultiByte(CP_UTF8, 0, input, -1, NULL, 0, NULL, NULL);
    char *out = new char[size];
    WideCharToMultiByte(CP_UTF8, 0, input, -1, out, size, NULL, NULL);
    return out;
}

bool PlayerServiceProtocolWin32::isDirectoryExists(WCHAR *directory)
{
    DWORD dwAttrib = GetFileAttributes(directory);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool PlayerServiceProtocolWin32::isFileExists(WCHAR *path)
{
    DWORD dwAttrib = GetFileAttributes(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

PLAYER_NS_END
