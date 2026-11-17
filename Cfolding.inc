.data
	folding_tmp___xml_tag 	db 	256	dup(0)
.code
	;	For C and C++
	.proc SlashAsterisk ,   _str:qword  
	.shadow
		mov rax,_str
		.if byte ptr [rax] == "/" && byte ptr [rax+1] == "*"  
			add rax,2
			@@:
				.if  byte ptr [rax] == 0ah || byte ptr [rax] == 0dh || byte ptr [rax] == 0 
					xor rax , rax
					ret
				.endif
				.if byte ptr [rax] == "*" && byte ptr [rax+1] == "/"  
					add rax,2
					ret
				.endif
				inc rax
				jmp @B
		.endif	
		ret
	.endp
	.proc SingleQuote ,   _str:qword 
	.shadow 
		mov rax,_str
		.if byte ptr [rax] == "'"  
			inc rax
			@@:
				.if  byte ptr [rax] == 0ah || byte ptr [rax] == 0dh || byte ptr [rax] == 0 
					xor rax , rax
					ret
				.endif
				.if byte ptr [rax] == "'"  
					inc rax
					ret
				.endif
				inc rax
				jmp @B
		.endif
	.endp
	.proc DoubleQuote ,   _str:qword  
	.shadow
		mov rax,_str
		.if byte ptr [rax] == '"'  
			inc rax
			@@:
				.if  byte ptr [rax] == 0ah || byte ptr [rax] == 0dh || byte ptr [rax] == 0 
					xor rax , rax
					ret
				.endif
				.if byte ptr [rax] == '"'  
					inc rax
					ret
				.endif
				inc rax
				jmp @B
		.endif
	.endp
	.proc folding_Left_Curly_Bracket_Exist ,  _str:qword 
	.shadow 		    
		mov rax,_str
		folding_Left_Curly_Bracket_Exist_Start:
		@@:
			.if  byte ptr [rax] == 0ah || byte ptr [rax] == 0dh || byte ptr [rax] == 0  
				xor rax , rax
				ret
			.endif
			.if byte ptr [rax] == "/" && byte ptr [rax+1] == "/"   
				xor rax , rax
				ret
			.endif
			.if byte ptr [rax] == "/" && byte ptr [rax+1] == "*"
				.if rv(SlashAsterisk,rax)==0
					ret
				.else
					jmp @B
				.endif
			.endif
			.if byte ptr [rax] == '"'
				.if rv(DoubleQuote,rax)==0
					ret
				.else
					jmp @B
				.endif
			.endif
			.if byte ptr [rax] == "'"
				.if rv(SingleQuote,rax)==0
					ret
				.else
					jmp @B
				.endif
			.endif
			.if byte ptr [rax] == "{" 
				inc rax
				jmp @F				
			.endif
			inc rax
			jmp @B

		@@:		
			.if  byte ptr [rax] == 0ah || byte ptr [rax] == 0dh || byte ptr [rax] == 0  
				mov rax,TRUE
				ret
			.endif
			.if byte ptr [rax] == "/" && byte ptr [rax+1] == "/"   
				mov rax,TRUE
				ret
			.endif
			.if byte ptr [rax] == "/" && byte ptr [rax+1] == "*"
				.if rv(SlashAsterisk,rax)==0
					mov rax,TRUE
					ret
				.else
					jmp @B
				.endif
			.endif
			.if byte ptr [rax] == '"'
				.if rv(DoubleQuote,rax)==0
					mov rax,TRUE
					ret
				.else
					jmp @B
				.endif
			.endif
			.if byte ptr [rax] == "'"
				.if rv(SingleQuote,rax)==0
					mov rax,TRUE
					ret
				.else
					jmp @B
				.endif
			.endif
			.if byte ptr [rax] == "}" 
				inc rax
				jmp folding_Left_Curly_Bracket_Exist_Start			
			.endif
			.if byte ptr [rax] == "{" 
				;inc rax
				.if rv(folding_Left_Curly_Bracket_Exist,rax)
					ret
				.endif
				jmp @B
			.endif		
			inc rax
			jmp @B			
	.endp
	.proc folding_Right_Curly_Bracket_Exist,  _str:qword  
	.shadow
		mov rax,_str
		folding_Right_Curly_Bracket_Exist_Start:
		@@:
			.if  byte ptr [rax] == 0ah || byte ptr [rax] == 0dh || byte ptr [rax] == 0  || byte ptr [rax] == "/" && byte ptr [rax+1] == "/"   
				xor rax , rax
				ret
			.endif
			.if byte ptr [rax] == "/" && byte ptr [rax+1] == "*"
				.if rv(SlashAsterisk,rax)==0
					ret
				.else
					jmp @B
				.endif
			.endif
			.if byte ptr [rax] == '"'
				.if rv(DoubleQuote,rax)==0
					ret
				.else
					jmp @B
				.endif
			.endif
			.if byte ptr [rax] == "'"
				.if rv(SingleQuote,rax)==0
					ret
				.else
					jmp @B
				.endif
			.endif
			.if byte ptr [rax] == "{" 
				;inc rax
				.if rv(folding_Left_Curly_Bracket_Exist,rax)
					xor rax,rax
					ret
				.endif
				jmp @B
			.endif
			.if byte ptr [rax] == "}" 
				mov rax,TRUE
				ret
			.endif
			inc rax
			jmp @B
	.endp
	.proc folding_xml_Get_Start_Tag ,  _str:qword 
	.shadow
		mov rax,_str
		lea rsi,	folding_tmp___xml_tag
		mov byte ptr [rsi],0
		.if  byte ptr [rax] == 0ah || byte ptr [rax] == 0dh || byte ptr [rax] == 0 
			xor rax,rax
		.else
	  	@@:
			.if  byte ptr [rax] == 0ah || byte ptr [rax] == 0dh || byte ptr [rax] == 0 
				jmp folding_xml_Get_Start_Tag_ret
			.endif
			.if  byte ptr [rax] == ">" || byte ptr [rax] == "<" || byte ptr [rax] == "\"
				jmp folding_xml_Get_Start_Tag_ret
			.endif
			.if byte ptr [rax] == "-" || byte ptr [rax+1] == "+" || byte ptr [rax+2] == "="  || \
				byte ptr [rax] == "*" || byte ptr [rax+1] == "!" || byte ptr [rax+2] == "$"  || \
				byte ptr [rax] == "%" || byte ptr [rax+1] == "^" || byte ptr [rax+2] == "&"  || \
				byte ptr [rax] == "(" || byte ptr [rax+1] == ")" || byte ptr [rax+2] == "?"  || \
				byte ptr [rax] == ";" || byte ptr [rax+1] == "," ;|| byte ptr [rax+2] == "/"   
				xor rax , rax 			
				ret
			.endif
			;.if  byte ptr [rax] == "<"  
			;	.if rv(folding_xml_Comment,rax)==0
			;		jmp @B
			;	.endif
			;.endif
			mov cl ,byte ptr [rax]
			mov byte ptr [rsi],cl
			inc rsi
			inc rax
			jmp @B
		.endif
	 folding_xml_Get_Start_Tag_ret:
		mov byte ptr [rsi],0
	  	lea rax,folding_tmp___xml_tag
	.endp	
	.proc folding_xml_Get_Close_Tag ,  _str:qword  
	.shadow
		mov rax,_str
		lea rsi,	folding_tmp___xml_tag
		mov byte ptr [rsi],0
		.if  byte ptr [rax] == 0ah || byte ptr [rax] == 0dh || byte ptr [rax] == 0 
			xor rax,rax
		.else
	  	@@:
			.if  byte ptr [rax] == 0ah || byte ptr [rax] == 0dh || byte ptr [rax] == 0 
				jmp folding_xml_Get_Close_Tag_ret
			.endif
			.if  byte ptr [rax] == ">" || byte ptr [rax] == "<" || byte ptr [rax] == "\"
				jmp folding_xml_Get_Close_Tag_ret
			.endif
			.if byte ptr [rax] == "-" || byte ptr [rax+1] == "+" || byte ptr [rax+2] == "="  || \
				byte ptr [rax] == "*" || byte ptr [rax+1] == "!" || byte ptr [rax+2] == "$"  || \
				byte ptr [rax] == "%" || byte ptr [rax+1] == "^" || byte ptr [rax+2] == "&"  || \
				byte ptr [rax] == "(" || byte ptr [rax+1] == ")" || byte ptr [rax+2] == "?"  || \
				byte ptr [rax] == ";" || byte ptr [rax+1] == "," ;|| byte ptr [rax+2] == "/"   
				xor rax , rax 			
				ret
			.endif
			;.if  byte ptr [rax] == "<"  
			;	.if rv(folding_xml_Comment,rax)==0
			;		jmp @B
			;	.endif
			;.endif
			mov cl ,byte ptr [rax]
			mov byte ptr [rsi],cl
			inc rsi
			inc rax
			jmp @B
		.endif
	 folding_xml_Get_Close_Tag_ret:
		mov byte ptr [rsi],0
	  	lea rax,folding_tmp___xml_tag
	.endp	
	.proc folding_xml_Comment ,  _str:qword  ; greater
	.shadow
		mov rax,_str
		@@:
		.if  byte ptr [rax] == "<" && byte ptr [rax+1] == 021H  && byte ptr [rax+2] == "-" && byte ptr [rax+3] == "-"  ; <!--
			add rax , 4
			@@:
				.if  byte ptr [rax] == 0ah || byte ptr [rax] == 0dh || byte ptr [rax] == 0 
					xor rax , rax
					ret
				.endif
				.if  byte ptr [rax] == "-" && byte ptr [rax+1] == "-" && byte ptr [rax+2] == ">"  ; <!--
					add rax , 3			
					ret
				.endif
				inc rax
				jmp @B
		.endif
	.endp	
	.proc folding_xml_Tag 	,  _str:qword  
	.shadow
		mov rax,_str
		@@:
			.if  byte ptr [rax] == 09h || byte ptr [rax] == " "  
				inc	rax
				jmp @B
			.endif
			.if  byte ptr [rax] == "<"  
				.if rv(folding_xml_Comment,rax)==0
					jmp @B
				.endif
				.if rv(folding_xml_Get_Start_Tag,rax)==0
					ret
				.endif
			.endif
			xor rax,rax
			ret
	.endp