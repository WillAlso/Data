// playerDlg.h : header file
//

#if !defined(AFX_PLAYERDLG_H__FE3B843D_BE0F_46C6_9038_4AA6AA8032A8__INCLUDED_)
#define AFX_PLAYERDLG_H__FE3B843D_BE0F_46C6_9038_4AA6AA8032A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPlayerDlg dialog
#include"mmsystem.h"
class CPlayerDlg : public CDialog
{
// Construction
public:
	int hour,minute,second;
    DWORD cdlen;
	DWORD m_count;
	void Tplay();
	void Thide();
	void Tdehide();
	void forfor();
	void forfor1();
	DWORD getinfo(DWORD item);
	CString aa;
	CString file[255];
	CString file1[255];
	int fi,fr;
	DWORD cdfrom,cdto;
	CBitmapButton   m_bexit;
	CBitmapButton   m_bmim;
	CBitmapButton   m_bhelp;
	CBitmapButton   m_play;
	CBitmapButton   m_stop;
	CBitmapButton   m_open;
	CBitmapButton   m_rp;
	CBitmapButton   m_pop;
	CBitmapButton	m_next;
	CBitmapButton	m_sdel;
	CBitmapButton	m_per;
	CBitmap m_bg,m_bg1;
	BOOL m_flag,m_flag1,m_flag2,m_flag3;
	CPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPlayerDlg)
	enum { IDD = IDD_PLAYER_DIALOG };
	CListBox	m_list;
	CSliderCtrl	m_sl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPlay();
	afx_msg void OnOpen();
	afx_msg void OnBexit();
	afx_msg void Onbhelp();
	afx_msg void Onbmim();
	afx_msg void Onstop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRp();
	afx_msg void OnPop();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDblclkList();
	afx_msg void OnPer();
	afx_msg void OnNext();
	afx_msg void OnSdel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERDLG_H__FE3B843D_BE0F_46C6_9038_4AA6AA8032A8__INCLUDED_)
