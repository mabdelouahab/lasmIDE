		include inputbox.asm
	.code
	MainWindow_CallBack_New_Empty_Project proc
		local prjname:gpointer
		local prjpath:gpointer
    	mov prjname,rv( user_input_box,".Input the new Project Name:","New project")
     	.if rax
  invoke printf,str$(<13,10,"prjname ={%s}",13,10>),prjname   
  		invoke Projects_Close_Current_Project,1
			invoke TreeView_Clear
            invoke g_chdir,firstworkingdir;HOMEdir;
invoke printf,str$(<13,10,"g_get_current_dir ={%s}",13,10>),rv(g_get_current_dir)   
        ;    invoke g_mkdir,ProgramdirStr,S_IRWXU
          ;  invoke g_chdir,ProgramdirStr
      ;      invoke g_mkdir,ProjectsPathStr,S_IRWXU            
            mov prjpath,rv(g_build_filename,ProjectsPath,prjname,0)
 	   g_chdir(ProjectsPath)
           invoke g_mkdir,prjname,S_IRWXU;prjpath
            invoke g_chdir,prjpath
			invoke 	Projects_Create_New_Empty_Project,prjname
			m2m 	Current_Project.Path	,prjpath	
			invoke 	Projects_Save_Current_Project
			call 	Projects_Save_Last_Project
			invoke 	TreeView_Show_Current_Project
    	.else
    	  invoke printf,str$(<13,10,"else prjname ={%s}",13,10>),prjname   

    	.endif		
		ret
	MainWindow_CallBack_New_Empty_Project endp	

	MainWindow_callback_Open_Project_From_List proc	instance:gpointer, _filename:gpointer

 
 
        local filename:gpointer
        local ltmpfilename:gpointer
        local ltmppath:gpointer
 
 
		
            mov filename,_filename                       
 		invoke printf,str$(<13,10,"Project_From_List ={%s}",13,10>),_filename   
 	;	ret
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
		invoke printf,str$(<13,10,"MainWindow_callback_Save_Project_As_Template ">)
		invoke printf,str$(<13,10>)
		ret
	MainWindow_callback_Save_Project_As_Template endp
	MainWindow_callback_New_Project_From_Template proc
		TemplateProjectDialog()
		.if WTemplateProjectDialog_RetValue
			Projects_Create_New_Project_From_Template(WTemplateProjectDialog_RetValue)
		.endif
		ret
	MainWindow_callback_New_Project_From_Template endp
	MainWindow_callback_ proc
		invoke printf,str$(<13,10,"MainWindow_callback_ ">)
		invoke printf,str$(<13,10>)
		ret
	MainWindow_callback_ endp	
	
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