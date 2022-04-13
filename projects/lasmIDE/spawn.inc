    vte_terminal_new                proto :vararg
    vte_terminal_spawn_async        proto :vararg
    vte_terminal_spawn_sync         proto :vararg
	vte_terminal_set_mouse_autohide proto :vararg
    vte_terminal_feed				proto :vararg

  
    
.code
	showvect proc _v__:gpointer
		local v__:gpointer
		local v__ind:gpointer
		local v__i:gpointer
		mov v__,_v__
		mov v__ind,_v__
		mov v__i,0
		.if v__ind
		    @@:
		    mov rax,v__ind
		    .if gpointer ptr [rax]
		       invoke printf,str$(<13,10,"arg[%d]={%s}">),v__i ,gpointer ptr [rax]
		       add v__ind,sizeof gpointer
		       inc v__i
		       jmp @B 
		    .endif
		    invoke printf,str$(<13,10,"arg final ...">)
		.endif
		ret
	showvect endp     
	appstrv proc _v__:gpointer,_s__:gpointer
		local v__:gpointer
		local v__ind:gpointer
		local v__i:gpointer
		local s__:gpointer
		mov s__,_s__
		mov v__,_v__
		mov v__ind,_v__
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
	appstrv endp     
    
    Terminal_PrintV macro str___@
     	invoke vte_terminal_feed,WTerminal,str___@,-1;@SizeStr(str___@)
    endm
    Terminal_Print_Line macro str___@
     	invoke vte_terminal_feed,WTerminal,str$(<13,10,str___@>),-1;@SizeStr(str___@)
    endm
    Terminal_Print_LineL macro str___@
     	invoke vte_terminal_feed,WTerminal,str$(<13,10,str___@,13,10>),-1;@SizeStr(str___@)+4
    endm
    Terminal_Print macro str___@
     	invoke vte_terminal_feed,WTerminal,str$(str___@),-1;@SizeStr(str___@)-2
    endm
    .DATA
    	spawn_run_handler_id		gulong	0	
    .CODE
    spawn_run PROC _spawn_launch:gpointer,_spawn_function:QWORD,_exited_function:QWORD,_H_function:QWORD
        local spawn_launch:gpointer
        local spawn_function:gpointer
        local exited_function:gpointer
        local io_channelOut:gpointer
        local H_function:gpointer
        local error:gpointer

        mov spawn_launch,_spawn_launch
        mov spawn_function,_spawn_function
        mov exited_function,_exited_function
        mov H_function,_H_function
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
        ret
    spawn_run ENDP 

    ;   how to use spawn_run_ex2:
    ;   .data
    ;       argstr01    db  'gcc -o out main.o ',0
    ;       argstr02    db  'pkg-config --cflags --libs gtk+-3.0',0
    ;       argstr03    db  'pkg-config --cflags --libs cairo',0
    ;       argv        gpointer argstr02,argstr03,0
    ;   .code
    ;       invoke spawn_run_ex2,addr argstr01,addr argv,addr callback_stdout_wach,addr callback_stderr_wach
    ;       mov exitcode,rax
    spawn_run_ex2 PROC SYSTEMV _spawn_launch:gpointer,_spawn_launch_opt:gpointer,_spawn_function:gpointer,_spawnerr_function:gpointer, _H_function:gpointer
        local spawn_launch:gpointer
        local spawn_launch_opt:gpointer
        local pspawn_launch_opt:gpointer
        local spawn_function:gpointer
        local spawnerr_function:gpointer
        local H_function:gpointer
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

        mov spawn_launch,_spawn_launch
        mov spawn_launch_opt,_spawn_launch_opt
        mov spawn_function,_spawn_function
        mov spawnerr_function,_spawnerr_function
        mov H_function,_H_function
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
    spawn_run_ex2 ENDP
