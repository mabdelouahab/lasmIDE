Private_getdecTypename MACRO __varg
	local val__
	instr_  INSTR <__varg>,<:>
	IF instr_
	    	val__ SUBSTR <__varg>,instr_+1
	    	exitm<val__>
	else
	    	exitm<>
	ENDIF
ENDM

Private_Def_Wedg MACRO __var,__varStr
	local val__,m_
	.data
	IFNB <__varStr>
		val__	DB	@CatStr(<!">,__varStr,<!">),0
	ENDIF
	IFB <__varStr>
		val__	DB	@CatStr(<!">,__var,<!">),0
	ENDIF
	;	__var	DQ	0
 	@CatStr(<gtkWed_Def_>,%CurrentWindowName,<_Count>)=@CatStr(<gtkWed_Def_>,%CurrentWindowName,<_Count>)+1;gtkWed_Def_&CurrentWindowName&_Count = gtkWed_Def_&CurrentWindowName&_Count + 1;
	m_=@CatStr(<gtkWed_Def_>,%CurrentWindowName,<_Count>)

	@CatStr(<Def_>,%CurrentWindowName,<_W_>,%m_) TEXTEQU <&__var&>
	@CatStr(<Def_>,%CurrentWindowName,<_N_>,%m_) TEXTEQU <addr val__>

ENDM
Private_Def_Wedg_Event MACRO __var,__varStr,__varProc
	local val__,m_
	.data
		val__	DB	@CatStr(<!">,__varStr,<!">),0
	IFNDEF	__var
	;	__var	DQ	0
	ENDIF
 		@CatStr(<gtkEvents_Def_>,%CurrentWindowName,<_Count>)=@CatStr(<gtkEvents_Def_>,%CurrentWindowName,<_Count>)+1
	m_=	@CatStr(<gtkEvents_Def_>,%CurrentWindowName,<_Count>)

	@CatStr(<Def_>,%CurrentWindowName,<_WE_>,%m_) TEXTEQU <&__var&>
	@CatStr(<Def_>,%CurrentWindowName,<_NE_>,%m_) TEXTEQU <addr val__>
	@CatStr(<Def_>,%CurrentWindowName,<_PE_>,%m_) TEXTEQU <__varProc>

ENDM



.glage_defwidgets MACRO __Args:VARARG
	FOR __varg,<__Args>
%		IFB <Private_getdecTypename(__varg)>
%			Private_Def_Wedg <__varg>
		else 
%			Private_Def_Wedg <Private_getdecvarname(__varg)>,	<Private_getdecTypename(__varg)>	
		ENDIF
	ENDM
ENDM
.glage_gtkwindow MACRO WindowName,WindowFileGladName,WindowCaption
	local val__,m_
	CurrentWindowName 			EQU <Private_getdecvarname(WindowName)> 
%		IFB <Private_getdecTypename(WindowName)>
			CurrentWindowInGladeName 	EQU <WindowName> 	
		else 
			CurrentWindowInGladeName 	EQU <Private_getdecTypename(WindowName)> 
		ENDIF
		CurrentWindowInGladeName 	EQU <Private_getdecvarname(WindowName)> 
		ifnb <WindowFileGladName>
			CurrentWindowFileGladName 	EQU <WindowFileGladName> 
		else; <WindowFileGladName>
			CurrentWindowFileGladName 	EQU <&CurrentWindowName&.glade> 
		endif
	.data
	%	ifnb <WindowCaption>
		%	val__	DB	@CatStr(<!">,&WindowCaption&,<!">),0
		else; <WindowCaption>
		%	val__	DB	@CatStr(<!">,%CurrentWindowName,<!">),0
			;CurrentWindowCaption 	EQU <&CurrentWindowName&> 
		endif
		CurrentWindowCaption 	EQU <addr val__> 

%		gtkWed_Def_&CurrentWindowName&_Count=0
%		gtkEvents_Def_&CurrentWindowName&_Count=0

%		IFB <Private_getdecTypename(WindowName)>
%			Private_Def_Wedg <WindowName>
		else 
%			Private_Def_Wedg 	<Private_getdecTypename(WindowName)>	;<Private_getdecvarname(WindowName)>,
		ENDIF
	
endm

.glage_initgtkwindow macro __Args:VARARG
%	Def_initgtkwindow_&CurrentWindowName&_&@FileName&	EQU 1
	;@CatStr(<Def_initgtkwindow_>,CurrentWindowName,<_>,%@FileName) EQU 1
	lastinitgtkwindowprocedureName EQU <@CatStr(<Init_>,%CurrentWindowName,<_>,%@FileName)>;<procName>
	lastinitgtkwindowprocedure__Args EQU <__Args>;<procName>
	lastinitgtkwindowprocedureArgs__ =0

	IFB <__Args>
		.code
		lastinitgtkwindowprocedureName PROC 
	ELSE
		lastinitgtkwindowprocedureStrArgs equ <>
		lastinitgtkwindowprocedureStrArgsCall equ <>
		j___=1
		FOR __varg,<__Args>
			
			IF j___ EQ 1 
				lastinitgtkwindowprocedureStrArgsCall CATSTR lastinitgtkwindowprocedureStrArgsCall,<Private_getdecvarname(__varg)>
			ELSE
				lastinitgtkwindowprocedureStrArgsCall CATSTR lastinitgtkwindowprocedureStrArgsCall,<,Private_getdecvarname(__varg)>
			ENDIF
			IF j___ EQ 1 
				lastinitgtkwindowprocedureStrArgs CATSTR lastinitgtkwindowprocedureStrArgs,<@&__varg>
			ELSE
				IF j___ GE 7 
					lastinitgtkwindowprocedureStrArgs CATSTR lastinitgtkwindowprocedureStrArgs,<,__varg>
				ELSE
					lastinitgtkwindowprocedureStrArgs CATSTR lastinitgtkwindowprocedureStrArgs,<,@&__varg>
					j___=j___+1
				ENDIF
			ENDIF
			lastinitgtkwindowprocedureArgs__=lastinitgtkwindowprocedureArgs__+1
		ENDM
		lastprocedureArgs__=lastinitgtkwindowprocedureArgs__
		.code
		lastinitgtkwindowprocedureName PROC lastinitgtkwindowprocedureStrArgs	
		j___=1
		FOR __varg,<__Args>
			IF j___ LT 7 
				LOCAL __varg
				@CatStr(<__@SubArg>,%j___) equ <Private_getdecvarname(__varg)>
				@CatStr(<__@SubArg_lastinitgtkwindow>,%j___) equ <Private_getdecvarname(__varg)>
				j___=j___+1
			ENDIF
		ENDM
	ENDIF

endm

.glage_endinitgtkwindow macro
		RET
	 lastinitgtkwindowprocedureName ENDP
endm	

.glage_newgtkwindow  macro __gtkwindow,__Args:VARARG
	ifb <__Args>
	%	Init___gtkwindow_&__gtkwindow&()
	else
	%	Init___gtkwindow_&__gtkwindow&( __Args)
	endif
endm	

.glage_endgtkwindow macro
	local l_,m_,structW,ioo
	.code
	align 8
%	IFDEF Def_initgtkwindow_&CurrentWindowName&_&@FileName& 
		IF lastinitgtkwindowprocedureArgs__ EQ 0
		;	%	echo	Init___gtkwindow_&CurrentWindowName&	PROC
			%		Init___gtkwindow_&CurrentWindowName&	PROC
		ELSE
		;	%	echo	Init___gtkwindow_&CurrentWindowName&	PROC lastinitgtkwindowprocedureStrArgs	
			%		Init___gtkwindow_&CurrentWindowName&	PROC lastinitgtkwindowprocedureStrArgs	
			j___=1
			FOR __varg,<lastinitgtkwindowprocedure__Args>
				IF j___ LT 7 
					LOCAL __varg
					j___=j___+1
				ENDIF
			ENDM
		ENDIF
		
	ENDIF		
%	IFNDEF Def_initgtkwindow_&CurrentWindowName&_&@FileName& 
;%	echo	Init___gtkwindow_&CurrentWindowName&	PROC
%		Init___gtkwindow_&CurrentWindowName&	PROC
	ENDIF			

		local lbuilder:gpointer
		local _err:gpointer
		
	%	IFDEF Def_initgtkwindow_&CurrentWindowName&_&@FileName& 
			n=0
			repeat  lastinitgtkwindowprocedureArgs__
				n=n+1
				IF n LT 7
		;	%echo	mov @CatStr(<__@SubArg_lastinitgtkwindow>,%n), @&@CatStr(<__@SubArg_lastinitgtkwindow>,%n)
			%	mov @CatStr(<__@SubArg_lastinitgtkwindow>,%n), @&@CatStr(<__@SubArg_lastinitgtkwindow>,%n)
				ENDIF
			endm
		ENDIF		
					
 		mov _err,0
		mov lbuilder,rv(gtk_builder_new)
	%	invoke gtk_builder_add_from_string,lbuilder,addr &CurrentWindowName&_Interface,&CurrentWindowName&_InterfaceSZ,addr _err
		.if rax==0
		    lea r12,_err
		    mov r12,[r12]
		    mov r12,QWORD PTR [r12+8]
		    invoke printf,str$(<13,10,"Error loading interface {%s}">),r12
		    ret
		.endif

	%	l_=gtkWed_Def_&CurrentWindowName&_Count 
		m_=0
		structW STRUCT	8
		repeat l_
			m_=m_+1
	%		@CatStr(<Def_>,%CurrentWindowName,<_W_>,%m_)	DQ	0
		endm
		structW ENDS
		.DATA
		%	&CurrentWindowName&	structW	<>
		.CODE
	%	l_=gtkWed_Def_&CurrentWindowName&_Count 
		m_=0
		repeat l_
			m_=m_+1
	%		invoke gtk_builder_get_object, lbuilder,@CatStr(<Def_>,%CurrentWindowName,<_N_>,%m_) 
	%		mov @CatStr(%CurrentWindowName,<.>,%@CatStr(<Def_>,%CurrentWindowName,<_W_>,%m_)),rax
		endm
%		IFDEF Def_initgtkwindow_&CurrentWindowName&_&@FileName&
			IF lastinitgtkwindowprocedureArgs__ NE 0
			%	invoke &lastinitgtkwindowprocedureName&, &lastinitgtkwindowprocedureStrArgsCall&
			ELSE
			%		invoke &lastinitgtkwindowprocedureName&	
			ENDIF
		ENDIF		
		
	%	l_=gtkEvents_Def_&CurrentWindowName&_Count 
		m_=0
		repeat l_
			m_=m_+1
		%	    invoke g_signal_connect_data, @CatStr(%CurrentWindowName,<.>,%@CatStr(<Def_>,%CurrentWindowName,<_WE_>,%m_)),@CatStr(<Def_>,%CurrentWindowName,<_NE_>,%m_),addr @CatStr(<Def_>,%CurrentWindowName,<_PE_>,%m_),0,0,0  ,0,0,0      
		endm
		m_=1
			invoke g_object_unref,lbuilder
		;%	invoke gtk_window_set_title, @CatStr(%CurrentWindowName,<.>,%@CatStr(<Def_>,%CurrentWindowName,<_W_>,%m_)),CurrentWindowCaption
		%	invoke gtk_widget_show_all ,@CatStr(%CurrentWindowName,<.>,%@CatStr(<Def_>,%CurrentWindowName,<_W_>,%m_))
			invoke gtk_main
			RET
%		Init___gtkwindow_&CurrentWindowName& ENDP

	.DATA
%	    &CurrentWindowName&_Interface label qword
%	    incbin <&CurrentWindowFileGladName&>
%	    &CurrentWindowName&_InterfaceSZ equ $-&CurrentWindowName&_Interface
	
endm	

.glage_gtkevent MACRO _WedGName,_EventName,__Args:VARARG
local evstr
	lastprocedureeventName EQU <@CatStr(<On_>,_WedGName,<_>,_EventName,<_>,%@FileName)>;<procName>

%	Private_Def_Wedg_Event _WedGName,_EventName,lastprocedureeventName 
	lastprocedureeventArgs__ =0
	lastprocedureArgs__=0
		.code
%	IFB <__Args>

	%echo	&lastprocedureeventName& PROC 
	%	&lastprocedureeventName& PROC 
	ELSE
		strArgs equ <>
		j___=1
		FOR __varg,<__Args>
			IF j___ EQ 1 
				strArgs CATSTR strArgs,<@&__varg>
				j___=j___+1
			ELSEIF j___ GE 7 
				strArgs CATSTR strArgs,<,__varg>
			ELSE
				strArgs CATSTR strArgs,<,@&__varg>
				j___=j___+1
			ENDIF
			lastprocedureeventArgs__=lastprocedureeventArgs__+1
		ENDM
		lastprocedureArgs__=lastprocedureeventArgs__
		.code
%echo		lastprocedureeventName PROC strArgs	
%		lastprocedureeventName PROC strArgs	
		j___=1
		FOR __varg,<__Args>
			IF j___ LT 7 
				LOCAL __varg
				@CatStr(<__@SubArg>,%j___) equ <Private_getdecvarname(__varg)>
				j___=j___+1
			ENDIF
		ENDM
	ENDIF

endm
.glage_endgtkevent macro
		RET
	lastprocedureeventName ENDP
endm	

