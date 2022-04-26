	include glib.inc
	include ./gtk/g_signal.inc
	include	./gtk/gtk_main.inc
	include	./gtk/gtk_widget.inc
	include	./gtk/gtk_window.inc
	include	./gtk/gdk_window.inc
	include	./gtk/gtk_builder.inc
	include ./gtk/gdk_display.inc
	include ./gtk/gdk_monitor.inc
	include ./gtk/gdk_screen.inc
	include ./gtk/gdk_pixbuf.inc
	include ./gtk/gtk_image.inc
	include ./gtk/gtk_notebook.inc
	include ./gtk/gtk_label.inc
	include ./gtk/gtk_container.inc
	include ./gtk/gtk_text_view.inc
	include ./gtk/gtk_source_view.inc
	include ./gtk/gtk_scrolled_window.inc
	include ./gtk/gtk_source_buffer.inc
	include ./gtk/gtk_source_language_manager.inc
	include ./gtk/gtk_source_language.inc
	include ./gtk/gtk_source_style_scheme_manager.inc
	include ./gtk/gtk_css_provider.inc
	include ./gtk/gtk_style_context.inc
	include ./gtk/gtk_tree_store.inc
	include ./gtk/gtk_cell_view.inc
	include ./gtk/gtk_icon_theme.inc
	include ./gtk/gtk_tree_view.inc
	include ./gtk/gtk_tree_selection.inc
	include ./gtk/gtk_tree_model.inc
	include ./gtk/gtk_cell_renderer_pixbuf.inc
	include ./gtk/gtk_rc.inc
	include ./gtk/gtk_box.inc
	include ./gtk/gtk_button.inc
	include ./gtk/gtk_paned.inc
	include ./gtk/gtk_text_buffer.inc
	include ./gtk/gtk_file_chooser_dialog.inc
	include ./gtk/gtk_file_chooser.inc
	include ./gtk/gtk_dialog.inc
	include ./gtk/gtk_entry.inc
	include ./gtk/gtk_entry_buffer.inc
	include ./gtk/gtk_cell_renderer_text.inc
	include ./gtk/gtk_tree_view_column.inc
	include ./gtk/gtk_list_store.inc
	include ./gtk/gdk_cairo.inc
	include ./gtk/gtk_source_mark_attributes.inc
	include ./gtk/gtk_text_iter.inc
	include ./gtk/gtk_source_mark.inc
	include ./gtk/gdk_pixbuf_loader.inc
	include ./gtk/gdk_pixbuf_new.inc	
	include ./gtk/gdk_pixbuf_transform.inc
	include ./gtk/gtk_menu.inc
	include ./gtk/gtk_menu_item.inc
	include ./gtk/gtk_menu_shell.inc
	include ./gtk/gdk_events.inc
	include ./gtk/gtk_file_filter.inc
	include ./gtk/gtk_message_dialog.inc
	include ./gtk/gtk_Main_loop_and_Events.inc
	include ./gtk/gtk_combo_box_text.inc	
	include ./gtk/gtk_combo_box.inc
	include ./gtk/gtk_toggle_button.inc
	include ./gtk/gtk_source_search_context.inc
	include ./gtk/gtk_source_search_settings.inc
	;include ./gtk/gdkkeysyms.inc


 
	gtkproperty struct
		_type   dq  0
		_value  dq  0
	gtkproperty ends
	GdkRectangle struct
		_x  dword   0
		_y  dword   0
		_w  dword   0
		_h  dword   0
	GdkRectangle ends
	GdkRGBA struct  
		red     gdouble 0;
		green   gdouble 0;
		blue    gdouble 0;
		alpha   gdouble 0;
	GdkRGBA ends  
	gdk_rgba macro  _r,_g,_b,_a
		local vGdkRGBA
		.data
		    vGdkRGBA    GdkRGBA <_r,_g,_b,_a>
		.code
		EXITM<vGdkRGBA>
	endm	
	GtkTextIter struct sizeof gpointer
		dummy1     gpointer 0
		dummy2     gpointer 0
		dummy3     gint     0
		dummy4     gint     0
		dummy5     gint     0
		dummy6     gint     0
		dummy7     gint     0
		dummy8     gint     0
		dummy9     gpointer 0
		dummy10    gpointer 0
		dummy11    gint     0
		dummy12    gint     0
		dummy13    gint     0
		dummy14    gpointer 0  
	GtkTextIter ends
	GtkTreeIter struct   sizeof gpointer
		stamp       gint     0
		user_data   gpointer 0
		user_data2  gpointer 0
		user_data3  gpointer 0
	GtkTreeIter ends   
  	gdk_pixbuf_add_alpha  PROTO :VARARG 
 	gdk_pixbuf_copy_area  PROTO :VARARG 
 	gdk_pixbuf_saturate_and_pixelate  PROTO :VARARG 
  	gdk_pixbuf_apply_embedded_orientation  PROTO :VARARG 
 	gdk_pixbuf_fill  PROTO :VARARG 
 	gdk_pixbuf_get_type PROTO :VARARG
 	
	GTK_STATE_FLAG_NORMAL       = 0
	GTK_STATE_FLAG_ACTIVE       = 1 shl 0
	GTK_STATE_FLAG_PRELIGHT     = 1 shl 1
	GTK_STATE_FLAG_SELECTED     = 1 shl 2
	GTK_STATE_FLAG_INSENSITIVE  = 1 shl 3
	GTK_STATE_FLAG_INCONSISTENT = 1 shl 4
	GTK_STATE_FLAG_FOCUSED      = 1 shl 5
	GTK_STATE_FLAG_BACKDROP     = 1 shl 6
	GTK_STATE_FLAG_DIR_LTR      = 1 shl 7
	GTK_STATE_FLAG_DIR_RTL      = 1 shl 8
	GTK_STATE_FLAG_LINK         = 1 shl 9
	GTK_STATE_FLAG_VISITED      = 1 shl 10
	GTK_STATE_FLAG_CHECKED      = 1 shl 11
	GTK_STATE_FLAG_DROP_ACTIVE  = 1 shl 12 	

	GTK_ORIENTATION_HORIZONTAL  equ 0
	GTK_ORIENTATION_VERTICAL    equ 1

	enum  	GDK_INTERP_NEAREST, \
		GDK_INTERP_TILES,\
		GDK_INTERP_BILINEAR,\
		GDK_INTERP_HYPER
	;GdkEventType
	GDK_NOTHING		= -1
	GDK_DELETE		= 0
	GDK_DESTROY		= 1
	GDK_EXPOSE		= 2
	GDK_MOTION_NOTIFY	= 3
	GDK_BUTTON_PRESS	= 4
	GDK_2BUTTON_PRESS	= 5
	GDK_DOUBLE_BUTTON_PRESS = GDK_2BUTTON_PRESS
	GDK_3BUTTON_PRESS	= 6
	GDK_TRIPLE_BUTTON_PRESS = GDK_3BUTTON_PRESS
	GDK_BUTTON_RELEASE	= 7
	GDK_KEY_PRESS		= 8
	GDK_KEY_RELEASE	        = 9
	GDK_ENTER_NOTIFY	= 10
	GDK_LEAVE_NOTIFY	= 11
	GDK_FOCUS_CHANGE	= 12
	GDK_CONFIGURE		= 13
	GDK_MAP		        = 14
	GDK_UNMAP		= 15
	GDK_PROPERTY_NOTIFY	= 16
	GDK_SELECTION_CLEAR	= 17
	GDK_SELECTION_REQUEST   = 18
	GDK_SELECTION_NOTIFY	= 19
	GDK_PROXIMITY_IN	= 20
	GDK_PROXIMITY_OUT	= 21
	GDK_DRAG_ENTER          = 22
	GDK_DRAG_LEAVE          = 23
	GDK_DRAG_MOTION         = 24
	GDK_DRAG_STATUS         = 25
	GDK_DROP_START          = 26
	GDK_DROP_FINISHED       = 27
	GDK_CLIENT_EVENT	= 28
	GDK_VISIBILITY_NOTIFY   = 29
	GDK_SCROLL              = 31
	GDK_WINDOW_STATE        = 32
	GDK_SETTING             = 33
	GDK_OWNER_CHANGE        = 34
	GDK_GRAB_BROKEN         = 35
	GDK_DAMAGE              = 36
	GDK_TOUCH_BEGIN         = 37
	GDK_TOUCH_UPDATE        = 38
	GDK_TOUCH_END           = 39
	GDK_TOUCH_CANCEL        = 40
	GDK_TOUCHPAD_SWIPE      = 41
	GDK_TOUCHPAD_PINCH      = 42
	GDK_PAD_BUTTON_PRESS    = 43
	GDK_PAD_BUTTON_RELEASE  = 44
	GDK_PAD_RING            = 45
	GDK_PAD_STRIP           = 46
	GDK_PAD_GROUP_MODE      = 47
	;GDK_EVENT_LAST        ; helper variable for decls */
	GdkEventType typedef dword
GdkModifierType typedef qWORD
    GDK_SHIFT_MASK		  			= 1 shl 0
    GDK_LOCK_MASK		  			= 1 shl 1
    GDK_CONTROL_MASK		  		= 1 shl 2
    GDK_MOD1_MASK		  			= 1 shl 3
    GDK_MOD2_MASK		  			= 1 shl 4
    GDK_MOD3_MASK		  			= 1 shl 5
    GDK_MOD4_MASK		  			= 1 shl 6
    GDK_MOD5_MASK		  			= 1 shl 7
    GDK_BUTTON1_MASK		  		= 1 shl 8
    GDK_BUTTON2_MASK		  		= 1 shl 9
    GDK_BUTTON3_MASK		  		= 1 shl 10
    GDK_BUTTON4_MASK		  		= 1 shl 11
    GDK_BUTTON5_MASK		  		= 1 shl 12
    GDK_SUPER_MASK		  			= 1 shl 26
    GDK_HYPER_MASK		  			= 1 shl 27
    GDK_META_MASK		  			= 1 shl 28
    GDK_RELEASE_MASK		  		= 1 shl 30
    GDK_MODIFIER_MASK		  		= 0x5c001fff


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

	GTK_TEXT_WINDOW_WIDGET EQU 1
	GTK_WINDOW_POPUP EQU 1
	GTK_WRAP_NONE EQU 0
	GTK_WRAP_WORD_CHAR EQU 3
	GTK_STYLE_PROVIDER_PRIORITY_USER EQU 800
	G_FILE_TEST_EXISTS = 1  shl  4

    	
	GdkEventButton struct sizeof gpointer
		_type 		GdkEventType	GDK_NOTHING
		window 		gpointer	0	;GdkWindow *
		send_event 	gint8		0
		time 		guint32		0
		x 		gdouble		0.0
		y 		gdouble		0.0
		axes 		gpointer	0	;gdouble * 
		state 		guint		0
		button 		guint		0
		device		gpointer 	0	;GdkDevice * 
		x_root 		gdouble		0.0
		y_root 		gdouble		0.0
	GdkEventButton ends
	GdkEventKey		STRUC sizeof gpointer
		_type				gint ?
		window				gpointer ?
		send_event			gint8 ?
		time				guint32 ?
		state				guint ?
		keyval				guint ?
		_length				gint ?
		string				gpointer ?
		hardware_keycode	guint16 ?
		_group				guint8 ?
		is_modifier			guint ? ; : 1
	GdkEventKey		ENDS
	
	enum GTK_MESSAGE_INFO,GTK_MESSAGE_WARNING, GTK_MESSAGE_QUESTION, GTK_MESSAGE_ERROR, GTK_MESSAGE_OTHER	

	messagebox macro _flags,_type,_buttons,__message_format,_msg:vararg
	    local _WMmessageBox
	    local _response
	    .data
			_WMmessageBox   gpointer 0
			_response       gint 0
	    .code
	    IFB <_msg>
			mov _WMmessageBox ,rv(gtk_message_dialog_new,0, _flags,_type,_buttons,__message_format)
	    ELSE
			mov _WMmessageBox ,rv(gtk_message_dialog_new,0, _flags,_type,_buttons,__message_format,_msg)
	    ENDIF
	    invoke gtk_dialog_run,_WMmessageBox
	    mov _response,eax
	    invoke gtk_widget_destroy,_WMmessageBox
	    EXITM<_response>
	endm



	msgbox macro __message_format,__msg:vararg
	    local ___WMmessageBox
	    .data
		___WMmessageBox     gpointer 0
	    .code
	    IFB <__msg>
	 
		mov ___WMmessageBox ,rv(gtk_message_dialog_new,0, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, __message_format)  
	    ELSE       
		mov ___WMmessageBox ,rv(gtk_message_dialog_new,0, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, __message_format,__msg)
	    ENDIF
	    invoke gtk_dialog_run,___WMmessageBox
	    invoke gtk_widget_destroy,___WMmessageBox
	endm		
 
	;GtkResponseType enum
	  	GTK_RESPONSE_NONE         = -1
		GTK_RESPONSE_REJECT       = -2
		GTK_RESPONSE_ACCEPT       = -3
		GTK_RESPONSE_DELETE_EVENT = -4
		GTK_RESPONSE_OK           = -5
		GTK_RESPONSE_CANCEL       = -6
		GTK_RESPONSE_CLOSE        = -7
		GTK_RESPONSE_YES          = -8
		GTK_RESPONSE_NO           = -9
		GTK_RESPONSE_APPLY        = -10
		GTK_RESPONSE_HELP         = -11



