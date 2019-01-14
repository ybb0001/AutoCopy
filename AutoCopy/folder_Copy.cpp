//windows copyfile
/*API
CreateFile(), ReadFile(), WriteFile(), CloseHandle()..so on
*/
#include "afxstr.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<windowsx.h>
#include<string.h>

void Mycp(char *fsource, char *ftarget);        //��ԴĿ¼��Ϣ���Ƶ�Ŀ��Ŀ¼��
void CopyFile(char *fsource, char *ftarget);   //
BOOL GetDirectoryTime(char *DirectoryName, FILETIME *lpCreationTime, FILETIME *lpLastAccessTime, FILETIME *lpLastWriteTime);  //�õ�ʱ����Ϣ
BOOL SetDirectoryTime(char *DirectoryName, FILETIME lpCreationTime, FILETIME lpLastAccessTime, FILETIME lpLastWriteTime);  //����ʱ����Ϣ
int CreateFileD(char *source, char *target);   //ΪĿ���ļ�����Ŀ¼�����ֺ�Դ�ļ���ͬ������

LPCWSTR Ch2LRC(char* szStr){

	CString str = CString(szStr);
	USES_CONVERSION;
	LPCWSTR lpc = A2CW(W2A(str));
	str.ReleaseBuffer();
	return lpc;
}


extern void main(char *src, char *dst)
{
	WIN32_FIND_DATA lpfindfiledata;
	/*
	typedef struct _WIN32_FIND_DATA {
	DWORD dwFileAttributes;      //�ļ�����
	FILETIME ftCreationTime;    // �ļ�����ʱ��
	FILETIME ftLastAccessTime; // �ļ����һ�η���ʱ��
	FILETIME ftLastWriteTime; // �ļ����һ���޸�ʱ��
	DWORD nFileSizeHigh;     // �ļ����ȸ�32λ
	DWORD nFileSizeLow;     // �ļ����ȵ�32λ
	DWORD dwReserved0;     // ϵͳ����
	DWORD dwReserved1;    // ϵͳ����
	TCHAR cFileName[ MAX_PATH ]; // ���ļ���
	TCHAR cAlternateFileName[ 14 ]; // 8.3��ʽ�ļ���
	} WIN32_FIND_DATA, *PWIN32_FIND_DATA;
	*/


	/*����ָ���ļ�·�����ļ�
	FindFirstFile
	HANDLE FindFirstFile(
	LPCTSTRlpFileName,                //filename
	LPWIN32_FIND_DATAlpFindFileData  //databuffer
	);
	���óɹ�����һ�������
	����ʧ�� ����ΪINVALID_HANDLE_VALUE
	*/

	if (FindFirstFile(Ch2LRC(dst), &lpfindfiledata) == INVALID_HANDLE_VALUE)
	{
		//argv[2]Ŀ���ļ�
		CreateFileD(src, dst);
	}
	Mycp(src, dst);      //����

}

int CreateFileD(char *source, char *target)
{
	FILETIME lpCreationTime;          //����ʱ��
	FILETIME lpLastAccessTime;           //���һ�η���ʱ��
	FILETIME lpLastWriteTime;           //���һ���޸�ʱ��
										//����Ŀ¼
										/*
										BOOL CreateDirectory(
										LPCTSTR lpPathName,                           //�´���Ŀ¼��·����
										LPSECURITY_ATTRIBUTES lpSecurityAttributes   //��ȫ����
										);
										*/
	int appendix = CreateDirectory(Ch2LRC(target), NULL);
	GetDirectoryTime(source, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	SetDirectoryTime(target, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
	return appendix;
}

BOOL GetDirectoryTime(char *DirectoryName, FILETIME *lpCreationTime, FILETIME *lpLastAccessTime, FILETIME *lpLastWriteTime)
{
	//��ȡ�ļ���ʱ��������Ϣ
	HANDLE hDirectory = CreateFile(Ch2LRC(DirectoryName), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	/*CreateFile���ɴ򿪻򴴽����¶��󣬲����ؿɷ��ʵľ��
	HANDLE WINAPI CreateFile(
	_In_ LPCTSTR lpFileName,
	_In_ DWORD dwDesiredAccess,      ���ʷ�ʽ
	_In_ DWORD dwShareMode,          ����
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,  ��ȫ����
	_In_ DWORD dwCreationDisposition,       OPEN_EXISTING �ļ������Ѿ�����
	_In_ DWORD dwFlagsAndAttributes,  ָʾϵͳΪ�ļ��Ĵ򿪻򴴽�ִ��һ�����ݻ�ָ�����. ϵͳ��֤���ý��̺����ļ��İ�ȫѡ��
	_In_opt_ HANDLE hTemplateFile
	);
	*/
	BOOL retval = GetFileTime(hDirectory, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
	CloseHandle(hDirectory);      //�ر��ļ���
	return retval;
}

BOOL SetDirectoryTime(char *DirectoryName, FILETIME lpCreationTime, FILETIME lpLastAccessTime, FILETIME lpLastWriteTime)
{
	//�����ļ���ʱ������
	HANDLE hDirectory = CreateFile(Ch2LRC(DirectoryName), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	BOOL retval = SetFileTime(hDirectory, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	CloseHandle(hDirectory);
	return retval;
}

void CopyFile(char *fsource, char *ftarget)
{
	WIN32_FIND_DATA lpfindfiledata;
	HANDLE hfind = FindFirstFile(Ch2LRC(fsource), &lpfindfiledata);   //����ָ���ļ�·��
	HANDLE hsource = CreateFile(Ch2LRC(fsource), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,/* �ļ����������*/FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE htarget = CreateFile(Ch2LRC(fsource), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,/*����һ���ļ�*/ FILE_ATTRIBUTE_NORMAL/* ����������*/, NULL);
	LONG size = lpfindfiledata.nFileSizeLow - lpfindfiledata.nFileSizeHigh;  //length
	DWORD wordbit;
	int *BUFFER = new int[size];  //�¿�������,��������
	ReadFile(hsource, BUFFER, size, &wordbit, NULL);  //Դ�ļ�������
													  /*
													  BOOL ReadFile(
													  HANDLE hFile,                   //�ļ��ľ��
													  LPVOID lpBuffer,               //����������ݵ�һ��������
													  DWORD nNumberOfBytesToRead,   //������ֽ���
													  LPDWORD lpNumberOfBytesRead, //ָ��ʵ�ʶ�ȡ�ֽ�����ָ��
													  LPOVERLAPPED lpOverlapped   //���ļ���ʱָ����FILE_FLAG_OVERLAPPED����ô���룬�������������һ������Ľṹ��
													  //�ýṹ������һ���첽��ȡ����������Ӧ�����������ΪNULL
													  );
													  */
													  /*
													  WriteFile ����ԭ����CreateFile��ͬ
													  */
	WriteFile(htarget, BUFFER, size, &wordbit, NULL); //Ŀ���ļ�д����
													  //�޸��ļ�ʱ����Ϣ
													  /*SetFileTime
													  ���� ���ͼ�˵��
													  hFile Long��ϵͳ�ļ����
													  lpCreationTime FILETIME���ļ��Ĵ���ʱ��
													  lpLastAccessTime FILETIME���ļ���һ�η��ʵ�ʱ��
													  lpLastWriteTime FILETIME���ļ����һ���޸ĵ�ʱ��
													  */
													  //GetFileTime(hsource,&lpfindfiledata.ftCreationTime,&lpfindfiledata.ftLastAccessTime,&lpfindfiledata.ftLastWriteTime);
													  //SetFileTime(htarget,&lpfindfiledata.ftCreationTime,&lpfindfiledata.ftLastAccessTime,&lpfindfiledata.ftLastWriteTime);
	CloseHandle(hfind);  //�رվ��
	CloseHandle(hsource);
	CloseHandle(htarget);
}

void Mycp(char *fsource, char *ftarget)       //��ԴĿ¼��Ϣ���Ƶ�Ŀ��Ŀ¼��
{
	WIN32_FIND_DATA lpfindfiledata;
	char source[512];
	char target[512];
	strcpy(source, fsource);    //copy  source->fsource
	strcpy(target, ftarget);
	strcat(source, "\\*.*");
	strcat(target, "\\");
	HANDLE hfind = FindFirstFile(Ch2LRC(source), &lpfindfiledata);
	if (hfind != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile(hfind, &lpfindfiledata) != 0)  //������һ���ļ��ɹ�
														   /*FindNextFile����ָ����һ���ļ���������һ���ļ�
														   BOOLFindNextFile(
														   HANDLE hFindFile,                  //searchhandle
														   LPWIN32_FIND_DATA lpFindFileData  //databuffer
														   );
														   */
		{
			if (lpfindfiledata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  //�ж�Ŀ¼
			{
				if ((strcmp((char const*)lpfindfiledata.cFileName, ".") != 0) && (strcmp((char const*)lpfindfiledata.cFileName, "..") != 0))
				{
					memset(source, '0', sizeof(source));
					strcpy(source, fsource);
					strcat(source, "\\");
					strcat(source, (char const*)lpfindfiledata.cFileName);   //׷���ļ���
					strcat(target, (char const*)lpfindfiledata.cFileName);
					CreateFileD(source, target);
					Mycp(source, target);   //������Ŀ¼����
					strcpy(source, fsource);
					strcat(source, "\\");
					strcpy(target, ftarget);
					strcat(target, "\\");
				}
			}
			else    //��Ŀ¼
			{
				//ֱ�Ӹ���
				memset(source, '0', sizeof(source));
				strcpy(source, fsource);
				strcat(source, "\\");
				strcat(source, (char const*)lpfindfiledata.cFileName);
				strcat(target, (char const*)lpfindfiledata.cFileName);
				CopyFile(source, target);
				strcpy(source, fsource);
				strcat(source, "\\");
				strcpy(target, ftarget);
				strcat(target, "\\");
			}
		}
	}
}

