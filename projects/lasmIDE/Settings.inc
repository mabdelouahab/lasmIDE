	SETTING_FileName	EQU	"CONFIG.INI"
	.DATA
	
		Helpers_Setting_var		Settings_Icon_Width			,gint		,18		,integer,"ICON"
		Helpers_Setting_var		Settings_Icon_Height		,gint		,18		,integer,"ICON"
		Helpers_Setting_var		Settings_Icons_ASM			,gpointer	,0		,string	,"ICON"
		Helpers_Setting_var		Settings_Icons_INC			,gpointer	,0		,string	,"ICON"
		Helpers_Setting_var		Settings_Icons_C				,gpointer	,0		,string	,"ICON"
		Helpers_Setting_var		Settings_Icons_H				,gpointer	,0		,string	,"ICON"
		Helpers_Setting_var		Settings_Icons_XML			,gpointer	,0		,string	,"ICON"
		Helpers_Setting_var		Settings_Icons_WIDG		,gpointer	,0		,string	,"ICON"
		Helpers_Setting_var		Settings_Icons_TXT			,gpointer	,0		,string	,"ICON"
		Helpers_Setting_var		Settings_Icons_RC			,gpointer	,0		,string	,"ICON"
		Helpers_Setting_var		Settings_Icons_ANY			,gpointer	,0		,string	,"ICON"	 
		Helpers_Setting_var		Settings_Icons_FLDRO		,gpointer	,0		,string	,"ICON"	 
		Helpers_Setting_var		Settings_Icons_FLDRC		,gpointer	,0		,string	,"ICON"	 
		Helpers_Setting_var		Settings_Icons_PRJ			,gpointer	,0		,string	,"ICON"	 

		Helpers_Setting_var		Settings_VTE_BG_red		,REAL8		,0.0	,int64	,"VTE"	 
		Helpers_Setting_var		Settings_VTE_BG_green	,REAL8		,0.0	,int64	,"VTE"	 
		Helpers_Setting_var		Settings_VTE_BG_blue		,REAL8		,0.0	,int64	,"VTE"	 
		Helpers_Setting_var		Settings_VTE_BG_alpha		,REAL8		,1.0	,int64	,"VTE"	 

		Helpers_Setting_var		Settings_VTE_cursor_red	,REAL8		,0.0	,int64	,"VTE"	 
		Helpers_Setting_var		Settings_VTE_cursor_green	,REAL8		,0.0	,int64	,"VTE"	 
		Helpers_Setting_var		Settings_VTE_cursor_blue	,REAL8		,0.0	,int64	,"VTE"	 
		Helpers_Setting_var		Settings_VTE_cursor_alpha	,REAL8		,1.0	,int64	,"VTE"	 

		Helpers_Setting_var		Settings_VTE_cursor_blnkMode,gint		,2		,integer,"VTE"	 
		Helpers_Setting_var		Settings_VTE_cursor_shape		,gint		,1		,integer,"VTE"	 

		Helpers_Setting_var		Settings_SV_show_line_numbers,gint		,-1		,integer,"SOURCEVIEW"	 
		Helpers_Setting_var		Settings_SV_show_line_marks	,gint		,-1		,integer,"SOURCEVIEW"	 
		Helpers_Setting_var		Settings_SV_auto_indent		,gint		,-1		,integer,"SOURCEVIEW"	 
		Helpers_Setting_var		Settings_SV_tab_width		,gint		,4		,integer,"SOURCEVIEW"	 

		Helpers_Setting_var		Settings_Load_Last_Project	,gboolean	,-1		,boolean,"PROJECT"	 
		Helpers_Setting_var		Settings_Last_Project		,gpointer	,0		,string	,"PROJECT"	 
		Helpers_Setting_var		Settings_Last_Project1		,gpointer	,0		,string	,"PROJECT"	 
		Helpers_Setting_var		Settings_Last_Project2		,gpointer	,0		,string	,"PROJECT"	 
		Helpers_Setting_var		Settings_Last_Project3		,gpointer	,0		,string	,"PROJECT"	 
		Helpers_Setting_var		Settings_Last_Project4		,gpointer	,0		,string	,"PROJECT"	 
		Helpers_Setting_var		Settings_Last_Project5		,gpointer	,0		,string	,"PROJECT"	 
		Helpers_Setting_var		Settings_Last_Project6		,gpointer	,0		,string	,"PROJECT"	 
		Helpers_Setting_var		Settings_Last_Project7		,gpointer	,0		,string	,"PROJECT"	 
		Helpers_Setting_var		Settings_Last_Project8		,gpointer	,0		,string	,"PROJECT"	 
		Helpers_Setting_var		Settings_Last_Project9		,gpointer	,0		,string	,"PROJECT"	 




	LastProjectMenuList macro
	local m
		 m=1
		 repeat 9
		 .data
		% 	@CatStr(<Menu_Last_Project>,%m)	gpointer	0
		 .code
		 	.if @CatStr(<Settings_Last_Project>,%m)  
			       mov  @CatStr(<Menu_Last_Project>,%m) ,rv( gtk_menu_item_new_with_label ,@CatStr(<Settings_Last_Project>,%m)  );
				invoke gtk_container_add,rv(gtk_builder_get_object,GGtkBuilder,"WMnOpenProjectsubmenu"), @CatStr(<Menu_Last_Project>,%m);	 
		 		invoke g_signal_connect_data,  @CatStr(<Menu_Last_Project>,%m),"activate",addr MainWindow_callback_Open_Project_From_List,@CatStr(<Settings_Last_Project>,%m),0,0         
		 	.endif		 
		 	m=m+1
		 endm
	endm

	Insert_LastProject_In_MenuList macro
	local m
		 .data
		 	m	gpointer	0
		 .code
		       mov  m ,rv( gtk_menu_item_new_with_label ,Settings_Last_Project)
			invoke gtk_container_add,rv(gtk_builder_get_object,GGtkBuilder,"WMnOpenProjectsubmenu"),m
	 		invoke g_signal_connect_data,  m,"activate",addr MainWindow_callback_Open_Project_From_List,Settings_Last_Project,0,0         
	endm
	
	.CODE
	Settings_Load	PROC
		local settingKEY	:gpointer
		local FullPName	:gpointer
		mov settingKEY     ,rv( g_key_file_new)      
		IFNB <firstworkingdir>
			mov FullPName,rv(g_build_filename,firstworkingdir,SETTING_FileName,0)
			invoke g_key_file_load_from_file,settingKEY,FullPName, 0,0   
			invoke g_free,FullPName
		ELSE
			invoke g_key_file_load_from_file,settingKEY,SETTING_FileName, 0,0   
		ENDIF
		Helpers_Setting_var_Get
		mov Settings_FilesTypeListe						,rv(g_key_file_get_string_list,settingKEY,"FilesTypeListe","Settings_FilesTypeListe",addr Settings_NFilesTypeListe,0)
		mov Settings_Folding_EndOf_First_Word_Liste		,rv(g_key_file_get_string_list,settingKEY,"Folding","Settings_Folding_EndOf_First_Word_Liste",addr Settings_NFolding_First_Word_Liste,0)
		mov Settings_Folding_EndOf_Second_Word_Liste	,rv(g_key_file_get_string_list,settingKEY,"Folding","Settings_Folding_EndOf_Second_Word_Liste",addr Settings_NFolding_Second_Word_Liste,0)

		mov Settings_Folding_First_Word_Liste				,rv(g_key_file_get_string_list,settingKEY,"Folding","Settings_Folding_First_Word_Liste",addr Settings_NFolding_First_Word_Liste,0)
		mov Settings_Folding_Second_Word_Liste			,rv(g_key_file_get_string_list,settingKEY,"Folding","Settings_Folding_Second_Word_Liste",addr Settings_NFolding_Second_Word_Liste,0)

		mov Settings_Folding_First_Word_End_Liste		,rv(g_key_file_get_string_list,settingKEY,"Folding","Settings_Folding_First_Word_End_Liste",addr Settings_NFolding_First_Word_End_Liste,0)
		mov Settings_Folding_Second_Word_End_Liste		,rv(g_key_file_get_string_list,settingKEY,"Folding","Settings_Folding_Second_Word_End_Liste",addr Settings_NFolding_Second_Word_End_Liste,0)
		invoke g_key_file_free,settingKEY
		ret
	Settings_Load	ENDP


	.data
		Settings_FilesTypeListe						gpointer	0
		Settings_NFilesTypeListe						qword		0
 
		Settings_Folding_First_Word_Liste				gpointer	0
		Settings_Folding_EndOf_First_Word_Liste		gpointer	0
		Settings_NFolding_First_Word_Liste			qword		0

		Settings_Folding_Second_Word_Liste			gpointer	0
		Settings_Folding_EndOf_Second_Word_Liste	gpointer	0
		Settings_NFolding_Second_Word_Liste			qword		0
 
		Settings_Folding_First_Word_End_Liste			gpointer	0
		Settings_NFolding_First_Word_End_Liste		qword		0

		Settings_Folding_Second_Word_End_Liste		gpointer	0
		Settings_NFolding_Second_Word_End_Liste		qword		0
 

		TFile_Type_ST__Name				gpointer	0
		TFile_Type_ST_ProgrammingLanguage	gpointer	0
		TFile_Type_ST_StyleScheme			gpointer	0
		TFile_Type_ST_Icon					gpointer	0
        	TFile_Type_ST_Extention				gpointer	0
	.code
	
	Settings_Get_Files_Type	PROC _ftypeName:gpointer
		local settingKEY	:gpointer
		local FullPName	:gpointer
        	local ftypeName:gpointer
        		mov ftypeName,_ftypeName
			mov settingKEY     ,rv( g_key_file_new)      
			IFNB <firstworkingdir>
				mov FullPName,rv(g_build_filename,firstworkingdir,SETTING_FileName,0)
				invoke g_key_file_load_from_file,settingKEY,FullPName, 0,0   
				invoke g_free,FullPName
			ELSE
				invoke g_key_file_load_from_file,settingKEY,SETTING_FileName, 0,0   
			ENDIF
			mov TFile_Type_ST__Name				,rv(g_key_file_get_string,settingKEY,ftypeName,"_Name",0)
			mov TFile_Type_ST_ProgrammingLanguage	,rv(g_key_file_get_string,settingKEY,ftypeName,"ProgrammingLanguage",0)
			mov TFile_Type_ST_StyleScheme			,rv(g_key_file_get_string,settingKEY,ftypeName,"StyleScheme",0)
			mov TFile_Type_ST_Icon					,rv(g_key_file_get_string,settingKEY,ftypeName,"Icon",0)
			mov TFile_Type_ST_Extention				,rv(g_key_file_get_string,settingKEY,ftypeName,"Extention",0)
			invoke g_key_file_free,settingKEY
		ret
	Settings_Get_Files_Type	ENDP
	
	Settings_Append_Files_Type	PROC _ftypeName:gpointer,ProgrammingLanguage :gpointer, StyleScheme:gpointer,Icon :gpointer, Extention:gpointer
		local __Name				:gpointer	
		local _ProgrammingLanguage :gpointer	
		local _StyleScheme			:gpointer	
		local _Icon					:gpointer	
        	local _Extention				:gpointer	
		local settingKEY	:gpointer
		local FullPName	:gpointer

			mov __Name				,_ftypeName		
			mov _ProgrammingLanguage	,ProgrammingLanguage	
			mov _StyleScheme			,StyleScheme		
			mov _Icon					,Icon		
			mov _Extention				,Extention
							  						

			mov settingKEY     ,rv( g_key_file_new)      
			IFNB <firstworkingdir>
				mov FullPName,rv(g_build_filename,firstworkingdir,SETTING_FileName,0)
				invoke g_key_file_load_from_file,settingKEY,FullPName, 0,0   
				invoke g_free,FullPName
			ELSE
				invoke g_key_file_load_from_file,settingKEY,SETTING_FileName, 0,0   
			ENDIF
			g_key_file_set_string(	settingKEY	,__Name	,"_Name"				,__Name	)	
			g_key_file_set_string(	settingKEY	,__Name	,"ProgrammingLanguage",_ProgrammingLanguage	)	
			g_key_file_set_string(	settingKEY	,__Name	,"StyleScheme"			,_StyleScheme	)	
			g_key_file_set_string(	settingKEY	,__Name	,"Icon"					,_Icon	)	
			g_key_file_set_string(	settingKEY	,__Name	,"Extention"				,_Extention	)	
			FilesTypes_Exist_Name proto :gpointer
			.if rv(FilesTypes_Exist_Name,	__Name)==0
				mov Settings_FilesTypeListe,rv(List_Append,Settings_FilesTypeListe,__Name,addr Settings_NFilesTypeListe)
				invoke g_key_file_set_string_list,settingKEY,"FilesTypeListe","Settings_FilesTypeListe",Settings_FilesTypeListe,Settings_NFilesTypeListe
			.endif
 
			IFNB <firstworkingdir>
				mov FullPName,rv(g_build_filename,firstworkingdir,SETTING_FileName,0)
				invoke g_key_file_save_to_file,settingKEY,FullPName,0
				invoke g_free,FullPName
			ELSE
				invoke g_key_file_save_to_file,settingKEY,SETTING_FileName,0
			ENDIF
			invoke g_key_file_free,settingKEY
		ret
	Settings_Append_Files_Type	ENDP
	
	Settings_InsertInProjectList	PROC  __ProjectStr:gpointer
	local ProjectStr:gpointer
	
		mov ProjectStr,__ProjectStr
		.if ProjectStr==0
			ret
		.endif
		.if byte ptr [ProjectStr]==0
			ret
		.endif
		.if 		rv(g_strcmp0,ProjectStr,Settings_Last_Project) == 0 
			ret
		.else
			.if 		rv(g_strcmp0,ProjectStr,Settings_Last_Project1) == 0 
				swapmm	Settings_Last_Project,Settings_Last_Project1
			.else
				.if 	rv(g_strcmp0,ProjectStr,Settings_Last_Project2) == 0 
					swapmm	Settings_Last_Project1,Settings_Last_Project2
					swapmm	Settings_Last_Project,Settings_Last_Project1
				.else
					.if 	rv(g_strcmp0,ProjectStr,Settings_Last_Project3) == 0 
						swapmm	Settings_Last_Project3,Settings_Last_Project2
						swapmm	Settings_Last_Project1,Settings_Last_Project2
						swapmm	Settings_Last_Project,Settings_Last_Project1
					.else
						.if 	rv(g_strcmp0,ProjectStr,Settings_Last_Project4) == 0 
							swapmm	Settings_Last_Project3,Settings_Last_Project4
							swapmm	Settings_Last_Project3,Settings_Last_Project2
							swapmm	Settings_Last_Project1,Settings_Last_Project2
							swapmm	Settings_Last_Project,Settings_Last_Project1
						.else
							.if 	rv(g_strcmp0,ProjectStr,Settings_Last_Project5) == 0 
								swapmm	Settings_Last_Project5,Settings_Last_Project4
								swapmm	Settings_Last_Project3,Settings_Last_Project4
								swapmm	Settings_Last_Project3,Settings_Last_Project2
								swapmm	Settings_Last_Project1,Settings_Last_Project2
								swapmm	Settings_Last_Project,Settings_Last_Project1
							.else
								.if 	rv(g_strcmp0,ProjectStr,Settings_Last_Project6) == 0 
									swapmm	Settings_Last_Project5,Settings_Last_Project6
									swapmm	Settings_Last_Project5,Settings_Last_Project4
									swapmm	Settings_Last_Project3,Settings_Last_Project4
									swapmm	Settings_Last_Project3,Settings_Last_Project2
									swapmm	Settings_Last_Project1,Settings_Last_Project2
									swapmm	Settings_Last_Project,Settings_Last_Project1
								.else
									.if 	rv(g_strcmp0,ProjectStr,Settings_Last_Project7) == 0 
										swapmm	Settings_Last_Project7,Settings_Last_Project6
										swapmm	Settings_Last_Project5,Settings_Last_Project6
										swapmm	Settings_Last_Project5,Settings_Last_Project4
										swapmm	Settings_Last_Project3,Settings_Last_Project4
										swapmm	Settings_Last_Project3,Settings_Last_Project2
										swapmm	Settings_Last_Project1,Settings_Last_Project2
										swapmm	Settings_Last_Project,Settings_Last_Project1
									.else
										.if 	rv(g_strcmp0,ProjectStr,Settings_Last_Project8) == 0 
											swapmm	Settings_Last_Project7,Settings_Last_Project8
											swapmm	Settings_Last_Project7,Settings_Last_Project6
											swapmm	Settings_Last_Project5,Settings_Last_Project6
											swapmm	Settings_Last_Project5,Settings_Last_Project4
											swapmm	Settings_Last_Project3,Settings_Last_Project4
											swapmm	Settings_Last_Project3,Settings_Last_Project2
											swapmm	Settings_Last_Project1,Settings_Last_Project2
											swapmm	Settings_Last_Project,Settings_Last_Project1
										.else
											.if 	rv(g_strcmp0,ProjectStr,Settings_Last_Project9) == 0 
												swapmm	Settings_Last_Project9,Settings_Last_Project8
												swapmm	Settings_Last_Project7,Settings_Last_Project8
												swapmm	Settings_Last_Project7,Settings_Last_Project6
												swapmm	Settings_Last_Project5,Settings_Last_Project6
												swapmm	Settings_Last_Project5,Settings_Last_Project4
												swapmm	Settings_Last_Project3,Settings_Last_Project4
												swapmm	Settings_Last_Project3,Settings_Last_Project2
												swapmm	Settings_Last_Project1,Settings_Last_Project2
												swapmm	Settings_Last_Project,Settings_Last_Project1
											.else
												swapmm	Settings_Last_Project9,Settings_Last_Project8
												swapmm	Settings_Last_Project7,Settings_Last_Project8
												swapmm	Settings_Last_Project7,Settings_Last_Project6
												swapmm	Settings_Last_Project5,Settings_Last_Project6
												swapmm	Settings_Last_Project5,Settings_Last_Project4
												swapmm	Settings_Last_Project3,Settings_Last_Project4
												swapmm	Settings_Last_Project3,Settings_Last_Project2
												swapmm	Settings_Last_Project1,Settings_Last_Project2
												swapmm	Settings_Last_Project,Settings_Last_Project1
												;invoke g_free,Settings_Last_Project
												m2m	Settings_Last_Project,ProjectStr
												Insert_LastProject_In_MenuList												
											.endif
										.endif
									.endif
								.endif
							.endif
						.endif
					.endif
				.endif
			.endif
		.endif

		call Settings_Save
		ret
	Settings_InsertInProjectList	ENDP
	Settings_Save	PROC
		local settingKEY	:gpointer     
		local FullPName	:gpointer


			mov settingKEY     ,rv( g_key_file_new)      
			IFNB <firstworkingdir>
				mov FullPName,rv(g_build_filename,firstworkingdir,SETTING_FileName,0)
				invoke g_key_file_load_from_file,settingKEY,FullPName, 0,0   
				invoke g_free,FullPName
			ELSE
				invoke g_key_file_load_from_file,settingKEY,SETTING_FileName, 0,0   
			ENDIF


	     	;mov FullPName,rv(g_build_filename,firstworkingdir,SETTING_FileName,0)
		;mov settingKEY     ,rv( g_key_file_new)    
			Helpers_Setting_var_Set

		invoke g_key_file_set_string_list,settingKEY,"FilesTypeListe","Settings_FilesTypeListe",Settings_FilesTypeListe,Settings_NFilesTypeListe
		invoke g_key_file_set_string_list,settingKEY,"Folding","Settings_Folding_EndOf_First_Word_Liste",Settings_Folding_EndOf_First_Word_Liste,Settings_NFolding_First_Word_Liste
		invoke g_key_file_set_string_list,settingKEY,"Folding","Settings_Folding_EndOf_Second_Word_Liste",Settings_Folding_EndOf_Second_Word_Liste	,Settings_NFolding_Second_Word_Liste
		invoke g_key_file_set_string_list,settingKEY,"Folding","Settings_Folding_First_Word_Liste",Settings_Folding_First_Word_Liste	,Settings_NFolding_First_Word_Liste
		invoke g_key_file_set_string_list,settingKEY,"Folding","Settings_Folding_Second_Word_Liste",Settings_Folding_Second_Word_Liste	,Settings_NFolding_Second_Word_Liste
		invoke g_key_file_set_string_list,settingKEY,"Folding","Settings_Folding_First_Word_End_Liste",Settings_Folding_First_Word_End_Liste	,Settings_NFolding_First_Word_End_Liste
		invoke g_key_file_set_string_list,settingKEY,"Folding","Settings_Folding_Second_Word_End_Liste",Settings_Folding_Second_Word_End_Liste	,Settings_NFolding_Second_Word_End_Liste
				
	    	invoke g_key_file_save_to_file,settingKEY,FullPName,0
		IFNB <firstworkingdir>
			mov FullPName,rv(g_build_filename,firstworkingdir,SETTING_FileName,0)
			invoke g_key_file_save_to_file,settingKEY,FullPName,0
			invoke g_free,FullPName
		ELSE
			invoke g_key_file_save_to_file,settingKEY,SETTING_FileName,0
		ENDIF

	    	invoke g_key_file_free,settingKEY

		ret
	Settings_Save	ENDP	
	
 