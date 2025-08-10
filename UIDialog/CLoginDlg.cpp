// CLoginDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CLoginDlg.h"
#include "resource.h"


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_LOGIN_USERNAME, m_sttUsername);
	DDX_Control(pDX, IDC_STT_LOGIN_PASSWORD, m_sttPassword);
	DDX_Control(pDX, IDC_EDB_LOGIN_USERNAME, m_edbUsername);
	DDX_Control(pDX, IDC_EDB_LOGIN_PASSWORD, m_sttPassword);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_COMMAND(IDC_BTN_LOGIN_REGISTER, &CLoginDlg::OnLoginRegister)
END_MESSAGE_MAP()


// CLoginDlg message handlers

void CLoginDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CEdit* pUsername = (CEdit*)GetDlgItem(IDC_EDB_LOGIN_USERNAME);
	if (pUsername)
	{
		pUsername->SetFocus();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnLoginRegister()
{
	// TODO: Add your command handler code here
}
