
#include "stdafx.h"

#include <Commdlg.h>
#include <Shlobj.h>
#include <winnls.h>
#include <shobjidl.h>
#include <objbase.h>
#include <objidl.h>
#include <shlguid.h>
#include <shellapi.h>

#include "PlayerWin32.h"
#include "PlayerFileDialogServiceWin32.h"

PLAYER_NS_BEGIN

string PlayerFileDialogServiceWin32::openFile(const char *title,
    const char *directory /* = NULL */,
    const char *extensions /* = NULL */)
{
    if (!title) title = "Open File";
    WCHAR *title_ws = utf8towide(title);

    PlayerWin32 *player = dynamic_cast<PlayerWin32*>(PlayerProtocol::getInstance());
    HWND hwnd = player->getWindowHandle();

    OPENFILENAME ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = L"Lua Script File (*.lua)\0*.lua\0";
    ofn.lpstrTitle = title_ws;

    WCHAR *directory_ws = NULL;
    if (directory)
    {
        directory_ws = utf8towide(directory);
        if (isDirectoryExists(directory_ws))
        {
            ofn.lpstrInitialDir = directory_ws;
        }
    }
    ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    WCHAR path_ws[MAX_PATH];
    ofn.lpstrFile = path_ws;
    ofn.nMaxFile = MAX_PATH;

    if (directory_ws) delete[] directory_ws;
    if (title_ws) delete[] title_ws;

    if (GetOpenFileName(&ofn))
    {
        char *path = widetoutf8(path_ws);
        string path = string(path);
        delete[] path;
        return path;
    }

    return string();
}

string PlayerFileDialogServiceWin32::openDirectory(const char *title,
    const char *directory /* = NULL */)
{
    if (!title) title = "Open File";
    WCHAR *title_ws = utf8towide(title);

    PlayerWin32 *player = dynamic_cast<PlayerWin32*>(PlayerProtocol::getInstance());
    HWND hwnd = player->getWindowHandle();

    char buff[MAX_PATH + 1] = { 0 };
    WCHAR curr[MAX_PATH + 1] = { 0 };

    if (baseDir.length() > 0)
    {
        MultiByteToWideChar(CP_UTF8, 0, baseDir.c_str(), baseDir.length(), curr, MAX_PATH);
    }
    else
    {
        GetCurrentDirectory(MAX_PATH + 1, curr);
    }

    BROWSEINFOA bi = { 0 };
    bi.hwndOwner = m_hwndDialog;
    bi.pszDisplayName = buff;
    bi.lpszTitle = "Select Project Directory";
    bi.lParam = reinterpret_cast<LPARAM>(curr);
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NONEWFOLDERBUTTON | BIF_NEWDIALOGSTYLE;
    bi.lpfn = BrowseFolderCallback;

    PIDLIST_ABSOLUTE pid = SHBrowseForFolderA(&bi);
    if (pid)
    {
        SHGetPathFromIDListA(pid, buff);
        return string(buff);
    }
    else
    {
        return string("");
    }
}

vector<string> PlayerFileDialogServiceWin32::openMultiple(const char *title,
    const char *directory /* = NULL */)
{

}

string PlayerFileDialogServiceWin32::saveFile(const char *title,
    const char *filename,
    const char *directory)
{

}

PLAYER_NS_END
