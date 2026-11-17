; see http://sourceforge.net/projects/libb64
IFNDEF  __BASE64___
	__BASE64___ EQU 1
	include macros.inc
	
	enum step_A, step_B, step_C				;base64_encodestep
	enum step_a, step_b, step_c, step_d		;base64_decodestep
	base64_encodestate STRUCT
		step		DD	0
		result		DD	0
		stepcount	DD	0
	base64_encodestate ENDS
	base64_decodestate	STRUCT
		step		DD	0
		plainchar	DD	0
	base64_decodestate 	ENDS

	base64_init_encodestate		PROTO :VARARG	;;void base64_init_encodestate(base64_encodestate* state_in);
	base64_encode_value			PROTO :VARARG	;;char base64_encode_value(char value_in);
	base64_encode_block			PROTO :VARARG	;;int base64_encode_block(const char* plaintext_in, int length_in, char* code_out, base64_encodestate* state_in);
	base64_encode_blockend		PROTO :VARARG	;;int base64_encode_blockend(char* code_out, base64_encodestate* state_in);

	base64_init_decodestate		PROTO :VARARG	;void base64_init_decodestate(base64_decodestate* state_in);
	base64_decode_value			PROTO :VARARG	;int base64_decode_value(char value_in);
	base64_decode_block			PROTO :VARARG	;int base64_decode_block(const char* code_in, const int length_in, char* plaintext_out, base64_decodestate* state_in);

	.CODE
	strlen proc lpSource:qword

		xor		rax,rax
		dec		rax
		mov		rsi,lpSource
	  @@:
		inc		rax
		cmp		byte ptr [rsi+rax],0
		jne		@b
		ret

	strlen endp
	
	.data
		d64buf	db	4096	dup(0)
		d64buf2	db	4096	dup(0)
	.sub b64encode, _output:QWORD, _input:QWORD
		local __cnt
		local __s:base64_encodestate
		local slen:qword
	.home
		base64_init_encodestate(addr __s)
		strlen(_input)
		mov slen,rax
		
		base64_encode_block(_input,slen, _output, ADDR __s);
		MOV __cnt,EAX
		XOR RAX,RAX
		MOV EAX,__cnt
		ADD RAX,_output
		MOV _output,RAX
		;printf("base64_encode_block __cnt: %d\n", __cnt)
		base64_encode_blockend(_output, ADDR __s)
		MOV __cnt,EAX
		XOR RAX,RAX
		MOV EAX,__cnt
		ADD RAX,_output
		MOV WORD PTR [RAX],0
		mov rax,_output
	.endsub
	
	.sub b64decode, _output:QWORD, _input:QWORD
		local __cnt
		local __s:base64_decodestate
		local slen:qword
	.home
		base64_init_decodestate(addr __s)
		strlen(_input)
		mov slen,rax
		base64_decode_block(_input, slen, _output, ADDR __s);
		MOV __cnt,EAX
		XOR RAX,RAX
		MOV EAX,__cnt
		ADD RAX,_output
		MOV WORD PTR [RAX],0
		mov rax,_output
	.endsub
	
ENDIF

