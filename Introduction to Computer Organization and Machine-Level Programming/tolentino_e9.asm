global _start

section .data
    LF equ 10
    NULL equ 0
    STDOUT equ 1
    SYS_WRITE equ 1
    STDIN equ 0
    SYS_READ equ 0
    SYS_EXIT equ 60

    menu db "************MENU***********", LF, "[1] Convert to Minutes", LF, "[2] Convert to Hours", LF, "[0] Exit", LF, "***************************", LF, "Choice: ", NULL     ;menu
    menuLength equ $-menu

    invalidChoice db LF, "Invalid choice!", LF                  ; prompt for invalid choice
	invalidChoiceLength equ $-invalidChoice

    enterSec db "Enter time in seconds (5-digits): ", NULL      ; prompt for asking user for input seconds
    enterSecLength equ $-enterSec

    newLine db LF, NULL             ; for newLine
    newLineLength equ $-newLine

    choice db 0                     ; storage for choice
    ans dq 0                        ; storage for result
    d1 dq 0                         ; storage for individual digits
    d2 dq 0
    d3 dq 0
    d4 dq 0

section .bss
;   we will reserve 5 bytes for input
    input resb 5                

section .text
_start:
; 	PRINT PROMPTS for the user
    mov rax, SYS_WRITE              
    mov rdi, STDOUT
    mov rsi, menu
    mov rdx, menuLength
    syscall

; 	INPUT statement
    mov rax, SYS_READ               ; ask user for input choice 
    mov rdi, STDIN
    mov rsi, choice
    mov rdx, 2
    syscall

    sub byte[choice], 30h           ; convert choice into a number

; 	JUMP to cMinutes
    cmp byte[choice], 1             ; convert to minutes if user input is 1
    je cMinutes

; 	JUMP to cHours
    cmp byte[choice], 2             ; convert to hours if user input is 2
    je cHours

; 	JUMP to exit here
    cmp byte[choice], 0             ; exit if choice is 0
    je exit_here

; 	PRINT if the user input is invalid
    mov rax, SYS_WRITE              ; invalid if input matches none of the choices
    mov rdi, STDOUT
    mov rsi, invalidChoice
    mov rdx, invalidChoiceLength
    syscall

    jmp _start                      ; loop the menu

; ------ CONVERTS SECONDS TO MINUTES ------
cMinutes:
; 	PRINT enterSec prompt for the user
    mov rax, SYS_WRITE              
    mov rdi, STDOUT
    mov rsi, enterSec
    mov rdx, enterSecLength
    syscall

    mov rax, SYS_READ               
    mov rdi, STDIN
    mov rsi, input
    mov rdx, 6
    syscall

    cld                             ; set flag to increment
    mov rsi, input                  ; point to first character of input
    mov dword[ans], 0               ; set ans to 0

;   TAKE the character in the ten thousandths place and multiplies it to 10000
    mov ebx, 10000                  
    lodsb                           ; store the character rsi is pointing to inside al
    sub eax, 30h                    ; convert the character in al into a number
    mul ebx
    mov dword[ans], eax             ; store in ans

;   TAKE the character in the thousandths place and multiplies it to 1000
    mov ebx, 1000                   
    mov eax, 0
    lodsb
    sub eax, 30h
    mul ebx
    add dword[ans], eax             ; add eax to ans (10000 + 1000 + 100 + 10 + 1 = 11111 to get the 5 digit number)

;   TAKE the character in the hundreths place and multiplies it to 100
    mov ebx, 100                   
    mov eax, 0                      ; set eax to 0
    lodsb
    sub eax, 30h
    mul ebx
    add dword[ans], eax

;   TAKE the character in the tenths plce and multiplies it to 10 
    mov ebx, 10                    
    mov eax, 0
    lodsb
    sub eax, 30h
    mul ebx
    add dword[ans], eax

;   TAKE the character in the ones place and multiplies it to 1
    mov ebx, 1                    
    mov eax, 0
    lodsb
    sub eax, 30h
    mul ebx
    add dword[ans], eax


;   CONVERT total seconds to minutes
    mov rdx, 0                      ; divide by 60 to convert seconds to minutes
    mov rax, qword[ans]
    mov rbx, 60
    div rbx
    mov qword[ans], rax

    mov rdx, 0                      ; divide by 10 to individually get each digit
    mov rax, qword[ans]
    mov rbx, 10
    div rbx
    mov qword[ans], rax             ; answer gets stored in ans to be used until we reach 0
    mov qword[d4], rdx              ; digit to be printed gets stored

    mov rdx, 0
    mov rax, qword[ans]
    mov rbx, 10
    div rbx
    mov qword[ans], rax
    mov qword[d3], rdx

    mov rdx, 0
    mov rax, qword[ans]
    mov rbx, 10
    div rbx
    mov qword[ans], rax
    mov qword[d2], rdx

    mov rdx, 0
    mov rax, qword[ans]
    mov rbx, 10
    div rbx
    mov qword[ans], rax
    mov qword[d1], rdx

    add qword[d1], 30h              ; convert back each digit into a string
    add qword[d2], 30h
    add qword[d3], 30h
    add qword[d4], 30h

;   ---- PRINTING ----
    mov rax, SYS_WRITE              ; print the digits one by one
    mov rdi, STDOUT
    mov rsi, d1
    mov rdx, 1
    syscall

    mov rax, SYS_WRITE
    mov rdi, STDOUT
    mov rsi, d2
    mov rdx, 1
    syscall

    mov rax, SYS_WRITE
    mov rdi, STDOUT
    mov rsi, d3
    mov rdx, 1
    syscall

    mov rax, SYS_WRITE
    mov rdi, STDOUT
    mov rsi, d4
    mov rdx, 1
    syscall

    mov rax, SYS_WRITE              ; newline
    mov rdi, STDOUT
    mov rsi, newLine
    mov rdx, newLineLength
    syscall

    jmp _start                      ; loop

; ------ CONVERTS SECONDS TO HOURS ------
cHours:                             ; similar to cMinutes except we convert seconds to hours
    mov rax, SYS_WRITE
    mov rdi, STDOUT
    mov rsi, enterSec
    mov rdx, enterSecLength
    syscall

    mov rax, SYS_READ
    mov rdi, STDIN
    mov rsi, input
    mov rdx, 6
    syscall

    cld
    mov rsi, input
    mov dword[ans], 0

;   PROCESS each character
    mov ebx, 10000
    lodsb
    sub eax, 30h
    mul ebx
    mov dword[ans], eax

    mov ebx, 1000
    mov eax, 0
    lodsb
    sub eax, 30h
    mul ebx
    add dword[ans], eax

    mov ebx, 100
    mov eax, 0
    lodsb
    sub eax, 30h
    mul ebx
    add dword[ans], eax

    mov ebx, 10
    mov eax, 0
    lodsb
    sub eax, 30h
    mul ebx
    add dword[ans], eax

    mov ebx, 1
    mov eax, 0
    lodsb
    sub eax, 30h
    mul ebx
    add dword[ans], eax


;   CONVERT total seconds to hours
    mov rdx, 0
    mov rax, qword[ans]
    mov rbx, 3600                   ; divide by 3600 to convert seconds to hours
    div rbx
    mov qword[ans], rax

    mov rdx, 0                      ; divide by 10 to individually get each digit
    mov rax, qword[ans]
    mov rbx, 10
    div rbx
    mov qword[ans], rax             ; answer gets stored in ans to be used until we reach 0
    mov qword[d4], rdx              ; digit to be printed gets stored

    mov rdx, 0
    mov rax, qword[ans]
    mov rbx, 10
    div rbx
    mov qword[ans], rax
    mov qword[d3], rdx

    mov rdx, 0
    mov rax, qword[ans]
    mov rbx, 10
    div rbx
    mov qword[ans], rax
    mov qword[d2], rdx

    mov rdx, 0
    mov rax, qword[ans]
    mov rbx, 10
    div rbx
    mov qword[ans], rax
    mov qword[d1], rdx

    add qword[d1], 30h              ; convert back each digit into a string
    add qword[d2], 30h
    add qword[d3], 30h
    add qword[d4], 30h

;   ---- PRINTING ----
    mov rax, SYS_WRITE              ; print the digits one by one 
    mov rdi, STDOUT
    mov rsi, d1
    mov rdx, 1
    syscall

    mov rax, SYS_WRITE              
    mov rdi, STDOUT
    mov rsi, d2
    mov rdx, 1
    syscall

    mov rax, SYS_WRITE              
    mov rdi, STDOUT
    mov rsi, d3
    mov rdx, 1
    syscall

    mov rax, SYS_WRITE              
    mov rdi, STDOUT
    mov rsi, d4
    mov rdx, 1
    syscall

    mov rax, SYS_WRITE              ; newline
    mov rdi, STDOUT
    mov rsi, newLine
    mov rdx, newLineLength
    syscall

    jmp _start                      ; loop

exit_here:
    mov rax, 60
	xor rdi, rdi
	syscall