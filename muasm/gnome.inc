	include gtk.inc
	include g_content_type.inc
	include g_object.inc
	include g_file.inc
	include g_string.inc
	include g_ustring.inc

	g_new	 		PROTO :VARARG
 	g_new0	 		PROTO :VARARG
 	g_renew	 		PROTO :VARARG
 	g_try_new		PROTO :VARARG
 	g_try_new0		PROTO :VARARG
 	g_try_renew		PROTO :VARARG
 	g_malloc 		PROTO :VARARG
 	g_malloc0 		PROTO :VARARG
 	g_realloc 		PROTO :VARARG
 	g_try_malloc 		PROTO :VARARG
 	g_try_malloc0 		PROTO :VARARG
 	g_try_realloc 		PROTO :VARARG
 	g_malloc_n 		PROTO :VARARG
 	g_malloc0_n 		PROTO :VARARG
 	g_realloc_n 		PROTO :VARARG
 	g_try_malloc_n 		PROTO :VARARG
 	g_try_malloc0_n 	PROTO :VARARG
 	g_try_realloc_n 	PROTO :VARARG
 	g_free 	 		PROTO :VARARG
 	g_clear_pointer 	PROTO :VARARG
 	g_steal_pointer 	PROTO :VARARG
 	g_alloca		PROTO :VARARG
 	g_newa	 		PROTO :VARARG
 	g_memmove		PROTO :VARARG
 	g_memdup 		PROTO :VARARG
 	g_mem_set_vtable	PROTO :VARARG
 	g_mem_is_system_malloc 	PROTO :VARARG
 	g_mem_profile 		PROTO :VARARG
 
