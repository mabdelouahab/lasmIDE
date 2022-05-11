include folding.inc

.CODE
align 16
Notebook_Get_Current_Viewer PROC
local current_page:gpointer
local OFilesIndex:gpointer

	mov current_page,rv(gtk_notebook_get_nth_page,WNotebook,rv(gtk_notebook_get_current_page,WNotebook))
	m2m OFilesIndex,Current_Prj_OFiles
	.if OFilesIndex==0
		xor eax,eax
		ret
	.else
		@@:
		mov rax,OFilesIndex
		mov rax,gpointer ptr [rax]
	 	.if rax
	 		mov rcx,[rax].OFile.NotebookPage
	 		.if rcx==current_page
	 			mov rax,[rax].OFile.source_view
	 			ret
	 		.endif
			add OFilesIndex	,sizeof gpointer
			jmp @B
		.endif
	.endif
xor eax,eax
RET
Notebook_Get_Current_Viewer ENDP
Notebook_Get_Viewer_From_Buffer PROC  _TBuffer:gpointer
local current_page:gpointer
local OFilesIndex:gpointer


	m2m OFilesIndex,Current_Prj_OFiles
	.if OFilesIndex==0
		xor eax,eax
		ret
	.else
		@@:
		mov rax,OFilesIndex
		mov rax,gpointer ptr [rax]
	 	.if rax
	 		mov rcx,[rax].OFile.buffer
	 		.if rcx==_TBuffer
	 			mov rax,[rax].OFile.source_view
	 			ret
	 		.endif
			add OFilesIndex	,sizeof gpointer
			jmp @B
		.endif
	.endif
xor eax,eax
RET
Notebook_Get_Viewer_From_Buffer ENDP

align 16
Notebook_Get_Current_Buffer PROC
local current_page:gpointer
local OFilesIndex:gpointer

	mov current_page,rv(gtk_notebook_get_nth_page,WNotebook,rv(gtk_notebook_get_current_page,WNotebook))
	m2m OFilesIndex,Current_Prj_OFiles
	.if OFilesIndex==0
		xor eax,eax
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
xor eax,eax
RET
Notebook_Get_Current_Buffer ENDP

align 16
Notebook_Get_Current_FileName PROC
local current_page:gpointer
local OFilesIndex:gpointer

	mov current_page,rv( gtk_notebook_get_nth_page,WNotebook,rv(gtk_notebook_get_current_page,WNotebook))
	m2m OFilesIndex,Current_Prj_OFiles
	.if OFilesIndex==0
		xor eax,eax
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
xor eax,eax
RET
Notebook_Get_Current_FileName ENDP

align 16
Notebook_Get_Current_OFile PROC
local current_page:gpointer
local OFilesIndex:gpointer

	mov current_page,rv(gtk_notebook_get_nth_page,WNotebook,rv(gtk_notebook_get_current_page,WNotebook))
	m2m OFilesIndex,Current_Prj_OFiles
	.if OFilesIndex==0
		xor eax,eax
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
xor eax,eax
RET
Notebook_Get_Current_OFile ENDP

align 16
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

align 16
Notebook_Save_Current_Tab PROC
local dir			:gpointer
local buffer		:gpointer
local fname			:gpointer
local bndtxt		:gpointer
local _Ofile		:gpointer
local __start_iter	:GtkTextIter
local __end_iter	:GtkTextIter

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

align 16
Notebook_Save_All_Tab PROC
local OFilesIndex:gpointer
local dir		:gpointer
local buffer		:gpointer
local fname		:gpointer
local bndtxt		:gpointer
local _Ofile		:gpointer
local __start_iter	:GtkTextIter
local __end_iter	:GtkTextIter        

	m2m OFilesIndex,Current_Prj_OFiles
	.if OFilesIndex==0
		xor eax,eax
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
			add OFilesIndex,sizeof gpointer
			jmp @B
		.endif
	.endif
	xor eax,eax
RET
Notebook_Save_All_Tab ENDP

align 16
Notebook_Close_Tab PROC _pOFile:gpointer
local pOFile		:gpointer

	mov pOFile,_pOFile
	mov rax,pOFile
	invoke Notebook_Get_N,[rax].OFile.NotebookPage
	invoke  gtk_notebook_remove_page,WNotebook,rax
ret
Notebook_Close_Tab ENDP

align 16
Notebook_Close_All_Tabs PROC
ret
Notebook_Close_All_Tabs ENDP

.data
gutter dq 0
.code
align 16
Notebook_Open_File PROC	uses r12 _pOFile:gpointer
local pOFile			:gpointer
local lview				:gpointer
local lscrolledwindow	:gpointer
local hbox				:gpointer
local lbutton			:gpointer
local llabel			:gpointer
local curPage			:guint
local GGtkSourceStyleScheme	:gpointer
local _err				:GError
local startiter:GtkTextIter
local enditer:GtkTextIter

	mov pOFile,_pOFile
	mov r12,pOFile
 
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

	invoke gtk_text_view_set_monospace,lview,TRUE
	
	invoke gtk_text_buffer_create_tag,[r12].OFile.buffer,"invisible", "invisible",1,0
	invoke g_signal_connect_data,lview,"line-mark-activated",addr on_line_mark_activated,[r12].OFile.buffer,0,0
	invoke g_signal_connect_data,lview,"key_press_event",addr key_press,[r12].OFile.buffer,0,0
	;invoke g_signal_connect_data,lview,"button_press_event",addr button_press,pOFile,0,0
	invoke create_marks,lview

;---------------------------
;each buffer holds their own completion words
	invoke gtk_source_view_get_completion,lview                  ;GtkSourceCompletion
	mov completion,rax
;	invoke gtk_source_completion_words_new,CStr("functions"),0
invoke gtk_source_completion_words_new,0,0
	mov provider,rax                                            ;GtkSourceCompletionWords
	invoke gtk_source_completion_add_provider,completion,provider,addr _err

	mov rax,pOFile
	invoke gtk_source_completion_words_register,provider,[rax].OFile.buffer
	.if rax == 0
		invoke g_print,CStr("error",10)
	.endif

G_CONNECT_AFTER equ (1  shl  0)
G_CONNECT_SWAPPED equ (1  shl  1)

;---------------------------
;line below moved to files.inc before opened text file is being inserted in buffer
;	invoke g_signal_connect_data,[r12].OFile.buffer,CStr("insert_text"),addr buffer_insert_text,[r12].Ofile.viewer,0,G_CONNECT_AFTER
;---------------------------


	mov lbutton,rv(gtk_button_new)			
	invoke gtk_button_set_relief,lbutton,2

	invoke gtk_button_set_label,lbutton,"x"
	invoke gtk_button_set_focus_on_click,lbutton,-1
	invoke g_signal_connect_data,lbutton,str$("clicked")	,addr	Notebook_On_Close_Button_Clicked 	,pOFile,0,0
	invoke g_signal_connect_data,lbutton,str$("enter")	,addr	Notebook_On_Close_Button_Enter 		,pOFile,0,0
	invoke g_signal_connect_data,lbutton,str$("leave")	,addr	Notebook_On_Close_Button_Leave	 	,pOFile,0,0  


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
		;invoke g_signal_connect_data,lbutton,str$("clicked"),addr Notebook_On_Close_Button_Clicked ,lscrolledwindow,0,0     
	.endif
	invoke gtk_widget_show_all,   WNotebook  
	mov rax,pOFile
	invoke gtk_notebook_set_current_page ,WNotebook,curPage
ret
Notebook_Open_File ENDP


align 16
Notebook_Show_Tab PROC
ret
Notebook_Show_Tab ENDP

align 16
Notebook_Show_File PROC
ret
Notebook_Show_File ENDP

align 16
Notebook_On_Close_Button_Clicked PROC  widget:gpointer,data:gpointer
local lwidget:gpointer
local ldata:gpointer
local np:gpointer

 	mov lwidget,widget
	mov ldata,data
	mov rax,ldata
 	.if [rax].OFile.Modified
		.if Helpers_messagebox_YesNoCancel("do you want to save %s",[rax].OFile.FileName)== GTK_RESPONSE_YES
			invoke Files_Save_Content,ldata
		.endif	
	.endif	
	mov rax,ldata
 	invoke gtk_notebook_remove_page,WNotebook,rv(Notebook_Get_N,[rax].OFile.NotebookPage)
	mov rax,ldata
	mov [rax].OFile.NotebookPage,0
	mov [rax].OFile.buffer,0
	mov [rax].OFile.Modified,0
	mov [rax].OFile.Content,0
	
ret
Notebook_On_Close_Button_Clicked ENDP

.data
__sc  GdkRGBA  <0.9, 0.9, 0.2, 1.0>
.code
align 16
Notebook_On_Close_Button_Enter PROC   widget:gpointer,data:gpointer
local lwidget:gpointer
	mov lwidget,widget
	invoke gtk_widget_override_background_color,lwidget,0,addr __sc
ret
Notebook_On_Close_Button_Enter ENDP

align 16
Notebook_On_Close_Button_Leave PROC   widget:gpointer,data:gpointer
local lwidget:gpointer
	mov lwidget,widget
	invoke gtk_widget_override_background_color,lwidget,0,0
ret
Notebook_On_Close_Button_Leave ENDP


	On_Buffer_delete_range proc	_self:gpointer,_start_Iter:gpointer,_end_Iter:gpointer,_user_data:gpointer
		invoke gtk_source_buffer_remove_source_marks,_self,_start_Iter,_end_Iter,0
		xor rax,rax
		ret 
	On_Buffer_delete_range endp
	On_Buffer_delete_range_AFTER proc	_self:gpointer,_start_Iter:gpointer,_end_Iter:gpointer,_user_data:gpointer
		local self:gpointer

		mov self,_self
	 
		gtk_text_iter_get_line(_start_Iter)
		folding_processing_Text(self,eax)
		xor rax,rax
		ret 
	On_Buffer_delete_range_AFTER endp

	GDK_KP_Enter	EQU	0ff8dh
	GDK_Linefeed    EQU 0ff0ah
	GDK_Return      EQU 0ff0dh
	GDK_Tab			EQU	0ff09h
	GDK_space		EQU	020h
	 
	align 16
	key_press PROC


		xor eax,eax
		ret

	key_press ENDP

g_utf8_strlen proto :vararg

GTK_TEXT_SEARCH_CASE_INSENSITIVE equ 2
align 16
;void user_function (GtkTextBuffer *textbuffer,GtkTextIter *location,gchar *text,gint len,gpointer user_data)
buffer_insert_text PROC uses rbx rbp r12 r13 r14 r15
local textbuffer		:gpointer
local location_start	:gpointer
local text			:gpointer
local line			:gint
local Nline			:qword
	mov textbuffer,rdi
	mov location_start,rsi            
	mov text,rdx

	gtk_text_iter_get_line(location_start)
	mov line,eax
	mov Nline,0
	mov r14,text
	@@:
	.if byte ptr [r14] 
		.if byte ptr [r14] ==0ah
			inc Nline
		.endif	
		inc r14	
		jmp @B
	.endif
	@@:
	folding_processing_Text(textbuffer,line)
	.if Nline
		dec Nline
		dec line
		jmp @B
	.endif
        xor rax,rax
        ret 

buffer_insert_text ENDP


align 16
;gboolean user_function (GtkWidget *widget,GdkEvent *event,gpointer user_data)
button_press proc uses r12 _widget:gpointer,_event:gpointer,_user_data:gpointer
local status:gpointer
local event:gpointer
local user_data:gpointer
local widget:gpointer
local x:gpointer
local y:gpointer
local iter:GtkTextIter
local iter_start:GtkTextIter
local iter_end:GtkTextIter
local visible_rect:_GdkRectangle
local event_time:gint
local mystring:gpointer

	mov widget,_widget		;textview
	mov event,_event
	mov user_data,_user_data	;pOFile
	
	mov r12,event
	assume r12:ptr GdkEventButton
	.if [r12].GdkEventButton.button != 3
		xor rax,rax
		ret
	.endif

	movsd xmm0,[r12].GdkEventButton.x
	movsd xmm1,[r12].GdkEventButton.y
	cvtsd2si rdx,xmm0
	cvtsd2si rcx,xmm1
	mov x,rdx
	mov y,rcx
;	mov eax,[r12].GdkEventButton.time
;	mov event_time,eax
	
	invoke gtk_text_view_get_visible_rect,widget,addr visible_rect
	lea r12,visible_rect
	assume r12:ptr _GdkRectangle
	mov rdx,y
	add edx,[r12]._GdkRectangle.y
	mov y,rdx
	assume r12:nothing

	invoke gtk_text_view_get_iter_at_location,widget,addr iter,x,y
	invoke gtk_text_view_get_iter_at_location,widget,addr iter_start,x,y
	invoke gtk_text_view_get_iter_at_location,widget,addr iter_end,x,y

	invoke gtk_text_iter_inside_word,addr iter
	.if rax
		@@:
		invoke gtk_text_iter_backward_word_start,addr iter_start
		invoke gtk_text_iter_backward_char,addr iter_start
		invoke gtk_text_iter_get_char,addr iter_start
		.if rax == "_"
			jmp @B
		.endif
		invoke gtk_text_iter_forward_char,addr iter_start
		
		@@:
		invoke gtk_text_iter_forward_word_end,addr iter_end
		invoke gtk_text_iter_get_char,addr iter_end
		.if rax == "_"
			jmp @B
		.endif

		invoke gtk_text_iter_get_text,addr iter_start,addr iter_end
		mov mystring,rax

		invoke g_signal_connect_data,widget,CStr("populate-popup"),addr append_menu,mystring,0,0         
	.else
		invoke gtk_text_iter_forward_word_end,addr iter_end
		invoke gtk_text_iter_get_text,addr iter_start,addr iter_end
	.endif
	
xor eax,eax
ret
button_press endp

.data
menu_mystring dq 0
.code
align 16
;void user_function (GtkTextView *text_view,GtkWidget *popup,gpointer user_data)
append_menu proc _text_view:gpointer,_popup:gpointer,_user_data:gpointer
local textview:gpointer
local popup:gpointer
local user_data:gpointer
local menu:gpointer
;local menu_mystring:gpointer

	mov textview,_text_view
	mov popup,_popup
	mov user_data,_user_data		;string to be append

	.if menu_mystring != 0			;to avoid append a lot of strings to context menu
		invoke gtk_container_remove,popup,menu_mystring
	.endif
	
	invoke gtk_menu_item_new_with_label,user_data
	mov menu_mystring,rax
	invoke gtk_widget_show,menu_mystring
	invoke gtk_menu_shell_append,popup,menu_mystring
	invoke g_signal_connect_data,menu_mystring,CStr("activate"),addr insert_proto,user_data,0,G_CONNECT_AFTER
	
xor eax,eax
ret
append_menu endp


.data
some_comment db ";right click in textview and select word to be append here",10,0
.code
align 16
;void user_function (GtkMenuItem *menuitem,gpointer user_data)
insert_proto proc uses r12 r13 _menuitem:gpointer,_user_data:gpointer
local menuitem:gpointer
local user_data:gpointer

local pfname :gpointer
local error:GError
local p_input:gpointer
local sz_input:dword
local buffer:gpointer
local iter:GtkTextIter
local iter_start:GtkTextIter
local iter_end:GtkTextIter
local miter:GtkTextIter
local miter1:GtkTextIter
local string:gpointer


	mov menuitem,_menuitem
	mov user_data,_user_data

	mov pfname,rv(g_build_filename,firstworkingdir,CStr("proto.inc"),0)
	
	mov error,0
    invoke g_file_test,pfname,G_FILE_TEST_EXISTS
    .if rax == FALSE
		invoke g_file_set_contents,pfname,addr some_comment,sizeof some_comment-1,addr error
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
    
	invoke gtk_text_buffer_new,0
	mov buffer,rax
	invoke gtk_text_buffer_set_text,buffer,p_input,sz_input
	invoke gtk_text_buffer_get_start_iter,buffer,addr iter_start
	invoke gtk_text_buffer_get_end_iter,buffer,addr iter_end
	invoke gtk_text_iter_forward_search,addr iter_start,user_data,0,addr miter,addr miter1,addr iter_end
	.if rax
		invoke g_printf,CStr("%s exist in proto.inc",10),user_data
		invoke g_free,pfname
		invoke g_object_unref,buffer
		mov rax,-1
		ret
	.endif
	invoke g_strdup_printf,CStr("%s proto :vararg",10),user_data
	mov string,rax
	invoke gtk_text_buffer_insert,buffer,addr iter_end,string,-1
	invoke gtk_text_buffer_get_start_iter,buffer,addr iter_start
	invoke gtk_text_buffer_get_end_iter,buffer,addr iter_end
	invoke gtk_text_buffer_get_text,buffer,addr iter_start,addr iter_end,0
	
	mov error,0
	invoke g_file_set_contents,pfname,rax,-1,addr error

    .if eax == FALSE
		mov rax,error
		assume rax:GError
		invoke g_printf,CStr("%s",10),[rax].message
		assume rax:nothing
		invoke g_free,pfname
		invoke g_free,string
		invoke g_object_unref,buffer
		mov rax,-1
		ret
    .endif

	invoke g_free,pfname
	invoke g_free,string
	invoke g_object_unref,buffer
;	invoke g_print,CStr("%s proto :vararg",10),user_data
ret
insert_proto endp
