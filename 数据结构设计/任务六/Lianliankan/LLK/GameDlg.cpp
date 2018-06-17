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
	, m_bFirstPoint(false)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_);
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;
	m_bFirstPoint = true;
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * 4;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * 4;
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
	ON_WM_LBUTTONUP()
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
	HANDLE bmp = ::LoadImageW(NULL,_T("theme\\picture\\fruit_bg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(bmp);

	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc,800,600);
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.BitBlt(0,0,800,600,&m_dcBG,0,0,SRCCOPY);

	//CGameDlg::UpdateWindow();
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
	/*int anMap[4][4] = {2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3};
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j < 4;j++)
		{
			m_anMap[i][j] = anMap[i][j];
		}
	}*/
	m_gameControl.StartGame();
	UpdateMap();
	//InvalidateRect(m_rtGameRect,FALSE);
	InvalidateRect(m_rtGameRect,FALSE);
}


void CGameDlg::UpdateMap(void)
{
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	m_dcMem.BitBlt(m_rtGameRect.left,m_rtGameRect.top,
		m_rtGameRect.Width(),m_rtGameRect.Height(),&m_dcBG,m_rtGameRect.left,m_rtGameRect.top,SRCCOPY);
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j < 4;j++)
		{
			int nInfo = m_gameControl.GetElement(i,j);
			if(nInfo == BLANK)
			{
				continue;
			}
			//m_dcMem.BitBlt(nLeft + j * nElemW,nTop + i * nElemH,nElemH,nElemW,&m_dcElement,0,m_anMap[i][j] * nElemH,SRCCOPY);
			m_dcMem.BitBlt(nLeft + j * nElemW,nTop + i * nElemH,nElemH,nElemW,&m_dcMask,0,nInfo * nElemH,SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW,nTop + i * nElemH,nElemH,nElemW,&m_dcElement,0,nInfo * nElemH,SRCAND);
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


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);;
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if(nRow > 3 || nCol > 3)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if(m_bFirstPoint)
	{
		DrawTipFrame(nRow,nCol);
		//m_ptSelFirst.col = nCol;
		//m_ptSelFirst.row = nRow;
		m_gameControl.SetFirstPoint(nRow,nCol);
	}else
	{
		DrawTipFrame(nRow,nCol);
		//m_ptSelSec.col = nCol;
		//m_ptSelSec.row = nRow;
		m_gameControl.SetSecPoint(nRow,nCol);

		Vertex avPath[4];
		int nVexnum;
		if(m_gameControl.Link(avPath,nVexnum))
		{
			DrawTipLine(avPath,nVexnum);
			//Clear
			//m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] = -1;
			//m_anMap[m_ptSelSec.row][m_ptSelSec.col] = -1;
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect,FALSE);
	}
	m_bFirstPoint = !m_bFirstPoint;
}


void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233,43,43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame,&brush);
}


bool CGameDlg::IsLink(void)
{
	if(m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] == m_anMap[m_ptSelSec.row][m_ptSelSec.col])
	{
		return true;
	}
	return false;
}


void CGameDlg::DrawTipLine(Vertex avPath[4],int nVexnum)
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID,2,RGB(0,255,0));
	CPen* pPen = dc.SelectObject(&penLine);
	
	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	
	for(int i = 1;i < nVexnum;i++)
	{
		dc.LineTo(m_ptGameTop.x + avPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pPen);
}
