// playerDlg.cpp : implementation file
#include "stdafx.h"
#include "player.h"
#include "playerDlg.h"
#include "mmsystem.h"
#include "hyperlink.h"
//#include "listdlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#define WM_MYMESSAGE WM_USER+6
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//download by http://down.liehuo.net
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	CHyperLink m_url;
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_url.SetURL(_T("mailto:xxx@163.com"));
	m_url.SetUnderline(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_EMAIL, m_url);
	//}}AFX_DATA_MAP
} 

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerDlg dialog

CPlayerDlg::CPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//*********************变量初始化**********
	aa="";
	hour=0,minute=0,second=0;fi=-1;fr=0;
}

void CPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayerDlg)
	DDX_Control(pDX, IDC_NEXT, m_next);
	DDX_Control(pDX, IDC_SDEL, m_sdel);
	DDX_Control(pDX, IDC_PER, m_per);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_SLIDER, m_sl);
	DDX_Control(pDX, IDC_POP, m_pop);
	DDX_Control(pDX, IDC_RP, m_rp);
	DDX_Control(pDX, IDC_STOP, m_stop);
	DDX_Control(pDX, IDC_PLAY, m_play);
	DDX_Control(pDX, IDC_OPEN, m_open);
	DDX_Control(pDX, IDC_BMIM, m_bmim);
	DDX_Control(pDX, IDC_BHELP, m_bhelp);
	DDX_Control(pDX, IDC_BEXIT, m_bexit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_BEXIT, OnBexit)
	ON_BN_CLICKED(IDC_BHELP, Onbhelp)
	ON_BN_CLICKED(IDC_BMIM, Onbmim)
	ON_BN_CLICKED(IDC_STOP, Onstop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RP, OnRp)
	ON_BN_CLICKED(IDC_POP, OnPop)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_BN_CLICKED(IDC_PER, OnPer)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_SDEL, OnSdel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerDlg message handlers

BOOL CPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);
	SetWindowText("MCI播放器");

	m_flag=true;

	m_flag1=true;

	m_flag2=false;

	m_flag3=true;
	MoveWindow(200,200,303,103);//初始程序大小
//******************加载图片***************
	m_bg.LoadBitmap(IDB_BITMAPBG);
	m_play.LoadBitmaps(IDB_BITMAPPLAY1,IDB_BITMAPPLAY3);
	m_stop.LoadBitmaps(IDB_BITMAPSTOP1,IDB_BITMAPSTOP3);
	m_open.LoadBitmaps(IDB_BITMAPOPEN1,IDB_BITMAPOPEN3);
	m_bhelp.LoadBitmaps(IDB_BITMAPHELP1,IDB_BITMAPHELP2);
	m_bmim.LoadBitmaps(IDB_BITMAPMIM1,IDB_BITMAPMIM2);
	m_bexit.LoadBitmaps(IDB_BITMAPEXIT1,IDB_BITMAPEXIT2);
	m_rp.LoadBitmaps(IDB_BITMAPRP1,IDB_BITMAPRP2);
	m_pop.LoadBitmaps(IDB_BITMAPC,IDB_BITMAPD);
	m_pop.LoadBitmaps(IDB_BITMAPA,IDB_BITMAPB);
	m_per.LoadBitmaps(IDB_BITMAPPER1,IDB_BITMAPPER2);
	m_next.LoadBitmaps(IDB_BITMAPNEXT1,IDB_BITMAPNEXT2);
	m_sdel.LoadBitmaps(IDB_BITMAPDEL1,IDB_BITMAPDEL2);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPlayerDlg::OnPaint() 
{		// Set big icon
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon	 = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
//		CDialog::OnPaint();
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC dcMem; 
		dcMem.CreateCompatibleDC(&dc); 
		BITMAP bitMap;
		m_bg.GetBitmap(&bitMap);
		CBitmap *pbmpOld=dcMem.SelectObject(&m_bg);
		dc.StretchBlt(0,0,502,rect.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);
		m_bexit.MoveWindow(284,0,19,19,false);
		m_bmim.MoveWindow(263,0,19,19,false);
		m_bhelp.MoveWindow(242,0,19,19,false);
		m_play.MoveWindow(13,60,40,40,false);
		m_stop.MoveWindow(55,68,30,30,false);
		m_open.MoveWindow(93,65,30,30,false);
		m_rp.MoveWindow(133,68,30,30,false);
		m_pop.MoveWindow(282,22,20,78,false);
		m_per.MoveWindow(170,60,40,40,false);
		m_next.MoveWindow(200,60,40,40,false);
		m_sdel.MoveWindow(484,30,18,40,false);
	}
}
HCURSOR CPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CPlayerDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{  
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM (point.x, point.y));
	CDialog::OnLButtonDown(nFlags, point);
}
void CPlayerDlg::OnPlay() 
{
	if(aa=="")
	{
		OnOpen();
	}
	else
	{
		if(m_flag&&aa!="")
		{
			m_play.LoadBitmaps(IDB_BITMAPPAUSE,IDB_BITMAPPLAY3);
			m_flag=false;
			m_play.RedrawWindow();
			MCI_OPEN_PARMS mciopenparms;//打开
			MCI_PLAY_PARMS mciplayparms;//播放
			mciopenparms.lpstrElementName=aa;//播放路径
			mciopenparms.lpstrDeviceType=NULL;//文件类型
			mciSendCommand(0,MCI_OPEN,MCI_DEVTYPE_WAVEFORM_AUDIO,(DWORD)(LPVOID)&mciopenparms);//向MCI设备发送命令消息
			m_count=mciopenparms.wDeviceID;
			mciplayparms.dwCallback=(DWORD)GetSafeHwnd();	
			cdlen=getinfo(MCI_STATUS_LENGTH);    //得到曲目长度                                                                                                                                                                                                                                          
			cdto=MCI_MAKE_HMS(MCI_HMS_HOUR(cdlen),MCI_HMS_MINUTE(cdlen),MCI_HMS_SECOND(cdlen));  
			mciplayparms.dwFrom=cdfrom;
			mciplayparms.dwTo=cdto;
			mciSendCommand(m_count,MCI_PLAY,MCI_TO|MCI_FROM,(DWORD)(LPVOID)& mciplayparms);
			SetTimer(0,1000,NULL);
			UpdateData(false);
		}
		else
		{
			m_play.LoadBitmaps(IDB_BITMAPPLAY1,IDB_BITMAPPLAY3);
			m_flag=true;
			m_play.RedrawWindow();
			KillTimer(0);
			DWORD dwsf=getinfo(MCI_STATUS_POSITION);
			cdfrom=MCI_MAKE_MSF(MCI_MSF_MINUTE(dwsf),MCI_MSF_SECOND(dwsf),
                      MCI_MSF_FRAME(dwsf));
			mciSendCommand(m_count,MCI_CLOSE,0,NULL);
			m_count=0;
		}
	}
}
DWORD CPlayerDlg::getinfo(DWORD item)
{
	MCI_STATUS_PARMS mcistatusparms;
	mcistatusparms.dwCallback=(DWORD)GetSafeHwnd();
	mcistatusparms.dwItem=item;
	mcistatusparms.dwReturn=0;
	mciSendCommand(m_count,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)&mcistatusparms);
	return mcistatusparms.dwReturn;
}
void CPlayerDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	CFileDialog f(true);
	f.m_ofn.Flags |=512;//OFN_ALLOWMULTISELECT;
	f.m_ofn.lpstrFilter="All Support type\0*.*\0\0";
    //选取内容部份
	POSITION pos=f.GetStartPosition();
	if(f.DoModal()==IDOK)
	 {	
		while (pos != NULL)
		{
			fi++;
			file[fi]=f.GetNextPathName(pos);
			if(aa=="")
			{
				aa=file[fi];
				fr=fi;
				Onstop();
				Tplay();
				
				m_play.LoadBitmaps(IDB_BITMAPPAUSE,IDB_BITMAPPLAY3);
				m_flag=false;
				m_play.RedrawWindow();
			}
			m_list.AddString(file[fi]);
			m_list.SetCurSel(fr);
			UpdateData(false);
		}
		forfor();
	 }
	 
}

void CPlayerDlg::OnBexit() 
{
	// TODO: Add your control notification handler code here
	Onstop();
	OnOK();
}
void CPlayerDlg::Onbhelp()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
void CPlayerDlg::Onbmim()
{
	Thide();
//	ShowWindow(SW_MINIMIZE);
	ShowWindow(SW_HIDE);
}
void CPlayerDlg::Onstop()
{
	KillTimer(0);
	cdfrom=MCI_MAKE_HMS(0,0,0);
	mciSendCommand(m_count,MCI_CLOSE,0,NULL);
	m_count=0;
	m_play.LoadBitmaps(IDB_BITMAPPLAY1,IDB_BITMAPPLAY3);
    m_flag=true;
    m_play.RedrawWindow();
}
void CPlayerDlg::Tplay()
{
		MCI_OPEN_PARMS mciopenparms;
		MCI_PLAY_PARMS mciplayparms;
		mciopenparms.lpstrElementName=aa;
		mciopenparms.lpstrDeviceType=NULL;
		mciSendCommand(0,MCI_OPEN,MCI_DEVTYPE_WAVEFORM_AUDIO,(DWORD)(LPVOID)&mciopenparms);
		m_count=mciopenparms.wDeviceID;
		mciplayparms.dwCallback=(DWORD)GetSafeHwnd();	
		cdlen=getinfo(MCI_STATUS_LENGTH);                                                                                                                                                                                                                                              
		cdfrom=MCI_MAKE_HMS(0,0,0);
		cdto=MCI_MAKE_HMS(MCI_HMS_HOUR(cdlen),MCI_HMS_MINUTE(cdlen),MCI_HMS_SECOND(cdlen));  
		mciplayparms.dwFrom=cdfrom;
		mciplayparms.dwTo=cdto;
		mciSendCommand(m_count,MCI_PLAY,MCI_TO|MCI_FROM,(DWORD)(LPVOID)& mciplayparms);
	    SetTimer(0,1000,NULL);
		m_sl.SetRange(0,cdlen);
}
void CPlayerDlg::Thide()
{
	//任务栏图标
	NOTIFYICONDATA tnd;
    tnd.cbSize=sizeof(NOTIFYICONDATA);
	tnd.hWnd=this->m_hWnd;
	tnd.uID=IDR_MAINFRAME;
    tnd.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage=WM_MYMESSAGE;
	tnd.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(tnd.szTip,"Mp3 Player,单击图标弹出窗口");
    Shell_NotifyIcon(NIM_ADD,&tnd);//向任务栏添加图标
}

LRESULT CPlayerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(message)
	{
	case WM_MYMESSAGE:
		if(lParam==WM_RBUTTONUP||lParam==WM_LBUTTONUP)
		{
			ShowWindow(SW_SHOW);
		Tdehide();
		}
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}
void CPlayerDlg::Tdehide()
{
	NOTIFYICONDATA tnd;
    tnd.cbSize=sizeof(NOTIFYICONDATA);
	tnd.hWnd=this->m_hWnd;
	tnd.uID=IDR_MAINFRAME;
    tnd.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage=WM_MYMESSAGE;
	//用户自定义的消息，即鼠标在任务栏上程序图标上动作时图标发送的消息
	tnd.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(tnd.szTip,"Mp3 Player,单击图标弹出窗口");//图标提示为"测试程序"
    Shell_NotifyIcon(NIM_DELETE,&tnd);//向任务栏添
}

void CPlayerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString stime,kk;
	second++;
	CClientDC dc(this);
	dc.SetBkColor(RGB(81,54,166));
	dc.SetTextColor(RGB(215,249,9));
    if(second==60)
	{
		minute++;second=0;
	}
	if(minute==60)
	{
		hour++;minute=0;
	}
	if(hour==24)
	{
		hour=0;
	}
	stime.Format("%02d:%02d:%02d",hour,minute,second);
	dc.TextOut(20,10,stime);
	m_sl.SetPos(cdfrom);
	kk.Format("%d",cdfrom);
	dc.TextOut(110,10,kk);
	DWORD cdf=getinfo(MCI_STATUS_POSITION);
	cdfrom=MCI_MAKE_MSF(MCI_MSF_MINUTE(cdf),MCI_MSF_SECOND(cdf),
                      MCI_MSF_FRAME(cdf));
	UpdateData(false);
	if(getinfo(MCI_STATUS_POSITION)==cdlen)
    {
		hour=0;second=0;minute=0;
		fr++;
		if(fr<=fi)
		{
			m_list.SetCurSel(fr);
			aa=file[fr];
			Onstop();
			OnPlay();
		}
		if(fr>fi)
		{
			fr=0;
			aa=file[fr];
			m_list.SetCurSel(fr);
			Onstop();
			if(m_flag2)
				OnPlay();
		}
	}
	CDialog::OnTimer(nIDEvent);
}


void CPlayerDlg::OnRp() 
{
	// TODO: Add your control notification handler code here
	if(m_flag1)
	{
		m_rp.LoadBitmaps(IDB_BITMAPRP2,IDB_BITMAPRP1);
        m_flag1=false;
		m_flag2=true;
        m_rp.RedrawWindow();
	}
	else
	{
		m_rp.LoadBitmaps(IDB_BITMAPRP1,IDB_BITMAPRP2);
		m_flag1=true;
		m_flag2=false;
        m_rp.RedrawWindow();
	}
}

void CPlayerDlg::OnPop() 
{
	// TODO: Add your control notification handler code here
	if(m_flag3)
	{
		for(int i=303;i<=502;i++)
		{
			Sleep(2);
			MoveWindow(200,200,i,103);
		}
			m_flag3=false;	
	}else
	{
		for(int i=502;i>=303;i--)
		{
			Sleep(2);
			MoveWindow(200,200,i,103);
		}
		m_flag3=true;	
	}
}
HBRUSH CPlayerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	return hbr;
}

void CPlayerDlg::OnDblclkList() 
{
	// TODO: Add your control notification handler code here
	int i=m_list.GetCurSel();
	CString tp;
	tp.Format("%d",i);
	fr=i;
	aa=file[i];
	Onstop();
	OnPlay();
	UpdateData(false);
}

void CPlayerDlg::OnPer() 
{
	// TODO: Add your control notification handler code here
	fr--;
	if(fr==-1)
	{
		fr=0;
	}
	if(fr>=0)
	{
		m_list.SetCurSel(fr);
		aa=file[fr];
		Onstop();
		OnPlay();
		UpdateData(false);
	}
}

void CPlayerDlg::OnNext() 
{
	// TODO: Add your control notification handler code here
	fr++;
	if(fr>fi)
	{
		fr=fi;
	}
	if(fr<=fi)
	{
		m_list.SetCurSel(fr);
		aa=file[fr];
		Onstop();
		OnPlay();
		UpdateData(false);
	}
}

void CPlayerDlg::OnSdel() 
{
	// TODO: Add your control notification handler code here
	int temp=0,i=0,j=0;
	temp=m_list.GetCurSel();
	for(i;i<=fi;i++)
	{
		if(i==temp)
		{
			j=i;
			for(j;j<fi;j++)
			{
				file1[j]=file1[j+1];
			}
				fi=fi-1;
				m_list.DeleteString(temp);
				m_list.SetCurSel(temp-1);
				UpdateData(false);
				forfor1();
		}
	}
}
void CPlayerDlg::forfor()
{
	int i=0;
	for(i;i<=fi;i++)
	{
		file1[i]=file[i];
	}
}
void CPlayerDlg::forfor1()
{
	int i=0;
	for(i;i<=fi;i++)
	{
		file[i]=file1[i];
	}
}

