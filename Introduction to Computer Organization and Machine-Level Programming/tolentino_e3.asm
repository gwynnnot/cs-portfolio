global _start

section .data
    SYS_EXIT equ 60
    ; a db 7 
    ; b db 15
    ; c db 21
    a db 15
    b db 7
    c db 21
    largestNum db 0
    largestInput db "N"

section .text
_start:

    mov al, byte[a]             ; move a to register al
    cmp al, byte[b]             ; compare register al to b
    ja isAboveA                 ; a is greater than b

    mov bl, byte[b]             ; move b to register bl
    cmp bl, byte[c]             ; compare register bl to c
    ja isLargestB                 ; b is greater than c

    mov cl, byte[c]             ; move c to register cl
    jmp isLargestC              ; jump if conditions above are false

isAboveA:
    cmp al, byte[c]             ; compare register al to c
    ja isLargestA               ; a is also greater than c

    jmp isLargestC      ; else, C is largest

isLargestA:
    mov byte[largestNum], al    ; move value of al to largestNum
    mov byte[largestInput], "A" ; a > b & c

    jmp exit_here       ;   

isLargestB:
    mov byte[largestNum], bl    ; move value of bl to largestNum
    mov byte[largestInput], "B" ; b > c & a

    jmp exit_here       ;

isLargestC:       
    mov cl, byte[c]             ; move c to register cl
    mov byte[largestNum], cl    ; move value of cl to largestNum
    mov byte[largestInput], "C" ; c > a & b

    jmp exit_here

exit_here:
    mov rax, SYS_EXIT
    xor rdi, rdi
    syscall