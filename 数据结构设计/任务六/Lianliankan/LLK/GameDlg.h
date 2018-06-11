#pragma once
#include "atltypes.h"


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
	CPoint m_ptGameTop;
	CSize m_sizeElem;
private:
	int m_anMap[4][4];
public:
	afx_msg void OnClickedBtnStart();
	void UpdateMap(void);
	void UpdateWindow(void);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTipFrame(int nRow, int nCol);
protected:
	bool m_bFirstPoint;
public:
	bool IsLink(void);
protected:
	CPoint m_ptSelFirst;
	CPoint m_ptSelSec;
public:
	void DrawTipLine(void);
};
