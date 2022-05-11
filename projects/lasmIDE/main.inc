	__forcheck  typedef ptr
	IF(SIZEOF __forcheck eq 8)
		__UASM64__  EQU 1
	ENDIF
	OPTION LITERALS:ON
	OPTION DOTNAME 

	include	./muasm/mmacros.inc
	include 	./muasm/libc.inc
	include 	./muasm/unistd_64.inc
	include 	./muasm/glib.inc
	include 	./muasm/gtk.inc
	include 	./muasm/cairo.inc
	include include.inc

 
	include inputbox.asm
	include Helpers.inc
	include Settings.inc
	include FilesTypes.wedg
	include icons.inc
	include STNG.inc  
	

;	firstworkingdirStr			EQU str$("/shareddoc/programmation/lasm" );"/usr/share/iasm" )
;	ProgramdirStr				EQU str$("lasm" )
	
	TemporaryProjectPathStr		EQU str$("Temporary" )
	ProjectsPathStr				EQU str$("projects" )
	LangPathStr					EQU str$("langs" )
	IconsPathStr				EQU str$("Icons" )
	TemplatesPathStr			EQU str$("templates" )
.DATA    
	TemplatesPath			        gpointer 0
	IconsPath			 		gpointer 0
	LangPath			    		gpointer 0
	TemporaryProjectPath            	gpointer 0
	ProjectsPath            			gpointer 0
	firstworkingdir     			gpointer 0	
	HOMEdir     					gpointer 0	

	WNotebook                       		gpointer  0
	GcssProvider_Asm            		gpointer  0
	GcssProvider_C            		gpointer  0
	GGtkSourceLanguageManager    gpointer  0
	GGtkSourceStyleSchemeManager    gpointer  0
	GGtkBuilder                    	 	gpointer  0
	WMainwindow                		gpointer  0
	WPaned1                         		gpointer  0
	WPaned2                         		gpointer  0 ;contain Treeview and notbook
	NoteBookContainer             	gpointer  0
	WProjectTreeView               	gpointer  0

	work_key                			gpointer    0
	project_key             			gpointer    0

    completion                  gpointer 0
    provider                    gpointer 0

	NotebookPageArray   		gpointer    256 dup(0)   
	Arg_Project		                	gpointer  0
       
	include spawn.inc
	include build.inc   
	include findandreplace.wedg
	include files.inc
	include Wedg_Dialog_Project_Option.wedg    
	
	include Notebook.inc
	include TreeView.inc
	include Projects.inc
	include TemplateProjectDialog.wedg
	include mainwindow.wedg
	
   ; 	include folding.inc


.CODE
	gInit   PROC
		local _err:gpointer
		mov _err,0
		invoke gtk_init,0,0

		.if firstworkingdir==0
			IFDEF firstworkingdirStr
				invoke g_chdir,firstworkingdirStr
			ENDIF
			mov HOMEdir,rv(g_getenv,"HOME")
			mov firstworkingdir,rv(g_get_current_dir)
 
			mov TemporaryProjectPath,rv(g_build_filename,firstworkingdir,TemporaryProjectPathStr,0)
			mov ProjectsPath,rv(g_build_filename,firstworkingdir,ProjectsPathStr,0);,ProgramdirStr
 
			mov LangPath,rv(g_build_filename,firstworkingdir,LangPathStr,0)
			mov IconsPath,rv(g_build_filename,firstworkingdir,IconsPathStr,0)
			mov TemplatesPath,rv(g_build_filename,firstworkingdir,TemplatesPathStr,0)
		.endif
		
		invoke Settings_Load   ;Settings_Save     
		invoke Icons_Init
		.if WNotebook==0 
			mov WNotebook ,rv( gtk_notebook_new)
			invoke gtk_notebook_set_scrollable,WNotebook,-1
		.endif
		.if GcssProvider_Asm==0
			mov GcssProvider_Asm,rv(gtk_css_provider_new)
			invoke gtk_css_provider_load_from_path,GcssProvider_Asm, str$("./langs/font_ASM.css"),addr _err
		.endif
		.if GcssProvider_C==0
			mov GcssProvider_Asm,rv(gtk_css_provider_new)
			invoke gtk_css_provider_load_from_path,GcssProvider_Asm, str$("./langs/font_C.css"),addr _err
		.endif
		.if GGtkSourceLanguageManager==0
			mov GGtkSourceLanguageManager,rv(gtk_source_language_manager_new);            
			invoke gtk_source_language_manager_get_search_path,GGtkSourceLanguageManager 
			invoke appstrv,rax,LangPath
			invoke gtk_source_language_manager_set_search_path,GGtkSourceLanguageManager ,rax
		.endif

		.if GGtkSourceStyleSchemeManager==0
			mov GGtkSourceStyleSchemeManager,rv(gtk_source_style_scheme_manager_new)
			invoke  gtk_source_style_scheme_manager_append_search_path,GGtkSourceStyleSchemeManager, LangPath
		.endif
		ret
	gInit   ENDP
.DATA
	clear_project_tree_view_iter    GtkTreeIter <>
	clear_items_iter                GtkTreeIter <>
	c_clear_project_tree_view_iter  gpointer  0
	c_clear_items_iter  gpointer  0
        
 .CODE
 
	get_group_from_n_tab proc data_:gpointer
		local ldata:gpointer
		local llength:gpointer
		local plgroups:gpointer
		local lgroups:gpointer
		local lgroup:gpointer
		mov ldata,data_
		mov ldata,rv(gtk_notebook_get_nth_page,WNotebook,ldata)

		mov llength,0
		mov plgroups,rv( g_key_file_get_groups,work_key,addr llength)
		mov lgroups,rax
		.if llength        
			@@:
			mov rax,lgroups
			mov rax,gpointer ptr [rax]
			.if rax
				mov lgroup,rax
				invoke g_key_file_get_ptr ,work_key,lgroup,"NotebookPage",0
				.if rax==ldata
					mov lgroup,rv(g_strdup,lgroup)
					invoke g_strfreev,plgroups
					mov rax,lgroup
					RET
				.endif
				add lgroups,sizeof gpointer
				jmp @B
			.endif
			invoke g_strfreev,plgroups
		.else
		.endif        
		XOR rax,rax    
		RET
	get_group_from_n_tab endp 
	new_tab_from_project_key_file0 PROC _kfileg:gpointer
		local kfileg:gpointer
		local strkv :gpointer        
		mov kfileg,_kfileg
		mov strkv,rv(g_key_file_get_string,project_key,kfileg,"Name",0 )
		RET
	new_tab_from_project_key_file0 ENDP
	new_tab_from_non_project_key_file0 PROC _kfileg:gpointer
		local kfileg:gpointer
		local strkv :gpointer

		mov kfileg,_kfileg

		RET
	new_tab_from_non_project_key_file0 ENDP
	

 

    load_file_to_buf proc _bufaddr:gpointer,_fn:gpointer
        local bufaddr       :gpointer
        local fn            :gpointer
        local hfile         :gpointer
        local utf8          :gpointer
        local lfcontents    :gpointer
        local bytes_written :gpointer  
        local lf_iter       :GtkTextIter   
        
        mov bufaddr,_bufaddr
        mov fn,_fn
        .if fn ==0
        	invoke g_print,"load_file_to_buf ERR: Null filename"
        	ret
    	.endif
        mov lfcontents,0
    
        .if rv(g_file_get_contents,fn,addr lfcontents, 0, 0)
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
        .else
            invoke g_print,"file to open: %s\n", fn
        .endif
        ret
    load_file_to_buf endp


    save_tab_n  PROC    n_tab_:gpointer
        local n_tab                 :gpointer
        local k_file               :gpointer
        local fname                :gpointer
        local buffer               :gpointer
        local bndtxt               :gpointer
        local strkey               :gpointer
        local __start_iter         :GtkTextIter
        local __end_iter           :GtkTextIter        
        mov n_tab,n_tab_
        
        .if rv(get_group_from_n_tab,n_tab)
            mov fname,rax
           mov buffer ,rv( g_key_file_get_ptr ,work_key,fname     ,"buffer",0) 
           invoke gtk_text_buffer_get_bounds,buffer,addr __start_iter,addr __end_iter
           mov bndtxt ,rv( gtk_text_buffer_get_text,buffer,addr __start_iter,addr __end_iter,-1)
           mov strkey ,rv(g_key_file_get_string,project_key,fname,"Dir",0)
           .if rax==0
                invoke g_file_set_contents,fname,bndtxt,-1,0
           .else
                mov strkey,rv(g_build_filename,strkey,fname,0)
                invoke g_file_set_contents,strkey,bndtxt,-1,0
                invoke g_free,strkey        
           .endif               
        .endif                 
        RET
    save_tab_n  ENDP     
    save_all_tab proc
        local np:gpointer
        invoke gtk_notebook_get_n_pages,WNotebook
        .if rax
            mov np,rax
            @@:
            dec np
            invoke save_tab_n,np
            cmp np,0           
            jne @B            
        .endif
        ret
    save_all_tab endp
    save_current_tab    proc
        invoke gtk_notebook_get_current_page,WNotebook
        invoke save_tab_n,rax               
        ret 
    save_current_tab    endp   
    close_tab_n proc n_tab_:gpointer
        local n_tab                 :gpointer
        mov n_tab,n_tab_
        invoke save_tab_n, n_tab
        .if rv(get_group_from_n_tab,n_tab)
            invoke g_key_file_remove_group,work_key,rax,0
            invoke gtk_notebook_remove_page,WNotebook,n_tab      
        .endif            
        ret
    close_tab_n endp
    close_all_tab proc
        local np:gpointer
        invoke gtk_notebook_get_n_pages,WNotebook
        .if rax
            mov np,rax
            @@:
            dec np
            invoke close_tab_n,np
            cmp np,0           
            jne @B            
        .endif
        ret
    close_all_tab endp
    
    open_and_show_file PROC    _k_file:gpointer ,_fname:gpointer
        local k_file               :gpointer
        local fname                :gpointer
        local NotebookPage          :gpointer

        local GGtkSourceStyleScheme :gpointer
        local scrolledwindow        :gpointer
        local llabel                :gpointer
        local button                :gpointer
        local buffer                :gpointer
        local view                  :gpointer
        local context               :gpointer
        local hbox                  :gpointer

        local np:gpointer
        local strkey                :gpointer
        local strkey2               :gpointer
        
        mov k_file,_k_file
        mov fname,_fname
        invoke g_key_file_get_ptr,work_key,fname,"buffer",0;
        .if RAX
            mov NotebookPage,rv( g_key_file_get_ptr ,work_key,fname,"NotebookPage",0)
            invoke gtk_notebook_get_n_pages,WNotebook
            .if rax
                mov np,rax
                @@:
                dec np
                invoke gtk_notebook_get_nth_page,WNotebook,np
                .if rax==NotebookPage
                    invoke gtk_notebook_set_current_page        ,WNotebook,np                
                    MOV RAX,-1
                    RET
                .endif
                 cmp np,0           
                jne @B            
            .endif
            MOV RAX,-1
            RET
        .endif
        mov buffer,rv( gtk_source_buffer_new,0)
        invoke g_key_file_set_ptr ,work_key,fname,"buffer",buffer

        mov strkey,rv(g_key_file_get_string,k_file,fname,"ProgrammingLanguage",0)

	    mov GGtkSourceStyleScheme,rv( gtk_source_style_scheme_manager_get_scheme,GGtkSourceStyleSchemeManager,strkey)       
	    invoke gtk_source_buffer_set_style_scheme,buffer, GGtkSourceStyleScheme         
		        
      ;  invoke gtk_source_language_manager_get_language, GGtkSourceLanguageManager,strkey
		invoke gtk_source_language_manager_guess_language,GGtkSourceLanguageManager,fname,0
        invoke gtk_source_buffer_set_language ,buffer, rax
        
        mov view,rv( gtk_source_view_new_with_buffer,buffer)


        invoke gtk_source_view_set_show_line_numbers,view,Settings_SV_show_line_numbers
        invoke gtk_source_view_set_show_line_marks,view,Settings_SV_show_line_marks
        invoke gtk_source_view_set_auto_indent,view,Settings_SV_auto_indent

        
       invoke gtk_text_buffer_create_tag ,buffer,"invisible", "invisible", 1, 0
       
       
       

       mov strkey   ,rv(g_key_file_get_string,k_file,fname,"Dir",0)
       .if rax==0
           invoke load_file_to_buf,buffer,fname
       .else
           mov strkey,rv(g_build_filename,strkey,fname,0);Name
           invoke load_file_to_buf,buffer,strkey         
           invoke g_free,strkey        
       .endif       
    		;	Folding Example:
	       ;invoke gtk_text_buffer_set_text,buffer,addr ___d,-1
		;       invoke create_marks,view
		;       invoke place_mark,buffer,0,fold_plus
		;       invoke place_mark,buffer,1,fold_vert
		;       invoke place_mark,buffer,2,fold_vert
		;       invoke place_mark,buffer,3,fold_vert
		;       invoke place_mark,buffer,4,fold_end
		;       invoke place_mark,buffer,5,fold_minus
		; ;       invoke gtk_text_buffer_get_bounds ,buffer,addr startiter,addr enditer
		;invoke gtk_text_buffer_apply_tag_by_name,buffer,"invisible",addr startiter,addr enditer

        .if GcssProvider_Asm
            mov context,rv(gtk_widget_get_style_context,view)
    	   invoke gtk_style_context_add_provider,context, GcssProvider_Asm, 1
       .endif
        invoke gtk_source_buffer_set_highlight_syntax,buffer,-1        
        mov scrolledwindow,rv(gtk_scrolled_window_new,0,0)
        mov llabel, rv(gtk_label_new,fname) 
        ;*************************************            
	mov button,rv(gtk_button_new)			
	invoke gtk_button_set_relief,button,2

        invoke gtk_button_set_label,button,"x"
	invoke gtk_button_set_focus_on_click,button,-1
	;invoke g_signal_connect_data,button,str$("clicked"),addr OnTabNootBookCloseClickedCallback ,0,0,0     
	invoke g_signal_connect_data,button,str$("enter"),addr   Notebook_On_Close_Button_Clicked ,0,0,0     
	invoke g_signal_connect_data,button,str$("leave"),addr   Notebook_On_Close_Button_Clicked ,0,0,0  
	;invoke g_signal_connect_data,view,str$("line-mark-activated"),addr on_line_mark_activated ,buffer,0,0  
  
	invoke gtk_widget_show,button			
	mov hbox,rv(gtk_box_new,0,0)
	invoke gtk_box_set_spacing,hbox,0
	invoke gtk_container_add,hbox,llabel
	invoke gtk_container_add,hbox,button
	invoke gtk_widget_show_all,hbox        

        invoke gtk_container_add,scrolledwindow,view   
        mov NotebookPage,rv( gtk_notebook_append_page,WNotebook,scrolledwindow,hbox); label1 
        .if dword ptr eax < 0
            invoke g_print,str$(<13,10," gtk_notebook_append_page fail">)
        .else
            invoke g_signal_connect_data,button,str$("clicked"),addr Notebook_On_Close_Button_Clicked ,scrolledwindow,0,0     
            invoke g_print,str$(<13,10," gtk_notebook_append_page page n= %d ">),NotebookPage
            invoke g_print,str$(<13,10," gtk_notebook_append_page page n= %s ">),fname
            invoke g_key_file_set_ptr ,work_key,fname,"NotebookPage",scrolledwindow;NotebookPage
        .endif
        invoke gtk_widget_show_all ,   WNotebook  
        invoke gtk_notebook_set_current_page ,WNotebook,NotebookPage
  
        ret
    open_and_show_file ENDP
    

    include signal_connect.asm
    include inputbox.asm
 

