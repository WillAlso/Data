// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "GameLogic.h"

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
	, m_bFirstPoint(false)
	, m_bPlaying(false)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_);
	m_ptGameTop.x = MAP_TOP;
	m_ptGameTop.y = MAP_TOP;
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;
	m_bFirstPoint = true;
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;
	m_bPlaying = false;
	m_bPause = true;
	Game_Time = 0;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_Game_Progress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_PROMPT, &CGameDlg::OnBnClickedBtnPrompt)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnBnClickedBtnReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_HELP, &CGameDlg::OnBnClickedBtnHelp)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_STOP, &CGameDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BUTTON5, &CGameDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->ModifyStyleEx(0,WS_EX_APPWINDOW);
	if(FLAG == 1)
	{
		this->SetWindowText(_T("欢乐连连看-基本模式"));
	}else if(FLAG == 2)
	{
		this->SetWindowText(_T("欢乐连连看-休闲模式"));
	}else
	{
		this->SetWindowText(_T("欢乐连连看-关卡模式"));
	}
	CGameDlg::InitBackground();
	CGameDlg::InitElement();
	if(FLAG == 2)
	{
		(CProgressCtrl *)GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
	}
	return TRUE;
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0,0,800,600,&m_dcMem,0,0,SRCCOPY);
	//dc.TextOut(0,0,L"asads",3);
	//DrawGameTime();
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
	CString pName1,pName2;
	if(FBG == 2)
	{
		pName1 = "theme\\picture\\animals_element.bmp";
		pName2 = "theme\\picture\\animals_mask.bmp";
	}else
	{
		pName1 = "theme\\picture\\shape.bmp";
		pName2 = "theme\\picture\\shape_mask.bmp";
	}
	
	HANDLE bmp = ::LoadImage(NULL,pName1,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(bmp);

	HANDLE bMask = ::LoadImage(NULL,pName2,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(bMask);
}


void CGameDlg::OnClickedBtnStart()
{
	m_gameControl.StartGame();
	UpdateMap();
	m_bPlaying = true;
	m_bPause = false;
	Game_Time = 0;
	(CButton*)GetDlgItem(IDC_BTN_START)->EnableWindow(false);
	InvalidateRect(m_rtGameRect,FALSE);

	m_Game_Progress.SetRange(0,300);
	m_Game_Progress.SetStep(-1);
	m_Game_Progress.SetPos(300);
	this->SetTimer(9999,1000,NULL);
	//DrawGameTime();
	
}


void CGameDlg::UpdateMap(void)
{
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	m_dcMem.BitBlt(m_rtGameRect.left,m_rtGameRect.top,
		m_rtGameRect.Width(),m_rtGameRect.Height(),&m_dcBG,m_rtGameRect.left,m_rtGameRect.top,SRCCOPY);
	for(int i = 0;i < MAX_ROW;i++)
	{
		for(int j = 0;j < MAX_COL;j++)
		{
			int nInfo = m_gameControl.GetElement(i,j);
			if(nInfo == BLANK)
			{
				continue;
			}
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
	if(m_bPause)
	{
		return;
	}
	if(point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);;
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if(nRow > MAX_ROW - 1 || nCol > MAX_COL - 1)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if(m_bFirstPoint)
	{
		DrawTipFrame(nRow,nCol);
		m_gameControl.SetFirstPoint(nRow,nCol);
	}else
	{
		DrawTipFrame(nRow,nCol);
		m_gameControl.SetSecPoint(nRow,nCol);

		Vertex avPath[4];
		int nVexnum = 0;
		if(m_gameControl.Link(avPath,nVexnum))
		{
			DrawTipLine(avPath,nVexnum);
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect,FALSE);

		if(m_gameControl.IsWin())
		{
			MessageBox(_T("恭喜你，获胜！"));
			m_bPlaying = false;
			(CButton*)GetDlgItem(IDC_BTN_START)->EnableWindow(true);
			if(Game_Time < rank[0])
			{
				rank[2] = rank[1];
				rank[1] = rank[0];
				rank[0] = Game_Time;
			}else if(Game_Time < rank[1])
			{
				rank[2] = rank[1];
				rank[1] = Game_Time;
			}else if(Game_Time < rank[2])
			{
				rank[2] = Game_Time;
			}
			return;
		}
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


void CGameDlg::OnBnClickedBtnPrompt()
{
	if(m_bPlaying == false)
	{
		return;
	}
	CGraph g = m_gameControl.GetGraph();
	CGameLogic logic;
	Vertex v[2];
	Vertex ver[MAX_VERTEX_NUM];
	int m = MAX_VERTEX_NUM;
	for(int i = 0;i < MAX_ROW;i++)
	{
		for(int j = 0;j < MAX_COL;j++)
		{
			ver[i * MAX_COL + j].info = g.GetVertex(i * MAX_COL + j);
		}
	}
	if(m_gameControl.Help(ver,m,v[0],v[1]))
	{
		DrawTipFrame(v[0].row,v[0].col);
		DrawTipFrame(v[1].row,v[1].col);
		Sleep(100);
	}
}


void CGameDlg::OnBnClickedBtnReset()
{
	if(m_bPlaying == false)
	{
		return;
	}
	m_bPause = false;
	Game_Time = 0;
	m_Game_Progress.SetPos(300);
	m_gameControl.ResetGraph();
	UpdateMap();
	Sleep(200);
	InvalidateRect(&m_rtGameRect);
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 9999 && m_bPause)
	{
		return;
	}
	if(nIDEvent == 9999 && m_bPlaying && !m_bPause)
	{
		m_Game_Progress.StepIt();
		Game_Time++;
		DrawGameTime();
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::DrawGameTime(void)
{
	CDC* pDC = this->GetDC();
	int s_time = Game_Time;
	CString str;
	str.Format(_T("时间:%d秒"),s_time);
	//pDC->SetTextColor(RGB(255,255,255));
	//pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(690,530,str);
}


void CGameDlg::OnBnClickedBtnHelp()
{
	this->ShowWindow(1);
	CHelpDialog dlg;
	dlg.DoModal();
	this->ShowWindow(1);
}


void CGameDlg::OnClose()
{
	if(m_bPlaying == true)
	{
		if(IDYES==::MessageBox(NULL,L"真的要退出？",L"提示",MB_YESNO))
		{
			CDialogEx::OnClose();

			KillTimer(9999);
		}
	}else
	{
		CDialogEx::OnClose();
		KillTimer(9999);
	}
	FLAG = 0;
}


void CGameDlg::OnBnClickedBtnStop()
{
	if(FLAG == 2 || !m_bPlaying)
	{
		return;
	}
	if(m_bPause)
	{
		m_bPause = false;
		GetDlgItem(IDC_BTN_STOP)->SetWindowTextW(L"暂停");
		m_gameControl.SetGraph(t_graph);
		UpdateMap();
		InvalidateRect(m_rtGameRect,FALSE);
	}else
	{
		m_bPause = true;
		GetDlgItem(IDC_BTN_STOP)->SetWindowTextW(L"继续");
		CGraph g;
		t_graph = m_gameControl.SetGraph(g);
		UpdateMap();
		InvalidateRect(m_rtGameRect,FALSE);
	}
}


void CGameDlg::OnBnClickedButton5()
{
	this->ShowWindow(1);
	CSetDlg dlg;
	dlg.DoModal();
	this->ShowWindow(1);
}
