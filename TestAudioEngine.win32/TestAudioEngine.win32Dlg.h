
// TestAudioEngine-win32Dlg.h : header file
//

#pragma once


// CTestAudioEnginewin32Dlg dialog
class CTestAudioEnginewin32Dlg : public CDialog
{
// Construction
public:
	CTestAudioEnginewin32Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTAUDIOENGINEWIN32_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMusic();
	afx_msg void OnBnClickedMusicStop();
	afx_msg void OnBnClickedEffect1();
	afx_msg void OnBnClickedEffect2();
//	afx_msg void OnClose();
	afx_msg void OnDestroy();
};
