#include "pintool.h"

extern std::wofstream		wLogFile;
extern PIN_LOCK logFileLock;
//extern std::wostringstream	wStringStream;
int iExpectedThread = -1;
int iSockExpThread = -1;

int jwConnect(CONTEXT *ctxt, AFUNPTR fpOrigin, WINDOWS::SOCKET socket, WINDOWS::PSOCKADDR pSocketName, int iNameLen)
{
	int iResult = 0;
	std::wostringstream wStringStream;

	wStringStream<<"Thread="<<hex<<PIN_GetTid()
					<<DELIM<<"connect"
					<<DELIM<<"CALL"
					<<DELIM<<"socket="<<hex<<socket
					<<DELIM<<"sa_family="<<hex<<pSocketName->sa_family;
	if(AF_INET == pSocketName->sa_family)
		{
			WINDOWS::SOCKADDR_IN *sockaddr_in = (WINDOWS::SOCKADDR_IN*) pSocketName;
			wStringStream<<DELIM<<"sin_port="<<dec<<sockaddr_in->sin_port
						 <<DELIM<<"sin_addr="<<hex<<sockaddr_in->sin_addr.S_un.S_addr;
		}
	wStringStream<<dec<<endl;   
	PIN_CallApplicationFunction(ctxt, PIN_ThreadId(), CALLINGSTD_STDCALL, fpOrigin,
		PIN_PARG(int*), &iResult, PIN_PARG(WINDOWS::SOCKET), socket, 
		PIN_PARG(WINDOWS::PSOCKADDR), pSocketName, PIN_PARG(int), iNameLen, PIN_PARG_END());
	
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
				<<DELIM<<"connect"
				<<DELIM<<"RETN"
				<<DELIM<<"Value="<<hex<<iResult
				<<DELIM<<dec<<endl;

	/*if(!iResult)
	{
		wStringStream<<DELIM<<"socket_name->sa_family="<<hex<<pSocketName->sa_family;
	}*/
	
	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str()<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
	return iResult;
}

void b4Connect(WINDOWS::SOCKET socket, WINDOWS::PSOCKADDR pSocketName)
{
	std::wostringstream wStringStream;

	iExpectedThread = PIN_GetTid();
	wStringStream<<"Thread="<<hex<<PIN_GetTid()
		<<DELIM<<"connect"
		<<DELIM<<"CALL"
		<<DELIM<<"socket="<<hex<<socket
		<<DELIM<<"socket_name->sa_family="<<hex<<pSocketName->sa_family;

	if(AF_INET == pSocketName->sa_family)
	{
		WINDOWS::SOCKADDR_IN *sockaddr_in = (WINDOWS::SOCKADDR_IN*) pSocketName;
		wStringStream<<DELIM<<"sin_port="<<dec<<sockaddr_in->sin_port
			<<DELIM<<"sin_addr="<<hex<<sockaddr_in->sin_addr.S_un.S_addr;
	}

	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str()<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
}
void afterConnect(int iResult)
{
	std::wostringstream wStringStream;

	if(iExpectedThread != PIN_GetTid())
		return;

	iExpectedThread = -1;  //TODO:: Resolve Reace Condition
	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<"Thread="<<hex<<PIN_GetTid()
				<<DELIM<<"connect"
				<<DELIM<<"RETN"
				<<DELIM<<"Value="<<hex<<iResult
				<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
	
}

void b4Socket(int af, int type, int protocol)
{
	std::wostringstream wStringStream;

	iSockExpThread =  PIN_GetTid();
	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<"Thread="<<hex<<PIN_GetTid()
				<<DELIM<<"socket"
				<<DELIM<<"CALL"
				<<DELIM<<"af="<<hex<<af
				<<DELIM<<"type="<<hex<<type
				<<DELIM<<"protocol="<<hex<<protocol
				<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
}

void afterSocket(WINDOWS::SOCKET socket)
{
	std::wostringstream wStringStream;

	if(PIN_GetTid() != iSockExpThread)
		return;
	iSockExpThread = -1;

	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<"Thread="<<hex<<PIN_GetTid()
				<<DELIM<<"socket"
				<<DELIM<<"RETN"
				<<DELIM<<"Value="<<hex<<socket
				<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
	
}

WINDOWS::SOCKET jwSocket(CONTEXT *ctxt, AFUNPTR fpOrigin, int af, int type, int protocol)
{
	WINDOWS::SOCKET socket = 0;
	std::wostringstream wStringStream;

	wStringStream<<"Thread="<<hex<<PIN_GetTid()
				<<DELIM<<"socket"
				<<DELIM<<"CALL"
				<<DELIM<<"af="<<hex<<af
				<<DELIM<<"type="<<hex<<type
				<<DELIM<<"protocol="<<hex<<protocol
				<<dec<<endl;

	PIN_CallApplicationFunction(ctxt, PIN_ThreadId(), CALLINGSTD_STDCALL, fpOrigin,
		PIN_PARG(WINDOWS::SOCKET *), &socket, PIN_PARG(int), af, PIN_PARG(int), type, 
		PIN_PARG(int), protocol, PIN_PARG_END());
	

	GetLock(&logFileLock, PIN_GetTid());
	wLogFile<<wStringStream.str()
			<<"Thread="<<hex<<PIN_GetTid()
			<<DELIM<<"socket"
			<<DELIM<<"RETN"
			<<DELIM<<"Value="<<hex<<socket
			<<dec<<endl;
	wLogFile.flush();
	ReleaseLock(&logFileLock);
	//wStringStream.str(L"");
	return socket;
}