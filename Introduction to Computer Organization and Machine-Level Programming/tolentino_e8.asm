global _start

section .data
	menu db 10, "[1] Add Patient", 10, "[2] Edit Patient", 10, "[3] Print Patients", 10, "[4] Exit", 10, "Enter choice: "
	menuLength equ $-menu

	invalidChoice db 10, "Invalid choice!", 10
	invalidChoiceLength equ $-invalidChoice

	fullPrompt db "Record is already full!", 10
	fullPromptLength equ $-fullPrompt

	addCase db 10, "Enter caseID: "		;Use this prompt for add and edit
	addCaseLength equ $-addCase

	addSex db "Enter sex (F - Female, M - Male): "
	addSexLength equ $-addSex

	addStatus db "Enter status (0 - deceased, 1 - admitted, 2 - recovered): " ;Use this prompt for add and edit
	addStatusLength equ $-addStatus

	addDate db "Enter date admitted (mm/dd/yyyy): "
	addDateLength equ $-addDate

	printCase db 10, "CaseID: "
	printCaseLength equ $-printCase

	printSex db 10, "Sex: "
	printSexLength equ $-printSex

	printStatus db 10, "Status: "
	printStatusLength equ $-printStatus

	printDate db 10, "Date Admitted: "
	printDateLength equ $-printDate

	cannotEdit db "Cannot edit records of a deceased patient.", 10
	cannotEditLength equ $-cannotEdit

	cannotFind db "Patient not found!", 10
	cannotFindPrompt equ $-cannotFind

	newLine db 10
	newLineLength equ $-newLine

;	ADDED PROMPTS FOR READABILITY

	addSuccess db "Patient successfully added!", 10
	addSuccessLength equ $-addSuccess

	editSuccess db "Patient status successfully edited!", 10
	editSuccessLength equ $-editSuccess

	emptyDatabase db "Patient database is empty!", 10
	emptyDatabaseLength equ $-emptyDatabase

;	PATIENT STRUCTURE
	patientSize equ 5			; patient database can only hold 5
	patient equ 34				; total size of patient
	caseID equ 0				; caseID beginning address
	caseIDEnd equ 20			; caseID last address
	caseIDSearch dq 0			; inputted caseID for searding
	caseIDSearchLen db 20		; inputted caseID length

	sex equ 21					; sex variable

	status equ 22				; status variable

	date equ 23					; date variable
	dateEnd equ 33				; date variable end

	choice db 0					; choice for user input in the menu

; 	FOR PRINTING
    caseIDLen equ 20
    sexLen equ 1
    statusLen equ 1
    dateLen equ 11

	inputSexLen equ 2
	inputStatusLen equ 2

section .bss
	; we have to reserve 5*34 sized array since we will be allowing 5 patients
	patientDatabase resb patientSize*patient

section .text
_start:
    mov rbp, 0                      ; rbp will serve as a counter for the number of patients

print_menu: 
; 	PRINT PROMPTS for the user
	mov rdi, 1
    mov rax, 1
	mov rsi, menu
	mov rdx, menuLength
	syscall

; 	INPUT statement
    mov rdi, 0
	mov rax, 0
	mov rsi, choice
	mov rdx, 2
	syscall

; 	JUMP to adding patients if user input is 1
    cmp byte[choice], '1'
    je add_patient

; 	JUMP to editing patients if user input is 2
    cmp byte[choice], '2'
    je edit_patient 

;	JUMP to printing patients if user input is 0
    cmp byte[choice], '3'
    je print_patients

; 	JUMP to exit here if user input is 0
    cmp byte[choice], '4'
    je exit_here

; 	PRINT if the user input is invalid
	mov rdi, 1
    mov rax, 1
	mov rsi, invalidChoice
	mov rdx, invalidChoiceLength
	syscall

    jmp print_menu

; ---------- ADD PATIENT INFORMATION ----------	
add_patient:
    cmp ebp, 5
    jge record_full					; checks if record is full

    mov eax, patient				
    mul ebp
    mov ebx, eax					; ebx will serve as the index for each patient 

;	-------- ADD CASE ID --------
    mov rdi, 1                  
	mov rax, 1
	mov rsi, addCase
	mov rdx, addCaseLength
    syscall

    mov rdi, 0
	mov rax, 0
	lea rsi, [patientDatabase + caseID + ebx] 
	mov rdx, caseIDLen
	syscall

    dec rax
    mov byte[patientDatabase + caseIDLen + ebx], al

;	-------- ADD SEX --------
    mov rdi, 1                  
	mov rax, 1
	mov rsi, addSex
	mov rdx, addSexLength
    syscall 

    mov rdi, 0
	mov rax, 0
	lea rsi, [patientDatabase + sex + ebx]
	mov rdx, inputSexLen
	syscall

;	-------- ADD STATUS --------
    mov rdi, 1                  
	mov rax, 1
	mov rsi, addStatus
	mov rdx, addStatusLength
    syscall

    mov rdi, 0
	mov rax, 0
	lea rsi, [patientDatabase + status + ebx]
	mov rdx, inputStatusLen
	syscall

; 	-------- ADD DATE --------
    mov rdi, 1                  
	mov rax, 1
	mov rsi, addDate
	mov rdx, addDateLength
    syscall

    mov rdi, 0
	mov rax, 0
	lea rsi, [patientDatabase + date + ebx]
	mov rdx, dateLen
	syscall

    dec rax
    mov byte[patientDatabase + dateLen + ebx], al

;	-------- PATIENT SUCCESSFULLY ADDED --------
	mov rdi, 1                  ; newline
	mov rax, 1
	mov rsi, newLine
	mov rdx, newLineLength
    syscall

	mov rdi, 1                  
	mov rax, 1
	mov rsi, addSuccess
	mov rdx, addSuccessLength
    syscall

	inc ebp						; increment patient counter
    jmp print_menu

; prints if record is already full
record_full:
    mov rdi, 1                  ; newline
	mov rax, 1
	mov rsi, newLine
	mov rdx, newLineLength
    syscall

    mov rdi, 1
    mov rax, 1
	mov rsi, fullPrompt
	mov rdx, fullPromptLength
	syscall

    jmp print_menu

; ---------- EDIT PATIENT INFORMATION ----------	
edit_patient:
	cmp ebp, 0
	je database_empty				; check if database is empty

	mov rdi, 1                  
	mov rax, 1
	mov rsi, addCase
	mov rdx, addCaseLength
    syscall

    mov rdi, 0
	mov rax, 0
	mov rsi, caseIDSearch
	mov rdx, caseIDSearchLen
	syscall

	dec rax
	mov byte[caseIDSearchLen], al
	sub qword[caseIDSearch], 30h		; convert string to decimal

	mov rsp, 0							; rsp will serve as counter for looping through the array

	find_patient:
		mov eax, patient
		mul esp							; esp*eax
		mov ebx, eax 					; ebx = the address of the nth patient

		sub byte[patientDatabase + ebx + caseID], 30h		; convert the caseID string to decimal
		mov rdi, [caseIDSearch]								
		mov rsi, [patientDatabase + caseID + ebx]
		add byte[patientDatabase + ebx + caseID], 30h		; convert caseID from decimal to string

		cmp rsi, rdi										; compare two strings
		je patient_exists									; if matched jump to patient existing

		inc rsp								; increment counter if not matched
		cmp esp, ebp						; if the counter already matches the patient number
		jl find_patient
		jmp patient_nonexisting				; then patient does not exist

	patient_exists:
		cmp byte[patientDatabase + status + ebx], 30h		; since the string format for 0 is 30h, we compate if the status at string is 30h
		je patient_deceased									; if yes, we jump to patient is deceased

		mov rdi, 1
		mov rax, 1
		mov rsi, addStatus
		mov rdx, addStatusLength
		syscall

		mov rdi, 0					; get new status from user
		mov rax, 0
		lea rsi, [patientDatabase + status + ebx]
		mov rdx, inputStatusLen
		syscall

		mov rdi, 1                  ; newline
		mov rax, 1
		mov rsi, newLine
		mov rdx, newLineLength
		syscall

		mov rdi, 1					; add success
		mov rax, 1
		mov rsi, editSuccess
		mov rdx, editSuccessLength
		syscall
		
		jmp print_menu

	; PRINTS if patient is non-existent/was not found in the array
	patient_nonexisting:
		mov rdi, 1                  ; newline
		mov rax, 1
		mov rsi, newLine
		mov rdx, newLineLength
		syscall

		mov rdi, 1
		mov rax, 1
		mov rsi, cannotFind
		mov rdx, cannotFindPrompt
		syscall

		jmp print_menu

	; PRINTS if user has the status of deceased
	patient_deceased:
		mov rdi, 1                  ; newline
		mov rax, 1
		mov rsi, newLine
		mov rdx, newLineLength
		syscall

		mov rdi, 1
		mov rax, 1
		mov rsi, cannotEdit
		mov rdx, cannotEditLength
		syscall

	jmp print_menu					; loop

; ---------- PRINT PATIENTS INFORMATION ----------
print_patients:
	cmp ebp, 0
	je database_empty

	; RSP serves as the counter
	mov rsp, 0

	print_information:
		mov eax, patient
		mul esp
		mov ebx, eax 

		; ---------- PRINT CASE IDs ----------
		mov rdi, 1                  
		mov rax, 1
		mov rsi, printCase
		mov rdx, printCaseLength
		syscall

		mov rdi, 1                  
		mov rax, 1
		lea rsi, [patientDatabase + caseID + ebx]
		mov rdx, 0
		mov dl, byte[patientDatabase + caseIDLen + ebx]
		syscall

		; ---------- PRINT SEX ----------
		mov rdi, 1                  
		mov rax, 1
		mov rsi, printSex
		mov rdx, printSexLength
		syscall

		mov rdi, 1                  
		mov rax, 1
		lea rsi, [patientDatabase + sex + ebx]
		mov rdx, 1
		syscall

		; ---------- PRINT STATUS ----------
		mov rdi, 1                  
		mov rax, 1
		mov rsi, printStatus
		mov rdx, printStatusLength
		syscall

		mov rdi, 1                  
		mov rax, 1
		lea rsi, [patientDatabase + status + ebx]
		mov rdx, 1
		syscall

		; ---------- PRINT DATE ADMITTED ----------
		mov rdi, 1                  
		mov rax, 1
		mov rsi, printDate
		mov rdx, printDateLength
		syscall

		mov rdi, 1                  
		mov rax, 1
		lea rsi, [patientDatabase + date + ebx]
		mov rdx, 0
		mov dl, byte[patientDatabase + dateLen + ebx]
		syscall

		mov rdi, 1                  ; newline
		mov rax, 1
		mov rsi, newLine
		mov rdx, newLineLength
		syscall

		inc rsp
		cmp esp, ebp
		jne print_information

	jmp print_menu

; print if there is no patient to edit/print in the database
database_empty:
	mov rdi, 1                  ; newline
	mov rax, 1
	mov rsi, newLine
	mov rdx, newLineLength
    syscall

    mov rdi, 1
    mov rax, 1
	mov rsi, emptyDatabase
	mov rdx, emptyDatabaseLength
	syscall

	jmp print_menu

exit_here:
	mov rax, 60
	xor rdi, rdi
	syscall