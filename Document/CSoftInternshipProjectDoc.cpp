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


// Overrides
// ----------------
CUsersAppService& CCSoftInternshipProjectDocument::GetService() {
	return this->m_oAppService;
}

BOOL CCSoftInternshipProjectDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}