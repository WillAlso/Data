#include "stdafx.h"
#include "Scheduler.h"
#include "SchedulerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CSchedulerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CSchedulerApp::CSchedulerApp()
{
	EnableHtmlHelp();
}

CSchedulerApp theApp;

BOOL CSchedulerApp::InitInstance()
{
	AfxEnableControlContainer();


	CSchedulerDlg dlg;
	m_pMainWnd = &dlg;

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	dlg.ExitScheduler();
	return FALSE;
}

template <> void AFXAPI SerializeElements <CMyScheduler> ( CArchive& ar, CMyScheduler* pSchedule, INT_PTR nCount )
{
    for ( int i = 0; i < nCount; i++, pSchedule++ )
    {
        pSchedule->Serialize( ar );
    }
}
