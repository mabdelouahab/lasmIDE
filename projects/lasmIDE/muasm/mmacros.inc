OPTION DOTNAME
IFDEF __UASM__
	OPTION LITERALS:ON
ENDIF
IFNDEF RAX
    rax TEXTEQU <eax>
ENDIF
str$ macro str__
local _strL
    .data
        _strL   db    str__,0  
    .code
    EXITM<offset _strL>
endm
    TypeOf MACRO arg
      EXITM % opattr(arg)
    ENDM
    Ty_Variable_GLOBAL 	EQU < 42 >
    Ty_Variable_LOCAL 	EQU < 98 >
    Ty_Register 		EQU < 48 >
    Ty_Constant		 	EQU < 36 >

rv macro fn_,arg_:vararg
    IFB <arg_>
        invoke fn_
    ELSE
        invoke fn_,arg_
    ENDIF
    EXITM<rax>
endm
ra macro v
local vforconst
	IF TypeOf(v) eq Ty_Constant
		.data
			vforconst	dq	v
		.code
		mov rax,vforconst
	ELSE
		mov rax,v
    ENDIF
    EXITM<rax>
endm
rc macro v
local vforconst
	IF TypeOf(v) eq Ty_Constant
		.data
			vforconst	dq	v
		.code
		mov rcx,vforconst
	ELSE
		mov rcx,v
    ENDIF
    EXITM<rcx>
endm
CnstStr macro __cnststring
	local adr__cnststring
	.const
		adr__cnststring db __cnststring,0
	.data
	exitm<adr__cnststring>
endm
newdq macro v_,i_
    .data
        v_  dq  0
    .code
    IFNB <i_>
        mov v_,i_
    ENDIF
endm
FP8 macro v_,i_
local r__
    .data
        r__  REAL8 v_
    .code
    EXITM<r__>
endm
FP4 macro v_,i_
local r__
    .data
        r__  REAL4 v_
    .code
    EXITM<r__>
endm
enum MACRO __vargs:VARARG
local val__
    val__=0
    FOR __varg,<__vargs>
        instr_  INSTR <__varg>,<=>
        IF instr_
            catstr_ SUBSTR <__varg>,instr_+1
            val__ =catstr_
            __varg
        else
            __varg EQU val__
        ENDIF
        val__ = val__ +1
    ENDM
ENDM  
	leam macro m1,m2
        lea rax,m2			
		mov m1,rax
	endm
	swapmm macro  m1,m2
	local n
		n equ type( m1)
		IF 		n eq 1
			MOV AL,m2
			MOV BL,m1
			MOV m1,AL
			MOV m2,BL
		ELSEIF 	n eq 2
			MOV AX,m2			
			MOV BX,m1			
			MOV m1,AX
			MOV m2,BX
		ELSEIF 	n eq 4
			MOV EAX,m2			
			MOV EBX,m1			
			MOV m1,EAX
			MOV m2,EBX
		ELSE
			MOV RAX,m2			
			MOV RBX,m1			
			MOV m1,RAX
			MOV m2,RBX
		ENDIF
	endm
	m2m macro m1,m2
	local n
		n equ type( m1)
		IF 		n eq 1
			MOV AL,m2			
			MOV m1,AL
		ELSEIF 	n eq 2
			MOV AX,m2			
			MOV m1,AX
		ELSEIF 	n eq 4
			MOV EAX,m2			
			MOV m1,EAX
		ELSE
			MOV RAX,m2			
			MOV m1,RAX
		ENDIF
	endm
	str2m	macro m,s
	local st_
		.DATA
			st_	db	s,0
		.CODE
		lea rax,st_
		mov m,rax
	endm
	ofs2m	macro m,s
		lea rax,s
		mov m,rax
	endm
	ifn0 macro	_if,_inst
		.if _if
			_inst
		.endif
	endm
    private_allocregs MACRO
        IFNDEF __reg_rax
            .DATA?
              __reg_rax dq ?
              __reg_rbx dq ?
              __reg_rcx dq ?
              __reg_rdx dq ?
              __reg_rsi dq ?
              __reg_rdi dq ?
              __reg_rbp dq ?
              __reg_rsp dq ?
              __reg_r8  dq ?
              __reg_r9  dq ?
              __reg_r10 dq ?
              __reg_r11 dq ?
              __reg_r12 dq ?
              __reg_r13 dq ?
              __reg_r14 dq ?
              __reg_r15 dq ?
            .CODE
        ENDIF
            ENDM

	
    pushaq MACRO
      private_allocregs
      mov __reg_rax, rax
      mov __reg_rbx, rbx
      mov __reg_rcx, rcx
      mov __reg_rdx, rdx
      mov __reg_rsi, rsi
      mov __reg_rdi, rdi
      mov __reg_rbp, rbp
      mov __reg_rsp, rsp
      mov __reg_r8,  r8
      mov __reg_r9,  r9
      mov __reg_r10, r10
      mov __reg_r11, r11
      mov __reg_r12, r12
      mov __reg_r13, r13
      mov __reg_r14, r14
      mov __reg_r15, r15
    ENDM      
    popaq MACRO
      mov rax, __reg_rax
      mov rbx, __reg_rbx
      mov rcx, __reg_rcx
      mov rdx, __reg_rdx
      mov rsi, __reg_rsi
      mov rdi, __reg_rdi
      mov rbp, __reg_rbp
      mov rsp, __reg_rsp
      mov r8,  __reg_r8
      mov r9,  __reg_r9
      mov r10, __reg_r10
      mov r11, __reg_r11
      mov r12, __reg_r12
      mov r13, __reg_r13
      mov r14, __reg_r14
      mov r15, __reg_r15
    ENDM
    
    readentre macro        
        mov rdi,0;stdin
        mov rax,0;sys_read
        ifndef _ch@__
        .data
        	_ch@__	db	0
        .code
        endif
        lea rsi ,_ch@__
        mov rdx,1
        SYSCALL
    endm
	.fequ macro f1,f2
		FINIT                              
		if (type(f1) eq REAL8) or (type(f1) eq REAL4) or (type(f1) eq REAL10)
			FLD     f1      
		else
			FILD     f1      
		endif
		if (type(f2) eq REAL8) or (type(f2) eq REAL4) or (type(f2) eq REAL10)
			FLD     f2      
		else
			FILD     f2     
		endif
		FCOM                               
		FSTSW  ax                          
		and    eax, 0100011100000000B 
		and    eax, 0100000000000000B
;_fpuSetRoundingMode ;truncate ;up
		exitm<EAX>
	endm
	
	.flt macro f1,f2
		FINIT                              
		if (type(f1) eq REAL8) or (type(f1) eq REAL4) or (type(f1) eq REAL10)
			FLD     f2      
		else
			FILD     f2      
		endif
		if (type(f2) eq REAL8) or (type(f2) eq REAL4) or (type(f2) eq REAL10)
			FLD     f1      
		else
			FILD     f1     
		endif
		FCOM                               
		FSTSW  ax                          
		and    eax, 0100011100000000B 
		and    eax, 0000000100000000B
;_fpuSetRoundingMode ;truncate ;up
		exitm<EAX>
	endm
	.fneg macro f1
		exitm<.flt(f1,FP8(0.0)>
	endm
	.fgt macro f1,f2
		xor rax,rax
		FINIT                              
		if (type(f2) eq REAL8) or (type(f2) eq REAL4) or (type(f2) eq REAL10)
			FLD     f2      
		else
			FILD     f2     
		endif
		if (type(f1) eq REAL8) or (type(f1) eq REAL4) or (type(f1) eq REAL10)
			FLD     f1      
		else
			FILD     f1      
		endif
		FCOM                               
		FSTSW  	ax                          
		and    	eax, 0100011100000000B 
;_fpuSetRoundingMode ;truncate ;up

		exitm<eax==0>
	endm
; ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

  ; ********************************************************
  ; format a C style string complete with escape characters
  ; and return the offset of the result to the calling macro
  ;
  ; 3 versions are presented here,
  ; 1. acfm$ = ASCII only version
  ; 2. ucfm$ = UNICODE only version
  ; 3. cfm$  = Either ASCII or UNICODE depending on the
  ;    __UNICODE__ equate being present in the source file
  ;
  ; This allows you to force either ASCII, UNICODE or either
  ; depending on the presence of the __UNICODE__ equate
  ; ********************************************************

  ; ********************************************************
  ;   branchless ASCII version of cfm$ with no ELSE clauses.
  ; ********************************************************

    acfm$ MACRO txt:VARARG

      LOCAL ch1,char,nu$,tmp,flag,lbuf,rbuf,cpos,sln
      ch1 equ <>
      nu$ equ <>
      flag = 0

      ch1 SUBSTR <txt>,1,1              ;; check if 1st character is a quote
      IFDIF ch1,<">
        EXITM <txt>                     ;; exit with original "txt" if it is not
      ENDIF

      FORC char,<txt>                   ;; scan through characters in "txt"

        IFIDN <char>,<\>                ;; increment the flag if "\" escape character
          flag = flag + 1
        ENDIF

      ; -----------------------------------------------

        IF flag EQ 0                    ;; <<< if flag = 0 then normal APPEND character
          nu$ CATSTR nu$,<char>
        ENDIF

        IF flag EQ 1                    ;; <<< if flag = 1 then perform replacement
          IFIDN <char>,<n>
            nu$ CATSTR nu$,<",13,10,">  ;; \n = CRLF
            flag = 0
          ENDIF
          IFIDN <char>,<t>
            nu$ CATSTR nu$,<",9,">      ;; \t = TAB
            flag = 0
          ENDIF
          IFIDN <char>,<q>
            nu$ CATSTR nu$,<",34,">     ;; \q = quote
            flag = 0
          ENDIF
          IFIDN <char>,<0>
            nu$ CATSTR nu$,<",0,">      ;; \0 = embedded zero
            flag = 0
          ENDIF

       ;; ---------------------
       ;; masm specific escapes
       ;; ---------------------
          IFIDN <char>,<l>
            nu$ CATSTR nu$,<",60,">     ;; \l = <
            flag = 0
          ENDIF
          IFIDN <char>,<r>
            nu$ CATSTR nu$,<",62,">     ;; \r = >
            flag = 0
          ENDIF
          IFIDN <char>,<x>
            nu$ CATSTR nu$,<",33,">     ;; \x = !
            flag = 0
          ENDIF
          IFIDN <char>,<a>
            nu$ CATSTR nu$,<",40,">     ;; \a = (
            flag = 0
          ENDIF
          IFIDN <char>,<b>
            nu$ CATSTR nu$,<",41,">     ;; \b = )
            flag = 0
          ENDIF
        ENDIF

        IF flag EQ 2                    ;; <<< if flag = 2 APPEND the "\" character
          IFIDN <char>,<\>
            nu$ CATSTR nu$,<",92,">     ;; \\ = \
            flag = 0
          ENDIF
        ENDIF

      ; -----------------------------------------------

      ENDM

    ;; ---------------------------------------------
    ;; strip any embedded <"",> characters sequences
    ;; ---------------------------------------------
        nu$ CATSTR nu$,<,0,0,0>                 ;; append trailing zeros

        cpos INSTR nu$,<"",>                    ;; test for leading junk
        IF cpos EQ 1
          nu$ SUBSTR nu$,4                      ;; chomp off any leading junk
        ENDIF

        cpos INSTR nu$,<"",>

        WHILE cpos
          lbuf SUBSTR nu$,1,cpos-1              ;; read text before junk
          rbuf SUBSTR nu$,cpos+3                ;; read text after junk
          nu$ equ <>                            ;; clear nu$
          nu$ CATSTR lbuf,rbuf                  ;; concantenate the two
          cpos INSTR nu$,<"",>                  ;; reload cpos for next iteration
        ENDM

        sln SIZESTR nu$
        nu$ SUBSTR nu$,1,sln-6                  ;; trim off tail padding

        .data
          tmp db nu$,0
          align 4
        .code
        EXITM <OFFSET tmp>                      ;; return the DATA section OFFSET

    ENDM
	return macro	__r
		MOV RAX,__r
		RET
	endm
Private_getdecvarname MACRO __varg
	local val__
	instr_  INSTR <__varg>,<:>
	IF instr_
	    	val__ SUBSTR <__varg>,1,instr_-1
	    	exitm<val__>
	else
	    	exitm<__varg>
	ENDIF
ENDM

.sub MACRO procName,__Args:VARARG
	lastprocedureName EQU <procName>
	lastprocedureArgs__ =0
	IFB <__Args>
		.code
		procName PROC 
	ELSE
		strArgs equ <>
		j___=1
		FOR __varg,<__Args>
			IF j___ GE 7 
				strArgs CATSTR strArgs,<,__varg>
			ELSE
				strArgs CATSTR strArgs,<,@&__varg>
				j___=j___+1
			ENDIF
			lastprocedureArgs__=lastprocedureArgs__+1
		ENDM
		.code
		procName PROC strArgs	
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
.home macro
	n=0
	repeat  lastprocedureArgs__
		n=n+1
		IF n LT 7
	%	mov @CatStr(<__@SubArg>,%n), @&@CatStr(<__@SubArg>,%n)
		ENDIF
	endm

endm
.endsub macro
		RET
	 lastprocedureName ENDP
endm	


	pushrax macro
		private_allocregs
		mov __reg_rax, rax
	endm
	poprax macro
		private_allocregs
		mov rax,__reg_rax
	endm
	pushrbx macro
		private_allocregs
		mov __reg_rbx, rbx
	endm
	poprbx macro
		private_allocregs
		mov rbx,__reg_rbx
	endm
	pushrcx macro
		private_allocregs
		mov __reg_rcx, rcx
	endm
	poprcx macro
		private_allocregs
		mov rcx,__reg_rcx
	endm
	pushrdx macro
		private_allocregs
		mov __reg_rdx, rdx
	endm
	poprdx macro
		private_allocregs
		mov rdx,__reg_rdx
	endm
	pushrsi macro
		private_allocregs
		mov __reg_rsi, rsi
	endm
	poprsi macro
		private_allocregs
		mov rsi,__reg_rsi
	endm
	pushrdi macro
		private_allocregs
		mov __reg_rdi, rdi
	endm
	poprdi macro
		private_allocregs
		mov rdi,__reg_rdi
	endm
	pushrbp macro
		private_allocregs
		mov __reg_rbp, rbp
	endm
	poprbp macro
		private_allocregs
		mov rbp,__reg_rbp
	endm
	pushrsp macro
		private_allocregs
		mov __reg_rsp, rsp
	endm
	poprsp macro
		private_allocregs
		mov rsp,__reg_rsp
	endm
	pushr8 macro
		private_allocregs
		mov __reg_r8, r8
	endm
	popr8 macro
		private_allocregs
		mov r8,__reg_r8
	endm
	pushr9 macro
		private_allocregs
		mov __reg_r9, r9
	endm
	popr9 macro
		private_allocregs
		mov r9,__reg_r9
	endm
	pushr10 macro
		private_allocregs
		mov __reg_r10, r10
	endm
	popr10 macro
		private_allocregs
		mov r10,__reg_r10
	endm
	pushr11 macro
		private_allocregs
		mov __reg_r11, r11
	endm
	popr11 macro
		private_allocregs
		mov r11,__reg_r11
	endm
	pushr12 macro
		private_allocregs
		mov __reg_r12, r12
	endm
	popr12 macro
		private_allocregs
		mov r12,__reg_r12
	endm
	pushr13 macro
		private_allocregs
		mov __reg_r13, r13
	endm
	popr13 macro
		private_allocregs
		mov r13,__reg_r13
	endm
	pushr14 macro
		private_allocregs
		mov __reg_r14, r14
	endm
	popr14 macro
		private_allocregs
		mov r14,__reg_r14
	endm
	pushr15 macro
		private_allocregs
		mov __reg_r15, r15
	endm
	popr15 macro
		private_allocregs
		mov r15,__reg_r15
	endm

