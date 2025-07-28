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
	FreeUsersArray();
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

	/*if (!m_oAppService.GetAllUsers(m_oUsersArray)) 
	{
		AfxMessageBox(_T("Failed to load"));
		return FALSE;
	}

	for (INT_PTR i = 0; i < m_oUsersArray.GetCount();i++) 
	{
		USERS* pUser = new USERS();
		CString strID;
		strID.Format(_T("$ld"), pUser->lID);
		int index = m_lscUsers.InsertItem(i, strID);
		m_lscUsers.SetItemText(index, 1, pUser->szName);
		m_lscUsers.SetItemText(index, 2, pUser->szEmail);
	}*/


	return TRUE;
}

void CUsersTableDialog::FreeUsersArray()
{
	for (INT_PTR i = 0; i < m_oUsersArray.GetCount();i++) 
	{
		delete m_oUsersArray[i];
	}
	m_oUsersArray.RemoveAll();
}
