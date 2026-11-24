	include main.inc 
.code

	main  PROC  argc:QWORD, argv:QWORD
	      LOCAL app:GtkApplication, status:DWORD
	   
	      mov app, RV(gtk_application_new , CStr("uasm.gtk.example"), G_APPLICATION_FLAGS_NONE)  
	      invoke g_signal_connect_data, app, CStr("activate"), ADDR activate, NULL, NULL, NULL
	      invoke g_application_run , app, 0 , 0 
	      mov status, eax
	      invoke g_object_unref, app
	      mov eax, status 
	      ret 
	main  ENDP

	activate PROC  app:GtkApplication, user_data:gpointer 
		 LOCAL window:GtkWidget

		 mov window , RV(gtk_application_window_new, app)
		 invoke gtk_window_set_title, window, CStr("Window")
		 invoke gtk_window_set_default_size, window, 200, 200
		 invoke gtk_widget_show_all, window
		 ret
	activate ENDP  
                    
end  