#pragma once


// CHelpDialog �Ի���

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHelpDialog();

// �Ի�������
	enum { IDD = IDD_HELP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CDC m_dcMem;
	CDC m_dcBG;
	int pos;
	int nMinpos;
	int nMaxpos;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void UpdateHelp(int nPos);
};
