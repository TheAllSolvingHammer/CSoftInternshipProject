#include "pch.h"
#include "framework.h"
#include "CSoftInternshipProjectView.h"

/////////////////////////////////////////////////////////////////////////////
//CCSoftInternshipProjectView

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CCSoftInternshipProjectView, CListView)

BEGIN_MESSAGE_MAP(CCSoftInternshipProjectView, CListView)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CCSoftInternshipProjectView::CCSoftInternshipProjectView() noexcept
{
}

CCSoftInternshipProjectView::~CCSoftInternshipProjectView()
{
}

// Methods
// ----------------
CCSoftInternshipProjectDocument* CCSoftInternshipProjectView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCSoftInternshipProjectDocument)));
	return (CCSoftInternshipProjectDocument*)m_pDocument;
}


// MFC Message Handlers
// ----------------


//Methods
// ----------------
void CCSoftInternshipProjectView::PopulateUsersList()
{
    CListCtrl& pLstCtrl = GetListCtrl(); 
    if (!pLstCtrl.GetSafeHwnd())
    {
        AfxMessageBox(_T("Error in getting the safe HWND"));
        return;
    }
    pLstCtrl.DeleteAllItems();

    CHeaderCtrl* pHeaderCtrl = pLstCtrl.GetHeaderCtrl();
    if (pHeaderCtrl == NULL)
    {
        AfxMessageBox(_T("Error in getting the header of the list control"));
        return;
    }
    if (pLstCtrl.GetHeaderCtrl()->GetItemCount() == 0) {
        pLstCtrl.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
        pLstCtrl.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 150);
        pLstCtrl.InsertColumn(2, _T("Email"), LVCFMT_LEFT, 200);
        pLstCtrl.InsertColumn(3, _T("Job Title"), LVCFMT_LEFT, 150);
    }

    CCSoftInternshipProjectDocument* pDoc = GetDocument();
    if (pDoc == NULL) {
        return;
    }

    const CUsersArray& users = pDoc->GetUsers();

    for (INT_PTR i = 0; i < users.GetSize(); ++i) {
        USERS* pUser = users.GetAt(i);
        if (pUser) {
            CString strID;
            strID.Format(_T("%ld"), pUser->lID);
            int index = pLstCtrl.InsertItem(i, strID);
            pLstCtrl.SetItemText(index, 1, pUser->szName);
            pLstCtrl.SetItemText(index, 2, pUser->szEmail);
            CString strJobID;
            strJobID.Format(_T("%ld"), pUser->lJobTitleID);
            pLstCtrl.SetItemText(index, 3, strJobID);
        }
    }
}

// Overrides
// ----------------
BOOL CCSoftInternshipProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;
    return CListView::PreCreateWindow(cs);
}

void CCSoftInternshipProjectView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
    GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);
    PopulateUsersList();
}

void CCSoftInternshipProjectView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    CListView::OnUpdate(pSender, lHint, pHint);
    PopulateUsersList();
}

#ifdef _DEBUG
void CCSoftInternshipProjectView::AssertValid() const
{
	CListView::AssertValid();
}

void CCSoftInternshipProjectView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif 