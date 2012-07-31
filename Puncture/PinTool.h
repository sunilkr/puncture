#include <iostream>
#include <fstream>
#include <sstream>
#include <pin.H>
namespace WINDOWS
{
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinNt.h>
#include <WinError.h>
#include <Winsock2.h>
}

#define MAX_THREAD 20

#define DELIM '|'
#define REG_QVALUE 0x1
#define REG_SETVAL 0x2
#define REG_DELKEY 0x3

#define CREATE_FILE 0x4
#define DELETE_FILE 0x5
#define SETFILE_PTR 0x6
#define WRITE_FILE	0x7
#define READ_FILE	0x8


void Image(IMG img, void *v);
void Fini(INT32 code, void *v);
const char* StripPath(const char* path);

//RegistryAPI Hooks -> ADVAPI32.DLL, Defs in RegistryAPI.cpp
void Image_ADVAPI32(IMG img, void *v);

WINDOWS::LONG jwRegOpenKeyEx(const char Code, CONTEXT *ctxt, AFUNPTR fpOrigin,  //Additional Analysis Arguments
	WINDOWS::HKEY hKey,		//Original Arguments 
	UINT32 lpSubKey,		// Will be typecasted based on Code in analysis routine
	WINDOWS::DWORD ulOptions, 
	WINDOWS::REGSAM samDesired, WINDOWS::PHKEY phkResult);
WINDOWS::LONG jwRegCreateKeyEx(const char Code, CONTEXT *ctxt, AFUNPTR fpOrigin, 
	WINDOWS::HKEY hKey, UINT32 lpSubKey, WINDOWS::DWORD dwReserved,
	UINT32 lpClass, WINDOWS::DWORD dwOptions, WINDOWS::REGSAM samDesired,
	WINDOWS::LPSECURITY_ATTRIBUTES lpSecurityAttributes, WINDOWS::PHKEY phkResult,
	WINDOWS::LPDWORD lpdwDisposition);
void b4RegQueryValueEx(const char Code, WINDOWS::HKEY hKey, UINT32 lpValueName);
void b4RegSetValueEx(const char Code, WINDOWS::HKEY, UINT32 lpValueName, 
	WINDOWS::DWORD dwType, const WINDOWS::BYTE *lpData, WINDOWS::DWORD cbData);
void b4RegDeleteKeyEx(const char Code, WINDOWS::HKEY, UINT32 lpSubKey);
void OnRegReturn(int funcCode, const char Code, WINDOWS::LONG lResult);

//FileAPI Hooks -> kernel32.dll, Defs in FileAPI.cpp
void Image_Kernel32(IMG img, void *v);

void b4CreateFile(const char Code, UINT32 lpFileName, WINDOWS::DWORD dwDesiredAccess,
				  WINDOWS::DWORD dwShareMode, WINDOWS::LPSECURITY_ATTRIBUTES lpSecurityAttributes,
				  WINDOWS::DWORD dwCreationDisposition, WINDOWS::DWORD dwFlagsAndAttributes);

void b4DeleteFile(const char Code, UINT32 lpFileName);

void b4SetFilePointer(const WINDOWS::BOOL isEx, WINDOWS::HANDLE hFile, 
					  WINDOWS::LONG lDistanceToMove, WINDOWS::DWORD dwMoveMethod);

/* Replacement Sugnatures. Required to capture by-ref paramaters'/data.

WINDOWS::BOOL jwReadFile(CONTEXT *ctxt, AFUNPTR fpOrigin,
	WINDOWS::HANDLE hFile, WINDOWS::LPVOID lpBuffer, WINDOWS::DWORD nNumberOfBytesToRead,
	WINDOWS::LPDWORD lpNumberOfBytesRead, WINDOWS::LPOVERLAPPED lpOverlapped);
WINDOWS::BOOL jwReadFileEx(CONTEXT *ctxt, AFUNPTR fpOrigin,
	WINDOWS::HANDLE hFile, WINDOWS::LPVOID lpBuffer, WINDOWS::DWORD nNumberOfBytesToRead,
	WINDOWS::LPOVERLAPPED lpOverlapped, WINDOWS::LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
WINDOWS::BOOL jwWriteFile(CONTEXT *ctxt, AFUNPTR fpOrigin,
	WINDOWS::HANDLE hFile, WINDOWS::LPCVOID lpBuffer, WINDOWS::DWORD nNumberOfBytesToWrite,
	WINDOWS::LPDWORD lpNumberOfBytessWritten, WINDOWS::LPOVERLAPPED lpOverlapped);
WINDOWS::BOOL jwWriteFileEx(CONTEXT *ctxt, AFUNPTR fpOrigin,
	WINDOWS::HANDLE hFile, WINDOWS::LPCVOID lpBuffer, WINDOWS::DWORD nNumberOfBytesToWrite,
	WINDOWS::LPOVERLAPPED lpOverlapped, WINDOWS::LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
*/

WINDOWS::HANDLE jwCreateFileW(CONTEXT *ctxt, AFUNPTR fpOrigin,
							  WINDOWS::LPWSTR lpFileName, WINDOWS::DWORD dwDesiredAccess,
							  WINDOWS::DWORD dwShareMode, WINDOWS::LPSECURITY_ATTRIBUTES lpSecurityAttributes,
							  WINDOWS::DWORD dwCreationDisposition, WINDOWS::DWORD dwFlagsAndAttributes, 
							  WINDOWS::HANDLE hTemplateFile);

void b4ReadFile(const WINDOWS::BOOL isEx, WINDOWS::HANDLE hFile);
void b4WriteFile(const WINDOWS::BOOL isEx, WINDOWS::HANDLE hFile);
void b4CloseHandle(WINDOWS::HANDLE hObject);
void OnFileReturn(const int fCode, const char Code, UINT32 lResult);

//NetworkAPI Hooks   -> WS2_32.dll, Defs in NetAPI.cpp
void Image_WS2_32(IMG img, void *v);
int	 jwConnect(CONTEXT *ctxt, AFUNPTR fpOrigin, WINDOWS::SOCKET socket, WINDOWS::PSOCKADDR pSocketName, int iNameLen);
void b4Connect(WINDOWS::SOCKET socket, WINDOWS::PSOCKADDR pSocketName);
void afterConnect(int iResult);
void b4Socket(int af, int type, int protocol);
void afterSocket(WINDOWS::SOCKET socket);
WINDOWS::SOCKET jwSocket(CONTEXT *ctxt, AFUNPTR fpOrigin, int af, int type, int protocol); 