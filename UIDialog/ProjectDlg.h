#pragma once
#include "afxdialogex.h"
#include <Projects.h>

#include <Users.h>
#include <Tasks.h>


// CProjectDlg dialog

/// <summary>
/// ���������� �� ������ �� �������
/// </summary>
enum ProjectDialogMode {
	PROEJCT_DIALOG_MODE_READ_ONLY=0,
	PROEJCT_DIALOG_MODE_EDITABLE,
	PROEJCT_DIALOG_MODE_CREATE

};

/// <summary>
/// ���������� �� ����������� �� ������( ������� � ��������� )
/// </summary>
enum ProjectStateDialog
{
	PROJECT_DIALOG_STATE_ACTIVE = 0,
	PROJECT_DIALOG_STATE_FINISHED,
	PROJECT_DIALOG_STATE_COUNT
};

/// <summary>
/// ���������� ����� �� ����������� �� �������
/// </summary>
const TCHAR* gl_szProjectStateDescriptionDialog[] = {
	_T("Active"),
	_T("Finished")
};

/// <summary>
/// ���������� �� �������� � ���� ���������� �� ��������
/// </summary>
enum TasksColumns
{
	TASK_COLUMN_ID = 0,
	TASK_COLUMN_NAME,
	TASK_COLUMN_DESCRIPTION,
	TASK_COLUMN_ASSIGNEE,
	TASK_COLUMN_STATUS,
	TASK_COLUMN_EFFORT,
	TASK_COLUMN_COUNT
};

/// <summary>
/// ���������� ������� ����� �� �������� � ���� ���������� �� ��������
/// </summary>
const TCHAR* gl_szColumnHeadersTasks[] = {
	_T("ID"),
	_T("Name"),
	_T("Description"),
	_T("User in Charge"),
	_T("Status"),
	_T("Effort"),
};

/// <summary>
/// ������ �� �������� �� ���� ���������� �� ��������
/// </summary>
const int gl_nColumnWidthsTasks[] = {
	50,
	150,
	200,
	150,
	100,
	150
};

/// <summary>
/// ���������� �������������� ����������� �� ������ ( Pending/In-Progress/Ended )
/// </summary>
enum TaskState
{
	TASK_STATE_PENDING = 0,
	TASK_STATE_IN_PROGRESS,
	TASK_STATE_ENDED,
	TASK_STATE_COUNT
};

/// <summary>
/// ���������� �������� ���� �� ����������� �� ������
/// </summary>
const TCHAR* gl_szTaskStateDescription[] = {
	_T("Pending"),
	_T("In Progress"),
	_T("Ended")
};

/// <summary>
/// ���� ��������� �� ����������� �� ������� �� �������
/// </summary>
class UIDialogDLL_EXP CProjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectDlg)

public:
	/// <summary>
	/// ���������� �� ������� �� �������, ������ �������� ���������
	/// </summary>
	/// <param name="pParent">CWnd �� ��������</param>
	/// <param name="recProject">������� �� ����� �� �� ������</param>
	/// <param name="oUsersArray">������������� ����� �� ����� �������� ���� ����� �� ����� �� ��������</param>
	/// <param name="oTasksArray">�������� ���������� �� �������</param>
	/// <param name="oUpdatedTasksArray">�������� ����� �� ���� ������������� �� �������</param>
	/// <param name="oDeletedtasksArray">�������� ����� �� ���� ������� �� �������</param>
	CProjectDlg(CWnd* pParent = nullptr, 
		PROJECTS& recProject=PROJECTS(),
		CUsersArray& oUsersArray=CUsersArray(), 
		CTasksArray& oTasksArray=CTasksArray(), 
		CTasksArray& oUpdatedTasksArray = CTasksArray(),
		CTasksArray& oDeletedtasksArray = CTasksArray(),
		ProjectDialogMode eProjectDialogMode=PROEJCT_DIALOG_MODE_EDITABLE);
	/// <summary>
	/// ���������� �� ������� �� �������
	/// </summary>
	virtual ~CProjectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	/// <summary>
	/// ������ ������ ��� �������
	/// </summary>
	afx_msg void OnBnClickedBtnProjectAddTask();
	/// <summary>
	/// ����������� ������ ��� �������
	/// </summary>
	afx_msg void OnBnClickedBtnProjectTaskDelete();
	/// <summary>
	/// ������� ������ ��� �������
	/// </summary>
	afx_msg void OnBnClickedBtnProjectTaskUpdate();
private:
	/// <summary>
	/// ������ ������� �� ���������� � ���������� ���� �������� ID
	/// </summary>
	/// <param name="lUserID">ID-�� �� �����������</param>
	/// <returns>������ �� ���������</returns>
	int FindUserIndex(const long lUserID);
	/// <summary>
	/// ������ ������� �� ����������� � ���������� ���� ������� ������ (�����)
	/// </summary>
	/// <param name="status">����� �������������� �������</param>
	/// <returns>������ �� ���������</returns>
	int FindStatusIndex(const short status);
	/// <summary>
	/// ������� �������� ����� �� ��������� �� ����� ������
	/// </summary>
	/// <returns>������ ��� � ������� ����������, �������� ��� �� �������</returns>
	bool FetchTableData();
	/// <summary>
	/// ����������� �������� ������ ����� �� ���������� �� ������ ������ ( �������� )
	/// </summary>
	void UpdateEffortTotal();
	/// <summary>
	/// ��������� ����������� �� ������� ���� �� � ��������� �� ��������/�������������/��������� �� ������
	/// </summary>
	void CheckProjectStatus();
	//void CheckUpdateArrayExistance(long lID);
private:
	//��������
	CEdit m_edbName;
	CRichEditCtrl m_recDescription;
	CComboBox m_cmbManager;
	CComboBox m_cmbStatus;
	CEdit m_edbEffort;
	CListCtrl m_lscTasks;
	CButton m_btnAddTask;
	CButton m_btnEditTask;
	CButton m_btnDeleteTask;
	
	//��������
	CStatic m_sttName;
	CStatic m_sttDescription;
	CStatic m_sttManager;
	CStatic m_sttStatus;
	CStatic m_sttEffortLabel;
	CStatic m_sttTasks;
	
	//�����
	ProjectDialogMode m_eProjectDialogMode;

	//������� ����������
public:
	PROJECTS& m_recProject;
	CUsersArray& m_oUsersArray;
	CTasksArray& m_oTasksArray;
	CTasksArray& m_oUpdatedTasks;
	CTasksArray& m_oDeletedTasks;
};
