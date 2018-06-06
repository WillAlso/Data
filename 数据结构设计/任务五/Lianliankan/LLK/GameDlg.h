#pragma once


// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
	enum { IDD = IDD_GAME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void InitBackground(void);
	void InitElement(void);
protected:
	CDC m_dcElement;
	CDC m_dcMem;
	CDC m_dcMask;
private:
	int m_anMap[4][4];
public:
	afx_msg void OnClickedBtnStart();
	void UpdateMap(void);
	void UpdateWindow(void);
};
