; ============================================================
; try.inc  --  TRY / CATCH / ENDTRY / THROW  (UASM, elf64, SysV)
; Include once at the top of the file, call TryRuntime once (anywhere
; in the .code/.data area, outside any proc), then TryInit from main.
; Catch reads:  __try_sig (dword)  __try_addr (qword)  __try_rip (qword)
; ============================================================
sigaction    PROTO SYSTEMV :QWORD, :QWORD, :QWORD
sigemptyset  PROTO SYSTEMV :QWORD
sigaltstack  PROTO SYSTEMV :QWORD, :QWORD
signal       PROTO SYSTEMV :QWORD, :QWORD
dprintf      PROTO SYSTEMV :QWORD, :QWORD, :VARARG
dladdr       PROTO SYSTEMV :QWORD, :QWORD
open         PROTO SYSTEMV :QWORD, :QWORD, :VARARG
lseek        PROTO SYSTEMV :QWORD, :QWORD, :QWORD
mmap         PROTO SYSTEMV :QWORD, :QWORD, :QWORD, :QWORD, :QWORD, :QWORD
munmap       PROTO SYSTEMV :QWORD, :QWORD
;close        PROTO SYSTEMV :QWORD
extern __executable_start:byte
extern etext:byte

TRYF_SIZE    equ 64          ; prev, catch, rbp, rbx, r12, r13, r14, r15
__tryCnt     = 0
__tryDepth   = 0

TryRuntime macro
    .data
__try_top      dq 0          ; top of the TRY frame chain
__try_sig      dq 0
__try_idx      dd 0
__try_code     dd 0          ; si_code (7FFFFFFFh = software THROW)
__try_fd       dd 2          ; where TryDump writes (stderr)
__try_regs     dq 23 dup(0)  ; copy of ucontext gregs at fault time
__d_dli        dq 4 dup(0)   ; Dl_info
__d_cnt        dd 0
__d_fd         dd 0
__try_stkok    dd 0
__try_stk      dq 96 dup(0)  ; copy of the stack at fault time
__d_map        dq 0          ; mmap of /proc/self/exe (for .symtab lookup)
__d_maplen     dq 0
__d_exe        	db "/proc/self/exe",0
__d_hdr  		db "=== fault ===",10,0
__d_thr  		db "software THROW, code=%d",10,0
__d_sig  		db "signal %d (%s)  si_code=%d  %s",10,0
__d_addr 		db "fault address: 0x%lx",10,0
__d_rip  		db "fault rip:",10,0
__d_rfmt 		db "%s=%016lx ",0
__d_nl   		db 10,0
__d_trh  		db "call trace (stack scan, candidates):",10,0
__d_ovf  		db "(no stack snapshot: stack overflow suspected)",10,0
__d_sym  		db "  0x%lx  <%s+0x%lx>",10,0
__d_nosym 		db "  0x%lx",10,0
__d_rn   		db "r8 ",0,"r9 ",0,"r10",0,"r11",0,"r12",0,"r13",0,"r14",0,"r15",0
         		db "rdi",0,"rsi",0,"rbp",0,"rbx",0,"rdx",0,"rax",0,"rcx",0,"rsp",0,"rip",0
__d_s4   		db "SIGILL",0
__d_s6   		db "SIGABRT",0
__d_s7   		db "SIGBUS",0
__d_s8   		db "SIGFPE",0
__d_s11  		db "SIGSEGV",0
__d_sx   		db "?",0
__d_c1   		db "unmapped address",0
__d_c2   		db "access denied (permissions)",0
__d_f1   		db "integer divide by zero",0
__d_f2   		db "integer overflow",0
__d_cx   		db "-",0
__try_addr     	dq 0          ; fault address (si_addr)
__try_rip      	dq 0          ; RIP at the time of the fault
__try_unhandled dq 0         ; optional: void hook(int sig, void *addr, void *rip)
__try_sigs     	dd 4, 6, 7, 8, 11, 0      ; SIGILL SIGABRT SIGBUS SIGFPE SIGSEGV
__try_ss       	dq 0, 0, 0                ; stack_t
__try_sa       	db 152 dup(0)             ; glibc struct sigaction
    .data?
    align 16
__try_altstk   db 65536 dup(?)
    .code

; void handler(int sig, siginfo_t *si, ucontext_t *uc)
__try_handler proc
    mov  rax, __try_top
    mov  ecx, edi
    mov  __try_sig, rcx
    mov  rcx, [rsi+16]                 ; si_addr
    mov  __try_addr, rcx
    mov  rcx, [rdx+168]                ; gregs[REG_RIP]
    mov  __try_rip, rcx
    mov  ecx, [rsi+8]                  ; si_code
    mov  __try_code, ecx
    lea  r8, [rdx+40]                  ; copy gregs for TryDump
    lea  r9, __try_regs
    xor  r10d, r10d
__try_cp:
    mov  rcx, [r8+r10*8]
    mov  [r9+r10*8], rcx
    inc  r10
    cmp  r10, 23
    jb   __try_cp
    mov  dword ptr __try_stkok, 0      ; snapshot the faulting stack (skipped on overflow)
    mov  r8, [rdx+160]                 ; saved RSP
    mov  r9, __try_addr
    sub  r9, r8
    add  r9, 65536
    cmp  r9, 131072
    jb   __try_nostk
    lea  r9, __try_stk
    xor  r10d, r10d
__try_cs:
    mov  rcx, [r8+r10*8]
    mov  [r9+r10*8], rcx
    inc  r10
    cmp  r10, 96
    jb   __try_cs
    mov  dword ptr __try_stkok, 1
__try_nostk:
    test rax, rax
    jz   __try___try_noframe
    mov  rcx, [rax+8]                  ; catch address
    mov  [rdx+168], rcx                ; RIP := catch
    mov  [rdx+160], rax                ; RSP := frame
    ret                                ; sigreturn -> resumes at catch
__try___try_noframe:
    push rbp
    mov  rbp, rsp
    and  rsp, -16
    mov  rax, __try_unhandled
    test rax, rax
    jz   __try_nohook
    mov  rsi, __try_addr
    mov  rdx, __try_rip
    call rax                           ; (edi still = sig)
    mov  edi, dword ptr __try_sig
__try_nohook:
    mov  edi, dword ptr __try_sig
    xor  esi, esi                      ; SIG_DFL
    call signal
    mov  rsp, rbp
    pop  rbp
    ret                                ; re-fault -> default action
__try_handler endp

; software throw: edi = code (stored in __try_sig); does not return
__try_throw proc
    mov  eax, edi
    mov  __try_sig, rax
    mov  qword ptr __try_addr, 0
    mov  eax, 7FFFFFFFh
    mov  __try_code, eax
    mov  rax, __try_top
    test rax, rax
    jz   __try_nofr
    mov  rsp, rax
    jmp  qword ptr [rax+8]
__try_nofr:
    ud2
__try_throw endp


; map our own executable read-only (to read .symtab)
__try_symload proc
    push rbp
    mov  rbp, rsp
    and  rsp, -16
    mov  qword ptr __d_map, 0
    lea  rdi, __d_exe
    xor  esi, esi
    xor  eax, eax
    call open
    test eax, eax
    js   __tl_out
    mov  __d_fd, eax
    mov  edi, eax
    xor  esi, esi
    mov  edx, 2                        ; SEEK_END
    call lseek
    test rax, rax
    jle  __tl_close
    mov  __d_maplen, rax
    xor  edi, edi
    mov  rsi, rax
    mov  edx, 1                        ; PROT_READ
    mov  ecx, 2                        ; MAP_PRIVATE
    mov  r8d, __d_fd
    xor  r9d, r9d
    call mmap
    cmp  rax, -1
    je   __tl_close
    mov  __d_map, rax
__tl_close:
    mov  edi, __d_fd
    call close
__tl_out:
    mov  rsp, rbp
    pop  rbp
    ret
__try_symload endp

__try_symunload proc
    push rbp
    mov  rbp, rsp
    and  rsp, -16
    mov  rdi, __d_map
    test rdi, rdi
    jz   __tu_out
    mov  rsi, __d_maplen
    call munmap
    mov  qword ptr __d_map, 0
__tu_out:
    mov  rsp, rbp
    pop  rbp
    ret
__try_symunload endp

; rdi = address  ->  rax = name pointer (0 if none), rdx = offset inside it
; nearest preceding .symtab symbol (NOTYPE/FUNC); names starting with "__" are skipped
__try_find proc
    push rbx
    push r12
    mov  r8, __d_map
    test r8, r8
    jz   __tf_none
    movzx eax, word ptr [r8+16]        ; e_type
    cmp  eax, 3                        ; ET_DYN (PIE): remove load base
    jne  __tf_abs
    lea  rax, __executable_start
    sub  rdi, rax
__tf_abs:
    mov  r9, [r8+40]                   ; e_shoff
    add  r9, r8
    movzx r12d, word ptr [r8+58]       ; e_shentsize
    movzx r11d, word ptr [r8+60]       ; e_shnum
    xor  ecx, ecx
__tf_sec:
    cmp  ecx, r11d
    jae  __tf_none
    mov  eax, ecx
    imul rax, r12
    lea  rsi, [r9+rax]
    mov  eax, [rsi+4]                  ; sh_type
    cmp  eax, 2                        ; SHT_SYMTAB
    je   __tf_found
    inc  ecx
    jmp  __tf_sec
__tf_found:
    mov  r10d, [rsi+40]                ; sh_link -> string table section
    mov  rax, [rsi+32]                 ; sh_size
    xor  edx, edx
    mov  ecx, 24
    div  rcx
    mov  r11, rax                      ; symbol count
    mov  rbx, [rsi+24]                 ; sh_offset
    add  rbx, r8                       ; first symbol
    mov  eax, r10d
    imul rax, r12
    lea  rsi, [r9+rax]
    mov  rsi, [rsi+24]
    add  rsi, r8                       ; string table
    xor  r9d, r9d                      ; best name
    xor  edx, edx                      ; best value
    xor  ecx, ecx
__tf_loop:
    cmp  rcx, r11
    jae  __tf_done
    mov  rax, [rbx+8]                  ; st_value
    cmp  rax, rdi
    ja   __tf_next
    cmp  rax, rdx
    jb   __tf_next
    movzx r10d, word ptr [rbx+6]       ; st_shndx
    test r10d, r10d
    jz   __tf_next
    cmp  r10d, 0FF00h
    jae  __tf_next
    movzx r10d, byte ptr [rbx+4]       ; st_info
    and  r10d, 15
    cmp  r10d, 0
    je   __tf_ok
    cmp  r10d, 2
    jne  __tf_next
__tf_ok:
    mov  r10d, [rbx]                   ; st_name
    test r10d, r10d
    jz   __tf_next
    add  r10, rsi
    cmp  word ptr [r10], 5F5Fh         ; "__" = internal labels
    je   __tf_next
    mov  rdx, rax
    mov  r9, r10
__tf_next:
    add  rbx, 24
    inc  rcx
    jmp  __tf_loop
__tf_done:
    test r9, r9
    jz   __tf_none
    mov  rax, r9
    sub  rdi, rdx
    mov  rdx, rdi
    jmp  __tf_out
__tf_none:
    xor  eax, eax
    xor  edx, edx
__tf_out:
    pop  r12
    pop  rbx
    ret
__try_find endp

__try_sym proc
    push rbp
    mov  rbp, rsp
    and  rsp, -16
    push rbx
    push r12
    mov  rbx, rdi
    call __try_find
    test rax, rax
    jz   __ts_dl
    mov  rcx, rax                      ; name
    mov  r8, rdx                       ; offset
    mov  edi, __try_fd
    lea  rsi, __d_sym
    mov  rdx, rbx
    xor  eax, eax
    call dprintf
    jmp  __ts_out
__ts_dl:
    mov  rdi, rbx
    lea  rsi, __d_dli
    call dladdr
    test eax, eax
    jz   __ts_none
    lea  rax, __d_dli
    mov  rcx, [rax+16]                 ; dli_sname
    test rcx, rcx
    jz   __ts_none
    mov  r8, rbx
    sub  r8, [rax+24]                  ; offset from dli_saddr
    mov  edi, __try_fd
    lea  rsi, __d_sym
    mov  rdx, rbx
    xor  eax, eax
    call dprintf
    jmp  __ts_out
__ts_none:
    mov  edi, __try_fd
    lea  rsi, __d_nosym
    mov  rdx, rbx
    xor  eax, eax
    call dprintf
__ts_out:
    pop  r12
    pop  rbx
    mov  rsp, rbp
    pop  rbp
    ret
__try_sym endp

; call from a CATCH block: dumps signal, address, registers, procedure, call trace
TryDump proc
    push rbp
    mov  rbp, rsp
    and  rsp, -16
    push rbx
    push r12
    mov  edi, __try_fd
    lea  rsi, __d_hdr
    xor  eax, eax
    call dprintf
    mov  eax, __try_code
    cmp  eax, 7FFFFFFFh
    jne  __td_hw
    mov  edi, __try_fd
    lea  rsi, __d_thr
    mov  edx, dword ptr __try_sig
    xor  eax, eax
    call dprintf
    jmp  __td_out
__td_hw:
    call __try_symload
    mov  eax, dword ptr __try_sig       ; signal name
    lea  rcx, __d_sx
    cmp  eax, 4
    jne  __td_n6
    lea  rcx, __d_s4
__td_n6:
    cmp  eax, 6
    jne  __td_n7
    lea  rcx, __d_s6
__td_n7:
    cmp  eax, 7
    jne  __td_n8
    lea  rcx, __d_s7
__td_n8:
    cmp  eax, 8
    jne  __td_n11
    lea  rcx, __d_s8
__td_n11:
    cmp  eax, 11
    jne  __td_nn
    lea  rcx, __d_s11
__td_nn:
    lea  r9, __d_cx                     ; si_code text (SEGV / FPE only)
    cmp  eax, 11
    je   __td_cc
    cmp  eax, 8
    jne  __td_cd
__td_cc:
    mov  r10d, __try_code
    cmp  r10d, 1
    jne  __td_c2
    lea  r9, __d_c1
    cmp  eax, 11
    je   __td_cd
    lea  r9, __d_f1
__td_c2:
    cmp  r10d, 2
    jne  __td_cd
    lea  r9, __d_c2
    cmp  eax, 11
    je   __td_cd
    lea  r9, __d_f2
__td_cd:
    mov  edi, __try_fd
    lea  rsi, __d_sig
    mov  edx, eax
    mov  r8d, __try_code
    xor  eax, eax
    call dprintf
    mov  edi, __try_fd
    lea  rsi, __d_addr
    mov  rdx, __try_addr
    xor  eax, eax
    call dprintf
    mov  edi, __try_fd
    lea  rsi, __d_rip
    xor  eax, eax
    call dprintf
    lea  rax, __try_regs
    mov  rdi, [rax+128]                 ; saved RIP
    call __try_sym
    ; registers
    xor  r12d, r12d
__td_rl:
    lea  rax, __d_rn
    lea  rdx, [rax+r12*4]
    lea  rax, __try_regs
    mov  rcx, [rax+r12*8]
    mov  edi, __try_fd
    lea  rsi, __d_rfmt
    xor  eax, eax
    call dprintf
    mov  eax, r12d
    and  eax, 3
    cmp  eax, 3
    jne  __td_nonl
    mov  edi, __try_fd
    lea  rsi, __d_nl
    xor  eax, eax
    call dprintf
__td_nonl:
    inc  r12d
    cmp  r12d, 17
    jb   __td_rl
    mov  edi, __try_fd
    lea  rsi, __d_nl
    xor  eax, eax
    call dprintf
    ; stack scan (on the snapshot taken by the handler)
    mov  eax, __try_stkok
    test eax, eax
    jnz  __td_scan
    mov  edi, __try_fd
    lea  rsi, __d_ovf
    xor  eax, eax
    call dprintf
    jmp  __td_out
__td_scan:
    mov  edi, __try_fd
    lea  rsi, __d_trh
    xor  eax, eax
    call dprintf
    lea  rbx, __try_stk
    xor  r12d, r12d
    mov  dword ptr __d_cnt, 0
__td_sl:
    mov  rdi, [rbx+r12*8]
    lea  rax, __executable_start
    cmp  rdi, rax
    jb   __td_sn
    lea  rax, etext
    cmp  rdi, rax
    jae  __td_sn
    call __try_sym
    inc  dword ptr __d_cnt
    mov  eax, __d_cnt
    cmp  eax, 16
    jae  __td_out
__td_sn:
    inc  r12d
    cmp  r12d, 96
    jb   __td_sl
__td_out:
    call __try_symunload
    pop  r12
    pop  rbx
    mov  rsp, rbp
    pop  rbp
    ret
TryDump endp

TryInit proc
    push rbp
    mov  rbp, rsp
    and  rsp, -16
    lea  rax, __try_altstk
    mov  qword ptr __try_ss, rax
    lea  rdi, __try_ss
    mov  qword ptr [rdi+16], 65536
    xor  esi, esi
    call sigaltstack
    lea  rax, __try_handler
    mov  qword ptr __try_sa, rax
    lea  rdi, __try_sa
    add  rdi, 8
    call sigemptyset
    lea  rax, __try_sa
    mov  dword ptr [rax+136], 4 or 08000000h        ; SA_SIGINFO|SA_ONSTACK
    mov  dword ptr __try_idx, 0
__try_nextsig:
    lea  rax, __try_sigs
    mov  ecx, __try_idx
    mov  edi, [rax+rcx*4]
    test edi, edi
    jz   __try_done
    lea  rsi, __try_sa
    xor  edx, edx
    call sigaction
    inc  dword ptr __try_idx
    jmp  __try_nextsig
__try_done:
    mov  rsp, rbp
    pop  rbp
    ret
TryInit endp
endm

; ---------- helpers (label names built from the counter) ----------
__SetId macro d, v
    __tryId&d = v
endm
__LeaCatch macro n
    lea  rax, __catch_&n
endm
__CatchBody macro n
    pop  __try_top                     ; normal path: unlink frame
    add  rsp, TRYF_SIZE-8
    jmp  __endtry_&n
__catch_&n:                            ; here RSP = frame (set by the handler)
    mov  rbp, [rsp+16]
    mov  rbx, [rsp+24]
    mov  r12, [rsp+32]
    mov  r13, [rsp+40]
    mov  r14, [rsp+48]
    mov  r15, [rsp+56]
    pop  __try_top
    add  rsp, TRYF_SIZE-8
endm
__CatchEnd macro n
__endtry_&n:
endm
__CatchD macro d
    __CatchBody %__tryId&d
endm
__EndD macro d
    __CatchEnd %__tryId&d
endm

TRY macro
    __tryCnt = __tryCnt + 1
    __tryDepth = __tryDepth + 1
    __SetId %__tryDepth, %__tryCnt
    push r15
    push r14
    push r13
    push r12
    push rbx
    push rbp
    __LeaCatch %__tryCnt
    push rax
    push __try_top
    mov  __try_top, rsp
endm

CATCH macro
    __CatchD %__tryDepth
endm

ENDTRY macro
    __EndD %__tryDepth
    __tryDepth = __tryDepth - 1
endm

THROW macro code
    mov  edi, code
    call __try_throw
endm
