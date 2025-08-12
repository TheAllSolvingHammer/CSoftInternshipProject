// CUsersTableDialog.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CUsersDlg.h"
#include "resource.h"
#include "../Application/JobTitleAppService.h"



// CUsersTableDialog dialog

IMPLEMENT_DYNAMIC(CUsersDlg, CDialogEx)

CUsersDlg::CUsersDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_USERS, pParent)
{
	if (!CJobTitlesAppService().GetAllJobs(m_oJobTitlesArray))
	{
		AfxMessageBox(_T("Failed to load job titles array."));
	}
}

CUsersDlg::~CUsersDlg()
{

}

void CUsersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_USERS_EMAIL, m_sttEmail);
	DDX_Control(pDX, IDC_STT_USERS_NAME, m_sttName);
	DDX_Control(pDX, IDC_EDB_USERS_NAME, m_edbName);
	DDX_Control(pDX, IDC_EDB_USERS_EMAIL, m_edbEmail);
	DDX_Control(pDX, IDC_CMB_USERS_JOB_TITLE, m_cmbJobTitle);
	DDX_Control(pDX, IDC_STT_USERS_JOB_TITLE, m_sttJobTitle);
}


BEGIN_MESSAGE_MAP(CUsersDlg, CDialogEx)
END_MESSAGE_MAP()


// CUsersTableDialog message handlers

BOOL CUsersDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (m_recUser.lID == 0) {
		SetWindowText(_T("Add New User"));
	}
	else {
		SetWindowText(_T("Edit User"));
	}

	m_sttName.SetWindowText(_T("Name: "));
	m_sttEmail.SetWindowText(_T("Email: "));
	m_sttJobTitle.SetWindowText(_T("Job Title: "));
	m_cmbJobTitle.ModifyStyle(CBS_SORT, 0);

	if (!FetchTableData()) {
		AfxMessageBox(_T("Failed to load job titles."), MB_ICONERROR);
	}
	CJobTitlesAppService().GetJobByID(m_recUser.lJobTitleID, m_recJobTitle);

	int nIndex = FindJobTitleIndex(m_recUser.lJobTitleID);
	if (nIndex != CB_ERR) {
		m_cmbJobTitle.SetCurSel(nIndex);
	}
	else {
		m_cmbJobTitle.SetCurSel(-1);
	}

	m_edbEmail.SetWindowText(m_recUser.szEmail);
	m_edbName.SetWindowText(m_recUser.szName);
	UpdateData(FALSE);
	return TRUE;
}

int CUsersDlg::FindJobTitleIndex(const long lJobTitleID)
{
	for (int i = 0; i < m_cmbJobTitle.GetCount(); ++i) {
		if (m_cmbJobTitle.GetItemData(i) == (DWORD_PTR)lJobTitleID) {
			return i;
		}
	}
	return CB_ERR;
}

BOOL CUsersDlg::FetchTableData() {

	if (!CJobTitlesAppService().GetAllJobs(m_oJobTitlesArray))
	{
		AfxMessageBox(_T("Failed to load job titles."));
		return FALSE;
	}

	for (INT_PTR i = 0; i < m_oJobTitlesArray.GetSize();i++)
	{
		JOB_TITLES* pJobTitle = m_oJobTitlesArray.GetAt(i);
		if (pJobTitle) {
			int nIndex = m_cmbJobTitle.AddString(pJobTitle->szTitleName);
			if (nIndex != CB_ERR) {
				m_cmbJobTitle.SetItemData(nIndex, pJobTitle->lID);
			}
		}
	}
	return TRUE;
}

void CUsersDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (!UpdateData(TRUE))
	{
		return;
	}

	int nCurSel = m_cmbJobTitle.GetCurSel();
	if (nCurSel != CB_ERR) {
		m_recUser.lJobTitleID = (long)m_cmbJobTitle.GetItemData(nCurSel);
	}
	else {
		m_recUser.lJobTitleID = 0;
		AfxMessageBox(_T("Please select a Job Title."), MB_ICONWARNING);
		m_cmbJobTitle.SetFocus();
		return;
	}
	CString strName;
	m_edbName.GetWindowText(strName);
	wcscpy_s(m_recUser.szName, strName.GetString());
	CString strEmail;
	m_edbEmail.GetWindowText(strEmail);
	wcscpy_s(m_recUser.szEmail, strEmail.GetString());

	CDialogEx::OnOK();
}
