

	 	g_spawn_async_with_fds PROTO :VARARG 
	 	g_spawn_async_with_pipes PROTO :VARARG 
	 	g_spawn_async PROTO :VARARG 
	 	g_spawn_sync PROTO :VARARG 
	 	g_spawn_check_exit_status PROTO :VARARG 
	 	g_spawn_command_line_async PROTO :VARARG 
	 	g_spawn_command_line_sync PROTO :VARARG 
	 	g_spawn_close_pid PROTO :VARARG 
			 	
		G_SPAWN_DEFAULT                = 0
		G_SPAWN_LEAVE_DESCRIPTORS_OPEN = 1 shl 0
		G_SPAWN_DO_NOT_REAP_CHILD      = 1 shl 1
		G_SPAWN_SEARCH_PATH            = 1 shl 2
		G_SPAWN_STDOUT_TO_DEV_NULL     = 1 shl 3
		G_SPAWN_STDERR_TO_DEV_NULL     = 1 shl 4
		G_SPAWN_CHILD_INHERITS_STDIN   = 1 shl 5
		G_SPAWN_FILE_AND_ARGV_ZERO     = 1 shl 6
		G_SPAWN_SEARCH_PATH_FROM_ENVP  = 1 shl 7
		G_SPAWN_CLOEXEC_PIPES          = 1 shl 8
		 	
