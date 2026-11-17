IFNDEF ___glib___
       ___glib___	EQU 0
    	gpointer    	TYPEDEF PTR
    	gchar			TYPEDEF SBYTE
    	guchar			TYPEDEF	BYTE
    	gshort			TYPEDEF SWORD
    	gushort			TYPEDEF WORD
    	gint			TYPEDEF SDWORD
    	guint			TYPEDEF DWORD
    	gboolean		TYPEDEF gint
    	gint8			TYPEDEF SBYTE
    	gint16			TYPEDEF SWORD
    	gint32			TYPEDEF SDWORD
    	gint64			TYPEDEF SQWORD
    	guint8			TYPEDEF BYTE
    	guint16			TYPEDEF WORD
    	guint32			TYPEDEF DWORD
    	guint64			TYPEDEF QWORD
    	gfloat			TYPEDEF REAL4
    	gdouble			TYPEDEF REAL8
    	
    	IF(SIZEOF(gpointer) eq 8)
    		gulong		TYPEDEF	QWORD
    		glong		TYPEDEF	SQWORD
    	ELSE
    		gulong		TYPEDEF	DWORD
    		glong		TYPEDEF	SDWORD
    	ENDIF
    	gsize			TYPEDEF gulong
    	gssize			TYPEDEF glong
    	goffset			TYPEDEF	gint64
    	gintptr			TYPEDEF glong
    	guintptr		TYPEDEF gulong
    	
	g_new	 		proto :VARARG
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
 	g_print			PROTO :VARARG
 	
 	g_shell_parse_argv	PROTO :VARARG
 
	include g_content_type.inc
	include g_object.inc
	include g_file.inc
	include g_string.inc
	include g_ustring.inc
	include g_list.inc
	include g_hash_table.inc
	include g_key_file.inc
	include gdir.inc
	include g_io_channel.inc
	include g_convert.inc
	include g_spawn.inc
	include g_main.inc
	include g_thread.inc
	include g_timer.inc

 	include gutils.inc
	include g_DateTime.inc

	GLIB_SYSDEF_POLLIN =1
	GLIB_SYSDEF_POLLOUT =4
	GLIB_SYSDEF_POLLPRI =2
	GLIB_SYSDEF_POLLERR =8
	GLIB_SYSDEF_POLLHUP =16
	GLIB_SYSDEF_POLLNVAL =32

	G_IO_IN	=	GLIB_SYSDEF_POLLIN
	G_IO_OUT=	GLIB_SYSDEF_POLLOUT
	G_IO_PRI=	GLIB_SYSDEF_POLLPRI
	G_IO_ERR=	GLIB_SYSDEF_POLLERR
	G_IO_HUP=	GLIB_SYSDEF_POLLHUP
	G_IO_NVAL=	GLIB_SYSDEF_POLLNVAL


	G_TYPE_FUNDAMENTAL_SHIFT	equ 2

	G_TYPE_MAKE_FUNDAMENTAL macro __t,__x
		__t = __x	shl G_TYPE_FUNDAMENTAL_SHIFT
	 
	endm
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_INVALID	,0
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_NONE	,1
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_INT64	,10
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_UINT64	,11
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_ENUM	,12
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_FLAGS	,13
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_FLOAT	,14
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_DOUBLE	,15
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_STRING	,16
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_POINTER	,17
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_BOXED	,18
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_PARAM	,19
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_INTERFACE	,2
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_OBJECT	,20
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_CHAR	,3
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_UCHAR	,4
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_BOOLEAN	,5
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_INT	,6
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_UINT	,7
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_LONG	,8
	G_TYPE_MAKE_FUNDAMENTAL G_TYPE_ULONG	,9



	GQuark typedef guint32

	GError typedef ptr _GError
	_GError struct 8
		domain 	GQuark 		?
		code   	gint 		?
		message gpointer 	?  ;gchar       *
	_GError ends

	TRUE EQU 1
	NULL EQU 0
	FALSE EQU 0



       
ENDIF


