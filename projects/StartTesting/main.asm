	include main.inc 
.code

	main  PROC  argc:QWORD, argv:QWORD
	local window:qword
		invoke gtk_init,0,0
		gtk_window_new(0)
		mov window,rax
		gtk_window_set_title(window, "Hello Linux!")		
		gtk_widget_show_all(window)
		g_signal_connect_data(window, "destroy",addr exit_prog, 0, 0, 0)
		gtk_main()
	      xor rax,rax 
	      ret 
	main  ENDP
	exit_prog proc
		gtk_main_quit()
		ret
	exit_prog endp
	      
end  