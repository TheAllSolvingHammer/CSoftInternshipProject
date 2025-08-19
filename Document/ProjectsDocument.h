#pragma once
#include "DLLExport.h"
#include <Projects.h>
#include <Users.h>
#include "Tasks.h"

#define MSG_ERR_LOAD_USERS _T("Failed to load users.")

/// <summary>
/// Енумерация на командата подадена за работа
/// </summary>
enum UpdateHint
{
    HINT_NONE = 0,
    HINT_PROJECT_ADDED,
    HINT_PROJECT_UPDATED,
    HINT_PROJECT_DELETED,
    HINT_TASK_ADDED,
    HINT_TASK_UPDATED,
    HINT_TASK_DELETED
};

/// <summary>
/// Документ клас на проектите
/// </summary>
class DocumentDLL_EXP CProjectsDocument : public CDocument
{
protected:
    DECLARE_DYNCREATE(CProjectsDocument)

public:
    /// <summary>
    /// Конструктор на документа
    /// </summary>
    CProjectsDocument();

    /// <summary>
    /// Деструктор на документа
    /// </summary>
    virtual ~CProjectsDocument();

    /// <summary>
    /// Добавя проект към базата
    /// </summary>
    /// <param name="recProject">проекта който ще се добави</param>
    /// <returns>Истина при успех, Неистина при неуспех</returns>
    bool AddProject(PROJECTS& recProject);

    /// <summary>
    /// Актуализира проект на подадени параметри
    /// </summary>
    /// <param name="recProject">Проекта който ще се актуализира</param>
    /// <param name="oTasksArray">Масив от задачите</param>
    /// <param name="oUpdatedTasksArray">Масив от актуализираните задачи</param>
    /// <param name="oDeletedTasksArray">Масив от изтритие задачи</param>
    /// <returns>Истина при успех, Неистина при неуспех</returns>
    bool UpdateProject(PROJECTS& recProject, CTasksArray& oTasksArray, CTasksArray& oUpdatedTasksArray, CTasksArray& oDeletedTasksArray);
    
    /// <summary>
    /// Изтрива проект от базата
    /// </summary>
    /// <param name="lID">Идентификатор на проекта</param>
    /// <returns>Истина при успех, Неистина при неуспех</returns>
    bool DeleteProject(const long lID);

    /// <summary>
    /// Гетър на потребител
    /// </summary>
    /// <param name="lID">Идентификатор на потребител</param>
    /// <param name="recUser">Структурата която ще попълни намерения потребител</param>
    /// <returns>Истина при успех, Неистина при неуспех</returns>
    bool GetUser(const long lID, USERS& recUser);

    /// <summary>
    /// Гетър на всички потребители
    /// </summary>
    /// <param name="oUsersArray">Масив който ще се запълни</param>
    /// <returns>Истина при успех, Неистина при неуспех</returns>
    bool GetAllUsers(CUsersArray& oUsersArray);

    /// <summary>
    /// Гетър на задачи при подаден идентификатор на проект
    /// </summary>
    /// <param name="lID">Идентификато на проекта</param>
    /// <param name="oTasksArray">Масив от задачи, който ще се попълни</param>
    /// <returns>Истина при успех, Неистина при неуспех</returns>
    bool GetTasksByProject(const long lID, CTasksArray& oTasksArray);
    /// <summary>
    /// Гетър на проекти
    /// </summary>
    /// <returns>Връща масив от всички проекти</returns>
    CProjectsArray& GetProjectsArray();
public:
    virtual BOOL OnNewDocument() override;
    virtual void OnCloseDocument();
private:
    /// <summary>
    /// Зарежда информацията на всички проекти
    /// </summary>
    void LoadProjects();

    /// <summary>
    /// Зарежда само 1 проект
    /// </summary>
    /// <param name="recProject">Идентификатор на проекта, който ще се зареди</param>
    void LoadSingleProject(PROJECTS& recProject);

    /// <summary>
    /// Изтрива 1 проект
    /// </summary>
    /// <param name="lID">Идентификатор на проекта, който ще се изтрие</param>
    void DeleteSingleProject(const long lID);
private:
    CProjectsArray m_oProjectsArray;
    
};