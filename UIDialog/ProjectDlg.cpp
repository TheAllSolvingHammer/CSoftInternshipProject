// ProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "ProjectDlg.h"
#include "resource.h"
#include <..\Application\UsersAppService.h>
#include <..\Application\ProjectsAppService.h>


// CProjectDlg dialog

IMPLEMENT_DYNAMIC(CProjectDlg, CDialogEx)
BEGIN_MESSAGE_MAP(CProjectDlg, CDialogEx)
END_MESSAGE_MAP()

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
	DDX_Control(pDX, IDC_LSC_PROJECT_TASKS, m_lscTasks);
	DDX_Control(pDX, IDC_STT_PROJECT_TASKS, m_sttTasks);
}





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
	m_sttTasks.SetWindowText(_T("Task list: "));
	DWORD dwStyle = m_lscTasks.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_lscTasks.SetExtendedStyle(dwStyle);
	m_lscTasks.SetView(LVS_REPORT);

	for (int i = 0; i < TASK_COLUMN_COUNT; ++i) 
	{
		m_lscTasks.InsertColumn(i, gl_szColumnHeadersTasks[i], LVCFMT_LEFT, gl_nColumnWidthsTasks[i]);
	}

	if (!FetchTableData()) {
		AfxMessageBox(_T("Failed to load combo boxes"), MB_ICONERROR);
		return FALSE;
	}

	int nIndex = FindUserIndex(m_recProject.lProjectManagerID);
	if (nIndex != CB_ERR) {
		m_cmbManager.SetCurSel(nIndex);
	}
	else {
		m_cmbManager.SetCurSel(-1);
	}

	nIndex = FindStatusIndex(m_recProject.sProjectStatus);
	if (nIndex != CB_ERR) {
		m_cmbStatus.SetCurSel(nIndex);
	}
	else {
		m_cmbStatus.SetCurSel(-1);
	}
	
	m_edbName.SetWindowText(m_recProject.szName);
	m_recDescription.SetWindowText(m_recProject.szDescription);
	CString strEffort;
	strEffort.Format(_T("%d"), m_recProject.nTotalEffort);
	m_sttEffort.SetWindowText(strEffort.GetString());
	UpdateData(FALSE);
	return TRUE;
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

int CProjectDlg::FindStatusIndex(const short sStatus)
{
	for (int i = 0; i < m_cmbStatus.GetCount(); ++i) {
		if ((short)m_cmbStatus.GetItemData(i) == sStatus) {
			return i;
		}
	}
	return CB_ERR;
}

bool CProjectDlg::FetchTableData() {

	if (!CUsersAppService().GetAllUsers(m_oUsersArray))
	{
		AfxMessageBox(_T("Failed to load users"));
		return false;
	}

	for (INT_PTR i = 0; i < m_oUsersArray.GetCount();i++)
	{
		USERS* pRecUser = m_oUsersArray.GetAt(i);
		if (pRecUser) {
			int nIndex = m_cmbManager.AddString(pRecUser->szName);
			if (nIndex != CB_ERR) {
				m_cmbManager.SetItemData(nIndex, pRecUser->lID);
			}
		}
	}

	for (int i = 0; i < PROJECT_DIALOG_STATE_COUNT; ++i)
	{
		int nIdx = m_cmbStatus.AddString(gl_szProjectStateDescriptionDialog[i]);
		m_cmbStatus.SetItemData(nIdx, i+1);
	}

	if (!CProjectsAppService().SelectTasksByProject(m_recProject.lID,m_oTasksArray))
	{
		AfxMessageBox(_T("Failed to load Tasks"));
		return false;
	}

	for (INT_PTR i = 0; i < m_oTasksArray.GetCount(); i++)
	{
		TASKS* pRecTask = m_oTasksArray.GetAt(i);

		CString strID;
		strID.Format(_T("%ld"), pRecTask->lID);
		int nIndex = m_lscTasks.InsertItem(i, strID);
		m_lscTasks.SetItemText(nIndex, TASK_COLUMN_NAME, pRecTask->szName);
		m_lscTasks.SetItemText(nIndex, TASK_COLUMN_DESCRIPTION, pRecTask->szDescription);
		for (int i = 0;i < TASK_STATE_COUNT;i++) {
			if (pRecTask->sTaskStatus = i + 1) {
				m_lscTasks.SetItemText(nIndex, TASK_COLUMN_STATUS, gl_szTaskStateDescription[i]);
				break;
			}
		}
		//fix !!!!!!!!
		CString strUserID;
		strUserID.Format(_T("%ld"), pRecTask->lUserInChargeID);
		m_lscTasks.SetItemText(nIndex, TASK_COLUMN_ASSIGNEE, strUserID.GetString());

		CString strEffort;
		strEffort.Format(_T("%d"), pRecTask->nTotalEffort);
		m_lscTasks.SetItemText(nIndex, TASK_COLUMN_EFFORT,strEffort.GetString());
	}
	return true;
}
