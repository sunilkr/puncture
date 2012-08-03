#include"pintool.h"

extern std::wofstream		wLogFile;
extern PIN_LOCK logFileLock;
//extern std::wostringstream	wStringStream;

void Image_ADVAPI32(IMG img, void *v)
{
	RTN rtn;
	PROTO proto;
	std::wostringstream	wStringStream;

	for(SYM sym = IMG_RegsymHead(img); SYM_Valid(sym); sym = SYM_Next(sym))
	{
		string sUndecFuncName = PIN_UndecorateSymbolName(SYM_Name(sym),UNDECORATION_NAME_ONLY);

		//RegOpenKeyEx
		if("RegOpenKeyExA" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"ADVAPI32.DLL"<<DELIM<<"RegOpenKeyExA"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				proto = PROTO_Allocate(PIN_PARG(WINDOWS::LONG),CALLINGSTD_STDCALL,"RegOpenKeyExA",
					PIN_PARG(WINDOWS::HKEY), PIN_PARG(WINDOWS::LPCTSTR), PIN_PARG(WINDOWS::DWORD),
					PIN_PARG(WINDOWS::REGSAM), PIN_PARG(WINDOWS::PHKEY), PIN_PARG_END());
				RTN_ReplaceSignature(rtn, AFUNPTR(jwRegOpenKeyEx),
					IARG_PROTOTYPE, proto,
					IARG_ADDRINT, 'A',
					IARG_CONTEXT,
					IARG_ORIG_FUNCPTR,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
					IARG_END
					);
				PROTO_Free(proto);
			}
		}
		else if("RegOpenKeyExW" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"ADVAPI32.DLL"<<DELIM<<"RegOpenKeyExW"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				proto = PROTO_Allocate(PIN_PARG(WINDOWS::LONG),CALLINGSTD_STDCALL,"RegOpenKeyExW",
					PIN_PARG(WINDOWS::HKEY), PIN_PARG(WINDOWS::LPCTSTR), PIN_PARG(WINDOWS::DWORD),
					PIN_PARG(WINDOWS::REGSAM), PIN_PARG(WINDOWS::PHKEY), PIN_PARG_END());
				RTN_ReplaceSignature(rtn, AFUNPTR(jwRegOpenKeyEx),
					IARG_PROTOTYPE, proto,
					IARG_ADDRINT, 'W',
					IARG_CONTEXT,
					IARG_ORIG_FUNCPTR,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
					IARG_END
					);
				PROTO_Free(proto);
			}
		}

		//RegCreateKeyEx
		else if("RegCreateKeyExA" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"ADVAPI32.DLL"<<DELIM<<"RegCreateKeyExA"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				proto = PROTO_Allocate(PIN_PARG(WINDOWS::LONG), CALLINGSTD_STDCALL, "RegCreateKeyExA",
					PIN_PARG(WINDOWS::HKEY), PIN_PARG(WINDOWS::LPWSTR), PIN_PARG(WINDOWS::DWORD),
					PIN_PARG(WINDOWS::LPWSTR), PIN_PARG(WINDOWS::DWORD), PIN_PARG(WINDOWS::REGSAM),
					PIN_PARG(WINDOWS::LPSECURITY_ATTRIBUTES), PIN_PARG(WINDOWS::PHKEY), 
					PIN_PARG(WINDOWS::LPDWORD), PIN_PARG_END());
				RTN_ReplaceSignature(rtn, AFUNPTR(jwRegCreateKeyEx),
					IARG_PROTOTYPE, proto,
					IARG_ADDRINT, 'A',
					IARG_CONTEXT,
					IARG_ORIG_FUNCPTR,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 6,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 7,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 8,
					IARG_END);
				PROTO_Free(proto);   
			}
		}
		else if("RegCreateKeyExW" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"ADVAPI32.DLL"<<DELIM<<"RegCreateKeyExW"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				proto = PROTO_Allocate(PIN_PARG(WINDOWS::LONG), CALLINGSTD_STDCALL, "RegCreateKeyExW",
					PIN_PARG(WINDOWS::HKEY), PIN_PARG(WINDOWS::LPWSTR), PIN_PARG(WINDOWS::DWORD),
					PIN_PARG(WINDOWS::LPWSTR), PIN_PARG(WINDOWS::DWORD), PIN_PARG(WINDOWS::REGSAM),
					PIN_PARG(WINDOWS::LPSECURITY_ATTRIBUTES), PIN_PARG(WINDOWS::PHKEY), 
					PIN_PARG(WINDOWS::LPDWORD), PIN_PARG_END());
				RTN_ReplaceSignature(rtn, AFUNPTR(jwRegCreateKeyEx),
					IARG_PROTOTYPE, proto,
					IARG_ADDRINT, 'W',
					IARG_CONTEXT,
					IARG_ORIG_FUNCPTR,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 6,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 7,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 8,
					IARG_END);
				PROTO_Free(proto);
			}
		}

		//RegQueryValueEx
		else if("RegQueryValueExA" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"ADVAPI32.DLL"<<DELIM<<"RegQueryValueExA"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, AFUNPTR(b4RegQueryValueEx),
					IARG_ADDRINT, 'A', IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1,IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, AFUNPTR(OnRegReturn), 
					IARG_ADDRINT, REG_QVALUE, IARG_ADDRINT, 'A', 
					IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}
		else if("RegQueryValueExW" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"ADVAPI32.DLL"<<DELIM<<"RegQueryValueExW"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, AFUNPTR(b4RegQueryValueEx),
					IARG_ADDRINT, 'W', IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, AFUNPTR(OnRegReturn),
					IARG_ADDRINT, REG_QVALUE, IARG_ADDRINT, 'W',
					IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}

		//RegSetValueEx
		else if("RegSetValueExA" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"ADVAPI32.DLL"<<DELIM<<"RegSetValueExA"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, AFUNPTR(b4RegSetValueEx),
					IARG_ADDRINT, 'A', 
					IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
					IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, AFUNPTR(OnRegReturn),
					IARG_ADDRINT, REG_SETVAL, IARG_ADDRINT, 'A', 
					IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}
		else if("RegSetValueExW" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"ADVAPI32.DLL"<<DELIM<<"RegSetValueExA"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, AFUNPTR(b4RegSetValueEx),
					IARG_ADDRINT, 'W',
					IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
					IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, AFUNPTR(OnRegReturn),
					IARG_ADDRINT, REG_SETVAL, IARG_ADDRINT, 'W',
					IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}

		//RegDeleteKeyEx
		else if("RegDeleteKeyExA" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"ADVAPI32.DLL"<<DELIM<<"RegDeleteKeyExA"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, AFUNPTR(b4RegDeleteKeyEx),
					IARG_ADDRINT, 'A', IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, AFUNPTR(OnRegReturn),
					IARG_ADDRINT, REG_DELKEY, IARG_ADDRINT, 'A',
					IARG_FUNCARG_ENTRYPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}
		else if("RegDeleteKeyExW" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"ADVAPI32.DLL"<<DELIM<<"RegDeleteKeyExW"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, AFUNPTR(b4RegDeleteKeyEx),
					IARG_ADDRINT, 'W', IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, AFUNPTR(OnRegReturn),
					IARG_ADDRINT, REG_DELKEY, IARG_ADDRINT, 'W', 
					IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}
	}
	
	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str();
	wLogFile.flush();
	ReleaseLock(&logFileLock);
}

void Image_Kernel32(IMG img, void *v)
{
	RTN rtn;
	PROTO proto;
	std::wostringstream	wStringStream;

	for(SYM sym = IMG_RegsymHead(img); SYM_Valid(sym); sym = SYM_Next(sym))
	{
		string sUndecFuncName = PIN_UndecorateSymbolName(SYM_Name(sym),UNDECORATION_NAME_ONLY);
		if("CreateFileW" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"KERNEL32.DLL"<<DELIM<<"CreateFileW"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				/*
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4CreateFile,
					IARG_ADDRINT, 'W', IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 3, IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 5, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) OnFileReturn,
					IARG_ADDRINT, CREATE_FILE, IARG_ADDRINT, 'W',
					IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
				*/
				proto = PROTO_Allocate(PIN_PARG(WINDOWS::HANDLE), CALLINGSTD_STDCALL, "CreateFileW",
					PIN_PARG(WINDOWS::LPWSTR), PIN_PARG(WINDOWS::LPDWORD), PIN_PARG(WINDOWS::DWORD),
					PIN_PARG(WINDOWS::LPSECURITY_ATTRIBUTES), PIN_PARG(WINDOWS::DWORD),
					PIN_PARG(WINDOWS::DWORD), PIN_PARG(WINDOWS::HANDLE), PIN_PARG_END());
				RTN_ReplaceSignature(rtn, (AFUNPTR) jwCreateFileW, IARG_PROTOTYPE, proto,
					IARG_CONTEXT, IARG_ORIG_FUNCPTR, IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 3, IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 5, IARG_FUNCARG_ENTRYPOINT_VALUE, 6, IARG_END);
				PROTO_Free(proto);

			}
		}
		/*::NOT_INSTRUMENTD. It calls CreateFileW or Fails :)
		else if("CreateFileA" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wLogFile<<DELIM<<"CreateFileA"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4CreateFile,
					IARG_ADDRINT, 'A', IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 3, IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 5, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) OnFileReturn,
					IARG_ADDRINT, CREATE_FILE, IARG_ADDRINT, 'A',
					IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}*/
		else if("ReadFile" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"KERNEL32.DLL"<<DELIM<<"ReadFile"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				/* Required if data transferred needs to be captured
				proto = PROTO_Allocate(PIN_PARG(WINDOWS::BOOL), CALLINGSTD_STDCALL, "ReadFile",
					PIN_PARG(WINDOWS::HANDLE), PIN_PARG(WINDOWS::LPVOID), PIN_PARG(WINDOWS::DWORD),
					PIN_PARG(WINDOWS::LPDWORD), PIN_PARG(WINDOWS::LPOVERLAPPED), PIN_PARG_END());
				RTN_ReplaceSignature(rtn, (AFUNPTR) jwReadFile,
					IARG_PROTOTYPE, proto, IARG_CONTEXT, IARG_ORIG_FUNCPTR,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 2, IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 4, IARG_END);
				PROTO_Free(proto);*/
				//Log Calls only
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4ReadFile,
					IARG_ADDRINT, FALSE, IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) OnFileReturn, 
					IARG_ADDRINT, READ_FILE, IARG_ADDRINT, ' ', IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
				
			}
		}
		else if("ReadFileEx" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"KERNEL32.DLL"<<DELIM<<"ReadFileEx"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				/*
				wLogFile<<DELIM<<"ReadFileEx"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				proto = PROTO_Allocate(PIN_PARG(WINDOWS::BOOL), CALLINGSTD_STDCALL, "ReadFileEx",
					PIN_PARG(WINDOWS::HANDLE), PIN_PARG(WINDOWS::LPVOID), PIN_PARG(WINDOWS::DWORD),
					PIN_PARG(WINDOWS::LPOVERLAPPED), PIN_PARG(WINDOWS::LPOVERLAPPED_COMPLETION_ROUTINE), PIN_PARG_END());
				RTN_ReplaceSignature(rtn, (AFUNPTR) jwReadFileEx, 
					IARG_PROTOTYPE, proto, IARG_CONTEXT, IARG_ORIG_FUNCPTR,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 2, IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 4, IARG_END);
				PROTO_Free(proto);
				*/
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4ReadFile,
					IARG_ADDRINT, FALSE, IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) OnFileReturn,
					IARG_ADDRINT, READ_FILE, IARG_ADDRINT, 'X', IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}
		else if("WriteFile" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				/*
				wLogFile<<DELIM<<"WriteFile"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				proto = PROTO_Allocate(PIN_PARG(WINDOWS::BOOL), CALLINGSTD_STDCALL, "WriteFile",
					PIN_PARG(WINDOWS::HANDLE), PIN_PARG(WINDOWS::LPVOID), PIN_PARG(WINDOWS::DWORD), 
					PIN_PARG(WINDOWS::LPDWORD), PIN_PARG(WINDOWS::LPOVERLAPPED), PIN_PARG_END());
				RTN_ReplaceSignature(rtn, (AFUNPTR) jwWriteFile,
					IARG_PROTOTYPE, proto, IARG_CONTEXT, IARG_ORIG_FUNCPTR,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 2, IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 4, IARG_END);
				PROTO_Free(proto);
				*/
				wStringStream<<"SYMBOL"<<DELIM<<"KERNEL32.DLL"<<DELIM<<"WriteFile"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;

				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4WriteFile,
					IARG_ADDRINT, FALSE, IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) OnFileReturn,
					IARG_ADDRINT, WRITE_FILE, IARG_ADDRINT, ' ', IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}
		else if("WriteFileEx" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"KERNEL32.DLL"<<DELIM<<"WriteFileEx"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				/*
				wLogFile<<DELIM<<"WriteFileEx"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				proto = PROTO_Allocate(PIN_PARG(WINDOWS::BOOL), CALLINGSTD_STDCALL, "WriteFileEx",
					PIN_PARG(WINDOWS::HANDLE), PIN_PARG(WINDOWS::LPVOID), PIN_PARG(WINDOWS::DWORD),
					PIN_PARG(WINDOWS::LPOVERLAPPED), PIN_PARG(WINDOWS::LPOVERLAPPED_COMPLETION_ROUTINE), PIN_PARG_END());
				RTN_ReplaceSignature(rtn, (AFUNPTR) jwWriteFileEx,
					IARG_PROTOTYPE, proto, IARG_CONTEXT, IARG_ORIG_FUNCPTR,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 2, IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 4, IARG_END);
				PROTO_Free(proto);*/
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4WriteFile,
					IARG_ADDRINT, TRUE, IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) OnFileReturn,
					IARG_ADDRINT, WRITE_FILE, IARG_ADDRINT, 'X', IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}
		/* ::NOT_INSTRUMENTD. It calls DeleteFileW or Fails :)
		else if("DeleteFileA" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wLogFile<<DELIM<<"DeleteFileA"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4DeleteFile,
					IARG_ADDRINT, 'A', IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) OnFileReturn,
					IARG_ADDRINT, DELETE_FILE, IARG_ADDRINT, 'A', IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}*/
		else if("DeleteFileW" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"KERNEL32.DLL"<<DELIM<<"DeleteFileW"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4DeleteFile,
					IARG_ADDRINT, 'W', IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) OnFileReturn,
					IARG_ADDRINT, DELETE_FILE, IARG_ADDRINT, 'W', IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		}

		else if("SetFilePointer" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"KERNEL32.DLL"<<DELIM<<"SetFilePointer"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4SetFilePointer,
					IARG_ADDRINT, FALSE, IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_FUNCARG_ENTRYPOINT_VALUE, 3, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) OnFileReturn,
					IARG_ADDRINT, SETFILE_PTR, IARG_ADDRINT, ' ', IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);
			}
		} 

		//For 64 Bit Values, Not Instumenting now
/*		else if("SetFilePointerEx" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wLogFile<<DELIM<<"SetFilePointerEx"<<DELIM<<"@"<<hex<<RTN_Address(rtn);
			}
		}*/

		//Misc functions required to verify correctness
		else if("CloseHandle" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				 wStringStream<<"SYMBOL"<<DELIM<<"KERNEL32.DLL"<<DELIM<<"CloseHandle"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				 /*RTN_Open(rtn);
				 RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4CloseHandle, IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_END);
				 RTN_Close(rtn);*/
			}
		}
	}

	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str();
	wLogFile.flush();
	ReleaseLock(&logFileLock);
}

void Image_WS2_32(IMG img, void *v)
{
	RTN rtn;
	PROTO proto;
	std::wostringstream	wStringStream;

	for(SYM sym = IMG_RegsymHead(img); SYM_Valid(sym); sym = SYM_Next(sym))
	{
		string sUndecFuncName = PIN_UndecorateSymbolName(SYM_Name(sym), UNDECORATION_NAME_ONLY);
		if("socket" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));
			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"WS2_32.DLL"<<DELIM<<"socket"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;
				/*RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4Socket,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 2, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) afterSocket, IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);*/

				proto = PROTO_Allocate(PIN_PARG(WINDOWS::SOCKET), CALLINGSTD_STDCALL, "socket",
					PIN_PARG(int), PIN_PARG(int), PIN_PARG(int), PIN_PARG_END());
				RTN_ReplaceSignature(rtn, (AFUNPTR) jwSocket, IARG_PROTOTYPE, proto,
					IARG_CONTEXT, IARG_ORIG_FUNCPTR, IARG_FUNCARG_ENTRYPOINT_VALUE ,0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_FUNCARG_ENTRYPOINT_VALUE, 2, IARG_END);
				PROTO_Free(proto);
			}
		}
		else if("connect" == sUndecFuncName)
		{
			rtn = RTN_FindByAddress(IMG_LowAddress(img)+SYM_Value(sym));

			if(RTN_Valid(rtn))
			{
				wStringStream<<"SYMBOL"<<DELIM<<"WS2_32.DLL"<<DELIM<<"connect"<<DELIM<<"@"<<hex<<RTN_Address(rtn)<<dec<<endl;

				proto = PROTO_Allocate(PIN_PARG(WINDOWS::BOOL), CALLINGSTD_STDCALL, "connect",
					PIN_PARG(WINDOWS::SOCKET), PIN_PARG(WINDOWS::PSOCKADDR), PIN_PARG(int),
					PIN_PARG_END());
				RTN_ReplaceSignature(rtn, (AFUNPTR)jwConnect, IARG_PROTOTYPE, proto,
					IARG_CONTEXT, IARG_ORIG_FUNCPTR, IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_FUNCARG_ENTRYPOINT_VALUE, 2, IARG_END);
				PROTO_Free(proto);
				/*RTN_Open(rtn);
				RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) b4Connect, IARG_FUNCARG_ENTRYPOINT_VALUE, 0, 
					IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_END);
				RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) afterConnect, IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
				RTN_Close(rtn);*/
			}
		}  
	}

	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str();
	wLogFile.flush();
	ReleaseLock(&logFileLock);
}