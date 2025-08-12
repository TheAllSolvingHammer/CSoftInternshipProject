#pragma once
#include "afxdialogex.h"
#include <Projects.h>

#include <Users.h>
#include <Tasks.h>


// CProjectDlg dialog
enum ProjectStateDialog
{
	PROJECT_DIALOG_STATE_ACTIVE = 0,
	PROJECT_DIALOG_STATE_FINISHED,
	PROJECT_DIALOG_STATE_COUNT
};

const TCHAR* gl_szProjectStateDescriptionDialog[] = {
	_T("Active"),
	_T("Finished")
};

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

const TCHAR* gl_szColumnHeadersTasks[] = {
	_T("ID"),
	_T("Name"),
	_T("Description"),
	_T("User in Charge"),
	_T("Status"),
	_T("Effort"),
};

const int gl_nColumnWidthsTasks[] = {
	50,
	150,
	200,
	150,
	100,
	150
};

enum TaskState
{
	TASK_STATE_PENDING = 0,
	TASK_STATE_IN_PROGRESS,
	TASK_STATE_ENDED,
	TASK_STATE_COUNT
};

const TCHAR* gl_szTaskStateDescription[] = {
	_T("Pending"),
	_T("In Progress"),
	_T("Ended")
};


class UIDialogDLL_EXP CProjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectDlg)

public:
	CProjectDlg(CWnd* pParent = nullptr);   // standard constructor
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
private:
	int FindUserIndex(const long lUserID);
	int FindStatusIndex(const short status);
	bool FetchTableData();
private:
	//Елементи
	CEdit m_edbName;
	CRichEditCtrl m_recDescription;
	CComboBox m_cmbManager;
	CComboBox m_cmbStatus;
	CStatic m_sttEffort;
	CListCtrl m_lscTasks;
	
	//Описания
	CStatic m_sttName;
	CStatic m_sttDescription;
	CStatic m_sttManager;
	CStatic m_sttStatus;
	CStatic m_sttEffortLabel;
	CStatic m_sttTasks;

	//Помощни променливи
public:
	USERS m_recUser;
	PROJECTS m_recProject;
	CUsersArray m_oUsersArray;
	CTasksArray m_oTasksArray;
};
