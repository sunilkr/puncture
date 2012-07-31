#include"pintool.h"

extern std::wofstream		wLogFile;
extern std::wostringstream wStringStream;
extern int iExpect[MAX_THREAD];

WINDOWS::LONG jwRegCreateKeyEx(const char Code, CONTEXT *ctxt, AFUNPTR fpOrigin, 
							   WINDOWS::HKEY hKey, UINT32 lpSubKey, 
							   WINDOWS::DWORD dwReserved, UINT32 lpClass, 
							   WINDOWS::DWORD dwOptions, WINDOWS::REGSAM samDesired, 
							   WINDOWS::LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
							   WINDOWS::PHKEY phkResult, WINDOWS::LPDWORD lpdwDisposition)
{
	WINDOWS::LONG Result = 0;
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"RegCreateKeyEx"<<Code
					<<DELIM<<"CALL"
					<<DELIM<<"hKey="<<hex<<hKey;
	switch(Code)
	{
	case 'A':
		if(lpSubKey)
			wStringStream<<DELIM<<"lpSubKey="<<(WINDOWS::LPCTSTR)lpSubKey;
		else
			wStringStream<<DELIM<<"lpSubKey=Default";
		PIN_CallApplicationFunction(ctxt, PIN_ThreadId(),
			CALLINGSTD_STDCALL, fpOrigin,
			PIN_PARG(WINDOWS::LONG*), &Result,
			PIN_PARG(WINDOWS::HKEY), hKey, 
			PIN_PARG(WINDOWS::LPCTSTR), lpSubKey, 
			PIN_PARG(WINDOWS::DWORD), dwReserved,
			PIN_PARG(WINDOWS::LPCTSTR), lpClass, 
			PIN_PARG(WINDOWS::DWORD), dwOptions, 
			PIN_PARG(WINDOWS::REGSAM), samDesired,
			PIN_PARG(WINDOWS::LPSECURITY_ATTRIBUTES), lpSecurityAttributes, 
			PIN_PARG(WINDOWS::PHKEY), phkResult, 
			PIN_PARG(WINDOWS::LPDWORD), lpdwDisposition,
			PIN_PARG_END());
		break;
	case 'W':
		if(lpSubKey)
			wStringStream<<DELIM<<"lpSubKey="<<(WINDOWS::LPWSTR)lpSubKey;
		else
			wStringStream<<DELIM<<"lpSubKey=Dfault";
		PIN_CallApplicationFunction(ctxt, PIN_ThreadId(),
			CALLINGSTD_STDCALL, fpOrigin,
			PIN_PARG(WINDOWS::LONG*), &Result,
			PIN_PARG(WINDOWS::HKEY), hKey, 
			PIN_PARG(WINDOWS::LPWSTR), lpSubKey, 
			PIN_PARG(WINDOWS::DWORD), dwReserved,
			PIN_PARG(WINDOWS::LPWSTR), lpClass, 
			PIN_PARG(WINDOWS::DWORD), dwOptions, 
			PIN_PARG(WINDOWS::REGSAM), samDesired,
			PIN_PARG(WINDOWS::LPSECURITY_ATTRIBUTES), lpSecurityAttributes, 
			PIN_PARG(WINDOWS::PHKEY), phkResult, 
			PIN_PARG(WINDOWS::LPDWORD), lpdwDisposition,
			PIN_PARG_END());
		break;
	}
	wStringStream<<dec<<endl;
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"RegCreateKeyEx"<<Code
					<<DELIM<<"RETN"
					<<DELIM<<"Value="<<hex<<Result;
	if(ERROR_SUCCESS == Result)
		wStringStream<<DELIM<<"phkResult="<<hex<<*phkResult;
	wLogFile<<wStringStream.str()<<DELIM<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");
	return Result;
}

WINDOWS::LONG jwRegOpenKeyEx(const char Code, CONTEXT *ctxt, AFUNPTR fpOrigin,
							 WINDOWS::HKEY hKey, UINT32 lpSubKey, WINDOWS::DWORD ulOptions,
							 WINDOWS::REGSAM samDesired, WINDOWS::PHKEY phkResult)
{
	WINDOWS::LONG Result=0;
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"RegOpenKeyEx"<<Code
					<<DELIM<<"CALL"
					<<DELIM<<"hKey="<<hKey;

	switch(Code)
	{
	case 'A':
		if(lpSubKey)
			wStringStream<<DELIM<<"lpSubKey="<<(WINDOWS::LPCTSTR)lpSubKey;
		else
			wStringStream<<DELIM<<"lpSubKey=Default";
		PIN_CallApplicationFunction(ctxt, PIN_ThreadId(),
			CALLINGSTD_STDCALL, fpOrigin,
			PIN_PARG(WINDOWS::LONG*), &Result,
			PIN_PARG(WINDOWS::HKEY), hKey,
			PIN_PARG(WINDOWS::LPCTSTR), lpSubKey,
			PIN_PARG(WINDOWS::DWORD), ulOptions,
			PIN_PARG(WINDOWS::REGSAM), samDesired,
			PIN_PARG(WINDOWS::PHKEY), phkResult,
			PIN_PARG_END());
		break;
	case 'W':
		if(lpSubKey)
			wStringStream<<DELIM<<"lpSubKey="<<(WINDOWS::LPWSTR)lpSubKey;
		else
			wStringStream<<DELIM<<"lpSubKey=Default";

		PIN_CallApplicationFunction(ctxt, PIN_ThreadId(),
			CALLINGSTD_STDCALL, fpOrigin,
			PIN_PARG(WINDOWS::LONG*), &Result,
			PIN_PARG(WINDOWS::HKEY), hKey,
			PIN_PARG(WINDOWS::LPWSTR), lpSubKey,
			PIN_PARG(WINDOWS::DWORD), ulOptions,
			PIN_PARG(WINDOWS::REGSAM), samDesired,
			PIN_PARG(WINDOWS::PHKEY), phkResult,
			PIN_PARG_END());
		break;
	}
	wStringStream<<dec<<endl;
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"RegOpenKeyEx"<<Code
					<<DELIM<<"RETN"
					<<DELIM<<"Value="<<hex<<Result;
	if(ERROR_SUCCESS == Result)
		wStringStream<<DELIM<<"phkResult="<<hex<<*phkResult;
	
	wLogFile<<wStringStream.str()<<DELIM<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");
	return Result;
}

void b4RegQueryValueEx(const char Code, WINDOWS::HKEY hKey, UINT32 lpValueName)
{
	iExpect[PIN_ThreadId()] = REG_QVALUE;

	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"RegQueryValueEx"<<Code
					<<DELIM<<"CALL"
					<<DELIM<<"hKey="<<hex<<hKey;
	if(lpValueName)
	{
		switch(Code)
		{
		case 'A': wStringStream<<DELIM<<"lpValueName="<<(WINDOWS::LPCTSTR)lpValueName;
			break;
		case 'W': wStringStream<<DELIM<<"lpValueName="<<(WINDOWS::LPWSTR)lpValueName;
			break;
		}
	}
	else
		wStringStream<<DELIM<<"lpValueName=Default";

	wLogFile<<wStringStream.str()<<DELIM<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");
}

void b4RegDeleteKeyEx(const char Code, WINDOWS::HKEY hKey, UINT32 lpSubKey)
{
	iExpect[PIN_ThreadId()] = REG_DELKEY;
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"RegDeleteKeyEx"<<Code
					<<DELIM<<"CALL"
					<<DELIM<<"hKey="<<hex<<hKey;
	if(lpSubKey)
	{
		switch(Code)
		{
		case 'A': wStringStream<<DELIM<<"lpSubKey="<<(WINDOWS::LPCTSTR)lpSubKey;
			break;
		case 'W': wStringStream<<DELIM<<"lpSubKey="<<(WINDOWS::LPWSTR)lpSubKey;
			break;
		}
	}
	else
		wStringStream<<DELIM<<"lpSubKey=Default";
	wLogFile<<wStringStream.str()<<DELIM<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");
}

void b4RegSetValueEx(const char Code, WINDOWS::HKEY hKey, UINT32 lpValueName, WINDOWS::DWORD dwType,
					 const WINDOWS::BYTE *lpData, WINDOWS::DWORD cbData)
{
	WINDOWS::LPCTSTR lpctTemp;
	WINDOWS::LPWSTR lpwTemp;
	WINDOWS::DWORD dwOffset=0;

	iExpect[PIN_ThreadId()] = REG_SETVAL;
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"RegSetValueEx"<<Code
					<<DELIM<<"CALL"
					<<DELIM<<"hKey"<<hex<<hKey;
	if(lpValueName)
	{
		switch(Code)
		{
		case 'A': wStringStream<<DELIM<<"lpValueName="<<(WINDOWS::LPCTSTR)lpValueName;
			break;
		case 'W': wStringStream<<DELIM<<"lpValueName="<<(WINDOWS::LPWSTR)lpValueName;
		}
	}
	else
		wStringStream<<DELIM<<"lpValuName=Default";

	wStringStream<<DELIM<<"dwType="<<hex<<dwType;
	wStringStream<<DELIM<<"cbData="<<dec<<cbData;

	switch(dwType)
	{	
	case REG_SZ:
		switch(Code)
		{
		case 'A': wStringStream<<DELIM<<"lpData="<<(WINDOWS::LPCTSTR)lpData;
			break;
		case 'W': wStringStream<<DELIM<<"lpData="<<(WINDOWS::LPWSTR)lpData;
		}
		break;
	case REG_EXPAND_SZ:
		switch(Code)
		{
		case 'A': wStringStream<<DELIM<<"lpData="<<(WINDOWS::LPCTSTR)lpData;
			break;
		case 'W': wStringStream<<DELIM<<"lpData="<<(WINDOWS::LPWSTR)lpData;
		}
		break;
	case REG_MULTI_SZ:
		wStringStream<<DELIM<<"lpData=";
		switch(Code)
		{
		case 'A':
			lpctTemp = (WINDOWS::LPCTSTR) lpData;
			while(dwOffset<cbData)
			{
				wStringStream<<"'"<<lpctTemp<<"',";
				dwOffset += strlen(lpctTemp);
				lpctTemp += dwOffset+1;
			}
			break;
		case 'W':
			lpwTemp = (WINDOWS::LPWSTR) lpData;
			while(dwOffset<cbData)
			{
				wStringStream<<"'"<<lpwTemp<<"',";
				dwOffset = wcslen(lpwTemp);
				lpwTemp += dwOffset+1;
			}
		}
		break;
	default:
		wStringStream<<DELIM<<"lpData="<<hex;
		for(WINDOWS::DWORD i = 0; i<cbData; i++)
			wStringStream<<*(lpData+i);
	}
	wLogFile<<wStringStream.str()<<DELIM<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");
}

void OnRegReturn(int funcCode, const char Code, WINDOWS::LONG lResult)
{
	if(iExpect[PIN_ThreadId()]!=funcCode)
		return;
	iExpect[PIN_ThreadId()] = 0;

	wStringStream<<"Thread="<<hex<<PIN_GetTid();
	switch(funcCode)
	{
	case REG_QVALUE: wStringStream<<DELIM<<"RegQueryValueEx"<<Code;
		break;
	case REG_SETVAL: wStringStream<<DELIM<<"RegSetValueEx"<<Code;
		break;
	case REG_DELKEY: wStringStream<<DELIM<<"RegDeleteKeyEx"<<Code;
	}
	wStringStream<<DELIM<<"RETN"<<DELIM<<"Value="<<hex<<lResult<<DELIM<<dec<<endl;
	wLogFile<<wStringStream.str();
	wLogFile.flush();
	wStringStream.str(L"");
}