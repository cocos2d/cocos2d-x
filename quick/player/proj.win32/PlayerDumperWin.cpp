
#include "stdafx.h"
#include <dbghelp.h>
#include "PlayerDumper.h"
#include <shellapi.h>

struct _EXCEPTION_POINTERS;

static HMODULE GetDebugHelperDll(FARPROC* ppfnMiniDumpWriteDump);
LONG WINAPI handleException(struct _EXCEPTION_POINTERS* pExceptionInfo);

typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)(HANDLE hProcess, DWORD dwPid, HANDLE hFile, MINIDUMP_TYPE DumpType,
										 CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
										 CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
										 CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

static TCHAR szAppName[MAX_PATH] = {0};

void activePlayerDumper()
{
	// todo: init the AppName

	MINIDUMPWRITEDUMP pfnMiniDumpWriteDump = NULL;
	HMODULE hDbgHelpDll = GetDebugHelperDll((FARPROC*)&pfnMiniDumpWriteDump);
	if (hDbgHelpDll)
	{
		if (pfnMiniDumpWriteDump)
			SetUnhandledExceptionFilter(handleException);
		FreeLibrary(hDbgHelpDll);
		hDbgHelpDll = NULL;
		pfnMiniDumpWriteDump = NULL;
	}
}

HMODULE GetDebugHelperDll(FARPROC* ppfnMiniDumpWriteDump)
{
	*ppfnMiniDumpWriteDump = NULL;
	HMODULE hDll = LoadLibrary(_T("DBGHELP.DLL"));
	if (hDll == NULL)
	{
		// if (bShowErrors) {
		// 	// Do *NOT* localize that string (in fact, do not use MFC to load it)!
		// 	MessageBox(NULL, _T("DBGHELP.DLL not found. Please install a DBGHELP.DLL."), m_szAppName, MB_ICONSTOP | MB_OK);
		// }
	}
	else
	{
		*ppfnMiniDumpWriteDump = GetProcAddress(hDll, "MiniDumpWriteDump");
		if (*ppfnMiniDumpWriteDump == NULL)
		{
			// if (bShowErrors) {
			// 	// Do *NOT* localize that string (in fact, do not use MFC to load it)!
			// 	MessageBox(NULL, _T("DBGHELP.DLL found is too old. Please upgrade to a newer version of DBGHELP.DLL."), m_szAppName, MB_ICONSTOP | MB_OK);
			// }
			hDll = NULL;
		}
	}
	return hDll;
}

extern "C" void toluafix_test_call_msg();

LONG WINAPI handleException(struct _EXCEPTION_POINTERS* pExceptionInfo)
{
	toluafix_test_call_msg();
	LONG lRetValue = EXCEPTION_CONTINUE_SEARCH;
	TCHAR szResult[_MAX_PATH + 1024] = {0};
	MINIDUMPWRITEDUMP pfnMiniDumpWriteDump = NULL;
	HMODULE hDll = GetDebugHelperDll((FARPROC*)&pfnMiniDumpWriteDump);
	HINSTANCE	hInstCrashReporter = NULL;	//ADDED by fengwen on 2006/11/15 : 使用新的发送错误报告机制。

	if (hDll)
	{
		if (pfnMiniDumpWriteDump)
		{
			// Ask user if they want to save a dump file
			// Do *NOT* localize that string (in fact, do not use MFC to load it)!
			//COMMENTED by fengwen on 2006/11/15	<begin> : 使用新的发送错误报告机制。
			if (MessageBox(NULL, _T("Player crashed :-(\r\n\r\nA diagnostic file can be created which will help the author to resolve this problem. This file will be saved on your Disk (and not sent).\r\n\r\nDo you want to create this file now?"), szAppName, MB_ICONSTOP | MB_YESNO) == IDYES)
			//COMMENTED by fengwen on 2006/11/15	<end> : 使用新的发送错误报告机制。
			{
				// Create full path for DUMP file
				TCHAR szDumpPath[_MAX_PATH] = {0};
				GetModuleFileName(NULL, szDumpPath, ARRAYSIZE(szDumpPath));
				LPTSTR pszFileName = _tcsrchr(szDumpPath, _T('\\'));
				if (pszFileName) {
					pszFileName++;
					*pszFileName = _T('\0');
				}

				TCHAR szCrashReport[MAX_PATH] = {0};
				_tcsncat(szCrashReport,szDumpPath,ARRAYSIZE(szCrashReport) - 1);
				_tcsncat(szCrashReport,_T("CrashReporter.exe"),ARRAYSIZE(szCrashReport) - 1);

				// Replace spaces and dots in file name.
				TCHAR szBaseName[_MAX_PATH] = {0};
				_tcsncat(szBaseName, szAppName, ARRAYSIZE(szBaseName) - 1);
				LPTSTR psz = szBaseName;
				while (*psz != _T('\0')) {
					if (*psz == _T('.'))
						*psz = _T('-');
					else if (*psz == _T(' '))
						*psz = _T('_');
					psz++;
				}
				_tcsncat(szDumpPath, szBaseName, ARRAYSIZE(szDumpPath) - 1);
				_tcsncat(szDumpPath, _T(".dmp"), ARRAYSIZE(szDumpPath) - 1);

				HANDLE hFile = CreateFile(szDumpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				if (hFile != INVALID_HANDLE_VALUE)
				{
					_MINIDUMP_EXCEPTION_INFORMATION ExInfo = {0};
					ExInfo.ThreadId = GetCurrentThreadId();
					ExInfo.ExceptionPointers = pExceptionInfo;
					ExInfo.ClientPointers = NULL;

					BOOL bOK = (*pfnMiniDumpWriteDump)(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL);
					if (bOK)
					{
						// Do *NOT* localize that string (in fact, do not use MFC to load it)!
						_sntprintf(szResult, ARRAYSIZE(szResult), _T("Saved dump file to \"%s\".\r\n\r\nPlease send this file together with a detailed bug report to dumps@emule-project.net !\r\n\r\nThank you for helping to improve eMule."), szDumpPath);
						lRetValue = EXCEPTION_EXECUTE_HANDLER;

						//ADDED by fengwen on 2006/11/15	<begin> : 使用新的发送错误报告机制。
						hInstCrashReporter = ShellExecute(NULL, _T("open"), szCrashReport, szDumpPath, NULL, SW_SHOW);
						if (hInstCrashReporter <= (HINSTANCE)32)
							lRetValue = EXCEPTION_CONTINUE_SEARCH;
						//ADDED by fengwen on 2006/11/15	<end> : 使用新的发送错误报告机制。
					}
					else
					{
						// Do *NOT* localize that string (in fact, do not use MFC to load it)!
						_sntprintf(szResult, ARRAYSIZE(szResult), _T("Failed to save dump file to \"%s\".\r\n\r\nError: %u"), szDumpPath, GetLastError());
					}
					CloseHandle(hFile);
				}
				else
				{
					// Do *NOT* localize that string (in fact, do not use MFC to load it)!
					_sntprintf(szResult, ARRAYSIZE(szResult), _T("Failed to create dump file \"%s\".\r\n\r\nError: %u"), szDumpPath, GetLastError());
				}
			}
		}
		FreeLibrary(hDll);
		hDll = NULL;
		pfnMiniDumpWriteDump = NULL;
	}

	//COMMENTED by fengwen on 2006/11/15	<begin> : 使用新的发送错误报告机制。
	//if (szResult[0] != _T('\0'))
	//	MessageBox(NULL, szResult, m_szAppName, MB_ICONINFORMATION | MB_OK);
	//COMMENTED by fengwen on 2006/11/15	<end> : 使用新的发送错误报告机制。

#ifndef _DEBUG
	if (EXCEPTION_EXECUTE_HANDLER == lRetValue)		//ADDED by fengwen on 2006/11/15 : 由此filter处理了异常，才去中止进程。
	{
		// Exit the process only in release builds, so that in debug builds the exceptio is passed to a possible
		// installed debugger
		ExitProcess(0);
	}
	else
		return lRetValue;

#else

	return lRetValue;
#endif
}
