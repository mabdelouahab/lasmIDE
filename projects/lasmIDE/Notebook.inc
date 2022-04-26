.DATA
TOOL_TIPS dq 0
expander_window dq 0


.CODE

	Notebook_Get_Current_Viewer PROC
		local current_page:gpointer
		local OFilesIndex:gpointer
       		 mov current_page,rv( gtk_notebook_get_nth_page,WNotebook,rv(gtk_notebook_get_current_page,WNotebook))
		m2m OFilesIndex,Current_Prj_OFiles
		.if OFilesIndex==0
			xor rax,rax
			ret
		.else
			@@:
			mov rax,OFilesIndex
			mov rax,gpointer ptr [rax]
		 	.if rax
		 		mov rcx,[rax].OFile.NotebookPage
		 		.if rcx==current_page
		 			mov rax,[rax].OFile.viewer
		 			ret
		 		.endif
				add OFilesIndex	,sizeof gpointer   			 			
				jmp @B
			.endif			
		.endif
        xor rax,rax
        RET
	Notebook_Get_Current_Viewer ENDP


	Notebook_Get_Current_Buffer PROC
		local current_page:gpointer
		local OFilesIndex:gpointer
        	mov current_page,rv( gtk_notebook_get_nth_page,WNotebook,rv(gtk_notebook_get_current_page,WNotebook))
		m2m OFilesIndex,Current_Prj_OFiles
		.if OFilesIndex==0
			xor rax,rax
			ret
		.else
			@@:
			mov rax,OFilesIndex
			mov rax,gpointer ptr [rax]
		 	.if rax
		 		mov rcx,[rax].OFile.NotebookPage
		 		.if rcx==current_page
		 			mov rax,[rax].OFile.buffer
		 			ret
		 		.endif
				add OFilesIndex	,sizeof gpointer   			 			
				jmp @B
			.endif			
		.endif
        xor rax,rax
        RET
	Notebook_Get_Current_Buffer ENDP
	Notebook_Get_Current_FileName PROC
		local current_page:gpointer
		local OFilesIndex:gpointer
        	mov current_page,rv( gtk_notebook_get_nth_page,WNotebook,rv(gtk_notebook_get_current_page,WNotebook))
		m2m OFilesIndex,Current_Prj_OFiles
		.if OFilesIndex==0
			xor rax,rax
			ret
		.else
			@@:
			mov rax,OFilesIndex
			mov rax,gpointer ptr [rax]
		 	.if rax
		 		mov rcx,[rax].OFile.NotebookPage
		 		.if rcx==current_page
		 			mov rax,[rax].OFile.FileName
		 			ret
		 		.endif
				add OFilesIndex	,sizeof gpointer   			 			
				jmp @B
			.endif			
		.endif
        xor rax,rax
        RET
	Notebook_Get_Current_FileName ENDP
	Notebook_Get_Current_OFile PROC
		local current_page:gpointer
		local OFilesIndex:gpointer
        	mov current_page,rv( gtk_notebook_get_nth_page,WNotebook,rv(gtk_notebook_get_current_page,WNotebook))
		m2m OFilesIndex,Current_Prj_OFiles
		.if OFilesIndex==0
			xor rax,rax
			ret
		.else
			@@:
			mov rax,OFilesIndex
			mov rax,gpointer ptr [rax]
		 	.if rax
		 		mov rcx,[rax].OFile.NotebookPage
		 		.if rcx==current_page
		 			ret
		 		.endif
				add OFilesIndex	,sizeof gpointer   			 			
				jmp @B
			.endif			
		.endif
        xor rax,rax
        RET
	Notebook_Get_Current_OFile ENDP
	Notebook_Get_N PROC	_NotebookPage:gpointer
		local NotebookPage:gpointer
		local nbkIndex:gpointer
		mov NotebookPage,_NotebookPage
		mov nbkIndex,rv( gtk_notebook_get_n_pages,WNotebook)
		.if nbkIndex
		    @@:
		    dec nbkIndex
		    invoke gtk_notebook_get_nth_page,WNotebook,nbkIndex
		    .if rax==NotebookPage
		        MOV RAX,nbkIndex
		        RET
		    .endif
		    cmp nbkIndex,0           
		    jnz @B            
		.endif
		MOV RAX,-1
		RET
	Notebook_Get_N ENDP
	Notebook_Save_Current_Tab PROC
		local dir		               :gpointer
		local buffer               :gpointer
		local fname                :gpointer
		local bndtxt               :gpointer
		local _Ofile:gpointer
		local __start_iter         :GtkTextIter
		local __end_iter           :GtkTextIter        
		mov _Ofile,rv(Notebook_Get_Current_OFile)
		.if _Ofile
			.if [rax].OFile.Modified
				mov rcx,rax
				m2m fname,[rcx].OFile.FileName
				m2m buffer,[rcx].OFile.buffer       	
				m2m dir,[rcx].OFile.Dir       	
				invoke gtk_text_buffer_get_bounds,buffer,addr __start_iter,addr __end_iter
				mov bndtxt ,rv( gtk_text_buffer_get_text,buffer,addr __start_iter,addr __end_iter,-1)
				.if Dir==0
					invoke g_file_set_contents,fname,bndtxt,-1,0
				.else
					mov fname,rv(g_build_filename,Dir,fname,0)
					invoke g_file_set_contents,fname,bndtxt,-1,0
					invoke g_free,fname        
				.endif           
				mov rax, _Ofile
				mov [rax].OFile.Modified,0				                 
			.endif
		.endif
		ret
	Notebook_Save_Current_Tab ENDP	
	Notebook_Save_All_Tab PROC
		local OFilesIndex:gpointer
		local dir		               :gpointer
		local buffer               :gpointer
		local fname                :gpointer
		local bndtxt               :gpointer
		local _Ofile:gpointer
		local __start_iter         :GtkTextIter
		local __end_iter           :GtkTextIter        
		m2m OFilesIndex,Current_Prj_OFiles
		.if OFilesIndex==0
			xor rax,rax
			ret
		.else
			@@:
			mov rax,OFilesIndex
			mov rax,gpointer ptr [rax]
		 	.if rax
				.if [rax].OFile.Modified
					mov _Ofile,rax
					mov rcx,rax
					m2m fname,[rcx].OFile.FileName
					m2m buffer,[rcx].OFile.buffer       	
					m2m dir,[rcx].OFile.Dir       	
					invoke gtk_text_buffer_get_bounds,buffer,addr __start_iter,addr __end_iter
					mov bndtxt ,rv( gtk_text_buffer_get_text,buffer,addr __start_iter,addr __end_iter,-1)
					.if Dir==0
						invoke g_file_set_contents,fname,bndtxt,-1,0
					.else
						mov fname,rv(g_build_filename,Dir,fname,0)
						invoke g_file_set_contents,fname,bndtxt,-1,0
						invoke g_free,fname        
					.endif           
					mov rax, _Ofile
					mov [rax].OFile.Modified,0				                 
				.endif
				add OFilesIndex	,sizeof gpointer   			 			
				jmp @B
			.endif			
		.endif
		xor rax,rax
		RET
	Notebook_Save_All_Tab ENDP
	Notebook_Close_Tab PROC _pOFile:gpointer
		local pOFile		:gpointer               
		mov pOFile,_pOFile
		mov rax,pOFile
		invoke Notebook_Get_N,[rax].OFile.NotebookPage
		invoke  gtk_notebook_remove_page,WNotebook,rax;
	
		ret
	Notebook_Close_Tab ENDP	
	Notebook_Close_All_Tabs PROC
	
		ret
	Notebook_Close_All_Tabs ENDP	
	Notebook_Open_File PROC	_pOFile:gpointer
		local pOFile		:gpointer       
        local lview			:gpointer
        local lscrolledwindow:gpointer
		local hbox			:gpointer
		local lbutton		:gpointer
		local llabel		:gpointer
		local curPage	
        local GGtkSourceStyleScheme :gpointer
        local _err:GError
        
		mov pOFile,_pOFile

	    mov lscrolledwindow,rv(gtk_scrolled_window_new,0,0)
	    mov rax,pOFile
	    mov llabel, rv(gtk_label_new,[rax].OFile.FileName) 
      	mov rax,pOFile	            	
	    mov lview,rv( gtk_source_view_new_with_buffer,[rax].OFile.buffer)


;----------------------------------
      	mov rax,pOFile
        mov rcx,lview
        mov [rax].OFile.viewer,rcx          ;if we have viewer we can get buffer
;----------------------------------

	    invoke gtk_source_view_set_show_line_numbers,lview,Settings_SV_show_line_numbers
	    invoke gtk_source_view_set_show_line_marks	,lview,Settings_SV_show_line_marks
	    invoke gtk_source_view_set_auto_indent		,lview,Settings_SV_auto_indent
	    invoke gtk_source_view_set_tab_width		,lview,Settings_SV_tab_width

	;---------------------------
	;invoke gtk_source_view_set_highlight_current_line,lview,1           ;this should be an option
	;invoke gtk_text_view_set_wrap_mode,lview,GTK_WRAP_WORD_CHAR		    ;WRAP ON

	;each buffer holds their own completion words
	invoke gtk_source_view_get_completion,lview                  ;GtkSourceCompletion
	mov completion,rax
	invoke gtk_source_completion_words_new,CStr("functions"),0
	;invoke gtk_source_completion_words_new,0,0
	mov provider,rax                                            ;GtkSourceCompletionWords
	invoke gtk_source_completion_add_provider,completion,provider,addr _err

	mov rax,pOFile
	invoke gtk_source_completion_words_register,provider,[rax].OFile.buffer
	.if rax == 0
	    invoke g_print,CStr("error",10)
	.endif

	;;--------------------------- TOOLTIPS, need a lot of work, not concluded yet
	push r12
	mov r12,pOFile
	;key_press_event: if user press ESC key so TOOLTIPS will be destroyed
	;activated when user press "[" and destroyed when user press "]" or ESC key
	;I need populate this with something usefull
	;If you copy a text that have "[" and paste so TOOLTIPS will be activated
	invoke g_signal_connect_data,[r12].OFile.viewer,CStr("key_press_event"),addr key_press,0,0,0
	invoke g_signal_connect_data,[r12].OFile.buffer,CStr("insert_text"),addr buffer_insert_text,[r12].Ofile.viewer,0,0
	pop r12
	;---------------------------

		mov lbutton,rv(gtk_button_new)			
		invoke gtk_button_set_relief,lbutton,2

		invoke gtk_button_set_label,lbutton,"x"
		invoke gtk_button_set_focus_on_click,lbutton,-1
		invoke g_signal_connect_data,lbutton,str$("clicked")	,addr 	Notebook_On_Close_Button_Clicked 	,pOFile,0,0     
		invoke g_signal_connect_data,lbutton,str$("enter")		,addr   Notebook_On_Close_Button_Enter 		,pOFile,0,0     
		invoke g_signal_connect_data,lbutton,str$("leave")		,addr   Notebook_On_Close_Button_Leave	 	,pOFile,0,0  

;this was blocking type text because function do not return rax=0
;by capturing ctrl+f, while typing a letter "f" so search activates
;invoke g_signal_connect_data,lview    ,str$("key-press-event")    ,addr On_Buffer_key_press_event   ,pOFile,0,0      

		invoke gtk_widget_show,lbutton			
		mov hbox,rv(gtk_box_new,0,0)
		invoke gtk_box_set_spacing,hbox,0
		invoke gtk_container_add,hbox,llabel
		invoke gtk_container_add,hbox,lbutton
		invoke gtk_widget_show_all,hbox        

	    invoke gtk_container_add,lscrolledwindow,lview   
	    invoke gtk_notebook_append_page,WNotebook,lscrolledwindow,hbox; label1 
	    .if dword ptr eax < 0
	        invoke g_print,str$(<13,10," gtk_notebook_append_page fail">)
	    .else
            mov curPage,eax
			mov rcx,pOFile
	     	m2m [rcx].OFile.NotebookPage,lscrolledwindow
	     	m2m [rcx].OFile.source_view,lview
				
	        invoke g_signal_connect_data,lbutton,str$("clicked"),addr Notebook_On_Close_Button_Clicked ,lscrolledwindow,0,0     
	    .endif
	    invoke gtk_widget_show_all ,   WNotebook  
		mov rax,pOFile
	    invoke gtk_notebook_set_current_page ,WNotebook,curPage         		
		ret
	Notebook_Open_File ENDP	
	Notebook_Show_Tab PROC
	
		ret
	Notebook_Show_Tab ENDP
	Notebook_Show_File PROC
	
		ret
	Notebook_Show_File ENDP
    Notebook_On_Close_Button_Clicked PROC  widget:gpointer,data:gpointer
        local lwidget:gpointer
        local ldata:gpointer
        local np:gpointer
        
        mov lwidget,widget
        mov ldata,data
        mov rax,ldata
        invoke gtk_notebook_remove_page,WNotebook,rv(Notebook_Get_N,[rax].OFile.NotebookPage)
        mov rax,ldata
        mov [rax].OFile.NotebookPage,0

        ret
    Notebook_On_Close_Button_Clicked ENDP	
    .data
        __sc  GdkRGBA  <0.9, 0.9, 0.2, 1.0>
    .code
    Notebook_On_Close_Button_Enter PROC   widget:gpointer,data:gpointer
        local lwidget:gpointer
        mov lwidget,widget
    	invoke gtk_widget_override_background_color,lwidget,0,addr __sc
        ret
    Notebook_On_Close_Button_Enter ENDP	
    Notebook_On_Close_Button_Leave PROC   widget:gpointer,data:gpointer
        local lwidget:gpointer
        mov lwidget,widget
        invoke gtk_widget_override_background_color,lwidget,0,0
        ret
    Notebook_On_Close_Button_Leave ENDP	

		
	;GtkWidget *widget, GdkEventKey *event, gpointer user_data
	align 16
	key_press PROC
	    local widget:gpointer
	    local event:gpointer

	mov widget,rdi
	mov event,rsi
	assume rsi:ptr _GdkEventKey

		.if [rsi].keyval == GDK_Escape
			.if TOOL_TIPS == TRUE && expander_window != 0
				    invoke gtk_widget_destroy,expander_window
				    mov TOOL_TIPS,0
				    mov expander_window,0
			.endif
		.endif
	assume rsi:nothing
	xor eax,eax             ;handle this to other widgets, we do not interfere with other widgets
		                ;if return TRUE, so, we done default processing and others widgets will not receive this event 
		                ;we can also disable keyboard input to text
	ret
	key_press ENDP



	align 16
	;void user_function (GtkTextBuffer *textbuffer,GtkTextIter *location,gchar *text,gint len,gpointer user_data)
	buffer_insert_text PROC uses rbx rbp r12 r13 r14 r15
	local textbuffer:gpointer
	local location:gpointer
	local text:gpointer
	local len:dword
	local user_data:gpointer
	local viewer:gpointer
	local buf_loc:_GdkRectangle
	local _label:gpointer
	local expander:gpointer
	local carety:gpointer
	local caretx:gpointer
	local caret:gpointer
	local winx:gpointer
	local winy:gpointer
	local buffer:gpointer
	local renderer:gpointer
	local tree_window:gpointer
	local list:gpointer
	local column:gpointer
	local _store:gpointer
	local tree_iter:GtkTreeIter
	local selection:gpointer
	local insert_mark:gpointer

	    mov textbuffer,rdi
	    mov location,rsi            ;iter
	    mov text,rdx
	    mov len,ecx
	    mov user_data,r8            ;viewer passed

	    mov rdx,text
	    mov rdx,[rdx]
	    .if dl == "["
		mov TOOL_TIPS,TRUE
		.if expander_window == 0
			    invoke Notebook_Get_Current_Viewer
			    mov viewer,rax
			    invoke gtk_text_view_get_iter_location,rax,location,addr buf_loc
			    invoke gtk_text_view_buffer_to_window_coords,viewer,GTK_TEXT_WINDOW_WIDGET,buf_loc.x,buf_loc.y,addr winx,addr winy
			    invoke gtk_text_view_get_window,viewer,GTK_TEXT_WINDOW_WIDGET
			    mov caret,rax
			    invoke gdk_window_get_origin,caret,addr caretx,addr carety
			    invoke gtk_expander_new,CStr("details")
			    mov expander,rax
			    invoke gtk_expander_set_expanded,expander,TRUE

			    invoke gtk_label_new,0
			    mov _label,rax
			    invoke gtk_label_set_markup,_label,CStr("<b>Function Info:</b>",10,"Return: <i>void</i>",10,"<tt>g_build_filename <a href=",'"',"path",'"',">path</a> other vars</tt>")
			    invoke gtk_container_add,expander,_label

			    invoke gtk_window_new,GTK_WINDOW_POPUP
			    mov expander_window,rax
			    invoke gtk_container_add,expander_window,expander

			    mov rdx,winy
			    add rdx,carety
			    add edx,buf_loc.height
			    invoke gtk_window_move,expander_window,caretx,edx

			    invoke gtk_label_set_selectable,_label,TRUE
			    invoke gtk_widget_show_all,expander_window
			    invoke gtk_widget_show,_label
		.endif
	    .elseif dl == "]"
			.if TOOL_TIPS == TRUE && expander_window != 0
				    invoke gtk_widget_destroy,expander_window
				    mov TOOL_TIPS,0
				    mov expander_window,0
			.endif
	    .endif

	xor eax,eax
	ret
	buffer_insert_text ENDP
