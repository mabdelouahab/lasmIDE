__Development_Phase	EQU 1
include try.inc

include main.inc
TryRuntime
.code

 	.proc main  ,largc:DWORD, largv:QWORD
 	.Shadow
		TRY
		invoke gInit
		
			.if largc > 1 
				mov rax,largv
				add rax,sizeof gpointer
				mov rax,[rax]
				mov Arg_Project,rax 
			.endif
			invoke InitMainWindow                
			invoke gtk_main
		CATCH
			call TryDump
		ENDTRY	
		xor rax,rax
		ret

invoke printf, "%d", fr_i16(iii)
invoke printf, "%d", fr_i8( bb ), dword ptr [rax]
invoke printf, "%f", fr_r4( rr4 ), fr_r8( rr8 )
invoke printf, fr_r8(rr8), rdi


.data

	rr8 REAL8 1.5
	iii  WORD 7
	bb  BYTE  5
	rr4 REAL4 2.5   
	
.code     

 	.endp
 
;%echo nbinvoke_ @CatStr(%nbinvoke)
	end 
	include		include/invoke.inc
	include 	./muasm/libc.inc
t_i6	PROTO	:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD 
t_i7	PROTO	:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD 
t_i8	PROTO	:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD 
t_i9	PROTO	:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD ,:QWORD 
t_d8	PROTO	:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 
t_d9	PROTO	:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 
t_d10	PROTO	:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 ,:REAL8 
t_mix	PROTO	:QWORD ,:REAL8 ,:QWORD ,:REAL8 ,:QWORD ,:REAL8 ,:QWORD ,:REAL8 , :QWORD ,:REAL8 ,:QWORD ,:REAL8 ,:QWORD ,:REAL8 ,:REAL8 ,:REAL8 
t_va	PROTO	:DWORD , :VARARG
t_sz	PROTO	:BYTE  ,:WORD  ,:DWORD ,:QWORD ,:REAL4 ,:REAL8 
t_str	PROTO	:PTR	,:PTR

.data
	fails	dd 0
	r8v	real8 4.5
	r4v	real4 5.5
	b1	db 1
	w2	dw 2
	y db "a,b!c<d>",0
.code
main proc

	push rbp

		invoke t_i6, 1,2,3,4,5,6
	add fails,eax
	invoke t_i7, 1,2,3,4,5,6,7
	add fails,eax
	invoke t_i8, 1,2,3,4,5,6,7,8
	add fails,eax
	invoke t_i9, 1,2,3,4,5,6,7,8,9
	add fails,eax
	invoke t_d8, 1.5,2.5,3.5,r8v,5.5,6.5,7.5,8.5
	add fails,eax
	invoke t_d9, 1.5,2.5,3.5,r8v,5.5,6.5,7.5,8.5,9.5
	add fails,eax
	invoke t_d10, 1.5,2.5,3.5,r8v,5.5,6.5,7.5,8.5,9.5,10.5
	add fails,eax
	invoke t_mix, 1,1.5,2,2.5,3,3.5,4,r8v,5,5.5,6,6.5,7,7,"ggg" ,8.5,9.5
	add fails,eax
	invoke t_va, 3, 1.5,2.5,3.5
	add fails,eax
	invoke t_sz, b1,w2,3,4,r4v,6.5
	add fails,eax
	;invoke t_str, "a,bc<d>", "\n"
	;add fails,eax
	invoke printf,".\t\ta,bc<d>\n\b%d", 12,"\n", 1,1.5,2,2.5,3,3.5,4,r8v,5,5.5,6,6.5,7,7,"ggg" ,8.5,9.5
	
 	invoke printf,".\t\ta,bcd\n\b%d", 12,"\n"
	mov eax,fails        ; الصفر = نجاح
	pop rbp
	ret
main endp
	end 
	

	
	
	
		