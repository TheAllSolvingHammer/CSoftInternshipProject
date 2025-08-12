#pragma once
#include <afxcview.h>
#include "DLLExport.h"
#include <afx.h>
#include "CUsersDocument.h"
#include "Users.h"


/////////////////////////////////////////////////////////////////////////////
//CCSoftInternshipProjectView

//Enums
//-----------
enum EUserColumns
{
	EUSER_COLUMN_ID = 0,
	EUSER_COLUMN_NAME,
	EUSER_COLUMN_EMAIL,
	EUSER_COLUMN_JOB_TITLE,
	EUSER_COLUMN_COUNT
};

const TCHAR* gl_szColumnHeaders[] = {
	_T("ID"),
	_T("Name"),
	_T("Email"),
	_T("Job Title")
};

const int gl_nColumnWidths[] = {
	50,
	150,
	200,
	150
};


class UIViewDLL_EXP CUsersView : public CListView
{
	// Macros
	// ----------------
	DECLARE_DYNCREATE(CUsersView)
	DECLARE_MESSAGE_MAP()

	// Constructor / Destructor
	// ----------------
public:
	CUsersView() noexcept;
	virtual ~CUsersView();

	// Methods
	// ----------------
public:
	CUsersDocument* GetDocument() const;
	void OnUserAdd();
	void OnUserEdit();
	void OnUserDelete();
private:
	void PopulateUsersList();
	// Overrides
	// ----------------
protected:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /* pSender */, LPARAM /* lHint */, CObject* /* pHint */);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnContextMenu(CWnd* pWnd, CPoint point);
	virtual void OnLButtonDblClk(UINT nFlags, CPoint point);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Members
	// ----------------
};