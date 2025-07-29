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
	const CUsersArray& GetUsers() const { return m_oUsersArray; }
	void FreeUsersMemory();
	CUsersAppService& GetService();
	void LoadUsers();
	bool AddUser(USERS& newUser);
	bool EditUser(USERS& updatedUser);
	bool DeleteUser(long lID);
	// Overrides
	// ----------------
public:
	BOOL OnNewDocument() override;
	virtual void OnCloseDocument();
	// Members
	// ----------------
public:
	CUsersAppService m_oAppService;
	CUsersArray m_oUsersArray;
};
