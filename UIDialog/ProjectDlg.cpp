// ProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "ProjectDlg.h"
#include "resource.h"
#include <UsersAppService.h>

enum ProjectState
{
	PROJECT_STATE_ACTIVE = 0,
	PROJECT_STATE_FINISHED,
	PROJECT_STATE_COUNT
};

const TCHAR* gl_szProjectStateDescription[] = {
	_T("Active"),
	_T("Finished")
};

// CProjectDlg dialog

IMPLEMENT_DYNAMIC(CProjectDlg, CDialogEx)

CProjectDlg::CProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_DIALOG, pParent)
{

}

CProjectDlg::~CProjectDlg()
{
}

void CProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_PROJECT_NAME, m_sttName);
	DDX_Control(pDX, IDC_EDB_PROJECT_NAME, m_edbName);
	DDX_Control(pDX, IDC_REC_PROJECT_DESCRIPTION, m_recDescription);
	DDX_Control(pDX, IDC_STT_PROJECT_DESCRIPTION, m_sttDescription);
	DDX_Control(pDX, IDC_CMB_PROJECT_MANAGER, m_cmbManager);
	DDX_Control(pDX, IDC_STT_PROJECT_MANAGER, m_sttManager);
	DDX_Control(pDX, IDC_CMB_PROJECT_STATUS, m_cmbStatus);
	DDX_Control(pDX, IDC_STT_PROJECT_STATUS, m_sttStatus);
	DDX_Control(pDX, IDC_STT_PROJECT_EFFORT, m_sttEffort);
	DDX_Control(pDX, IDC_STT_PROJECT_LABEL_EFFORT, m_sttEffortLabel);
}


BEGIN_MESSAGE_MAP(CProjectDlg, CDialogEx)
END_MESSAGE_MAP()


// CProjectDlg message handlers

BOOL CProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("Project"));
	m_sttName.SetWindowText(_T("Name: "));
	m_sttDescription.SetWindowText(_T("Description: "));
	m_sttManager.SetWindowText(_T("User in charge: "));
	m_sttStatus.SetWindowText(_T("Status: "));
	m_sttEffortLabel.SetWindowText(_T("Total Effort: "));
	// TODO:  Add extra initialization here
	int nIndex = FindUserIndex(m_recProject.lProjectManagerID);
	if (nIndex != CB_ERR) {
		m_cmbManager.SetCurSel(nIndex);
	}
	else {
		m_cmbManager.SetCurSel(-1);
	}
	for (int i = 0; i < PROJECT_STATE_COUNT; ++i) {
		int nIdx = m_cmbStatus.AddString(gl_szProjectStateDescription[i]);
		m_cmbStatus.SetItemData(nIdx, i);
	}
	m_edbName.SetWindowText(m_recProject.szName);
	m_recDescription.SetWindowText(m_recProject.szDescription);
	CString strEffort;
	strEffort.Format(_T("%d"), m_recProject.nTotalEffort);
	m_sttEffort.SetWindowText(strEffort.GetString());
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProjectDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}

int CProjectDlg::FindUserIndex(const long lUserID)
{
	for (int i = 0; i < m_cmbManager.GetCount(); ++i) {
		if (m_cmbManager.GetItemData(i) == (DWORD_PTR)lUserID) {
			return i;
		}
	}
	return CB_ERR;
}

bool CProjectDlg::FetchTableData() {

	if (!CUsersAppService().GetAllUsers(m_oUsersArray));
	{
		AfxMessageBox(_T("Failed to load users"));
		return false;
	}

	for (INT_PTR i = 0; i < m_oUsersArray.GetSize();i++)
	{
		USERS* pRecUser = m_oUsersArray.GetAt(i);
		if (pRecUser) {
			int nIndex = m_cmbManager.AddString(pRecUser->szName);
			if (nIndex != CB_ERR) {
				m_cmbManager.SetItemData(nIndex, pRecUser->lID);
			}
		}
	}
	return true;
}
