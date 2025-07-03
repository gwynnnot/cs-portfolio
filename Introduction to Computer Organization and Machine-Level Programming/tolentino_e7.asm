global _start

section .data
    SYS_EXIT equ 60
    all_negative db 0
    num_arr dw 0,-2,-3,-4,-5
    largest dw -1

section .text
_start:
    mov rax, 0                          ; return value for largest number
    mov rsi, 0                          ; negative counter
    mov rcx, 0                          ; counter
    mov r8, 0                           ; index value
    mov rdi, num_arr                    ; move address of num_arr into rdi 
    call checker                        ; jump to checker
    mov qword[largest], rax             ; move value in rax to largest
    cmp rax, -1                         ; compare rax with -1
    je last                             ; if equal, jump to last
    jmp exit_here                       

last:
    mov byte[all_negative], 1           ; move 1 into all_negative if there is no positive number

exit_here:
    mov rax, SYS_EXIT
    xor rdi, rdi
    syscall

checker:
    cmp word[rdi+rsi*2], 0              ; check if any of the array elements is negative
    jl negative                         ; if less than 0, jump to negative
    jmp compare                         ; jump to compare

compare:
    mov ax, word[rdi+rcx*2]             ; move array element to ax           
    cmp ax, word[rdi+r8*2]              ; compare array element with another
    jl less                             ; if less than 0, jump to less
    inc r8                              ; if not less, increment r8 to check other elements 
    cmp r8, 4                           ; if r8 is 4, it means r8 has reached all elements in index
    jg positive_return                  ; if greater, jum to positive_return
    jmp compare                         ; jump to compare

less:                                   
    mov rcx, r8                         ; move r8 to rcx
    mov r8, 0                           ; reset r8
    jmp compare                         ; jump to compare

positive_return:                        
    ret

negative:
    inc rsi                             ; increment rsi (negative counter) by 1 so it can also move onto next element of array
    cmp rsi, 4                          ; check if rsi has reached the last index
    jg negative_return                  ; jump to negative_return if everything is negative
    jmp checker

negative_return:                        ; set rdx and rax to 1 and -1
    mov rax, -1                         ; move -1 into rax if there is no positive number
    ret