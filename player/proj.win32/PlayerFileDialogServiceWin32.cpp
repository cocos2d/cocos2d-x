
#include "stdafx.h"

#include <Commdlg.h>
#include <Shlobj.h>

#include "PlayerWin32.h"
#include "PlayerFileDialogServiceWin32.h"

PLAYER_NS_BEGIN

string PlayerFileDialogServiceWin32::openFile(const char *title,
    const char *directory /* = NULL */,
    const char *extensions /* = NULL */)
{
    if (!title) title = "Open File";
    WCHAR *title_ws = utf8towide(title);

    OPENFILENAME ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = dynamic_cast<PlayerWin32*>(PlayerProtocol::getInstance())->getWindowHandle();
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

    WCHAR path_ws[MAX_PATH + 1];
    ofn.lpstrFile = path_ws;
    ofn.nMaxFile = MAX_PATH;

    if (directory_ws) delete[] directory_ws;
    if (title_ws) delete[] title_ws;

    if (GetOpenFileName(&ofn))
    {
        char *path = widetoutf8(path_ws);
        string out = string(path);
        delete[] path;
        return out;
    }

    return string();
}

int CALLBACK BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    if (uMsg == BFFM_INITIALIZED && lpData)
    {
        LPCTSTR path = reinterpret_cast<LPCTSTR>(lpData);
        if (path)
        {
            SendMessage(hwnd, BFFM_SETSELECTION, true, (LPARAM)path);
        }
    }
    return 0;
}

string PlayerFileDialogServiceWin32::openDirectory(const char *title,
    const char *directory /* = NULL */)
{
    if (!title) title = "Open Directory";
    WCHAR *title_ws = utf8towide(title);

    WCHAR *cwd = NULL;
    if (directory)
    {
        cwd = utf8towide(directory);
    }
    else
    {
        cwd = new WCHAR[MAX_PATH + 1];
        GetCurrentDirectory(MAX_PATH, cwd);
    }

    WCHAR path_ws[MAX_PATH + 1];
    BROWSEINFO bi = { 0 };
    bi.hwndOwner = dynamic_cast<PlayerWin32*>(PlayerProtocol::getInstance())->getWindowHandle();
    bi.pszDisplayName = path_ws;
    bi.lpszTitle = title_ws;
    bi.lParam = reinterpret_cast<LPARAM>(cwd);
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NONEWFOLDERBUTTON | BIF_NEWDIALOGSTYLE;
    bi.lpfn = BrowseFolderCallback;

    PIDLIST_ABSOLUTE pid = SHBrowseForFolder(&bi);

    if (cwd) delete[] cwd;
    if (title_ws) delete[] title_ws;

    if (pid)
    {
        SHGetPathFromIDList(pid, path_ws);
        char *path = widetoutf8(path_ws);
        string out = string(path);
        delete[] path;
        return out;
    }
    else
    {
        return string();
    }
}

vector<string> PlayerFileDialogServiceWin32::openMultiple(const char *title,
    const char *directory /* = NULL */)
{
    vector<string> paths;

    return paths;
}

string PlayerFileDialogServiceWin32::saveFile(const char *title,
    const char *filename,
    const char *directory)
{

    return string();
}

PLAYER_NS_END
