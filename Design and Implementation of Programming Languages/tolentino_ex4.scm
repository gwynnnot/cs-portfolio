; MARY GWYNETH A. TOLENTINO
; 2021-02990
; CMSC 124 S-4L


; PART 1
; Tail-Recursive Helper-Function for Subtraction of Matrices
(define (subtractM list1 list2 result)
    ; Check if list1 is empty
    (if (null? list1) ; Same as (if (null? list2))
		result ; Base Case (will be returned when last comparison is finished)
        (subtractM 
            (cdr list1) ; Move to the next element
            (cdr list2)
            (append result (list (- (car list1) (car list2)))) ; Subtract the first elements of list1 and list2, and append the result
        ) ; Recursive case (process the first elements of list1 and list2)
    )
)

; Tail-Recursive Main-Function for Subtraction of Matrices
(define (subtractMatrices matrix)
	(subtractM (car matrix) (cadr matrix) '()) ;Initialization
)



; PART 2
; Helper function to check if a number is even
(define (isEven n)
    (cond
        ((= n 0) #t)
        ((= n 1) #f)
        (else (isEven (- n 2)))
    )
)

; Insert element into list in descending order
(define (insert-descending n first)
    (cond
        ((null? first) (list n))  ; If the list is empty, create a new list with n
        ; If n is greater than or equal to the first element, place n at the front
        ((>= n (car first)) (cons n first))
        ; Otherwise, place the first element (car lst) in front, and recursively insert n
        (else (cons (car first) (insert-descending n (cdr first))))
    )
)

; Tail-recursive function to separate evens and odds while sorting them in descending order
(define (OddEven mainList evenList oddList)
    (if (null? mainList)    ; If the main list is empty, 
        (append evenList oddList) ; Append evens first, then odds
        ; Otherwise, check if the current element (car mainList) is even
        (if (isEven (car mainList))
            ; If even, insert it into the evenList in descending order
            (OddEven (cdr mainList) (insert-descending (car mainList) evenList) oddList)
            ; If odd, insert it into the oddList in descending order
            (OddEven (cdr mainList) evenList (insert-descending (car mainList) oddList))
        )
    )    
)

; Main function to sort the list
(define (sortOddEven mainList)
    (OddEven mainList '() '())
)



; TEST
; (load "tolentino_ex4.scm")
; (subtractMatrices (list (list 24 5 14) (list 3 5 10)))
; (sortOddEven '(17 54 83 71 28 42 23 90 67 2))




