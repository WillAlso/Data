// demoDlg.h : header file
//

#if !defined(AFX_DEMODLG_H__EEAB7C89_84EA_4538_937F_C23F6B75D1D7__INCLUDED_)
#define AFX_DEMODLG_H__EEAB7C89_84EA_4538_937F_C23F6B75D1D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

class CDemoDlg : public CDialog
{
// Construction
public:
	CDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDemoDlg)
	enum { IDD = IDD_DEMO_DIALOG };
	CComboBox	m_Name_ComBo;
	CComboBox	m_Favorate_ComBo;
	CString	m_Show_Edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExitButton();
	afx_msg void OnShowButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODLG_H__EEAB7C89_84EA_4538_937F_C23F6B75D1D7__INCLUDED_)
