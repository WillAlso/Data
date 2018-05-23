#if !defined(AFX_LISTDLG_H__6DAFEA5F_75F2_4D01_9801_AF6458837BED__INCLUDED_)
#define AFX_LISTDLG_H__6DAFEA5F_75F2_4D01_9801_AF6458837BED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// listdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// listdlg dialog

class listdlg : public CDialog
{
// Construction
public:
	listdlg(CWnd* pParent = NULL);   // standard constructor
	CBitmap m_bg1;
// Dialog Data
	//{{AFX_DATA(listdlg)
//	enum { IDD = IDD_LISTDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(listdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(listdlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTDLG_H__6DAFEA5F_75F2_4D01_9801_AF6458837BED__INCLUDED_)
