#pragma once
#include "afxdialogex.h"
#include "Users.h"
#include "JobTitles.h"
#include "DllExport.h"
#include "../Application/JobTitleAppService.h"



// CUsersTableDialog dialog

class UIDialogDLL_EXP CUsersTableDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CUsersTableDialog)

public:
	CUsersTableDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUsersTableDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_USERS };
#endif
public:
	virtual void OnOK();
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
private:
	BOOL FetchTableData();
	void FreeJobTitlesArray();
	int FindJobTitleIndex(long lJobTitleID);
public:
	CStatic m_sttEmail;
	CStatic m_sttName;
	CStatic m_sttJobTitle;
	CEdit m_edbName;
	CEdit m_edbEmail;
	USERS m_recUser;
	JOB_TITLES m_recJobTitle;
	CComboBox m_cmbJobTitle;
	CJobTitlesArray m_oJobTitlesArray;
	CJobTitlesAppService m_oJobTitlesAppService;
};
