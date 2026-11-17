	IF 		@Platform EQ 1	;	Win64
		.proto FormatMessageA,GetLastError
		.data
			sizeof_@szError=256
			@szError	db	sizeof_@szError	dup(0)
		.proc _GetLastErrorMsg 
			local @dwError
			GetLastError()
			mov @dwError,eax
			FormatMessageA(1000h,0,@dwError,0,addr @szError,sizeof_@szError,0)
			lea rax,@szError
		.EndP
	ENDIF
	.proc Helpers_Load_Pixbuf_From_File ,_lfile:gpointer
		local lpixbuf:gpointer
		local lFullPName:gpointer		
	.shadow
		mov lFullPName,rv(g_build_filename,IconsPath,_lfile,0)
		mov lpixbuf,rv(gdk_pixbuf_new_from_file,lFullPName, 0)
		mov lpixbuf,rv ( gdk_pixbuf_add_alpha,lpixbuf,255,255,255,255)
		mov lpixbuf,rv ( gdk_pixbuf_scale_simple,lpixbuf,Settings_Icon_Width,Settings_Icon_Height,GDK_INTERP_BILINEAR)
		invoke g_free,lFullPName
		mov rax,lpixbuf
		ret
    .endp
    .proc Helpers_Load_Pixbuf_From_Data , dataaddr:gpointer,datasz:glong
		local lloader:gpointer
		local lpixbuf:gpointer
	.shadow
			.if datasz==1
				XOR RAX,RAX
				RET
			.endif
		mov lloader,rv(gdk_pixbuf_loader_new )
		invoke gdk_pixbuf_loader_write,lloader,dataaddr,datasz,0
		invoke gdk_pixbuf_loader_close,lloader,0
		mov lpixbuf,rv ( gdk_pixbuf_loader_get_pixbuf,lloader)
		mov lpixbuf,rv ( gdk_pixbuf_add_alpha,lpixbuf,255,255,255,255)
		mov lpixbuf,rv ( gdk_pixbuf_scale_simple,lpixbuf,Settings_Icon_Width,Settings_Icon_Height,GDK_INTERP_BILINEAR)
			.if lpixbuf
				invoke g_object_ref,lloader
			.endif
		invoke g_object_unref,lloader
		mov rax,lpixbuf
		ret
    .endp
    .proc	Helpers_GtkImage_From_File ,_Builder:gpointer,_Image:gpointer, _file:gpointer
		local lFullPName	:gpointer
		local lpixbuf		:gpointer
		local lgtkImg		:gpointer      
	.shadow    
	       	mov lgtkImg             ,rv(gtk_builder_get_object, _Builder,_Image)
	       	invoke Helpers_Load_Pixbuf_From_File,_file;lFullPName
		invoke gtk_image_set_from_pixbuf,lgtkImg,rax
		ret
    .endp

    Helpers_rv_rcx macro fn_,arg_:vararg
    	IFNDEF RCX_PushV
    		.DATA
    			RCX_PushV	gpointer	0
    		.CODE
    	ENDIF
    	MOV RCX_PushV,RCX
		IFB <arg_>
		    invoke fn_
		ELSE
		    invoke fn_,arg_
		ENDIF
    	MOV RCX,RCX_PushV
		EXITM<RAX>
    endm
    Helpers_invoke_Save_rax macro fn_,arg_:vararg
    	IFNDEF RAX_PushV
    		.DATA
    			RAX_PushV	gpointer	0
    		.CODE
    	ENDIF
    	MOV RAX_PushV,RAX
		IFB <arg_>
		    invoke fn_
		ELSE
		    invoke fn_,arg_
		ENDIF
    	MOV RAX,RAX_PushV
    endm    
    Helpers_if macro C_,fn_,arg_:vararg
    	.if C_
		IFB <arg_>
		    invoke fn_
		ELSE
		    invoke fn_,arg_
		ENDIF
    	.endif
    endm
    Helpers_SaveKeyString macro C_,  _@key_file,_@group_name,_@key,_@string
   	IFNDEF Helpers_Err
   		.DATA
   			Helpers_Err	gpointer	0
   		.CODE
   	ENDIF
    	.if C_
		invoke g_key_file_set_string,  _@key_file,_@group_name,_@key,_@string
    	.else	
		mov Helpers_Err,0
		invoke g_key_file_remove_key,  _@key_file,_@group_name,_@key,addr Helpers_Err
    	.endif    	
    endm
    Helpers_SaveKeyString_RAX macro C_,  _@key_file,_@group_name,_@key,_@string
     	IFNDEF RAX_PushV
    		.DATA
    			RAX_PushV	gpointer	0
    		.CODE
    	ENDIF
  	IFNDEF Helpers_Err
   		.DATA
   			Helpers_Err	gpointer	0
   		.CODE
   	ENDIF
	MOV RAX_PushV,RAX
    	.if C_
		invoke g_key_file_set_string,  _@key_file,_@group_name,_@key,_@string
    	.else	
		mov Helpers_Err,0
		invoke g_key_file_remove_key,  _@key_file,_@group_name,_@key,addr Helpers_Err
    	.endif    	
	MOV RAX,RAX_PushV
    endm
    Helpers_if_RAX macro C_,fn_,arg_:vararg
    	IFNDEF RAX_PushV
    		.DATA
    			RAX_PushV	gpointer	0
    		.CODE
    	ENDIF
    	.if C_
			MOV RAX_PushV,RAX
			IFB <arg_>
				invoke fn_
			ELSE
				invoke fn_,arg_
			ENDIF
			MOV RAX,RAX_PushV
    	.endif
    endm
    Helpers_gtk_entry_set_text macro  wid__,Var__
    	.if Var__
    	    invoke gtk_entry_set_text,wid__,Var__
    	.endif
    endm
    Helpers_gtk_entry_get_text macro  Var__,wid__
    	invoke gtk_entry_get_text,wid__
    	invoke g_strdup,rax
    	.if rax
		.if byte ptr [rax]
			mov Var__,rax
	   	.else
	    		mov Var__,0
		.endif
    	.else
    		mov Var__,0
   	.endif
    endm
 	Helpers_signal_connect_data  macro wedg_,Event_,CallB__
 		invoke g_signal_connect_data,   rv(gtk_builder_get_object,GGtkBuilder,wedg_),Event_,addr CallB__,0,0,0         
 	endm
	


 	.proc Helpers_Input_Box_New_File,_ext:gpointer
        local lfile	:gpointer    
        local lfiles	:gpointer    
        local lnewfile	:gpointer    
        local lfullnewfile	:gpointer    
    .shadow
        invoke user_input_box,"Input the new file name :  ","New file"
 		.if rax
 			mov lnewfile,rax
 			mov lfullnewfile,rax
	  		m2m	lfiles,Current_Prj_Files
	  		.if lfiles
	 			.if _ext
	 				mov lfullnewfile,rv(g_strconcat,lfullnewfile,_ext,0)
				.endif
			    @@:
				mov rax,lfiles
				mov rax,gpointer ptr [rax]
				.if rax
					mov lfile,rax
		            .if rv(g_strcmp0,rax, lfullnewfile) == 0                            
		                msgbox  "file already exists {%s}" ,  lfullnewfile                      
		                xor rax,rax
		                ret
		            .endif
					add lfiles,sizeof gpointer    			
					jmp @B
				.endif       			
	 			.if _ext
	 				invoke g_free,lfullnewfile 
				.endif
	  		.endif
 			mov rax,lnewfile
 		.endif
		RET
	.endp
	
 	.proc Helpers_Input_Box_New_Dir	
        local ldirs	:gpointer    
        local lnewdir	:gpointer  
        invoke user_input_box,"Input the new folder name :  ","New folder"
 		.if rax
 			mov lnewdir,rax
 		    m2m	ldirs,Current_Prj_Dirs
		    @@:
			mov rax,ldirs
			mov rax,gpointer ptr [rax]
			.if rax
				.if rv(g_strcmp0,rax, lnewdir) == 0                            
				    msgbox  "directory already exists {%s}" ,  lnewdir                        
				    xor rax,rax
				    ret
				.endif
				add ldirs,sizeof gpointer    			
				jmp @B
			.endif       			
 			mov rax,lnewdir
 		.endif
		RET
	.endp
	Helpers_messagebox_YesNoCancel macro __message_format,_msg:vararg
	    local _WMmessageBox
	    local _response
	    .data
			_WMmessageBox   gpointer 0
			_response       gint	 0
	    .code
	    IFB <_msg>
			mov _WMmessageBox ,rv(gtk_message_dialog_new,0, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION,GTK_BUTTONS_NONE,__message_format)
	    ELSE
			mov _WMmessageBox ,rv(gtk_message_dialog_new,0, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION,GTK_BUTTONS_NONE,__message_format,_msg)
	    ENDIF
	    invoke gtk_dialog_add_buttons,_WMmessageBox, \
	    								"Yes", GTK_RESPONSE_YES, \
	    								"No", GTK_RESPONSE_NO, \
	    								"Cancel", GTK_RESPONSE_CANCEL,0
	    invoke gtk_dialog_run,_WMmessageBox
	    mov _response,eax
	    invoke gtk_widget_destroy,_WMmessageBox
	    EXITM<_response>
	endm
	
    
    
