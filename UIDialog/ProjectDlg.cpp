// ProjectDlg.cpp : implementation file
#include "pch.h"
#include "afxdialogex.h"
#include "ProjectDlg.h"
#include "resource.h"
#include "TaskDlg.h"



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
	CTasksArray& oDeletedTasksArray)
	: CDialogEx(IDD_PROJECT_DIALOG, pParent),
	m_recProject(recProject),
	m_oUsersArray(oUsersArray),
	m_oTasksArray(oTasksArray),
	m_oUpdatedTasks(oUpdatedTasksArray),
	m_oDeletedTasks(oDeletedTasksArray)
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
	UpdateData(FALSE);
	return TRUE;
}

void CProjectDlg::OnOK()
{
	CString strName;
	m_edbName.GetWindowText(strName);
	strName.Trim();

	if (strName.IsEmpty())
	{
		AfxMessageBox(_T("Please enter a project name."), MB_ICONWARNING);
		m_edbName.SetFocus();
		return;
	}

	int nManagerIdx = m_cmbManager.GetCurSel();
	if (nManagerIdx == CB_ERR)
	{
		AfxMessageBox(_T("Please select a user in charge (manager)."), MB_ICONWARNING);
		m_cmbManager.SetFocus();
		return;
	}

	int nStatusIdx = m_cmbStatus.GetCurSel();
	if (nStatusIdx == CB_ERR)
	{
		AfxMessageBox(_T("Please select a project status."), MB_ICONWARNING);
		m_cmbStatus.SetFocus();
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

	for (int i = 0; i < PROJECT_DIALOG_STATE_COUNT; ++i)
	{
		int nIdx = m_cmbStatus.AddString(gl_szProjectStateDescriptionDialog[i]);
		m_cmbStatus.SetItemData(nIdx, i + 1);
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

			CString strAssigneeName = _T("Unknown");
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
			nTotalEffort += pTask->nTotalEffort;
	}

	CString strEffort;
	strEffort.Format(_T("%d"), nTotalEffort);
	m_sttEffort.SetWindowText(strEffort);
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
}

void CProjectDlg::OnBnClickedBtnProjectTaskDelete()
{
	POSITION pos = m_lscTasks.GetFirstSelectedItemPosition();
	if (!pos)
	{
		AfxMessageBox(_T("Please select a task to delete."), MB_ICONEXCLAMATION);
		return;
	}

	int nItem = m_lscTasks.GetNextSelectedItem(pos);
	TASKS* pTask = (TASKS*)m_lscTasks.GetItemData(nItem);

	if (!pTask)
	{
		AfxMessageBox(_T("Task not found."), MB_ICONERROR);
		return;
	}

	if (pTask->sTaskStatus != (TASK_STATE_ENDED + 1))
	{
		AfxMessageBox(_T("Only tasks with status 'Ended' can be deleted."), MB_ICONEXCLAMATION);
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

	AfxMessageBox(_T("Task deleted successfully."), MB_ICONINFORMATION);
}


void CProjectDlg::OnBnClickedBtnProjectTaskUpdate()
{
	POSITION pos = m_lscTasks.GetFirstSelectedItemPosition();
	if (!pos)
	{
		AfxMessageBox(_T("Please select a task to edit."));
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
	}
}
