
    .code
    .proc split_to_build , _s:gpointer
    .shadow
        invoke g_strdup,_s
        mov rdx,rax
        xor rcx,rcx 
        @@:
            .if byte ptr [rdx]=="."
                mov byte ptr [rdx],0
                ret
            .endif
            inc rdx
            CMP byte ptr [rdx],0
            jne @B
            .if rcx
                mov byte ptr [rcx],0
            .endif
        ret
    .endp
    .proc get_o_name , _s:gpointer
        local _ssplit:gpointer
    .shadow
        mov _ssplit,rv(split_to_build,_s)
	IF 		@Platform EQ 1	;	Win64
		invoke g_strconcat,_ssplit,".obj",0
	ELSEIF 	@Platform EQ 3	;	ELF64
		invoke g_strconcat,_ssplit,".o",0	
 	ENDIF    
        push rax
        invoke g_free,_ssplit
        pop rax
        ret                     
    .endp
    .data
        replace_variable_buffer    db  1024 dup(0)
    .code
    Files_Get_OFile_From_Name proto :gpointer
    ;$SRC : Source, input file,source code,project main file
    ;$EXE : Output executable, Output library
    ;$OBJ : Object file
    ;$DIR : Project path
    .proc replace_variable_with_value_str , __s:gpointer      
        local r_@SRC:gpointer
        local r_@EXE:gpointer
        local r_@OBJ:gpointer
        local r_@DIR:gpointer
        local lofile:gpointer        
    .shadow
        m2m r_@SRC,Current_Prj_MainFile
        m2m r_@EXE,Current_Prj_Name
        mov r_@OBJ,rv(get_o_name,r_@SRC)
        m2m r_@DIR,Current_Prj_Path
        lea rcx,replace_variable_buffer
        mov rdx,__s
        replace_variable@B:
            .if byte ptr [rdx]
                .if byte ptr [rdx]=="$"
                   .if     dword ptr [rdx]== 043525324h;$SRC
                        add rdx,4
                        push rdx
                        mov rdx,r_@SRC
                        replace_variableSRCNext:
                        .if byte ptr [rdx]
                            mov al,byte ptr [rdx]
                            mov byte ptr [rcx],al                    
                            inc rdx
                            inc rcx
                            jmp replace_variableSRCNext
                        .else
                            pop rdx
                            jmp replace_variable@B
                        .endif                        
                    .elseif dword ptr [rdx]== 045584524h;$EXE            
                        add rdx,4
                        push rdx
                        mov rdx,r_@EXE
                        replace_variableEXENext:
                        .if byte ptr [rdx]
                            mov al,byte ptr [rdx]
                            mov byte ptr [rcx],al                    
                            inc rdx
                            inc rcx
                            jmp replace_variableEXENext
                        .else
                            pop rdx
                            jmp replace_variable@B
                        .endif                        
                    .elseif dword ptr [rdx]== 04A424F24h;$OBJ            
                        add rdx,4
                        push rdx
                        mov rdx,r_@OBJ
                        replace_variableOBJNext:
                        .if byte ptr [rdx]
                            mov al,byte ptr [rdx]
                            mov byte ptr [rcx],al                    
                            inc rdx
                            inc rcx
                            jmp replace_variableOBJNext
                        .else
                            pop rdx
                            jmp replace_variable@B
                        .endif                        
                    .elseif dword ptr [rdx]== 052494424h;$DIR 
                        add rdx,4
                        push rdx
                        mov rdx,r_@DIR
                        replace_variableDIRNext:
                        .if byte ptr [rdx]
                            mov al,byte ptr [rdx]
                            mov byte ptr [rcx],al                    
                            inc rdx
                            inc rcx
                            jmp replace_variableDIRNext
                        .else
                            pop rdx
                            jmp replace_variable@B
                        .endif                        
                    .else
                        mov al,"$"
                        mov byte ptr [rcx],al                    
                        inc rdx                           
                        inc rcx                           
                    .endif
                .else
                    mov al,byte ptr [rdx]
                    mov byte ptr [rcx],al                    
                    inc rcx     
                    inc rdx
                .endif
                jmp replace_variable@B                   
            .endif
            mov byte ptr [rcx],0   
        lea rax,replace_variable_buffer
        ret
    .endp
    
    	;########################################################################	run and stop
    .DATA
    	run_handler_id		gulong	0	
    	run_pid				gint	0	
    .CODE
    .proc run_CallBack 	,term:gpointer, pid:gint, err:gpointer, user_data:gpointer
    .shadow

     	.if err==0
     		mov eax,pid
     		mov run_pid, eax		
            invoke gtk_widget_set_sensitive,WMnTBStopRun, -1   ;enable       
            invoke gtk_widget_set_sensitive,WMnTBRun	, 0    ;disable run button      
     		Terminal_Print_Line "Run..."    
     	.else
            invoke gtk_widget_set_sensitive,WMnTBStopRun, 0    ;disable stop button      
            invoke gtk_widget_set_sensitive,WMnTBRun	, -1   ;enable run button      
            mov run_pid,0 		     	
      		Terminal_Print_Line "Fail to run project"
            mov rax,err
            invoke printf,str$(<13,10,"ERROR(run) [%d]:{%s}">),QWORD PTR [rax],QWORD PTR [rax+8]
            xor rax,rax        
     	.endif  	
    	RET
    .endp
    .proc run_Exited 	, __vteterminal:gpointer, _status:gint, __user_data:gpointer
 	.shadow
 	IF 	@Platform EQ 3	;	ELF64
     	invoke g_signal_handler_disconnect,WTerminal,run_handler_id	
    ENDIF
 		.if _status==0
 			Terminal_Print "... SUCCESS"
  		.endif     	
        mov run_pid,0 		     	
        invoke gtk_widget_set_sensitive,WMnTBStopRun, 0    ;disable stop button      
        invoke gtk_widget_set_sensitive,WMnTBRun	, -1   ;enable run button      
    	REt
    .endp
    .proc run_toolbar 
		mov build_run,-1		
 		call build_toolbar            	
    	ret
    .endp
    .proc run_current_project 
    	local runcmd:gpointer
        local retv   :gpointer
        .if Current_Prj_FileName==0
            ret
        .endif
		
        m2m runcmd,Current_Prj_Run_cmd
        .if	runcmd
		    mov runcmd,rv(g_strdup,rv(replace_variable_with_value_str,runcmd))
        .endif
        xor rax,rax
	IF 		@Platform EQ 1	;	Win64
        mov retv,rv( spawn_run_ex2,runcmd,rax,addr run_CallBack,addr run_Exited,TRUE)
	ELSEIF 	@Platform EQ 3	;	ELF64
        mov retv,rv( spawn_run_ex2,runcmd,rax,addr run_CallBack,addr run_Exited,addr run_handler_id)
 	ENDIF
        .if	runcmd
		    invoke g_free,runcmd
        .endif
        RET 
	.endp
    
   	.proc stoprun_current_project  
		IF 		@Platform EQ 1	;	Win64
			w_terminal_TerminateChildProcess()
		ELSEIF 	@Platform EQ 3	;	ELF64
			.if	run_pid 
				invoke _kill,run_pid,1
	   		.endif
		ENDIF	
        RET 
    .endp
    
    	;########################################################################	Build
    .DATA
    	build_handler_id		gulong	0	
    	build_run				gboolean	0	
    .CODE
    .proc build_CallBack , term:gpointer, pid:gpointer, err:gpointer, user_data:gpointer
    .shadow

     	.if err==0
     		Terminal_Print_Line "Build started..." 
     		ret    		
     	.else
      		Terminal_Print_Line "Fail to build project"
            mov rax,err
            invoke printf,str$(<13,10,"ERROR(build) [%d]:{%s}">),QWORD PTR [rax],QWORD PTR [rax+8]
            mov build_run,0
            xor rax,rax        
     	.endif  	
    	RET
    .endp
    .proc build_Exited 	, __vteterminal:gpointer, _status:gint, __user_data:gpointer
 	.shadow
 	IF 	@Platform EQ 3	;	ELF64
     	invoke g_signal_handler_disconnect,WTerminal,build_handler_id
   	ENDIF	
 			Terminal_Print "... build_Exited"
 		.if _status==0
 			Terminal_Print "... SUCCESS"
			.if build_run
 				invoke run_current_project
 			.endif
  		.endif     	
		mov build_run,0
    	RET
    .endp
    .data
    	b__ gpointer	0
    	    gpointer	0,0
    .code
    .proc build_toolbar 
		mov assemble_Build,-1		
 		call assemble_current_project            	
    	ret
    .endp
    .proc build_current_project
        local Linkcmd:gpointer
        local retv   :gpointer
        local Link_optlst:gpointer
        local _len:gpointer
        local show_watchendIter:GtkTextIter
        
        .if Current_Prj_FileName==0
            ret
        .endif
		
        m2m Linkcmd,Current_Prj_Link
        .if	Linkcmd
        	mov rax,Linkcmd
        	.if byte ptr [rax]
			mov Linkcmd,rv(g_strdup,rv(replace_variable_with_value_str,Linkcmd))
        	.else
        		mov Linkcmd,0
        	.endif
        .endif
        m2m Link_optlst,Current_Prj_Link_opt
        .if	Link_optlst
        	mov rax,Link_optlst
        	.if byte ptr [rax]
			mov Link_optlst,rv(g_strsplit,rv(replace_variable_with_value_str,Link_optlst),";",-1)
        	.else
        		mov Link_optlst,0
        	.endif
        .endif
        .if	Linkcmd
			IF 		@Platform EQ 1	;	Win64
				mov retv,rv( spawn_run_ex2,Linkcmd,Link_optlst,addr build_CallBack,addr build_Exited,FALSE)
			ELSEIF 	@Platform EQ 3	;	ELF64
				mov retv,rv( spawn_run_ex2,Linkcmd,Link_optlst,addr build_CallBack,addr build_Exited,addr build_handler_id)
		 	ENDIF
       		 invoke g_free,Linkcmd
        .else
		.if build_run
			invoke run_current_project
		.endif        	
        .endif
        .if	Link_optlst
		    invoke g_strfreev,Link_optlst
        .endif
        RET
    .endp
    
    	;########################################################################	Assemble
    .DATA
    	assemble_handler_id		gulong		0	
    	assemble_status			gint		0	    	
    	assemble_Build			gboolean	0	
    .CODE
    .proc assemble_CallBack , term:gpointer, pid:gpointer, err:gpointer, user_data:gpointer
    .shadow

     	.if err==0
     		Terminal_Print_Line "Assemble started..."     		
     	.else
      		Terminal_Print_Line "Fail to Assemble project"
            mov rax,err
            invoke printf,str$(<13,10,"ERROR(Assemble) [%d]:{%s}">),QWORD PTR [rax],QWORD PTR [rax+8]
 			mov assemble_Build,0
 		    xor rax,rax        
     	.endif  	
    	RET
    .endp
    .proc assemble_Exited 	, __vteterminal:gpointer, _status:gint, __user_data:gpointer
 	.shadow
 	IF 	@Platform EQ 3	;	ELF64
     	invoke g_signal_handler_disconnect,WTerminal,assemble_handler_id
    ENDIF	
 		.if _status==0
 			Terminal_Print "... SUCCESS"
 			m2m assemble_status,_status
 			.if assemble_Build
 				invoke build_current_project
 			.endif
 		.endif     	
 		mov assemble_Build,0
    	RET
    .endp
    .proc assemble_current_project
        local Assemblecmd:gpointer
        local retv   :gpointer
        local Assemble_optlst:gpointer

        
        .if Current_Prj_FileName==0
            ret
        .endif
        ;call save_all_tab;save_current_tab
        mov rdi,-1
        call Projects_Save_Current_Project_Files_Content
		m2m Assemblecmd,Current_Prj_Assemble
		.if	Assemblecmd
	        mov Assemblecmd,rv(g_strdup,rv(replace_variable_with_value_str,Assemblecmd))
		.endif 	
        
        m2m Assemble_optlst,Current_Prj_Assemble_opt
        .if Assemble_optlst
	        mov Assemble_optlst,rv(g_strsplit,rv(replace_variable_with_value_str,Assemble_optlst),";",-1)        
        .endif
		IF 		@Platform EQ 1	;	Win64
			mov retv,rv( spawn_run_ex2,Assemblecmd,Assemble_optlst,addr assemble_CallBack,addr assemble_Exited,FALSE)
		ELSEIF 	@Platform EQ 3	;	ELF64
			mov retv,rv( spawn_run_ex2,Assemblecmd,Assemble_optlst,addr assemble_CallBack,addr assemble_Exited,addr assemble_handler_id)
	 	ENDIF
        
        ;
        .if Assemble_optlst
        	invoke g_strfreev,Assemble_optlst
        .endif        
		.if	Assemblecmd
        	invoke g_free,Assemblecmd
		.endif 	
        RET
    .endp
    
    	;########################################################################	Pre-Assemble
     .DATA
    	preassemble_handler_id		gulong		0	
    	preassemble_status			gint		0	    	
    	preassemble_assemble			gboolean	0	
    .CODE
    .proc preassemble_CallBack , term:gpointer, pid:gpointer, err:gpointer, user_data:gpointer
    .shadow
     	.if err==0
     		Terminal_Print_Line "Pre-Assemble started..."     		
     	.else
      		Terminal_Print_Line "Fail to Pre-Assemble project"
            mov rax,err
            invoke printf,str$(<13,10,"ERROR(Pre-Assemble ) [%d]:{%s}">),QWORD PTR [rax],QWORD PTR [rax+8]
 			mov preassemble_assemble,0
 		    xor rax,rax        
     	.endif  	
    	RET
    .endp
    .proc preassemble_Exited 	, __vteterminal:gpointer, _status:gint, __user_data:gpointer
 	.shadow
 	IF 	@Platform EQ 3	;	ELF64
     		invoke g_signal_handler_disconnect,WTerminal,preassemble_handler_id	
    ENDIF
 		.if _status==0
 			Terminal_Print "... SUCCESS"
 			m2m preassemble_status,_status
 			.if preassemble_assemble
 				invoke assemble_current_project 
 			.endif
 		.endif     	
 		mov preassemble_assemble,0
    	RET
    .endp
    .proc preassemble_current_project
        local PreAssemblecmd:gpointer
        local retv   :gpointer
        local preassemble_optlst:gpointer

        
        .if Current_Prj_FileName==0
            ret
        .endif
        ;call save_all_tab;save_current_tab
        mov rdi,-1
        call Projects_Save_Current_Project_Files_Content
		m2m PreAssemblecmd,Current_Prj_PreAssemble
		.if	PreAssemblecmd
	        mov PreAssemblecmd,rv(g_strdup,rv(replace_variable_with_value_str,PreAssemblecmd))
		.endif 	
        
        m2m preassemble_optlst,Current_Prj_PreAssemble_opt
        .if preassemble_optlst
	        mov preassemble_optlst,rv(g_strsplit,rv(replace_variable_with_value_str,preassemble_optlst),";",-1)        
        .endif
	IF 		@Platform EQ 1	;	Win64
        mov retv,rv( spawn_run_ex2,PreAssemblecmd,preassemble_optlst,addr preassemble_CallBack,addr preassemble_Exited,FALSE)
	ELSEIF 	@Platform EQ 3	;	ELF64
        mov retv,rv( spawn_run_ex2,PreAssemblecmd,preassemble_optlst,addr preassemble_CallBack,addr preassemble_Exited,addr preassemble_handler_id)
 	ENDIF
        
        ;
        .if preassemble_optlst
        	invoke g_strfreev,preassemble_optlst
        .endif        
		.if	PreAssemblecmd
        	invoke g_free,PreAssemblecmd
		.endif 	
        RET
    .endp


    .data   
    	_watch_buff_    db  2048    dup(?)
    .code    
    .proc remove_ANSI_Escape_sequences ,__s:gpointer
    .shadow
            lea rcx,_watch_buff_
            mov rdx,__s
            @@B:
                cmp byte ptr [rdx],0
                je  @@F
                cmp byte ptr [rdx],01bh
                jne @next_
           remov:
                inc rdx
                cmp byte ptr [rdx],"m"
                je @next_1
                cmp byte ptr [rdx],"H"
                je @next_1
                cmp byte ptr [rdx],"f"
                je @next_1
                cmp byte ptr [rdx],"A"
                je @next_1
                cmp byte ptr [rdx],"B"
                je @next_1
                cmp byte ptr [rdx],"C"
                je @next_1
                cmp byte ptr [rdx],"D"
                je @next_1
                cmp byte ptr [rdx],"s"
                je @next_1
                cmp byte ptr [rdx],"u"
                je @next_1
                cmp byte ptr [rdx],"J"
                je @next_1
                cmp byte ptr [rdx],"K"
                je @next_1
                cmp byte ptr [rdx],"h"
                je @next_1
                cmp byte ptr [rdx],"l"
                je @next_1
                
                jmp remov
           @next_1:
           
                inc rdx
                cmp byte ptr [rdx],01bh
                je  remov
                cmp byte ptr [rdx],0
                je  @@F                
           @next_:
                mov al,byte ptr [rdx]
                mov byte ptr [rcx],al                    
                inc rcx     
                inc rdx
                jmp @@B
            @@F:
            mov byte ptr [rcx],0
            lea rax,_watch_buff_
        ret
    .endp
