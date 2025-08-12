#pragma once
#pragma once
#include <afxcview.h>
#include "DLLExport.h"
#include <afx.h>
#include "ProjectsDocument.h"


/////////////////////////////////////////////////////////////////////////////


//Enums
//-----------
enum ProjectColumns
{
	PROJECT_COLUMN_ID = 0,
	PROJECT_COLUMN_NAME,
	PROJECT_COLUMN_DESCRIPTION,
	PROJECT_COLUMN_PROJECT_MANAGER,
	PROJECT_COLUMN_STATUS,
	PROJECT_COLUMN_EFFORT,
	PROJECT_COLUMN_COUNT
};

const TCHAR* gl_szColumnHeadersProject[] = {
	_T("ID"),
	_T("Name"),
	_T("Description"),
	_T("Manager"),
	_T("Status"),
	_T("Effort"),
};

const int gl_nColumnWidthsProject[] = {
	50,
	150,
	200,
	150,
	100,
	150
};

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


class UIViewDLL_EXP CProjectsView : public CListView
{
	// Macros
	// ----------------
	DECLARE_DYNCREATE(CProjectsView)
	DECLARE_MESSAGE_MAP()

	// Constructor / Destructor
	// ----------------
public:
	CProjectsView() noexcept;
	virtual ~CProjectsView();

	// Methods
	// ----------------
public:
	CProjectsDocument* GetDocument() const;
	void OnProjectAdd();
	void OnProjectEdit();
	void OnProjectDelete();
private:
	void PopulateProjectsList();
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