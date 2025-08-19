// ProjectDlg.cpp : implementation file
#include "pch.h"
#include "afxdialogex.h"
#include "ProjectDlg.h"
#include "resource.h"
#include "TaskDlg.h"

#define DLG_PROJECT_TITLE _T("Project")
#define DLG_PROJECT_NAME _T("Name: ")
#define DLG_PROJECT_DESCRIPTION _T("Description: ")
#define DLG_PROJECT_USER_IN_CHARGE _T("User in charge: ")
#define DLG_PROJECT_STATUS _T("Status: ")
#define DLG_PROJECT_EFFORT _T("Total Effort: ")
#define DLG_PROJECT_TASKS _T("Task list: ")

#define DLG_FAIL_COMBO_BOX _T("Failed to load combo boxes")
#define DLG_ENTER_PROJECT_NAME _T("Please enter a project name.")
#define DLG_SELECT_USER_IN_CHANGE _T("Please select a user in charge (manager).")
#define DLG_FAIL_COMBO_BOX_STATUS _T("Error in combo box status")

#define DLG_PROJECT_UNKNOWN_ASSIGNEE _T("Unknown")

#define DLG_HINT_TASK_DELETE _T("Please select a task to delete.")
#define DLG_HINT_TASK_NOT_FOUND _T("Task not found.")
#define DLG_HINT_TASK_DELETION_ENDED _T("Tasks with status 'Ended' can not be deleted.")
#define DLG_TASK_DELETION_SUCCESS _T("Task deleted successfully.")

#define DLG_HINT_TASK_UPDATE _T("Please select a task to edit.")

// CProjectDlg dialog

IMPLEMENT_DYNAMIC(CProjectDlg, CDialogEx)
BEGIN_MESSAGE_MAP(CProjectDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_PROJECT_ADD_TASK, &CProjectDlg::OnBnClickedBtnProjectAddTask)
	ON_BN_CLICKED(IDC_BTN_PROJECT_TASK_DELETE, &CProjectDlg::OnBnClickedBtnProjectTaskDelete)
	ON_BN_CLICKED(IDC_BTN_PROJECT_TASK_UPDATE, &CProjectDlg::OnBnClickedBtnProjectTaskUpdate)
END_MESSAGE_MAP()


CProjectDlg::CProjectDlg(CWnd* pParent /*=nullptr*/, 
	PROJECTS& recProject, 
	CUsersArray& oUsersArray, 
	CTasksArray& oTasksArray,
	CTasksArray& oUpdatedTasksArray,
	CTasksArray& oDeletedTasksArray,
	ProjectDialogMode eProjectDialogMode)
	: CDialogEx(IDD_PROJECT_DIALOG, pParent),
	m_recProject(recProject),
	m_oUsersArray(oUsersArray),
	m_oTasksArray(oTasksArray),
	m_oUpdatedTasks(oUpdatedTasksArray),
	m_oDeletedTasks(oDeletedTasksArray),
	m_eProjectDialogMode(eProjectDialogMode)
{

}

CProjectDlg::~CProjectDlg()
{
	m_oUpdatedTasks.RemoveAll();
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
	DDX_Control(pDX, IDC_EDB_PROJECT_EFFORT, m_edbEffort);
	DDX_Control(pDX, IDC_STT_PROJECT_LABEL_EFFORT, m_sttEffortLabel);
	DDX_Control(pDX, IDC_LSC_PROJECT_TASKS, m_lscTasks);
	DDX_Control(pDX, IDC_STT_PROJECT_TASKS, m_sttTasks);
	DDX_Control(pDX, IDC_BTN_PROJECT_ADD_TASK, m_btnAddTask);
	DDX_Control(pDX, IDC_BTN_PROJECT_TASK_UPDATE, m_btnEditTask);
	DDX_Control(pDX, IDC_BTN_PROJECT_TASK_DELETE, m_btnDeleteTask);
}

// CProjectDlg message handlers

BOOL CProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(DLG_PROJECT_TITLE);
	m_sttName.SetWindowText(DLG_PROJECT_NAME);
	m_sttDescription.SetWindowText(DLG_PROJECT_DESCRIPTION);
	m_sttManager.SetWindowText(DLG_PROJECT_USER_IN_CHARGE);
	m_sttStatus.SetWindowText(DLG_PROJECT_STATUS);
	m_sttEffortLabel.SetWindowText(DLG_PROJECT_EFFORT);
	m_sttTasks.SetWindowText(DLG_PROJECT_TASKS);
	m_recDescription.SetTargetDevice(NULL, 0);
	m_recDescription.ModifyStyle(0, WS_VSCROLL | ES_AUTOVSCROLL);
	m_edbEffort.SetReadOnly(TRUE);
	m_cmbStatus.EnableWindow(FALSE);

	DWORD dwStyle = m_lscTasks.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_lscTasks.SetExtendedStyle(dwStyle);
	m_lscTasks.SetView(LVS_REPORT);

	for (int i = 0; i < TASK_COLUMN_COUNT; ++i) 
	{
		m_lscTasks.InsertColumn(i, gl_szColumnHeadersTasks[i], LVCFMT_LEFT, gl_nColumnWidthsTasks[i]);
	}

	if (!FetchTableData()) {
		AfxMessageBox(DLG_FAIL_COMBO_BOX, MB_ICONERROR);
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
	if (nIndex != CB_ERR) 
	{
		m_cmbStatus.SetCurSel(nIndex);
	}
	else 
	{
		m_cmbStatus.SetCurSel(-1);
	}
	
	m_edbName.SetWindowText(m_recProject.szName);
	m_recDescription.SetWindowText(m_recProject.szDescription);

	UpdateEffortTotal();
	CheckProjectStatus();
	switch (m_eProjectDialogMode)
	{
	case PROEJCT_DIALOG_MODE_READ_ONLY:

		m_edbName.SetReadOnly(TRUE);
		m_recDescription.SetReadOnly(TRUE);
		m_cmbManager.EnableWindow(FALSE);
		m_cmbStatus.EnableWindow(FALSE);
		m_btnAddTask.EnableWindow(FALSE);
		m_btnEditTask.EnableWindow(FALSE);
		m_btnDeleteTask.EnableWindow(FALSE);
		break;

	case PROEJCT_DIALOG_MODE_EDITABLE:
		m_edbEffort.SetReadOnly(TRUE);
		m_cmbStatus.EnableWindow(FALSE);
		break;
	case PROEJCT_DIALOG_MODE_CREATE:
		m_btnAddTask.EnableWindow(FALSE);
		m_btnEditTask.EnableWindow(FALSE);
		m_btnDeleteTask.EnableWindow(FALSE);
		m_edbEffort.SetReadOnly(TRUE);
		m_cmbStatus.EnableWindow(FALSE);
		break;

	default:
		m_edbEffort.SetReadOnly(TRUE);
		m_cmbStatus.EnableWindow(FALSE);
		break;
	}
	UpdateData(FALSE);
	return TRUE;
}

void CProjectDlg::OnOK()
{
	if (m_eProjectDialogMode == PROEJCT_DIALOG_MODE_READ_ONLY) {
		CDialogEx::OnOK();
	}
	CString strName;
	m_edbName.GetWindowText(strName);
	strName.Trim();

	if (strName.IsEmpty())
	{
		AfxMessageBox(DLG_ENTER_PROJECT_NAME, MB_ICONWARNING);
		m_edbName.SetFocus();
		return;
	}

	int nManagerIdx = m_cmbManager.GetCurSel();
	if (nManagerIdx == CB_ERR)
	{
		AfxMessageBox(DLG_SELECT_USER_IN_CHANGE, MB_ICONWARNING);
		m_cmbManager.SetFocus();
		return;
	}
	CheckProjectStatus();
	int nStatusIdx = m_cmbStatus.GetCurSel();
	if (nStatusIdx == CB_ERR)
	{
		AfxMessageBox(DLG_FAIL_COMBO_BOX_STATUS, MB_ICONWARNING);
		return;
	}

	
	_tcsncpy_s(m_recProject.szName, strName, _TRUNCATE);

	CString strDescription;
	m_recDescription.GetWindowText(strDescription);
	_tcsncpy_s(m_recProject.szDescription, strDescription, _TRUNCATE);

	m_recProject.lProjectManagerID = (long)m_cmbManager.GetItemData(nManagerIdx);
	m_recProject.sProjectStatus = (short)m_cmbStatus.GetItemData(nStatusIdx);

	CDialogEx::OnOK();

}

int CProjectDlg::FindUserIndex(const long lUserID)
{
	for (int i = 0; i < m_cmbManager.GetCount(); ++i) 
	{
		if (m_cmbManager.GetItemData(i) == (DWORD_PTR)lUserID) 
		{
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

bool CProjectDlg::FetchTableData()
{
	m_cmbManager.Clear();
	m_cmbStatus.Clear();
	m_lscTasks.DeleteAllItems();

	for (INT_PTR i = 0; i < m_oUsersArray.GetCount(); i++)
	{
		USERS* pRecUser = m_oUsersArray.GetAt(i);
		if (pRecUser)
		{
				int nIndex = m_cmbManager.AddString(pRecUser->szName);
				if (nIndex != CB_ERR)
				{
					m_cmbManager.SetItemData(nIndex, pRecUser->lID);
				}	
		}
	}

	for (int i = 0; i < m_cmbManager.GetCount(); i++)
	{
		if ((LONG)m_cmbManager.GetItemData(i) == m_recProject.lProjectManagerID)
		{
			m_cmbManager.SetCurSel(i);
			break;
		}
	}

	for (int i = 0; i < PROJECT_DIALOG_STATE_COUNT; ++i)
	{
		if (m_cmbStatus.FindStringExact(-1, gl_szProjectStateDescriptionDialog[i]) == CB_ERR)
		{
			int nIdx = m_cmbStatus.AddString(gl_szProjectStateDescriptionDialog[i]);
			m_cmbStatus.SetItemData(nIdx, i + 1);
		}
	}

	for (INT_PTR i = 0; i < m_oTasksArray.GetCount(); i++)
	{
		TASKS* pRecTask = m_oTasksArray.GetAt(i);
		if (pRecTask)
		{
			CString strID;
			strID.Format(_T("%ld"), pRecTask->lID);
			int nIndex = m_lscTasks.InsertItem(i, strID);

			m_lscTasks.SetItemData(nIndex, (DWORD_PTR)pRecTask);

			m_lscTasks.SetItemText(nIndex, TASK_COLUMN_NAME, pRecTask->szName);
			m_lscTasks.SetItemText(nIndex, TASK_COLUMN_DESCRIPTION, pRecTask->szDescription);
			for (int j = 0; j < TASK_STATE_COUNT; j++) {
				if (pRecTask->sTaskStatus == j + 1) {
					m_lscTasks.SetItemText(nIndex, TASK_COLUMN_STATUS, gl_szTaskStateDescription[j]);
					break;
				}
			}

			CString strAssigneeName = DLG_PROJECT_UNKNOWN_ASSIGNEE;
			for (INT_PTR u = 0; u < m_oUsersArray.GetCount(); u++)
			{
				USERS* pRecUser = m_oUsersArray.GetAt(u);
				if (pRecUser && pRecUser->lID == pRecTask->lUserInChargeID)
				{
					strAssigneeName = pRecUser->szName;
					break;
				}
			}
			m_lscTasks.SetItemText(nIndex, TASK_COLUMN_ASSIGNEE, strAssigneeName);

			CString strEffort;
			strEffort.Format(_T("%d"), pRecTask->nTotalEffort);
			m_lscTasks.SetItemText(nIndex, TASK_COLUMN_EFFORT, strEffort.GetString());
		}
	}

	return true;
}

void CProjectDlg::UpdateEffortTotal()
{
	int nTotalEffort = 0;
	for (INT_PTR i = 0; i < m_oTasksArray.GetCount(); ++i)
	{
		TASKS* pTask = m_oTasksArray.GetAt(i);
		if (pTask)
		{
			nTotalEffort += pTask->nTotalEffort;
		}
	}

	CString strEffort;
	strEffort.Format(_T("%d"), nTotalEffort);
	m_edbEffort.SetWindowText(strEffort);
}

void CProjectDlg::CheckProjectStatus()
{
	bool bAllTasksEnded = true;
	for (INT_PTR i = 0; i < m_oTasksArray.GetCount(); ++i)
	{
		TASKS* pTask = m_oTasksArray.GetAt(i);
		if (pTask && pTask->sTaskStatus != (TASK_STATE_ENDED + 1))
		{
			bAllTasksEnded = false;
			break;
		}
	}

	if (bAllTasksEnded)
	{
		m_recProject.sProjectStatus = (short)(PROJECT_DIALOG_STATE_FINISHED + 1);

		int nIndex = FindStatusIndex(m_recProject.sProjectStatus);
		if (nIndex != CB_ERR)
		{
			m_cmbStatus.SetCurSel(nIndex);
		}
	}
	else 
	{
		m_recProject.sProjectStatus = (short)(PROJECT_DIALOG_STATE_ACTIVE + 1);

		int nIndex = FindStatusIndex(m_recProject.sProjectStatus);
		if (nIndex != CB_ERR)
		{
			m_cmbStatus.SetCurSel(nIndex);
		}
	}
}

void CProjectDlg::OnBnClickedBtnProjectAddTask()
{
	TASKS* pNewTask = new TASKS{};
	pNewTask->lID = 0;
	pNewTask->lProjectID = m_recProject.lID;

	CTaskDlg dlg(this, *pNewTask, m_oUsersArray, TASK_ADD);
	if (dlg.DoModal() == IDOK)
	{		
		m_oTasksArray.Add(pNewTask);
		m_oUpdatedTasks.Add(pNewTask);
	}
	else
	{
		delete pNewTask;
	}

	FetchTableData();
	UpdateEffortTotal();
	CheckProjectStatus();
}

void CProjectDlg::OnBnClickedBtnProjectTaskDelete()
{
	POSITION pos = m_lscTasks.GetFirstSelectedItemPosition();
	if (!pos)
	{
		AfxMessageBox(DLG_HINT_TASK_DELETE, MB_ICONEXCLAMATION);
		return;
	}

	int nItem = m_lscTasks.GetNextSelectedItem(pos);
	TASKS* pTask = (TASKS*)m_lscTasks.GetItemData(nItem);

	if (!pTask)
	{
		AfxMessageBox(DLG_HINT_TASK_NOT_FOUND, MB_ICONERROR);
		return;
	}

	if (pTask->sTaskStatus == (TASK_STATE_ENDED + 1))
	{
		AfxMessageBox(DLG_HINT_TASK_DELETION_ENDED, MB_ICONEXCLAMATION);
		return;
	}

	for (INT_PTR i = 0; i < m_oUpdatedTasks.GetCount(); ++i)
	{
		if (m_oUpdatedTasks.GetAt(i) == pTask)
		{
			m_oUpdatedTasks.RemoveAt(i);
			break;
		}
	}

	if (pTask->lID > 0)
	{
		TASKS* pCopy = new TASKS(*pTask);
		m_oDeletedTasks.Add(pCopy);
	}

	INT_PTR idxInAll = -1;
	for (INT_PTR i = 0; i < m_oTasksArray.GetCount(); ++i)
	{
		if (m_oTasksArray.GetAt(i) == pTask)
		{
			idxInAll = i;
			break;
		}
	}

	if (idxInAll != -1)
	{
		delete m_oTasksArray.GetAt(idxInAll);
		m_oTasksArray.RemoveAt(idxInAll);
	}

	FetchTableData();
	UpdateEffortTotal();
	CheckProjectStatus();

	AfxMessageBox(DLG_TASK_DELETION_SUCCESS, MB_ICONINFORMATION);
}


void CProjectDlg::OnBnClickedBtnProjectTaskUpdate()
{
	POSITION pos = m_lscTasks.GetFirstSelectedItemPosition();
	if (!pos)
	{
		AfxMessageBox(DLG_HINT_TASK_UPDATE);
		return;
	}

	int nItem = m_lscTasks.GetNextSelectedItem(pos);
	TASKS* pRecTask = (TASKS*)m_lscTasks.GetItemData(nItem);

	if (!pRecTask) return;

	CTaskDlg dlg(this, *pRecTask, m_oUsersArray, TASK_UPDATE);
	if (dlg.DoModal() == IDOK)
	{
		bool bFound = false;
		for (INT_PTR i = 0; i < m_oUpdatedTasks.GetCount(); ++i)
		{
			if (m_oUpdatedTasks.GetAt(i) == pRecTask)
			{
				*m_oUpdatedTasks.GetAt(i) = *pRecTask;
				bFound = true;
				break;
			}
		}

		if (!bFound)
		{
			m_oUpdatedTasks.Add(pRecTask);
		}

		FetchTableData();
		UpdateEffortTotal();
		CheckProjectStatus();
	}
}
