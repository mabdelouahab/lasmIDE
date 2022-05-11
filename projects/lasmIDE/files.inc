
	OFile		STRUCT
		_Name				gpointer	0
		FileName			gpointer	0
		Description			gpointer	0
		ProgrammingLanguage	gpointer	0
		StyleScheme			gpointer	0
		icon				gpointer	0
        	viewer				gpointer	0
		buffer				gpointer	0
		NotebookPage		gpointer	0
		Dir 					gpointer	0
		Content				gpointer	0
		Modified			gpointer	0
		Path				gpointer	0
		search_context		gpointer	0
		source_view			gpointer	0
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
		mov 	[rcx].OFile.viewer				,0	 
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
		mov 	[rcx].OFile.viewer				,0	 
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
		mov 	[rcx].OFile.viewer				,0	 
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
		str2m 	[rcx].OFile.StyleScheme			,"c"	 
		str2m 	[rcx].OFile.icon				,"cfileicon" 
		mov 	[rcx].OFile.viewer				,0	 
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
		str2m 	[rcx].OFile.StyleScheme			,"c"	 
		str2m 	[rcx].OFile.icon				,"hfileicon" 
		mov 	[rcx].OFile.viewer				,0	 
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
		mov 	[rcx].OFile.viewer				,0	 
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
		mov 	[rcx].OFile.viewer				,0	 
		mov 	[rcx].OFile.buffer				,0	 
		mov 	[rcx].OFile.NotebookPage		,0	 
		mov 	[rcx].OFile.Dir					,0	 
		mov 	[rcx].OFile.Content				,0							
		mov 	[rcx].OFile.Path				,0							
		mov rax,rcx

	
		ret
	Files_Create_RC_File ENDP



	Files_Create_FT_File PROC	 _FName:gpointer , _FTypeName:gpointer 
        local FName		:gpointer
        local FTypeName		:gpointer
        local FFileName	:gpointer
        local __str_	:gpointer
         mov FName,_FName
         mov FTypeName,_FTypeName
        Settings_Get_Files_Type(_FTypeName)
        

        mov FFileName,rv(g_strconcat,FName,str$("."),TFile_Type_ST_Extention,0)
        invoke g_malloc,sizeof OFile    
        mov rcx,rax  
		m2m 	[rcx].OFile._Name				,FName		
        	m2m 	[rcx].OFile.FileName				,FFileName
		m2m 	[rcx].OFile.Description			,FName	 
		m2m 	[rcx].OFile.ProgrammingLanguage,TFile_Type_ST_ProgrammingLanguage
		m2m 	[rcx].OFile.StyleScheme			,TFile_Type_ST_StyleScheme	 
		m2m 	[rcx].OFile.icon					,TFile_Type_ST_Icon 
		mov 	[rcx].OFile.viewer				,0	 
		mov 	[rcx].OFile.buffer					,0	 
		mov 	[rcx].OFile.NotebookPage			,0	 
		mov 	[rcx].OFile.Dir					,0	 
		mov 	[rcx].OFile.Content				,0							
		mov 	[rcx].OFile.Path					,0							
		mov rax,rcx
		ret
	Files_Create_FT_File ENDP


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
		mov 	[rcx].OFile.viewer				,0	 
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
		mov 	[rcx].OFile.viewer				,0	 
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
				mov FullPName,rv(g_build_filename,Current_Prj_Path,[rax].OFile.Dir,[rax].OFile.FileName,0)
			.else
				mov FullPName,rv(g_build_filename,Current_Prj_Path,[rax].OFile.FileName,0)
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
	    Helpers_Load_Pixbuf_From_File(Ifile_)
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
		;mov [rcx].OFile.Content				,Helpers_rv_rcx(g_key_file_get_string,	lKeyProject,file_Key_,"Content",0)
		m2m [rcx].OFile.FileName			,file_Key_
		mov [rcx].OFile.viewer				,0	 
		mov [rcx].OFile.buffer				,0
		mov [rcx].OFile.Modified			,0
		mov [rcx].OFile.NotebookPage		,0			
		mov [rcx].OFile.Path				,0	
		mov [rcx].OFile.content				,0	
		
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
	folding_processing_Text proto :gpointer,:gint
	Files_Text_Buffer_Changed PROC __textbuffer:gpointer,_pOFile:gpointer
		local textbuffer:gpointer
		local pOFile:gpointer
			mov pOFile,_pOFile	
			mov rax,pOFile
			mov [rax].OFile.Modified,-1
			mov textbuffer,__textbuffer
 
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
		local FileName :gpointer	
		local SScheme:gpointer

        local GGtkSourceStyleScheme :gpointer
        
		mov pOFile,_pOFile
		mov rax,pOFile		
		m2m FileName,[rax].OFile.FileName  
		mov rax,pOFile		
		mov rax,pOFile		
		mov rax,pOFile
		.if	[rax].OFile.Path
    			mov FullPName,rv(g_build_filename,[rax].OFile.Path,[rax].OFile.FileName,0)		
		.else
			.if	[rax].OFile.Dir
				mov FullPName,rv(g_build_filename,Current_Prj_Path,[rax].OFile.Dir,[rax].OFile.FileName,0)
			.else
				mov FullPName,rv(g_build_filename,Current_Prj_Path,FileName,0)
			.endif
		.endif
 
        .if rv(g_file_get_contents,FullPName,addr lfcontents, 0, 0)
		invoke gtk_source_buffer_new,0
		mov rcx,pOFile
		mov [rcx].OFile.buffer,rax
		mov bufaddr,rax
;---------------------------------------------------------------------------------------------------------------
		;invoke g_signal_connect_data,bufaddr ,str$("changed")   ,addr buffer_insert_text,pOFile,0,0      
		invoke g_signal_connect_data,bufaddr,CStr("insert_text"),addr buffer_insert_text,pOFile,0,G_CONNECT_AFTER
		invoke g_signal_connect_data,bufaddr,CStr("delete-range"),addr On_Buffer_delete_range,pOFile,0,0;G_CONNECT_AFTER
		invoke g_signal_connect_data,bufaddr,CStr("delete-range"),addr On_Buffer_delete_range_AFTER,pOFile,0,G_CONNECT_AFTER
;---------------------------------------------------------------------------------------------------------------

		gtk_source_search_context_new (bufaddr, 0 )
		mov rcx,pOFile
		mov [rcx].OFile.search_context,rax
		mov rax,rcx
		invoke gtk_source_buffer_begin_not_undoable_action,bufaddr         		   	
		mov utf8 ,rv(g_locale_to_utf8 ,lfcontents, -1, 0, addr bytes_written, 0)
		mov rcx,pOFile
		m2m [rcx].OFile.Content,utf8
		
		invoke g_free,lfcontents
	;	invoke gtk_text_buffer_get_end_iter,bufaddr,addr lf_iter
	;	invoke gtk_text_buffer_insert,bufaddr ,addr lf_iter,utf8,-1
	;	invoke g_free,utf8
		invoke gtk_source_buffer_end_not_undoable_action ,bufaddr
		invoke gtk_text_buffer_set_modified,bufaddr,0
		invoke gtk_text_buffer_get_start_iter,bufaddr,addr lf_iter
		invoke gtk_text_buffer_place_cursor,bufaddr,addr lf_iter
		invoke g_signal_connect_data,bufaddr    ,str$("changed")    ,addr Files_Text_Buffer_Changed    ,pOFile,0,0      
	       	invoke g_signal_connect_data,bufaddr    ,str$("mark-set")    ,addr On_gtk_text_buffer_mark_set   ,pOFile,0,0      

		mov rcx,pOFile
		m2m PLanguage,[rcx].OFile.ProgrammingLanguage
		m2m SScheme,[rcx].OFile.StyleScheme
		mov GGtkSourceStyleScheme,rv( gtk_source_style_scheme_manager_get_scheme,GGtkSourceStyleSchemeManager,SScheme)
		invoke gtk_source_buffer_set_style_scheme,bufaddr, GGtkSourceStyleScheme         
		mov rax,pOFile
		;invoke gtk_source_language_manager_guess_language,GGtkSourceLanguageManager,[rax].OFile.FileName;;StyleScheme
		invoke gtk_source_language_manager_get_language,GGtkSourceLanguageManager,PLanguage
		
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
	Notebook_Get_Current_Buffer proto
	.data
		__Old__start_iter       GtkTextIter	<>
		__Old__end_iter         GtkTextIter    <>    	
	.code
	On_gtk_text_buffer_Selection_Changed PROC __Buffer:gpointer,_pOFile:gpointer
		local buf:gpointer
		local pOFile:gpointer
		local Sel_Text:gpointer
		local _search_settings:gpointer
		local _search_context:gpointer
		local __start_iter         :GtkTextIter
		local __end_iter           :GtkTextIter        
		
		mov buf,__Buffer
		mov pOFile,_pOFile
		mov rcx,pOFile
		m2m _search_context,[rcx].OFile.search_context
		mov _search_settings,rv(gtk_source_search_context_get_settings,_search_context)
		gtk_text_buffer_get_selection_bounds(buf,addr __Old__start_iter,addr __Old__end_iter)
		mov Sel_Text,rv(gtk_text_buffer_get_text,buf,addr __Old__start_iter,addr __Old__end_iter,0)	
		gtk_source_search_settings_set_search_text (_search_settings,Sel_Text)    
		g_free(Sel_Text)
		ret
	On_gtk_text_buffer_Selection_Changed ENDP

	On_gtk_text_buffer_mark_set PROC textbuffer__:gpointer,_d1:gpointer,_d2:gpointer,_pOFile:gpointer
		local buf:gpointer
		local pOFile:gpointer
		local __start_iter         :GtkTextIter
		local __end_iter           :GtkTextIter        
		mov buf,textbuffer__
		mov pOFile,_pOFile
		.if buf
		        .if rv(gtk_text_buffer_get_has_selection,buf)
		        	gtk_text_buffer_get_selection_bounds(buf,addr __start_iter,addr __end_iter)
		        	.if __Old__start_iter.dummy1==0
						On_gtk_text_buffer_Selection_Changed(buf,pOFile)
		        	.else
					.if gtk_text_iter_compare(addr __start_iter,addr __Old__start_iter)
						On_gtk_text_buffer_Selection_Changed(buf,pOFile)
					.else
						.if gtk_text_iter_compare(addr __end_iter,addr __Old__end_iter)
							On_gtk_text_buffer_Selection_Changed(buf,pOFile)
						.endif
					.endif			         	
		        	.endif
		        .endif
		.endif
		xor eax,eax
		ret
	On_gtk_text_buffer_mark_set ENDP
	
	
	Files_Get_OFile_From_Name PROC __fileName:gpointer
		local  _fileName:gpointer
		local OFilesIndex:gpointer
		mov _fileName,__fileName
		m2m OFilesIndex,Current_Prj_OFiles
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






	
