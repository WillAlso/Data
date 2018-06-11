#pragma once

// CSanpSession ÃüÁîÄ¿±ê

class CSanpSession : public CInternetSession
{
public:
	CSanpSession(LPCTSTR szSessionNAME);
	CSanpSession(LPCTSTR szSessionNAME,CWnd* pStatusWnd);
	virtual ~CSanpSession();
	void Init();
	void SetStatus();
	void SetStatusWnd(CWnd* pWnd)
	{
		m_pStatusWnd = pWnd;
	}
	CString GetErrorMessage();
	virtual void OnStatusCallback(DWORD dwCotext,DWORD dwInternetStatus,
			LPVOID lpvStatusInformation,DWORD dwStatusInformationLength);
protected:
	CWnd* m_pStatusWnd;
	CString errorMessage;
};

CSanpSession::CSanpSession(LPCTSTR szSessionNAME)
	:CInternetSession(szSessionNAME)
{
	Init();
}

CSanpSession::CSanpSession(LPCTSTR szSessionNAME,CWnd* pStatusWnd)
	:CInternetSession(szSessionNAME)
{
	Init();
	m_pStatusWnd = pStatusWnd;
}

CSanpSession::~CSanpSession()
{
}

void CSanpSession::Init()
{
	m_pStatusWnd = NULL;
	//try
	EnableStatusCallback(TRUE);
}

void CSanpSession::OnStatusCallback(
	DWORD dwContext,
	DWORD dwInternetStatus,
	LPVOID lpvStatusInformaton,
	DWORD dwStatusInformationLength
	)
{

}