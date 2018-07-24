// HelpDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "HelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelpDialog::IDD, pParent)
{

}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHelpDialog 消息处理程序


void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
	switch(nSBCode)
	{
	case SB_LINEUP:
		pos -= 1;
		break;
	case SB_LINEDOWN:
		pos += 1;
		break;
	case SB_PAGEUP:
		pos -= 10;
		break;
	case SB_PAGEDOWN:
		pos += 10;
		break;
	case SB_TOP:
		pos = nMinpos;
		break;
	case SB_BOTTOM:
		pos = nMaxpos;
		break;
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
	default:
		break;
	}
	UpdateHelp(pos);
}


BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CClientDC dc(this);

	HANDLE bmp = ::LoadImageW(NULL,_T("theme\\picture\\Picture_Help01.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(bmp);

	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc,400,600);
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.BitBlt(0,0,400,600,&m_dcBG,0,0,SRCCOPY);

	pos = 0;
	nMinpos = 0;
	nMaxpos = 600;

	return TRUE;
}


void CHelpDialog::OnPaint()
{
	CPaintDC dc(this);
	dc.BitBlt(0,0,400,600,&m_dcMem,0,0,SRCCOPY);
}


void CHelpDialog::UpdateHelp(int nPos)
{
	m_dcMem.BitBlt(0,0,400,600,NULL,0,0,WHITENESS);
	m_dcMem.BitBlt(0,0,400,600,&m_dcBG,0,nPos,SRCCOPY);
	Invalidate(FALSE);
}
