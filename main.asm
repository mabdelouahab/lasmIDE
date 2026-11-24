__Development_Phase	EQU 1

include main.inc
TryRuntime
.code

 	.proc main  ,largc:DWORD, largv:QWORD
 	.Shadow
 		invoke TryInit
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
 	.endp
end 
	