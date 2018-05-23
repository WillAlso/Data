// listdlg.cpp : implementation file
// download by http://down.liehuo.net

#include "stdafx.h"
#include "player.h"
#include "listdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// listdlg dialog


listdlg::listdlg(CWnd* pParent /*=NULL*/)
	: CDialog(listdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(listdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void listdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(listdlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL listdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
//		OnCtlColor(IDD_LISTDLG,,);
/*		m_bg1.LoadBitmap(IDB_BITMAPBG1);
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC dcMem; 
		dcMem.CreateCompatibleDC(&dc); 
		BITMAP bitMap;
		m_bg1.GetBitmap(&bitMap);
		CBitmap *pbmpOld=dcMem.SelectObject(&m_bg1);
		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);
*/
 // open.EnableWindow(true);
//	b=false;
//	SetWindowPos(&CWnd::wndNoTopMost,200,200,100,100,SWP_SHOWWINDOW);
	  // TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(listdlg, CDialog)
	//{{AFX_MSG_MAP(listdlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// listdlg message handlers

HBRUSH listdlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
