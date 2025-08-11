// CLoginDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CLoginDlg.h"
#include "resource.h"
#include "RegisterDlg.h"

#define STATIC_TEXT_LOGIN_USERNAME "Username: "
#define STATIC_TEXT_LOGIN_PASSWORD "Password: "

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
    UpdateData(TRUE);

    CString strUsername;
    m_edbUsername.GetWindowText(strUsername);
    CString strPassword;
    m_edbPassword.GetWindowText(strPassword);
    if (strUsername.IsEmpty() || strPassword.IsEmpty())
    {
        AfxMessageBox(_T("Please enter both email and password."));
        return;
    }

    ////!!!!!!!!!!!!!!!!!
    //if (!CUsersAppService().VerifyUserLogin(strUsername, strPassword))
    //{
    //    AfxMessageBox(_T("Invalid email or password."));
    //    
    //}
	AfxMessageBox(_T("Login successful!"));
	//pdoc set user !!!!!!!!!!!!!!!!!!!!!!
	CDialogEx::OnOK();
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CEdit* pUsername = (CEdit*)GetDlgItem(IDC_EDB_LOGIN_USERNAME);
	if (pUsername)
	{
		pUsername->SetFocus();
	}

    m_sttUsername.SetWindowText(_T(STATIC_TEXT_LOGIN_USERNAME));
    m_sttPassword.SetWindowText(_T(STATIC_TEXT_LOGIN_PASSWORD));
	return TRUE;  
	
}

void CLoginDlg::OnLoginRegister()
{

    CRegisterDlg regDlg;
    if (regDlg.DoModal() == IDOK)
    {
        AfxMessageBox(_T("Registration successful! You can now log in."));
        UpdateData(FALSE);
        CEdit* pUsername = (CEdit*)GetDlgItem(IDC_EDB_LOGIN_USERNAME);
        if (pUsername)
        {
            pUsername->SetFocus();
        }
    }
}
