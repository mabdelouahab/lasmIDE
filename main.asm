
include main.inc
.code

 	.proc main  ,largc:DWORD, largv:QWORD
 	.Shadow
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
	.endp

	end 
	