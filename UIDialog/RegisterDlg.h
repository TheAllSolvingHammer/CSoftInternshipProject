#pragma once
#include "afxdialogex.h"


// CRegisterDlg dialog

class CRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CRegisterDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
private:
	CEdit m_edbUsername;
	CEdit m_edbEmail;
	CEdit m_edbPassword;
	CEdit m_edbPasswordRepeat;
	CComboBox m_cmbJobTitle;
	CStatic m_sttUsername;
	CStatic m_sttEmail;
	CStatic m_sttJobTitle;
	CStatic m_sttPassword;
	CStatic m_sttPasswordRepeat;
};
