	.CODE
	Helpers_Load_Pixbuf_From_File PROC  __vfile:gpointer
		local _lfile:gpointer
		local lpixbuf:gpointer
		local lFullPName:gpointer
		
		mov _lfile,__vfile
		mov lFullPName,rv(g_build_filename,IconsPath,_lfile,0)
		mov lpixbuf,rv(gdk_pixbuf_new_from_file,lFullPName, 0)
		mov lpixbuf,rv ( gdk_pixbuf_add_alpha,lpixbuf,255,255,255,255)
		mov lpixbuf,rv ( gdk_pixbuf_scale_simple,lpixbuf,Settings_Icon_Width,Settings_Icon_Height,GDK_INTERP_BILINEAR)
		invoke g_free,lFullPName
		mov rax,lpixbuf
		ret
    	Helpers_Load_Pixbuf_From_File ENDP
	Helpers_Load_Pixbuf_From_Data proc _dataaddr:gpointer,_datasz:glong
		local lloader:gpointer
		local dataaddr:gpointer
		local datasz:gpointer
		local lpixbuf:gpointer

		mov datasz,_datasz
		mov dataaddr,_dataaddr
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
    	Helpers_Load_Pixbuf_From_Data endp
 	Helpers_GtkImage_From_File proc  __Builder:gpointer,__Image:gpointer, __file:gpointer
		local _Image		:gpointer
		local _file			:gpointer
		local _Builder		:gpointer;        
		local lFullPName	:gpointer
		local lpixbuf		:gpointer
		local lgtkImg		:gpointer      
		mov _Image,__Image
		mov _file,__file
		mov _Builder,__Builder      
	       	mov lgtkImg             ,rv(gtk_builder_get_object, _Builder,_Image)
	       	invoke Helpers_Load_Pixbuf_From_File,_file;lFullPName
		invoke gtk_image_set_from_pixbuf,lgtkImg,rax
		ret
    	Helpers_GtkImage_From_File endp

    	Helpers_Setting_var macro __var,__mtypr,__Dvalue,__keytype,__key,NList:vararg
	    	local m
	   	local n
	   	    IFNDEF Helpers_Setting_NVAR
		    	Helpers_Setting_NVAR = 0
		    ENDIF
		    Helpers_Setting_NVAR=Helpers_Setting_NVAR+1
		    m=Helpers_Setting_NVAR
		    IFB <NList>
			%	@CatStr(<shhg>,%m) TEXTEQU	<invoke g_key_file_get_&__keytype,settingKEY, &__key,!"&__var!",0>
			%	@CatStr(<shhs>,%m) TEXTEQU	<invoke g_key_file_set_&__keytype,settingKEY, &__key,!"&__var!",&__var>
		    ELSE
			%	@CatStr(<shhg>,%m) TEXTEQU	<invoke g_key_file_get_&__keytype,settingKEY, &__key,!"&__var!",addr NList,0>
			%	@CatStr(<shhs>,%m) TEXTEQU	<invoke g_key_file_set_&__keytype,settingKEY, &__key,!"&__var!",&__var,NList>
		    ENDIF 
			n equ type(__mtypr)
			IF 		n eq 1
			%	@CatStr(<shhm>,%m) TEXTEQU	<MOV &__var,AL>
			ELSEIF 	n eq 2
			%	@CatStr(<shhm>,%m) TEXTEQU	<MOV &__var,AX>
			ELSEIF 	n eq 4
			%	@CatStr(<shhm>,%m) TEXTEQU	<MOV &__var,EAX>
			ELSE
			%	@CatStr(<shhm>,%m) TEXTEQU	<MOV &__var,RAX>
			ENDIF
				__var	__mtypr	__Dvalue
    	endm
    	Helpers_Setting_var_Get macro 
	    IFNDEF Helpers_Setting_NVAR
	    	Helpers_Setting_NVAR = 0
	    ENDIF
	    m=0
	    repeat Helpers_Setting_NVAR
		    m=m+1
			%  @CatStr(<shhg>,%m) 
			%  @CatStr(<shhm>,%m)
	    endm	
    	endm
    	Helpers_Setting_var_Set macro 
	    IFNDEF Helpers_Setting_NVAR
	    	Helpers_Setting_NVAR = 0
	    ENDIF
	    m=0
	    repeat Helpers_Setting_NVAR
		    m=m+1
			%  @CatStr(<shhs>,%m) 
	    endm
    	endm
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
	


 	Helpers_Input_Box_New_File	PROC		__ext:gpointer
        local lfile	:gpointer    
        local lfiles	:gpointer    
        local lnewfile	:gpointer    
        local lfullnewfile	:gpointer    
        local _ext:gpointer
        mov _ext,__ext  
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
	Helpers_Input_Box_New_File	ENDP
	
 	Helpers_Input_Box_New_Dir	PROC
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
	Helpers_Input_Box_New_Dir	ENDP
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
	
    
    
