
	OFile		STRUCT
		_Name				gpointer	0
		FileName			gpointer	0
		Description			gpointer	0
		ProgrammingLanguage	gpointer	0
		StyleScheme			gpointer	0
		icon				gpointer	0
		buffer				gpointer	0
		NotebookPage		gpointer	0
		Dir 				gpointer	0
		Content				gpointer	0
		Modified			gpointer	0
		Path				gpointer	0
	OFile		ENDS

	.code
	Files_Create_ASM_File PROC	 _FName:gpointer 
        local FName		:gpointer
        local FFileName	:gpointer
        mov FName,_FName
        
        mov FFileName,rv(g_strconcat,FName,str$(".asm"),0)
        invoke g_malloc,sizeof OFile  
        mov rcx,rax  
		m2m 	[rcx].OFile._Name				,FName		
        m2m 	[rcx].OFile.FileName			,FFileName
		m2m 	[rcx].OFile.Description			,FName	 
		str2m 	[rcx].OFile.ProgrammingLanguage	,"assembly" 
		str2m 	[rcx].OFile.StyleScheme			,"assembly"	 
		str2m 	[rcx].OFile.icon				,"asmfileicon" 
		mov 	[rcx].OFile.buffer				,0	 
		mov 	[rcx].OFile.NotebookPage		,0	 
		mov 	[rcx].OFile.Dir					,0	 
		mov 	[rcx].OFile.Content				,0							
		mov 	[rcx].OFile.Path				,0							
		mov rax,rcx
		ret
	Files_Create_ASM_File ENDP
	Files_Create_INC_File PROC	 _FName:gpointer 
        local FName		:gpointer
        local FFileName	:gpointer
        mov FName,_FName
        
        mov FFileName,rv(g_strconcat,FName,str$(".inc"),0)
        invoke g_malloc,sizeof OFile    
        mov rcx,rax  
		m2m 	[rcx].OFile._Name				,FName		
        m2m 	[rcx].OFile.FileName			,FFileName
		m2m 	[rcx].OFile.Description			,FName	 
		str2m 	[rcx].OFile.ProgrammingLanguage	,"assembly" 
		str2m 	[rcx].OFile.StyleScheme			,"assembly"	 
		str2m 	[rcx].OFile.icon				,"incfileicon" 
		mov 	[rcx].OFile.buffer				,0	 
		mov 	[rcx].OFile.NotebookPage		,0	 
		mov 	[rcx].OFile.Dir					,0	 
		mov 	[rcx].OFile.Content				,0							
		mov 	[rcx].OFile.Path				,0							
		mov rax,rcx

	
		ret
	Files_Create_INC_File ENDP
	Files_Create_WEDG_File PROC	 _FName:gpointer 
        local FName		:gpointer
        local FFileName	:gpointer
        mov FName,_FName
        
        mov FFileName,rv(g_strconcat,FName,str$(".wedg"),0)
        invoke g_malloc,sizeof OFile    
        mov rcx,rax  
		m2m 	[rcx].OFile._Name				,FName		
        m2m 	[rcx].OFile.FileName			,FFileName
		m2m 	[rcx].OFile.Description			,FName	 
		str2m 	[rcx].OFile.ProgrammingLanguage	,"assembly" 
		str2m 	[rcx].OFile.StyleScheme			,"assembly"	 
		str2m 	[rcx].OFile.icon				,"wedgfileicon" 
		mov 	[rcx].OFile.buffer				,0	 
		mov 	[rcx].OFile.NotebookPage		,0	 
		mov 	[rcx].OFile.Dir					,0	 
		mov 	[rcx].OFile.Content				,0							
		mov 	[rcx].OFile.Path				,0							
		mov rax,rcx

	
		ret
	Files_Create_WEDG_File ENDP
	Files_Create_C_File PROC	 _FName:gpointer 
        local FName		:gpointer
        local FFileName	:gpointer
        mov FName,_FName
        
        mov FFileName,rv(g_strconcat,FName,str$(".c"),0)
        invoke g_malloc,sizeof OFile    
        mov rcx,rax  
		m2m 	[rcx].OFile._Name				,FName		
        m2m 	[rcx].OFile.FileName			,FFileName
		m2m 	[rcx].OFile.Description			,FName	 
		str2m 	[rcx].OFile.ProgrammingLanguage	,"c" 
		str2m 	[rcx].OFile.StyleScheme			,"assembly"	 
		str2m 	[rcx].OFile.icon				,"cfileicon" 
		mov 	[rcx].OFile.buffer				,0	 
		mov 	[rcx].OFile.NotebookPage		,0	 
		mov 	[rcx].OFile.Dir					,0	 
		mov 	[rcx].OFile.Content				,0							
		mov 	[rcx].OFile.Path				,0							
		mov rax,rcx

	
		ret
	Files_Create_C_File ENDP
	Files_Create_H_File PROC	 _FName:gpointer 
        local FName		:gpointer
        local FFileName	:gpointer
        mov FName,_FName
        
        mov FFileName,rv(g_strconcat,FName,str$(".h"),0)
        invoke g_malloc,sizeof OFile    
        mov rcx,rax  
		m2m 	[rcx].OFile._Name				,FName		
        m2m 	[rcx].OFile.FileName			,FFileName
		m2m 	[rcx].OFile.Description			,FName	 
		str2m 	[rcx].OFile.ProgrammingLanguage	,"c" 
		str2m 	[rcx].OFile.StyleScheme			,"assembly"	 
		str2m 	[rcx].OFile.icon				,"hfileicon" 
		mov 	[rcx].OFile.buffer				,0	 
		mov 	[rcx].OFile.NotebookPage		,0	 
		mov 	[rcx].OFile.Dir					,0	 
		mov 	[rcx].OFile.Content				,0							
		mov 	[rcx].OFile.Path				,0							
		mov rax,rcx

	
		ret
	Files_Create_H_File ENDP
	Files_Create_TXT_File PROC	 _FName:gpointer 
        local FName		:gpointer
        local FFileName	:gpointer
        mov FName,_FName
        
        mov FFileName,rv(g_strconcat,FName,str$(".txt"),0)
        invoke g_malloc,sizeof OFile    
        mov rcx,rax  
		m2m 	[rcx].OFile._Name				,FName		
        m2m 	[rcx].OFile.FileName			,FFileName
		m2m 	[rcx].OFile.Description			,FName	 
		str2m 	[rcx].OFile.ProgrammingLanguage	,"text" 
		str2m 	[rcx].OFile.StyleScheme			,"classic"	 
		str2m 	[rcx].OFile.icon				,"txtfileicon" 
		mov 	[rcx].OFile.buffer				,0	 
		mov 	[rcx].OFile.NotebookPage		,0	 
		mov 	[rcx].OFile.Dir					,0	 
		mov 	[rcx].OFile.Content				,0							
		mov 	[rcx].OFile.Path				,0							
		mov rax,rcx

	
		ret
	Files_Create_TXT_File ENDP
	Files_Create_RC_File PROC	 _FName:gpointer 
        local FName		:gpointer
        local FFileName	:gpointer
        mov FName,_FName
        
        mov FFileName,rv(g_strconcat,FName,str$(".rc"),0)
        invoke g_malloc,sizeof OFile    
        mov rcx,rax  
		m2m 	[rcx].OFile._Name				,FName		
        m2m 	[rcx].OFile.FileName			,FFileName
		m2m 	[rcx].OFile.Description			,FName	 
		str2m 	[rcx].OFile.ProgrammingLanguage	,"rc" 
		str2m 	[rcx].OFile.StyleScheme			,"classic"	 
		str2m 	[rcx].OFile.icon				,"rcfileicon" 
		mov 	[rcx].OFile.buffer				,0	 
		mov 	[rcx].OFile.NotebookPage		,0	 
		mov 	[rcx].OFile.Dir					,0	 
		mov 	[rcx].OFile.Content				,0							
		mov 	[rcx].OFile.Path				,0							
		mov rax,rcx

	
		ret
	Files_Create_RC_File ENDP
	Files_Create_ANY_File PROC	 _FName:gpointer 
        local FName		:gpointer
        local FFileName	:gpointer
        mov FName,_FName
        
        mov FFileName,rv(g_strconcat,FName,0)
        invoke g_malloc,sizeof OFile    
        mov rcx,rax  
		m2m 	[rcx].OFile._Name				,FName		
        m2m 	[rcx].OFile.FileName			,FFileName
		m2m 	[rcx].OFile.Description			,FName	 
		str2m 	[rcx].OFile.ProgrammingLanguage	,"text" 
		str2m 	[rcx].OFile.StyleScheme			,"classic"	 
		str2m 	[rcx].OFile.icon				,"txtfileicon" 
		mov 	[rcx].OFile.buffer				,0	 
		mov 	[rcx].OFile.NotebookPage		,0	 
		mov 	[rcx].OFile.Dir					,0	 
		mov 	[rcx].OFile.Content				,0							
		mov 	[rcx].OFile.Path				,0							
		mov rax,rcx

	
		ret
	Files_Create_ANY_File ENDP
	Files_Create_XML_File PROC	 _FName:gpointer 
        local FName		:gpointer
        local FFileName	:gpointer
        mov FName,_FName
        
        mov FFileName,rv(g_strconcat,FName,str$(".xml"),0)
        invoke g_malloc,sizeof OFile    
        mov rcx,rax  
		m2m 	[rcx].OFile._Name				,FName		
        m2m 	[rcx].OFile.FileName			,FFileName
		m2m 	[rcx].OFile.Description			,FName	 
		str2m 	[rcx].OFile.ProgrammingLanguage	,"xml" 
		str2m 	[rcx].OFile.StyleScheme			,"assembly"	 
		str2m 	[rcx].OFile.icon				,"xmlfileicon" 
		mov 	[rcx].OFile.buffer				,0	 
		mov 	[rcx].OFile.NotebookPage		,0	 
		mov 	[rcx].OFile.Dir					,0	 
		mov 	[rcx].OFile.Content				,0							
		mov 	[rcx].OFile.Path				,0							
		mov rax,rcx

	
		ret
	Files_Create_XML_File ENDP
	Files_Save_Content PROC	_pOFile:gpointer
		local 	pOFile		:gpointer
		local   buf			:gpointer
		local   content		:gpointer
        local __start_iter	:GtkTextIter
        local __end_iter  	:GtkTextIter 
        local 	FullPName	:gpointer      
                 
		mov pOFile,_pOFile
		mov rax,pOFile
		mov rcx,[rax].OFile.buffer
		mov buf,rcx 
		mov rcx,[rax].OFile.Content
		mov content,rcx 
		.if	[rax].OFile.Path
    		mov FullPName,rv(g_build_filename,[rax].OFile.Path,[rax].OFile.FileName,0)		
		.else
			.if	[rax].OFile.Dir
				mov FullPName,rv(g_build_filename,Current_Project.Path,[rax].OFile.Dir,[rax].OFile.FileName,0)		
			.else
				mov FullPName,rv(g_build_filename,Current_Project.Path,[rax].OFile.FileName,0)
			.endif
		.endif
		.if	buf
           invoke gtk_text_buffer_get_bounds,buf,addr __start_iter,addr __end_iter
           mov content ,rv( gtk_text_buffer_get_text,buf,addr __start_iter,addr __end_iter,-1)
		.endif
        invoke _close,rv(_open,FullPName,O_WRONLY or O_CREAT , S_IRWXU or S_IRWXG or S_IRWXO)
		.if content
			invoke g_file_set_contents,FullPName,content,-1,0
			
			mov rax,pOFile
			mov [rax].OFile.Modified,0
		.endif
		
    	invoke g_free,FullPName	
		ret
	Files_Save_Content ENDP
    Files_Get_File_Icon_PixBuf Proc  ofile__:gpointer        
        local ofile_:gpointer
        local Ifile_:gpointer
      
        mov ofile_,ofile__
        mov rax,ofile_
        mov rax,[rax].OFile.icon
        mov Ifile_,rax
	    .if 	rv(g_strcmp0,Ifile_, "asmfileicon") == 0 
				return Icons_ASM_PixBuf    		
	    .endif
	    .if rv(g_strcmp0,Ifile_, "incfileicon") == 0 
				return Icons_INC_PixBuf
	    .endif
	    .if rv(g_strcmp0,Ifile_, "cfileicon") == 0 
				return Icons_C_PixBuf						
	    .endif
	    .if rv(g_strcmp0,Ifile_, "hfileicon") == 0 
				return Icons_H_PixBuf		
	    .endif
	    .if rv(g_strcmp0,Ifile_, "xmlfileicon") == 0 
				return Icons_XML_PixBuf
	    .endif
	    .if rv(g_strcmp0,Ifile_, "wedgfileicon") == 0 
				return Icons_WIDG_PixBuf
	    .endif
	    .if rv(g_strcmp0,Ifile_, "txtfileicon") == 0 
				return Icons_TXT_PixBuf
	    .endif
	    .if rv(g_strcmp0,Ifile_, "rcfileicon") == 0 
				return Icons_RC_PixBuf		
	    .endif
 		;Any auther 
		return Icons_ANY_PixBuf
 	    ret
    Files_Get_File_Icon_PixBuf EndP
	Files_Load PROC lKeyProject_:gpointer,file_Key__:gpointer
		local lKeyProject	:gpointer        
        local file_Key_	:gpointer
        
		mov lKeyProject		,lKeyProject_
		mov file_Key_	,file_Key__
		
        invoke g_malloc,sizeof OFile  
        mov rcx,rax  
		mov [rcx].OFile._Name				,Helpers_rv_rcx(g_key_file_get_string,	lKeyProject,file_Key_,"Name",0)
		mov [rcx].OFile.Description			,Helpers_rv_rcx(g_key_file_get_string,	lKeyProject,file_Key_,"Description",0)
		mov [rcx].OFile.ProgrammingLanguage	,Helpers_rv_rcx(g_key_file_get_string,	lKeyProject,file_Key_,"ProgrammingLanguage",0)
		mov [rcx].OFile.StyleScheme			,Helpers_rv_rcx(g_key_file_get_string,	lKeyProject,file_Key_,"StyleScheme",0)
		mov [rcx].OFile.icon				,Helpers_rv_rcx(g_key_file_get_string,	lKeyProject,file_Key_,"icon",0)
		mov [rcx].OFile.Dir					,Helpers_rv_rcx(g_key_file_get_string,	lKeyProject,file_Key_,"Dir",0)
		mov [rcx].OFile.Content				,Helpers_rv_rcx(g_key_file_get_string,	lKeyProject,file_Key_,"Content",0)
		m2m [rcx].OFile.FileName			,file_Key_
		mov [rcx].OFile.buffer				,0
		mov	[rcx].OFile.Modified			,0
		mov [rcx].OFile.NotebookPage		,0			
		mov [rcx].OFile.Path				,0	
		
		mov rax,rcx
		ret
	Files_Load ENDP
	Files_Save PROC lKeyProject_:gpointer,OFile__:gpointer
		local lKeyProject	:gpointer        
        local OFile_	:gpointer
        
		mov lKeyProject		,lKeyProject_
		mov OFile_	,OFile__
		mov rax,OFile_

		Helpers_invoke_Save_rax g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"Name"				,[rax].OFile._Name
		Helpers_invoke_Save_rax g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"Description"		,[rax].OFile.Description
		Helpers_invoke_Save_rax g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"ProgrammingLanguage",[rax].OFile.ProgrammingLanguage
		Helpers_invoke_Save_rax g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"StyleScheme"		,[rax].OFile.StyleScheme
		Helpers_invoke_Save_rax g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"icon"				,[rax].OFile.icon
		Helpers_invoke_Save_rax g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"Dir"				,[rax].OFile.Dir
		Helpers_invoke_Save_rax g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"Content"			,[rax].OFile.Content
		
		ret
	Files_Save ENDP
	Files_Text_Buffer_Changed PROC __textbuffer:gpointer,_pOFile:gpointer
		local pOFile:gpointer
		mov pOFile,_pOFile	
		mov rax,pOFile
		mov [rax].OFile.Modified,-1
invoke printf,str$(<13,10,"Files_Text_Buffer_Changed pOFile: %s">),[rax].OFile.FileName   
invoke printf,"."
 		ret
 	Files_Text_Buffer_Changed ENDP
	Files_Load_contents PROC 	_pOFile:gpointer
		local pOFile		:gpointer
        local FullPName	:gpointer      
		local lfcontents	:gpointer
        local utf8        :gpointer
        local bytes_written :gpointer  
        local bufaddr	    :gpointer              
        local lf_iter       :GtkTextIter   
        local PLanguage		:gpointer
        local lscrolledwindow:gpointer
		local hbox			:gpointer
		local lbutton		:gpointer
		local llabel		:gpointer
        local GGtkSourceStyleScheme :gpointer
        
		mov pOFile,_pOFile
		mov rax,pOFile
		.if	[rax].OFile.Path
    		mov FullPName,rv(g_build_filename,[rax].OFile.Path,[rax].OFile.FileName,0)		
		.else
			.if	[rax].OFile.Dir
				mov FullPName,rv(g_build_filename,Current_Project.Path,[rax].OFile.Dir,[rax].OFile.FileName,0)		
			.else
				mov FullPName,rv(g_build_filename,Current_Project.Path,[rax].OFile.FileName,0)
			.endif
		.endif
        .if rv(g_file_get_contents,FullPName,addr lfcontents, 0, 0)
invoke printf,str$(<13,10,"Files_Load_contents pOFile: %d">),pOFile   
invoke printf,"."
         	invoke gtk_source_buffer_new,0
			mov rcx,pOFile
         	mov [rcx].OFile.buffer,rax
         	mov bufaddr,rax
            invoke gtk_source_buffer_begin_not_undoable_action,bufaddr         		   	
		        mov utf8 ,rv(g_locale_to_utf8 ,lfcontents, -1, 0, addr bytes_written, 0)
		        invoke g_free,lfcontents
		        invoke gtk_text_buffer_get_end_iter,bufaddr,addr lf_iter
		        invoke gtk_text_buffer_insert,bufaddr ,addr lf_iter,utf8,-1
		        invoke g_free,utf8
            invoke gtk_source_buffer_end_not_undoable_action ,bufaddr
            invoke gtk_text_buffer_set_modified,bufaddr,0
            invoke gtk_text_buffer_get_start_iter,bufaddr,addr lf_iter
            invoke gtk_text_buffer_place_cursor,bufaddr,addr lf_iter
         	invoke g_signal_connect_data,bufaddr    ,str$("changed")    ,addr Files_Text_Buffer_Changed    ,pOFile,0,0      
			mov rcx,pOFile
         	m2m PLanguage,[rcx].OFile.ProgrammingLanguage

			mov GGtkSourceStyleScheme,rv( gtk_source_style_scheme_manager_get_scheme,GGtkSourceStyleSchemeManager,PLanguage)       
			invoke gtk_source_buffer_set_style_scheme,bufaddr, GGtkSourceStyleScheme         
			mov rax,pOFile
			invoke gtk_source_language_manager_guess_language,GGtkSourceLanguageManager,[rax].OFile.FileName,0
		    invoke gtk_source_buffer_set_language ,bufaddr, rax
		    invoke gtk_source_buffer_set_highlight_syntax,bufaddr,-1        
            
    		invoke g_free,FullPName	
            mov rax,-1
            ret
        .else
            invoke g_print,"faile to open: %s\n", FullPName
    		invoke g_free,FullPName	
            xor rax,rax
			ret
		.endif	
		ret
	Files_Load_contents ENDP
	Files_Get_OFile_From_Name PROC __fileName:gpointer
		local  _fileName:gpointer
		local OFilesIndex:gpointer
		mov _fileName,__fileName
		m2m OFilesIndex,Current_Project.OFiles
		.if OFilesIndex==0
			xor rax,rax
			ret
		.else
			@@:
			mov rax,OFilesIndex
			mov rax,gpointer ptr [rax]
		 	.if rax
				.if rv(g_strcmp0,[rax].OFile.FileName,_fileName) == 0  
					mov rax,OFilesIndex
					mov rax,gpointer ptr [rax]
		 			ret
		 		.endif
				add OFilesIndex	,sizeof gpointer   			 			
				jmp @B
			.endif			
		.endif
		xor rax,rax
		ret
	Files_Get_OFile_From_Name ENDP






	