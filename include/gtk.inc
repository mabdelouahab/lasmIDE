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



