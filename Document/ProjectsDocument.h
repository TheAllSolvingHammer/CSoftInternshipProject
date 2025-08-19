#pragma once
#include "DLLExport.h"
#include <Projects.h>
#include <Users.h>
#include "Tasks.h"

#define MSG_ERR_LOAD_USERS _T("Failed to load users.")

/// <summary>
/// ���������� �� ��������� �������� �� ������
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
/// �������� ���� �� ���������
/// </summary>
class DocumentDLL_EXP CProjectsDocument : public CDocument
{
protected:
    DECLARE_DYNCREATE(CProjectsDocument)

public:
    /// <summary>
    /// ����������� �� ���������
    /// </summary>
    CProjectsDocument();

    /// <summary>
    /// ���������� �� ���������
    /// </summary>
    virtual ~CProjectsDocument();

    /// <summary>
    /// ������ ������ ��� ������
    /// </summary>
    /// <param name="recProject">������� ����� �� �� ������</param>
    /// <returns>������ ��� �����, �������� ��� �������</returns>
    bool AddProject(PROJECTS& recProject);

    /// <summary>
    /// ����������� ������ �� �������� ���������
    /// </summary>
    /// <param name="recProject">������� ����� �� �� �����������</param>
    /// <param name="oTasksArray">����� �� ��������</param>
    /// <param name="oUpdatedTasksArray">����� �� ��������������� ������</param>
    /// <param name="oDeletedTasksArray">����� �� �������� ������</param>
    /// <returns>������ ��� �����, �������� ��� �������</returns>
    bool UpdateProject(PROJECTS& recProject, CTasksArray& oTasksArray, CTasksArray& oUpdatedTasksArray, CTasksArray& oDeletedTasksArray);
    
    /// <summary>
    /// ������� ������ �� ������
    /// </summary>
    /// <param name="lID">������������� �� �������</param>
    /// <returns>������ ��� �����, �������� ��� �������</returns>
    bool DeleteProject(const long lID);

    /// <summary>
    /// ����� �� ����������
    /// </summary>
    /// <param name="lID">������������� �� ����������</param>
    /// <param name="recUser">����������� ����� �� ������� ��������� ����������</param>
    /// <returns>������ ��� �����, �������� ��� �������</returns>
    bool GetUser(const long lID, USERS& recUser);

    /// <summary>
    /// ����� �� ������ �����������
    /// </summary>
    /// <param name="oUsersArray">����� ����� �� �� �������</param>
    /// <returns>������ ��� �����, �������� ��� �������</returns>
    bool GetAllUsers(CUsersArray& oUsersArray);

    /// <summary>
    /// ����� �� ������ ��� ������� ������������� �� ������
    /// </summary>
    /// <param name="lID">������������ �� �������</param>
    /// <param name="oTasksArray">����� �� ������, ����� �� �� �������</param>
    /// <returns>������ ��� �����, �������� ��� �������</returns>
    bool GetTasksByProject(const long lID, CTasksArray& oTasksArray);
    /// <summary>
    /// ����� �� �������
    /// </summary>
    /// <returns>����� ����� �� ������ �������</returns>
    CProjectsArray& GetProjectsArray();
public:
    virtual BOOL OnNewDocument() override;
    virtual void OnCloseDocument();
private:
    /// <summary>
    /// ������� ������������ �� ������ �������
    /// </summary>
    void LoadProjects();

    /// <summary>
    /// ������� ���� 1 ������
    /// </summary>
    /// <param name="recProject">������������� �� �������, ����� �� �� ������</param>
    void LoadSingleProject(PROJECTS& recProject);

    /// <summary>
    /// ������� 1 ������
    /// </summary>
    /// <param name="lID">������������� �� �������, ����� �� �� ������</param>
    void DeleteSingleProject(const long lID);
private:
    CProjectsArray m_oProjectsArray;
    
};