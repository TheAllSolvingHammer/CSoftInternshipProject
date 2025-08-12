#pragma once
#include "afxdialogex.h"
#include <Projects.h>

#include <Users.h>


// CProjectDlg dialog


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
	bool FetchTableData();
private:
	CEdit m_edbName;
	CRichEditCtrl m_recDescription;
	CComboBox m_cmbManager;
	CComboBox m_cmbStatus;
	CStatic m_sttEffort;
	
	CStatic m_sttName;
	CStatic m_sttDescription;
	CStatic m_sttManager;
	CStatic m_sttStatus;
	CStatic m_sttEffortLabel;
public:
	USERS m_recUser;
	PROJECTS m_recProject;
	CUsersArray m_oUsersArray;
};
