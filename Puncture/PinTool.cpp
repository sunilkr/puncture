#include "pintool.h"
#include <string.h>

std::wofstream		wLogFile;
std::wostringstream wStringStream;
int	iExpect[MAX_THREAD];

int main(int argc, char *argv[])
{
	PIN_InitSymbols();
	if(PIN_Init(argc,argv))
		return -1;

	wLogFile.open("LogFile.txt");
	wLogFile<<hex;
	wLogFile.setf(ios::showbase);

	IMG_AddInstrumentFunction(Image, 0);
	PIN_AddFiniFunction(Fini,0);

	PIN_StartProgram();
	return 0;
}

void Image(IMG img, void *v)
{
	wLogFile<<"Image"<<DELIM<<IMG_Name(img).c_str()
		<<DELIM<<"Base@"<<hex<<IMG_StartAddress(img)
		<<DELIM<<"MappedSize@"<<IMG_SizeMapped(img)
		<<DELIM<<"EntryPoint@"<<IMG_Entry(img)<<endl;
	
	const char *lpImageName = StripPath(IMG_Name(img).c_str());

	//Instrument Registry API
	if(!_strnicmp(lpImageName, "ADVAPI32.DLL",15))
	{
//		wLogFile<<"Image"<<DELIM<<IMG_Name(img).c_str()<<endl;
		Image_ADVAPI32(img,v);
	}
	//Instrument File API
	else if(!_strnicmp(lpImageName, "Kernel32.dll",15))
	{
//		wLogFile<<"In "<<IMG_Name(img).c_str()<<endl;
		Image_Kernel32(img, v);
	}
	// Instrument Socket API
	else if(!_strnicmp(lpImageName, "WS2_32.dll",15))
	{
//		wLogFile<<"In "<<IMG_Name(img).c_str()<<endl;
		Image_WS2_32(img, v);
	}  
}

void Fini(INT32 code, void *v)
{
	wLogFile<<"[*]Done"<<endl;
	wLogFile.close();
}

const char* StripPath(const char *path)
{
	const char *file = strrchr(path, '\\');
	if(file)
		return file+1;
	return file;
}
