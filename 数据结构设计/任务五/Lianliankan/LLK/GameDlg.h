#pragma once


// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
	enum { IDD = IDD_GAME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
