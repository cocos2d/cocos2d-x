
// TestAudioEngine-win32.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTestAudioEnginewin32App:
// See TestAudioEngine-win32.cpp for the implementation of this class
//

class CTestAudioEnginewin32App : public CWinAppEx
{
public:
	CTestAudioEnginewin32App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTestAudioEnginewin32App theApp;