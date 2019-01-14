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

void Mycp(char *fsource, char *ftarget);        //将源目录信息复制到目标目录下
void CopyFile(char *fsource, char *ftarget);   //
BOOL GetDirectoryTime(char *DirectoryName, FILETIME *lpCreationTime, FILETIME *lpLastAccessTime, FILETIME *lpLastWriteTime);  //得到时间信息
BOOL SetDirectoryTime(char *DirectoryName, FILETIME lpCreationTime, FILETIME lpLastAccessTime, FILETIME lpLastWriteTime);  //设置时间信息
int CreateFileD(char *source, char *target);   //为目标文件创建目录并保持和源文件相同的属性

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
	DWORD dwFileAttributes;      //文件属性
	FILETIME ftCreationTime;    // 文件创建时间
	FILETIME ftLastAccessTime; // 文件最后一次访问时间
	FILETIME ftLastWriteTime; // 文件最后一次修改时间
	DWORD nFileSizeHigh;     // 文件长度高32位
	DWORD nFileSizeLow;     // 文件长度低32位
	DWORD dwReserved0;     // 系统保留
	DWORD dwReserved1;    // 系统保留
	TCHAR cFileName[ MAX_PATH ]; // 长文件名
	TCHAR cAlternateFileName[ 14 ]; // 8.3格式文件名
	} WIN32_FIND_DATA, *PWIN32_FIND_DATA;
	*/


	/*查找指定文件路径的文件
	FindFirstFile
	HANDLE FindFirstFile(
	LPCTSTRlpFileName,                //filename
	LPWIN32_FIND_DATAlpFindFileData  //databuffer
	);
	调用成功返回一个句柄；
	调用失败 返回为INVALID_HANDLE_VALUE
	*/

	if (FindFirstFile(Ch2LRC(dst), &lpfindfiledata) == INVALID_HANDLE_VALUE)
	{
		//argv[2]目标文件
		CreateFileD(src, dst);
	}
	Mycp(src, dst);      //复制

}

int CreateFileD(char *source, char *target)
{
	FILETIME lpCreationTime;          //创建时间
	FILETIME lpLastAccessTime;           //最近一次访问时间
	FILETIME lpLastWriteTime;           //最近一次修改时间
										//创建目录
										/*
										BOOL CreateDirectory(
										LPCTSTR lpPathName,                           //新创建目录的路径名
										LPSECURITY_ATTRIBUTES lpSecurityAttributes   //安全属性
										);
										*/
	int appendix = CreateDirectory(Ch2LRC(target), NULL);
	GetDirectoryTime(source, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	SetDirectoryTime(target, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
	return appendix;
}

BOOL GetDirectoryTime(char *DirectoryName, FILETIME *lpCreationTime, FILETIME *lpLastAccessTime, FILETIME *lpLastWriteTime)
{
	//获取文件夹时间属性信息
	HANDLE hDirectory = CreateFile(Ch2LRC(DirectoryName), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	/*CreateFile，可打开或创建以下对象，并返回可访问的句柄
	HANDLE WINAPI CreateFile(
	_In_ LPCTSTR lpFileName,
	_In_ DWORD dwDesiredAccess,      访问方式
	_In_ DWORD dwShareMode,          共享
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,  安全属性
	_In_ DWORD dwCreationDisposition,       OPEN_EXISTING 文件必须已经存在
	_In_ DWORD dwFlagsAndAttributes,  指示系统为文件的打开或创建执行一个备份或恢复操作. 系统保证调用进程忽略文件的安全选项
	_In_opt_ HANDLE hTemplateFile
	);
	*/
	BOOL retval = GetFileTime(hDirectory, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
	CloseHandle(hDirectory);      //关闭文件夹
	return retval;
}

BOOL SetDirectoryTime(char *DirectoryName, FILETIME lpCreationTime, FILETIME lpLastAccessTime, FILETIME lpLastWriteTime)
{
	//设置文件夹时间属性
	HANDLE hDirectory = CreateFile(Ch2LRC(DirectoryName), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	BOOL retval = SetFileTime(hDirectory, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	CloseHandle(hDirectory);
	return retval;
}

void CopyFile(char *fsource, char *ftarget)
{
	WIN32_FIND_DATA lpfindfiledata;
	HANDLE hfind = FindFirstFile(Ch2LRC(fsource), &lpfindfiledata);   //查找指定文件路径
	HANDLE hsource = CreateFile(Ch2LRC(fsource), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,/* 文件若存在则打开*/FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE htarget = CreateFile(Ch2LRC(fsource), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,/*创建一个文件*/ FILE_ATTRIBUTE_NORMAL/* 不设置属性*/, NULL);
	LONG size = lpfindfiledata.nFileSizeLow - lpfindfiledata.nFileSizeHigh;  //length
	DWORD wordbit;
	int *BUFFER = new int[size];  //新开缓冲区,保存数据
	ReadFile(hsource, BUFFER, size, &wordbit, NULL);  //源文件读数据
													  /*
													  BOOL ReadFile(
													  HANDLE hFile,                   //文件的句柄
													  LPVOID lpBuffer,               //保存读入数据的一个缓冲区
													  DWORD nNumberOfBytesToRead,   //读入的字节数
													  LPDWORD lpNumberOfBytesRead, //指向实际读取字节数的指针
													  LPOVERLAPPED lpOverlapped   //如文件打开时指定了FILE_FLAG_OVERLAPPED，那么必须，用这个参数引用一个特殊的结构。
													  //该结构定义了一次异步读取操作。否则，应将这个参数设为NULL
													  );
													  */
													  /*
													  WriteFile 函数原型与CreateFile相同
													  */
	WriteFile(htarget, BUFFER, size, &wordbit, NULL); //目标文件写数据
													  //修改文件时间信息
													  /*SetFileTime
													  参数 类型及说明
													  hFile Long，系统文件句柄
													  lpCreationTime FILETIME，文件的创建时间
													  lpLastAccessTime FILETIME，文件上一次访问的时间
													  lpLastWriteTime FILETIME，文件最近一次修改的时间
													  */
													  //GetFileTime(hsource,&lpfindfiledata.ftCreationTime,&lpfindfiledata.ftLastAccessTime,&lpfindfiledata.ftLastWriteTime);
													  //SetFileTime(htarget,&lpfindfiledata.ftCreationTime,&lpfindfiledata.ftLastAccessTime,&lpfindfiledata.ftLastWriteTime);
	CloseHandle(hfind);  //关闭句柄
	CloseHandle(hsource);
	CloseHandle(htarget);
}

void Mycp(char *fsource, char *ftarget)       //将源目录信息复制到目标目录下
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
		while (FindNextFile(hfind, &lpfindfiledata) != 0)  //查找下一个文件成功
														   /*FindNextFile根据指定的一个文件名查找下一个文件
														   BOOLFindNextFile(
														   HANDLE hFindFile,                  //searchhandle
														   LPWIN32_FIND_DATA lpFindFileData  //databuffer
														   );
														   */
		{
			if (lpfindfiledata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  //判断目录
			{
				if ((strcmp((char const*)lpfindfiledata.cFileName, ".") != 0) && (strcmp((char const*)lpfindfiledata.cFileName, "..") != 0))
				{
					memset(source, '0', sizeof(source));
					strcpy(source, fsource);
					strcat(source, "\\");
					strcat(source, (char const*)lpfindfiledata.cFileName);   //追加文件名
					strcat(target, (char const*)lpfindfiledata.cFileName);
					CreateFileD(source, target);
					Mycp(source, target);   //进入子目录复制
					strcpy(source, fsource);
					strcat(source, "\\");
					strcpy(target, ftarget);
					strcat(target, "\\");
				}
			}
			else    //无目录
			{
				//直接复制
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

