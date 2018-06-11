
// WebBrowserDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CWebBrowserDlg 对话框
class CWebBrowserDlg : public CDialogEx
{
// 构造
public:
	CWebBrowserDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WEBBROWSER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit7();
	BOOL m_bProxy;
protected:
	CString m_strURL;
	UINT m_nCode;
	CEdit m_editProxy;
public:
	afx_msg void OnEnChangeEditProxy();
protected:
	CString m_strProxy;
	CEdit m_editPort;
	UINT m_nPort;
	CString m_strHTML;
	CEdit m_editUser;
	CString m_strUser;
	CEdit m_editPass;
	CString m_strPass;
};
