	settings1 struct
		paned2_ID			dword ?
		paned2_position 	dword ?
		paned1_ID			dword ?
		paned1_position 	dword ?
		EOS 				qword ?
	settings1 ends


	.data
	stg settings1 <2,300,1,300,0>			;initial settings, for compatibility, if file do not exist

	    __bufForRead        DB  10000    DUP(0)
	.data
	    SettingFileName     DB  "setting.stg",  0
	    hSettingFile        DQ  0
	    slist               DQ  0    
	.code




enum    stng_EOS, \         
        stng_paned1_Position, \
        stng_paned2_Position, \
        stng_show_line_numbre, \
        stng_main_window_maximised , \
        stng_main_window_x , \
        stng_main_window_y , \
        stng_main_window_w, \
        stng_main_window_h        
        

    STNG_Get PROC uses r12 _setting:dword,_pValue:gpointer
        Local l_setting:dword
        Local l__pValue:gpointer
        local n_bytes:dword
        local pfname :gpointer
        local error:GError
	local p_input:gpointer
	local sz_input:dword


        mov l_setting,_setting
        mov l__pValue,_pValue
        
        mov pfname,rv(g_build_filename,firstworkingdir,addr SettingFileName,0) 
        
        mov error,0
        invoke g_file_get_contents,pfname,addr p_input,addr sz_input,addr error	;try to open file

        .if eax == FALSE
		mov rax,error
		assume rax:GError
		invoke g_printf,CStr("%s",10),[rax].message
		assume rax:nothing
	         invoke g_free,pfname
		mov rax,-1
		ret
        .endif

	mov r12,p_input
	assume r12:ptr settings1

	xor rax,rax
	mov rcx,l__pValue
	.if l_setting == stng_paned1_Position
		mov eax,[r12].paned1_position
		mov [rcx],eax
	.elseif l_setting == stng_paned2_Position
		mov eax,[r12].paned2_position
		mov [rcx],eax
	.endif
	assume r12:nothing
	mov r12,rax
         invoke g_free,pfname
         mov rax,r12
        ret

    STNG_Get ENDP
    
    STNG_Set PROC uses r12 _setting:dword,_Value:dword
        Local l_setting:dword
        Local l_Value:dword
        local n_bytes:qword
        local pfname :gpointer
        local error:GError
        local error1:GError
	local p_input:gpointer
	local sz_input:dword

        mov l_setting,_setting
        mov l_Value,_Value
        mov pfname,rv(g_build_filename,firstworkingdir,addr SettingFileName,0)

	mov error1,0                
        invoke g_file_test,pfname,G_FILE_TEST_EXISTS
        .if rax == FALSE
		invoke g_file_set_contents,pfname,addr stg,sizeof settings1,addr error1
        .endif


        mov error,0
        invoke g_file_get_contents,pfname,addr p_input,addr sz_input,addr error	;try to open file

        .if eax == FALSE
		mov rax,error
		assume rax:GError
		invoke g_printf,CStr("%s",10),[rax].message
		assume rax:nothing
	         invoke g_free,pfname
		mov rax,-1
		ret
        .endif

	mov r12,p_input
	assume r12:ptr settings1

	xor rax,rax
	mov ecx,l_Value
	.if l_setting == stng_paned1_Position
		mov [r12].paned1_position,ecx
		mov [r12].paned1_ID,stng_paned1_Position
	.elseif l_setting == stng_paned2_Position
		mov [r12].paned2_position,ecx
		mov [r12].paned2_ID,stng_paned2_Position
	.endif
	assume r12:nothing
	
        mov error,0
	invoke g_file_set_contents,pfname,p_input,sz_input,addr error
        .if eax == FALSE
		mov rax,error
		assume rax:GError
		invoke g_printf,CStr("%s",10),[rax].message
		assume rax:nothing
	         invoke g_free,pfname
		mov rax,-1
		ret
        .endif

         invoke g_free,pfname
	xor eax,eax
        ret

    STNG_Set ENDP
