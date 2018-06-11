// SanpSession.cpp : 实现文件
//

#include "stdafx.h"
#include "WebBrowser.h"
#include "SanpSession.h"


// CSanpSession

CSanpSession::CSanpSession(LPCTSTR pstrAgent /*= NULL*/,
		DWORD dwContext /*= 1*/,
		DWORD dwAccessType /*= PRE_CONFIG_INTERNET_ACCESS*/,
		LPCTSTR pstrProxyName /*= NULL*/,
		LPCTSTR pstrProxyBypass /*= NULL*/,
		DWORD dwFlags /*= 0*/)
		: CInternetSession (pstrAgent, dwContext, dwAccessType, pstrProxyName, 
							pstrProxyBypass, dwFlags)
{
}

CSanpSession::~CSanpSession()
{
}


// CSanpSession 成员函数
