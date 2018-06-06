// 4Dlg.h : header file
//

#if !defined(AFX_4DLG_H__F8740B8D_0089_4BC6_BD45_560BF64D0ECA__INCLUDED_)
#define AFX_4DLG_H__F8740B8D_0089_4BC6_BD45_560BF64D0ECA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy4Dlg dialog

class CMy4Dlg : public CDialog
{
// Construction
public:
	CMy4Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy4Dlg)
	enum { IDD = IDD_MY4_DIALOG };
	int		m_A;
	int		m_B;
	CString	m_C;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy4Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy4Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_4DLG_H__F8740B8D_0089_4BC6_BD45_560BF64D0ECA__INCLUDED_)
