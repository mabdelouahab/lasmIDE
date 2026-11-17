		include inputbox.asm
	gtk_clipboard_get proto :vararg
	_GDK_MAKE_ATOM = 69
	GDK_SELECTION_CLIPBOARD = _GDK_MAKE_ATOM

	.code
	.proc MainWindow_CallBack_New_Empty_Project  
		local prjname:gpointer
		local prjpath:gpointer
    		mov prjname,rv( user_input_box,".Input the new Project Name:","New project")
	     	.if rax
	  		invoke Projects_Close_Current_Project,0
			invoke TreeView_Clear
		    	invoke g_chdir,firstworkingdir;HOMEdir;
			mov prjpath,rv(g_build_filename,ProjectsPath,prjname,0)
			g_chdir(ProjectsPath)
			invoke g_mkdir,prjname,01c0h
			invoke g_chdir,prjpath
			invoke 	Projects_Create_New_Empty_Project,prjname
			m2m 	Current_Prj_Path	,prjpath
			invoke 	Projects_Save_Current_Project
			call 	Projects_Save_Last_Project
			invoke 	TreeView_Show_Current_Project
	    	.endif		
	.endp	 
	.proc MainWindow_callback_Open_Project_From_List ,	instance:gpointer, filename:gpointer
        local ltmpfilename:gpointer
        local ltmppath:gpointer
	.shadow                      
			.if Current_Project.Path
				mov ltmpfilename,rv( g_path_get_basename,filename)
				mov ltmppath,rv(g_path_get_dirname,filename)
				.if rv(g_strcmp0,Current_Project.Path,ltmppath) == 0 
					.if rv(g_strcmp0,Current_Project.FileName,ltmpfilename) == 0  
						invoke g_free,ltmpfilename
						invoke g_free,ltmppath
						ret			
					.endif		
				.endif
				invoke g_free,ltmpfilename
				invoke g_free,ltmppath
			.endif
    		invoke Projects_Close_Current_Project,0
    		.if rax==0
				invoke TreeView_Clear
				invoke Projects_Load_Project,filename
				invoke TreeView_Show_Current_Project
    		.endif
	.endp	 
	.proc MainWindow_callback_Open_Project  
        local dialog:gpointer
        local res:gpointer
        local filename:gpointer
        local ltmpfilename:gpointer
        local ltmppath:gpointer
        local filter:gpointer
		xor rax,rax
        __@action = GTK_FILE_CHOOSER_ACTION_OPEN
        mov dialog,rv(gtk_file_chooser_dialog_new,"Open File",WMainwindow,__@action,"_Cancel",GTK_RESPONSE_CANCEL,"_Open",GTK_RESPONSE_ACCEPT,0)
		gtk_file_chooser_set_current_folder(dialog,ProjectsPath)        
        mov filter,rv(gtk_file_filter_new)
        invoke gtk_file_filter_set_name,filter,"Assembly Project"
        invoke gtk_file_filter_add_pattern,filter,"*.aprj"
        invoke gtk_file_chooser_add_filter,dialog,filter
        mov res,rv(gtk_dialog_run,dialog)
        .if eax==GTK_RESPONSE_ACCEPT
            mov filename,rv(gtk_file_chooser_get_filename,dialog)                            
			invoke gtk_widget_destroy,dialog
			.if Current_Project.Path
				mov ltmpfilename,rv( g_path_get_basename,filename)
				mov ltmppath,rv(g_path_get_dirname,filename)
				.if rv(g_strcmp0,Current_Project.Path,ltmppath) == 0 
					.if rv(g_strcmp0,Current_Project.FileName,ltmpfilename) == 0  
						invoke g_free,ltmpfilename
						invoke g_free,ltmppath
						ret			
					.endif		
				.endif
				invoke g_free,ltmpfilename
				invoke g_free,ltmppath
			.endif
    		invoke Projects_Close_Current_Project,0
    		.if rax==0
			invoke TreeView_Clear
			invoke Projects_Load_Project,filename
			invoke TreeView_Show_Current_Project
    		.endif
		.else
			invoke gtk_widget_destroy,dialog
		.endif	
	.endp	 	
	.proc MainWindow_callback_Save_Project_As_Template  
		Projects_Create_New_Template_From_Current_Project()
	.endp	 
	.proc MainWindow_callback_New_Project_From_Template  
		Projects_Create_New_Project_From_Template()
	.endp 
;--------------------------------------------------------
	.proc MainWindow_callback_wQuit	
		invoke gtk_paned_get_position,WPaned1
		invoke STNG_Set,stng_paned1_Position,eax

		invoke gtk_paned_get_position,WPaned2
		invoke STNG_Set,stng_paned2_Position,eax
		invoke Projects_Close_Current_Project,0
		invoke gtk_main_quit
	.endp  
;--------------------------------------------------------

	.proc 	On_WMnTBUndo_activate	
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
		    .if rv(gtk_source_buffer_can_undo,buf)
				invoke gtk_source_buffer_undo,buf
			    .endif	
		.endif
	.endp	  
	.proc	On_WMnTBRedo_activate	  
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			.if rv(gtk_source_buffer_can_redo,buf)
				invoke gtk_source_buffer_redo,buf
				.endif	
		.endif
	.endp 
	.proc	On_WMnTBCut_Clicked	
		local buf:gpointer
		local clipboard:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			mov clipboard,rv( gtk_clipboard_get,GDK_SELECTION_CLIPBOARD)
			gtk_text_buffer_cut_clipboard (buf, clipboard, -1)
		.endif
	.endp	 
	.proc	On_WMnTBCopy_Clicked	
		local buf:gpointer
		local clipboard:gpointer
		local text:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			mov clipboard,rv( gtk_clipboard_get,GDK_SELECTION_CLIPBOARD)
			gtk_text_buffer_copy_clipboard (buf, clipboard)
		.endif
	.endp	  
	.proc	On_WMnTBPaste_Clicked	
		local buf:gpointer
		local clipboard:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			mov clipboard ,rv(gtk_clipboard_get,GDK_SELECTION_CLIPBOARD)
			gtk_text_buffer_paste_clipboard (buf, clipboard, 0, -1)
		.endif
	.endp	 
	.proc	On_WMnTBDelete_Clicked	
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			        gtk_text_buffer_delete_selection (buf, 0, -1);
		.endif
	.endp	 	
 	.proc 	On_WMnTBFind_Clicked	
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			Init_WFARBox()
		.endif
	.endp	 
	.proc	On_WMnTBReplace_Clicked	
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			Init_WFARBox()
		.endif
	.endp	 
 	.proc 	On_WMnSaveFile_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnTBOpenFile_Clicked	
		msgbox "Incomplete Code"
	.endp	  
	.proc	On_WMnTBNewFile_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnTBSaveAll_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnTBUnindent_Clicked	
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			msgbox "Incomplete Code"
		.endif
	.endp	 
	.proc	On_WMnTBIndent_Clicked	
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			msgbox "Incomplete Code"
		.endif
	.endp	 
	.proc	On_WMnNewFile_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_NewFile_asm_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_NewFile_inc_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_NewFile_wedg_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_NewFile_rc_Clicked	
		msgbox "Incomplete Code"
	.endp	  
	.proc	On_WMn_NewFile_c_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_NewFile_h_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_NewFile_txt_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_NewFile_xml_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_NewFile_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnOpenFile_Clicked	
		msgbox "Incomplete Code"
	.endp	  
	.proc	On_WMnSaveAs_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnSaveAll_Clicked	
		msgbox "Incomplete Code"
	.endp	 

	.proc 	On_WMnFind_Clicked	
		msgbox "Incomplete Code"
	.endp 
	.proc	On_WMnFindAndReplace_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnSellectAll_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnNewProject_Clicked	
		msgbox "Incomplete Code"
	.endp	  
	.proc	On_WMnBrowse_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_AddFile_asm_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_AddFile_inc_Clicked	
		msgbox "Incomplete Code"
	.endp	  
	.proc	On_WMn_AddFile_wedg_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_AddFile_rc_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_AddFile_c_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_AddFile_h_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_AddFile_txt_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_AddFile_xml_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMn_AddFile_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnAssemble_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnLink_Clicked	
		msgbox "Incomplete Code"
	.endp	  
	.proc	On_WMnBuild_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnRun_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnDoAll_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnSetting_Clicked	
		msgbox "Incomplete Code"
	.endp	 
	.proc	On_WMnAbout_Clicked	
		invoke gtk_window_set_interactive_debugging,TRUE
	.endp	 
	 
    
