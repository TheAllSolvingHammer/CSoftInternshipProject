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
	/// Добавя нов потребител към базата
	/// </summary>
	/// <param name="recNewUser">Подаден потребител по референция.
	/// След добавянето му към базата, подаденият нов потребител
	/// може да бъде използван и от клиента</param>
	/// <returns>True ако операциите са успешни, 
	/// False ако се срещне проблем при вмъкването</returns>
	bool AddNewUser(USERS& recNewUser);

	/// <summary>
	/// Редактира потребител от базата
	/// </summary>
	/// <param name="lID">ID-то на потребителя който желаем да променим</param>
	/// <param name="recUpdatedUser">Новите данни, под формата на структурата USERS, които ще бъдат актуализирани</param>
	/// <returns>True ако операциите са успешни, 
	/// False ако се срещне проблем при вмъкването</returns>
	bool EditUser(const long lID,USERS& recUpdatedUser);

	/// <summary>
	/// Изтрива потребител от базата
	/// </summary>
	/// <param name="lID">ID-то на потребителя който трябва да се изтрие</param>
	/// <returns>True ако операциите са успешни, 
	/// False ако се срещне проблем при вмъкването</returns>
	bool DeleteUser(const long lID);

	/// <summary>
	/// Търси позиция от базата 
	/// </summary>
	/// <param name="lID">ID-то на позицията която търсим</param>
	/// <param name="recJobTitle">Структура JOB_TITLES, която ще приеме намерения резултат</param>
	/// <returns>True ако операциите са успешни, 
	/// False ако се срещне проблем при вмъкването</returns>
	bool GetJobTitle(const long lID, JOB_TITLES& recJobTitle);
	
	/// <summary>
	/// Гетър за typedef на CUsersArray
	/// </summary>
	/// <returns>Референция към полето m_oUsersArray </returns>
	CUsersArray& GetUsersArray() { return this->m_oUsersArray; };

private:

	/// <summary>
	/// Освобождава паметта от всички запазени указатели за потребители
	/// </summary>
	void FreeUsersMemory();

	/// <summary>
	/// Зарежда всички потребители от базата, при неуспех ще се изведе съобщение за грешка
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
