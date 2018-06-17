#include "stdafx.h"
#include "Scheduler.h"
#include "SchedulerDlg.h"
#include "InputNewEventDlg.h"
#include "MyScheduler.h"
using namespace std;
	
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnNewEvent();
	afx_msg void OnExit();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


BEGIN_DHTML_EVENT_MAP(CSchedulerDlg)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONMOUSEOVER, _T("time"),  OnMouseOverTime)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONMOUSEOUT, _T("time"),  OnMouseOutTime)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONMOUSEOVER, _T("cmdbuttons"),  OnMouseOverButtons)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONMOUSEOUT, _T("cmdbuttons"),  OnMouseOutButtons)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONMOUSEOVER, _T("timedesc"),  OnMouseOverTimeDesc)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONMOUSEOVER, _T("newElements"),  OnMouseOverNewElements)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONMOUSEOUT, _T("newElements"),  OnMouseOutNewElements)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONCLICK, _T("newElements"),  OnClickNewElements)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONCLICK, _T("time"),  OnClickTime)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONCLICK, _T("timedesc"),  OnClickTimeDesc)
	DHTML_EVENT_AXCONTROL(DISPID_HTMLELEMENTEVENTS_ONCLICK, _T("Calendar1"), OnClickCalendar)
	DHTML_EVENT_ONCLICK(_T("BClearAll"), OnButtonClearAll)
END_DHTML_EVENT_MAP()


CSchedulerDlg::CSchedulerDlg(CWnd* pParent)
	: CDHtmlDialog(CSchedulerDlg::IDD, CSchedulerDlg::IDH, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSchedulerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	DDX_DHtml_AxControl(pDX, _T("Calendar1"), DISPID_MONTH, m_month);
	DDX_DHtml_AxControl(pDX, _T("Calendar1"), DISPID_DAY, m_day);
	DDX_DHtml_AxControl(pDX, _T("Calendar1"), DISPID_YEAR, m_year);
}

BEGIN_MESSAGE_MAP(CSchedulerDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
	ON_COMMAND(IDD_HELP_ABOUTSCHEDULER, OnHelpAbout)
	ON_COMMAND(IDD_EXIT, &CSchedulerDlg::OnExit)
	ON_COMMAND(IDD_SAVE, &CSchedulerDlg::OnSave)
END_MESSAGE_MAP()

BOOL CSchedulerDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

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

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	CTime t = CTime::GetCurrentTime();
	m_currMonth = (short)t.GetMonth();
	m_currDay = (short)t.GetDay();
	m_currYear = (short)t.GetYear();

	SetDefaultProperties();

	m_szDivClass = _T("newElements");
	m_iLastDivID = 0;


	VERIFY(SHGetSpecialFolderPath(NULL, m_scheduler_filepath, CSIDL_PERSONAL, 0));
	
	if(SHGetSpecialFolderPath(NULL, m_scheduler_filepath, CSIDL_PERSONAL, 0))
		PathAppend(m_scheduler_filepath, _T("Scheduler.sdr"));
		
	ASSERT(m_scheduler_filepath);

	return TRUE;
}

void CSchedulerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

void CSchedulerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

HCURSOR CSchedulerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HRESULT CSchedulerDlg::OnMouseOverTime(IHTMLElement* pElement)
{
	COleVariant varColor;
	CComPtr<IHTMLStyle> phtmlStyle;
	pElement->get_style(&phtmlStyle);

	ASSERT(phtmlStyle);

	if (phtmlStyle)
	{
		varColor = RED;
		phtmlStyle->put_textDecorationUnderline(VARIANT_TRUE);
		phtmlStyle->put_color(varColor);
		phtmlStyle->put_cursor(L"hand");
	}
	return NULL;
}

HRESULT CSchedulerDlg::OnMouseOutTime(IHTMLElement* pElement)
{
	COleVariant varColor;
	CComPtr<IHTMLStyle> phtmlStyle;
	
	pElement->get_style(&phtmlStyle);

	ASSERT(phtmlStyle);

	if (phtmlStyle)
	{
		varColor = BLACK;
		phtmlStyle->put_textDecorationUnderline(VARIANT_FALSE);
		phtmlStyle->put_color(varColor);
	}
	return NULL;
}

HRESULT CSchedulerDlg::OnMouseOverButtons(IHTMLElement* pElement)
{
	COleVariant varColor;
	CComPtr<IHTMLStyle> phtmlStyle;

	pElement->get_style(&phtmlStyle);

	ASSERT(phtmlStyle);

	if (phtmlStyle)
	{
		varColor = AQUA;
		phtmlStyle->put_color(varColor);
		phtmlStyle->put_cursor(L"hand");
	}
	return NULL;
}

HRESULT CSchedulerDlg::OnMouseOutButtons(IHTMLElement* pElement)
{
	COleVariant varColor;
	CComPtr<IHTMLStyle> phtmlStyle;

	pElement->get_style(&phtmlStyle);

	ASSERT(phtmlStyle);

	if (phtmlStyle)
	{
		varColor = YELLOW;
		phtmlStyle->put_color(varColor);
	}
	return NULL;
}

HRESULT CSchedulerDlg::OnMouseOverTimeDesc(IHTMLElement* pElement)
{
	CComPtr<IHTMLStyle> phtmlStyle;
	pElement->get_style(&phtmlStyle);

	ASSERT(phtmlStyle);

	if (phtmlStyle)
	{
		phtmlStyle->put_cursor(L"hand");
	}
	return NULL;
}

HRESULT CSchedulerDlg::OnMouseOverNewElements(IHTMLElement* pElement)
{
	COleVariant varColor;
	CComPtr<IHTMLStyle> phtmlStyle;

	pElement->get_style(&phtmlStyle);

	ASSERT(phtmlStyle);

	if (phtmlStyle)
	{
		varColor = RED;
		phtmlStyle->put_textDecorationUnderline(VARIANT_TRUE);
		phtmlStyle->put_color(varColor);
		phtmlStyle->put_cursor(L"hand");
	}
	return NULL;
}

HRESULT CSchedulerDlg::OnMouseOutNewElements(IHTMLElement* pElement)
{
	COleVariant varColor;
	CComPtr<IHTMLStyle> phtmlStyle;

	pElement->get_style(&phtmlStyle);

	ASSERT(phtmlStyle);

	if (phtmlStyle)
	{
		varColor = BLUE;
		phtmlStyle->put_textDecorationUnderline(VARIANT_FALSE);
		phtmlStyle->put_color(varColor);
	}
	return NULL;
}

HRESULT CSchedulerDlg::OnClickTime(IHTMLElement *pElement)
{
	CComBSTR getbstr;
	CEntryInfoDlg InfoDlg;
	
	UpdateData(true);

	if (CheckDates())
	{
		pElement->get_id(&getbstr);
		
		ASSERT(getbstr);

		InfoDlg.m_szStartTime = getbstr;
		InfoDlg.DoModal();

		if (InfoDlg.m_fUpdateScheduleDisplay)    
			OnUpdateScheduleDisplay(InfoDlg);
	}
	return S_OK;
}

HRESULT CSchedulerDlg::OnClickTimeDesc(IHTMLElement *pElement)
{
	CComBSTR getbstr;
	CEntryInfoDlg InfoDlg;
	CString szStr;
	
	pElement->get_id(&getbstr);
	
	ASSERT(getbstr);

	InfoDlg.m_fVisibleButtons = false;
	InfoDlg.m_fVisibleDefaultButtons = true;
	szStr = getbstr;
	InfoDlg.m_szStartTime = GetStartTimeFormatted(szStr);
	
	InfoDlg.DoModal();

	if (InfoDlg.m_fUpdateScheduleDisplay)    
		OnUpdateScheduleDisplay(InfoDlg);
	
	return S_OK;
}

HRESULT CSchedulerDlg::OnClickNewElements(IHTMLElement *pElement)
{
	BSTR getbstr = NULL;
	CEntryInfoDlg InfoDlg;
	CMyScheduler scheduler;
	CString szStr;
	CComPtr<IHTMLElement> phtmlElement;
	int iDivID, iScheduleInfo;

	pElement->get_parentElement(&phtmlElement);

	ASSERT(phtmlElement);

	if (phtmlElement)
		phtmlElement->get_id(&getbstr);

	ASSERT(getbstr);

	szStr = getbstr;
	InfoDlg.m_szStartTime = GetStartTimeFormatted(szStr);

	pElement->get_id(&getbstr);

	ASSERT(getbstr);

	szStr = getbstr;
	iDivID = atoi(szStr);
	
	for (iScheduleInfo=0; iScheduleInfo < m_scheduler_array.GetSize(); iScheduleInfo++)
	{
		scheduler = m_scheduler_array.GetAt(iScheduleInfo);

		if (scheduler.m_iId == iDivID)
			break;
	}
	
	ASSERT(scheduler.m_iId==iDivID);

	InfoDlg.m_szTitle = scheduler.m_szTitle;
	InfoDlg.m_szDescription = scheduler.m_szDescription;

	InfoDlg.m_fVisibleButtons = true;
	InfoDlg.m_fVisibleDefaultButtons = false;
	InfoDlg.DoModal();

	if (InfoDlg.m_fDeleteSchedule)
	{
		m_scheduler_array.RemoveAt(iScheduleInfo);
		OnDeleteScheduleDisplay(scheduler);
	}	
	else if (InfoDlg.m_fModifySchedule)
	{
		RemoveInfoFromTable();
		OnModifyScheduleDisplay(m_scheduler_array.ElementAt(iScheduleInfo), InfoDlg);
		DateSchedules();
	}
	else

	InfoDlg.SetDefaultSettings();

	return S_OK;
}

HRESULT CSchedulerDlg::OnButtonClearAll(IHTMLElement* /*pElement*/)
{
	RemoveInfoFromTable();
	m_scheduler_array.RemoveAll();
	SetDefaultProperties();
	return S_OK;
}

void CSchedulerDlg::SetDefaultProperties()
{
	m_month = m_currMonth;
	m_day = m_currDay;
	m_year = m_currYear;

	UpdateData(false);
}

BOOL CSchedulerDlg::CheckDates()
{
	BOOL fRetval = true;

	ASSERT(m_month.iVal);
	ASSERT(m_day.iVal);
	ASSERT(m_year.iVal);

	CTime currTime(m_currYear, m_currMonth, m_currDay, 0, 0, 0, 0);
	CTime enteredTime(m_year.iVal, m_month.iVal, m_day.iVal, 0, 0, 0, 0);

	if (!(m_month.iVal && m_day.iVal && m_year.iVal) || (currTime > enteredTime))
	{
		fRetval = false;
		SetDefaultProperties();
		AfxMessageBox (IDS_INVALIDDATE);
	}

	return fRetval;
}
CString CSchedulerDlg::AdjustHour(int iHour)
{
	ASSERT(iHour < 24);
	CString szRetval;
	szRetval.Format("%d", iHour < 13 ? iHour : iHour-12);
	return(szRetval);
}

CString CSchedulerDlg::SetTimeFormat(int iHour, int iMinutes)
{
	CString szTime_span;

	szTime_span = AdjustHour(iHour);
	
	if (iMinutes)
		szTime_span += _T(":30");
	else
		szTime_span += _T(":00");

	if (iHour >= 12)
		szTime_span += _T(" pm");
	else
		szTime_span += _T(" am");
	 
	return szTime_span;
}

inline void CSchedulerDlg::DateSchedules()
{
	CComBSTR startTime;
	CComBSTR endTime;
	CComBSTR scheduleEntry;
	CComBSTR tempbstr;
	CMyScheduler scheduler;
	CString szTempstr;
	CString szInnerHtml;
	CString szHour;
	CString szDate;
	CString szElementId;
	CString szEid;
	CString szTempstring;
	CTime mytime;
	HRESULT result;
	COleVariant varColor;

	if(CheckDates()) 
	{
		if (m_scheduler_array.GetSize())
		{
			for (int iallDates = 0; iallDates < m_scheduler_array.GetSize(); iallDates++)
			{
				scheduler = m_scheduler_array.GetAt(iallDates);
				if ((scheduler.m_iYear == m_year.iVal) && (scheduler.m_iMonth == m_month.iVal) && (scheduler.m_iDay == m_day.iVal))
				{
					CTime mytime( m_year.iVal, m_month.iVal, m_day.iVal, scheduler.m_iStartHour, scheduler.m_iStartMinutes, 0); 
					szDate = mytime.Format( "%A, %B %d, %Y" );
					szElementId = SetTimeFormat(scheduler.m_iStartHour, scheduler.m_iStartMinutes);

					for (int j=0; szElementId.GetAt(j) != ' ';j++)
						szEid += szElementId.GetAt(j);

					CComPtr<IHTMLElement> pHTMLElement;
					result = GetElement(szEid, &pHTMLElement);

					ASSERT(pHTMLElement);

					szElementId += _T(" - ");
					szElementId += SetTimeFormat(scheduler.m_iEndHour, scheduler.m_iEndMinutes);
					
					CComPtr<IHTMLStyle> phtmlStyle;
					if (pHTMLElement)
						pHTMLElement->get_style(&phtmlStyle); 

					ASSERT(phtmlStyle);

					if (phtmlStyle)
					{
						varColor = BLUE;
						phtmlStyle->put_color(varColor);
					}
				
					szInnerHtml = scheduler.m_szTitle;
					szInnerHtml += _T(": ");
					szInnerHtml += szElementId;
					szInnerHtml += _T(" (");
					szInnerHtml += szDate;
					szInnerHtml += _T(")");
					szInnerHtml += _T("\n");	
	
					szTempstr.Format(_T("<DIV class=%s title=%s id=%d>%s</DIV>"), m_szDivClass, "Modify/Delete", 
						scheduler.m_iId, szInnerHtml);
					tempbstr = szTempstr.AllocSysString();

					scheduleEntry = GetElementHtml(szEid);
					if (scheduleEntry)
						scheduleEntry += tempbstr;
					else
						scheduleEntry = tempbstr;
					
					SetElementHtml(szEid, scheduleEntry);
					szEid.Empty();
					scheduleEntry.Empty();
				}
			}
		}
	}
}

void CSchedulerDlg::RemoveInfoFromTable()
{
	CComBSTR blankBstr;
	CMyScheduler schedulerEntry;
	CString szTime;

	for (int iallDates = 0; iallDates < m_scheduler_array.GetSize(); iallDates++)
	{
		schedulerEntry = m_scheduler_array.GetAt(iallDates);
		
		szTime = AdjustHour(schedulerEntry.m_iStartHour);
		szTime += _T(":");

		if (schedulerEntry.m_iStartMinutes)
			szTime += _T("30");
		else
			szTime += _T("00");

		SetElementText(szTime, blankBstr);
	}
}
void CSchedulerDlg::OpenScheduler(void)
{
	CFile schedulerFile;
	CMyScheduler scheduler;

	if( schedulerFile.Open(m_scheduler_filepath, CFile::modeRead) ) 
	{
		CArchive ar(&schedulerFile, CArchive::load);
		m_scheduler_array.Serialize(ar);
		ar >> m_iLastDivID;

		DateSchedules();
		
		ar.Close();
		schedulerFile.Close();
	}
}

void CSchedulerDlg::ExitScheduler(void)
{
	CFile schedulerFile;
	CMyScheduler scheduler;
	
	if (m_scheduler_array.GetSize())
	{
		TRY
		{
			if( !schedulerFile.Open(m_scheduler_filepath, CFile::modeCreate | CFile::modeWrite)) 
			{
				AfxMessageBox (IDS_CANNOTOPENFILE);
			}
			else
			{
				CArchive ar(&schedulerFile, CArchive::store);
				m_scheduler_array.Serialize(ar);
				ar << m_iLastDivID;

				ar.Close();

				schedulerFile.Close();
			}
		}
		CATCH( CFileException, e )
		{
			#ifdef _DEBUG
				afxDump << "File " << m_scheduler_filepath << " cannot be created\n";
			#endif
		}
		END_CATCH
	}
	else
	{
		if (schedulerFile.Open(m_scheduler_filepath, CFile::modeRead))
		{
			schedulerFile.Close();
			TRY
			{
				CFile::Remove(m_scheduler_filepath);
			}
			CATCH( CFileException, e)
			{
				#ifdef _DEBUG
					afxDump << "File " << m_scheduler_filepath << " cannot be removed\n";
				#endif
			}
			END_CATCH
		}
	}
	PostQuitMessage(0);
}

void CSchedulerDlg::OnHelpAbout(void)
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CSchedulerDlg::OnUpdateScheduleDisplay(const CEntryInfoDlg& InfoDlg)
{
	CMyScheduler schedulerEntry;

	schedulerEntry.m_iMonth = m_month.iVal;
	schedulerEntry.m_iDay = m_day.iVal;
	schedulerEntry.m_iYear = m_year.iVal;
	schedulerEntry.m_szTitle = InfoDlg.m_szTitle;
	schedulerEntry.m_szDescription = InfoDlg.m_szDescription;
	schedulerEntry.m_iStartHour = InfoDlg.m_iStartHour;
	schedulerEntry.m_iEndHour = InfoDlg.m_iEndHour;
	schedulerEntry.m_iStartMinutes = atoi(InfoDlg.m_szStartTimeMinute);
	schedulerEntry.m_iEndMinutes = atoi(InfoDlg.m_szEndTimeMinute);
	schedulerEntry.m_iId = m_iLastDivID++;
	
	m_scheduler_array.Add(schedulerEntry);

	RemoveInfoFromTable();
	
	DateSchedules();
}

void __stdcall CSchedulerDlg::OnClickCalendar()
{
	UpdateData(true);
	RemoveInfoFromTable();
	DateSchedules();
}

CString CSchedulerDlg::GetStartTimeFormatted(CString szStartTime)
{
	CString szHour;
	CString szAmpm;
	CString szRetval;
	int i, iHour;

	for(i=0; szStartTime.GetAt(i) != ':'; i++)
		szHour += szStartTime.GetAt(i);

	ASSERT(szHour);

	iHour = atoi(szHour);
	szAmpm.Format("%s", iHour == 12 ? _T(" pm") : iHour > 6 ? _T(" am") : _T(" pm"));

	szRetval = szStartTime;
	szRetval += szAmpm;

	return szRetval;
}

void CSchedulerDlg::OnDeleteScheduleDisplay(CMyScheduler& scheduler)
{
	CComBSTR getbstr;
	CString szStr;
	
	szStr.Format("%d", scheduler.m_iId);

	ASSERT(szStr);

	SetElementHtml(szStr, getbstr);
}

void CSchedulerDlg::OnModifyScheduleDisplay(CMyScheduler& scheduler, const CEntryInfoDlg& InfoDlg)
{
	scheduler.m_iMonth = m_month.iVal;
	scheduler.m_iDay = m_day.iVal;
	scheduler.m_iYear = m_year.iVal;
	scheduler.m_szTitle = InfoDlg.m_szTitle;
	scheduler.m_szDescription = InfoDlg.m_szDescription;
	scheduler.m_iStartHour = InfoDlg.m_iStartHour;
	scheduler.m_iEndHour = InfoDlg.m_iEndHour;
	scheduler.m_iStartMinutes = atoi(InfoDlg.m_szStartTimeMinute);
	scheduler.m_iEndMinutes = atoi(InfoDlg.m_szEndTimeMinute);
}

void CSchedulerDlg::OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl)
{
	IHTMLElement *pClearAllElement;
	IHTMLStyle *pClearAllStyle;
	VARIANT varColor;
	HRESULT result = GetElement(_T("BClearAll"), &pClearAllElement);
	
	if (SUCCEEDED(result)) {
		pClearAllElement->get_style(&pClearAllStyle);
		varColor.vt = VT_I4;
		varColor.lVal = 0xfffacd;
		pClearAllStyle->put_color(varColor);
		varColor.lVal = 0x00000;
		pClearAllStyle->put_backgroundColor(varColor);
		pClearAllStyle->Release();	
		pClearAllElement->Release();
	}

	OpenScheduler();

	CDHtmlDialog::OnDocumentComplete(pDisp, szUrl);
}


void CAboutDlg::OnBnClickedOk()
{
	CDialog::OnOK();
}

void CSchedulerDlg::OnExit()
{
	CDialog::SendMessage(WM_CLOSE);
}


void CSchedulerDlg::OnSave()
{
	ofstream fout;
	fout.open("Output.txt");
	fout << "日期\t\t开始 - 结束\t标题\t描述\n";
	int cnt = m_scheduler_array.GetSize();
	CMyScheduler p;
	for(int i = 0;i < cnt;i++)
	{
		p = m_scheduler_array.ElementAt(i);
		fout << p.m_iYear << "." <<  p.m_iMonth  << "." << p.m_iDay << "\t";
		fout << p.m_iStartHour << ":"<< p.m_iStartMinutes << " - ";
		fout << p.m_iEndHour << ":" << p.m_iEndMinutes << "\t";
		fout << p.m_szTitle << "\t" << p.m_szDescription << endl;
	}
}
