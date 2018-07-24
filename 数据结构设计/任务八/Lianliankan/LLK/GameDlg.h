#pragma once

#include "atltypes.h"
#include "global.h"
#include "GameControl.h"
#include "global.h"
#include "SetDlg.h"
#include "afxcmn.h"


// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

// 对话框数据
	enum { IDD = IDD_GAME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	
	HICON m_hIcon;
	CDC m_dcElement;
	CDC m_dcMem;
	CDC m_dcMask;
	CDC m_dcBG;
	CPoint m_ptGameTop;
	CSize m_sizeElem;
	CRect m_rtGameRect;
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;
	bool m_bFirstPoint;
	CGameControl m_gameControl;
	CGraph t_graph;
private:
	int m_anMap[MAX_ROW][MAX_COL];
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void InitBackground(void);
	void InitElement(void);
	CGameDlg(CWnd* pParent = NULL);
	virtual ~CGameDlg();
	afx_msg void OnClickedBtnStart();
	void UpdateMap(void);
	void UpdateWindow(void);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex avPath[4],int nVexnum);
	bool IsLink(void);
protected:
	bool m_bPlaying;
	bool m_bPause;
	int Game_Time;
public:
	afx_msg void OnBnClickedBtnPrompt();
	afx_msg void OnBnClickedBtnReset();
protected:
	CProgressCtrl m_Game_Progress;
	int falg;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawGameTime(void);
	afx_msg void OnBnClickedBtnHelp();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedButton5();
};
