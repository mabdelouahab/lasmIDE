
_GdkEventKey    struct 8
    type_   QWORD    ?               ;8
    window  QWORD   ?                          ;8
    send_event      DWORD   ?       ;4
    time    DWORD ?              ;4
    state   DWORD   ?              ;4
    keyval  DWORD   ?              ;4           ;until here is right, bellow can be wrong size
    length_ DWORD    ?              ;4
    string  QWORD   ?              ;8
    hardware_keycode        DWORD ?      ;
    group_  DWORD  ?              ;
    GdkEventKey_R0 DWORD ?
_GdkEventKey    ends

GdkModifierType typedef qWORD
GDK_SHIFT_MASK = 1  shl  0
GDK_LOCK_MASK = 1  shl  1
GDK_CONTROL_MASK = 1  shl  2
GDK_MOD1_MASK = 1  shl  3
GDK_MOD2_MASK = 1  shl  4
GDK_MOD3_MASK = 1  shl  5
GDK_MOD4_MASK = 1  shl  6
GDK_MOD5_MASK = 1  shl  7
GDK_BUTTON1_MASK = 1  shl  8
GDK_BUTTON2_MASK = 1  shl  9
GDK_BUTTON3_MASK = 1  shl  10
GDK_BUTTON4_MASK = 1  shl  11
GDK_BUTTON5_MASK = 1  shl  12
GDK_SUPER_MASK = 1  shl  26
GDK_HYPER_MASK = 1  shl  27
GDK_META_MASK = 1  shl  28
GDK_RELEASE_MASK = 1  shl  30
GDK_MODIFIER_MASK = 5c001fffh


_GdkRectangle   struct
x       dword    ?
y       dword   ?
width_  dword   ?
height  dword   ?
_GdkRectangle   ends

gtk_font_chooser_get_font  proto :vararg
gtk_font_chooser_dialog_new proto :vararg
gtk_font_selection_dialog_new proto :vararg
gtk_font_selection_dialog_get_font_name  proto :vararg
pango_font_description_from_string  proto :vararg
gtk_color_selection_dialog_new proto :vararg
gtk_color_chooser_dialog_new proto :vararg
gtk_color_chooser_get_rgba proto :vararg
gdk_color_to_string proto :vararg
g_strsplit proto :vararg
gtk_expander_new proto :vararg
gtk_expander_set_expanded proto :vararg

gdk_rgba_to_string proto :vararg
gdk_rgba_parse proto :vararg
gtk_source_completion_words_new proto :vararg
gtk_source_completion_words_register proto :vararg
gtk_source_completion_add_provider proto :vararg
gtk_check_menu_item_toggled proto :vararg
gtk_check_menu_item_get_active proto :vararg

TRUE EQU 1
NULL EQU 0
FALSE EQU 0
GTK_TEXT_WINDOW_WIDGET EQU 1
GTK_TEXT_WINDOW_WIDGET = 1
GTK_TEXT_WINDOW_TEXT = 2
GTK_TEXT_WINDOW_LEFT = 3


GTK_WINDOW_POPUP EQU 1
GTK_WRAP_NONE EQU 0
GTK_WRAP_WORD_CHAR EQU 3
GTK_STYLE_PROVIDER_PRIORITY_USER EQU 800
G_FILE_TEST_EXISTS = 1  shl  4

_GtkTextIter    struct
    dummy1  gpointer        ?
    dummy2  gpointer        ?
    dummy3  gint    ?
    dummy4  gint    ?
    dummy5  gint    ?
    dummy6  gint    ?
    dummy7  gint    ?
    dummy8  gint    ?
    dummy9  gpointer        ?
    dummy10 gpointer        ?
    dummy11 gint    ?
    dummy12 gint    ?
    dummy13 gint    ?
    dummy14 gpointer        ?
_GtkTextIter    ends

GError typedef ptr _GError
GQuark typedef guint32

GError typedef ptr _GError
_GError struct 8
domain GQuark ?
code   gint ?
message gpointer ?  ;gchar       *
_GError ends


gtk_text_mark_set_visible proto :vararg

_GdkRectangle	struct
x	gint	?
y	gint	?
width_	gint	?
height	gint	?
_GdkRectangle	ends

.code

	List_Append	PROC	_old_DatasList:gpointer,_OData:gpointer,_pNewSz:gpointer
		local old_Datas	:gpointer
		local Nold_Datas	:gpointer
		local Nnew_Datas	:gpointer

		local newLDatas	:gpointer
		local lOData:gpointer
		local ODatasI:gpointer
		local byte_:gpointer	
 		mov lOData,_OData
		mov old_Datas,_old_DatasList
 		mov Nold_Datas,0
 		.if old_Datas
	 		mov rax,old_Datas
	 		@@:
	 		.if qword ptr [rax]
	 			inc Nold_Datas
	 			add rax,sizeof gpointer
	 			jmp @B
	 		.endif
 		.endif
 		m2m Nnew_Datas,Nold_Datas
		inc Nnew_Datas
		.if _pNewSz
			mov r10,_pNewSz
			m2m [r10],Nnew_Datas
		.endif
	 	xor rax,rax
		mov rax,Nnew_Datas
		inc rax ;null terminate array
		mov rcx,sizeof gpointer
		mul rcx
		mov byte_,rax
		mov newLDatas,rv(g_malloc,byte_)
		mov rcx,old_Datas
		mov rdx,newLDatas
		.if Nold_Datas
			@@:
			.if gpointer ptr [rcx]
				m2m gpointer ptr [rdx],gpointer ptr [rcx]	
				add rcx	,sizeof gpointer 
				add rdx	,sizeof gpointer   			 			
				jmp @B
			.endif
		.endif
		m2m gpointer ptr [rdx],lOData
		add rdx	,sizeof gpointer   			 			
		mov gpointer ptr [rdx],0
		.if Nold_Datas
			 invoke g_free,old_Datas
		.endif
		 mov rax,newLDatas
		ret
	List_Append	ENDP
	
	align 16
get_combo_box_index_by_value proc _combobox:gpointer,__value:gpointer
	local combobox:gpointer
	local _value:gpointer
	local tvalue:gpointer
	local model:gpointer
	local index:qword
	local iter_:GtkTreeIter
	mov combobox,_combobox
	mov _value,__value
	mov index,0
	mov model,rv(gtk_combo_box_get_model,combobox);
	.if model==0
		mov rax,-1
		ret
	.endif
	.if rv(gtk_tree_model_get_iter_first,model,addr iter_)==0
		mov rax,-1
		ret
	.endif
	@@:
		invoke gtk_tree_model_get,model,addr iter_,0,addr tvalue, -1,0,0,0,0
		.if rv(g_strcmp0,tvalue,_value) == 0  
			mov rax ,index
			ret			
		.endif		
		inc index
		.if rv(gtk_tree_model_iter_next,model,addr iter_)
			jmp @B
		.endif
 	mov rax ,-1
	ret 
get_combo_box_index_by_value endp
get_combo_box_append_ PROC  _combobox:gpointer,_str:qword  
	local combobox:gpointer
        local store:gpointer
        local l_str:gpointer
        local l__iter :gpointer
	mov combobox,_combobox
        mov l_str,_str  
	mov store,rv(gtk_combo_box_get_model,combobox);
        invoke gtk_list_store_append,store, addr l__iter 
        invoke gtk_list_store_set,store, addr l__iter, 0, l_str, -1 ,0,0,0,0
        RET
get_combo_box_append_ ENDP

