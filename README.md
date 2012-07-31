A pin tool for behavioral analysis.
Its slightly updated version of original tool presented at Nullcon 2011.

Current Pintool features Logging calls to
  * Kernel32.dll
    * CreateFile*
    * ReadFileEx
    * WriteFileEx
    * SetFilePointer
    * CloseHandle
  * ADVAPI32.dll
    * Reg* 
  * WS2_32.dll
    * socket
    * connect

log_parser.rb parses the log created by pintool to create xml or html report (not-completed).


