#pragma once
#include "DLLExport.h"
#include "..\Application\UsersAppService.h"
#include <..\Application\JobTitleAppService.h>



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
	bool AddNewUser(USERS& recNewUser);
	bool EditUser(long lID,USERS& recUpdatedUser);
	bool DeleteUser(long lID);
	void GetJobTitle(long lID, JOB_TITLES& recJobTitle);
	// Overrides
	// ----------------
public:
	BOOL OnNewDocument() override;
	virtual void OnCloseDocument();
	// Members
	// ----------------
public:
	CUsersAppService m_oUserAppService;
	CJobTitlesAppService m_oJobTitlesAppService;
	CUsersArray m_oUsersArray;
};
