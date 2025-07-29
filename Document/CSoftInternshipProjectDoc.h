#pragma once
#include "DLLExport.h"
#include "..\Application\UsersAppService.h"



/////////////////////////////////////////////////////////////////////////////
// CCSoftInternshipProjectDocument
class DocumentDLL_EXP CCSoftInternshipProjectDocument : public CDocument
{
	// Macros
	// ----------------
	DECLARE_DYNCREATE(CCSoftInternshipProjectDocument)

	// Constructor / Destructor
	// ----------------
public:
	CCSoftInternshipProjectDocument() noexcept;
	virtual ~CCSoftInternshipProjectDocument();

	// Methods
	// ----------------


	// Overrides
	// ----------------
public:
	BOOL OnNewDocument() override;
	virtual void OnCloseDocument();
	void LoadUsers();
	const CUsersArray& GetUsers() const { return m_oUsersArray; }
	void FreeUsersMemory();
	// Members
	// ----------------
	CUsersAppService& GetService();
public:
	CUsersAppService m_oAppService;
	CUsersArray m_oUsersArray;
};
