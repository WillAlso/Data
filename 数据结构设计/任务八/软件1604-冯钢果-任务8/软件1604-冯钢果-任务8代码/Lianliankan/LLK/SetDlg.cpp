// SetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "SetDlg.h"
#include "afxdialogex.h"

int FBG = 0;

// CSetDlg �Ի���

IMPLEMENT_DYNAMIC(CSetDlg, CDialogEx)

CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetDlg::IDD, pParent)
{

}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSetDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSetDlg ��Ϣ�������


void CSetDlg::OnBnClickedButton1()
{
	FBG = 1;
}


void CSetDlg::OnBnClickedButton2()
{
	FBG = 2;
}
