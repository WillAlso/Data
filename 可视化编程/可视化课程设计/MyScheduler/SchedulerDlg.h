
#ifndef __SCHEDULERDLG_H_
#define __SCHEDULERDLG_H_

#include "InputNewEventDlg.h"
#include "MyScheduler.h"
#include <iostream>
#include <fstream>

#define DISPID_MONTH 0x10
#define DISPID_DAY 0x11
#define DISPID_YEAR 0x0f

#pragma once

#pragma message("*** NOTE: This sample requires the Microsoft Access Calendar control (MSCAL.OCX). ***")

class CSchedulerDlg : public CDHtmlDialog
{
public:
	CSchedulerDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_SCHEDULER_DIALOG, IDH = IDR_HTML_SCHEDULER_DIALOG };

	CArray <CMyScheduler> m_scheduler_array;
	COleVariant m_month;
	COleVariant m_day;
	COleVariant m_year;
	CString m_szDivClass;
	TCHAR m_scheduler_filepath[MAX_PATH];
	int m_iLastDivID;
	short m_currMonth, m_currDay, m_currYear;
	
	void SetDefaultProperties();
	void DateSchedules();
	void RemoveInfoFromTable();
	void OnUpdateScheduleDisplay(const CEntryInfoDlg& InfoDlg);
	void OnDeleteScheduleDisplay(CMyScheduler& scheduler);
	void OnModifyScheduleDisplay(CMyScheduler& scheduler,const CEntryInfoDlg& InfoDlg);
	void OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl);
	BOOL CheckDates();
	CString AdjustHour(int iHour);
	CString SetTimeFormat(int iHour, int iMinutes);
	CString GetStartTimeFormatted(CString szStartTime);

	HRESULT OnMouseOverTime(IHTMLElement *pElement);
	HRESULT OnMouseOutTime(IHTMLElement *pElement);
	HRESULT OnMouseOverButtons(IHTMLElement *pElement);
	HRESULT OnMouseOutButtons(IHTMLElement *pElement);
	HRESULT OnMouseOverTimeDesc(IHTMLElement *pElement);
	HRESULT OnMouseOverNewElements(IHTMLElement *pElement);
	HRESULT OnMouseOutNewElements(IHTMLElement *pElement);
	HRESULT OnClickNewElements(IHTMLElement *pElement);
	HRESULT OnClickTime(IHTMLElement *pElement);
	HRESULT OnClickTimeDesc(IHTMLElement *pElement);
	HRESULT OnButtonClearAll(IHTMLElement *pElement);
	void __stdcall OnClickCalendar(); 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	HICON m_hIcon;
	HACCEL m_hAccel;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	void OpenScheduler(void);
	void ExitScheduler(void);
	void OnHelpAbout(void);
	afx_msg void OnExit();
	afx_msg void OnSave();
};

#endif
