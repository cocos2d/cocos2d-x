
// TestAudioEngine-win32.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestAudioEngine-win32.h"
#include "TestAudioEngine-win32Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestAudioEnginewin32App

BEGIN_MESSAGE_MAP(CTestAudioEnginewin32App, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTestAudioEnginewin32App construction

CTestAudioEnginewin32App::CTestAudioEnginewin32App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTestAudioEnginewin32App object

CTestAudioEnginewin32App theApp;


// CTestAudioEnginewin32App initialization

BOOL CTestAudioEnginewin32App::InitInstance()
{
	CWinAppEx::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CTestAudioEnginewin32Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
