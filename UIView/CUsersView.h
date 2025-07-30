#pragma once
#include <afxcview.h>
#include "DLLExport.h"
#include <afx.h>
#include "CUsersDocument.h"


/////////////////////////////////////////////////////////////////////////////
//CCSoftInternshipProjectView

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
	void PopulateUsersList();
	void OnUserAdd();
	void OnUserEdit();
	void OnUserDelete();
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