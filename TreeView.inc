	.DATA
	        TreeView_Project_Iter           	GtkTreeIter <>
	        TreeView_Dir_Iter            		GtkTreeIter <>
	        TreeView_Last_Dir            		gpointer 0
	        
	        TreeView_Selection			gpointer	0
 			GDK_TYPE_PIXBUF         		gpointer    0
	        WProjectTreeStore       		gpointer    0
	        
	
	Projects_Insert_File proto	:gpointer   
	Projects_Save_Current_Project	proto
	.code
    enum    TreeView_BMP_COLUMN, TreeView_TEXT_COLUMN, TreeView_TYPE_COLUMN,TreeView_DATA_COLUMN

    .proc TreeView_Show_PopUp_Menu_For_File 	,treeview:gpointer, event:gpointer,  pOfile:gpointer
        local menu:gpointer
        local menuitem:gpointer
    .shadow
    
        mov menu , rv(gtk_menu_new)
        mov rax,pOfile
        mov menuitem , rv(gtk_menu_item_new_with_label,"Remove from project")        
        invoke g_signal_connect_data,menuitem    ,str$("activate"),addr TreeView_PopUp_Menu_File_Remove_From_Project ,pOfile,0,0 
        invoke gtk_menu_shell_append,menu,menuitem
        mov menuitem , rv(gtk_menu_item_new_with_label,"Rename")        
        invoke g_signal_connect_data,menuitem    ,str$("activate") ,addr TreeView_PopUp_Menu_File_Rename ,pOfile,0,0 
        invoke gtk_menu_shell_append,menu,menuitem
            
        invoke gtk_widget_show_all,menu
        invoke gdk_event_get_time,event
        invoke gtk_menu_popup,menu, 0, 0, 0, 0, 0,rax
    .endp    
    .proc TreeView_PopUp_Menu_File_Rename	  				, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
   		invoke printf,str$(<13,10,"TreeView_PopUp_Menu_File_Rename">)
    	mov TreeView_Last_Dir,0
   	.endp
    .proc TreeView_PopUp_Menu_File_Remove_From_Project	, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	invoke printf,str$(<13,10,"TreeView_PopUp_Menu_File_Remove_From_Project">)
    	mov TreeView_Last_Dir,0
   	.endp
  	.proc TreeView_Show_PopUp_Menu_For_Directory 	,treeview:gpointer, event:gpointer,  userdata:gpointer

        local menu:gpointer
        local menuitem:gpointer
		local _FilesTypeListe:gpointer
        local __addStr	:gpointer
    .shadow
        mov menu , rv(gtk_menu_new)
				
		.if userdata==0	;	Project node		
		    mov menuitem , rv(gtk_menu_item_new_with_label,"Add New directory")        
		    invoke g_signal_connect_data,menuitem    ,str$("activate")    ,addr TreeView_PopUp_Menu_Project_Add_New_Directory ,userdata,0,0 
		    invoke gtk_menu_shell_append,menu,menuitem	
		.else			;	directory node
		    mov menuitem , rv(gtk_menu_item_new_with_label,"Rename directory")        
		    invoke g_signal_connect_data,menuitem    ,str$("activate")    ,addr TreeView_PopUp_Menu_Directory_Rename_Directory ,userdata,0,0 
		    invoke gtk_menu_shell_append,menu,menuitem

		    mov menuitem , rv(gtk_menu_item_new_with_label,"Delete directoty")        
		    invoke g_signal_connect_data,menuitem    ,str$("activate")    ,addr TreeView_PopUp_Menu_Directory_Delete_Directoty ,userdata,0,0 
		    invoke gtk_menu_shell_append,menu,menuitem          
		.endif
 		gtk_separator_menu_item_new proto
        mov menuitem , rv(gtk_separator_menu_item_new)        
        invoke gtk_menu_shell_append,menu,menuitem

        mov menuitem , rv(gtk_menu_item_new_with_label,"Add new assembly file (.asm)")        
        invoke g_signal_connect_data,menuitem    ,str$("activate") ,addr TreeView_PopUp_Menu_Directory_Add_New_ASM ,userdata,0,0 
        invoke gtk_menu_shell_append,menu,menuitem

        mov menuitem , rv(gtk_menu_item_new_with_label,"Add new include file (.inc)")        
        invoke g_signal_connect_data,menuitem    ,str$("activate") ,addr TreeView_PopUp_Menu_Directory_Add_New_INC ,userdata,0,0 
        invoke gtk_menu_shell_append,menu,menuitem

        mov menuitem , rv(gtk_menu_item_new_with_label,"Add new wedgete file (.wedg)")        
        invoke g_signal_connect_data,menuitem    ,str$("activate") ,addr TreeView_PopUp_Menu_Directory_Add_New_WEDG ,userdata,0,0 
        invoke gtk_menu_shell_append,menu,menuitem

        mov menuitem , rv(gtk_separator_menu_item_new)        
        invoke gtk_menu_shell_append,menu,menuitem

        mov menuitem , rv(gtk_menu_item_new_with_label,"Add new c file (.c)")        
        invoke g_signal_connect_data,menuitem    ,str$("activate") ,addr TreeView_PopUp_Menu_Directory_Add_New_C ,userdata,0,0 
        invoke gtk_menu_shell_append,menu,menuitem

        mov menuitem , rv(gtk_menu_item_new_with_label,"Add new header file (.h)")        
        invoke g_signal_connect_data,menuitem    ,str$("activate") ,addr TreeView_PopUp_Menu_Directory_Add_New_H ,userdata,0,0 
        invoke gtk_menu_shell_append,menu,menuitem

        mov menuitem , rv(gtk_menu_item_new_with_label,"Add new text file (.txt)")        
        invoke g_signal_connect_data,menuitem    ,str$("activate") ,addr TreeView_PopUp_Menu_Directory_Add_New_TXT ,userdata,0,0 
        invoke gtk_menu_shell_append,menu,menuitem

        mov menuitem , rv(gtk_menu_item_new_with_label,"Add new ressource file (.rc)")        
        invoke g_signal_connect_data,menuitem    ,str$("activate") ,addr TreeView_PopUp_Menu_Directory_Add_New_RC ,userdata,0,0 
        invoke gtk_menu_shell_append,menu,menuitem

        mov menuitem , rv(gtk_menu_item_new_with_label,"Add new xml file (.xml)")        
        invoke g_signal_connect_data,menuitem    ,str$("activate") ,addr TreeView_PopUp_Menu_Directory_Add_New_XML ,userdata,0,0 
        invoke gtk_menu_shell_append,menu,menuitem

        mov menuitem , rv(gtk_menu_item_new_with_label,"Add new file ")        
        invoke g_signal_connect_data,menuitem    ,str$("activate") ,addr TreeView_PopUp_Menu_Directory_Add_New_ANY ,userdata,0,0 
        invoke gtk_menu_shell_append,menu,menuitem

;**********************************************************
        mov menuitem , rv(gtk_separator_menu_item_new)        
        invoke gtk_menu_shell_append,menu,menuitem
        	m2m _FilesTypeListe,Settings_FilesTypeListe
		.if _FilesTypeListe
		 @@: 
		   	mov rax,_FilesTypeListe    
		   	mov rax,[rax] 
		 	.if  rax
		 		mov userdata,rax
		 		Settings_Get_Files_Type(rax)
		 		mov __addStr,rv(g_strconcat,str$("Add new "),TFile_Type_ST__Name,str$("  (*."),TFile_Type_ST_Extention,str$(") "),0)
				mov menuitem , rv(gtk_menu_item_new_with_label,__addStr)        
				invoke g_signal_connect_data,menuitem    ,str$("activate") ,addr TreeView_PopUp_Menu_Directory_Add_New_Files_Type ,userdata,0,0 
				invoke gtk_menu_shell_append,menu,menuitem
				invoke g_free ,__addStr
		 		add _FilesTypeListe,8
		 		jmp @B
		 	.endif
		.endif

;***********************************************************
        invoke gtk_widget_show_all,menu
        invoke gdk_event_get_time,event
        invoke gtk_menu_popup,menu, 0, 0, 0, 0, 0,rax
    .endp   
    .proc TreeView_PopUp_Menu_Project_Add_New_Directory	, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	invoke printf,str$(<13,10,"TreeView_PopUp_Menu_Project_Add_New_Directory">)
    	mov TreeView_Last_Dir,0
   	.endp 
    .proc TreeView_PopUp_Menu_Directory_Rename_Directory	, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	invoke printf,str$(<13,10,"TreeView_PopUp_Menu_Directory_Rename_Directory">)
    	mov TreeView_Last_Dir,0
   	.endp
    .proc TreeView_PopUp_Menu_Directory_Delete_Directoty	, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	invoke printf,str$(<13,10,"TreeView_PopUp_Menu_Directory_Delete_Directoty">)
    	mov TreeView_Last_Dir,0
   	.endp   
    .proc TreeView_PopUp_Menu_Directory_Add_New_ASM		, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	;invoke user_input_box,"Input the new file name :  ","New file"
    	.if rv(Helpers_Input_Box_New_File,".asm")
			mov of,rv(Files_Create_ASM_File,rax)
			invoke Files_Save_Content,of
			invoke Projects_Insert_File,of   
			invoke Projects_Save_Current_Project
			TreeView_Show_File proto OFile__:gpointer,__DirIter:gpointer 
			.if _userdata
				invoke TreeView_Show_File,of,addr TreeView_Dir_Iter	
			.else
				invoke TreeView_Show_File,of,addr TreeView_Project_Iter	
			.endif
    	.endif
    	mov TreeView_Last_Dir,0
   	.endp
    .proc TreeView_PopUp_Menu_Directory_Add_New_INC		, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	;invoke user_input_box,"Input the new file name :  ","New file"
    	.if rv(Helpers_Input_Box_New_File,".inc")
			mov of,rv(Files_Create_INC_File,rax)
			invoke Files_Save_Content,of
			invoke Projects_Insert_File,of   
			invoke Projects_Save_Current_Project
 
			.if _userdata
				invoke TreeView_Show_File,of,addr TreeView_Dir_Iter	
			.else
				invoke TreeView_Show_File,of,addr TreeView_Project_Iter	
			.endif
    	.endif
    	mov TreeView_Last_Dir,0
   	.endp
    .proc TreeView_PopUp_Menu_Directory_Add_New_WEDG		, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	;invoke user_input_box,"Input the new file name :  ","New file"
    	.if rv(Helpers_Input_Box_New_File,".wedg")
			mov of,rv(Files_Create_WEDG_File,rax)
			invoke Files_Save_Content,of
			invoke Projects_Insert_File,of   
			invoke Projects_Save_Current_Project
 
			.if _userdata
				invoke TreeView_Show_File,of,addr TreeView_Dir_Iter	
			.else
				invoke TreeView_Show_File,of,addr TreeView_Project_Iter	
			.endif
    	.endif
    	mov TreeView_Last_Dir,0
   	.endp
    .proc TreeView_PopUp_Menu_Directory_Add_New_C		, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	;invoke user_input_box,"Input the new file name :  ","New file"
    	.if rv(Helpers_Input_Box_New_File,".c")
			mov of,rv(Files_Create_C_File,rax)
			invoke Files_Save_Content,of
			invoke Projects_Insert_File,of   
			invoke Projects_Save_Current_Project
 
			.if _userdata
				invoke TreeView_Show_File,of,addr TreeView_Dir_Iter	
			.else
				invoke TreeView_Show_File,of,addr TreeView_Project_Iter	
			.endif
    	.endif
    	mov TreeView_Last_Dir,0
   	.endp
    .proc TreeView_PopUp_Menu_Directory_Add_New_H		, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	;invoke user_input_box,"Input the new file name :  ","New file"
    	.if rv(Helpers_Input_Box_New_File,".hasm")
			mov of,rv(Files_Create_H_File,rax)
			invoke Files_Save_Content,of
			invoke Projects_Insert_File,of   
			invoke Projects_Save_Current_Project
 
			.if _userdata
				invoke TreeView_Show_File,of,addr TreeView_Dir_Iter	
			.else
				invoke TreeView_Show_File,of,addr TreeView_Project_Iter	
			.endif
    	.endif
    	mov TreeView_Last_Dir,0
   	.endp
    .proc TreeView_PopUp_Menu_Directory_Add_New_TXT	, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	;invoke user_input_box,"Input the new file name :  ","New file"
    	.if rv(Helpers_Input_Box_New_File,".txt")
			mov of,rv(Files_Create_TXT_File,rax)
			invoke Files_Save_Content,of
			invoke Projects_Insert_File,of   
			invoke Projects_Save_Current_Project
 
			.if _userdata
				invoke TreeView_Show_File,of,addr TreeView_Dir_Iter	
			.else
				invoke TreeView_Show_File,of,addr TreeView_Project_Iter	
			.endif
    	.endif
    	mov TreeView_Last_Dir,0
   	.endp
    .proc TreeView_PopUp_Menu_Directory_Add_New_RC	, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	;invoke user_input_box,"Input the new file name :  ","New file"
    	.if rv(Helpers_Input_Box_New_File,".rc")
			mov of,rv(Files_Create_RC_File,rax)
			invoke Files_Save_Content,of
			invoke Projects_Insert_File,of   
			invoke Projects_Save_Current_Project
 
			.if _userdata
				invoke TreeView_Show_File,of,addr TreeView_Dir_Iter	
			.else
				invoke TreeView_Show_File,of,addr TreeView_Project_Iter	
			.endif
    	.endif
    	mov TreeView_Last_Dir,0
   	.endp
    .proc TreeView_PopUp_Menu_Directory_Add_New_XML	, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	;invoke user_input_box,"Input the new file name :  ","New file"
    	.if rv(Helpers_Input_Box_New_File,".xml")
			mov of,rv(Files_Create_XML_File,rax)
			invoke Files_Save_Content,of
			invoke Projects_Insert_File,of   
			invoke Projects_Save_Current_Project
 
			.if _userdata
				invoke TreeView_Show_File,of,addr TreeView_Dir_Iter	
			.else
				invoke TreeView_Show_File,of,addr TreeView_Project_Iter	
			.endif
    	.endif
    	mov TreeView_Last_Dir,0
   	.endp
    .proc TreeView_PopUp_Menu_Directory_Add_New_ANY	, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	;invoke user_input_box,"Input the new file name :  ","New file"
    	xor rax,rax
    	.if rv(Helpers_Input_Box_New_File,rax)
			mov of,rv(Files_Create_ANY_File,rax)
			invoke Files_Save_Content,of
			invoke Projects_Insert_File,of   
			invoke Projects_Save_Current_Project
 
			.if _userdata
				invoke TreeView_Show_File,of,addr TreeView_Dir_Iter	
			.else
				invoke TreeView_Show_File,of,addr TreeView_Project_Iter	
			.endif
    	.endif
    	mov TreeView_Last_Dir,0
   	.endp
    .proc TreeView_PopUp_Menu_Directory_Add_New_Files_Type	, _menuitem:gpointer,  _userdata:gpointer
        local of:gpointer
    .shadow
    	Settings_Get_Files_Type(_userdata)
    	xor rax,rax
    	.if rv(Helpers_Input_Box_New_File,rax)
		mov of,rv(Files_Create_FT_File,rax,TFile_Type_ST__Name)
		invoke Files_Save_Content,of
		invoke Projects_Insert_File,of   
		invoke Projects_Save_Current_Project
 
		.if TreeView_Last_Dir
			invoke TreeView_Show_File,of,addr TreeView_Dir_Iter	
		.else
			invoke TreeView_Show_File,of,addr TreeView_Project_Iter	
		.endif
    	.endif
	mov TreeView_Last_Dir,0
    	mov TreeView_Last_Dir,0
   	.endp
        
	.proc TreeView_On_button_press_event , lwidget:gpointer,levent:gpointer,luser_data:gpointer

		local path	:gpointer
		local _dx,_dy
		local lValue	:gpointer
		local ltext	:gpointer
		local lDataU	:gpointer
		local lTreeModel	:gpointer
		local lTreeIter:GtkTreeIter
		local __path:gpointer
		
 	.shadow

        mov rax,levent
        .if ([rax].GdkEventButton._type == GDK_BUTTON_PRESS  &&  [rax].GdkEventButton.button == 3)
           invoke gtk_tree_selection_count_selected_rows,TreeView_Selection
           .if ( rax  <= 1) 
                mov rax,levent
                mov __path,0
                fld [rax].GdkEventButton.x
                fistp _dx
                fld [rax].GdkEventButton.y
                fistp _dy
                invoke gtk_tree_view_get_path_at_pos,WProjectTreeView,_dx,_dy,addr __path, 0, 0, 0       
                .if rax    
                    invoke gtk_tree_selection_unselect_all,TreeView_Selection 
                    invoke gtk_tree_selection_select_path,TreeView_Selection, __path 
                    invoke gtk_tree_path_free,__path                      
                .endif    
           .endif    
            invoke gtk_tree_selection_get_selected,TreeView_Selection,addr lTreeModel,addr lTreeIter
            .if rax
                invoke gtk_tree_model_get,lTreeModel			, addr lTreeIter, \
                						  TreeView_TYPE_COLUMN	,addr lValue,\
                						  TreeView_TEXT_COLUMN	,addr ltext, \  
                						  TreeView_DATA_COLUMN	,addr lDataU,-1
                 mov rax,lValue
                .if     BYTE PTR [RAX] == "P"
                	xor rax,rax
                	mov TreeView_Last_Dir,rax
                    invoke TreeView_Show_PopUp_Menu_For_Directory,lwidget,levent,rax
                .elseif BYTE PTR [RAX] == "D"
                	m2m TreeView_Last_Dir,ltext
                    invoke TreeView_Show_PopUp_Menu_For_Directory,lwidget,levent,ltext
                .elseif BYTE PTR [RAX] == "F"
                	xor rax,rax
                	mov TreeView_Last_Dir,rax                	
                	mov rax,[rax].OFile.FileName
                	mov lDataU,rax
                	;msgbox "TreeView_On_button_press______event %s",lDataU
                    invoke TreeView_Show_PopUp_Menu_For_File,lwidget,levent,lDataU
                .endif
                ;invoke  g_free,lValue
            .endif                    
            mov rax,-1           
        .else
            xor rax,rax
        .endif
	.endp
    .proc TreeView_initProjecttreeview   ,    pTreeView:gpointer
        local pPixBuf:gpointer
        local     pColumn:gpointer;
        local     pCellRenderer:gpointer;
    .shadow
        ;;;;row-activated
        invoke g_signal_connect_data,pTreeView    ,str$("button-press-event")    ,addr TreeView_On_button_press_event,0,0,0     
        ;;;;
        invoke g_signal_connect_data,pTreeView    ,str$("row-activated")    ,addr TreeView_On_row_activated    ,0,0,0     
        mov TreeView_Selection,rv(gtk_tree_view_get_selection,WProjectTreeView);
        
        mov GDK_TYPE_PIXBUF,rv(gdk_pixbuf_get_type)
        invoke gtk_tree_view_set_headers_visible,pTreeView, 0
    
        mov WProjectTreeStore ,rv(gtk_tree_store_new,4, GDK_TYPE_PIXBUF, G_TYPE_STRING,G_TYPE_POINTER,G_TYPE_POINTER)   
        invoke gtk_tree_store_append,WProjectTreeStore, addr TreeView_Project_Iter , 0
        
        mov pCellRenderer ,rv (gtk_cell_renderer_pixbuf_new);
        mov pColumn ,rv( gtk_tree_view_column_new_with_attributes,"Image",pCellRenderer,"pixbuf", TreeView_BMP_COLUMN,0)
        invoke gtk_tree_view_append_column,pTreeView, pColumn
        
        mov pCellRenderer ,rv(gtk_cell_renderer_text_new);
        mov pColumn ,rv( gtk_tree_view_column_new_with_attributes,"Label",pCellRenderer,"text", TreeView_TEXT_COLUMN,0)
        invoke gtk_tree_view_append_column,pTreeView , pColumn 
        
        invoke gtk_tree_view_set_model,pTreeView,WProjectTreeStore
    .endp    
    .proc TreeView_On_row_activated , ltree_view:gpointer,lpath:gpointer,lcolumn:gpointer,luser_data:gpointer
		local lTreeModel	:gpointer
		local lTreeIter:GtkTreeIter 
		local lValue	:gpointer
		local ltext	:gpointer
		local lDataU	:gpointer
        local lf_iter       :GtkTextIter   

    .shadow
        invoke gtk_tree_selection_get_selected,TreeView_Selection,addr lTreeModel,addr lTreeIter
        .if rax
            invoke gtk_tree_model_get,lTreeModel, addr lTreeIter, \
            						  TreeView_TYPE_COLUMN	,addr lValue,\
            						  TreeView_TEXT_COLUMN	,addr ltext,  \ 
            						  TreeView_DATA_COLUMN	,addr lDataU,-1
             mov rax,lValue
            .if     BYTE PTR [RAX] == "P"
        		invoke printf,str$(<13,10,"row-activatedTV project">)                		
            .elseif BYTE PTR [RAX] == "D"
        		invoke printf,str$(<13,10,"row-activatedTV Directory{%s}">),ltext            
            .elseif BYTE PTR [RAX] == "F"
				mov rax,lDataU
            	.if [rax].OFile.buffer==0
            		invoke Files_Load_contents,lDataU
 
            	.endif
            	mov rax,lDataU
            	.if [rax].OFile.buffer==0
            		invoke printf,str$(<13,10,"Unable to load {%s}">),[rax].OFile.FileName
            		ret
            	.endif
            	.if [rax].OFile.NotebookPage==0

            		invoke Notebook_Open_File,lDataU
 
					mov rax,lDataU
					invoke gtk_text_buffer_get_end_iter,[rax].OFile.buffer,addr lf_iter
 

					mov rax,lDataU
					invoke gtk_source_buffer_begin_not_undoable_action,[rax].OFile.buffer    
 
					mov rax,lDataU
 
					mov rax,lDataU
					invoke gtk_text_buffer_insert,[rax].OFile.buffer ,addr lf_iter,[rax].OFile.Content,-1
 ;mov rax,lDataU
;invoke g_signal_connect_data,[rax].OFile.buffer,CStr("insert_text"),addr buffer_insert_text,lDataU,0,G_CONNECT_AFTER
					mov rax,lDataU
					invoke gtk_source_buffer_end_not_undoable_action ,[rax].OFile.buffer 
 
					mov rax,lDataU
					invoke gtk_text_buffer_set_modified,[rax].OFile.buffer ,0
 
					mov rax,lDataU
					invoke g_free,[rax].OFile.Content
 
					mov rax,lDataU
					mov [rax].OFile.Modified,0
            	.else
            		invoke Notebook_Get_N,[rax].OFile.NotebookPage
            		invoke gtk_notebook_set_current_page,WNotebook,RAX
            	.endif        
 
           	        	
			mov rax,lDataU
        		mov rax,[rax].OFile.FileName
        		mov lDataU,rax                       
            .endif
 
            invoke  g_free,ltext
 
        .endif
        xor rax,rax
    .endp    
    .proc TreeView_Show_Directory , DirName_:gpointer
 	.shadow
        invoke gtk_tree_store_append,WProjectTreeStore,addr TreeView_Dir_Iter,addr TreeView_Project_Iter
        invoke gtk_tree_store_set,WProjectTreeStore		,addr TreeView_Dir_Iter,\
        						  TreeView_BMP_COLUMN	, Icons_FLDRC_PixBuf,\
        						  TreeView_TEXT_COLUMN	, DirName_,\
        						  TreeView_TYPE_COLUMN	,"D",-1
        lea rax,TreeView_Dir_Iter
    .endp
    .proc TreeView_Show_File , OFile_:gpointer,_DirIter:gpointer       
        local lIcon_PixBuf	:gpointer        
        local lfile_Iter	: GtkTreeIter 
    .shadow    
        mov rax,OFile_
        mov lIcon_PixBuf,rv(Files_Get_File_Icon_PixBuf,OFile_)
        invoke gtk_tree_store_append,WProjectTreeStore,addr lfile_Iter,_DirIter    
        mov rax,OFile_
        mov r12,[rax].OFile.FileName
        invoke gtk_tree_store_set,WProjectTreeStore		,addr lfile_Iter,\
        						  TreeView_BMP_COLUMN	,lIcon_PixBuf,\
        						  TreeView_TEXT_COLUMN	,r12,\
        						  TreeView_TYPE_COLUMN	,"F",\
        						  TreeView_DATA_COLUMN	,OFile_ 		,-1
    .endp
	.proc TreeView_Clear	
	 	.if WProjectTreeStore==0
	 		ret
        .endif  
		invoke gtk_tree_store_clear,WProjectTreeStore
	    mov WProjectTreeStore ,rv(gtk_tree_store_new,4, GDK_TYPE_PIXBUF, G_TYPE_STRING,G_TYPE_POINTER,G_TYPE_POINTER)
	    invoke gtk_tree_store_append,WProjectTreeStore, addr TreeView_Project_Iter , 0
	    invoke gtk_tree_view_set_model,WProjectTreeView,WProjectTreeStore	
	.endp
    .proc TreeView_Show_Current_Project   
        local lfiles:gpointer
        local lDirs:gpointer        
        local lfile:gpointer
        local lDir:gpointer        
        .if WProjectTreeView==0
            mov WProjectTreeView  ,rv(gtk_builder_get_object, GGtkBuilder,str$("WProjectTreeView"))
            invoke TreeView_initProjecttreeview,WProjectTreeView
        .endif
        .if WProjectTreeStore==0
            invoke TreeView_initProjecttreeview,WProjectTreeView
        .endif  
        invoke gtk_tree_store_set,WProjectTreeStore		, addr TreeView_Project_Iter ,\
        						  TreeView_BMP_COLUMN	, Icons_PRJ_PixBuf,\
        						  TreeView_TEXT_COLUMN	, Current_Prj_Name,\
        						  TreeView_TYPE_COLUMN	, "P", -1

    						  
        m2m lDirs,Current_Prj_Dirs
		.if lDirs
		    @TreeView_Show_Current_Project_Dirs@:
			mov rax,lDirs
			mov rax,gpointer ptr [rax]
			mov lDir,rax
			.if rax
				invoke TreeView_Show_Directory,rax
				m2m lfiles,Current_Prj_OFiles
				.if lfiles
					@TreeView_Show_Current_Project_Dirs_File@:
					mov rax,lfiles
					mov rax,gpointer ptr [rax]
					mov lfile,rax
					.if rax
						.if rv(g_strcmp0,[rax].OFile.Dir,lDir) == 0  
							invoke TreeView_Show_File,lfile,addr TreeView_Dir_Iter
						.endif					
						add lfiles,sizeof gpointer    			
						jmp @TreeView_Show_Current_Project_Dirs_File@
					.endif
				.endif				
				add lDirs,sizeof gpointer    			
				jmp @TreeView_Show_Current_Project_Dirs@
			.endif
		.endif
		m2m lfiles,Current_Prj_OFiles
		.if lfiles
			@TreeView_Show_Current_Project_File@:
			mov rax,lfiles
			mov rax,gpointer ptr [rax]
			mov lfile,rax
			.if rax
				.if [rax].OFile.Dir == 0  
					invoke TreeView_Show_File,lfile,addr TreeView_Project_Iter
				.endif					
				add lfiles,sizeof gpointer    			
				jmp @TreeView_Show_Current_Project_File@
			.endif
		.endif				

    .endp
