OProject 	STRUCT	gpointer
	_Name				gpointer	0
	Description			gpointer	0
	MainFile			gpointer	0
	PreAssemble			gpointer	0
	PreAssemble_opt		gpointer	0
	Assemble			gpointer	0
	Link				gpointer	0 
	Files				gpointer	0
	OFiles				gpointer	0
	NFiles				gint		0
	Dirs				gpointer	0	
	NDirs				gint		0
	Path				gpointer	0
	FileName			gpointer	0
	Assemble_opt		gpointer	0
	Link_opt			gpointer	0
	Run_cmd			    gpointer	0
OProject 	ENDS

	.data
		Current_Project	OProject	<>
	.code
	Projects_Init_Project	PROC	 
		mov 	Current_Project._Name			,0		
        mov 	Current_Project.FileName		,0
		m2m 	Current_Project.Description		,0	 
		mov 	Current_Project.MainFile		,0	 
		mov 	Current_Project.PreAssemble		,0	 
		mov 	Current_Project.PreAssemble_opt	,0	 
		mov 	Current_Project.Assemble		,0	 
		mov 	Current_Project.Link			,0	 
		mov 	Current_Project.Files			,0	 
		mov 	Current_Project.OFiles			,0	 
		mov 	Current_Project.NFiles			,0	 
		mov 	Current_Project.Dirs			,0		
		mov 	Current_Project.Path			,0	
		mov 	Current_Project.Assemble_opt	,0	
		mov 	Current_Project.Link_opt		,0	
		mov 	Current_Project.Run_cmd			,0    				
		RET
	Projects_Init_Project	ENDP
	Projects_Create_New_Empty_Project	PROC	 _PName:gpointer 
        local PName:gpointer
        mov PName,_PName
        
		m2m 	Current_Project._Name			,PName		
		invoke  g_strconcat,PName,str$(".aprj"),0
        	mov 	Current_Project.FileName		,rax
		m2m 	Current_Project.Description		,PName	 
		mov 	Current_Project.MainFile		,0	 
		mov 	Current_Project.PreAssemble		,0	 
		mov 	Current_Project.PreAssemble_opt	,0	 
		mov 	Current_Project.Assemble		,0	 
		mov 	Current_Project.Link			,0	 
		mov 	Current_Project.Files			,0	 
		mov 	Current_Project.OFiles			,0	 
		mov 	Current_Project.NFiles			,0	 
		mov 	Current_Project.Dirs			,0		
		mov 	Current_Project.Path			,0	
		mov 	Current_Project.Assemble_opt	,0	
		mov 	Current_Project.Link_opt		,0	
		str2m 	Current_Project.Run_cmd			,"./$EXE"    
					
		RET
	Projects_Create_New_Empty_Project	ENDP
	Projects_Create_New_temporary_Project	PROC
		local mainasmfile	:gpointer	 
		local mainincfile	:gpointer	
		 		
         n_template_files	=	2
         
        invoke Projects_Create_New_Empty_Project,"temporaryProject"
        
		m2m 	Current_Project.Path			,TemporaryProjectPath
		invoke g_chdir, TemporaryProjectPath
		str2m 	Current_Project.MainFile		,"main.asm"	 
		str2m 	Current_Project.Assemble		,"uasm -elf64 $SRC" 
		str2m 	Current_Project.Link			,"gcc -o $EXE $OBJ -fno-pie -no-pie"	 
		str2m 	Current_Project.Run_cmd			,"./$EXE"    
		mov 	Current_Project.Files			,rv(g_strsplit,"main.asm;main.inc",";",-1)
		mov		Current_Project.NFiles			,n_template_files
		
		.DATA
			mainasmfilestr	db	"	include main.inc",0Ah
							db	"	.code",0Ah
							db	"		main PROC SYSTEMV",0Ah
							db	'		invoke 	printf, "Hello World.."',0Ah
							db	"		xor rax,rax",0Ah
							db	"		ret",0Ah
							db	"	main ENDP",0Ah
							db	"	end",0
			mainincfilestr	db	"	include libc.inc",0
		.CODE
		mov		mainasmfile,rv(Files_Create_ASM_File,"main")
		lea 	rcx,mainasmfilestr
		mov		[rax].OFile.Content,rcx
		mov		[rax].OFile.Modified,-1		
		mov		mainincfile,rv(Files_Create_INC_File,"main")
		lea 	rcx,mainincfilestr
		mov		[rax].OFile.Content,rcx
		mov		[rax].OFile.Modified,-1		
		
		mov 	rax	,n_template_files	+1
		mov 	rcx	,sizeof gpointer
		mul 	rcx
		invoke 	g_malloc	,rax
		mov		Current_Project.OFiles			,rax
		mov 	rcx,rax
		m2m		gpointer ptr [rcx+sizeof gpointer*0],mainasmfile
		m2m		gpointer ptr [rcx+sizeof gpointer*1],mainincfile
		m2m		gpointer ptr [rcx+sizeof gpointer*2],0
		mov rdi,0		
     	call 	Projects_Save_Current_Project_And_Files
	    call    TreeView_Show_Current_Project 
	                   
		RET
	Projects_Create_New_temporary_Project	ENDP
	Projects_Create_New_Project_From_Template	PROC __tmplPrj:gpointer
	local tmplPrj:gpointer
		mov tmplPrj,__tmplPrj
		invoke printf,str$(<13,10,"Projects_Create_New_Project_From_Template {%s}">),tmplPrj	   	
		RET
	Projects_Create_New_Project_From_Template	ENDP
	Projects_Create_New_Template_From_Current_Project	PROC
		RET
	Projects_Create_New_Template_From_Current_Project	ENDP
	Projects_Save_Last_Project	PROC
	    local FullPName:gpointer
;	    .if Settings_Last_Project
;	    		invoke g_free,Settings_Last_Project
;	    .endif    	
;	   	mov Settings_Last_Project,rv(g_build_filename,Current_Project.Path,Current_Project.FileName,0)
;invoke printf,str$(<13,10,"Projects_Save_Last_Project {%s}">),Settings_Last_Project	   	
;invoke printf,str$(<13,10>)   	
	   	;call Settings_Save
	   	invoke Settings_InsertInProjectList,rv(g_build_filename,Current_Project.Path,Current_Project.FileName,0)
	   	
		RET
	Projects_Save_Last_Project	ENDP

	Projects_Load_Project	PROC	projectFile:gpointer
        local lKeyProject	:gpointer
        local pprojectFile	:gpointer
        local lfiles:gpointer
        local lfile:gpointer
        local OFilesI:gpointer
	local _err:gpointer
	    	mov _err,0        
	    	mov pprojectFile,projectFile
 
        mov lKeyProject     ,rv( g_key_file_new)      
		.if rv(g_key_file_load_from_file,lKeyProject,pprojectFile, 0,addr _err    )
			invoke Projects_Init_Project
			mov Current_Project._Name,rv(g_key_file_get_string,	lKeyProject,"Project","Name",0)
			mov Current_Project.Description,rv( g_key_file_get_string,	lKeyProject,"Project","Description",0)
			mov Current_Project.MainFile,rv( g_key_file_get_string,	lKeyProject,"Project","MainFile",0)
			mov Current_Project.PreAssemble,rv( g_key_file_get_string,	lKeyProject,"Project","PreAssemble",0)
			mov Current_Project.PreAssemble_opt,rv( g_key_file_get_string,	lKeyProject,"Project","PreAssemble_opt",0)
			mov Current_Project.Assemble,rv( g_key_file_get_string,	lKeyProject,"Project","Assemble",0)
			mov Current_Project.Link,rv( g_key_file_get_string,	lKeyProject,"Project","Link",0)		
			mov Current_Project.Assemble_opt,rv( g_key_file_get_string,	lKeyProject,"Project","Assemble_opt",0)
			mov Current_Project.Link_opt,rv( g_key_file_get_string,	lKeyProject,"Project","Link_opt",0)
			mov Current_Project.Run_cmd,rv( g_key_file_get_string,	lKeyProject,"Project","Run_cmd",0)
			
			mov Current_Project.Path,rv( g_path_get_dirname,pprojectFile)

			mov Current_Project.FileName,rv(g_path_get_basename,pprojectFile)
			
			mov Current_Project.Files,rv(g_key_file_get_string_list,	lKeyProject,"Project","Files",addr Current_Project.NFiles,0)
			mov Current_Project.Dirs,rv(g_key_file_get_string_list,lKeyProject,"Project","Dirs",addr Current_Project.NDirs,0)
			call Projects_Save_Last_Project
		 	;----------- load files
		 	xor rax,rax
			mov eax,Current_Project.NFiles
			inc rax
			mov rcx,sizeof gpointer
			mul rcx
			mov Current_Project.OFiles,rv(g_malloc,rax)
			mov OFilesI,rax
			m2m lfiles,Current_Project.Files
			.if lfiles
				@Projects_Load_Project_File@:
				mov rax,lfiles
				mov rax,gpointer ptr [rax]
				mov lfile,rax
				.if rax
					invoke Files_Load,lKeyProject,lfile
					
					mov rcx,OFilesI
					mov gpointer ptr [rcx],rax
					
					add OFilesI	,sizeof gpointer 
					add lfiles	,sizeof gpointer   
					 			
					jmp @Projects_Load_Project_File@
				.endif
				mov rcx,OFilesI
				mov gpointer ptr [rcx],0
			.endif	
			;call Projects_Save_Current_Project
			invoke g_chdir,Current_Project.Path			
	    		invoke g_key_file_free,lKeyProject
		.else
		    lea r12,_err
		    mov r12,[r12]
		    mov r12,QWORD PTR [r12+8]
		;    invoke printf,str$(<13,10,"Load Project ERR : {%s}">),r12			
		.endif
    	
		RET
	Projects_Load_Project	ENDP
	
	Projects_Insert_File	PROC	_OFile:gpointer
		local oldOFiles	:gpointer
		local oldFiles	:gpointer
		local lOFile:gpointer
        local lfiles:gpointer
        local lfile:gpointer
        local OFilesI:gpointer
        local byte_:gpointer		
		mov lOFile,_OFile
		m2m oldOFiles,Current_Project.OFiles
		m2m oldFiles,Current_Project.Files
		inc Current_Project.NFiles
	 	xor rax,rax
		mov eax,Current_Project.NFiles
		add rax,2
		mov rcx,sizeof gpointer
		mul rcx
		mov byte_,rax
		mov Current_Project.OFiles,rv(g_malloc,byte_)
		mov Current_Project.Files ,rv(g_malloc,byte_)
		mov rcx,oldOFiles
		mov rdx,Current_Project.OFiles
		mov r8,oldFiles
		mov r9,Current_Project.Files

		.if rcx
			@@:
			.if gpointer ptr [rcx]
				m2m gpointer ptr [rdx],gpointer ptr [rcx]	
				add rcx	,sizeof gpointer 
				add rdx	,sizeof gpointer   			 			
				m2m gpointer ptr [r9],gpointer ptr [r8]	
				add r8	,sizeof gpointer 
				add r9	,sizeof gpointer   			 			
				jmp @B
			.endif
		.endif	
					
		m2m gpointer ptr [rdx],lOFile
		add rdx	,sizeof gpointer   			 			
		mov gpointer ptr [rdx],0
		mov rcx,lOFile
		m2m gpointer ptr [r9],[rcx].OFile.FileName
		add r9	,sizeof gpointer   			 			
		mov gpointer ptr [r9],0
		.if oldOFiles
		 	invoke g_free,oldFiles
		 	invoke g_free,oldOFiles
		.endif	
		ret
	Projects_Insert_File	ENDP
	
	Projects_Load_Last_Project	PROC
;invoke printf,str$(<13,10,"Projects_Load_Last_Project ={%s}">),Settings_Last_Project   
		.if Settings_Last_Project
			invoke Projects_Load_Project,Settings_Last_Project
		.endif
		RET
	Projects_Load_Last_Project	ENDP
	Projects_Save_Current_Project_Files_Content	PROC	shift__:gboolean
        local shift_	:gboolean
        local lfiles	:gpointer     
        local _RESPONSE :gint
        mov shift_,shift__
        m2m	lfiles,Current_Project.OFiles
        @@:
    	mov rax,lfiles
		mov rax,gpointer ptr [rax]
    	.if rax
    		.if [rax].OFile.Modified
    			.if shift_
    				invoke Files_Save_Content,rax		;gpointer ptr [rax]
    			.else
					.if	[rax].OFile.NotebookPage
						invoke gtk_notebook_set_current_page,WNotebook,rv(Notebook_Get_N,[rax].OFile.NotebookPage)
					.endif
					mov rax,lfiles
					mov rax,gpointer ptr [rax]
					m2m	_RESPONSE,Helpers_messagebox_YesNoCancel("do you want to save %s",[rax].OFile.FileName)
					.if _RESPONSE==GTK_RESPONSE_CANCEL
						mov rax,-1
						ret
					.endif
    				.if _RESPONSE== GTK_RESPONSE_YES
						mov rax,lfiles
						invoke Files_Save_Content,gpointer ptr [rax]
					.endif
					mov rax,lfiles
					mov rax,gpointer ptr [rax]
					.if	[rax].OFile.NotebookPage
						invoke gtk_notebook_remove_page,WNotebook,rv(Notebook_Get_N,[rax].OFile.NotebookPage)
						mov rax,lfiles
						mov rax,gpointer ptr [rax]
						mov [rax].OFile.NotebookPage,0
					.endif
				.endif
		   	.endif
			add lfiles,sizeof gpointer    			
    		jmp @B
    	.endif 
    	xor rax,rax      		
		RET
	Projects_Save_Current_Project_Files_Content	ENDP
	
	Projects_Save_Current_Project	PROC 	 
        local lfiles	:gpointer     
        local FullPName	:gpointer
        local lKeyProject	:gpointer
        local _err:gpointer

               
       	;create dir
    	invoke g_mkdir,Current_Project.Path,S_IRWXU

        mov lKeyProject     ,rv( g_key_file_new)
        
		Helpers_if Current_Project._Name			,g_key_file_set_string,	lKeyProject,"Project","Name"	,Current_Project._Name
		Helpers_if Current_Project.Description		,g_key_file_set_string,lKeyProject,"Project","Description",Current_Project.Description
		Helpers_if Current_Project.MainFile			,g_key_file_set_string,lKeyProject,"Project","MainFile"	,Current_Project.MainFile
		Helpers_if Current_Project.PreAssemble		,g_key_file_set_string,lKeyProject,"Project","PreAssemble",Current_Project.PreAssemble
		Helpers_if Current_Project.PreAssemble_opt	,g_key_file_set_string, 	lKeyProject,"Project","PreAssemble_opt"	,Current_Project.PreAssemble_opt
		Helpers_if Current_Project.Assemble			,g_key_file_set_string,lKeyProject,"Project","Assemble"	,Current_Project.Assemble
		Helpers_if Current_Project.Link				,g_key_file_set_string,lKeyProject,"Project","Link",Current_Project.Link
		Helpers_if Current_Project.Path				,g_key_file_set_string,lKeyProject,"Project","Path"	,Current_Project.Path
		Helpers_if Current_Project.Assemble_opt		,g_key_file_set_string,lKeyProject,"Project","Assemble_opt"	,Current_Project.Assemble_opt
		Helpers_if Current_Project.Link_opt			,g_key_file_set_string,lKeyProject,"Project","Link_opt"	,Current_Project.Link_opt
		Helpers_if Current_Project.Run_cmd			,g_key_file_set_string,lKeyProject,"Project","Run_cmd",Current_Project.Run_cmd
		
		
		invoke g_key_file_set_string_list,lKeyProject,"Project","Files",Current_Project.Files,Current_Project.NFiles
		invoke g_key_file_set_string_list,	lKeyProject,"Project","Dirs",Current_Project.Dirs,Current_Project.NDirs
 
        m2m	lfiles,Current_Project.OFiles
        .if lfiles
    	 @@:
    	 mov rax,lfiles
		 mov rax,gpointer ptr [rax]
		 .if rax
		  Helpers_if_RAX [rax].OFile._Name,g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"Name",[rax].OFile._Name
		  Helpers_if_RAX [rax].OFile.Description,g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"Description",[rax].OFile.Description
		  Helpers_if_RAX [rax].OFile.ProgrammingLanguage,g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"ProgrammingLanguage",[rax].OFile.ProgrammingLanguage
		  Helpers_if_RAX [rax].OFile.StyleScheme,g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"StyleScheme",[rax].OFile.StyleScheme
		  Helpers_if_RAX [rax].OFile.icon,g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"icon",[rax].OFile.icon
		  Helpers_if_RAX [rax].OFile.Dir,g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"Dir",[rax].OFile.Dir
		  Helpers_if_RAX [rax].OFile.Content,g_key_file_set_string,lKeyProject,[rax].OFile.FileName,"Content",[rax].OFile.Content
		  add lfiles,sizeof gpointer    			
		  jmp @B
		 .endif       		
		.endif

    	;save to file
    	mov FullPName,rv(g_build_filename,Current_Project.Path,Current_Project.FileName,0)
		mov _err,0 
    	invoke g_key_file_save_to_file,lKeyProject,FullPName,addr _err
        .if rax==0
            lea r12,_err
            mov r12,[r12]
            mov r12,QWORD PTR [r12+8]
            invoke printf,str$(<13,10,"Error loading interface {%s}">),r12
            ret
        .endif
    	invoke g_free,FullPName
    	
		RET
	Projects_Save_Current_Project	ENDP
	Projects_Save_Current_Project_And_Files	PROC 	shift__:gboolean
        local shift_	:gboolean
        
        mov shift_,shift__	
 		invoke Projects_Save_Current_Project				 	
		invoke Projects_Save_Current_Project_Files_Content	,shift_

		RET
	Projects_Save_Current_Project_And_Files	ENDP
	Projects_Close_Current_Project	PROC		shift__:gboolean
        local shift_	:gboolean
        local lfiles	:gpointer
		local lofile 	:gpointer
		local lfname	:gpointer
		local lfilename	:gpointer

        mov shift_,shift__
        .if 	Current_Project.FileName==0
        	ret
        .endif
		invoke Projects_Save_Current_Project_And_Files,shift_
		.if rax==0
			m2m	lfiles,Current_Project.OFiles
			.if lfiles
				@@:
				mov rax,lfiles
				mov rax,gpointer ptr [rax]
				.if rax
					mov rcx,rax
					mov lofile,rax
					
					m2m lfname		,[rcx].OFile._Name 	
					m2m lfilename	,[rcx].OFile.FileName
					.if [rcx].OFile.NotebookPage
						mov rax,[rcx].OFile.NotebookPage
						invoke gtk_notebook_remove_page,WNotebook,rv(Notebook_Get_N,rax)
					.endif
	 				mov rax,lofile
	 				.if [rax].OFile.buffer
						invoke g_clear_object,[rax].OFile.buffer
	 				.endif
								  
					invoke g_free,lofile
					invoke g_free,lfname
					;invoke g_free,lfilename	; free with  g_strfreev,Current_Project.Files 
					
					add lfiles,sizeof gpointer    			
					jmp @B
				.endif 
				invoke g_free,Current_Project.OFiles      		
			.endif
			.if Current_Project.Files
				invoke g_strfreev,Current_Project.Files     		
			.endif		
			.if Current_Project.Dirs
				invoke g_strfreev,Current_Project.Dirs     		
			.endif				
			xor rax,rax
		.endif
		    
		RET
	Projects_Close_Current_Project	ENDP

		
				
				
				
			
				
					 
					
					 	 	
					
			
				
				    
				 	 
			 		 	

			






	