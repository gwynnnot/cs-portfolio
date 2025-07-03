global _start

section .data
    NULL equ 0
    SYS_EXIT equ 60
    string1 db 'bored girl', NULL       
    string2 db 'robed girl', NULL       
    anagram db 'Y', NULL
    strlen dq 0                         

section .text
_start:
    mov rdi, string1                    ; move address of string1 into rdi
    mov rsi, strlen                     ; move address of strlen into rdi
    call get_strlen                     ; jumps to get_strlen

    mov rcx, qword[strlen]              ; move the length of string1 into rcx
    mov rsi, string1                    ; move address of string1 into rsi
    mov rdi, string2                    ; move address of string2 into rdi
    mov rbx, 0                          ; counter for matched characters
    mov rsp, 0                          ; counter for number of characters in a string
    cld                                 ; flag for incrementing
    lodsb                               ; initiaze al
    jmp checker                         ; jumps to checker

initialize:
    mov al, '@'                         ; set value of al to @
    sub rdi, rbx                        ; adjust rdi to point to matched character position in string2
    stosb                               ; replace character of string2 with the character it matched in string1 to prevent from repeating
    mov rdi, string2                    ; reset rdi
    mov rbp, 0                          ; set rbp to 0, helps checker for length of string
    lodsb                               ; initialize al
    inc rsp                             ; increment rsp
    cmp rsp, rcx                        ; if rsp is equal to rcx, every character in string1 has been iterated over
    je exit_here                        ; exits if rsp and rcx are equal 

checker:
    inc rbx                             ; increment rbx everytime a checker is called (matched characters)
    scasb                               ; cmp al with characters in rdi
    je initialize                       ; if equal, jump to initialize
    inc rbp                             ; if not equal, increment rbp
    mov rbx, 0                          ; reset rbx back to 0 if no character matches with another character
    cmp rbp, rcx                        ; check rbp if all characters have been checked
    je stop                             ; if yes, jump to stop and string is not an anagram
    jmp checker                         ; loops

stop:
    mov byte[anagram], 'N'              ; strings are not anagrams
    jmp exit_here

exit_here:
    mov rax, SYS_EXIT
    xor rdi, rdi
    syscall

get_strlen:
    len_loop:
        mov al, byte[rdi]               ; move byte from rdi into al
        cmp al, NULL                    ; cmp al with NULL
        je return                       ; if equal, return

        inc rdi                         ; increment rdi to next byte
        inc byte[rsi]                   ; increment counter for string length
        jmp len_loop                    ; jumps to len_loop
    return:
        ret