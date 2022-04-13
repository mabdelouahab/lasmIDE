.CODE
GetTickCountMS PROC
	LOCAL tspec:timespec
	;LOCAL __ms:QWORD
	invoke clock_gettime, CLOCK_MONOTONIC, ADDR tspec
	cvtsi2ss xmm0,tspec.tv_nsec
	divss xmm0,FP4(1000000.0)
	cvttss2si rax,xmm0
	mov RCX,rax
	mov rax,tspec.tv_sec
	imul rax,1000
	add rax,RCX
ret
GetTickCountMS ENDP
GetTickCountNS PROC
	LOCAL tspec:timespec
	;LOCAL __ms:QWORD
	invoke clock_gettime, CLOCK_MONOTONIC, ADDR tspec
	cvtsi2ss xmm0,tspec.tv_nsec
	;divss xmm0,FP4(1000000.0)
	cvttss2si rax,xmm0
	mov RCX,rax
	mov rax,tspec.tv_sec
	imul rax,1000
	add rax,RCX
ret
GetTickCountNS ENDP
;----------------------------------------Timer
.DATA
	_Timer_tspec	timespec	<>
	_Timer_start_MS	QWORD		0
	_Timer_N_to_M	REAL4		1000000.0
.CODE
StartTimer 	PROC

	invoke 	  clock_gettime, CLOCK_MONOTONIC, ADDR _Timer_tspec
	cvtsi2ss  xmm0,_Timer_tspec.tv_nsec
	divss     xmm0,_Timer_N_to_M
	cvttss2si rax,xmm0
	mov 	  _Timer_start_MS,rax
	mov 	  rax,_Timer_tspec.tv_sec
	imul 	  rax,1000
	add 	  _Timer_start_MS,rax
	ret
StartTimer 	ENDP
EndTimer 	PROC
	invoke    clock_gettime, CLOCK_MONOTONIC, ADDR _Timer_tspec
	cvtsi2ss  xmm0,_Timer_tspec.tv_nsec
	divss 	  xmm0,_Timer_N_to_M
	cvttss2si rax,xmm0
	mov 	  rcx,_Timer_tspec.tv_sec
	imul 	  rcx,1000
	add 	  rax,rcx
	sub 	  rax,_Timer_start_MS
	ret
EndTimer 	ENDP

.data
	szTempBCD	db	18 dup (0)
.code
FloatToBCD	PROC	public  
	ret
    sub rsp, 16

	; The fbstp instruction converts the top of the stack to a
	; packed BCD form in ten bytes, with two digits per byte.  The top 
	; byte has the sign, which we ignore.

    ;fbstp dword ptr [rsp]

	; Now we need to unpack the BCD to ASCII.

    mov rsi, rsp
    add rsi,8
    lea rdi, szTempBCD
    mov ecx, 9

    .REPEAT
	mov al, [rsi]          ; xxxx xxxx AAAA BBBB
	dec rsi
	rol ax, 12             ; BBBB xxxx xxxx AAAA
	rol ah, 4              ; xxxx BBBB xxxx AAAA
	and ax, 0f0fh          ; 0000 BBBB 0000 AAAA
	add ax, 3030h          ; 3B3A
	mov [rdi], ax
	add rdi, 2
	dec ecx
    .UNTIL ZERO?

    add rsp, 16
    ret

FloatToBCD	ENDP
.data

temp_bcd     dt   ?
szdecimal    db   32 dup(0)

.code

bcd2a PROC

   push  1000000000            ;use the stack as storage for this value
   fimul dword ptr[rsp] ;converts 2 decimal places as 2 more integer digits
   fbstp temp_bcd       ;store the packed BCD integer value
   pop  rax             ;clean the stack of the pushed 100 

; rSI will be used for pointing to the packed BCD
; rDI will be used for pointing to the decimal string

   push rsi
   push rdi
   lea  rsi,temp_bcd+9  ;point to the most significant byte
   lea  rdi,szdecimal   ;point to the start of the decimal string buffer
   xor  eax,eax
   fwait                ;to ascertain that the transfer of the
                        ;packed BCD is completed

   mov  al,[rsi]        ;get the byte with the sign code
   dec  rsi             ;decrement to next most significant byte
   or   al,al           ;for checking the sign bit
   jns  @F              ;jump if no sign bit
   mov  al,"-"          ;the value is negative
   stosb                ;insert the negative sign

@@:

; The next 8 bytes (in this example) will contain the integer digits
; and the least significant byte will then contain the 2 decimal digits.
; No leading 0 will be included in the integer portion
; unless it would be the only integer digit.

   mov  ecx,8           ;number of bytes to process for integer digits

@@:

   mov  al,[rsi]        ;get the next byte
   dec  rsi             ;adjust the pointer to the next one
   or   al,al           ;for checking if it is 0
   jnz  @F              ;the starting integer digit is now in AL
   dec  ecx             ;adjust the counter of integer bytes
   jnz  @B              ;continue searching for the first integer digit

; If the loop terminates with ECX=0, the integer portion would be 0.
; A "0" character must be inserted before processing the decimal digits

   mov  al,"0"          ;the ASCII 0
   stosb                ;insert it
   mov  al,[rsi]        ;get the byte containing the decimal digits
   jmp  decimal_digits

@@:

; The first integer byte must be checked to determine
; if it contains 1 or 2 integer digits

   test al,0f0h         ;test if the H.O. nibble contains a digit
   jz   int_digit2      ;if not, process only the L.O. nibble

int_digit1:
   ror  ax,4            ;puts the H.O. nibble in the L.O. nibble position
                        ;and saves the L.O. nibble in AH
   add  al,30h          ;convert it to ASCII character
   stosb                ;store this character
   shr  ax,12           ;restores the L.O. nibble in AL
                        ;and also resets the other bits of AX

int_digit2:
   add  al,30h          ;convert it to ASCII character
   stosb                ;store this character
   mov  al,[rsi]        ;get next byte
   dec  rsi             ;adjust the pointer to the next one
   dec  ecx             ;adjust the counter of integer bytes
   jnz  int_digit1      ;continue processing the integer bytes

decimal_digits:
   mov  byte ptr [rdi],"." ;insert the preferred decimal delimiter
   inc  rdi

; If more than 2 decimal digits are required, a counter would be needed
; to process the necessary bytes.
; Also, if the number of required decimal digits is not even, the code
; would have to be altered to insert the decimal delimiter at the
; proper location.

   ror  ax,4            ;puts the H.O. nibble in the L.O. nibble position
                        ;and saves the L.O. nibble in AH
   add  al,30h          ;convert it to ASCII character
   stosb                ;store this character
   shr  ax,12           ;restores the L.O. nibble in AL
                        ;and also resets the other bits of AX
   add  al,30h          ;convert it to ASCII character
   stosw                ;store this character + the terminating 0

   pop rdi
   pop rsi
   ret

bcd2a ENDP



