#include"pintool.h"

extern std::wofstream		wLogFile;
extern PIN_LOCK logFileLock;
//extern std::wostringstream	wStringStream;
extern int iExpect[MAX_THREAD];

WINDOWS::HANDLE jwCreateFileW(CONTEXT *ctxt, AFUNPTR fpOrigin, WINDOWS::LPWSTR lpFileName, 
							  WINDOWS::DWORD dwDesiredAccess, WINDOWS::DWORD dwShareMode,
							  WINDOWS::LPSECURITY_ATTRIBUTES lpSecurityAttributes, WINDOWS::DWORD dwCreationDisposition,
							  WINDOWS::DWORD dwFlagsAndAttributes, WINDOWS::HANDLE hTemplateFile)
{
	WINDOWS::HANDLE hFile = 0;
	std::wostringstream wStringStream;

	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"CreateFileW"
					<<DELIM<<"CALL"
					<<DELIM<<"lpFileName="<<lpFileName
					<<DELIM<<"dwDesiredAccess="<<hex<<dwDesiredAccess
					<<DELIM<<"dwShareMode="<<hex<<dwShareMode
					<<DELIM<<"dwCreationDisposition="<<dwCreationDisposition
					<<DELIM<<"dwFlagsAndAttributes="<<dwFlagsAndAttributes
					<<dec<<endl;
	PIN_CallApplicationFunction(ctxt, PIN_ThreadId(), CALLINGSTD_STDCALL, fpOrigin,
		PIN_PARG(WINDOWS::HANDLE*), &hFile, PIN_PARG(WINDOWS::LPWSTR), lpFileName,
		PIN_PARG(WINDOWS::DWORD), dwDesiredAccess, PIN_PARG(WINDOWS::DWORD), dwShareMode,
		PIN_PARG(WINDOWS::LPSECURITY_ATTRIBUTES), lpSecurityAttributes,
		PIN_PARG(WINDOWS::DWORD), dwCreationDisposition, PIN_PARG(WINDOWS::DWORD), dwFlagsAndAttributes,
		PIN_PARG(WINDOWS::HANDLE), hTemplateFile, PIN_PARG_END());

	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str()
			<<"Thread="<<hex<<PIN_GetTid()
			<<DELIM<<"CreateFileW"
			<<DELIM<<"RETN"
			<<DELIM<<"Value="<<hex<<hFile
			<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
	return hFile;
}

void b4CreateFile(const char Code, UINT32 lpFileName, WINDOWS::DWORD dwDesiredAccess,
				  WINDOWS::DWORD dwShareMode, WINDOWS::LPSECURITY_ATTRIBUTES lpSecurityAttributes,
				  WINDOWS::DWORD dwCreationDisposition, WINDOWS::DWORD dwFlagsAndAttributes)
{
	std::wostringstream wStringStream;

	iExpect[PIN_ThreadId()] = CREATE_FILE;
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"CreateFile"<<Code
					<<DELIM<<"CALL"
					<<DELIM<<"lpFileName=";
	if('A' == Code)
		wStringStream<<(WINDOWS::LPCSTR)lpFileName;
	else
		wStringStream<<(WINDOWS::LPWSTR)lpFileName;

	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str()
		<<DELIM<<"dwDesiredAccess="<<hex<<dwDesiredAccess
		<<DELIM<<"dwShareMode="<<hex<<dwShareMode
		<<DELIM<<"dwCreationDisposition="<<dwCreationDisposition
		<<DELIM<<"dwFlagsAndAttributes="<<dwFlagsAndAttributes
		<<dec<<endl;
	wLogFile.flush();	
	ReleaseLock(&logFileLock);
	//wStringStream.str(L"");
}

void b4DeleteFile(const char Code, UINT32 lpFileName)
{
	std::wostringstream wStringStream;

	iExpect[PIN_ThreadId()] = DELETE_FILE;
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"DeleteFile"<<Code
					<<DELIM<<"CALL"
					<<DELIM<<"lpFileName=";
	if('A' == Code)
		wStringStream<<(WINDOWS::LPCSTR)lpFileName;
	else
		wStringStream<<(WINDOWS::LPWSTR)lpFileName;

	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str()<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
	//wStringStream.str(L"");
}

void b4ReadFile(const WINDOWS::BOOL isEx, WINDOWS::HANDLE hFile)
{
	std::wostringstream wStringStream;

	iExpect[PIN_ThreadId()] = READ_FILE;

	wStringStream<<"Thread="<<hex<<PIN_GetTid()
			<<DELIM<<"ReadFile";
	if(isEx)
		wStringStream<<"Ex";

	wStringStream<<DELIM<<"CALL"
			<<DELIM<<"hFile="<<hex<<hFile;

	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str()<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
}

void b4WriteFile(const WINDOWS::BOOL isEx, WINDOWS::HANDLE hFile)
{
	std::wostringstream wStringStream;

	iExpect[PIN_ThreadId()] = WRITE_FILE;

	wStringStream<<"Thread="<<hex<<PIN_GetTid()
		<<DELIM<<"WriteFile";
	if(isEx)
		wStringStream<<"Ex";	   
	wStringStream<<DELIM<<"CALL"
			<<DELIM<<"hFile="<<hex<<hFile;

	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str()<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
}

void b4SetFilePointer(const WINDOWS::BOOL isEx, WINDOWS::HANDLE hFile, 
					  WINDOWS::LONG lDistanceToMove, WINDOWS::DWORD dwMoveMethod)
{
	std::wostringstream wStringStream;

	iExpect[PIN_ThreadId()]=SETFILE_PTR;

	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"SetFilePointer";
	if(isEx)
		wStringStream<<"Ex";
	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str()
			<<DELIM<<"CALL"
			<<DELIM<<"hFile="<<hex<<hFile
			<<DELIM<<"lDistanceToMove="<<lDistanceToMove
			<<DELIM<<"dwMoveMethod="<<dwMoveMethod
			<<dec<<endl;
	wLogFile.flush();
	wLogFile.flush();
	ReleaseLock(&logFileLock);
	//wStringStream.str(L"");
}

//Ovlerlapping Handles
void b4CloseHandle(WINDOWS::HANDLE hObject)
{
	//std::wostringstream wStringStream;
	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<"Thread="<<hex<<PIN_GetTid()
			<<DELIM<<"CloseHandle"
			<<DELIM<<"CALL"
			<<DELIM<<"hObject="<<hex<<hObject
			<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
}
	
void OnFileReturn(const int fCode, const char Code, UINT32 lResult)
{
	std::wostringstream wStringStream;

	if(fCode != iExpect[PIN_ThreadId()])
		return;
	iExpect[PIN_ThreadId()]=0;
	
	wStringStream<<"Thread="<<hex<<PIN_GetTid()<<DELIM;
	switch(fCode)
	{
	case CREATE_FILE:
		wStringStream<<"CreateFile"<<Code
						<<DELIM<<"RETN"
						<<DELIM<<"Value="<<hex<<(WINDOWS::HANDLE)lResult;
		break;
	case DELETE_FILE:
		wStringStream<<"DeleteFile"<<Code
						<<DELIM<<"RETN"
						<<DELIM<<"Value="<<hex<<(WINDOWS::BOOL)lResult;			
		break;
	case SETFILE_PTR:
		wStringStream<<"SetFilePointer";
		if(' ' != Code)
			wStringStream<<"Ex";
		wStringStream<<DELIM<<"RETN"
			<<DELIM<<"Value="<<hex<<(WINDOWS::LONG)lResult;
		break;
	case WRITE_FILE:
		wStringStream<<"WriteFile";
		if(' ' != Code)
			wStringStream<<"Ex";
		wStringStream<<DELIM<<"RETN"
			<<DELIM<<"Value="<<hex<<(WINDOWS::BOOL)lResult;
		break;
	case READ_FILE:
		wStringStream<<"ReadFile";
		if(' ' != Code)
			wStringStream<<"Ex";
		wStringStream<<DELIM<<"RETN"<<DELIM<<"Value="<<hex<<(WINDOWS::BOOL)lResult;
	}

	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str()<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
}