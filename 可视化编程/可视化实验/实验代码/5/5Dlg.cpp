// 5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "5.h"
#include "5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
struct struData{
	double dfData[5];
}InputData[5];
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy5Dlg dialog

CMy5Dlg::CMy5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy5Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy5Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy5Dlg)
	DDX_Control(pDX, IDC_EDIT8, m_Min_Edit);
	DDX_Control(pDX, IDC_EDIT7, m_Max_Edit);
	DDX_Control(pDX, IDC_EDIT6, m_No5_Edit);
	DDX_Control(pDX, IDC_EDIT5, m_No4_Edit);
	DDX_Control(pDX, IDC_EDIT4, m_No3_Edit);
	DDX_Control(pDX, IDC_EDIT3, m_No2_Edit);
	DDX_Control(pDX, IDC_EDIT2, m_No1_Edit);
	DDX_Control(pDX, IDC_EDIT1, m_Group_Edit);
	DDX_Control(pDX, IDC_BUTTON4, m_Exit_Btn);
	DDX_Control(pDX, IDC_BUTTON3, m_Search_Btn);
	DDX_Control(pDX, IDC_BUTTON2, m_Result_Btn);
	DDX_Control(pDX, IDC_BUTTON1, m_Input_Btn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy5Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy5Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy5Dlg message handlers

BOOL CMy5Dlg::OnInitDialog()
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
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy5Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy5Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy5Dlg::OnButton1() 
{
	CString cstrGroup,cstrInputData[5];
 	int iGroup;
 	m_Group_Edit.GetWindowText(cstrGroup); 
	m_No1_Edit.GetWindowText(cstrInputData[0]);
 	m_No2_Edit.GetWindowText(cstrInputData[1]);
	m_No3_Edit.GetWindowText(cstrInputData[2]);
	m_No4_Edit.GetWindowText(cstrInputData[3]);
	m_No5_Edit.GetWindowText(cstrInputData[4]); 
 	iGroup=atoi((LPCTSTR)cstrGroup); 
	for(int i=0;i<5;i++)
 	{ 
 	 	InputData[iGroup-1].dfData[i]=atof((LPCTSTR)cstrInputData[i]); 
 	} 

}

void CMy5Dlg::OnButton2() 
{
	CString cstrGroup;
	int iGroup;
	double dfMax=0,dfMin=0; 
 	char cBuffer[10]; 
 	m_Group_Edit.GetWindowText(cstrGroup);
 	iGroup=atoi((LPCTSTR)cstrGroup); 
 	dfMax=InputData[iGroup-1].dfData[0];
	dfMin=InputData[iGroup-1].dfData[0];  	 	 
 	for(int i=0;i<5;i++)
 	{ 
 	 	if(dfMax<InputData[iGroup-1].dfData[i]) 
 	 	{ 
 	 	 	dfMax=InputData[iGroup-1].dfData[i]; 
 	 	} 
 	 	if(dfMin>InputData[iGroup-1].dfData[i]) 
 	 	{ 
 	 	 	dfMin=InputData[iGroup-1].dfData[i]; 
 	 	} 
 	} 
 	_gcvt(dfMax,10,cBuffer);
 	m_Max_Edit.SetWindowText((LPCTSTR)cBuffer);
 	_gcvt(dfMin,10,cBuffer);
 	m_Min_Edit.SetWindowText((LPCTSTR)cBuffer);
	
}

void CMy5Dlg::OnButton3() 
{

 
 	CString cstrGroup; 
	int iGroup; 
	char cBuffer[10]; 
	int i; 			
 	m_Group_Edit.GetWindowText(cstrGroup);
	iGroup=atoi((LPCTSTR)cstrGroup); 
 	_gcvt(InputData[iGroup-1].dfData[0],10,cBuffer); 
 	m_No1_Edit.SetWindowText((LPCTSTR)cBuffer); 
 	_gcvt(InputData[iGroup-1].dfData[1],10,cBuffer); 	
	m_No2_Edit.SetWindowText((LPCTSTR)cBuffer); 
	_gcvt(InputData[iGroup-1].dfData[2],10,cBuffer); 	
	m_No3_Edit.SetWindowText((LPCTSTR)cBuffer); 	  
	_gcvt(InputData[iGroup-1].dfData[3],10,cBuffer); 	  
	m_No4_Edit.SetWindowText((LPCTSTR)cBuffer); 	  	
	_gcvt(InputData[iGroup-1].dfData[4],10,cBuffer); 	  
	m_No5_Edit.SetWindowText((LPCTSTR)cBuffer);
}

void CMy5Dlg::OnButton4() 
{
	OnOK();	
}
