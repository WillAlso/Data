#ifndef __MYSCHEDULER_H_
#define __MYSCHEDULER_H_

#pragma once

class CMyScheduler : public CObject
{
public:
	CMyScheduler();
	virtual ~CMyScheduler();
	virtual void Serialize( CArchive& ar );
	const CMyScheduler& operator=(const CMyScheduler& scheduler);

	int m_iMonth;
	int m_iDay;
	int m_iYear;
	int m_iStartHour;
	int m_iStartMinutes;
	int m_iEndHour;
	int m_iEndMinutes;
	int m_iId;
	CString m_szTitle;
	CString m_szDescription;

protected:
	DECLARE_SERIAL( CMyScheduler )
};

#endif
