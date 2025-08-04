#pragma once
#include "DLLExport.h"
#include <Users.h>
#include <JobTitles.h>



/////////////////////////////////////////////////////////////////////////////
// CCSoftInternshipProjectDocument
class DocumentDLL_EXP CUsersDocument : public CDocument
{
	// Macros
	// ----------------
	DECLARE_DYNCREATE(CUsersDocument)

	// Constructor / Destructor
	// ----------------
public:
	/// <summary>
	/// Constructor
	/// </summary>
	CUsersDocument() noexcept;
	/// <summary>
	/// Desctructor
	/// </summary>
	virtual ~CUsersDocument();

	// Methods
	// ----------------



	/// <summary>
	/// ������ ��� ���������� ��� ������
	/// </summary>
	/// <param name="recNewUser">������� ���������� �� ����������.
	/// ���� ���������� �� ��� ������, ���������� ��� ����������
	/// ���� �� ���� ��������� � �� �������</param>
	/// <returns>True ��� ���������� �� �������, 
	/// False ��� �� ������ ������� ��� ����������</returns>
	bool AddNewUser(USERS& recNewUser);

	/// <summary>
	/// ��������� ���������� �� ������
	/// </summary>
	/// <param name="lID">ID-�� �� ����������� ����� ������ �� ��������</param>
	/// <param name="recUpdatedUser">������ �����, ��� ������� �� ����������� USERS, ����� �� ����� �������������</param>
	/// <returns>True ��� ���������� �� �������, 
	/// False ��� �� ������ ������� ��� ����������</returns>
	bool EditUser(const long lID,USERS& recUpdatedUser);

	/// <summary>
	/// ������� ���������� �� ������
	/// </summary>
	/// <param name="lID">ID-�� �� ����������� ����� ������ �� �� ������</param>
	/// <returns>True ��� ���������� �� �������, 
	/// False ��� �� ������ ������� ��� ����������</returns>
	bool DeleteUser(const long lID);

	/// <summary>
	/// ����� ������� �� ������ 
	/// </summary>
	/// <param name="lID">ID-�� �� ��������� ����� ������</param>
	/// <param name="recJobTitle">��������� JOB_TITLES, ����� �� ������ ��������� ��������</param>
	/// <returns>True ��� ���������� �� �������, 
	/// False ��� �� ������ ������� ��� ����������</returns>
	bool GetJobTitle(const long lID, JOB_TITLES& recJobTitle);
	
	/// <summary>
	/// ����� �� typedef �� CUsersArray
	/// </summary>
	/// <returns>���������� ��� ������ m_oUsersArray </returns>
	CUsersArray& GetUsersArray() { return this->m_oUsersArray; };

private:

	/// <summary>
	/// ����������� ������� �� ������ �������� ��������� �� �����������
	/// </summary>
	void FreeUsersMemory();

	/// <summary>
	/// ������� ������ ����������� �� ������, ��� ������� �� �� ������ ��������� �� ������
	/// </summary>
	void LoadUsers();
	// Overrides
	// ----------------
public:
	BOOL OnNewDocument() override;
	virtual void OnCloseDocument();
	// Members
	// ----------------
private:
	CUsersArray m_oUsersArray;
};
