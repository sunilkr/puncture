#include "pintool.h"

extern std::wofstream		wLogFile;
extern std::wostringstream	wStringStream;
int iExpectedThread = -1;
int iSockExpThread = -1;

int jwConnect(CONTEXT *ctxt, AFUNPTR fpOrigin, WINDOWS::SOCKET socket, WINDOWS::PSOCKADDR pSocketName, int iNameLen)
{
	int iResult = 0;
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
	
	wLogFile<<wStringStream.str();
	wLogFile.flush();
	wStringStream.str(L"");	
	return iResult;
}

void b4Connect(WINDOWS::SOCKET socket, WINDOWS::PSOCKADDR pSocketName)
{
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
	wLogFile<<wStringStream.str()<<DELIM<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");	
}
void afterConnect(int iResult)
{
	if(iExpectedThread != PIN_GetTid())
		return;

	iExpectedThread = -1;  //TODO:: Resolve Reace Condition
	wLogFile<<"Thread="<<hex<<PIN_GetTid()
				<<DELIM<<"connect"
				<<DELIM<<"RETN"
				<<DELIM<<"Value="<<hex<<iResult
				<<DELIM<<dec<<endl;
	wLogFile.flush();
}

void b4Socket(int af, int type, int protocol)
{
	iSockExpThread =  PIN_GetTid();

	wLogFile<<"Thread="<<hex<<PIN_GetTid()
				<<DELIM<<"socket"
				<<DELIM<<"CALL"
				<<DELIM<<"af="<<hex<<af
				<<DELIM<<"type="<<hex<<type
				<<DELIM<<"protocol="<<hex<<protocol
				<<DELIM<<dec<<endl;
	wLogFile.flush();
}

void afterSocket(WINDOWS::SOCKET socket)
{
	if(PIN_GetTid() != iSockExpThread)
		return;
	iSockExpThread = -1;

	wLogFile<<"Thread="<<hex<<PIN_GetTid()
				<<DELIM<<"socket"
				<<DELIM<<"RETN"
				<<DELIM<<"Value="<<hex<<socket
				<<DELIM<<dec<<endl;
	wLogFile.flush();
}

WINDOWS::SOCKET jwSocket(CONTEXT *ctxt, AFUNPTR fpOrigin, int af, int type, int protocol)
{
	WINDOWS::SOCKET socket = 0;
	wLogFile<<"Thread="<<hex<<PIN_GetTid()
				<<DELIM<<"socket"
				<<DELIM<<"CALL"
				<<DELIM<<"af="<<hex<<af
				<<DELIM<<"type="<<hex<<type
				<<DELIM<<"protocol="<<hex<<protocol
				<<DELIM<<dec<<endl;
	PIN_CallApplicationFunction(ctxt, PIN_ThreadId(), CALLINGSTD_STDCALL, fpOrigin,
		PIN_PARG(WINDOWS::SOCKET *), &socket, PIN_PARG(int), af, PIN_PARG(int), type, 
		PIN_PARG(int), protocol, PIN_PARG_END());
	
	wLogFile<<wStringStream.str()
			<<"Thread="<<hex<<PIN_GetTid()
			<<DELIM<<"socket"
			<<DELIM<<"RETN"
			<<DELIM<<"Value="<<hex<<socket
			<<DELIM<<dec<<endl;
	wLogFile.flush();
	wStringStream.str(L"");
	return socket;
}