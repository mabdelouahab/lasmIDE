OPTION RENAMEKEYWORD:<invoke>=invokeOld

invoke MACRO ProcName,args:vararg

	invoke_rspV 		= 	0;Calc_align_RSP(args)
	invoke_floatreg 	= 	1
	invoke_intreg		=	1
	;invoke_Rax_usd		=	Chk_RAX_In_Args(args)
	invoke_RAX_svd		=	0
	invoke_XMM0_svd		=	0
	invoke_Arg_n		=	0
	invoke_NB_floatreg 	= 	0;Chk_Float_In_Args(args)
	;Calc_NArgs args
;%echo ProcName,args
	revercedArgs EQU <reverseArg(args)>
%	IFB	<args>
		CALL	ProcName
	ELSE
	%	FOR __varg,<args>
		%	IFB <__varg>
%				.err <Syntax ERROR {ProcName,args}>
				EXITM
			ENDIF
	 		;Err_RegisterValueOverwrittenByINVOKE(__varg)
			assign_values_REG_UP __varg  
			invoke_Arg_n=invoke_Arg_n+1
		ENDM 
		invoke_intreg 		=	invoke_intreg-1
		IF invoke_intreg GT 6
			invoke_rspV 	=	(invoke_intreg -6)
		ELSE
			invoke_rspV=0	
		ENDIF
		invoke_floatreg = invoke_NB_floatreg
		IF invoke_NB_floatreg GT 7
			invoke_rspV 	=	invoke_rspV + (invoke_NB_floatreg -7)
			invoke_floatreg	=	8
		ENDIF
		IF invoke_rspV
			if ( invoke_rspV and 1)
				invoke_rspV=invoke_rspV+1
				SUB RSP,8
			ENDIF 
		ENDIF 
		invoke_rspV=invoke_rspV*8
	%	FOR __varg,<revercedArgs>
		%	IFB <__varg>
				EXITM
			ENDIF
	 		;Err_RegisterValueOverwrittenByINVOKE(args)
			assign_values_REG_DWN __varg  
			invoke_Arg_n=invoke_Arg_n+1
		ENDM
		IF invoke_floatreg
			MOV RAX,invoke_floatreg
		ELSE
			XOR EAX,EAX
		ENDIF
		CALL	ProcName
		IF	invoke_rspV
			ADD 	RSP,invoke_rspV
		ENDIF

	ENDIF
	ENDM
reverseArg MACRO arglist:vararg
	LOCAL revercedArgs, __varg,n
	revercedArgs TEXTEQU <>
	n=0
	FOR __varg, <arglist>
		if n eq 0
			revercedArgs CATSTR <__varg>
			n=n+1
		else
			revercedArgs CATSTR <__varg>, <,>, revercedArgs
		endif
	ENDM
	EXITM <revercedArgs>
ENDM

	private_UpStr macro UpStr_Str_:req
		ts_t  TEXTEQU <UpStr_Str_>
		ts_txt TEXTEQU <>
	%	FORC _arg_,<ts_t>
	      tlc_pos2 INSTR 1,<abcdefghijklmnopqrstuvwxy	z>,<&_arg_>
	      IF tlc_pos2
	         ts_txt TEXTEQU ts_txt,@SubStr(<ABCDEFGHIJKLMNOPQRSTUVWXY Z>,%tlc_pos2,1)
	      ELSE
	         ts_txt TEXTEQU ts_txt,<&_arg_>
	      ENDIF
		ENDM
	%	EXITM <ts_txt>
	endm

	private__IsImmFloat macro v_Str_:req
	local IsFloat,tmpLen,cur_Pos,tlc_pos2
		IsFloat=1
		tmpLen	=	@SizeStr(<v_Str_>)
		cur_Pos 	=	0
		repeat tmpLen
			cur_Pos=cur_Pos+1
			ch_unq SubStr <v_Str_>,cur_Pos,1
			tlc_pos2 INSTR 1,<.0123456789>,ch_unq
			IF tlc_pos2 EQ 0
				IsFloat=0
				EXITM
			ENDIF
		endm
		if IsFloat EQ 1
			IsFloat=0
			tlc_pos2 INSTR 1,<v_Str_>,<.>
			IF tlc_pos2		;It must contain the point
				IF tlc_pos2 NE 1  	;The point doesn't have to be at the beginning
					IF tmpLen NE tlc_pos2	;The point doesn't have to be at the end
						tlc_pos2 INSTR tlc_pos2+1,<v_Str_>,<.>
						IF tlc_pos2 EQ 0	;It must not contain two points
							IsFloat=1
						endif					
					ENDIF
				ENDIF		
			ENDIF		
		ENDIF
		EXITM <IsFloat>
	endm	


Err_Chk_RegisterValueOverwrittenByINVOKE macro chk_,args:vararg
	local retv,j
	retv=0
	j=0
%	FOR __varg,<args>
	%	IFB <__varg>
			EXITM
		ENDIF
		j=j+1
		IF j gt invoke_Arg_n 
		echo ************************************************
			instrUP  CatStr  <private_UpStr(&__varg)> 
		%	instr_  INSTR <chk_>,<instrUP>
			IF instr_
			%	.err	<Register value overwritten by INVOKE...(__varg)>
				retv=1
				EXITM
			ENDIF
		ENDIF
	ENDM
	EXITM<retv>
ENDM
Is_RAX_	MACRO __varg
	local Is_RAX
	Is_RAX=0
	instrUP  CatStr  <private_UpStr(&__varg)> 
%	instr_  INSTR <-RAX-EAX-AX-AH-AL->,<-&instrUP&->
	IF instr_
		Is_RAX=1
	ENDIF
	EXITM<Is_RAX>
ENDM
Is_XMM_	MACRO __varg
	local Is_XMM
	Is_XMM=0
	instrUP  CatStr  <private_UpStr(&__varg)> 
%	instr_  INSTR <-XMM0-XMM1-XMM2-XMM3-XMM4-XMM5-XMM6-XMM7-XMM8-XMM9-XMM10-XMM11-XMM12-XMM13-XMM14-XMM15->,<-&instrUP&->
	IF instr_
		Is_XMM=1
	;%echo exit_Is_XMM_ with : @CatStr(%Is_XMM): __varg instrUP
		EXITM<1>
	ELSE
		EXITM<0>
	ENDIF
	
ENDM
Chk_RAX_In_Args macro args:vararg
	local retv,n_arg
	retv=0
	n_arg=0
%	FOR __varg,<args>
	%	IFB <__varg>
			EXITM
		ENDIF
		n_arg=n_arg+1
		instrUP  CatStr  <private_UpStr(&__varg)> 
	%	instr_  INSTR <-RAX-EAX-AX-AH-AL->,<-&instrUP&->
		IF instr_
			retv=n_arg
			EXITM
		ENDIF
	ENDM
	EXITM<retv>
ENDM
		


Err_RegisterValueOverwrittenByINVOKE macro args:vararg
	IF 		invoke_intreg	EQ	1
		EXITM< Err_Chk_RegisterValueOverwrittenByINVOKE( < RDI EDI DI DIL >,args)>
	ELSEIF	invoke_intreg	EQ	2
		EXITM< Err_Chk_RegisterValueOverwrittenByINVOKE( < RSI ESI SI SIL >,args)>
	ELSEIF	invoke_intreg	EQ	3
		EXITM< Err_Chk_RegisterValueOverwrittenByINVOKE( < RDX EDX DX DH DL >,args)>
	ELSEIF	invoke_intreg	EQ	4
		EXITM< Err_Chk_RegisterValueOverwrittenByINVOKE( < RCX ECX CX CH CL CH >,args)>
	ELSEIF	invoke_intreg	EQ	5
		EXITM< Err_Chk_RegisterValueOverwrittenByINVOKE( < R8 R8D R8W R8B >,args)>
	ELSEIF	invoke_intreg	EQ	6
		EXITM< Err_Chk_RegisterValueOverwrittenByINVOKE( < R9 R9D R9W R9B >,args)>
	ENDIF
ENDM

private_Int_Reg	macro __val
	LOCAL _regsz
	_regsz equ type( __val)
	IF 		invoke_intreg	EQ	1
		;invoke_intreg=invoke_intreg+1
		IF 		_regsz	EQ	8
			EXITM<RDI>
		ELSEIF	_regsz	EQ	4	
			EXITM<EDI>
		ELSEIF	_regsz	EQ	2	
			EXITM<DI>
		ELSEIF	_regsz	EQ	1
			EXITM<DIL>
		ENDIF	
	ELSEIF	invoke_intreg	EQ	2
	;	invoke_intreg=invoke_intreg-1
		IF 		_regsz	EQ	8
			EXITM<RSI>
		ELSEIF	_regsz	EQ	4	
			EXITM<ESI>
		ELSEIF	_regsz	EQ	2	
			EXITM<SI>
		ELSEIF	_regsz	EQ	1
			EXITM<SIL>
		ENDIF	
	ELSEIF	invoke_intreg	EQ	3
		;invoke_intreg=invoke_intreg-1
		IF 		_regsz	EQ	8
			EXITM<RDX>
		ELSEIF	_regsz	EQ	4	
			EXITM<EDX>
		ELSEIF	_regsz	EQ	2	
			EXITM<DX>
		ELSEIF	_regsz	EQ	1
			EXITM<DL>
		ENDIF	
	ELSEIF	invoke_intreg	EQ	4
		;invoke_intreg=invoke_intreg-1
		IF 		_regsz	EQ	8
			EXITM<RCX>
		ELSEIF	_regsz	EQ	4	
			EXITM<ECX>
		ELSEIF	_regsz	EQ	2	
			EXITM<CX>
		ELSEIF	_regsz	EQ	1
			EXITM<CL>
		ENDIF	
	ELSEIF	invoke_intreg	EQ	5
		;invoke_intreg=invoke_intreg-1
		IF 		_regsz	EQ	8
			EXITM<R8>
		ELSEIF	_regsz	EQ	4	
			EXITM<R8D>
		ELSEIF	_regsz	EQ	2	
			EXITM<R8W>
		ELSEIF	_regsz	EQ	1
			EXITM<R8B>
		ENDIF	
	ELSEIF	invoke_intreg	EQ	6
		;invoke_intreg=invoke_intreg-1
		IF 		_regsz	EQ	8
			EXITM<R9>
		ELSEIF	_regsz	EQ	4	
			EXITM<R9D>
		ELSEIF	_regsz	EQ	2	
			EXITM<R9W>
		ELSEIF	_regsz	EQ	1
			EXITM<R9B>
		ENDIF	
	ELSE 
		;invoke_intreg=invoke_intreg-1
		IF 		_regsz	EQ	8
			EXITM<RAX>
		ELSEIF	_regsz	EQ	4	
			EXITM<EAX>
		ELSEIF	_regsz	EQ	2	
			EXITM<AX>
		ELSEIF	_regsz	EQ	1
			EXITM<AL>
		ENDIF	
	ENDIF
ENDM


Private_save_rax	macro
	IFNDEF save_raxV
		.DATA
			save_raxV	DQ	0
		.CODE
	ENDIF
	MOV save_raxV,RAX
endm
Private_restor_rax	macro
	IF invoke_RAX_svd
		MOV RAX,save_raxV
	ENDIF
endm
Private_save_xmm0	macro
	IFNDEF save_xmm0V
		.DATA
			save_xmm0V	DQ	0
		.CODE
	ENDIF
	MOVQ save_xmm0V,XMM0
	invoke_XMM0_svd
endm
Private_restor_xmm0	macro
	IF invoke_XMM0_svd
		MOVQ xmm0,save_xmm0V
	ENDIF
endm

If_Must_be_Save_RAX MACRO args:vararg
	local n
	IF invoke_Rax_usd GT 6
		n=0
	%	FOR __varg,<args>
		%	IFB <__varg>
				EXITM
			ENDIF
			n=n+1
			IF n gt 6
				IF n eq invoke_Rax_usd
					EXITM
				ENDIF
				instrUP  CatStr  <private_UpStr(&__varg)> 
			%	tlc_pos2 INSTR 1,<instrUP>,<ADDR >
				IF tlc_pos2 EQ 0
					instrUP  CatStr  <private_UpStr(&__varg)> 
				%	tlc_pos2 INSTR 1,<instrUP>,<OFFSET >
					IF tlc_pos2 EQ 0
						tlc_pos2 INSTR 1,<__varg>,<!">
						IF tlc_pos2 EQ 0
							tlc_pos2 INSTR 1,<__varg>,<!">
							IF tlc_pos2 EQ 0
					%			IF 		private__IsImmFloat(__varg)		EQ 0 
									IF OPATTR(__varg)	ne	48
										Private_save_rax
										invoke_Rax_svd=1
										EXITM
									ENDIF						
								ENDIF						
							ENDIF
						ENDIF
					ENDIF
				ENDIF
			ENDIF
		ENDM	
	ENDIF
endm


Chk_Float_In_Args macro args:vararg
	local nFloat
	nFloat=0
	%	FOR __varg,<args>
		%	IFB <__varg>
				EXITM
			ENDIF
			instrUP  CatStr  <private_UpStr(&__varg)> 
		%	tlc_pos2 INSTR 1,<instrUP>,<ADDR >
			IF tlc_pos2 EQ 0
				instrUP  CatStr  <private_UpStr(&__varg)> 
			%	tlc_pos2 INSTR 1,<instrUP>,<OFFSET >
				IF tlc_pos2 EQ 0
					tlc_pos2 INSTR 1,<__varg>,<!">
					IF tlc_pos2 EQ 0
						tlc_pos2 INSTR 1,<__varg>,<!">
						IF tlc_pos2 EQ 0
					%			IF 		private__IsImmFloat(__varg)		 
									nFloat=nFloat+1
								else
							 		IF OPATTR(__varg)
						%				IF 	(TYPE(__varg) EQ REAL8) 
											nFloat=nFloat+1
						%				elseIF 	(TYPE(__varg) EQ REAL10) 
											nFloat=nFloat+1
						%				elseIF (TYPE(__varg) EQ REAL4)
											nFloat=nFloat+1
										ENDIF
							 		ENDIF
								ENDIF
						ENDIF
					ENDIF
				ENDIF
			ENDIF
		ENDM	
	EXITM<nFloat>

endm

assign_XMMs macro  v_
%echo _assign_XMMs  v_
	IF 		invoke_floatreg lt 9
		MOVAPD  @CatStr(<XMM>,%invoke_floatreg-1),v_ 
		invoke_NB_floatreg=invoke_NB_floatreg+1
	ELSE
		;LEA     RSP, [RSP - 8]
		MOVSD   QWORD PTR [RSP+invoke_rspPos], v_ 
		invoke_rspPos=invoke_rspPos+8
	ENDIF
	invoke_floatreg=invoke_floatreg+1
ENDM


assign_values_Float macro _rSz, v_
	IF 		invoke_floatreg lt 9
	%	MOVS&_rSz& @CatStr(<XMM>,%invoke_floatreg-1),v_ 
		invoke_NB_floatreg=invoke_NB_floatreg+1
	ELSE
		if invoke_XMM0_svd EQ 0
			Private_save_xmm0
		ENDIF
		;LEA     RSP, [RSP - 8]
	%	MOVS&_rSz& XMM0,v_ 
		MOVSD   QWORD PTR [RSP+invoke_rspPos], XMM0
		invoke_rspPos=invoke_rspPos+8
	ENDIF
	invoke_floatreg=invoke_floatreg+1
ENDM

assign_values_Float2 macro _rSz, v_
	IF 		invoke_floatreg lt 9
	%	MOVS&_rSz& @CatStr(<XMM>,%invoke_floatreg-1),v_ 
		invoke_NB_floatreg=invoke_NB_floatreg+1
	ELSE
		if invoke_XMM0_svd EQ 0
			Private_save_xmm0
		ENDIF
		LEA     RSP, [RSP - 8]
	%	MOVS&_rSz& XMM0,v_ 
		MOVSD   QWORD PTR [RSP], XMM0
	ENDIF
	invoke_floatreg=invoke_floatreg+1
ENDM

PUSH_If_Necessary MACRO
	IF invoke_intreg GT 6
		push 
	;	LEA     RSP, [RSP - 8]
		MOV   QWORD PTR [RSP+invoke_rspPos], RAX
		invoke_rspPos=invoke_rspPos+8
		;invoke_rspV=invoke_rspV+8
	ENDIF
ENDM



PUSH_If_Necessary2 MACRO
	IF invoke_intreg GT 7
		LEA     RSP, [RSP - 8]
		MOV   QWORD PTR [RSP], RAX
		;invoke_rspV=invoke_rspV+8
	ENDIF
ENDM

assign_values_REG macro  v_
	local v_var,v_type,vreg__
	IF private__IsImmFloat(v_)	
		.DATA
			v_var	REAL8	v_
		.CODE
		assign_values_Float D,v_var
		EXITM
	ENDIF
;	IF (TYPE(v_) EQ REAL10) 
;
;	ENDIF
	tlc_pos2 INSTR 1,<v_>,<!">
	IF tlc_pos2 EQ 1
		.DATA
			v_var	db	v_,0
		.CODE
		IF invoke_intreg GT 6
			LEA RAX,v_var
			PUSH RAX 
		ELSE
	%		LEA private_Int_Reg(QWORD),v_var
		ENDIF
		invoke_intreg=invoke_intreg-1
		EXITM
	ENDIF
	tlc_pos2 INSTR 1,<v_>,<!'>
	IF tlc_pos2 EQ 1
		.DATA
			v_var	db	v_,0
		.CODE
		IF invoke_intreg GT 6
			LEA RAX,v_var
			PUSH RAX 
		ELSE
			LEA private_Int_Reg(QWORD),v_var
		ENDIF
		invoke_intreg=invoke_intreg-1
		EXITM
	ENDIF
	instrUP  CatStr  <private_UpStr(&v_)> 
%	tlc_pos2 INSTR 1,<instrUP>,<ADDR >
	IF tlc_pos2 EQ 1
		IF invoke_intreg GT 6
		%	LEA RAX,@SubStr(v_,5)
			PUSH RAX 
		ELSE
		% 	LEA private_Int_Reg(QWORD), @SubStr(v_,5)
		ENDIF
		invoke_intreg=invoke_intreg-1
		EXITM
	ENDIF					
%	tlc_pos2 INSTR 1,<instrUP>,<OFFSET >
	IF tlc_pos2 EQ 1
		IF invoke_intreg GT 6
			LEA RAX, @SubStr(v_,7)
			PUSH RAX 
		ELSE
		% 	LEA private_Int_Reg(QWORD), @SubStr(v_,7)
		ENDIF
		invoke_intreg=invoke_intreg-1
		EXITM
	ENDIF
    v_type = opattr(v_)

	IF OPATTR(v_)
		IF (TYPE(v_) EQ REAL4) 
			assign_values_Float S,v_
			EXITM
		ENDIF
		IF (TYPE(v_) EQ REAL8) 
			assign_values_Float D,v_
			EXITM
		ENDIF
	ENDIF
    IF  (v_type eq 48)     ;;register
		IF Is_RAX_(v_)
			Private_restor_rax
		ENDIF
		IF Is_XMM_(v_)
			assign_XMMs v_
			EXITM	
		ENDIF
		IF invoke_intreg GT 6
			PUSH v_
			invoke_intreg=invoke_intreg-1
			EXITM
		ELSE
			MOV private_Int_Reg(v_),v_
			invoke_intreg=invoke_intreg-1
			EXITM
		ENDIF
	ENDIF
    IF  ((v_type eq 42) OR (v_type eq 98) OR (v_type eq 48))     ;; GLOBAL var; LOCAL  var; register
		IF invoke_intreg GT 6
			PUSH v_ 
		ELSE
			MOV private_Int_Reg(v_),v_
		ENDIF
		invoke_intreg=invoke_intreg-1
		EXITM
    ELSEIF v_type eq 36     ;; immediate operand or constant
	%	IF &v_& EQ 0
	%	vreg__ EQU <private_Int_Reg(QWORD)>
			IF invoke_intreg GT 6
				PUSH RAX
			ELSE
		%		XOR vreg__,vreg__
			ENDIF
			invoke_intreg=invoke_intreg-1
			EXITM	
		ELSE
			IF invoke_intreg GT 6
				PUSH v_ 
			ELSE
				MOV private_Int_Reg(QWORD),v_
			ENDIF
			invoke_intreg=invoke_intreg-1
			EXITM
		ENDIF
    ENDIF
	PUSH v_
	IF invoke_intreg lt 7
		POP  private_Int_Reg(QWORD)
	ENDIF
	invoke_intreg=invoke_intreg-1
endm
Calc_NArgs MACRO  args:vararg
	local nargs,nfloat
	nargs=0
%	FOR __varg,<args>
		nargs=invoke_intreg+1
	ENDM
	invoke_NB_floatreg 	= Chk_Float_In_Args(args)
	invoke_Arg_n		=	invoke_intreg
	invoke_intreg 		= 	invoke_intreg - invoke_NB_floatreg
	
	IF invoke_intreg GT 6
		invoke_rspV 	=	(invoke_intreg -6)*8
	ELSE
		invoke_rspV=0	
	ENDIF
ENDM

Calc_align_RSP MACRO  args:vararg
	local nargs,nfloat
	nargs=0
%	FOR __varg,<args>
		nargs=nargs+1
	ENDM
	nfloat = Chk_Float_In_Args(args)
	nargs = nargs - nfloat
	IF nargs GT 6
			nargs = (nargs - 6)*8
	%echo args @CatStr(%nargs)
	ELSE
		nargs=0	
	ENDIF
	EXITM<nargs>
ENDM


assign_values_REG_UP macro  v_
	local v_var,v_type,vreg__,instrUP,p
	IF private__IsImmFloat(v_)
		IF invoke_NB_floatreg lt 8
			.DATA
				v_var	REAL8	v_
			.CODE
			MOVSD @CatStr(<XMM>,%invoke_NB_floatreg),v_var 
		ENDIF
		invoke_NB_floatreg=invoke_NB_floatreg+1
		EXITM
	ENDIF
;	IF (TYPE(v_) EQ REAL10) 
;
;	ENDIF
	tlc_pos2 INSTR 1,<v_>,<!">
	IF tlc_pos2 EQ 1
		IF invoke_intreg lt 7
			.DATA
				v_var	db	parseescape(v_),0
			.CODE
;%			echo acfm$(v_)
		%	LEA private_Int_Reg(QWORD),v_var;acfm$(v_)
		ENDIF
		invoke_intreg=invoke_intreg+1
		EXITM
	ENDIF
	tlc_pos2 INSTR 1,<v_>,<!'>
	IF tlc_pos2 EQ 1
		IF invoke_intreg lt 7
			.DATA
				v_var	db	parseescape(v_),0
			.CODE
			LEA private_Int_Reg(QWORD),v_var;acfm$(v_)
		ENDIF
		invoke_intreg=invoke_intreg+1
		EXITM
	ENDIF
%	instrUP  CatStr  <private_UpStr(&v_)> 
%	tlc_pos2 INSTR 1,<instrUP>,<ADDR >
%	tlc_pos3 INSTR 1,<instrUP>,<ADDR	>
;	%echo _instrUP +++++++++++++++++++v_+ @CatStr(<tlc_pos2_:>,%tlc_pos2,<,tlc_pos3_:>,%tlc_pos3)
	
	IF ((tlc_pos2 EQ 1) OR (tlc_pos3 EQ 1))
	;%echo _instrUP ////////// v_
		IF invoke_intreg lt 7
		% 	LEA private_Int_Reg(QWORD), @SubStr(v_,5)

		ENDIF					
		invoke_intreg=invoke_intreg+1
		EXITM
	ENDIF					
%	tlc_pos2 INSTR 1,<instrUP>,<OFFSET >
	IF tlc_pos2 EQ 1
		IF invoke_intreg lt 7
		% 	LEA private_Int_Reg(QWORD), @SubStr(v_,7)
		ENDIF
		invoke_intreg=invoke_intreg+1
		EXITM
	ENDIF
    v_type = .TYPE(v_);opattr
	IF v_type;OPATTR(v_)
		IF (TYPE(v_) EQ REAL4) 
			IF	invoke_NB_floatreg lt 8
				MOVSS @CatStr(<XMM>,%invoke_NB_floatreg),v_ 
			ENDIF 
			invoke_NB_floatreg=invoke_NB_floatreg+1
			EXITM
		ENDIF
		IF (TYPE(v_) EQ REAL8) 
			IF	invoke_NB_floatreg lt 8
				MOVSD @CatStr(<XMM>,%invoke_NB_floatreg),v_ 
			ENDIF 
			invoke_NB_floatreg=invoke_NB_floatreg+1
			EXITM
		ENDIF
		IF Is_XMM_(v_)
	;%	echo ---------- v_
			IF	invoke_NB_floatreg lt 8
				MOVAPD  @CatStr(<XMM>,%invoke_NB_floatreg),v_ 
		;%echo		MOVAPD  @CatStr(<XMM>,%invoke_NB_floatreg),v_ 
			ENDIF 
			invoke_NB_floatreg=invoke_NB_floatreg+1
			EXITM	
		ENDIF
	ENDIF
	IF invoke_intreg lt 7
		IF  ((v_type eq 42) OR (v_type eq 98) OR (v_type eq 48) OR (v_type eq 34))    ;; GLOBAL var; LOCAL  var; register;; MEM
			MOV private_Int_Reg(v_),v_
		ELSEIF v_type eq 165     ;; proc
			LEA private_Int_Reg(QWORD),v_
		ELSEIF v_type eq 36     ;; immediate operand or constant
		%	IF &v_& EQ 0
		%	vreg__ EQU <private_Int_Reg(QWORD)>
			%	XOR vreg__,vreg__
			ELSE
				;echo ===========
				MOV private_Int_Reg(QWORD),v_
			ENDIF
		ELSE
		;y=typeof v_ 
;% echo %%%%%%%%%%%%% v_ ,; @CatStr(%y);, @CatStr(%y),
	 		PUSH v_
;% echo %%%%%%%%%%%%% private_Int_Reg(QWORD) v_ @CatStr(%.TYPE(v_)) @CatStr(%opattr(v_))
			POP  private_Int_Reg(QWORD)
		ENDIF
	ENDIF
	invoke_intreg=invoke_intreg+1
	EXITM
endm
















assign_values_REG_DWN macro  v_
	local v_var,v_type,vreg__,instrUP
	IF private__IsImmFloat(v_)	
		IF invoke_NB_floatreg gt 7
			.DATA
				v_var	REAL8	v_
			.CODE
			if invoke_XMM0_svd EQ 0
				Private_save_xmm0
			ENDIF
			LEA     RSP, [RSP - 8]
			MOVSD 	XMM0,v_var
			MOVSD   QWORD PTR [RSP], XMM0
		ENDIF
		invoke_NB_floatreg=invoke_NB_floatreg-1
		EXITM
	ENDIF
;	IF (TYPE(v_) EQ REAL10) 
;
;	ENDIF
	tlc_pos2 INSTR 1,<v_>,<!">
	IF tlc_pos2 EQ 1
		IF invoke_intreg gt 6
			.DATA
				v_var	db	parseescape(v_),0
			.CODE
			LEA RAX,v_var;acfm$(v_)
			PUSH RAX 
		ENDIF
		invoke_intreg=invoke_intreg-1
		EXITM
	ENDIF
	tlc_pos2 INSTR 1,<v_>,<!'>
	IF tlc_pos2 EQ 1
		IF invoke_intreg gt 6
			.DATA
				v_var	db	parseescape(v_),0
			.CODE
			LEA RAX,v_var;acfm$(v_)
			PUSH RAX 
		ENDIF
		invoke_intreg=invoke_intreg-1
		EXITM
	ENDIF
%	instrUP  CatStr  <private_UpStr(&v_)> 
%	tlc_pos2 INSTR 1,<instrUP>,<ADDR >
%	tlc_pos3 INSTR 1,<instrUP>,<ADDR	>
	;%echo instrUP +++++++++++++++++++v_+ @CatStr(<tlc_pos2_:>,%tlc_pos2,<,tlc_pos3_:>,%tlc_pos3)
	
	IF ((tlc_pos2 EQ 1) OR (tlc_pos3 EQ 1))
	;echo jjjjjjjj
		IF invoke_intreg gt 6
		%	LEA RAX,@SubStr(v_,5)
			PUSH RAX 
		ENDIF					
		invoke_intreg=invoke_intreg-1
		EXITM
	ENDIF					
%	tlc_pos2 INSTR 1,<instrUP>,<OFFSET >
	;%echo instrUP ++++++++++OFFSET+++++++++v_+ @CatStr(<tlc_pos2_:>,%tlc_pos2)
	IF tlc_pos2 EQ 1
		IF invoke_intreg gt 6
			LEA RAX, @SubStr(v_,7)
			PUSH RAX 
		ENDIF
		invoke_intreg=invoke_intreg-1
		EXITM
	ENDIF
	;echo __________________-
    v_type = .TYPE(v_);opattr(v_)
	;echo __________________+
	IF v_type; OPATTR(v_)  
		IF (TYPE(v_) EQ REAL4) 
			IF invoke_NB_floatreg gt 7
				LEA     RSP, [RSP - 8]
				MOVSS 	XMM0,v_ 
				MOVSD   QWORD PTR [RSP], XMM0
				invoke_NB_floatreg=invoke_NB_floatreg-1
			ENDIF
			EXITM
		ENDIF
		IF (TYPE(v_) EQ REAL8) 
			IF invoke_NB_floatreg gt 7
				LEA     RSP, [RSP - 8]
				MOVSD 	XMM0,v_ 
				MOVSD   QWORD PTR [RSP], XMM0
				invoke_NB_floatreg=invoke_NB_floatreg-1
			ENDIF
			EXITM
		ENDIF
		IF Is_XMM_(v_)
			IF invoke_NB_floatreg gt 7
				LEA     RSP, [RSP - 8]
				MOVSD   QWORD PTR [RSP], v_
				invoke_NB_floatreg=invoke_NB_floatreg-1
				echo Is_XMM_Is_XMM_Is_XMM_Is_XMM_
			ENDIF
			exitm	
		ENDIF
	ENDIF
	IF invoke_intreg gt 6
		PUSH v_
		invoke_intreg=invoke_intreg-1
	ENDIF
endm
IsEscapeC MACRO ___n
	IFIDN <___n>,<n>	;	\n
	%	EXITM<10>
	ENDIF
	IFIDN <___n>,<t>	 
	%	EXITM<9>
	ENDIF
	IFIDN <___n>,<v>	 
	%	EXITM<11>
	ENDIF
	IFIDN <___n>,<r>	 
	%	EXITM<13>
	ENDIF
	IFIDN <___n>,<!\>	 
	%	EXITM<92>
	ENDIF
	IFIDN <___n>,<0>	 
	%	EXITM<0>
	ENDIF
	IFIDN <___n>,<a>	 
	%	EXITM<7>
	ENDIF
	IFIDN <___n>,<b>	 
	%	EXITM<8>
	ENDIF
	IFIDN <___n>,<f>	 
	%	EXITM<12>
	ENDIF
	EXITM<>
ENDM
parseescape MACRO _text:VARARG
		LOCAL Onechar,Sresult,IsEscape,theQuote,TInsert,InPosCase,ch1,strSize,nu$,tmp,flag,lbuf,rbuf,cpos,sln
		strSize=@SizeStr(_text)

		theQuote SUBSTR <_text>,1,1              
		IFDIF theQuote,<!">
			IFDIF theQuote,<!'>
				EXITM <_text>                      
			ENDIF
		ENDIF
		IsEscape	=	0
		cpos		=	0
		InPosCase	=	0	; at start
		Sresult		EQU	<>
%		FORC Onechar,<_text>
			cpos=cpos+1        
			if strSize eq cpos
				exitm
			endif          
			IFIDN <Onechar>,<\>  
				IsEscape = 1
			ENDIF
			IFDIF <Onechar>,<\> 
				IF IsEscape EQ 0
					IF 		InPosCase EQ 0	;	at start
						IFDIF <Onechar>,<">  
							IFDIF <Onechar>,<'>  
								Sresult CATSTR theQuote,<Onechar>
								InPosCase = 1
							ENDIF
						ENDIF
					ELSEIF 	InPosCase EQ 1	;	opned quote
						Sresult CATSTR Sresult,<Onechar>
					ELSEIF 	InPosCase EQ 3	;	closed quote
						Sresult CATSTR Sresult,<,>,theQuote,<Onechar>
						InPosCase = 1
					ENDIF					
				ELSE
				%	IFNB <IsEscapeC(Onechar)>
						IF 		InPosCase EQ 0	;	at start
							Sresult CATSTR <IsEscapeC(Onechar)>
							InPosCase = 3
						ELSEIF 	InPosCase EQ 1	;	opned quote
							Sresult CATSTR Sresult,theQuote,<,>,<IsEscapeC(Onechar)>
							InPosCase = 3
						ELSEIF 	InPosCase EQ 3	;	closed quote
							Sresult CATSTR Sresult,<,>,<IsEscapeC(Onechar)>
						ENDIF						
					ELSE
						IF 		InPosCase EQ 0	;	at start
							Sresult CATSTR theQuote,<\>,<Onechar>
							InPosCase = 1
						ELSEIF 	InPosCase EQ 1	;	opned quote
							Sresult CATSTR Sresult,<\>,<Onechar>
						ELSEIF 	InPosCase EQ 3	;	closed quote
							Sresult CATSTR Sresult,<,>,theQuote,<\>,<Onechar>
							InPosCase = 1
						ENDIF											
					ENDIF
				ENDIF
				IsEscape = 0
			ENDIF
		ENDM
		IF 		InPosCase EQ 0	;	at start
			Sresult CATSTR <0>
		ELSEIF 	InPosCase EQ 1	;	opned quote
			Sresult CATSTR Sresult,theQuote
		ENDIF											
		
	%	EXITM<Sresult>
ENDM
