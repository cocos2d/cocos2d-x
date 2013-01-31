#ifndef __03022006__WIN32INPUTBOX__
#define __03022006__WIN32INPUTBOX__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
/*

This library is (c) Elias Bachaalany aka lallous <lallousx86@yahoo.com>
You may use this library under the following license agreement:

The zlib/libpng License.
---------------------------
This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, 
and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; 
   you must not claim that you wrote the original software. 
   If you use this software in a product, an acknowledgment in the product 
   documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, 
   and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution. 

*/

#include <windows.h>
#include <tchar.h>

class CWin32InputBox;

// Structure used to orient the inputbox behavior
struct WIN32INPUTBOX_PARAM
{
  friend class CWin32InputBox;

  //
  IN OPTIONAL bool bMultiline;

  // Pass this as none zero so to use this memory dlg template
  IN OPTIONAL LPVOID DlgTemplateData;

  // Pass this as none ZERO so to load DLGTEMPLATE from resources
  IN OPTIONAL LPCSTR DlgTemplateName;

  // passing both "DlgTemplateName" and "DlgTemplateData" ZERO will cause
  // the dialog to use his default embedded resource

  // Center on monitor or owner window?
  IN OPTIONAL bool bCenter;

  // Want to add more styles to the dialog?
  IN OPTIONAL DWORD dwStylesPlus, dwStylesMinus;
  IN OPTIONAL DWORD dwExStylesPlus, dwExStylesMinus;

  IN LPCSTR szTitle, szPrompt;

  // Return buffer
  OUT LPSTR szResult;
  IN DWORD nResultSize;

  // Owner window
  HWND hwndOwner;
  HINSTANCE hInstance;

  short xPos, yPos;

  WIN32INPUTBOX_PARAM();
private:
  HWND hDlg;
};

class CWin32InputBox
{
private:
  WIN32INPUTBOX_PARAM *_param;
  static LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
  HWND _hwndEditCtrl;

  void InitDialog();
  void SetParam(WIN32INPUTBOX_PARAM *);
  WIN32INPUTBOX_PARAM * GetParam();

public:

  CWin32InputBox(WIN32INPUTBOX_PARAM *);
  ~CWin32InputBox();

  static INT_PTR InputBoxEx(WIN32INPUTBOX_PARAM *);
  static INT_PTR InputBox(
    LPCSTR szTitle, 
    LPCSTR szPrompt, 
    LPSTR szResult, 
    DWORD nResultSize,
    bool bMultiLine = false,
    HWND hwndParent = 0);

  static std::string AnsiToUtf8(std::string strAnsi);
  static std::string Utf8ToAnsi(std::string strUTF8);
};

#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */

#endif