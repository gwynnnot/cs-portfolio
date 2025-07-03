global _start

section .data
    SYS_EXIT equ 60
    num db 127                 ; check if 2 is a prime number
    isPrime db 1                ; set isPrime to 1

section .text
_start:
    mov cl, byte[num]   ; move num to al
    
prime_check:
    dec cl              ; decrement since it will used for dividing num
    cmp cl, 2           ; compare al to 2
    jl exit_here        ; jump to exit_here if less than 2

    mov ah, 0           ; rem = 0
    mov al, byte[num]
    div cl              ; quo = al

    cmp ah, 0           ; composite if remainder is 0
    je not_prime        

    jmp prime_check

not_prime:
    dec byte[isPrime]   ; set isPrime to 0 if num is composite

exit_here:
    mov rax, SYS_EXIT
    xor rdi, rdi
    syscall