#ifndef __InputNewEventDlg_H_
#define __InputNewEventDlg_H_

#include "Scheduler.h"
#pragma once

class CEntryInfoDlg : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CEntryInfoDlg)

public:
	CEntryInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEntryInfoDlg();
	void OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl);
	void ResetVariables();
	void SetDefaultSettings();
	void GetHourMinute(CString szTime, CString &szHour, CString &szMinute, int &iHour);
	BOOL CheckStartEndTime();
	BOOL CheckValidTitle();
	BOOL CheckValidDescription();
	const CEntryInfoDlg& operator=(const CEntryInfoDlg& InfoDlg);

	BOOL m_fUpdateScheduleDisplay;
	BOOL m_fDeleteSchedule;
	BOOL m_fModifySchedule;
	BOOL m_fClearSchedule;
	BOOL m_fCancelSchedule;
	BOOL m_fVisibleButtons;
	BOOL m_fVisibleDefaultButtons;
	CString m_szStartTime;
	CString m_szEndTime;
	CString m_szTitle;
	CString m_szDescription;
	CString m_szStartTimeHour;
	CString m_szStartTimeMinute;
	CString m_szEndTimeHour;
	CString m_szEndTimeMinute;
	int m_iStartHour;
	int m_iEndHour;

	HRESULT OnMouseOverButtons(IHTMLElement* pElement);
	HRESULT OnMouseOutButtons(IHTMLElement* pElement);
	HRESULT OnButtonSave(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	HRESULT OnButtonClear(IHTMLElement *pElement);
	HRESULT OnButtonModify(IHTMLElement *pElement);
	HRESULT OnButtonDelete(IHTMLElement *pElement);

	enum { IDD = IDD_ENTRYINFO_DLG, IDH = IDR_HTML_ENTRYINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};

#endif