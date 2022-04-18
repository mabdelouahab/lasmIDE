
    .code
    split_to_build proc s:gpointer
        local _s:gpointer
        mov _s,s
        invoke g_strdup,_s
        mov rdx,rax
        xor rcx,rcx
        @@:
            .if byte ptr [rdx]=="."
                mov rcx,rdx
            .endif
            inc rdx
            CMP byte ptr [rdx],0
            jne @B
            .if rcx
                mov byte ptr [rcx],0
            .endif
        ret
    split_to_build endp
    get_o_name proc s:gpointer
        local _s:gpointer
        local _ssplit:gpointer
        mov _s,s
        mov _ssplit,rv(split_to_build,_s)
        invoke g_strconcat,_ssplit,".o",0
        push rax
        invoke g_free,_ssplit
        pop rax
        ret                     
    get_o_name endp
    .data
        replace_variable_buffer    db  1024 dup(0)
    .code
    Files_Get_OFile_From_Name proto :gpointer
    ;$SRC : Source, input file,source code,project main file
    ;$EXE : Output executable, Output library
    ;$OBJ : Object file
    ;$DIR : Project path
    replace_variable_with_value_str proc __s_:gpointer
        local r_@SRC:gpointer
        local r_@EXE:gpointer
        local r_@OBJ:gpointer
        local r_@DIR:gpointer
        local lofile:gpointer        
        local __s:gpointer      
        
        mov __s,__s_
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
    replace_variable_with_value_str endp

    

    

    
    	;########################################################################	run and stop
    .DATA
    	run_handler_id		gulong	0	
    	run_pid				gint	0	
    .CODE
    run_CallBack 	PROC	_term:gpointer,_pid:gint,_err:gpointer,_user_data:gpointer
     	local term:gpointer
     	local pid:gint
     	local err:gpointer
     	local user_data:gpointer
     	mov term,_term
     	mov pid,_pid
     	mov err,_err
     	mov user_data,_user_data

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
    run_CallBack 	ENDP
    run_Exited 		PROC ___vteterminal:gpointer,__status:gint,___user_data:gpointer
 		local __vteterminal:gpointer
 		local _status:gint
 		local __user_data:gpointer
 		
 		mov __vteterminal,___vteterminal
 		mov _status,__status
 		mov __user_data,___user_data
 		
     	invoke g_signal_handler_disconnect,WTerminal,run_handler_id	
 		.if _status==0
 			Terminal_Print "... SUCCESS"
  		.endif     	

        mov run_pid,0 		     	
        invoke gtk_widget_set_sensitive,WMnTBStopRun, 0    ;disable stop button      
        invoke gtk_widget_set_sensitive,WMnTBRun	, -1   ;enable run button      
    	REt
    run_Exited 		ENDP
    run_toolbar PROC
		mov build_run,-1		
 		call build_toolbar            	
    	ret
    run_toolbar endp
          
    run_current_project PROC
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
        mov retv,rv( spawn_run_ex2,runcmd,rax,addr run_CallBack,addr run_Exited,addr run_handler_id)
        .if	runcmd
		    invoke g_free,runcmd
        .endif
        RET 
	run_current_project      ENDP
    
   	stoprun_current_project  PROC
   		.if	run_pid 		
   			invoke _kill,run_pid,1
   		.endif
        RET 
    stoprun_current_project  ENDP
    
    	;########################################################################	Build
    .DATA
    	build_handler_id		gulong	0	
    	build_run				gboolean	0	
    .CODE
    build_CallBack 	PROC	_term:gpointer,_pid:gpointer,_err:gpointer,_user_data:gpointer
     	local term:gpointer
     	local pid:gpointer
     	local err:gpointer
     	local user_data:gpointer
     	mov term,_term
     	mov pid,_pid
     	mov err,_err
     	mov user_data,_user_data

     	.if err==0
     		Terminal_Print_Line "Build started..."     		
     	.else
      		Terminal_Print_Line "Fail to build project"
            mov rax,err
            invoke printf,str$(<13,10,"ERROR(build) [%d]:{%s}">),QWORD PTR [rax],QWORD PTR [rax+8]
            mov build_run,0
            xor rax,rax        
     	.endif  	
    	RET
    build_CallBack 	ENDP
    build_Exited 	PROC ___vteterminal:gpointer,__status:gint,___user_data:gpointer
 		local __vteterminal:gpointer
 		local _status:gint
 		local __user_data:gpointer
 		
 		mov __vteterminal,___vteterminal
 		mov _status,__status
 		mov __user_data,___user_data
     	invoke g_signal_handler_disconnect,WTerminal,build_handler_id	
 		.if _status==0
 			Terminal_Print "... SUCCESS"
			.if build_run
 				invoke run_current_project
 			.endif
  		.endif     	
		mov build_run,0
    	RET
    build_Exited 	ENDP
    .data
    	b__ gpointer	0
    	    gpointer	0,0
    .code
    build_toolbar PROC
		mov assemble_Build,-1		
 		call assemble_current_project            	
    	ret
    build_toolbar endp
    build_current_project PROC
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
		    mov Linkcmd,rv(g_strdup,rv(replace_variable_with_value_str,Linkcmd))
        .endif
        m2m Link_optlst,Current_Prj_Link_opt
        .if	Link_optlst
		    mov Link_optlst,rv(g_strsplit,rv(replace_variable_with_value_str,Link_optlst),";",-1)
		    ;mov b__,rax
        .endif
        mov retv,rv( spawn_run_ex2,Linkcmd,Link_optlst,addr build_CallBack,addr build_Exited,addr build_handler_id)
        .if	Linkcmd
		    invoke g_free,Linkcmd
        .endif
        .if	Link_optlst
		    invoke g_strfreev,Link_optlst
        .endif
        RET
    build_current_project ENDP
    
    	;########################################################################	Assemble
    .DATA
    	assemble_handler_id		gulong		0	
    	assemble_status			gint		0	    	
    	assemble_Build			gboolean	0	
    .CODE
    assemble_CallBack 	PROC	_term:gpointer,_pid:gpointer,_err:gpointer,_user_data:gpointer
     	local term:gpointer
     	local pid:gpointer
     	local err:gpointer
     	local user_data:gpointer
     	mov term,_term
     	mov pid,_pid
     	mov err,_err
     	mov user_data,_user_data

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
    assemble_CallBack 	ENDP
    assemble_Exited 	PROC ___vteterminal:gpointer,__status:gint,___user_data:gpointer
 		local __vteterminal:gpointer
 		local _status:gint
 		local __user_data:gpointer
 		
 		mov __vteterminal,___vteterminal
 		mov _status,__status
 		mov __user_data,___user_data
     	invoke g_signal_handler_disconnect,WTerminal,assemble_handler_id	
 		.if _status==0
 			Terminal_Print "... SUCCESS"
 			m2m assemble_status,_status
 			.if assemble_Build
 				invoke build_current_project
 			.endif
 		.endif     	
 		mov assemble_Build,0
    	RET
    assemble_Exited 	ENDP
    assemble_current_project PROC
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
        
        mov retv,rv( spawn_run_ex2,Assemblecmd,Assemble_optlst,addr assemble_CallBack,addr assemble_Exited,addr assemble_handler_id);
        .if Assemble_optlst
        	invoke g_strfreev,Assemble_optlst
        .endif        
		.if	Assemblecmd
        	invoke g_free,Assemblecmd
		.endif 	
        RET
    assemble_current_project ENDP
    
    	;########################################################################	Pre-Assemble
    preassemble_current_project PROC
        RET
    preassemble_current_project ENDP




    .data   
    	_watch_buff_    db  2048    dup(?)
    .code    
    remove_ANSI_Escape_sequences proc __s_:gpointer
        local __s:gpointer      
        mov __s,__s_
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
    remove_ANSI_Escape_sequences endp
