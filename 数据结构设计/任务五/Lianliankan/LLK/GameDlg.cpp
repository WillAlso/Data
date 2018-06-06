// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
{

}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->ModifyStyleEx(0,WS_EX_APPWINDOW);
	this->SetWindowText(_T("欢乐连连看-基本模式"));
	CGameDlg::InitBackground();
	CGameDlg::InitElement();
	return TRUE;
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0,0,800,600,&m_dcMem,0,0,SRCCOPY);
}


void CGameDlg::InitBackground(void)
{
	CClientDC dc(this);
	HANDLE bmp = ::LoadImage(NULL,_T("theme\\picture\\fruit_bg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmp);

	CGameDlg::UpdateWindow();
}


void CGameDlg::InitElement(void)
{
	CClientDC dc(this);
	HANDLE bmp = ::LoadImage(NULL,_T("theme\\picture\\shape.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(bmp);

	HANDLE bMask = ::LoadImage(NULL,_T("theme\\picture\\shape_mask.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(bMask);
}


void CGameDlg::OnClickedBtnStart()
{
	int anMap[4][4] = {2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3};
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j < 4;j++)
		{
			m_anMap[i][j] = anMap[i][j];
		}
	}
	CGameDlg::UpdateMap();
	Invalidate(FALSE);
}


void CGameDlg::UpdateMap(void)
{
	int nLeft = 50;
	int nTop = 50;
	int nElemW = 40;
	int nElemH = 40;
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j < 4;j++)
		{
			//m_dcMem.BitBlt(nLeft + j * nElemW,nTop + i * nElemH,nElemH,nElemW,&m_dcElement,0,m_anMap[i][j] * nElemH,SRCCOPY);
			m_dcMem.BitBlt(nLeft + j * nElemW,nTop + i * nElemH,nElemH,nElemW,&m_dcMask,0,m_anMap[i][j] * nElemH,SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW,nTop + i * nElemH,nElemH,nElemW,&m_dcElement,0,m_anMap[i][j] * nElemH,SRCAND);
		}
	}
}


void CGameDlg::UpdateWindow(void)
{
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0,0,800 + nSpanWidth,600 + nSpanHeight);
	CenterWindow();
}
