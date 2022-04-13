 	g_key_file_new  PROTO :VARARG 
	g_key_file_free  PROTO :VARARG 
 	g_key_file_ref  PROTO :VARARG 
	g_key_file_unref  PROTO :VARARG 
	g_key_file_set_list_separator  PROTO :VARARG 
	g_key_file_load_from_file  PROTO :VARARG 
	g_key_file_load_from_data  PROTO :VARARG 
	g_key_file_load_from_bytes  PROTO :VARARG 
	g_key_file_load_from_data_dirs  PROTO :VARARG 
	g_key_file_load_from_dirs  PROTO :VARARG 
 	g_key_file_to_data  PROTO :VARARG 
	g_key_file_save_to_file  PROTO :VARARG 
 	g_key_file_get_start_group  PROTO :VARARG 
 	g_key_file_get_groups  PROTO :VARARG 
 	g_key_file_get_keys  PROTO :VARARG 
	g_key_file_has_group  PROTO :VARARG 
	g_key_file_has_key  PROTO :VARARG 
 	g_key_file_get_value  PROTO :VARARG 
 	g_key_file_get_string  PROTO :VARARG 
 	g_key_file_get_locale_string  PROTO :VARARG 
 	g_key_file_get_locale_for_key  PROTO :VARARG 
	g_key_file_get_boolean  PROTO :VARARG 
	g_key_file_get_integer  PROTO :VARARG 
	g_key_file_get_int64  PROTO :VARARG 	
	    IFDEF RAX
		IF TYPE(RAX) EQ 8
    	    	    g_key_file_set_ptr	TEXTEQU <g_key_file_set_int64>    	    	    
    	    	    g_key_file_get_ptr	TEXTEQU <g_key_file_get_int64>
		ELSE
    	    	    g_key_file_set_ptr	TEXTEQU <g_key_file_set_integer>    	    	    
    	    	    g_key_file_get_ptr	TEXTEQU <g_key_file_get_integer>
		ENDIF
	    ELSE
    	    	    g_key_file_set_ptr	TEXTEQU <g_key_file_set_integer>    	    	    
    	    	    g_key_file_get_ptr	TEXTEQU <g_key_file_get_integer>
	    ENDIF	
	g_key_file_get_uint64  PROTO :VARARG 
	g_key_file_get_double  PROTO :VARARG 
 	g_key_file_get_string_list  PROTO :VARARG 
 	g_key_file_get_locale_string_list  PROTO :VARARG 
 	g_key_file_get_boolean_list  PROTO :VARARG 
 	g_key_file_get_integer_list  PROTO :VARARG 
 	g_key_file_get_double_list  PROTO :VARARG 
 	g_key_file_get_comment  PROTO :VARARG 
	g_key_file_set_value  PROTO :VARARG 
	g_key_file_set_string  PROTO :VARARG 
	g_key_file_set_locale_string  PROTO :VARARG 
	g_key_file_set_boolean  PROTO :VARARG 
	g_key_file_set_integer  PROTO :VARARG 
	g_key_file_set_int64  PROTO :VARARG 
	g_key_file_set_uint64  PROTO :VARARG 
	g_key_file_set_double  PROTO :VARARG 
	g_key_file_set_string_list  PROTO :VARARG 
	g_key_file_set_locale_string_list  PROTO :VARARG 
	g_key_file_set_boolean_list  PROTO :VARARG 
	g_key_file_set_integer_list  PROTO :VARARG 
	g_key_file_set_double_list  PROTO :VARARG 
	g_key_file_set_comment  PROTO :VARARG 
	g_key_file_remove_group  PROTO :VARARG 
	g_key_file_remove_key  PROTO :VARARG 
	g_key_file_remove_comment  PROTO :VARARG 
	
	G_KEY_FILE_NONE          	= 0 
	G_KEY_FILE_KEEP_COMMENTS     	= 1 
	G_KEY_FILE_KEEP_TRANSLATIONS 	= 2		
