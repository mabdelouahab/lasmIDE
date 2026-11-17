 	IFNDEF SECURITY_ATTRIBUTES
		SECURITY_ATTRIBUTES STRUCT
			nLength 				DWORD ?
									DWORD ?
			lpSecurityDescriptor  	gpointer ?
			bInheritHandle 			DWORD ?
									DWORD ?
		SECURITY_ATTRIBUTES ENDS
 	ENDIF
 	IFNDEF PROCESS_INFORMATION
 		PROCESS_INFORMATION STRUCT
			hProcess        gpointer ?
			hThread         gpointer ?
			dwProcessId     DWORD ?
			dwThreadId      DWORD ?
		PROCESS_INFORMATION ENDS
	ENDIF
 	IFNDEF STARTUPINFO
		STARTUPINFO STRUCT
			cb    			DWORD 2 dup(?)
			lpReserved      gpointer ?
			lpDesktop       gpointer ?
			lpTitle         gpointer ?
			dwX             DWORD ?
			dwY             DWORD ?
			dwXSize         DWORD ?
			dwYSize         DWORD ?
			dwXCountChars   DWORD ?
			dwYCountChars   DWORD ?
			dwFillAttribute DWORD ?
			dwFlags         DWORD ?
			wShowWindow     WORD ?
			cbReserved2     WORD 3 dup(?)
			lpReserved2    gpointer ?
			hStdInput      gpointer ?
			hStdOutput     gpointer ?
			hStdError      gpointer ?
		STARTUPINFO ENDS
	ENDIF
	.proto GetCurrentProcess,RtlZeroMemory,CreatePipe,DuplicateHandle,CloseHandle,g_markup_escape_text
	.proto CreateThread,CreateEventA,GetExitCodeProcess,WaitForSingleObject,Sleep,TerminateProcess
	.proto GetLastError,strlen,WaitForMultipleObjects,ReadFile,WriteFile,CreateProcessA,SetEvent
	w_terminal_StartChildProcess proto lpszCmdLine:gpointer, bShowChildWindow:dword
	WAIT_OBJECT_0 EQU	0
	CREATE_NEW_CONSOLE EQU 00000010h
	SW_HIDE                              equ 0
	SW_SHOW                              equ 5
	STARTF_USESHOWWINDOW                 equ 1h
	STARTF_USESTDHANDLES                 equ 100h
	DUPLICATE_SAME_ACCESS                equ 2h
	ERROR_BROKEN_PIPE                    equ 109
	ERROR_NO_DATA                        equ 232
	STATUS_PENDING            			 equ 00000103h
	STILL_ACTIVE              			 equ STATUS_PENDING
	
    Process_Exited_PROTO 	TYPEDEF PROTO  teterminal:gpointer, _status:gint, __user_data:gpointer
    Process_Exited_T	 	TYPEDEF PTR  Process_Exited_PROTO

   	Process_Started_PROTO 	TYPEDEF PROTO  teterminal:gpointer, pid:gpointer, err:gpointer, user_data:gpointer
    Process_Started_T	 	TYPEDEF PTR  Process_Started_PROTO

   	Process_StdOut_PROTO 	TYPEDEF PROTO  lpszBuffer:gpointer
    Process_StdOut_T	 	TYPEDEF PTR  Process_StdOut_PROTO

   	Process_StdErr_PROTO 	TYPEDEF PROTO  lpszBuffer:gpointer
    Process_StdErr_T	 	TYPEDEF PTR  Process_StdErr_PROTO



.DATA
	 m_hStdIn 			gpointer	0
	 m_hStdOut 			gpointer	0
	 m_hStdErr 			gpointer	0
	 m_hStdInWrite 		gpointer	0
	 m_hStdOutRead 		gpointer	0
	 m_hStdErrRead 		gpointer	0
	 m_hChildProcess 	gpointer	0
	 m_hStdOutThread 	gpointer	0
	 m_hStdErrThread 	gpointer	0
	 m_hProcessThread 	gpointer	0
	 m_hExitEvent 		gpointer	0
	 m_bRunThread 		gpointer	0
	 m_bCreateProcessAE	gpointer	0
	 
	 w_terminal_view	gpointer	0
	 w_terminal_buffer	gpointer	0

	m_lpProcessStartedCallBack 	Process_Started_T 	0
	m_lpProcessExitedCallBack 	Process_Exited_T  	0
	m_lpProcessStdOutCallBack	Process_StdOut_T	0
	m_lpProcessStdErrCallBack	Process_StdErr_T	0

.proc w_terminal_Initialisation
	mov m_hStdIn 						,	0
	mov m_hStdOut 						,	0
	mov m_hStdErr 						,	0
	mov m_hStdInWrite 					,	0
	mov m_hStdOutRead 					,	0
	mov m_hStdErrRead 					,	0
	mov m_hChildProcess 				,	0
	mov m_hStdOutThread 				,	0
	mov m_hStdErrThread 				,	0
	mov m_hProcessThread 				,	0
	mov m_hExitEvent 					,	0
	mov m_bRunThread 					,	0
	mov m_bCreateProcessAE				,	0
	mov m_lpProcessStartedCallBack 		,	0
	mov m_lpProcessExitedCallBack 		,	0
	mov m_lpProcessStdOutCallBack 		,	0
	mov m_lpProcessStdErrCallBack 		,	0
.endp

	.proc w_terminal_new
		local w_terminal_GcssProvider:gpointer
		mov w_terminal_buffer, gtk_source_buffer_new(0)
			
		mov w_terminal_view,rv(gtk_source_view_new_with_buffer,w_terminal_buffer)
		mov w_terminal_GcssProvider,rv(gtk_css_provider_new)
		.if w_terminal_GcssProvider
			gtk_css_provider_load_from_data(w_terminal_GcssProvider,"* { font-family: Monospace; font-size: 10pt; background: #000000; color:#ffff99;}",-1)
			invoke gtk_style_context_add_provider,rv(gtk_widget_get_style_context,w_terminal_view), w_terminal_GcssProvider, 600
		.endif	
	.endp
	.proc w_terminal_run
	
	.endp
	.proc w_terminal_OnChildStarted,lpszCmdLine:gpointer
	.shadow
		.if m_lpProcessStartedCallBack
			invoke m_lpProcessStartedCallBack,0, m_hChildProcess, 0,0
		.endif
	.endp 
		Terminal_PrintV macro str___@
		 	invoke w_terminal_print,str___@
		endm
		Terminal_Print_Line macro str___@
		 	invoke w_terminal_print,str$(<13,10,str___@>)
		endm
		Terminal_Print_LineL macro str___@
		 	invoke w_terminal_print,str$(<13,10,str___@,13,10>)
		endm
		Terminal_Print macro str___@
		 	invoke w_terminal_print,str$(str___@)
		endm
	.proc w_terminal_print,lpszBuffer:qword
		local et:_GtkTextIter
	.shadow
		.if w_terminal_buffer
		    gtk_text_buffer_get_end_iter(w_terminal_buffer,addr et)
		    gtk_text_buffer_insert_markup(w_terminal_buffer,addr et, lpszBuffer, -1)
		.endif
	.endp 
	
	.proc w_terminal_OnChildWrite,lpszBuffer:qword
		local et:_GtkTextIter
	.shadow
		.if w_terminal_buffer
  			 gtk_text_buffer_get_end_iter(w_terminal_buffer,addr et)
  			 g_markup_escape_text(lpszBuffer,-1)
  			 gtk_text_buffer_insert_markup(w_terminal_buffer,addr et, rax, -1)
			;invoke gtk_text_buffer_insert_at_cursor,w_terminal_buffer,lpszOutput,-1
			;Terminal_PrintV lpszBuffer ;................................
		.endif
	.endp 
	.proc w_terminal_OnChildStdOutWrite,lpszBuffer:qword
		local et:_GtkTextIter
	.shadow
		.if m_lpProcessStdOutCallBack
			invoke m_lpProcessStdOutCallBack,lpszBuffer
		.else
			.if w_terminal_buffer
				gtk_text_buffer_get_end_iter(w_terminal_buffer,addr et)
				g_markup_escape_text(lpszBuffer,-1)
				gtk_text_buffer_insert_markup(w_terminal_buffer,addr et, rax, -1)
				;invoke gtk_text_buffer_insert_at_cursor,w_terminal_buffer,lpszBuffer,-1
				;Terminal_PrintV lpszBuffer ;................................
			.endif
		.endif
	.endp 
	.proc w_terminal_OnChildStdErrWrite,lpszBuffer:qword
		local et:_GtkTextIter
	.shadow

		.if m_lpProcessStdErrCallBack
			invoke m_lpProcessStdErrCallBack,lpszBuffer
		.else
			.if w_terminal_buffer
				gtk_text_buffer_get_end_iter(w_terminal_buffer,addr et)
				g_markup_escape_text(lpszBuffer,-1)
				gtk_text_buffer_insert_markup(w_terminal_buffer,addr et, rax, -1)
				;Terminal_PrintV lpszBuffer ;................................
			.endif
		.endif
	.endp 
	.proc w_terminal_OnChildTerminate
		local dwExitCode:	DWORD 
		local   lpszBuffer		[1024+1]:byte;
		.if (m_hChildProcess == NULL) 
			mov dwExitCode,-1
		.else
			GetExitCodeProcess(m_hChildProcess, addr dwExitCode)
			.if eax==0
				mov dwExitCode,-1
				sprintf(addr lpszBuffer, "GetExitCodeProcess error: %s \n",rv(_GetLastErrorMsg));
				w_terminal_OnChildStdOutWrite(addr lpszBuffer)
			.else
				.if dwExitCode!=0
					sprintf(addr lpszBuffer, "Process returned %d exit status\n", dwExitCode);
					w_terminal_OnChildStdOutWrite(addr lpszBuffer)
					w_terminal_OnChildStdOutWrite(rv(_GetLastErrorMsg))
				.else
					.if m_lpProcessExitedCallBack
						invoke m_lpProcessExitedCallBack,0, dwExitCode, 0
					.endif			
				.endif 
			.endif
		.endif
	.endp 

	.proc w_terminal_close
		call w_terminal_TerminateChildProcess
	.endp
.data
	w_terminal_lastOutputStdOut		db	65536 dup(?)
	w_terminal_Index_Output_StdOut	dq	0
	.proc w_terminal_Init_Output_From_StdOut
		m2m m_lpProcessStdOutCallBack,w_terminal_Get_Output_From_StdOut
		lea	rax,w_terminal_lastOutputStdOut
		mov w_terminal_Index_Output_StdOut,rax
		mov byte ptr [rax],0
	.endp
	.proc w_terminal_Get_Output_From_StdOut,lpszBuffer:qword
	.shadow
		mov rsi,lpszBuffer
		mov rdi,w_terminal_Index_Output_StdOut
	@@:
		.if byte ptr [rsi]
			.if byte ptr [rsi]<32
				inc rsi
				jmp @B 
			.endif
			.if byte ptr [rsi] > 126
				inc rsi
				jmp @B 
			.endif
			mov al,byte ptr [rsi]
			mov byte ptr [rdi],al
			inc rsi
			inc rdi
			inc w_terminal_Index_Output_StdOut
			jmp @B
		.endif
		mov byte ptr [rdi],0
	.endp 

	.proc w_terminal_Add_Space_To_Buf_StdOut 

	.shadow
		mov rdi,w_terminal_Index_Output_StdOut
		mov byte ptr [rdi],32
		inc rdi
		inc w_terminal_Index_Output_StdOut
		mov byte ptr [rdi],0
	.endp 

	.proc w_terminal_LaunchAndGetOutput,lpszCmdLine:gpointer
	.shadow
		@@:
		.if m_bRunThread
			jmp @B
		.endif
		w_terminal_Initialisation()
		lea	rax,w_terminal_Get_Output_From_StdOut
		mov m_lpProcessStdOutCallBack,rax
		invoke w_terminal_StartChildProcess,lpszCmdLine,FALSE
	.endp 




.proc w_terminal_PrepAndLaunchRedirectedChild,lpszCmdLine:gpointer, hStdOut:gpointer, hStdIn:gpointer, hStdErr:gpointer, bShowChildWindow
	local hProcess:gpointer
	local pi:PROCESS_INFORMATION
	local sui:STARTUPINFO
	local bResult:gpointer
.shadow

	mov hProcess ,GetCurrentProcess();

	RtlZeroMemory(addr sui, SizeOf (STARTUPINFO))
	mov sui.cb 			, SizeOf STARTUPINFO
	mov sui.dwFlags 		, STARTF_USESTDHANDLES  OR STARTF_USESHOWWINDOW;
	m2m sui.hStdOutput 	, hStdOut
	m2m sui.hStdInput  	, hStdIn
	m2m sui.hStdError  	, hStdErr
	.if bShowChildWindow
		mov sui.wShowWindow 	, SW_SHOW
	.else
		mov sui.wShowWindow 	, SW_HIDE;
	.endif

	mov bResult ,CreateProcessA(NULL,lpszCmdLine, NULL, NULL, TRUE,CREATE_NEW_CONSOLE, NULL, NULL, addr sui, addr pi)

	.if (!bResult)
		mov m_bCreateProcessAE,TRUE
		mov m_bRunThread 	, FALSE
		Terminal_Print_Line " CreateProcessA err{" 
		Terminal_PrintV lpszCmdLine 
		Terminal_Print " }" 
		xor rax,rax
		ret
	.endif

	CloseHandle(pi.hThread)

	mov rax ,pi.hProcess
.endp

.proc w_terminal_StartChildProcess, lpszCmdLine:gpointer, bShowChildWindow
	local	hProcess		:gpointer
	local	hStdInWriteTmp	:gpointer
	local	hStdOutReadTmp	:gpointer
	local	hStdErrReadTmp	:gpointer
	local 	sa				:SECURITY_ATTRIBUTES
	local   lpszBuffer		[1024+1]:byte;
	local   dwThreadID		:DWORD
	
.shadow	
	mov	hProcess,GetCurrentProcess()
 
	RtlZeroMemory(addr sa, sizeof( SECURITY_ATTRIBUTES))
	mov sa.nLength, sizeof(SECURITY_ATTRIBUTES)
	mov sa.lpSecurityDescriptor ,0 
	mov sa.bInheritHandle	,-1

	CreatePipe(addr m_hStdIn		, addr hStdInWriteTmp	, addr sa, 0)
	CreatePipe(addr hStdOutReadTmp	, addr m_hStdOut		, addr sa, 0)
 	CreatePipe(addr hStdErrReadTmp	, addr m_hStdErr		, addr sa, 0)

	DuplicateHandle(hProcess, hStdInWriteTmp,hProcess, addr m_hStdInWrite, 0, FALSE, DUPLICATE_SAME_ACCESS)
	DuplicateHandle(hProcess, hStdOutReadTmp,hProcess, addr m_hStdOutRead, 0, FALSE, DUPLICATE_SAME_ACCESS)
	DuplicateHandle(hProcess, hStdErrReadTmp,hProcess, addr m_hStdErrRead, 0, FALSE, DUPLICATE_SAME_ACCESS)

	CloseHandle(hStdInWriteTmp)
	CloseHandle(hStdOutReadTmp)
	CloseHandle(hStdErrReadTmp)
	
	mov m_bRunThread 	, TRUE
	mov m_hExitEvent 	, CreateEventA(NULL, TRUE, FALSE, NULL)
	mov m_hStdOutThread , CreateThread(NULL, 0,addr  w_terminal_StdOutThread,m_hStdOutRead, 0, addr dwThreadID)
	mov m_hStdErrThread , CreateThread(NULL, 0,addr  w_terminal_StdErrThread,m_hStdErrRead, 0, addr dwThreadID)
	

	mov m_hChildProcess , w_terminal_PrepAndLaunchRedirectedChild(lpszCmdLine,	m_hStdOut, m_hStdIn, m_hStdErr, bShowChildWindow)

	.if (m_hChildProcess == NULL)

		mov m_bRunThread 	, FALSE
		sprintf(addr lpszBuffer, "Unable to start  %s\n", lpszCmdLine);
		Terminal_Print_Line "Error:"
		Terminal_PrintV addr lpszBuffer

		CloseHandle(m_hStdIn)
		CloseHandle(m_hStdOut)
		CloseHandle(m_hStdErr)
		mov m_hStdIn , NULL
		mov m_hStdOut, NULL
		mov m_hStdErr , NULL
		xor rax,rax
		ret
	.endif
	mov m_hProcessThread, CreateThread(NULL, 0,addr w_terminal_ProcessThread,0, 0,addr dwThreadID)
	w_terminal_OnChildStarted(lpszCmdLine)
	mov rax, TRUE
.endp

.proc w_terminal_IsChildRunning
	local dwExitCode:	DWORD 
    .if (m_hChildProcess == NULL) 
    	xor rax,rax
    	ret
    .endif
	GetExitCodeProcess(m_hChildProcess, addr dwExitCode)
	.if (dwExitCode == STILL_ACTIVE)
		mov rax,TRUE
	.else
		mov rax,FALSE
	.endif
	ret 
.endp

.proc w_terminal_TerminateChildProcess

	mov m_bRunThread , FALSE
	SetEvent(m_hExitEvent)
	Sleep(500)

	.if (m_hProcessThread != NULL)
		WaitForSingleObject(m_hProcessThread, 1000)  
		mov m_hProcessThread , NULL;
	.endif
	.if (m_hStdIn != NULL)
		CloseHandle(m_hStdIn)
		mov m_hStdIn , NULL
	.endif
	.if (m_hStdOut != NULL)
		CloseHandle(m_hStdOut)
		mov m_hStdOut , NULL
	.endif
	.if (m_hStdErr != NULL)
		CloseHandle(m_hStdErr)
		mov m_hStdErr , NULL
	.endif

    Sleep(100)

	.if (m_hStdInWrite != NULL)
		CloseHandle(m_hStdInWrite)
		mov m_hStdInWrite , NULL
	.endif
	.if (m_hStdOutRead != NULL)
		CloseHandle(m_hStdOutRead)
		mov m_hStdOutRead , NULL
	.endif
	.if (m_hStdErrRead != NULL)
		CloseHandle(m_hStdErrRead)
		mov m_hStdErrRead , NULL
	.endif

    Sleep(100);

	.if (m_hStdOutThread != NULL)
		WaitForSingleObject(m_hStdOutThread, 1000) 
		mov m_hStdOutThread , NULL
	.endif
	.if (m_hStdErrThread != NULL)
		WaitForSingleObject(m_hStdErrThread, 1000) 
		mov m_hStdErrThread , NULL
	.endif

    Sleep(100);

	.if (w_terminal_IsChildRunning())
		TerminateProcess(m_hChildProcess, 1)
		WaitForSingleObject(m_hChildProcess, 1000)
    .endif
	mov m_hChildProcess , NULL;
	.if (m_hExitEvent != NULL)
		CloseHandle(m_hExitEvent)
	.endif
	mov m_hExitEvent , NULL
	
.endp

.proc w_terminal_StdOutThread,hStdOutRead:gpointer
	local  nBytesRead:QWORD
	local  lpszBuffer [1024+1]:BYTE
.shadow
	@StdOut_:
		.if ReadFile(m_hStdOutRead,addr lpszBuffer, 1024,	addr nBytesRead, NULL) 
			.if nBytesRead
				lea rsi,lpszBuffer
				add rsi,nBytesRead
				mov byte ptr [rsi],0 
				w_terminal_OnChildStdOutWrite(addr lpszBuffer)
				jmp @StdOut_
			.else
				.if GetLastError() == ERROR_BROKEN_PIPE
					;.BREAK			
				.else
					;ASSERT(FALSE);	// Something bad happened.
				.endif			
			.endif
		.endif
	.if m_bRunThread
		jmp @StdOut_
	.endif
	xor rax,rax
	ret 
.endp

.proc w_terminal_StdErrThread, hStdErrRead:gpointer
	local  nBytesRead:QWORD
	local  lpszBuffer[1024+1]:BYTE
.shadow
	@StdErr_:
		.if ReadFile(m_hStdErrRead,addr lpszBuffer, 1024,addr nBytesRead, NULL) 
			.if nBytesRead
				lea rsi,lpszBuffer
				add rsi,nBytesRead
				mov byte ptr [rsi],0 
				w_terminal_OnChildStdErrWrite(addr lpszBuffer)
				jmp	@StdErr_
			.else
				.if GetLastError() == ERROR_BROKEN_PIPE
					;.BREAK			
				.else
					; Something bad happened.
				.endif			
			.endif
		.endif
	.if m_bRunThread
		jmp	@StdErr_
	.endif
	xor rax,rax
	ret 
.endp


.proc w_terminal_ProcessThread
	local hWaitHandle[2]:gpointer

	lea rsi,hWaitHandle
	m2m gpointer ptr [rsi],m_hExitEvent
	m2m gpointer ptr [rsi+sizeof(gpointer)],m_hChildProcess

	.WHILE	m_bRunThread
		WaitForMultipleObjects(2,addr hWaitHandle, FALSE, 1)
		.if rax==WAIT_OBJECT_0 + 0	; exit on event
				.BREAK
		.elseif rax==WAIT_OBJECT_0 + 1; child process exit
				mov m_bRunThread , FALSE;
				.BREAK
		.endif
	.ENDW
	.if !m_bCreateProcessAE
		w_terminal_OnChildTerminate()
	.endif
	xor rax,rax
	ret 
.endp


.proc w_terminal_WriteChildStdIn, lpszInput:gpointer
	local nBytesWrote:DWORD
	local _Length:QWORD
.shadow
	 ;
	 mov _Length , strlen(lpszInput)
	.if (m_hStdInWrite != NULL && _Length > 0)
		.if !(WriteFile(m_hStdInWrite, lpszInput, _Length, addr nBytesWrote, NULL))
			.if GetLastError() == ERROR_NO_DATA
				;Pipe was closed (do nothing).
			.else
				;Something bad happened.
			.endif
		.endif
	.endif
.endp

 




