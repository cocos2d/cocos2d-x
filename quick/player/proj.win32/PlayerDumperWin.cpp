
#include "stdafx.h"
#include <dbghelp.h>
#include "PlayerDumper.h"
#include <shellapi.h>

#pragma comment( lib, "dbghelp.lib" )

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

PBYTE   GetFuncCallStack(int nLevel/*=0*/, char* pBuf/*=NULL*/, PEXCEPTION_POINTERS pException/*=NULL*/)
{
	typedef struct STACK
	{
		STACK *	Ebp;
		PBYTE	Ret_Addr;
		DWORD	Param[0];
	} STACK, *PSTACK;

	STACK	Stack = { 0, 0 };
	PSTACK	Ebp;
	int nPos = 0;

	if (pException)	//fake frame for exception address
	{
		Stack.Ebp = (PSTACK)pException->ContextRecord->Ebp;
		Stack.Ret_Addr = (PBYTE)pException->ExceptionRecord->ExceptionAddress;
		Ebp = &Stack;
	}
	else
		Ebp = (PSTACK)&nLevel - 1;	//frame addr of DumpFuncAddress()
	if (pBuf)
		*pBuf = 0;

	bool bData = false;
	// Break trace on wrong stack frame.
	for (int Ret_Addr_I = 0; Ret_Addr_I <= nLevel;)
	{
		if (!IsBadReadPtr(Ebp, sizeof(PSTACK)) && !IsBadCodePtr(FARPROC(Ebp->Ret_Addr)))
		{
			if (pBuf)
			{
				sprintf(pBuf + nPos, "%p:%i ", Ebp->Ret_Addr, Ret_Addr_I);
				//nPos += 9;
				nPos += 11;
				bData = true;
			}
			if (Ret_Addr_I == nLevel)
				return pBuf ? (PBYTE)pBuf : Ebp->Ret_Addr;

			Ret_Addr_I++;
			Ebp = Ebp->Ebp;
		}
		else
			break;

	}
	if (bData)
		return pBuf ? (PBYTE)pBuf : Ebp->Ret_Addr;
	return 0;
}
//void trans_func(unsigned int u, EXCEPTION_POINTERS* pExp)
//{
//	throw *pExp;
//}
//
//void initialize_seh_trans_to_ce()
//{
//	_set_se_translator(trans_func);
//}

void dump_callstack(CONTEXT *context)
{
	STACKFRAME sf;
	memset(&sf, 0, sizeof(STACKFRAME));

	sf.AddrPC.Offset = context->Eip;
	sf.AddrPC.Mode = AddrModeFlat;
	sf.AddrStack.Offset = context->Esp;
	sf.AddrStack.Mode = AddrModeFlat;
	sf.AddrFrame.Offset = context->Ebp;
	sf.AddrFrame.Mode = AddrModeFlat;

	DWORD machineType = IMAGE_FILE_MACHINE_I386;

	HANDLE hProcess = GetCurrentProcess();
	HANDLE hThread = GetCurrentThread();

	for (;;)
	{
		if (!StackWalk(machineType, hProcess, hThread, &sf, context, 0, SymFunctionTableAccess, SymGetModuleBase, 0))
		{
			break;
		}

		if (sf.AddrFrame.Offset == 0)
		{
			break;
		}
		BYTE symbolBuffer[sizeof(SYMBOL_INFOW) + 1024];
		PSYMBOL_INFOW pSymbol = (PSYMBOL_INFOW)symbolBuffer;

		pSymbol->SizeOfStruct = sizeof(symbolBuffer);
		pSymbol->MaxNameLen = 1024;

		DWORD64 symDisplacement = 0;
		if (SymFromAddrW(hProcess, sf.AddrPC.Offset, 0, pSymbol))
		{
			printf("Function : %s\n", pSymbol->Name);
		}
		else
		{
			printf("SymFromAdd failed!\n");
		}

		IMAGEHLP_LINE lineInfo = { sizeof(IMAGEHLP_LINE) };
		DWORD dwLineDisplacement;

		if (SymGetLineFromAddr(hProcess, sf.AddrPC.Offset, &dwLineDisplacement, &lineInfo))
		{
			printf("[Source File : %s]\n", lineInfo.FileName);
			printf("[Source Line : %u]\n", lineInfo.LineNumber);
		}
		else
		{
			printf("SymGetLineFromAddr failed!\n");
		}
	}
}

extern "C" void toluafix_test_call_msg();


LONG WINAPI handleException(struct _EXCEPTION_POINTERS* pExceptionInfo)
{
	//StackWalker sw;
	//sw.ShowCallstack(GetCurrentThread(), pExceptionInfo->ContextRecord);
	//dump_callstack(pExceptionInfo->ContextRecord);
	char *buf = new char[1024*16];
	GetFuncCallStack(2, buf, pExceptionInfo);
	printf("%s", buf);
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
