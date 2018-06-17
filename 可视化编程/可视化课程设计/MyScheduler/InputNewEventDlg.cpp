#include "stdafx.h"
#include "InputNewEventDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CEntryInfoDlg, CDHtmlDialog)

CEntryInfoDlg::CEntryInfoDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CEntryInfoDlg::IDD, CEntryInfoDlg::IDH, pParent)
{
	SetDefaultSettings();
}

CEntryInfoDlg::~CEntryInfoDlg()
{
}

void CEntryInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	DDX_DHtml_SelectString (pDX, _T("ListStartTime"), m_szStartTime);
	DDX_DHtml_SelectString (pDX, _T("ListEndTime"), m_szEndTime);
	DDX_DHtml_ElementValue (pDX, _T("Title"), m_szTitle);
	DDX_DHtml_ElementValue (pDX, _T("Description"), m_szDescription);
	DDV_MaxChars(pDX, m_szTitle, 30);
	DDV_MaxChars(pDX, m_szDescription, 200);
}

BOOL CEntryInfoDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	m_szEndTime = _T("6:00 pm");
	return TRUE;
}

BEGIN_MESSAGE_MAP(CEntryInfoDlg, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CEntryInfoDlg)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONMOUSEOVER, _T("buttons"),  OnMouseOverButtons)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONMOUSEOUT, _T("buttons"),  OnMouseOutButtons)
	DHTML_EVENT_ONCLICK(_T("BSave"), OnButtonSave)
	DHTML_EVENT_ONCLICK(_T("BCancel"), OnButtonCancel)
	DHTML_EVENT_ONCLICK(_T("BClear"), OnButtonClear)
	DHTML_EVENT_ONCLICK(_T("BModify"), OnButtonModify)
	DHTML_EVENT_ONCLICK(_T("BDelete"), OnButtonDelete)
END_DHTML_EVENT_MAP()

HRESULT CEntryInfoDlg::OnButtonSave(IHTMLElement*)
{
	UpdateData(true);

	if (CheckValidTitle() && CheckValidDescription() && CheckStartEndTime())
	{
		ASSERT(m_szTitle);
		ASSERT(m_szDescription.GetLength() <= 200);

		m_fUpdateScheduleDisplay = true;
		OnOK();
	}
	else
		m_fUpdateScheduleDisplay = false;
	
	return S_OK;
}

HRESULT CEntryInfoDlg::OnButtonCancel(IHTMLElement*)
{
	m_fCancelSchedule = true;
	OnCancel();
	return S_OK;
}

HRESULT CEntryInfoDlg::OnButtonClear(IHTMLElement*)
{
	m_fClearSchedule = true;
	m_szTitle.Empty();
	m_szDescription.Empty();
	UpdateData (false);
	return S_OK;
}

HRESULT CEntryInfoDlg::OnButtonModify(IHTMLElement*)
{
	UpdateData(true);
	
	if (CheckValidTitle() && CheckValidDescription() && CheckStartEndTime())
	{
		ASSERT(m_szTitle);
		ASSERT(m_szDescription.GetLength() <= 200);

		m_fModifySchedule = true;
		OnOK();
	}
	else
		m_fModifySchedule = false;

	return S_OK;
}

HRESULT CEntryInfoDlg::OnButtonDelete(IHTMLElement*)
{
	m_fDeleteSchedule = true;
	OnCancel();
	return S_OK;
}

void CEntryInfoDlg::OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl)
{
	CDHtmlDialog::OnDocumentComplete(pDisp, szUrl);

	CComPtr<IHTMLElement> pModifyElement;
	CComPtr<IHTMLElement> pDeleteElement;
	CComPtr<IHTMLElement> pSaveElement;
	CComPtr<IHTMLElement> pClearElement;
	CComPtr<IHTMLElement> pCancelElement;
	CComPtr<IHTMLStyle> pModifyStyle;
	CComPtr<IHTMLStyle> pDeleteStyle;
	CComPtr<IHTMLStyle> pSaveStyle;
	CComPtr<IHTMLStyle> pClearStyle;
	CComPtr<IHTMLStyle> pCancelStyle;

	HRESULT result;
	CComBSTR bstr;
	CComBSTR Defaultbstr;
	CString szStr;
	CString szDefaultstr;
	COleVariant varColor;

	if (!m_fVisibleButtons)
		szStr = _T("hidden");
	else
		szStr = _T("visible");

	if (!m_fVisibleDefaultButtons)
		szDefaultstr = _T("hidden");
	else
		szDefaultstr = _T("visible");

	result = GetElement(_T("BModify"), &pModifyElement);
	result = GetElement(_T("BDelete"), &pDeleteElement); 
	result = GetElement(_T("BSave"), &pSaveElement);
	result = GetElement(_T("BClear"), &pClearElement); 
	result = GetElement(_T("BCancel"), &pCancelElement);
	
	ASSERT(pModifyElement);
	ASSERT(pDeleteElement);
	ASSERT(pSaveElement);
	ASSERT(pClearElement);
	ASSERT(pCancelElement);

	pModifyElement->get_style(&pModifyStyle);
	pDeleteElement->get_style(&pDeleteStyle);
	pSaveElement->get_style(&pSaveStyle);
	pClearElement->get_style(&pClearStyle);
	pCancelElement->get_style(&pCancelStyle);

	ASSERT(pModifyStyle);
	ASSERT(pDeleteStyle);
	ASSERT(pSaveStyle);
	ASSERT(pClearStyle);
	ASSERT(pCancelStyle);
	
	bstr = szStr.AllocSysString();
	Defaultbstr = szDefaultstr.AllocSysString();
	
	if (pModifyStyle && pDeleteStyle && pSaveStyle && pClearStyle && pCancelStyle)
	{
		pModifyStyle->put_visibility(bstr);
		pDeleteStyle->put_visibility(bstr);
		pSaveStyle->put_visibility(Defaultbstr);
		pClearStyle->put_visibility(Defaultbstr);
		varColor = YELLOW;
		pModifyStyle->put_color(varColor);
		pDeleteStyle->put_color(varColor);
		pSaveStyle->put_color(varColor);
		pClearStyle->put_color(varColor);
		pCancelStyle->put_color(varColor);
		varColor = BLACK;
		pModifyStyle->put_backgroundColor(varColor);
		pDeleteStyle->put_backgroundColor(varColor);
		pSaveStyle->put_backgroundColor(varColor);
		pClearStyle->put_backgroundColor(varColor);
		pCancelStyle->put_backgroundColor(varColor);
	}
}

HRESULT CEntryInfoDlg::OnMouseOverButtons(IHTMLElement* pElement)
{
	CComPtr<IHTMLStyle> phtmlStyle;
	COleVariant varColor;

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

HRESULT CEntryInfoDlg::OnMouseOutButtons(IHTMLElement* pElement)
{
	CComPtr<IHTMLStyle> phtmlStyle;
	COleVariant varColor;

	pElement->get_style(&phtmlStyle);

	ASSERT(phtmlStyle);

	if (phtmlStyle)
	{
		varColor = YELLOW;
		phtmlStyle->put_color(varColor);
	}
	return NULL;
}

void CEntryInfoDlg::SetDefaultSettings()
{
	m_fVisibleButtons = false;
	m_fVisibleDefaultButtons = true;
	m_fUpdateScheduleDisplay = false;
	m_fDeleteSchedule = false;
	m_fModifySchedule = false;
	m_fClearSchedule = false;
	m_fCancelSchedule = false;
	m_iStartHour = 0;
	m_iEndHour = 0;
}

BOOL CEntryInfoDlg::CheckStartEndTime()
{
	BOOL fRetval = true;

	ResetVariables();

	GetHourMinute(m_szStartTime, m_szStartTimeHour, m_szStartTimeMinute, m_iStartHour);

	GetHourMinute(m_szEndTime, m_szEndTimeHour, m_szEndTimeMinute, m_iEndHour);

	CTime startTime(2000, 8, 27, m_iStartHour, atoi(m_szStartTimeMinute), 0);
	CTime endTime(2000, 8, 27, m_iEndHour, atoi(m_szEndTimeMinute), 0);

	if (startTime >= endTime)
	{
		AfxMessageBox(IDS_INVALIDTIME);
		fRetval = false;
	}
		
	return fRetval;
}

const CEntryInfoDlg& CEntryInfoDlg::operator= (const CEntryInfoDlg& InfoDlg)
{
	if (this != &InfoDlg)
	{
		m_fUpdateScheduleDisplay = InfoDlg.m_fUpdateScheduleDisplay;
		m_fDeleteSchedule = InfoDlg.m_fDeleteSchedule;
		m_fModifySchedule = InfoDlg.m_fModifySchedule;
		m_fClearSchedule = InfoDlg.m_fClearSchedule;
		m_fVisibleButtons = InfoDlg.m_fVisibleButtons;
		m_fVisibleDefaultButtons = InfoDlg.m_fVisibleDefaultButtons;
		m_szStartTime = InfoDlg.m_szStartTime;
		m_szEndTime = InfoDlg.m_szEndTime;
		m_szTitle = InfoDlg.m_szTitle;
		m_szDescription = InfoDlg.m_szDescription;
		m_szStartTimeHour = InfoDlg.m_szStartTimeHour;
		m_szStartTimeMinute = InfoDlg.m_szStartTimeMinute;
		m_szEndTimeHour = InfoDlg.m_szEndTimeHour;
		m_szEndTimeMinute = InfoDlg.m_szEndTimeMinute;
		m_iStartHour = InfoDlg.m_iStartHour;
		m_iEndHour = InfoDlg.m_iEndHour;
	}
	return *this;
}

BOOL CEntryInfoDlg::CheckValidTitle()
{
	BOOL fRetval;
	CComPtr<IHTMLControlElement> pTitleControlElement;
	HRESULT result;

	if (m_szTitle.IsEmpty())
	{
		AfxMessageBox(IDS_ENTERTITLE);

		result = GetElementInterface(_T("Title"), &pTitleControlElement);
		
		ASSERT(pTitleControlElement);

		result = pTitleControlElement->focus();

		fRetval = false;
	}
	else
		fRetval = true;

	return fRetval;
}

BOOL CEntryInfoDlg::CheckValidDescription()
{
	BOOL fRetval = true;

	if (m_szDescription.GetLength() > 200)
		fRetval = false;

	return fRetval;
}

void CEntryInfoDlg::ResetVariables()
{
	m_szStartTimeHour.Empty();
	m_szStartTimeMinute.Empty();
	m_szEndTimeHour.Empty();
	m_szEndTimeMinute.Empty();
}

void CEntryInfoDlg::GetHourMinute(CString szTime, CString &szHour, CString &szMinute, int &iHour)
{
	CString szAmpm;
	int iTime;

	for (iTime =0; szTime.GetAt(iTime) != ':';iTime++)
		szHour += szTime.GetAt(iTime);
	
	iTime++;
	for (iTime; szTime.GetAt(iTime) != ' ';iTime++)
		szMinute += szTime.GetAt(iTime);
	
	szAmpm = szTime.Right(2);

	iHour = atoi(szHour);

	if (iHour != 12 && !strcmp(szAmpm, _T("pm")))
		iHour += 12;
}