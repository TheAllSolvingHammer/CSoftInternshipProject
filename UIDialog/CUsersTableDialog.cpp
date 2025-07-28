// CUsersTableDialog.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CUsersTableDialog.h"
#include "resource.h"


// CUsersTableDialog dialog

IMPLEMENT_DYNAMIC(CUsersTableDialog, CDialogEx)

CUsersTableDialog::CUsersTableDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_USERS, pParent)
{

}

CUsersTableDialog::~CUsersTableDialog()
{
}

void CUsersTableDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LSC_USERS, m_lscUsers);
	DDX_Control(pDX, IDC_STT_USERS_EMAIL, m_sttEmail);
	DDX_Control(pDX, IDC_STT_USERS_NAME, m_sttName);
	DDX_Control(pDX, IDC_EDB_USERS_NAME, m_edbName);
	DDX_Control(pDX, IDC_EDB_USERS_EMAIL, m_edbEmail);
}


BEGIN_MESSAGE_MAP(CUsersTableDialog, CDialogEx)
END_MESSAGE_MAP()


// CUsersTableDialog message handlers

BOOL CUsersTableDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_sttName.SetWindowText(_T("Name: "));
	m_sttEmail.SetWindowText(_T("Email: "));
	m_lscUsers.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
	m_lscUsers.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 150);
	m_lscUsers.InsertColumn(2, _T("Email"), LVCFMT_LEFT, 200);
	m_lscUsers.InsertColumn(2, _T("Job Title"), LVCFMT_LEFT, 150);
	m_lscUsers.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	FetchTableData();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CUsersTableDialog::FetchTableData() {
	FreeUsersArray();
	m_lscUsers.DeleteAllItems();

	//
	

	return TRUE;
}

void CUsersTableDialog::FreeUsersArray()
{
	for (INT_PTR i = 0; i < m_oUsersArray.GetSize();i++) 
	{
		delete m_oUsersArray[i];
	}
	m_oUsersArray.RemoveAll();
}
