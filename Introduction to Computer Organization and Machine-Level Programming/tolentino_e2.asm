global _start

section .data
	SYS_EXIT equ 60
    daysNum dd 365  ;number of days
    hoursNum dd 24  ;number of hours

	age db 25       ;age is byte-size with value of 25 (works up to 100)
	days dd 0       ;days is double-word
    hours dq 0      ;hours is quad-word

section .text
_start:
    mov ax, 0
    mov al, byte[age]       ;al = age
    mul word[daysNum]       ;al * age
    mov word[days], ax   

    mov eax, 0
    mov eax, dword[days]    ;eax = days
    mul dword[hoursNum]     ;eax * 24
    mov dword[hours], eax   ;lower half 
    mov dword[hours+4], edx ;upper half (32 bits)

exit_here:
    mov rax, SYS_EXIT
    xor rdi, rdi
	syscall