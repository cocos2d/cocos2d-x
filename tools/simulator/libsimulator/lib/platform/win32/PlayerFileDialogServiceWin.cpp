
#include <string.h>

#include "stdafx.h"
#include <Windowsx.h>
#include <Shlobj.h>
#include <Commdlg.h>

#include "cocos2d.h"
#include "PlayerUtils.h"
#include "PlayerFileDialogServiceWin.h"

PLAYER_NS_BEGIN

PlayerFileDialogServiceWin::PlayerFileDialogServiceWin(HWND hwnd)
: _hwnd(hwnd)
{
}

std::string PlayerFileDialogServiceWin::openFile(const std::string &title,
                                                 const std::string &directory,
                                                 const std::string &extensions) const
{
    vector<std::string> result = openMultipleInternal(title, directory, extensions, false);
    if (result.size())
    {
        return result.at(0);
    }
    return std::string();
}

std::vector<std::string> PlayerFileDialogServiceWin::openMultiple(const std::string &title,
                                                                  const std::string &directory,
                                                                  const std::string &extensions) const
{
    return openMultipleInternal(title, directory, extensions, true);
}

std::string PlayerFileDialogServiceWin::saveFile(const std::string &title,
                                                 const std::string &path) const
{
    std::u16string u16title;
    cocos2d::StringUtils::UTF8ToUTF16(title, u16title);

    WCHAR buff[MAX_PATH + 1] = {0};
    if (path.length() > 0)
    {
        std::u16string u16filename;
        cocos2d::StringUtils::UTF8ToUTF16(path, u16filename);
        wcscpy_s(buff, (WCHAR*)u16filename.c_str());
    }

    OPENFILENAME ofn = {0};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = _hwnd;
    ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
    ofn.lpstrTitle = (LPCTSTR)u16title.c_str();
    ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_LONGNAMES;
    ofn.lpstrFile = buff;
    ofn.nMaxFile = MAX_PATH;

    std::string result;
    if (!GetSaveFileName(&ofn))
    {
        // user cancel dialog, GetSaveFileName() will return FALSE
        DWORD err = CommDlgExtendedError();
        if (err)
        {
            CCLOG("PlayerFileDialogServiceWin::saveFile() - failed, title (%s),  error code = %u", title.c_str(), err);
        }
        return result;
    }

    cocos2d::StringUtils::UTF16ToUTF8((char16_t*)buff, result);
    return result;
}

// for openDirectory
int CALLBACK BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    if (uMsg == BFFM_INITIALIZED && lpData)
    {
        LPCTSTR path = (LPCTSTR)lpData;
        SendMessage(hwnd, BFFM_SETSELECTION, true, (LPARAM)path);
    }
    return 0;
}

std::string PlayerFileDialogServiceWin::openDirectory(const std::string &title,
                                                      const std::string &directory) const
{
    std::u16string u16title;
    cocos2d::StringUtils::UTF8ToUTF16(title, u16title);

    WCHAR basedir[MAX_PATH + 1];
    if (directory.length())
    {
        std::u16string u16directory;
        cocos2d::StringUtils::UTF8ToUTF16(directory, u16directory);
        wcscpy_s(basedir, (WCHAR*)u16directory.c_str());
    }
    else
    {
        GetCurrentDirectory(MAX_PATH, basedir);
    }

    WCHAR buff[MAX_PATH + 1] = {0};
    BROWSEINFO bi = {0};
    bi.hwndOwner = _hwnd;
    bi.pszDisplayName = buff;
    bi.lpszTitle = (LPCTSTR)u16title.c_str();
    bi.lParam = (LPARAM)basedir;
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NONEWFOLDERBUTTON | BIF_NEWDIALOGSTYLE;
    bi.lpfn = BrowseFolderCallback;

    PIDLIST_ABSOLUTE pid = SHBrowseForFolder(&bi);
    if (pid)
    {
        SHGetPathFromIDList(pid, buff);
        std::string result;
        cocos2d::StringUtils::UTF16ToUTF8((char16_t*)buff, result);
        return result;
    }
    else
    {
        return std::string("");
    }
}

LPTSTR PlayerFileDialogServiceWin::parseExtensions(const std::string &extensions) const
{
    static WCHAR *defaultExtensions = L"All Files (*.*)\0*.*\0";
    if (extensions.length() == 0)
    {
        WCHAR *buff = new WCHAR[wcslen(defaultExtensions) + 1];
        wcscpy(buff, defaultExtensions);
        return buff;
    }

    // 1.
    // "Lua Script File|*.lua;JSON File|*.json"
    // to
    // "Lua Script File (*.lua)\0*.lua\0JSON File (*.json)\0*.json\0";
    // 
    // 2.
    // "Lua Script File|*.lua;Cocos Studio File|*.csd,*.csb"
    // to
    // "Lua Script File (*.lua)\0*.lua\0Cocos Studio File (*.csd;*.csb")\0*.csd;*.csb"\0";
    std::u16string u16extensions;
    std::u16string split1((char16_t*)L";");
    std::u16string split2((char16_t*)L"|");
    std::u16string split3((char16_t*)L",");
    std::string extensionsArg(extensions);
    cocos2d::StringUtils::UTF8ToUTF16(extensions, u16extensions);
    vector<std::u16string> pairs = splitString(u16extensions, split1);

    size_t buffsize = extensions.length() * 6;
    WCHAR *buff = new WCHAR[buffsize];
    memset(buff, 0, sizeof(WCHAR) * buffsize);
    size_t offset = 0;
    for (auto it = pairs.begin(); it != pairs.end(); ++it)
    {
        vector<std::u16string> p = splitString(*it, split2);
        std::u16string descr, ext;
        if (p.size() < 2)
        {
            descr = ext = *it;
        }
        else
        {
            descr = p.at(0);
            ext = p.at(1);
        }

        // *.csd,*.csb -> *.csd;*.csb
        std::replace(ext.begin(), ext.end(), ',', ';');

        wcscat(buff + offset, (WCHAR*)descr.c_str());
        wcscat(buff + offset, L" (");
        wcscat(buff + offset, (WCHAR*)ext.c_str());
        wcscat(buff + offset, L")");
        offset += descr.length() + ext.length() + 4;
        wcscat(buff + offset, (WCHAR*)ext.c_str());
        offset += ext.length() + 1;
    }

    return buff;
}

std::vector<std::string> PlayerFileDialogServiceWin::openMultipleInternal(const std::string &title,
                                                                          const std::string &directory,
                                                                          const std::string &extensions,
                                                                          bool isMulti) const
{
    std::u16string u16title;
    cocos2d::StringUtils::UTF8ToUTF16(title, u16title);

    WCHAR basedir[MAX_PATH + 1];
    if (directory.length())
    {
        std::u16string u16directory;
        cocos2d::StringUtils::UTF8ToUTF16(directory, u16directory);
        wcscpy_s(basedir, (WCHAR*)u16directory.c_str());
    }
    else
    {
        GetCurrentDirectory(MAX_PATH, basedir);
    }

    size_t buffsize = MAX_PATH;
    if (isMulti) buffsize = MAX_PATH * 64;
    WCHAR *buff = new WCHAR[buffsize + 1];
    memset(buff, 0, sizeof(WCHAR) * (buffsize + 1));

    OPENFILENAME ofn = {0};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = _hwnd;
    ofn.lpstrFilter = parseExtensions(extensions);
    ofn.lpstrTitle = (LPCTSTR)u16title.c_str();
    ofn.lpstrInitialDir = basedir;
    ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_LONGNAMES;
    if (isMulti) ofn.Flags |= OFN_ALLOWMULTISELECT | OFN_EXPLORER;
    ofn.lpstrFile = buff;
    ofn.nMaxFile = buffsize;

    vector<std::string> result;
    BOOL ret = GetOpenFileName(&ofn);
    delete[] ofn.lpstrFilter;
    if (!ret)
    {
        // user cancel dialog, GetOpenFileName() will return FALSE
        DWORD err = CommDlgExtendedError();
        if (err)
        {
            CCLOG("PlayerFileDialogServiceWin::openMultipleInternal() - failed, title (%s),  error code = %u", title.c_str(), err);
        }
        delete[] buff;
        return result;
    }

    if (isMulti)
    {
        WORD offset = 0;
        std::string path;
        while (buff[offset] != '\0')
        {
            std::string filename;
            std::u16string u16filename((char16_t*)(buff + offset));
            cocos2d::StringUtils::UTF16ToUTF8(u16filename, filename);

            if (offset == 0)
            {
                path = filename;
                if (path[path.length() - 1] != '\\')
                {
                    path.append("\\");
                }
            }
            else
            {
                result.push_back(path + filename);
            }
            offset += u16filename.length() + 1;
        }
    }
    else
    {
        std::string path;
        cocos2d::StringUtils::UTF16ToUTF8((char16_t*)buff, path);
        result.push_back(path);
    }
    delete[] buff;
    return result;
}

PLAYER_NS_END
