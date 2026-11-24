include try.inc
    TryRuntime
    .code
public level2, level1, overflow
level2 proc public
    xor eax, eax
    mov qword ptr [rax+8], 5       ; the crash
    ret
level2 endp
level1 proc public
    call level2
    ret
level1 endp
overflow proc public
    sub rsp, 4096-8
    mov byte ptr [rsp], 1
    call overflow
    add rsp, 4096-8
    ret
overflow endp
main proc public
    call TryInit
    TRY
        call level1
    CATCH
        call TryDump
    ENDTRY
    TRY
        mov ecx, 0
        mov eax, 1
        xor edx, edx
        div ecx
    CATCH
        call TryDump
    ENDTRY
    TRY
        call overflow
    CATCH
        call TryDump
    ENDTRY
    TRY
        THROW 42
    CATCH
        call TryDump
    ENDTRY
    xor eax, eax
    ret
main endp
end
