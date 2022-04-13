
.CODE
	Notebook_Get_Current_Buffer PROC
		local current_page:gpointer
		local OFilesIndex:gpointer
        mov current_page,rv( gtk_notebook_get_nth_page,WNotebook,rv(gtk_notebook_get_current_page,WNotebook))
		m2m OFilesIndex,Current_Project.OFiles
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
	
		ret
	Notebook_Save_Current_Tab ENDP	
	Notebook_Save_All_Tab PROC
	
		ret
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
        
		mov pOFile,_pOFile

	    mov lscrolledwindow,rv(gtk_scrolled_window_new,0,0)
	    mov rax,pOFile
	    mov llabel, rv(gtk_label_new,[rax].OFile.FileName) 
      	mov rax,pOFile	            	
	    mov lview,rv( gtk_source_view_new_with_buffer,[rax].OFile.buffer)


	    invoke gtk_source_view_set_show_line_numbers,lview,Settings_SV_show_line_numbers
	    invoke gtk_source_view_set_show_line_marks	,lview,Settings_SV_show_line_marks
	    invoke gtk_source_view_set_auto_indent		,lview,Settings_SV_auto_indent
	    invoke gtk_source_view_set_tab_width		,lview,Settings_SV_tab_width

		mov lbutton,rv(gtk_button_new)			
		invoke gtk_button_set_relief,lbutton,2

		invoke gtk_button_set_label,lbutton,"x"
		invoke gtk_button_set_focus_on_click,lbutton,-1
		invoke g_signal_connect_data,lbutton,str$("clicked")	,addr 	Notebook_On_Close_Button_Clicked 	,pOFile,0,0     
		invoke g_signal_connect_data,lbutton,str$("enter")		,addr   Notebook_On_Close_Button_Enter 		,pOFile,0,0     
		invoke g_signal_connect_data,lbutton,str$("leave")		,addr   Notebook_On_Close_Button_Leave	 	,pOFile,0,0  

	       	
     

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

	