global _start

section .data
    SYS_EXIT equ 60

    dividend dq 123456789
    divisor dq 54321
    quo dq 0

section .text
_start:
    mov rdi, qword[dividend]    ; store the dividend to the first parameter
    mov rsi, qword[divisor]     ; store the divisor to the second parameter
    call divide                 ; call the function divide
    mov qword[quo], rax         ; value is stored in rax upon return

exit_here: 
    mov rax, SYS_EXIT
    xor rdi, rdi
    syscall

divide:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    mov r10, 0  
              
    looping:
        sub rdi, rsi 
        cmp rdi, 0
        jl exit_loop
        inc r10           ; temporary storage for rax
        jmp looping

    exit_loop:            ; deallocate stack
        add rsp, 8
        pop rbp
        mov rax, r10

        ret



