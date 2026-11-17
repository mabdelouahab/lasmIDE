
	GtkApplication 	TYPEDEF QWORD 
 	GtkWidget      	TYPEDEF QWORD
 	gpointer      	 	TYPEDEF QWORD  
 
 	g_signal_connect_data 		PROTO :QWORD,:QWORD, :QWORD, :QWORD, :QWORD, :QWORD
 	gtk_window_set_default_size  	PROTO :QWORD, :QWORD, :QWORD
 	g_application_run     			PROTO :QWORD,:QWORD, :QWORD
 	gtk_application_window_new   PROTO :QWORD
 	gtk_application_new   		PROTO :QWORD,:QWORD
 	gtk_window_set_title  		PROTO :QWORD,:QWORD
 	gtk_widget_show_all   		PROTO :QWORD
 	g_object_unref 				PROTO :QWORD
 
 	G_APPLICATION_FLAGS_NONE equ 0
 
 	NULL EQU 0
 