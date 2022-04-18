include main.inc
.code
 
	main PROC SYSTEMV      _argc:DWORD, _argv:QWORD 
		local largc:DWORD
		local  largv:QWORD   
		mov  largc,_argc    
		mov  largv,_argv   
		invoke gInit
		.if largc > 1 
			mov rax,largv
			add rax,sizeof gpointer
			mov rax,[rax]
			mov Arg_Project,rax 
		.endif
		invoke InitMainWindow                
		invoke gtk_main
		xor rax,rax
		ret
	main ENDP
	end 
	