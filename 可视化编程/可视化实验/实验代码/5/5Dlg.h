// 5Dlg.h : header file
//

#if !defined(AFX_5DLG_H__2C21F8AD_5900_4DA3_8B4D_01B5954ADE94__INCLUDED_)
#define AFX_5DLG_H__2C21F8AD_5900_4DA3_8B4D_01B5954ADE94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy5Dlg dialog

class CMy5Dlg : public CDialog
{
// Construction
public:
	CMy5Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy5Dlg)
	enum { IDD = IDD_MY5_DIALOG };
	CEdit	m_Min_Edit;
	CEdit	m_Max_Edit;
	CEdit	m_No5_Edit;
	CEdit	m_No4_Edit;
	CEdit	m_No3_Edit;
	CEdit	m_No2_Edit;
	CEdit	m_No1_Edit;
	CEdit	m_Group_Edit;
	CButton	m_Exit_Btn;
	CButton	m_Search_Btn;
	CButton	m_Result_Btn;
	CButton	m_Input_Btn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy5Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy5Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_5DLG_H__2C21F8AD_5900_4DA3_8B4D_01B5954ADE94__INCLUDED_)
