#include"pintool.h"

extern std::wofstream		wLogFile;
extern std::wostringstream	wStringStream;
extern int iExpect[MAX_THREAD];

WINDOWS::HANDLE jwCreateFileW(CONTEXT *ctxt, AFUNPTR fpOrigin, WINDOWS::LPWSTR lpFileName, 
							  WINDOWS::DWORD dwDesiredAccess, WINDOWS::DWORD dwShareMode,
							  WINDOWS::LPSECURITY_ATTRIBUTES lpSecurityAttributes, WINDOWS::DWORD dwCreationDisposition,
							  WINDOWS::DWORD dwFlagsAndAttributes, WINDOWS::HANDLE hTemplateFile)
{
	WINDOWS::HANDLE hFile = 0;
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

	wLogFile<<wStringStream.str()
			<<"Thread="<<hex<<PIN_GetTid()
			<<DELIM<<"CreateFileW"
			<<DELIM<<"RETN"
			<<DELIM<<"Value="<<hex<<hFile
			<<DELIM<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");
	return hFile;
}

void b4CreateFile(const char Code, UINT32 lpFileName, WINDOWS::DWORD dwDesiredAccess,
				  WINDOWS::DWORD dwShareMode, WINDOWS::LPSECURITY_ATTRIBUTES lpSecurityAttributes,
				  WINDOWS::DWORD dwCreationDisposition, WINDOWS::DWORD dwFlagsAndAttributes)
{
	iExpect[PIN_ThreadId()] = CREATE_FILE;
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"CreateFile"<<Code
					<<DELIM<<"CALL"
					<<DELIM<<"lpFileName=";
	if('A' == Code)
		wStringStream<<(WINDOWS::LPCSTR)lpFileName;
	else
		wStringStream<<(WINDOWS::LPWSTR)lpFileName;
	wLogFile<<wStringStream.str()
					<<DELIM<<"dwDesiredAccess="<<hex<<dwDesiredAccess
					<<DELIM<<"dwShareMode="<<hex<<dwShareMode
					<<DELIM<<"dwCreationDisposition="<<dwCreationDisposition
					<<DELIM<<"dwFlagsAndAttributes="<<dwFlagsAndAttributes
					<<DELIM<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");
}

void b4DeleteFile(const char Code, UINT32 lpFileName)
{
	iExpect[PIN_ThreadId()] = DELETE_FILE;
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"DeleteFile"<<Code
					<<DELIM<<"CALL"
					<<DELIM<<"lpFileName=";
	if('A' == Code)
		wStringStream<<(WINDOWS::LPCSTR)lpFileName;
	else
		wStringStream<<(WINDOWS::LPWSTR)lpFileName;
	wLogFile<<wStringStream.str()<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");
}

void b4ReadFile(const WINDOWS::BOOL isEx, WINDOWS::HANDLE hFile)
{
	iExpect[PIN_ThreadId()] = READ_FILE;

	wLogFile<<"Thread="<<hex<<PIN_GetTid()
			<<DELIM<<"ReadFile";
	if(isEx)
		wLogFile<<"Ex";
	wLogFile<<DELIM<<"CALL"
			<<DELIM<<"hFile="<<hex<<hFile
			<<dec<<endl;
	wLogFile.flush();
}

void b4WriteFile(const WINDOWS::BOOL isEx, WINDOWS::HANDLE hFile)
{
	iExpect[PIN_ThreadId()] = WRITE_FILE;

	wLogFile<<"Thread="<<hex<<PIN_GetTid()
		<<DELIM<<"WriteFile";
	if(isEx)
		wLogFile<<"Ex";	   
	wLogFile<<DELIM<<"CALL"
			<<DELIM<<"hFile="<<hex<<hFile
			<<dec<<endl;
	wLogFile.flush();
}

void b4SetFilePointer(const WINDOWS::BOOL isEx, WINDOWS::HANDLE hFile, 
					  WINDOWS::LONG lDistanceToMove, WINDOWS::DWORD dwMoveMethod)
{
	iExpect[PIN_ThreadId()]=SETFILE_PTR;

	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"SetFilePointer";
	if(isEx)
		wStringStream<<"Ex";
	wLogFile<<wStringStream.str()
			<<DELIM<<"CALL"
			<<DELIM<<"hFile="<<hex<<hFile
			<<DELIM<<"lDistanceToMove="<<lDistanceToMove
			<<DELIM<<"dwMoveMethod="<<dwMoveMethod
			<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");
}

//Ovlerlapping Handles
void b4CloseHandle(WINDOWS::HANDLE hObject)
{
	wLogFile<<"Thread="<<hex<<PIN_GetTid()
			<<DELIM<<"CloseHandle"
			<<DELIM<<"CALL"
			<<DELIM<<"hObject="<<hex<<hObject
			<<dec<<endl;
	wLogFile.flush();
}
	
void OnFileReturn(const int fCode, const char Code, UINT32 lResult)
{
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
	wLogFile<<wStringStream.str()<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");	
}