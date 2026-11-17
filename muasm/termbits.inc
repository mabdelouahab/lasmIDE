ifndef __ASM_GENERIC_TERMBITS_H
 __ASM_GENERIC_TERMBITS_H equ 1

;#include <linux/posix_types.h>

cc_t    TYPEDEF BYTE   ; typedef unsigned char	cc_t;
speed_t TYPEDEF qWORD ;typedef unsigned int	speed_t;
tcflag_t TYPEDEF qWORD ;typedef unsigned int	tcflag_t;
        setbit__ macro v,cst_
            OR  v ,cst_
        endm
        clearbit__ macro v,cst_
            AND  v ,-cst_
        endm

NCCS EQU 20 ;    NCCS 19
termios STRUCT  ;struct termios {
        c_iflag tcflag_t    0;	tcflag_t c_iflag;		; input mode flags */
        c_oflag tcflag_t    0  ;	tcflag_t c_oflag;		; output mode flags */
        c_cflag tcflag_t    0;	tcflag_t c_cflag;		; control mode flags */
        c_lflag tcflag_t    0;	tcflag_t c_lflag;		; local mode flags */
        c_line  cc_t        0;	cc_t c_line;			; line discipline */
        c_cc    cc_t NCCS DUP(0Eh);	cc_t c_cc[NCCS];		; control characters */
termios ENDS ;};
;
termios2 STRUCT
            termios     <>
            c_ispeed    speed_t 0    
            c_ospeed    speed_t 0    
termios2 ENDS
ktermios STRUCT
            termios2     <>
ktermios ENDS
;XFD_SETSIZE	EQU 512
;FD_SETSIZE  equ 	XFD_SETSIZE
NBBY	equ 8
NFDBITS equ (sizeof(fd_mask) * NBBY)
fd_mask TYPEDEF QWORD
howmany macro x,y
    EXITM<(((x)+((y)-1))/(y))>
endm
fd_setST STRUCT
        fds_bits   fd_mask howmany(FD_SETSIZE, NFDBITS) DUP(0)
fd_setST ENDS
;struct termios2 {
;	tcflag_t c_iflag;		; input mode flags */
;	tcflag_t c_oflag;		; output mode flags */
;	tcflag_t c_cflag;		; control mode flags */
;	tcflag_t c_lflag;		; local mode flags */
;	cc_t c_line;			; line discipline */
;	cc_t c_cc[NCCS];		; control characters */
;	speed_t c_ispeed;		; input speed */
;	speed_t c_ospeed;		; output speed */
;};
;
;struct ktermios {
;	tcflag_t c_iflag;		; input mode flags */
;	tcflag_t c_oflag;		; output mode flags */
;	tcflag_t c_cflag;		; control mode flags */
;	tcflag_t c_lflag;		; local mode flags */
;	cc_t c_line;			; line discipline */
;	cc_t c_cc[NCCS];		; control characters */
;	speed_t c_ispeed;		; input speed */
;	speed_t c_ospeed;		; output speed */
;};
;
tcgetattr PROTO fildes:QWORD,termios_p:QWORD
cfsetispeed PROTO :QWORD,:QWORD
cfsetospeed PROTO :QWORD,:QWORD      
tcsetattr   PROTO :QWORD,:QWORD,:QWORD  ;
.data
    _Opt termios    <>
.code
set_speed   PROC  SYSTEMV _fd:qword
    local fd:QWORD
   ; local _Opt:termios
    MOV fd,_fd
    invoke tcgetattr,fd,addr _Opt
    invoke printf, "set_speed:tcgetattr[%d]\n"    ,rax  

    invoke cfsetispeed,addr _Opt,B19200;B115200        ;B9600; ; 104560 ; 
    invoke cfsetospeed,addr _Opt,B19200      
    invoke tcsetattr,fd,TCSANOW, addr _Opt
    invoke printf, "set_speed:tcsetattr[%d]\n"    ,rax  
    RET
set_speed   ENDP
set_Parity  PROC  SYSTEMV _fd:qword
    local fd:QWORD
   ; local _Opt:termios
    MOV fd,_fd
    invoke tcgetattr,fd,addr _Opt
    invoke printf, "set_Parity:tcgetattr[%d]\n"    ,rax  
       clearbit__ t.c_cflag ,PARENB            ;tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
       clearbit__ t.c_cflag ,CSTOPB            ;tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
       setbit__   t.c_cflag ,_CS8              ;tty.c_cflag |= CS8; // 8 bits per byte (most common)
   ;    clearbit__ t.c_cflag ,CRTSCTS           ;tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    ;   setbit__   t.c_cflag ,CREAD or CLOCAL   ;tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)            
    ;   clearbit__ t.c_lflag,ICANON             ;tty.c_lflag &= ~ICANON;
   ;    clearbit__ t.c_lflag,_ECHO              ;tty.c_lflag &= ~ECHO; // Disable echo
   ;    clearbit__ t.c_lflag,ECHOE              ;tty.c_lflag &= ~ECHOE; // Disable erasure
    ;   clearbit__ t.c_lflag,ECHONL             ;tty.c_lflag &= ~ECHONL; // Disable new-line echo 
    ;   clearbit__ t.c_lflag,CRTSCTS
   ;    clearbit__ t.c_lflag,ISIG               ;tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
   ;    clearbit__ t.c_iflag,(IXON or IXOFF or IXANY)        ;tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl   
   ;    clearbit__ t.c_iflag,(IGNBRK or BRKINT or PARMRK or ISTRIP or INLCR or IGNCR or ICRNL);tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes        
   ;    clearbit__ t.c_oflag,OPOST              ;tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
   ;    clearbit__ t.c_oflag,ONLCR              ;tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed


    invoke tcsetattr,fd,TCSANOW, addr _Opt
    invoke printf, "set_Parity:tcsetattr[%d]\n"    ,rax  
    RET
set_Parity  ENDP
OpenSerial  PROC  SYSTEMV _dev:qword
    local fd:QWORD
    local dev:QWORD
    MOV dev,_dev

     invoke _open,"/dev/ttyUSB0", O_RDWR,0    ;OR O_NOCTTY OR O_NDELAY
    .if SQWORD PTR rax < 0
       invoke 	printf, "_open: Can't Open Serial Port {%s}Err:%d\n"   ,rax 
       MOV RAX,-1
    .else
        MOV fd,rax
        invoke set_speed    ,fd
        invoke set_Parity   ,fd
        MOV RAX,fd
    .endif
    RET
OpenSerial  ENDP
showt proc
 local adr_:qword
 local ind_:qword

 
 
        mov t4.c_iflag,-1
        invoke 	printf, "\nt4.c_iflag=%0Xh\n\n"  ,t4.c_iflag  
        invoke 	printf, "\nt= BYTE: "
        invoke 	printf, "\nt.c_iflag=%0Xh}\n"  ,t.c_iflag  
        invoke 	printf, "t.c_oflag=%0Xh}\n"  ,t.c_oflag  
        invoke 	printf, "t.c_cflag=%0Xh}\n"  ,t.c_cflag  
        invoke 	printf, "t.c_lflag=%0Xh}\n"  ,t.c_lflag  
        mov ind_,0;
       @@:
        inc ind_
        cmp ind_,20
        je @F
        LEA RCX,t.c_line
        DEC RCX
        ADD RCX,ind_
        XOR RAX,RAX
        MOV AL,Byte PTR [RCX]
            invoke 	printf, "t.c_line[%d]:%X\n"  ,ind_,rax
        jmp @B
      @@:
        invoke 	printf, "{t4.c_iflag%0Xh}\n"  ,t4.c_iflag  
        ret
 showt endp
;; c_cc characters */
    VINTR   EQU  0
    VQUIT    EQU  1
    VERASE    EQU  2
    VKILL    EQU  3
    VEOF    EQU  4
    VTIME   EQU   5
    VMIN    EQU  6
    VSWTC    EQU  7
    VSTART   EQU   8
    VSTOP    EQU  9
    VSUSP   EQU   10
    VEOL    EQU  11
    VREPRINT    EQU  12
    VDISCARD    EQU  13
    VWERASE    EQU  14
    VLNEXT    EQU  15
    VEOL2   EQU   16

; c_iflag bits */
    IGNBRK	EQU 0000001
    BRKINT	EQU 0000002
    IGNPAR	EQU 0000004
    ; DIFIND IN :unistd_64
;    PARMRK	EQU 0000010
;    INPCK	EQU 0000020
;    ISTRIP	EQU 0000040
;    INLCR	EQU 0000100
;    IGNCR	EQU 0000200
;    ICRNL	EQU 0000400
;    IUCLC	EQU 0001000
;    IXON	EQU 0002000
;    IXANY	EQU 0004000
;    IXOFF	EQU 0010000
;    IMAXBEL	EQU 0020000
;    IUTF8	EQU 0040000
;
; c_oflag bits */
    OPOST	EQU 0000001
    OLCUC	EQU 0000002
;    ONLCR	EQU 0000004
;    OCRNL	EQU 0000010
;    ONOCR	EQU 0000020
;    ONLRET	EQU 0000040
;    OFILL	EQU 0000100
;    OFDEL	EQU 0000200
    NLDLY	EQU 0000400
      NL0	EQU 0000000
      NL1	EQU 0000400
    CRDLY	EQU 0003000
      _CR0	EQU 0000000
      _CR1	EQU 0001000
      _CR2	EQU 0002000
      _CR3	EQU 0003000
    TABDLY	EQU 0014000
      TAB0	EQU 0000000
      TAB1	EQU 0004000
      TAB2	EQU 0010000
      TAB3	EQU 0014000
      XTABS	EQU 0014000
    BSDLY	EQU 0020000
      BS0	EQU 0000000
      BS1	EQU 0020000
    VTDLY	EQU 0040000
      VT0	EQU 0000000
      VT1	EQU 0040000
    FFDLY	EQU 0100000
      FF0	EQU 0000000
      FF1	EQU 0100000

; c_cflag bit meaning */
    CBAUD	EQU 0010017
     B0	EQU 0000000		; hang up */
     B50	EQU 0000001
     B75    	EQU 0000002
     B110	EQU 0000003
     B134	EQU 0000004
     B150	EQU 0000005
     B200	EQU 0000006
;     B300	EQU 0000007
;     B600	EQU 0000010
;     B1200	EQU 0000011
;     B1800	EQU 0000012
;     B2400	EQU 0000013
;     B4800	EQU 0000014
;     B9600	EQU 0000015
;     B19200	EQU 0000016
;     B38400	EQU 0000017
    EXTA	        EQU   B19200
    EXTB 	EQU B38400
;    CSIZE	EQU 0000060
      _CS5	EQU 0000000
      _CS6	EQU 0000020
      _CS7	EQU 0000040
      _CS8	EQU 0000060
;    CSTOPB	EQU 0000100
;    CREAD	EQU 0000200
;    PARENB	EQU 0000400
;    PARODD	EQU 0001000
;    HUPCL	EQU 0002000
;    CLOCAL	EQU 0004000
;    CBAUDEX	EQU 0010000
       BOTHER	EQU 0010000
;       B57600	EQU 0010001
;      B115200	EQU 0010002
;      B230400	EQU 0010003
;      B460800	EQU 0010004
;      B500000	EQU 0010005
;      B576000	EQU 0010006
;      B921600	EQU 0010007
;     B1000000	EQU 0010010
;     B1152000	EQU 0010011
;     B1500000	EQU 0010012
;     B2000000	EQU 0010013
;     B2500000	EQU 0010014
;     B3000000	EQU 0010015
;     B3500000	EQU 0010016
;     B4000000	EQU 0010017
;    CIBAUD	 	EQU 002003600000	; input baud rate */
    CMSPAR	 	EQU 010000000000	; mark or space (stick) parity */
    CRTSCTS	 	EQU 020000000000	; flow control */

    IBSHIFT		EQU   16		; Shift from CBAUD to CIBAUD */

; c_lflag bits */
    ISIG        	EQU 0000001
    ICANON	EQU 0000002
    XCASE	EQU 0000004
    _ECHO	        EQU 0000010
;    ECHOE	EQU 0000020
;    ECHOK	EQU 0000040
;    ECHONL	EQU 0000100
;    NOFLSH	EQU 0000200
;    TOSTOP	EQU 0000400
;    ECHOCTL	EQU 0001000
;    ECHOPRT	EQU 0002000
;    ECHOKE	EQU 0004000
;    FLUSHO	EQU 0010000
;    PENDIN	EQU 0040000
;    IEXTEN	EQU 0100000
;    EXTPROC	EQU 0200000

; tcflow() and TCXONC use these */
	TCOOFF		EQU 0
	TCOON	EQU 1
	TCIOFF	EQU 2
	TCION	EQU 3

; tcflush() and TCFLSH use these */
	TCIFLUSH	EQU 0
	TCOFLUSH		EQU 1
	TCIOFLUSH	EQU 2

; tcsetattr uses these */
	TCSANOW		EQU 0
	TCSADRAIN	EQU 1
	TCSAFLUSH	EQU 2

endif ; __ASM_GENERIC_TERMBITS_H */
