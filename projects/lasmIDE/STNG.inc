.data
    __bufForRead        DB  10000    DUP(0)
.data
    SettingFileName     DB  "setting.stg",  0
    hSettingFile        DQ  0
    slist               DQ  0    
.code

enum    stng_EOS, \         
        stng_paned1_Position, \
        stng_paned2_Position, \
        stng_show_line_numbre, \
        stng_main_window_maximised , \
        stng_main_window_x , \
        stng_main_window_y , \
        stng_main_window_w, \
        stng_main_window_h        
        

    STNG_Get PROC _setting:dword,_pValue:gpointer
        Local l_setting:dword
        Local l__pValue:gpointer
        local n_bytes:dword
        local pfname :gpointer
        mov l_setting,_setting
        mov l__pValue,_pValue
        
        mov pfname,rv(g_build_filename,firstworkingdir,addr SettingFileName,0)       
        invoke _open,pfname,O_RDONLY ,0     
        .if (sdword ptr eax < 0)	
            xor rax,rax
            ret
        .else
            mov hSettingFile,rax
            invoke _read,hSettingFile,addr __bufForRead,10000
            .if rax==0
            invoke printf,str$(<13,10,"get_setting _read 0={%d}">),rax 
                invoke _close,hSettingFile
                xor rax,rax
                ret
            .else
                mov n_bytes,eax
                lea rdx,__bufForRead
                mov eax,l_setting
                xor rcx,rcx
             @@:
                cmp qword ptr [rdx+rcx],stng_EOS
                je  @F
                cmp eax,dword ptr [rdx+rcx]
                je  @F
                add rcx,8
                cmp ecx,n_bytes
                jl  @B                
             @@:
                cmp ecx,n_bytes
                jl  @F
                    invoke _close,hSettingFile
                    xor rax,rax
                    ret                
             @@:cmp qword ptr [rdx+rcx],stng_EOS
                jne  @F
                    invoke _close,hSettingFile
                    xor rax,rax
                    ret                
             @@:add rcx,4
                mov eax,dword ptr [rdx+rcx]
                mov rcx,l__pValue
                mov dword ptr [rcx],eax
                invoke _close,hSettingFile
                mov rax,-1
                ret
            .endif            
        .endif
         invoke g_free,pfname        
        ret
    STNG_Get ENDP
    
    STNG_Set PROC _setting:dword,_Value:dword
        Local l_setting:dword
        Local l_Value:dword
        local n_bytes:qword
        local pfname :gpointer

        mov l_setting,_setting
        mov l_Value,_Value
        mov pfname,rv(g_build_filename,firstworkingdir,addr SettingFileName,0)
        invoke _open,pfname,O_RDONLY ,0     
        .IF (sdword ptr eax < 0)	
            mov n_bytes,16
            lea rdx,__bufForRead        
            mov ecx,l_Value           
            mov eax,l_setting
            mov dword ptr [rdx],eax
            mov dword ptr [rdx+4],ecx  
            mov qword ptr [rdx+8],0 
        .else
            mov hSettingFile,rax
            invoke _read,hSettingFile,addr __bufForRead,10000
            .if rax==0
                invoke _close,hSettingFile
                ret
            .else
                mov n_bytes,rax
                invoke _close,hSettingFile
                lea rdx,__bufForRead
                mov eax,l_setting
                xor rcx,rcx
             @@:
                cmp eax,dword ptr [rdx+rcx]
                je  @F
                cmp dword ptr [rdx+rcx],stng_EOS
                je  @F
                add rcx,8
                cmp rcx,n_bytes
                jl  @B                
               @@:
                cmp dword ptr [rdx+rcx],stng_EOS
                je  @F
                    add rdx,rcx
                    add rdx,4
                    mov eax,l_Value
                    mov dword ptr [rdx],eax
                    jmp _@write
               @@:
                ;not found:insert at last
                    add rdx,rcx
                    mov ecx,l_Value
                    mov eax,l_setting
                    mov dword ptr [rdx],eax
                    mov dword ptr [rdx+4],ecx
                    mov Qword ptr [rdx+8],0
                    add n_bytes,8
              
            .endif            
        .endif
       _@write:
            invoke _open,pfname,O_WRONLY or O_CREAT , S_IRWXU or S_IRWXG or S_IRWXO
            mov hSettingFile,rax
            invoke _write,hSettingFile,addr __bufForRead,n_bytes
            invoke _close,hSettingFile
            invoke g_free,pfname        
            xor rax,rax
            ret                      
    STNG_Set ENDP
