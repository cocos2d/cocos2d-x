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

// 用来定向输入框行为的结构体
struct WIN32INPUTBOX_PARAM
{
  friend class CWin32InputBox;

  //
  IN OPTIONAL bool bMultiline;

  // 给它传递非零参数来使用这个内存对话框模板
  IN OPTIONAL LPVOID DlgTemplateData;

  // 给它传递非零参数来从资源中加载对话框模板
  IN OPTIONAL LPCSTR DlgTemplateName;

  // 如果给"DlgTemplateName"和"DlgTemplateData"传递零，对话框就会使用默认的内置资源
  

  // 决定是否放置在显示器或者所有者窗口中间的变量
  IN OPTIONAL bool bCenter;

  // 给对话框添加更多的类型的变量
  IN OPTIONAL DWORD dwStylesPlus, dwStylesMinus;
  IN OPTIONAL DWORD dwExStylesPlus, dwExStylesMinus;

  IN LPCSTR szTitle, szPrompt;

  // 返回缓冲区
  OUT LPSTR szResult;
  IN DWORD nResultSize;

  // 所有者窗口的句柄
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
