
.code
	gtk_init_check		proto	:vararg
    gtk_window_new		proto	:vararg
    gtk_widget_show_all	proto	:vararg
    gtk_main			proto	:vararg
    gtk_main_quit		proto	:vararg

main proc _argc, _argv:qword

  local window  :ptr  
	gtk_init_check(0, 0)
    gtk_window_new(0)
    mov window,rax
    gtk_widget_show_all(window)
    gtk_main()
    gtk_main_quit()
    ret

main endp
 

    end
