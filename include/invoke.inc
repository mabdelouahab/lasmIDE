IF 		@Platform EQ 3	;	ELF64
	OPTION RENAMEKEYWORD:<invoke>=invokeOld
	OPTION RENAMEKEYWORD:<END>=ENDOld
	END MACRO entry:VARARG
		PURGE fr_r4
		PURGE fr_r8
		PURGE fr_i8
		PURGE fr_i16
		PURGE fr_i32
		InvokeVerify
		ENDOld entry
	ENDM
ENDIF

;	forward-referenced Macros
fr_r4 MACRO VV
	_ForwardReferencedDef_&VV	EQU  .TYPE REAL4 
	_ForwardReferencedDef2_&VV	EQU  REAL4
%	InvRecordHint VV,_ForwardReferencedDef_&VV,_ForwardReferencedDef2_&VV
	EXITM<VV>
ENDM
fr_r8 MACRO VV
	_ForwardReferencedDef_&VV	EQU .TYPE REAL8
	_ForwardReferencedDef2_&VV	EQU REAL8
%	InvRecordHint VV,_ForwardReferencedDef_&VV,_ForwardReferencedDef2_&VV
	EXITM<VV>
ENDM

fr_i8 MACRO VV
	_ForwardReferencedDef_&VV	EQU 42;.TYPE BYTE 
	_ForwardReferencedDef2_&VV	EQU 1
%	InvRecordHint VV,_ForwardReferencedDef_&VV,_ForwardReferencedDef2_&VV
	EXITM<VV>
ENDM
fr_i16 MACRO VV
	_ForwardReferencedDef_&VV	EQU 42;.TYPE WORD 
	_ForwardReferencedDef2_&VV	EQU 2
%	InvRecordHint VV,_ForwardReferencedDef_&VV,_ForwardReferencedDef2_&VV
	EXITM<VV>
ENDM
fr_i32 MACRO VV
	_ForwardReferencedDef_&VV	EQU 42;.TYPE DWORD 
	_ForwardReferencedDef2_&VV	EQU 4
%	InvRecordHint VV,_ForwardReferencedDef_&VV,_ForwardReferencedDef2_&VV
	EXITM<VV>
ENDM
	InvHintCount = 0
	InvRecordHint MACRO op:REQ,_ForwardReferencedDef_:REQ,_ForwardReferencedDef2_:REQ
		InvHintCount = InvHintCount + 1
	%	@CatStr(<_VH_>,%InvHintCount) TEXTEQU <op>
	%	@CatStr(<_VH_L_>,%InvHintCount) = @Line
	%	@CatStr(<_VH_FN_>,%InvHintCount) TEXTEQU <@FileCur>
	%	@CatStr(<_VH_FR2_>,%InvHintCount) TEXTEQU <_ForwardReferencedDef2_>
	
	ENDM

IF 		@Platform EQ 3	;	ELF64




	InvokeVerify MACRO
		LOCAL n, vt,found
		n = 0
		found=0
		REPEAT InvokeVerifyCount
		
			n = n + 1
			_VarName TEXTEQU @CatStr(<_VM_>,%n)
			_FileName TEXTEQU @CatStr(<_VM_FN_>,%n)
			_ProcName TEXTEQU @CatStr(<_VM_PN_>,%n)
	%		vt = .TYPE _VarName
	%		IF (TYPE(_VarName) EQ REAL4) 
	%			echo ***** INVOKE VERIFY: forward-referenced FLOAT operand _VarName (invoke _ProcName [File: _FileName at line(@CatStr(%(@CatStr(<_VM_L_>,%n)) ))] )
	%			echo .	Suggested fixes:
	%			echo .		1. Move _VarName definition before INVOKE.
	%			echo .		2. Specify the operand type explicitly: @CatStr(<fr_r4>)( _VarName )
				found = 1;
			ENDIF
	%		IF (TYPE(_VarName) EQ REAL8) 
	%			echo ***** INVOKE VERIFY: forward-referenced FLOAT operand _VarName (invoke _ProcName [File: _FileName at line(@CatStr(%(@CatStr(<_VM_L_>,%n)) ))] )
	%			echo .	Suggested fixes:
	%			echo .		1. Move _VarName definition before INVOKE.
	%			echo .		2. Specify the operand type explicitly:  @CatStr(<fr_r8>)( _VarName )
				found = 1;
			ENDIF
	%		IF (TYPE(_VarName) EQ 1) 
	%			echo ***** INVOKE VERIFY: forward-referenced BYTE operand _VarName (invoke _ProcName [File: _FileName at line(@CatStr(%(@CatStr(<_VM_L_>,%n)) ))] )
	%			echo .	Suggested fixes:
	%			echo .		1. Move _VarName definition before INVOKE.
	%			echo .		2. Specify the operand type explicitly: @CatStr(<fr_i8>)( _VarName )
				found = 1;
			ENDIF
	%		IF (TYPE(_VarName) EQ 2) 
	%			echo ***** INVOKE VERIFY: forward-referenced WORD operand _VarName (invoke _ProcName [File: _FileName at line(@CatStr(%(@CatStr(<_VM_L_>,%n)) ))] )
	%			echo .	Suggested fixes:
	%			echo .		1. Move _VarName definition before INVOKE.
	%			echo .		2. Specify the operand type explicitly: @CatStr(<fr_i16>)( _VarName )
				found = 1
			ENDIF
	%		IF (TYPE(_VarName) EQ 4) 
	%			echo ***** INVOKE VERIFY: forward-referenced DWORD operand _VarName (invoke _ProcName [File: _FileName at line(@CatStr(%(@CatStr(<_VM_L_>,%n)) ))] )
	%			echo .	Suggested fixes:
	%			echo .		1. Move _VarName definition before INVOKE.
	%			echo .		2. Specify the operand type explicitly: @CatStr(<fr_i32>)( _VarName )
				found = 1
			ENDIF
			IF vt AND 1
	%			echo ***** INVOKE VERIFY: forward-referenced PROC operand _VarName (invoke  IN _ProcName at line @CatStr(%(@CatStr(<_VM_L_>,%n)))). Define it before the invoke.
	%			.ERRNDEF <INVOKE_FORWARD_PROC: forward-referenced PROC operand _VarName (invoke  IN _ProcName at line @CatStr(%(@CatStr(<_VM_L_>,%n)))). Define it before the invoke.>
			ENDIF
		ENDM
		n = 0
		REPEAT InvHintCount
			n = n + 1
			_VarName TEXTEQU @CatStr(<_VH_>,%n)
			_FileName TEXTEQU @CatStr(<_VH_FN_>,%n)
%			IF TYPE(_VarName) NE @CatStr(<_VH_FR2_>,%n)
%				echo ******** INVOKE VERIFY: wrong type hint for _VarName (File: _FileName at line @CatStr(%(@CatStr(<_VH_L_>,%n))))
				found = 1
			ENDIF
		ENDM
		
		IF 	found EQ 1
		%	.ERR <INVOKE_FORWARD_REFERENCED: forward-referenced operands .>
		ENDIF
	ENDM
	InvokeVerifyCount = 0
	InvRecord MACRO op:REQ
		InvokeVerifyCount = InvokeVerifyCount + 1
	%	@CatStr(<_VM_>,%InvokeVerifyCount) TEXTEQU <op>
	%	@CatStr(<_VM_L_>,%InvokeVerifyCount) = @Line
	%	@CatStr(<_VM_FN_>,%InvokeVerifyCount) TEXTEQU <@FileCur>
	%	@CatStr(<_VM_PN_>,%InvokeVerifyCount) TEXTEQU <__CurrentInvokeProcName>
	ENDM 

	nbinvoke=0
	invoke MACRO ProcName,args:vararg
	__CurrentInvokeProcName TEXTEQU <ProcName,args>
	nbinvoke=nbinvoke+1
		invoke_rspV 		= 	0 
		invoke_floatreg 	= 	1
		invoke_intreg		=	1
		invoke_NB_floatreg 	= 	0 

		IF HAS_REG(<private_UpStrAndClean(&ProcName)>, <RAX,EAX,AX,AH,AL>) EQ 1
			.ERR <INVOKE Error (SysV): call target uses RAX>
		ENDIF

		IF HAS_REG(<private_UpStrAndClean(&ProcName)>, <RSP,ESP>) EQ 1
			.ERR <INVOKE Error (SysV): call target uses RSP>
		ENDIF
		IFB	<args>
			XOR	EAX,EAX
			CALL	ProcName
			EXITM
		ENDIF
		Err_RegisterValueOverwrittenByINVOKE args 
		
		revercedArgs EQU <reverseArg(args)>
		
	%	FOR __varg,<args>
		%	IFB <__varg>
	%			.ERR <Syntax ERROR {ProcName,args}>
				EXITM
			ENDIF
			assign_values_REG_UP __varg  

		ENDM 
		
		invoke_intreg 		=	invoke_intreg-1		; عدد المعاملات الصحيحة

		IF invoke_intreg GT 6
			invoke_rspV 	=	invoke_intreg - 6
		ENDIF
		invoke_floatreg 	=	invoke_NB_floatreg	; عدد معاملات float
		IF invoke_NB_floatreg GT 8
			invoke_rspV 	=	invoke_rspV + (invoke_NB_floatreg - 8)
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
			assign_values_REG_DWN __varg  

		ENDM
		IF invoke_floatreg
			MOV EAX,invoke_floatreg
		ELSE
			XOR EAX,EAX
		ENDIF
		CALL	ProcName
		IF	invoke_rspV
			ADD 	RSP,invoke_rspV
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
		local ts_t,ts_txt,_arg_,tlc_pos2
		%	ts_t  TEXTEQU <UpStr_Str_>
			ts_txt TEXTEQU <>
		%	FORC _arg_,<ts_t>
			  tlc_pos2 INSTR 1,<abcdefghijklmnopqrstuvwxyz>,<&_arg_>
			  IF tlc_pos2
			     ts_txt TEXTEQU ts_txt,@SubStr(<ABCDEFGHIJKLMNOPQRSTUVWXYZ>,%tlc_pos2,1)
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

	 
	Is_XMM_	MACRO __varg
	local instrUP,instr_
		instrUP  CatStr  <private_UpStr(&__varg)> 
	%	instr_  INSTR <-XMM0-XMM1-XMM2-XMM3-XMM4-XMM5-XMM6-XMM7-XMM8-XMM9-XMM10-XMM11-XMM12-XMM13-XMM14-XMM15->,<-&instrUP&->
		IF instr_
			EXITM<1>
		ELSE
			EXITM<0>
		ENDIF
	ENDM 

	private_Int_Reg	macro __val,TY
		LOCAL _regsz
%		IFNB <TY>
			_regsz = TY
		ELSE
			_regsz = type( __val)
		ENDIF
		IF _regsz EQ 0
			_regsz = 8	;; sizeless memory operand such as [rax]: treat as QWORD (pointer)
		ENDIF

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
	ResolveOperandType MACRO v_
		rt_unknown = 0
		rt_type = .TYPE(v_)
		IF (rt_type AND 20h) EQ 0
	%		IFDEF _ForwardReferencedDef_&v_
	%			rt_type = _ForwardReferencedDef_&v_
				rt_type2 TEXTEQU <_ForwardReferencedDef2_&v_>
			ELSE
				rt_type2 TEXTEQU <0>
				rt_unknown = 1
			ENDIF
		ELSE
			rt_type2 TEXTEQU <TYPE(v_)>
		ENDIF
	ENDM
	assign_values_REG_UP macro  v_
		local v_var,vreg__,instrUP,tlc_pos2,tlc_pos3
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
		tlc_pos2 INSTR 1,<v_>,<!">
		IF tlc_pos2 EQ 1
			IF invoke_intreg lt 7
				.DATA
					v_var	db	parseescape(v_),0
				.CODE
	 
			%	LEA private_Int_Reg(QWORD,8),v_var 
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
				LEA private_Int_Reg(QWORD,8),v_var 
			ENDIF
			invoke_intreg=invoke_intreg+1
			EXITM
		ENDIF
	%	instrUP  CatStr  <private_UpStr(&v_)> 
	%	tlc_pos2 INSTR 1,<instrUP>,<ADDR >
	%	tlc_pos3 INSTR 1,<instrUP>,<ADDR	>
		IF ((tlc_pos2 EQ 1) OR (tlc_pos3 EQ 1))
			IF invoke_intreg lt 7
			% 	LEA private_Int_Reg(QWORD,8), @SubStr(v_,5)
			ENDIF					
			invoke_intreg=invoke_intreg+1
			EXITM
		ENDIF					
	%	tlc_pos2 INSTR 1,<instrUP>,<OFFSET >
		IF tlc_pos2 EQ 1
			IF invoke_intreg lt 7
			% 	LEA private_Int_Reg(QWORD,8), @SubStr(v_,7)
			ENDIF
			invoke_intreg=invoke_intreg+1
			EXITM
		ENDIF
	%	tlc_pos2 INSTR 1,<instrUP>,<&>
		IF tlc_pos2 EQ 1
			IF invoke_intreg lt 7
			% 	LEA private_Int_Reg(QWORD,8), @SubStr(v_,2)
			ENDIF
			invoke_intreg=invoke_intreg+1
			EXITM
		ENDIF
		ResolveOperandType v_
		IF rt_unknown
				InvRecord v_
		ENDIF
		IF rt_type 
			IF (rt_type2 EQ REAL4) 
				IF	invoke_NB_floatreg lt 8
					MOVSS @CatStr(<XMM>,%invoke_NB_floatreg),v_ 
				ENDIF 
				invoke_NB_floatreg=invoke_NB_floatreg+1
				EXITM
			ENDIF
			IF (rt_type2 EQ REAL8) 
				IF	invoke_NB_floatreg lt 8
					MOVSD @CatStr(<XMM>,%invoke_NB_floatreg),v_ 
				ENDIF 
				invoke_NB_floatreg=invoke_NB_floatreg+1
				EXITM
			ENDIF
			IF Is_XMM_(v_)
				IF	invoke_NB_floatreg lt 8
					MOVAPD  @CatStr(<XMM>,%invoke_NB_floatreg),v_ 
				ENDIF 
				invoke_NB_floatreg=invoke_NB_floatreg+1
				EXITM	
			ENDIF
		ENDIF
		IF invoke_intreg lt 7
			IF  ((rt_type eq 42) OR (rt_type eq 98) OR (rt_type eq 48) OR (rt_type eq 34))    ;; GLOBAL var; LOCAL  var; register;; MEM
				MOV private_Int_Reg(v_, rt_type2),v_
			ELSEIF rt_type eq 165     ;; proc
				LEA private_Int_Reg(QWORD),v_
			ELSEIF rt_type eq 36     ;; immediate operand or constant
			%	IF &v_& EQ 0
			%	vreg__ EQU <private_Int_Reg(QWORD)>
				%	XOR vreg__,vreg__
				ELSE
					MOV private_Int_Reg(QWORD),v_
				ENDIF
			ELSE
		 		PUSH v_
				POP  private_Int_Reg(QWORD)
			ENDIF
		ENDIF
		invoke_intreg=invoke_intreg+1
		EXITM
	endm

	assign_values_REG_DWN macro  v_
		local v_var,instrUP,tlc_pos2,tlc_pos3
		IF private__IsImmFloat(v_)
			IF invoke_NB_floatreg gt 8
				.DATA
					v_var	REAL8	v_
				.CODE
				MOV	RAX,QWORD PTR v_var 
				PUSH	RAX 
			ENDIF
			invoke_NB_floatreg=invoke_NB_floatreg-1
			EXITM
		ENDIF
		tlc_pos2 INSTR 1,<v_>,<!">
		tlc_pos3 INSTR 1,<v_>,<!'>
		IF (tlc_pos2 EQ 1) OR (tlc_pos3 EQ 1)
			IF invoke_intreg gt 6
				.DATA
					v_var	db	parseescape(v_),0
				.CODE
				LEA	RAX,v_var 
				PUSH	RAX 
			ENDIF
			invoke_intreg=invoke_intreg-1
			EXITM
		ENDIF
		;; ---- ADDR / OFFSET
	%	instrUP  CatStr  <private_UpStr(&v_)> 
	%	tlc_pos2 INSTR 1,<instrUP>,<ADDR >
	%	tlc_pos3 INSTR 1,<instrUP>,<ADDR	>
		IF ((tlc_pos2 EQ 1) OR (tlc_pos3 EQ 1))
			IF invoke_intreg gt 6
			%	LEA RAX,@SubStr(v_,5) 
				PUSH	RAX
			ENDIF
			invoke_intreg=invoke_intreg-1
			EXITM
		ENDIF
	%	tlc_pos2 INSTR 1,<instrUP>,<OFFSET >
		IF tlc_pos2 EQ 1
			IF invoke_intreg gt 6
			%	LEA RAX,@SubStr(v_,7) 
				PUSH	RAX 
			ENDIF
			invoke_intreg=invoke_intreg-1
			EXITM
		ENDIF
	%	tlc_pos2 INSTR 1,<instrUP>,<&>
		IF tlc_pos2 EQ 1
			IF invoke_intreg gt 6
			%	LEA RAX,@SubStr(v_,2) 
				PUSH	RAX 
			ENDIF
			invoke_intreg=invoke_intreg-1
			EXITM
		ENDIF
		;; ---- float من متغير أ سجل XMM (العدّاد يُنقَص دائمًا)

		ResolveOperandType v_
		IF rt_type
			IF (rt_type2 EQ REAL4)
				IF invoke_NB_floatreg gt 8
					MOV	EAX,DWORD PTR v_ 
					PUSH	RAX 
				ENDIF
				invoke_NB_floatreg=invoke_NB_floatreg-1
				EXITM
			ENDIF
			IF (rt_type2 EQ REAL8)
				IF invoke_NB_floatreg gt 8
					MOV	RAX,QWORD PTR v_ 
					PUSH	RAX 
				ENDIF
				invoke_NB_floatreg=invoke_NB_floatreg-1
				EXITM
			ENDIF
			IF Is_XMM_(v_)
				IF invoke_NB_floatreg gt 8
					LEA	RSP,[RSP-8]
					MOVSD	QWORD PTR [RSP],v_
				ENDIF
				invoke_NB_floatreg=invoke_NB_floatreg-1
				EXITM
			ENDIF
		ENDIF
		IF invoke_intreg gt 6
			IF rt_type EQ 165
				LEA	RAX,v_
			ELSEIF (rt_type2 EQ 1) OR (rt_type2 EQ 2)
				MOVZX	EAX,v_ 
			ELSEIF rt_type2 EQ 4
				MOV	EAX,v_ 
			ELSE
				MOV	RAX,v_ 
			ENDIF
			PUSH	RAX 
		ENDIF
		invoke_intreg=invoke_intreg-1
	endm
	IsEscapeC MACRO ___n
	%	IFIDN <___n>,<n>	;	\n
		%	EXITM<0AH>
		ENDIF
	%	IFIDN <___n>,<t>
		%	EXITM<09H>
		ENDIF
	%	IFIDN <___n>,<v>	 
		%	EXITM<11>
		ENDIF
	%	IFIDN <___n>,<B>
		%	EXITM<33>
		ENDIF
	%	IFIDN <___n>,<r>	 
		%	EXITM<13>
		ENDIF
	%	IFIDN <___n>,<!\>	 
		%	EXITM<92>
		ENDIF
	%	IFIDN <___n>,<0>	 
		%	EXITM<0>
		ENDIF
	%	IFIDN <___n>,<a>	 
		%	EXITM<7>
		ENDIF
	%	IFIDN <___n>,<b>	 
		%	EXITM<8>
		ENDIF
	%	IFIDN <___n>,<f>	 
		%	EXITM<12>
		ENDIF
	%	IFIDN <___n>,<!">
		%	EXITM<34>
		ENDIF
	%	IFIDN <___n>,<!'>
		%	EXITM<39>
		ENDIF
		EXITM<-1>
	ENDM
	 

	parseescape MACRO _text:VARARG
		LOCAL Onechar, Sresult, IsEscape, IsBS, IsCode, theQuote, InPosCase, strSize, cpos, escVal, ise
		strSize = @SizeStr(<_text>)
		IF strSize EQ 0
		    EXITM <>
		ENDIF
		theQuote SUBSTR <_text>, 1, 1
		IFDIF theQuote, <!">
		    IFDIF theQuote, <!'>
		        EXITM <_text>
		    ENDIF
		ENDIF
		IsEscape  = 0
		cpos      = 1
		InPosCase = 0                  ; 0 بداية، 1 داخل نص، 3 بعد رقم
		Sresult   TEXTEQU <>
		WHILE cpos LT strSize - 1
		    cpos = cpos + 1
		    Onechar SUBSTR <_text>, cpos, 1
		    IsBS = 0
		    IFIDN Onechar, <\>
		        IF IsEscape EQ 0
		            IsEscape = 1
		            IsBS = 1
		        ENDIF
		    ENDIF
		    IF IsBS EQ 0
		        IsCode = 0
		        IF IsEscape
	%               escVal = IsEscapeC(Onechar)
		            IF escVal GE 0
		                IsCode = 1
		                ise TEXTEQU %escVal
		            ENDIF
		        ENDIF
		        IF IsCode
		            IF InPosCase EQ 0
		                Sresult TEXTEQU ise
		            ELSEIF InPosCase EQ 1
		                Sresult CATSTR Sresult, <!",>, ise
		            ELSE
		                Sresult CATSTR Sresult, <,>, ise
		            ENDIF
		            InPosCase = 3
		        ELSE
		            IFIDN Onechar, <!<>
		                Onechar CATSTR <!!>, <!<>
		            ELSEIFIDN Onechar, <!>>
		                Onechar CATSTR <!!>, <!>>
		            ENDIF
		            IF IsEscape
		                Onechar CATSTR <\>, Onechar      ; هرب غير معرف: نُبقي  
		            ENDIF
		            IF InPosCase EQ 0
		                Sresult CATSTR <!">, Onechar
		            ELSEIF InPosCase EQ 1
		                Sresult CATSTR Sresult, Onechar
		            ELSE
		                Sresult CATSTR Sresult, <,!">, Onechar
		            ENDIF
		            InPosCase = 1
		        ENDIF
		        IsEscape = 0
		    ENDIF
		ENDM
		IF InPosCase EQ 0
		    Sresult TEXTEQU <0>
		ELSEIF InPosCase EQ 1
		    Sresult CATSTR Sresult, <!">
		ENDIF
	%   EXITM <Sresult>
	ENDM

	 

	Chk_IsPtr macro __varg:REQ
	local tlc_pos,tlc_pos2,CurrentArg
	%	IFB <__varg>
			EXITM<0>
		ENDIF
	%	tlc_pos INSTR 1,<__varg>,<!">
		IF tlc_pos NE 0
			EXITM<2>
		ENDIF
	%	tlc_pos INSTR 1,<__varg>,<!'>
		IF tlc_pos NE 0
			EXITM<2>
		ENDIF
	%	tlc_pos INSTR 1,< __varg>,< &>
		IF tlc_pos NE 0
			EXITM<2>
		ENDIF
		CurrentArg  CatStr  <private_UpStr(&__varg)> 
	%	tlc_pos INSTR 1,< CurrentArg >,< ADDR >
		IF tlc_pos NE 0
		%	tlc_pos2 INSTR 1,<CurrentArg>,<[>
			IF tlc_pos2 EQ 0
				EXITM<2>
			ENDIF
			EXITM<1>
		ENDIF
	%	tlc_pos INSTR 1,< CurrentArg >,< OFFSET >
		IF tlc_pos NE 0
		%	tlc_pos INSTR 1,<CurrentArg>,<[>
			IF tlc_pos EQ 0
				EXITM<2>
			ENDIF
			EXITM<1>
		ENDIF
		EXITM<0>
	endm

	Chk_IsFloat macro __varg:REQ

	%	IFB <__varg>
			EXITM<0>
		ENDIF
		
		ResolveOperandType __varg
		IF rt_type 
			IF (rt_type2 EQ REAL4) OR  (rt_type2 EQ REAL8) 
				EXITM<1>
			ENDIF 
		ENDIF
	
		
	%	IF 	private__IsImmFloat(__varg)		 
			EXITM<1>
		else
	 %		IF OPATTR(__varg)
			%	IF 	(TYPE(__varg) EQ REAL8)  OR (TYPE(__varg) EQ REAL4)
					EXITM<1>
				ENDIF
	 		ENDIF
		ENDIF
		EXITM<0>
	endm

	Chk_XMM macro __varg:REQ
	local tlc_pos
	%	IFB <__varg>
			EXITM<0>
		ENDIF
	%	tlc_pos INSTR 1,< XMM0 XMM1 XMM2 XMM3 XMM4 XMM5 XMM6 XMM7 XMM8 XMM9 XMM10 XMM11 XMM12 XMM13 XMM14 XMM15 >,< __varg >
		IF tlc_pos NE 0
			EXITM<1>					
		ENDIF
		EXITM<0>
	endm

	HAS_REG MACRO Expr:REQ, RegList:REQ
		LOCAL  Result, Token,tp
		Result = 0
	%    FOR Token, <RegList>
		    %	tp INSTR < Expr >,< Token >
			IF tp
		        Result = 1
		        EXITM
		    ENDIF
		ENDM
		EXITM %Result
	ENDM

	private_UpStrAndClean macro UpStr_Str_:req
	local ts_t,ts_txt,tlc_pos2,_arg_
	%	ts_t  TEXTEQU <UpStr_Str_>
		ts_txt TEXTEQU <>
	%	FORC _arg_,<ts_t>
	%      tlc_pos2 INSTR 1,<abcdefghijklmnopqrstuvwxyz[]+-*(),:>,<&_arg_>
		  IF tlc_pos2
		     ts_txt TEXTEQU ts_txt,@SubStr(<ABCDEFGHIJKLMNOPQRSTUVWXYZ                >,%tlc_pos2,1)
		  ELSE
		     ts_txt TEXTEQU ts_txt,<&_arg_>
		  ENDIF
		ENDM
	%	EXITM <ts_txt>
	endm

	Err_RegisterValueOverwrittenByINVOKE MACRO  Args:VARARG
		LOCAL ArgIdx,ArgFlt,  CurrentArg,_IsPtr,_IsFloat,tp
		ArgIdx = 0
		ArgFlt = 0
	%    FOR _CurrentArg, <Args>
			_IsPtr = Chk_IsPtr(&_CurrentArg)
			_IsFloat = 0
			IF _IsPtr lt 2
				CurrentArg  CatStr  <private_UpStrAndClean(&_CurrentArg)> 
			ENDIF
			IF _IsPtr EQ 0
				IF Chk_IsFloat(_CurrentArg) OR Chk_XMM(CurrentArg)
					_IsFloat = 1
				ENDIF
			ENDIF
			IF _IsFloat
				ArgFlt = ArgFlt + 1
					IF ArgFlt GE 2
						%	tp INSTR < XMM0 >,< CurrentArg >
						IF tp NE 0
							.ERR <INVOKE Error (SysV): XMM0 overwritten by Arg 1 before being read>
						ENDIF
					ENDIF
					IF ArgFlt GE 3
						%	tp INSTR < XMM1 >,< CurrentArg >
						IF tp
							.ERR <INVOKE Error (SysV): XMM1 overwritten by Arg 2 before being read>
						ENDIF
					ENDIF
					IF ArgFlt GE 4
						%	tp INSTR < XMM2 >,< CurrentArg >
						IF tp
							.ERR <INVOKE Error (SysV): XMM2 overwritten by Arg 3 before being read>
						ENDIF
					ENDIF
					IF ArgFlt GE 5
						%	tp INSTR < XMM3 >,< CurrentArg >
						IF tp
							.ERR <INVOKE Error (SysV): XMM3 overwritten by Arg 4 before being read>
						ENDIF
					ENDIF
					IF ArgFlt GE 6
						%	tp INSTR < XMM4 >,< CurrentArg >
						IF tp
							.ERR <INVOKE Error (SysV): XMM4 overwritten by Arg 5 before being read>
						ENDIF
					ENDIF			
					IF ArgFlt GE 7
						%	tp INSTR < XMM5 >,< CurrentArg >
						IF tp
							.ERR <INVOKE Error (SysV): XMM5 overwritten by Arg 6 before being read>
						ENDIF
					ENDIF			
					IF ArgFlt GE 8
						%	tp INSTR < XMM6 >,< CurrentArg >
						IF tp
							.ERR <INVOKE Error (SysV): XMM6 overwritten by Arg 7 before being read>
						ENDIF
					ENDIF			
					IF ArgFlt GE 9
						%	tp INSTR < XMM7 >,< CurrentArg >
						IF tp
							.ERR <INVOKE Error (SysV): XMM7 overwritten by Arg 8 before being read>
						ENDIF
					ENDIF	
					IF ArgFlt GT 8
						IF HAS_REG(<CurrentArg>, <RAX,EAX,AX,AH,AL>) EQ 1
							.ERR <INVOKE Error (SysV): RAX used in a stack-passed argument>
						ENDIF
						IF HAS_REG(<CurrentArg>, <RSP,ESP,SP,SPL>) EQ 1
							.ERR <INVOKE Error (SysV): RSP used in a stack-passed argument>
						ENDIF
					ENDIF		
			ELSE
				ArgIdx = ArgIdx + 1
				IF _IsPtr lt 2
					IF ArgIdx GE 2  
						IF HAS_REG(<CurrentArg>, <RDI,EDI,DI,DIL>) EQ 1
								.ERR <INVOKE Error (SysV): RDI overwritten by Arg 1 before being read>
						ENDIF
					ENDIF
					IF ArgIdx GE 3  
						IF HAS_REG(<CurrentArg>, <RSI,ESI,SI,SIL>) EQ 1
								.ERR <INVOKE Error (SysV): RSI overwritten by Arg 2 before being read>
						ENDIF
					ENDIF
					IF ArgIdx GE 4  
						IF HAS_REG(<CurrentArg>, <RDX,EDX,DX,DH,DL>) EQ 1;
								.ERR <INVOKE Error (SysV): RDX overwritten by Arg 3 before being read>
						ENDIF
					ENDIF
					IF ArgIdx GE 5  
						IF HAS_REG(<CurrentArg>, <RCX,ECX,CX,CH,CL>) EQ 1
							.ERR <INVOKE Error (SysV): RCX overwritten by Arg 4 before being read>
						ENDIF
					ENDIF
					IF ArgIdx GE 6  
						IF HAS_REG(<CurrentArg>, <R8,R8D,R8W,R8B>) EQ 1
							.ERR <INVOKE Error (SysV): R8 overwritten by Arg 5 before being read>
						ENDIF
					ENDIF
					IF ArgIdx GE 7  
						IF HAS_REG(<CurrentArg>, <R9,R9D,R9W,R9B>) EQ 1
							.ERR <INVOKE Error (SysV): R9 overwritten by Arg 6 before being read>
						ENDIF
					ENDIF	
				    IF ArgIdx GT 6
						IF HAS_REG(<CurrentArg>, <RAX,EAX,AX,AH,AL>) EQ 1
							.ERR <INVOKE Error (SysV): RAX used in a stack-passed argument>
						ENDIF
						IF HAS_REG(<CurrentArg>, <RSP,ESP,SP,SPL>) EQ 1
							.ERR <INVOKE Error (SysV): RSP used in a stack-passed argument>
						ENDIF
					ENDIF				
				ENDIF	
			ENDIF
		ENDM
	ENDM
		 	
ENDIF
