
// TestAudioEngine-win32Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestAudioEngine.win32.h"
#include "TestAudioEngine.win32Dlg.h"

#include  "SimpleAudioEngine.h"

const static char kszMusic[]	= "music.mid";
const static char kszEffect1[]	= "effect1.wav";
const static char kszEffect2[]	= "effect2.wav";

static int   s_nEffect1;
static int   s_nEffect2;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestAudioEnginewin32Dlg dialog




CTestAudioEnginewin32Dlg::CTestAudioEnginewin32Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestAudioEnginewin32Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestAudioEnginewin32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestAudioEnginewin32Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_MUSIC, &CTestAudioEnginewin32Dlg::OnBnClickedMusic)
	ON_BN_CLICKED(IDC_MUSIC_STOP, &CTestAudioEnginewin32Dlg::OnBnClickedMusicStop)
	ON_BN_CLICKED(IDC_EFFECT1, &CTestAudioEnginewin32Dlg::OnBnClickedEffect1)
	ON_BN_CLICKED(IDC_EFFECT2, &CTestAudioEnginewin32Dlg::OnBnClickedEffect2)
//	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTestAudioEnginewin32Dlg message handlers

BOOL CTestAudioEnginewin32Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestAudioEnginewin32Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestAudioEnginewin32Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestAudioEnginewin32Dlg::OnBnClickedMusic()
{
	SimpleAudioEngine::getSharedEngine()->playBackgroundMusic(kszMusic, true);
}

void CTestAudioEnginewin32Dlg::OnBnClickedMusicStop()
{
	SimpleAudioEngine::getSharedEngine()->stopBackgroundMusic();
}

void CTestAudioEnginewin32Dlg::OnBnClickedEffect1()
{
	s_nEffect1 = SimpleAudioEngine::getSharedEngine()->playEffect(kszEffect1);
}

void CTestAudioEnginewin32Dlg::OnBnClickedEffect2()
{
	s_nEffect2 = SimpleAudioEngine::getSharedEngine()->playEffect(kszEffect2);
}

void CTestAudioEnginewin32Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	SimpleAudioEngine::getSharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::getSharedEngine()->unloadEffectAll();
}
