.data
	Current_Prj_Name			gpointer	0
	Current_Prj_Description		gpointer	0
	Current_Prj_MainFile			gpointer	0
	Current_Prj_PreAssemble	gpointer	0
	Current_Prj_PreAssemble_opt		gpointer	0
	Current_Prj_Assemble		gpointer	0
	Current_Prj_Link				gpointer	0
	Current_Prj_Files				gpointer	0
	Current_Prj_OFiles			gpointer	0
	Current_Prj_NFiles			gint			0
	Current_Prj_Dirs				gpointer	0
	Current_Prj_NDirs			gint			0
	Current_Prj_Path				gpointer	0
	Current_Prj_FileName		gpointer	0
	Current_Prj_Assemble_opt	gpointer	0
	Current_Prj_Link_opt			gpointer	0
	Current_Prj_Run_cmd		gpointer	0
OProject STRUCT	
	_Name			gpointer	0
	Description		gpointer	0
	MainFile			gpointer	0
	PreAssemble	gpointer	0
	PreAssemble_opt		gpointer	0
	Assemble		gpointer	0
	Link				gpointer	0 
	Files				gpointer	0
	OFiles			gpointer	0
	NFiles			gint			0
	NDirs			gint			0
	Dirs				gpointer	0	
	Path				gpointer	0
	FileName		gpointer	0
	Assemble_opt	gpointer	0
	Link_opt			gpointer	0
	Run_cmd		gpointer	0
OProject ENDS
 	Current_Project OProject <>
	.code
	Projects_Init_Project	PROC	 
		.ifline	Current_Prj_Name		,g_free,Current_Prj_Name
		.ifline	Current_Prj_FileName	,g_free,Current_Prj_FileName
		.ifline	Current_Prj_Description	,g_free,Current_Prj_Description
		.ifline	Current_Prj_MainFile	,g_free,Current_Prj_MainFile
		.ifline	Current_Prj_PreAssemble	,g_free,Current_Prj_PreAssemble
		.ifline	Current_Prj_PreAssemble_opt	,g_free,Current_Prj_PreAssemble_opt
		.ifline	Current_Prj_Assemble	,g_free,Current_Prj_Assemble
		.ifline	Current_Prj_Assemble_opt,g_free,Current_Prj_Assemble_opt
		.ifline	Current_Prj_Link		,g_free,Current_Prj_Link
		.ifline	Current_Prj_Path		,g_free,Current_Prj_Path
		.ifline	Current_Prj_Link_opt	,g_free,Current_Prj_Link_opt
		.ifline	Current_Prj_Run_cmd		,g_free,Current_Prj_Run_cmd
		
		mov 	Current_Prj_Name			,0
        	mov 	Current_Prj_FileName		,0
		m2m 	Current_Prj_Description		,0
		mov 	Current_Prj_MainFile			,0
		mov 	Current_Prj_PreAssemble	,0
		mov 	Current_Prj_PreAssemble_opt	,0
		mov 	Current_Prj_Assemble		,0
		mov 	Current_Prj_Link			,0
		mov 	Current_Prj_Files			,0
		mov 	Current_Prj_OFiles			,0
		mov 	Current_Prj_NFiles			,0
		mov 	Current_Prj_Dirs			,0
		mov 	Current_Prj_Path			,0
		mov 	Current_Prj_Assemble_opt	,0
		mov 	Current_Prj_Link_opt		,0
		mov 	Current_Prj_Run_cmd			,0
		RET
	Projects_Init_Project	ENDP
	Projects_Create_New_Empty_Project	PROC	 _PName:gpointer 
        local PName:gpointer
        mov PName,_PName
        
		m2m 	Current_Prj_Name			,PName
		invoke  g_strconcat,PName,str$(".aprj"),0
		mov 	Current_Prj_FileName		,rax
		m2m 	Current_Prj_Description		,PName
		mov 	Current_Prj_MainFile		,0
		mov 	Current_Prj_PreAssemble		,0
		mov 	Current_Prj_PreAssemble_opt	,0
		mov 	Current_Prj_Assemble		,0
		mov 	Current_Prj_Link			,0
		mov 	Current_Prj_Files			,0
		mov 	Current_Prj_OFiles			,0
		mov 	Current_Prj_NFiles			,0
		mov 	Current_Prj_Dirs			,0
		mov 	Current_Prj_Path			,0
		mov 	Current_Prj_Assemble_opt	,0
		mov 	Current_Prj_Link_opt		,0
		str2m 	Current_Prj_Run_cmd			,"./$EXE"
					
		RET
	Projects_Create_New_Empty_Project	ENDP
	Projects_Create_New_temporary_Project	PROC
		local mainasmfile	:gpointer	 
		local mainincfile	:gpointer	
		 		
         n_template_files	=	2
         
        invoke Projects_Create_New_Empty_Project,"temporaryProject"
        
		m2m 	Current_Prj_Path			,TemporaryProjectPath
		invoke g_chdir, TemporaryProjectPath
		str2m 	Current_Prj_MainFile		,"main.asm"
		str2m 	Current_Prj_Assemble	,"uasm -elf64 $SRC"
		str2m 	Current_Prj_Link			,"gcc -o $EXE $OBJ -fno-pie -no-pie"
		str2m 	Current_Prj_Run_cmd	,"./$EXE"
		mov 	Current_Prj_Files			,rv(g_strsplit,"main.asm;main.inc",";",-1)
		mov		Current_Prj_NFiles	,n_template_files
		
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
		mov		Current_Prj_OFiles			,rax
		mov 	rcx,rax
		m2m		gpointer ptr [rcx+sizeof gpointer*0],mainasmfile
		m2m		gpointer ptr [rcx+sizeof gpointer*1],mainincfile
		m2m		gpointer ptr [rcx+sizeof gpointer*2],0
		mov 	Current_Prj_NDirs			,0
		mov rdi,0		
     		call 	Projects_Save_Current_Project_And_Files
	    	call    TreeView_Show_Current_Project 
	                   
		RET
	Projects_Create_New_temporary_Project	ENDP
	Projects_Save_Last_Project	PROC
	   	invoke Settings_InsertInProjectList,rv(g_build_filename,Current_Prj_Path,Current_Prj_FileName,0)   	
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
			mov Current_Prj_Name					,rv(g_key_file_get_string,	lKeyProject,"Project","Name",0)
			mov Current_Prj_Description				,rv(g_key_file_get_string	,lKeyProject,"Project","Description",0)
			mov Current_Prj_MainFile				,rv( g_key_file_get_string,	lKeyProject,"Project","MainFile",0)
			mov Current_Prj_PreAssemble			,rv( g_key_file_get_string,	lKeyProject,"Project","PreAssemble",0)
			mov Current_Prj_PreAssemble_opt		,rv( g_key_file_get_string,	lKeyProject,"Project","PreAssemble_opt",0)
			mov Current_Prj_Assemble				,rv( g_key_file_get_string,	lKeyProject,"Project","Assemble",0)
			mov Current_Prj_Link						,rv( g_key_file_get_string,	lKeyProject,"Project","Link",0)
			mov Current_Prj_Assemble_opt			,rv( g_key_file_get_string,	lKeyProject,"Project","Assemble_opt",0)
			mov Current_Prj_Link_opt					,rv( g_key_file_get_string,	lKeyProject,"Project","Link_opt",0)
			mov Current_Prj_Run_cmd				,rv( g_key_file_get_string,	lKeyProject,"Project","Run_cmd",0)
			
			mov Current_Prj_Files					,rv(g_key_file_get_string_list,	lKeyProject,"Project","Files",addr Current_Prj_NFiles,0)
			mov Current_Prj_Dirs					,rv(g_key_file_get_string_list	,lKeyProject,"Project","Dirs",addr Current_Prj_NDirs,0)
			
			mov Current_Prj_FileName				,rv(g_path_get_basename	,pprojectFile)
			mov Current_Prj_Path					,rv( g_path_get_dirname		,pprojectFile)

			call Projects_Save_Last_Project
		 	;----------- load files
		 	xor rax,rax
			mov eax,Current_Prj_NFiles
			inc rax
			mov rcx,sizeof gpointer
			mul rcx
			mov Current_Prj_OFiles,rv(g_malloc,rax)
			mov OFilesI,rax
			m2m lfiles,Current_Prj_Files
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
			call Projects_Save_Current_Project
			invoke g_chdir,Current_Prj_Path
	    		invoke g_key_file_free,lKeyProject
		.else
		    lea r12,_err
		    mov r12,[r12]
		    mov r12,QWORD PTR [r12+8]
		   invoke printf,str$(<13,10,"Load Project ERR : {%s}">),r12			
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
		m2m oldOFiles,Current_Prj_OFiles
		m2m oldFiles,Current_Prj_Files
		inc Current_Prj_NFiles
	 	xor rax,rax
		mov eax,Current_Prj_NFiles
		add rax,2
		mov rcx,sizeof gpointer
		mul rcx
		mov byte_,rax
		mov Current_Prj_OFiles,rv(g_malloc,byte_)
		mov Current_Prj_Files ,rv(g_malloc,byte_)
		mov rcx,oldOFiles
		mov rdx,Current_Prj_OFiles
		mov r8,oldFiles
		mov r9,Current_Prj_Files

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
        m2m	lfiles,Current_Prj_OFiles
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
    	invoke g_mkdir,Current_Prj_Path,S_IRWXU

        mov lKeyProject     ,rv( g_key_file_new)
        
		Helpers_if Current_Prj_Name				,g_key_file_set_string,	lKeyProject,"Project","Name"	,Current_Prj_Name
		Helpers_if Current_Prj_Description		,g_key_file_set_string		,lKeyProject,"Project","Description",Current_Prj_Description
		Helpers_if Current_Prj_MainFile			,g_key_file_set_string		,lKeyProject,"Project","MainFile"	,Current_Prj_MainFile
		Helpers_if Current_Prj_PreAssemble		,g_key_file_set_string		,lKeyProject,"Project","PreAssemble",Current_Prj_PreAssemble
		Helpers_if Current_Prj_PreAssemble_opt	,g_key_file_set_string, 	lKeyProject,"Project","PreAssemble_opt"	,Current_Prj_PreAssemble_opt
		Helpers_if Current_Prj_Assemble			,g_key_file_set_string		,lKeyProject,"Project","Assemble"	,Current_Prj_Assemble
		Helpers_if Current_Prj_Link				,g_key_file_set_string		,lKeyProject,"Project","Link",Current_Prj_Link
		Helpers_if Current_Prj_Path				,g_key_file_set_string		,lKeyProject,"Project","Path"	,Current_Prj_Path
		Helpers_if Current_Prj_Assemble_opt		,g_key_file_set_string		,lKeyProject,"Project","Assemble_opt"	,Current_Prj_Assemble_opt
		Helpers_if Current_Prj_Link_opt			,g_key_file_set_string		,lKeyProject,"Project","Link_opt"	,Current_Prj_Link_opt
		Helpers_if Current_Prj_Run_cmd			,g_key_file_set_string		,lKeyProject,"Project","Run_cmd",Current_Prj_Run_cmd
		
		
		invoke g_key_file_set_string_list,lKeyProject,"Project","Files",Current_Prj_Files,Current_Prj_NFiles
		;.if Current_Prj_NDirs
			invoke g_key_file_set_string_list,	lKeyProject,"Project","Dirs",Current_Prj_Dirs,Current_Prj_NDirs
 		;.endif
        m2m	lfiles,Current_Prj_OFiles
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
    	mov FullPName,rv(g_build_filename,Current_Prj_Path,Current_Prj_FileName,0)
		mov _err,0 
    	invoke g_key_file_save_to_file,lKeyProject,FullPName,addr _err
        .if rax==0
            lea r12,_err
            mov r12,[r12]
            mov r12,QWORD PTR [r12+8]
            invoke printf,str$(<13,10,"Fail to save Key File {%s}">),r12
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
        .if 	Current_Prj_FileName==0
        	ret
        .endif
		invoke Projects_Save_Current_Project_And_Files,shift_
		.if rax==0
			m2m	lfiles,Current_Prj_OFiles
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
					;invoke g_free,lfilename	; free with  g_strfreev,Current_Prj_Files
					
					add lfiles,sizeof gpointer    			
					jmp @B
				.endif 
				invoke g_free,Current_Prj_OFiles
			.endif
			.if Current_Prj_Files
				invoke g_strfreev,Current_Prj_Files
				mov Current_Prj_Files,0
			.endif		
			.if Current_Prj_Dirs
				invoke g_strfreev,Current_Prj_Dirs
				mov Current_Prj_Dirs,0
			.endif			
			Projects_Init_Project()	
			xor rax,rax
		.endif
		    
		RET
	Projects_Close_Current_Project	ENDP

	TemplateProjectDialog PROTO	
	Projects_Create_New_Project_From_Template	PROC  
		local prjname:gpointer
		local prjpath:gpointer
		local FilesL:gpointer
		local FullPNameext:gpointer
		local FullPName:gpointer
		local newContent:gpointer
		local newFileName:gpointer
		local FullnewFileName:gpointer				
		local kf:gpointer				
		local FilesL0:gpointer
		local FilesN:gpointer
		local _err:gpointer

		TemplateProjectDialog()
		.if WTemplateProjectDialog_RetValue
	    		mov prjname,rv( user_input_box,".Input the Project Name:","From Template")
		     	.if rax
		    		invoke Projects_Close_Current_Project,0
		    		.if rax==0
					mov prjpath,rv(g_build_filename,ProjectsPath,prjname,0)
					g_chdir(ProjectsPath)
					invoke g_mkdir,prjname,S_IRWXU;prjpath
					invoke g_chdir,prjpath
					mov kf,rv( g_key_file_new)
					invoke g_key_file_load_from_file,kf,WTemplateProjectDialog_RetValue, 0,0    
					g_key_file_set_string(	kf,"Project","Name",prjname)	
											
					mov FullPName,rv(g_build_filename,prjpath,prjname,0)
					mov FullPNameext,rv(  g_strconcat,FullPName,str$(".aprj"),0)
					mov FilesL,rv(g_key_file_get_string_list,	kf,"Project","Files",addr FilesN,0)
					.if FilesL
						mov FilesL0,rax
				    	 @@:
						mov rax,FilesL
						mov rax,gpointer ptr [rax]
						.if rax
							mov newFileName,rax
							mov FullnewFileName,rv(g_build_filename,prjpath,newFileName,0)							
							invoke _close,rv(_open,FullnewFileName,O_WRONLY or O_CREAT , S_IRWXU or S_IRWXG or S_IRWXO)				
							mov newContent,rv(g_key_file_get_string,	kf,newFileName,"Content",0)							
							invoke g_file_set_contents,FullnewFileName,newContent,-1,0	
							g_key_file_remove_key(kf,newFileName,"Content",0)															
							g_free(newContent)
							g_free(FullnewFileName)					
							add FilesL,sizeof gpointer    			
							jmp @B
						.endif       		
					.endif
					mov _err,0 
					invoke g_key_file_save_to_file,kf,FullPNameext,addr _err
				   	invoke g_key_file_free,kf	
				   	g_strfreev(FilesL0)
				   	g_free(prjpath)
				   	g_free(FullPName)
					invoke TreeView_Clear
					invoke Projects_Load_Project,FullPNameext
					invoke TreeView_Show_Current_Project
					invoke g_free,FullPNameext
		    		.endif
		    	.endif		
		.endif
		ret
	Projects_Create_New_Project_From_Template	ENDP
	Projects_Create_New_Template_From_Current_Project	PROC
		local prjname:gpointer
		local prjpath:gpointer
		local FilesL:gpointer
		local FullPNameext:gpointer
		local FullPName:gpointer
		local newContent:gpointer
		local newFileName:gpointer
		local FullnewFileName:gpointer				
		local kf:gpointer				
		local FilesL0:gpointer
		local FilesN:gpointer
		local _err:gpointer
		
		local Descript:gpointer

		.if Current_Prj_FileName==0
			ret
		.endif
    		mov prjname,rv( user_input_box,".Input the Project Template Name:","Save As  Template")
	     	.if rax
	     		mov Descript,rv( user_input_box,".Input the  Template Description:","Save As  Template")
			mov prjpath,rv(g_build_filename,Current_Prj_Path,Current_Prj_FileName,0)
			mov kf,rv( g_key_file_new)
			mov _err,0
			invoke g_key_file_load_from_file,kf,prjpath, 0,addr _err
			.if rax
				invoke g_free,prjpath
 				mov prjpath,rv(g_build_filename,TemplatesPath,prjname,0)
				mov FullPName	,rv( g_strconcat,prjpath,str$(".atmpl"),0)
				mov _err,0
				invoke g_key_file_save_to_file,kf,FullPName,addr _err
  				invoke g_key_file_set_string,kf,"Project","Name",prjname
				invoke g_key_file_set_string,kf,"Project","Description",Descript
				mov FilesL,rv(g_key_file_get_string_list,	kf,"Project","Files",addr FilesN,0)
				.if FilesL
					mov FilesL0,rax
			    	 @@:
					mov rax,FilesL
					mov rax,gpointer ptr [rax]
					.if rax
						mov newFileName,rax
						mov FullnewFileName,rv(g_build_filename,Current_Prj_Path,newFileName,0)							
						invoke g_file_get_contents,FullnewFileName,addr newContent,0,0	
						invoke g_key_file_set_string,kf,newFileName,"Content",newContent
						g_free(FullnewFileName)					
						g_free(newContent)					
						add FilesL,sizeof gpointer    			
						jmp @B
					.endif       		
				.endif
				mov _err,0
				invoke g_key_file_save_to_file,kf,FullPName,addr _err
			   	invoke g_key_file_free,kf	
 				g_free(prjpath)
 				g_free(FullPName)			
			.else
				lea r12,_err
				mov r12,[r12]
				mov r12,QWORD PTR [r12+8]
				invoke printf,str$(<13,10,"g_key_file_load_from_file -----  ERR : {%s}">),r12			
			.endif
	    	.endif		
		ret
	Projects_Create_New_Template_From_Current_Project	ENDP
