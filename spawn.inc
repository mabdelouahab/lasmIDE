	.code
	IF  @Platform EQ ELF64
		vte_terminal_new                proto :vararg
		vte_terminal_spawn_async        proto :vararg
		vte_terminal_spawn_sync         proto :vararg
		vte_terminal_set_mouse_autohide proto :vararg
		vte_terminal_feed				proto :vararg
 	ENDIF

  
    
.code
   .proc appstrv , v__:gpointer,s__:gpointer
		local v__ind:gpointer
		local v__i:gpointer
 	.shadow
		m2m v__ind,v__
		mov v__i,0
 
		xor rax,rax
		.if v__ind
		    @@:
		    mov rcx,v__ind
		    .if gpointer ptr [rcx]
		       add v__ind,sizeof gpointer
		       inc v__i
		       jmp @B 
		    .endif
		.endif
		.if	v__i
			add v__i,2
			mov rax,v__i
			mov rcx,sizeof gpointer
			mul rcx
			invoke g_malloc,rax
			mov rdx,rax
			mov rcx,v__
		    @@:
		    .if gpointer ptr [rcx]	
		    	mov r10,gpointer ptr [rcx]	    	
		    	mov gpointer ptr [rax],r10	    	
		       add rcx,sizeof gpointer
		       add rax,sizeof gpointer
		       jmp @B 
		    .endif
	    	mov r10,s__	    	
	    	mov gpointer ptr [rax],r10	
	    	add rax,sizeof gpointer   
	    	mov gpointer ptr [rax],0 
	    	mov rax,rdx	
		.else
			xor rax,rax
		.endif
		ret
	.endp 
	    
    
	.DATA
    	spawn_run_handler_id		gulong	0	
    .CODE
IF 		@Platform EQ 1	;	Win64
    .proc spawn_run , spawn_launch:gpointer,spawn_function:QWORD,exited_function:QWORD,H_function:QWORD
        local io_channelOut:gpointer
        local error:gpointer
	.shadow
     ;   @@:
	;	.if m_bRunThread
	;		jmp @B
	;	.endif
		.if	spawn_function
			m2m m_lpProcessStartedCallBack,spawn_function
		.endif	
		.if	exited_function
			m2m m_lpProcessExitedCallBack,exited_function 
		.endif	
		mov rax,H_function
		w_terminal_StartChildProcess(spawn_launch,eax)
	.endp

    .proc spawn_run_ex2 ,spawn_launch:gpointer,spawn_launch_opt:gpointer,spawn_function:gpointer,spawnerr_function:gpointer, H_function:gpointer
    .shadow
        .if spawn_launch==0
            ret
        .endif
         @@:
        .if spawn_launch_opt
		    w_terminal_Init_Output_From_StdOut()
		    w_terminal_Get_Output_From_StdOut(spawn_launch)
		    spawn_launch_optExLoop:
		        mov rax,spawn_launch_opt
		        mov rax,gpointer ptr [rax]
		        .if rax
		        	.if byte ptr [rax]
			            ;-----------------------------------------------------------
			            w_terminal_Add_Space_To_Buf_StdOut()
			            w_terminal_LaunchAndGetOutput(rax)
			            ;--------------------------------------------------------------                             
		        	.endif  
			        add spawn_launch_opt,sizeof gpointer
			        jmp spawn_launch_optExLoop
		        .endif  
            @@:
			.if m_bRunThread
				jmp @B
			.endif
			w_terminal_Initialisation()
			spawn_run(addr w_terminal_lastOutputStdOut,spawn_function,spawnerr_function,H_function)       
        .else
        	w_terminal_Initialisation()
        	spawn_run(spawn_launch,spawn_function,spawnerr_function,H_function) 
        .endif
    .endp 

ELSEIF 	@Platform EQ 3	;	ELF64
		Terminal_PrintV macro str___@
		 	invoke vte_terminal_feed,WTerminal,str___@,-1   	
		endm
		Terminal_Print_Line macro str___@
		 	invoke vte_terminal_feed,WTerminal,str$(<13,10,str___@>),-1 
		endm
		Terminal_Print_LineL macro str___@
		 	invoke vte_terminal_feed,WTerminal,str$(<13,10,str___@,13,10>),-1 
		endm
		Terminal_Print macro str___@
		 	invoke vte_terminal_feed,WTerminal,str$(str___@),-1 
		endm


    .proc spawn_run , spawn_launch:gpointer,spawn_function:QWORD,exited_function:QWORD,H_function:QWORD
        local io_channelOut:gpointer
        local error:gpointer
	.shadow
		    mov error,0
		    mov spawn_run_handler_id,0
			.if exited_function 
				.if H_function
					invoke g_signal_connect_data,WTerminal ,str$("child-exited"),exited_function,0,0,0
					mov rcx,H_function
					mov gpointer ptr [rcx],rax
				.endif
			.endif

			mov WTerminal_child_pid,0
		  ;  invoke vte_terminal_spawn_sync ,WTerminal,0,0,spawn_launch,0,G_SPAWN_SEARCH_PATH or G_SPAWN_DO_NOT_REAP_CHILD,\
		  ;  								0,0,addr WTerminal_child_pid,0,  addr error  
		    invoke vte_terminal_spawn_async,WTerminal,0,0,spawn_launch,0,G_SPAWN_SEARCH_PATH or G_SPAWN_DO_NOT_REAP_CHILD,\
		    								0,0,0,-1,0,spawn_function,0			 		
    .endp 
  
    ;   how to use spawn_run_ex2:
    ;   .data
    ;       argstr01    db  'gcc -o out main.o ',0
    ;       argstr02    db  'pkg-config --cflags --libs gtk+-3.0',0
    ;       argstr03    db  'pkg-config --cflags --libs cairo',0
    ;       argv        gpointer argstr02,argstr03,0
    ;   .code
    ;       invoke spawn_run_ex2,addr argstr01,addr argv,addr callback_stdout_wach,addr callback_stderr_wach
    ;       mov exitcode,rax
    .proc spawn_run_ex2 ,spawn_launch:gpointer,spawn_launch_opt:gpointer,spawn_function:gpointer,spawnerr_function:gpointer, H_function:gpointer
        local pspawn_launch_opt:gpointer
        local argcp:gpointer
        local argvp:gpointer
        local argcpopt:gpointer
        local argvpopt:gpointer
        local argcpt:gpointer
        local argvpt:gpointer
        local argvects:gpointer
        local argvectsindex:gpointer
        local argvptindex:gpointer
        local error:gpointer
        local standard_output:gpointer
        local standard_error:gpointer
        local exit_status:gpointer
        local retv:gpointer
        local errstr:gpointer

    .shadow
        .if spawn_launch==0
            ret
        .endif
        mov argcp,0
        mov argcpopt,0
        mov argcpt,0
        mov error,0

        invoke g_shell_parse_argv,spawn_launch,addr argcp,addr argvp,addr error
        .if rax==0
            mov rax,error
            invoke printf,str$(<13,10,"g_shell_parse_argv error[%d]:{%s}">),QWORD PTR [rax],QWORD PTR [rax+8]
            xor rax,rax
            ret        
        .endif
        .if argcp ==0
            ret
        .endif        
        invoke g_malloc,2048
        mov argvpt,rax
        mov argvptindex,rax
        
        mov rcx,argvp
        @@:
		    mov rdx,gpointer ptr [rcx]
		    mov gpointer ptr [rax],rdx
		    add rcx,sizeof gpointer
		    add rax,sizeof gpointer
		    dec argcp
		    cmp argcp,0
        jne @B

        mov gpointer ptr [rax],0
        mov argvptindex,rax   
        .if spawn_launch_opt
            invoke g_malloc,16*(sizeof gpointer)
            mov argvects,rax
            mov argvectsindex,rax
            mov gpointer ptr [rax],0
        spawn_launch_optExLoop:
            mov rax,spawn_launch_opt
            mov rax,gpointer ptr [rax]
            .if rax
                mov pspawn_launch_opt,rax
                    ;-----------------------------------------------------------
                    mov error,0
                    mov standard_output,0
                    invoke g_spawn_command_line_sync,pspawn_launch_opt,addr standard_output,addr standard_error,addr exit_status,addr error
                    .if rax==0
                        mov rax,error
                        mov rcx,QWORD PTR [rax+8]
                        mov errstr,rcx
                       invoke printf,str$(<13,10,"g_spawn_command_line_sync error[%d]:{%s}">),QWORD PTR [rax],errstr
                       invoke vte_terminal_feed,WTerminal,errstr,-1 
                        xor rax,rax
                        ret        
                    .endif 
                    mov rax,standard_error
                    .if byte ptr [rax]
						invoke vte_terminal_feed,WTerminal,str$(<13,10,"OPT ERR:">),-1                    	
						invoke vte_terminal_feed,WTerminal,standard_error,-1 
                    .endif
                    mov error,0
                    invoke g_shell_parse_argv,standard_output,addr argcpopt,addr argvpopt,addr error
                    .if rax==0
                        mov rax,error
                         mov rcx,QWORD PTR [rax+8]
                        mov errstr,rcx
                       invoke vte_terminal_feed,WTerminal,str$(<13,10,"OPT ERR:">),-1 
                       invoke vte_terminal_feed,WTerminal,errstr,-1 
                       xor rax,rax
                        ret        
                    .endif
                    mov rcx,argvpopt
                    mov rax,argvectsindex
                    mov gpointer ptr [rax],rcx
                    mov gpointer ptr [rax+sizeof gpointer],0
                    add argvectsindex,sizeof gpointer
                    mov rax,argvptindex
                    .if argcpopt
                        mov rcx,argvpopt
                        @@:
                        mov rdx,gpointer ptr [rcx]
                        mov gpointer ptr [rax],rdx
                        add rcx,sizeof gpointer
                        add rax,sizeof gpointer
                        dec argcpopt
                        cmp argcpopt,0
                        jne @B
                    .endif
                    mov gpointer ptr [rax],0
                    mov argvptindex,rax
                    ;--------------------------------------------------------------                             
                add spawn_launch_opt,sizeof gpointer
                jmp spawn_launch_optExLoop
            .endif  
            mov retv,rv( spawn_run,argvpt ,spawn_function,spawnerr_function,H_function)
            mov rax,argvects
            mov argvectsindex,rax            
            @@:
            mov rax,argvectsindex
            mov rax,gpointer ptr [rax]
            .if rax
                invoke g_strfreev,rax                                      
                add argvectsindex,sizeof gpointer
                jmp @B
            .endif     
            invoke g_free,argvects
         .else
            mov retv,rv( spawn_run,argvpt ,spawn_function,spawnerr_function,H_function)
        .endif                
        invoke g_free,argvpt
        mov rax,retv
        ret 
    .endp

ENDIF