#include "pch.h"
#include "CSoftInternshipProjectDoc.h"

/////////////////////////////////////////////////////////////////////////////
//CCSoftInternshipProjectDocument

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CCSoftInternshipProjectDocument, CDocument)

// Constructor / Destructor
// ----------------
CCSoftInternshipProjectDocument::CCSoftInternshipProjectDocument() noexcept
{
}

CCSoftInternshipProjectDocument::~CCSoftInternshipProjectDocument()
{
}

// Methods
// ----------------
void CCSoftInternshipProjectDocument::FreeUsersMemory() {
	for (INT_PTR i = 0; i < m_oUsersArray.GetCount(); ++i) {
		delete m_oUsersArray.GetAt(i);
	}
	m_oUsersArray.RemoveAll();
}

// Overrides
// ----------------
CUsersAppService& CCSoftInternshipProjectDocument::GetService() {
	return this->m_oAppService;
}

void CCSoftInternshipProjectDocument::LoadUsers()
{
    FreeUsersMemory();
    if (m_oAppService.GetAllUsers(m_oUsersArray)) {
        UpdateAllViews(NULL);
    }
    else {
        AfxMessageBox(_T("Failed to load users."));
    }
}

BOOL CCSoftInternshipProjectDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	LoadUsers();
	return TRUE;
}

void CCSoftInternshipProjectDocument::OnCloseDocument() 
{
	CDocument::OnCloseDocument();
}