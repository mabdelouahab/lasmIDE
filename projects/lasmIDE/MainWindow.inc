		include inputbox.asm
	.code
	MainWindow_CallBack_New_Empty_Project proc
		local prjname:gpointer
		local prjpath:gpointer
    		mov prjname,rv( user_input_box,".Input the new Project Name:","New project")
	     	.if rax
	  		invoke Projects_Close_Current_Project,1
			invoke TreeView_Clear
		    	invoke g_chdir,firstworkingdir;HOMEdir;
			mov prjpath,rv(g_build_filename,ProjectsPath,prjname,0)
			g_chdir(ProjectsPath)
			invoke g_mkdir,prjname,S_IRWXU;prjpath
			invoke g_chdir,prjpath
			invoke 	Projects_Create_New_Empty_Project,prjname
			m2m 	Current_Prj_Path	,prjpath
			invoke 	Projects_Save_Current_Project
			call 	Projects_Save_Last_Project
			invoke 	TreeView_Show_Current_Project
	    	.endif		
		ret
	MainWindow_CallBack_New_Empty_Project endp	

	MainWindow_callback_Open_Project_From_List proc	instance:gpointer, _filename:gpointer
        local filename:gpointer
        local ltmpfilename:gpointer
        local ltmppath:gpointer
 
            mov filename,_filename                       
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
		ret
	MainWindow_callback_Open_Project_From_List endp	

	MainWindow_callback_Open_Project proc
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
		ret
	MainWindow_callback_Open_Project endp	
	MainWindow_callback_Save_Project_As_Template proc
		Projects_Create_New_Template_From_Current_Project()
		ret
	MainWindow_callback_Save_Project_As_Template endp
	MainWindow_callback_New_Project_From_Template proc
		Projects_Create_New_Project_From_Template()
		ret
	MainWindow_callback_New_Project_From_Template endp	
	MainWindow_callback_wQuit PROC
		invoke gtk_main_quit
		RET
	MainWindow_callback_wQuit   ENDP
    
	On_WMnTBUndo_activate PROC
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
		    .if rv(gtk_source_buffer_can_undo,buf)
				invoke gtk_source_buffer_undo,buf
			    .endif	
		.endif
		RET
	On_WMnTBUndo_activate ENDP
      
      
	On_WMnTBRedo_activate PROC  
	local buf:gpointer
	mov buf,rv(Notebook_Get_Current_Buffer)
	.if buf
	    .if rv(gtk_source_buffer_can_redo,buf)
			invoke gtk_source_buffer_redo,buf
		    .endif	
	.endif
		 RET
	On_WMnTBRedo_activate ENDP   	
	gtk_clipboard_get proto :vararg
_GDK_MAKE_ATOM = 69
GDK_SELECTION_CLIPBOARD = _GDK_MAKE_ATOM

	On_WMnTBCut_Clicked PROC
		local buf:gpointer
		local clipboard:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			mov clipboard,rv( gtk_clipboard_get,GDK_SELECTION_CLIPBOARD)
			gtk_text_buffer_cut_clipboard (buf, clipboard, -1)
		.endif
		Ret
	On_WMnTBCut_Clicked ENDP
	On_WMnTBCopy_Clicked PROC
		local buf:gpointer
		local clipboard:gpointer
		local text:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			mov clipboard,rv( gtk_clipboard_get,GDK_SELECTION_CLIPBOARD)
			gtk_text_buffer_copy_clipboard (buf, clipboard)
		.endif
		Ret
	On_WMnTBCopy_Clicked ENDP
	On_WMnTBPaste_Clicked PROC
		local buf:gpointer
		local clipboard:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			mov clipboard ,rv(gtk_clipboard_get,GDK_SELECTION_CLIPBOARD)
			gtk_text_buffer_paste_clipboard (buf, clipboard, 0, -1)
		.endif
		Ret
	On_WMnTBPaste_Clicked ENDP
	On_WMnTBDelete_Clicked PROC
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			        gtk_text_buffer_delete_selection (buf, 0, -1);
		.endif
		Ret
	On_WMnTBDelete_Clicked ENDP	
	
	
	
 	On_WMnTBFind_Clicked PROC
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			Init_WFARBox("Incomplete Code")
		.endif
		Ret
	On_WMnTBFind_Clicked ENDP
	On_WMnTBReplace_Clicked PROC
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			Init_WFARBox("Incomplete Code")
		.endif
		Ret
	On_WMnTBReplace_Clicked ENDP
   
 

    
	On_WMnSaveFile_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnSaveFile_Clicked ENDP
	On_WMnTBOpenFile_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnTBOpenFile_Clicked ENDP
	On_WMnTBNewFile_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnTBNewFile_Clicked ENDP
	On_WMnTBSaveAll_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnTBSaveAll_Clicked ENDP
	


	On_WMnTBUnindent_Clicked PROC
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			msgbox "Incomplete Code"
		.endif
		Ret
	On_WMnTBUnindent_Clicked ENDP
	On_WMnTBIndent_Clicked PROC
		local buf:gpointer
		mov buf,rv(Notebook_Get_Current_Buffer)
		.if buf
			msgbox "Incomplete Code"
		.endif
		Ret
	On_WMnTBIndent_Clicked ENDP

 
	On_WMnNewFile_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnNewFile_Clicked ENDP
	On_WMn_NewFile_asm_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_NewFile_asm_Clicked ENDP
	On_WMn_NewFile_inc_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_NewFile_inc_Clicked ENDP
	On_WMn_NewFile_wedg_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_NewFile_wedg_Clicked ENDP
	On_WMn_NewFile_rc_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_NewFile_rc_Clicked ENDP
	On_WMn_NewFile_c_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_NewFile_c_Clicked ENDP
	On_WMn_NewFile_h_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_NewFile_h_Clicked ENDP
	On_WMn_NewFile_txt_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_NewFile_txt_Clicked ENDP
	On_WMn_NewFile_xml_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_NewFile_xml_Clicked ENDP
	On_WMn_NewFile_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_NewFile_Clicked ENDP
	On_WMnOpenFile_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnOpenFile_Clicked ENDP
	On_WMnSaveAs_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnSaveAs_Clicked ENDP
	On_WMnSaveAll_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnSaveAll_Clicked ENDP

	On_WMnFind_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnFind_Clicked ENDP
	On_WMnFindAndReplace_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnFindAndReplace_Clicked ENDP
	On_WMnSellectAll_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnSellectAll_Clicked ENDP
	On_WMnNewProject_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnNewProject_Clicked ENDP
	On_WMnBrowse_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnBrowse_Clicked ENDP
	On_WMn_AddFile_asm_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_AddFile_asm_Clicked ENDP
	On_WMn_AddFile_inc_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_AddFile_inc_Clicked ENDP
	On_WMn_AddFile_wedg_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_AddFile_wedg_Clicked ENDP
	On_WMn_AddFile_rc_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_AddFile_rc_Clicked ENDP
	On_WMn_AddFile_c_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_AddFile_c_Clicked ENDP
	On_WMn_AddFile_h_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_AddFile_h_Clicked ENDP
	On_WMn_AddFile_txt_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_AddFile_txt_Clicked ENDP
	On_WMn_AddFile_xml_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_AddFile_xml_Clicked ENDP
	On_WMn_AddFile_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMn_AddFile_Clicked ENDP
	On_WMnAssemble_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnAssemble_Clicked ENDP
	On_WMnLink_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnLink_Clicked ENDP
	On_WMnBuild_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnBuild_Clicked ENDP
	On_WMnRun_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnRun_Clicked ENDP
	On_WMnDoAll_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnDoAll_Clicked ENDP
	On_WMnSetting_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnSetting_Clicked ENDP
	On_WMnAbout_Clicked PROC
		msgbox "Incomplete Code"
		Ret
	On_WMnAbout_Clicked ENDP
	 
    
