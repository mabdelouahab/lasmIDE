CAIRO_FORMAT_ARGB32    = 0

  .data
    __rcol  REAL8    1.0
    __rcolB REAL8    0.0
    
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
    invoke cairo_set_source_rgb,lcr,__rcol,__rcolB,__rcol
        fild __w
        fsub FP8(8.0)
        fstp _w2
        fild __h
        fsub FP8(8.0)
        fstp _h2   
    invoke cairo_rectangle,lcr, FP8(4.0),FP8(4.0),_w2,_h2
   ; invoke cairo_fill,lcr
    
  ;  invoke cairo_set_source_rgb,lcr,__rcolB,__rcolB,__rcolB
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
    invoke cairo_set_source_rgb,lcr ,__rcol,__rcolB,__rcol
        fild __w
        fsub FP8(8.0)
        fstp _w2
        fild __h
        fsub FP8(8.0)
        fstp _h2   
    invoke cairo_rectangle,lcr, FP8(4.0),FP8(4.0),_w2,_h2
   ; invoke cairo_fill,lcr
    
  ;  invoke cairo_set_source_rgb,lcr,__rcolB,__rcolB,__rcolB;
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
    invoke cairo_set_source_rgb,lcr,__rcol,__rcolB,__rcol    
        finit
        fild __w
        fdiv FP8(2.0) 
        fstp _w2
        fild __h
        fstp _h2
    invoke cairo_move_to ,lcr,_w2,FP8(0.0);__rcolB
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
    invoke cairo_set_source_rgb,lcr,__rcol,__rcolB,__rcol 
        finit
        fild __w
        fdiv FP8(2.0) 
        fstp _w2
    invoke cairo_move_to ,lcr,_w2,__rcolB
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
    fold_plus   = 0
    fold_minus  = 1
    fold_vert   = 2
    fold_end    = 3
place_mark PROC tbuf:gpointer,ln,Nmark
local ltb:gpointer
local lln
local lNmark
    mov ltb,tbuf
    mov lln,ln
    mov lNmark,Nmark
    invoke gtk_text_buffer_get_iter_at_line,ltb,addr __iter,lln
    .if lNmark ==fold_plus
        invoke gtk_source_buffer_create_source_mark,ltb,0,"+",addr __iter
        invoke printf,str$(<13,10,"create_source_mark,fold_plus={%d}">),rax
    .elseif lNmark ==fold_minus
        invoke gtk_source_buffer_create_source_mark,ltb,0,"-",addr __iter
    .elseif lNmark ==fold_vert
        invoke gtk_source_buffer_create_source_mark,ltb,0,"|",addr __iter
        invoke printf,str$(<13,10,"create_source_mark,fold_vert={%d}">),rax
    .elseif lNmark ==fold_end
        invoke gtk_source_buffer_create_source_mark,ltb,0,".",addr __iter
        invoke printf,str$(<13,10,"create_source_mark,fold_end={%d}">),rax
    .endif
    RET
place_mark ENDP
create_marks proc v:gpointer
    local lpixbuf:gpointer
    local lmark_attr:gpointer
    local lv:gpointer
    
    mov lv,v
    mov lpixbuf     ,rv(get_fold_plus_pixbuf)
    mov lmark_attr  ,rv(gtk_source_mark_attributes_new)
    invoke gtk_source_mark_attributes_set_pixbuf,lmark_attr,lpixbuf
    invoke gtk_source_view_set_mark_attributes,lv,"+",lmark_attr,0
    
    mov lpixbuf     ,rv(get_fold_minus_pixbuf)
    mov lmark_attr  ,rv(gtk_source_mark_attributes_new)
    invoke gtk_source_mark_attributes_set_pixbuf,lmark_attr,lpixbuf
    invoke gtk_source_view_set_mark_attributes,lv,"-",lmark_attr,0
    
    mov lpixbuf     ,rv(get_fold_vert_pixbuf)
    mov lmark_attr  ,rv(gtk_source_mark_attributes_new)
    invoke gtk_source_mark_attributes_set_pixbuf,lmark_attr,lpixbuf
    invoke gtk_source_view_set_mark_attributes,lv,"|",lmark_attr,0
    
    mov lpixbuf     ,rv(get_fold_end_pixbuf)
    mov lmark_attr  ,rv(gtk_source_mark_attributes_new)
    invoke gtk_source_mark_attributes_set_pixbuf,lmark_attr,lpixbuf
    invoke gtk_source_view_set_mark_attributes,lv,".",lmark_attr,0
    
    ret
create_marks endp   

                
on_line_mark_activated proc view:gpointer,iter:gpointer,event:gpointer,user_data:gpointer
    local ln
    local liter:gpointer
    local luser_data:gpointer
    mov luser_data,user_data
    mov liter,iter
    invoke gtk_text_iter_get_line,liter
    mov ln,eax
    invoke gtk_source_buffer_get_source_marks_at_iter,luser_data,liter,0
    .if rax
        invoke gtk_source_mark_get_category ,[rax]
        .if byte ptr [rax] == '+'
invoke printf,str$(<13,10,"on_line_mark_activated line={%d,++++++,%s}">),ln,rax,rax        
        .elseif byte ptr [rax] == '-'
        inc ln
        invoke gtk_text_buffer_get_iter_at_line,luser_data,addr enditer,ln

invoke gtk_text_buffer_apply_tag_by_name,luser_data,"invisible",liter,addr enditer
invoke printf,str$(<13,10,"on_line_mark_activated line={%d,--,%s}">),ln,rax,rax                
        .elseif byte ptr [rax] == '|'
invoke printf,str$(<13,10,"on_line_mark_activated line={%d,||,%s}">),ln,rax,rax        
        .elseif byte ptr [rax] == '.'
invoke printf,str$(<13,10,"on_line_mark_activated line={%d,end,%s}">),ln,rax,rax        
        .endif
;        invoke printf,str$(<13,10,"on_line_mark_activated line={%d,marks=%d,%s}">),ln,rax,rax
    .endif

    ret
on_line_mark_activated endp
 