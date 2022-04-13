
; Declare GLIBC prototypes (with output format -elf64 SYSTEMV ABI is assumed as the default).
;********************************************************************************************
	include 	unistd_64.inc

malloc PROTO :QWORD
free   PROTO memPtr:QWORD
printf PROTO pString:PTR, args:VARARG
sprintf PROTO pString:PTR, args:VARARG
exit   PROTO exitcode:DWORD
remove    PROTO fn:DWORD
close  PROTO fd:DWORD
memset PROTO :vararg
memcpy PROTO :vararg
__errno_location PROTO 
__h_errno_location PROTO


CLOCK_REALTIME	= 0
CLOCK_MONOTONIC	= 1
TIMER_ABSTIME	= 1

time_t TYPEDEF QWORD

timespec STRUCT 8
	tv_sec  dd ?
	;dd ?
	tv_nsec dq ?
timespec ENDS
.code 
	sleepsp	proc milisec:qword
		local req:timespec

		mov rax,milisec
		mov rcx,1000
		xor rdx,rdx
		div rcx
		mov req.tv_sec ,eax;
		mov req.tv_nsec,0
		invoke _nanosleep,addr req,0
		ret
	sleepsp	endp


clock_gettime PROTO clockid_t:DWORD, pTimeSpec:PTR


