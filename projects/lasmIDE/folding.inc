CAIRO_FORMAT_ARGB32    = 0

  .data
    __rcol  REAL8    1.0
    __rcolC REAL8    0.0
    
.code
get_fold_minus_pixbuf PROC
local lsurface:gpointer
local lcr:gpointer
local __w
local __h
local _w2:REAL8
local _h2:REAL8

    mov __w, 24
    mov __h, 24
    mov lsurface,rv(cairo_image_surface_create,CAIRO_FORMAT_ARGB32,__w,__h)
    mov lcr,rv(cairo_create,lsurface) 
    invoke cairo_set_source_rgb,lcr,__rcol,__rcolC,__rcol
        fild __w
        fsub FP8(8.0)
        fstp _w2
        fild __h
        fsub FP8(8.0)
        fstp _h2   
    invoke cairo_rectangle,lcr, FP8(4.0),FP8(4.0),_w2,_h2
   ; invoke cairo_fill,lcr
    
  ;  invoke cairo_set_source_rgb,lcr,__rcolC,__rcolC,__rcolC
        finit
        fild __w
        fdiv FP8(5.0) 
        fstp _w2
        fild __h
        fdiv FP8(2.0) 
        fstp _h2
    invoke cairo_move_to ,lcr,_w2,_h2
        fild __w
        fmul FP8(0.8) 
        fstp _w2
    invoke cairo_line_to ,lcr,_w2,_h2
    invoke cairo_stroke,lcr
                 
    invoke gdk_pixbuf_get_from_surface,lsurface,0,0,__w,__h
    
     RET
get_fold_minus_pixbuf ENDP


get_fold_plus_pixbuf PROC
local lsurface:gpointer
local __w
local __h
local _w2:REAL8
local _h2:REAL8
local lcr:gpointer

    mov __w, 24
    mov __h, 24
    mov lsurface,rv(cairo_image_surface_create,CAIRO_FORMAT_ARGB32,__w,__h)
    mov lcr,rv(cairo_create,lsurface) 
    invoke cairo_set_source_rgb,lcr ,__rcol,__rcolC,__rcol
        fild __w
        fsub FP8(8.0)
        fstp _w2
        fild __h
        fsub FP8(8.0)
        fstp _h2   
    invoke cairo_rectangle,lcr, FP8(4.0),FP8(4.0),_w2,_h2
   ; invoke cairo_fill,lcr
    
  ;  invoke cairo_set_source_rgb,lcr,__rcolC,__rcolC,__rcolC;
        finit
        fild __w
        fdiv FP8(5.0) 
        fstp _w2
        fild __h
        fdiv FP8(2.0) 
        fstp _h2
    invoke cairo_move_to ,lcr,_w2,_h2
        fild __w
        fmul FP8(0.8) 
        fstp _w2
    invoke cairo_line_to ,lcr,_w2,_h2
    invoke cairo_stroke,lcr

        finit
        fild __w
        fdiv FP8(2.0) 
        fstp _w2
        fild __h
        fdiv FP8(5.0) 
        fstp _h2
    invoke cairo_move_to ,lcr,_w2,_h2
        fild __h
        fmul FP8(0.8) 
        fstp _h2
    invoke cairo_line_to ,lcr,_w2,_h2
    invoke cairo_stroke,lcr
                                  
    invoke gdk_pixbuf_get_from_surface,lsurface,0,0,__w,__h
    
     RET

get_fold_plus_pixbuf ENDP


get_fold_vert_pixbuf PROC
local lsurface:gpointer
local __w
local __h
local _w2:REAL8
local lcr:gpointer
local _h2:REAL8
    mov __w, 24
    mov __h, 24
    mov lsurface,rv(cairo_image_surface_create,CAIRO_FORMAT_ARGB32,__w,__h)
    mov lcr,rv(cairo_create,lsurface) 
    invoke cairo_set_source_rgb,lcr,__rcol,__rcolC,__rcol    
        finit
        fild __w
        fdiv FP8(2.0) 
        fstp _w2
        fild __h
        fstp _h2
    invoke cairo_move_to ,lcr,_w2,FP8(0.0);__rcolC
    invoke cairo_line_to ,lcr,_w2,_h2
    invoke cairo_stroke,lcr                              
    invoke gdk_pixbuf_get_from_surface,lsurface,0,0,__w,__h
     RET
get_fold_vert_pixbuf ENDP


get_fold_end_pixbuf PROC
local lsurface:gpointer
local __w
local __h
local _w2:REAL8
local lcr:gpointer
local _h2:REAL8
    mov __w, 24
    mov __h, 24
    mov lsurface,rv(cairo_image_surface_create,CAIRO_FORMAT_ARGB32,__w,__h)
    mov lcr,rv(cairo_create,lsurface) 
    invoke cairo_set_source_rgb,lcr,__rcol,__rcolC,__rcol 
        finit
        fild __w
        fdiv FP8(2.0) 
        fstp _w2
    invoke cairo_move_to ,lcr,_w2,__rcolC
        fild __w
        fdiv FP8(2.0) 
        fstp _w2
        fild __h
        fdiv FP8(2.0) 
        fstp _h2
    invoke cairo_line_to ,lcr,_w2,_h2
        fild __w
        fstp _w2
    invoke cairo_line_to ,lcr,_w2,_h2
    invoke cairo_stroke,lcr     
    invoke gdk_pixbuf_get_from_surface,lsurface,0,0,__w,__h
     RET
get_fold_end_pixbuf ENDP


place_mark PROC tbuf:gpointer,ln:guint,Nmark:gint
local ltb:gpointer
local lln:gint
local lNmark:gint
local __iter:GtkTextIter

    mov ltb,tbuf
    mov lln,ln
    mov lNmark,Nmark
    invoke gtk_text_buffer_get_iter_at_line,ltb,addr __iter,lln
    .if lNmark == fold_plus
        invoke gtk_source_buffer_create_source_mark,ltb,0,"+",addr __iter
        invoke gtk_text_mark_set_visible,rax,TRUE
    .elseif lNmark == fold_minus
        invoke gtk_source_buffer_create_source_mark,ltb,0,"-",addr __iter
		invoke gtk_text_mark_set_visible,rax,TRUE
    .elseif lNmark == fold_vert
        invoke gtk_source_buffer_create_source_mark,ltb,0,"|",addr __iter
		invoke gtk_text_mark_set_visible,rax,TRUE
    .elseif lNmark == fold_end
        invoke gtk_source_buffer_create_source_mark,ltb,0,".",addr __iter
		invoke gtk_text_mark_set_visible,rax,TRUE
    .endif
    RET
place_mark ENDP
Notebook_Get_Current_Viewer proto
Notebook_Get_Viewer_From_Buffer proto :gpointer
	place_mark_S PROC tbuf:gpointer,ln:guint,S_mark:gpointer,Nmark:gint
		local ltb:gpointer
		local lv:gpointer
		local lln:gint
		local lNmark:gint
		local l_S_mark:gpointer
		local __iter:GtkTextIter
		local priority:gint
		mov ltb,tbuf
		mov lln,ln
		mov l_S_mark,S_mark
    		mov lNmark,Nmark
		mov priority,-1
		mov lv,rv(Notebook_Get_Current_Viewer)
		.if rv( gtk_source_view_get_mark_attributes,lv,l_S_mark,0)==0
			.if folding_Attribute_Plus==0
				call Folding_Set_Attributes
			.endif
			.if lNmark == fold_plus
				invoke gtk_source_view_set_mark_attributes,lv,l_S_mark,folding_Attribute_Plus,0
			.elseif lNmark == fold_minus
				invoke gtk_source_view_set_mark_attributes,lv,l_S_mark,folding_Attribute_Minus,0
			.elseif lNmark == fold_vert
				invoke gtk_source_view_set_mark_attributes,lv,l_S_mark,folding_Attribute_Vert,0
			.elseif lNmark == fold_end
				invoke gtk_source_view_set_mark_attributes,lv,l_S_mark,folding_Attribute_End,0
			.endif
		.endif

		invoke gtk_text_buffer_get_iter_at_line,ltb,addr __iter,lln
		invoke gtk_source_buffer_create_source_mark,ltb,0,l_S_mark,addr __iter
		invoke gtk_text_mark_set_visible,rax,TRUE
	    RET
	place_mark_S ENDP
.data
	folding_Attribute_Plus	gpointer	0
	folding_Attribute_Minus	gpointer	0
	folding_Attribute_End	gpointer	0
	folding_Attribute_Vert	gpointer	0
.code
Folding_Set_Attributes proc
    local lpixbuf:gpointer
    mov lpixbuf     ,rv(get_fold_plus_pixbuf)
    mov folding_Attribute_Plus  ,rv(gtk_source_mark_attributes_new)
    invoke gtk_source_mark_attributes_set_pixbuf,folding_Attribute_Plus,lpixbuf

    mov lpixbuf     ,rv(get_fold_minus_pixbuf)
    mov folding_Attribute_Minus  ,rv(gtk_source_mark_attributes_new)
    invoke gtk_source_mark_attributes_set_pixbuf,folding_Attribute_Minus,lpixbuf
  
    mov lpixbuf     ,rv(get_fold_end_pixbuf)
    mov folding_Attribute_End  ,rv(gtk_source_mark_attributes_new)
    invoke gtk_source_mark_attributes_set_pixbuf,folding_Attribute_End,lpixbuf

    mov lpixbuf     ,rv(get_fold_vert_pixbuf)
    mov folding_Attribute_Vert  ,rv(gtk_source_mark_attributes_new)
    invoke gtk_source_mark_attributes_set_pixbuf,folding_Attribute_Vert,lpixbuf

	ret
Folding_Set_Attributes endp
create_marks proc v:gpointer
    local lpixbuf:gpointer
    local lmark_attr:gpointer
    local lv:gpointer
    
    mov lv,v
    call Folding_Set_Attributes

    invoke gtk_source_view_set_mark_attributes,lv,"+",folding_Attribute_Plus,0
    invoke gtk_source_view_set_mark_attributes,lv,"-",folding_Attribute_Minus,0
    invoke gtk_source_view_set_mark_attributes,lv,".",folding_Attribute_End,0
    invoke gtk_source_view_set_mark_attributes,lv,"|",folding_Attribute_Vert,0
   
    ret
create_marks endp   

fold_plus   equ 0
fold_minus  equ 1
fold_vert   equ 2
fold_end    equ 3


on_line_mark_activated proc uses r12 view:gpointer,iter:gpointer,event:gpointer,user_data:gpointer
	local ln:guint
	local liter:gpointer
	local luter:gpointer
	local lDuterP:gpointer
	local lDuterM:gpointer
	local startiter:_GtkTextIter
	local lbuffer:gpointer
	local enditer:_GtkTextIter
	local ln1:guint
	local viewer:gpointer
	local plus:gpointer
	local ln_end:guint
	local marksSList:gpointer
	local __CatdStr:gpointer
	local __EndStr:gpointer
	local __DubStr:gpointer

	mov viewer,view
	mov lbuffer,user_data
	mov liter,iter
	mov luter,rv(gtk_text_iter_copy,liter)
	mov lDuterP,rv(gtk_text_iter_copy,liter)
	mov lDuterM,rv(gtk_text_iter_copy,liter)
	invoke gtk_text_iter_get_line,liter
	mov ln,eax
	mov ln1,eax
	mov marksSList,rv( gtk_source_buffer_get_source_marks_at_iter,lbuffer,liter,0)
	.if marksSList
		mov __CatdStr,rv(g_strdup,rv( gtk_source_mark_get_category,[rax]))
		.if byte ptr [rax] == "-"
			inc __CatdStr
	 		mov __EndStr,rv(g_strconcat,str$("."),__CatdStr,0)
			invoke gtk_source_buffer_remove_source_marks,lbuffer,liter,liter,0
			invoke gtk_source_buffer_forward_iter_to_source_mark,lbuffer,luter,__EndStr
	 			mov __DubStr,rv(g_strconcat,str$("+"),__CatdStr,0)
	 			@@:
		 		.if rv( gtk_source_buffer_forward_iter_to_source_mark,lbuffer,lDuterP,__DubStr)
		 			.if rv(gtk_text_iter_compare,luter,lDuterP)==1
	 			 		invoke gtk_source_buffer_forward_iter_to_source_mark,lbuffer,luter,__EndStr
	 			 		jmp @B
	 			 	.endif
				.endif
				invoke g_free ,__DubStr			
				mov __DubStr,rv(g_strconcat,str$("-"),__CatdStr,0)
				@@:
		 		.if rv( gtk_source_buffer_forward_iter_to_source_mark,lbuffer,lDuterM,__DubStr)
		 			.if rv(gtk_text_iter_compare,luter,lDuterM)==1
	 			 		invoke gtk_source_buffer_forward_iter_to_source_mark,lbuffer,luter,__EndStr
	 			 		jmp @B
	 			 	.endif
				.endif
				invoke g_free ,__DubStr			
				invoke gtk_text_iter_get_line,luter
				mov ln_end,eax
				inc ln
				inc ln_end
				invoke gtk_text_buffer_get_iter_at_line,lbuffer,addr startiter,ln
				invoke gtk_text_buffer_get_iter_at_line,lbuffer,addr enditer,ln_end
				invoke gtk_text_buffer_apply_tag_by_name,lbuffer,"invisible",addr startiter,addr enditer
				invoke g_free ,__EndStr
		 		mov __EndStr,rv(g_strconcat,str$("+"),__CatdStr,0,0,0,0,0)
				place_mark_S(lbuffer,ln1,__EndStr,fold_plus)
		 	invoke g_free ,__EndStr		
			

		.elseif byte ptr [rax] == "+"
			inc __CatdStr
	 		mov __EndStr,rv(g_strconcat,str$("."),__CatdStr,0,0,0,0,0)
			invoke gtk_source_buffer_remove_source_marks,lbuffer,liter,liter,0
			invoke gtk_source_buffer_forward_iter_to_source_mark,lbuffer,luter,__EndStr
	 			mov __DubStr,rv(g_strconcat,str$("-"),__CatdStr,0)
	 			@@:
		 		.if rv( gtk_source_buffer_forward_iter_to_source_mark,lbuffer,lDuterP,__DubStr)
		 			.if rv(gtk_text_iter_compare,luter,lDuterP)==1
	 			 		invoke gtk_source_buffer_forward_iter_to_source_mark,lbuffer,luter,__EndStr
	 			 		jmp @B
	 			 	.endif
				.endif
				invoke g_free ,__DubStr			
				mov __DubStr,rv(g_strconcat,str$("+"),__CatdStr,0)
				@@:
		 		.if rv( gtk_source_buffer_forward_iter_to_source_mark,lbuffer,lDuterM,__DubStr)
		 			.if rv(gtk_text_iter_compare,luter,lDuterM)==1
	 			 		invoke gtk_source_buffer_forward_iter_to_source_mark,lbuffer,luter,__EndStr
	 			 		jmp @B
	 			 	.endif
				.endif
				invoke g_free ,__DubStr			
				invoke gtk_text_iter_get_line,luter
				mov ln_end,eax
				inc ln
				inc ln_end

				invoke gtk_text_buffer_get_iter_at_line,lbuffer,addr startiter,ln
				invoke gtk_text_buffer_get_iter_at_line,lbuffer,addr enditer,ln_end
				invoke gtk_text_buffer_remove_tag_by_name,lbuffer,"invisible",addr startiter,addr enditer 		
				invoke g_free ,__EndStr
		 		mov __EndStr,rv(g_strconcat,str$("-"),__CatdStr,0,0,0,0,0)
				place_mark_S(lbuffer,ln1,__EndStr,fold_minus)
			invoke g_free ,__EndStr
			
		.elseif byte ptr [rax] == "|"
	;			invoke printf,str$(<"on_line_mark_activated line={%d,,%s}",10>),ln,[rax]
		.elseif byte ptr [rax] == "."
	;			invoke printf,str$(<"on_line_mark_activated line={%d,end,%s}",10>),ln,[rax]
		.endif

    	.endif
    	dec __CatdStr
	invoke g_free ,__CatdStr
	g_slist_free proto :gpointer
	g_slist_free(marksSList)
	gtk_text_iter_free(luter)
	gtk_text_iter_free(lDuterP)
	gtk_text_iter_free(lDuterM)

    ret
on_line_mark_activated endp


.data
	folding_tmp___first_word 		db 	128	dup(0)
	folding_tmp___second_word 	db 	128	dup(0)
.code
folding_get_first_and_second_word PROC  _str:qword  
        local l_str:gpointer
        
	mov rcx,_str
	lea rsi,folding_tmp___first_word
	mov byte ptr [rsi],0
	lea rsi,folding_tmp___second_word
	mov byte ptr [rsi],0
	.if byte ptr [rcx] == 0ah
		ret
	.endif
	.if byte ptr [rcx] == ";" 
		lea rsi,folding_tmp___first_word
		mov rax,rsi
		@@:
			.if byte ptr [rcx] == 0  
				mov byte ptr [rsi],0
				ret
			.endif
			.if  byte ptr [rcx] == 0ah || byte ptr [rcx] == " " || byte ptr [rcx] == 09h
				mov byte ptr [rsi],0
				lea rsi,folding_tmp___second_word
				jmp @F
			.endif
			mov r9b,byte ptr [rcx]
			mov byte ptr [rsi],r9b
			inc rsi
			inc rcx
			jmp @B
		ret
	.endif
	
	@@:
		.if byte ptr [rcx] == 0 || byte ptr [rcx] == ";" || byte ptr [rcx] == "'"  || byte ptr [rcx] == '"'
			ret
		.endif
		.if byte ptr [rcx] == 0ah || byte ptr [rcx] == " " || byte ptr [rcx] == 09h
			inc rcx
			jmp @B
		.endif
	lea rsi,folding_tmp___first_word
	mov rax,rsi
	@@:
		.if byte ptr [rcx] == 0  || byte ptr [rcx] == ";" || byte ptr [rcx] == "'"  || byte ptr [rcx] == '"'
			mov byte ptr [rsi],0
			ret
		.endif
		.if  byte ptr [rcx] == 0ah || byte ptr [rcx] == " " || byte ptr [rcx] == 09h
			mov byte ptr [rsi],0
			lea rsi,folding_tmp___second_word
			jmp @F
		.endif
		mov r9b,byte ptr [rcx]
		mov byte ptr [rsi],r9b
		inc rsi
		inc rcx
		jmp @B
	@@:
		.if byte ptr [rcx] == 0  || byte ptr [rcx] == ";" || byte ptr [rcx] == "'"  || byte ptr [rcx] == '"'
			mov byte ptr [rsi],0
			xor rax,rax
			ret
		.endif
		.if byte ptr [rcx] == 0ah || byte ptr [rcx] == " " || byte ptr [rcx] == 09h
			inc rcx
			jmp @B
		.endif
	@@:
		.if byte ptr [rcx] == 0|| byte ptr [rcx] == 0ah || byte ptr [rcx] == " " || byte ptr [rcx] == 09h  || byte ptr [rcx] == ";" || byte ptr [rcx] == "'"  || byte ptr [rcx] == '"'
			mov byte ptr [rsi],0
			ret
		.endif
		mov r9b,byte ptr [rcx]
		mov byte ptr [rsi],r9b
		inc rsi
		inc rcx
		jmp @B
          RET
folding_get_first_and_second_word ENDP

folding_processing_Text proc _textbuffer:gpointer,__Line:gint
local textbuffer:gpointer
local iter:GtkTextIter
local iter1:GtkTextIter
local __EndStr:gpointer
local mark:gpointer
local _Line:gint
local _Folding_Word_List:gpointer
local _Folding_Word_End_List:gpointer
local UpC_str:gpointer

	mov textbuffer,_textbuffer
	mov _Line,__Line
	.if _Line==-1	
		invoke gtk_text_buffer_get_insert,textbuffer
		invoke  gtk_text_buffer_get_iter_at_mark,textbuffer,addr iter,rax
		invoke gtk_text_iter_get_line,addr iter
		mov _line,eax	
	.endif
	invoke gtk_text_buffer_get_iter_at_line,textbuffer,addr iter,_line
	invoke gtk_text_buffer_get_iter_at_line,textbuffer,addr iter1,_line
	invoke gtk_text_iter_forward_to_line_end,addr iter1

	invoke gtk_source_buffer_remove_source_marks,textbuffer,addr iter,addr iter,0
 
	invoke gtk_text_iter_get_text,addr iter,addr iter1
	.if byte ptr [rax]==0ah
		ret
	.endif
	mov UpC_str,rv(g_strup,rax)

	folding_get_first_and_second_word(UpC_str)
	g_free(UpC_str)
	        m2m _Folding_Word_List		,Settings_Folding_First_Word_Liste
	        m2m _Folding_Word_End_List	,Settings_Folding_EndOf_First_Word_Liste
		.if _Folding_Word_List
		 @@: 
		   	mov rax,_Folding_Word_List    
		   	mov rax,[rax] 
		 	.if  rax
		 		.if 	rv(g_strcmp0,addr folding_tmp___first_word, rax) == 0 	
				   	mov rax,_Folding_Word_End_List    
				   	mov rax,[rax] 
			 		mov __EndStr,rv(g_strconcat,str$("-"),rax,0,0,0,0,0)
 
			 		place_mark_S(textbuffer,_line,__EndStr,fold_minus)
					invoke g_free ,__EndStr
					ret
	   	 		.endif
		 		add _Folding_Word_List,8
		 		add _Folding_Word_End_List,8
		 		jmp @B
		 	.endif
		.endif

	        m2m _Folding_Word_List		,Settings_Folding_Second_Word_Liste
	        m2m _Folding_Word_End_List	,Settings_Folding_EndOf_Second_Word_Liste
		.if _Folding_Word_List
		 @@: 
		   	mov rax,_Folding_Word_List    
		   	mov rax,[rax] 
		 	.if  rax
		 		.if 	rv(g_strcmp0,addr folding_tmp___second_word, rax) == 0 	
				   	mov rax,_Folding_Word_End_List    
				   	mov rax,[rax] 
			 		mov __EndStr,rv(g_strconcat,str$("-"),rax,0,0,0,0,0)
 
			 		place_mark_S(textbuffer,_line,__EndStr,fold_minus)
					invoke g_free ,__EndStr
					ret
	   	 		.endif
		 		add _Folding_Word_List,8
		 		add _Folding_Word_End_List,8
		 		jmp @B
		 	.endif
		.endif

	        m2m _Folding_Word_List		,Settings_Folding_First_Word_End_Liste
		.if _Folding_Word_List
		 @@: 
		   	mov rax,_Folding_Word_List    
		   	mov rax,[rax] 
		 	.if  rax
		 		.if 	rv(g_strcmp0,addr folding_tmp___first_word, rax) == 0 					
			 		mov __EndStr,rv(g_strconcat,str$("."),addr folding_tmp___first_word,0,0,0,0,0)
 
			 		place_mark_S(textbuffer,_line,__EndStr,fold_end)
					invoke g_free ,__EndStr
					ret
	   	 		.endif
		 		add _Folding_Word_List,8
		 		jmp @B
		 	.endif
		.endif
		
	        m2m _Folding_Word_List,Settings_Folding_Second_Word_End_Liste
		.if _Folding_Word_List
		 @@: 
		   	mov rax,_Folding_Word_List    
		   	mov rax,[rax] 
		 	.if  rax
		 		.if 	rv(g_strcmp0,addr folding_tmp___second_word, rax) == 0 					
			 		mov __EndStr,rv(g_strconcat,str$("."),addr folding_tmp___second_word,0)
 
			 		place_mark_S(textbuffer,_line,__EndStr,fold_end)
					invoke g_free ,__EndStr
					ret
	   	 		.endif
		 		add _Folding_Word_List,8
		 		jmp @B
		 	.endif
		.endif
	ret
folding_processing_Text endp