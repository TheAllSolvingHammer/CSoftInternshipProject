// RegisterDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "RegisterDlg.h"
#include "resource.h"
#include <Users.h>
#include <bcrypt.h>

#define STATIC_TEXT_USERNAME            "Username: "
#define STATIC_TEXT_EMAIL               "E-mail Address: "
#define STATIC_TEXT_JOB_TITLE           "Assigned position: "
#define STATIC_TEXT_PASSWORD            "Password: "
#define STATIC_TEXT_REPEAT_PASSWORD     "Repeat password: "
// CRegisterDlg dialog

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTER_DIALOG, pParent)
{

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_REGISTER_USERNAME, m_edbUsername);
	DDX_Control(pDX, IDC_EDB_REGISTER_EMAIL, m_edbEmail);
	DDX_Control(pDX, IDC_CMB_REGISTER_JOB_TITLE, m_cmbJobTitle);
	DDX_Control(pDX, IDC_EDB_REGISTER_PASSWORD, m_edbPassword);
	DDX_Control(pDX, IDC_EDB_REGISTER_REPEAT_PASSWORD, m_edbPasswordRepeat);
	DDX_Control(pDX, IDC_STT_REGISTER_USERNAME, m_sttUsername);
	DDX_Control(pDX, IDC_STT_REGISTER_EMAIL, m_sttEmail);
	DDX_Control(pDX, IDC_STT_REGISTER_JOB_TITLE, m_sttJobTitle);
	DDX_Control(pDX, IDC_STT_REGISTER_PASSWORD, m_sttPassword);
	DDX_Control(pDX, IDC_STT_REGISTER_REPEAT_PASSWORD, m_sttPasswordRepeat);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
END_MESSAGE_MAP()

// CRegisterDlg message handlers

void CRegisterDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    
    UpdateData(TRUE);
    CString strUsername, strEmail, strPassword, strPasswordRepeat;
    m_edbUsername.GetWindowText(strUsername);
    m_edbEmail.GetWindowText(strEmail);
    m_edbPassword.GetWindowText(strPassword);
    m_edbPasswordRepeat.GetWindowText(strPasswordRepeat);

    if (strUsername.IsEmpty() || strEmail.IsEmpty() || strPassword.IsEmpty() || strPasswordRepeat.IsEmpty())
    {
        AfxMessageBox(_T("Please fill in all fields."));
        return;
    }

    if (strPassword.GetString() != strPasswordRepeat.GetString())
    {
        AfxMessageBox(_T("Passwords do not match. Please try again."));
        return;
    }

  
    USERS recUser;
    wcscpy_s(recUser.szName, strUsername.GetString());
    wcscpy_s(recUser.szEmail, strEmail.GetString());
    wcscpy_s(recUser.szHashedPassword, strEmail.GetString());
    int nCurSel = m_cmbJobTitle.GetCurSel();
    if (nCurSel != CB_ERR) {
        recUser.lJobTitleID = (long)m_cmbJobTitle.GetItemData(nCurSel);
    }
    else {
        recUser.lJobTitleID = 0;
        AfxMessageBox(_T("Please select a Job Title."), MB_ICONWARNING);
        m_cmbJobTitle.SetFocus();
        return;
    }
    
   //this must be fixed

	CDialogEx::OnOK();
}

BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
    m_sttUsername.SetWindowText(_T(STATIC_TEXT_USERNAME));
    m_sttEmail.SetWindowText(_T(STATIC_TEXT_EMAIL));
    m_sttJobTitle.SetWindowText(_T(STATIC_TEXT_JOB_TITLE));
    m_sttPassword.SetWindowText(_T(STATIC_TEXT_PASSWORD));
    m_sttPasswordRepeat.SetWindowText(_T(STATIC_TEXT_REPEAT_PASSWORD));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
