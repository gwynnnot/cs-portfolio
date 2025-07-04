       IDENTIFICATION DIVISION.
       PROGRAM-ID. exercise.
       AUTHOR. gwy.

       ENVIRONMENT DIVISION.

       DATA DIVISION.
       WORKING-STORAGE SECTION.
           77 EXITED PIC 9 VALUE 0.
           77 CHOICE PIC 9.

           77 SMALLEST PIC 9(5).
           77 SMALL PIC 9 VALUE 0.
           77 NON-REPEATED PIC 9 VALUE 1.
           
           77 ARRAY-EMPTY PIC 9 VALUE 1.

           01 array.
               02 elements occurs 5 times indexed by idx.
                   03 element pic 9(5).

       PROCEDURE DIVISION.
           PERFORM PMENU UNTIL EXITED = 1.
           STOP RUN.

       PMENU.
           DISPLAY " ".            
           DISPLAY "    MENU ".
           DISPLAY "[1] Fill Array ".
           DISPLAY "[2] Print Array ".
           DISPLAY "[3] Smallest Non-Repeating Number ".
           DISPLAY "[4] Exit ".
           DISPLAY "Choice: " WITH NO ADVANCING.
           ACCEPT CHOICE.
           DISPLAY " ".

           IF CHOICE = 1
               DISPLAY " FILL ARRAY "
               PERFORM fillarray
           ELSE
               IF CHOICE = 2
                   IF ARRAY-EMPTY = 0
                       DISPLAY " PRINT ARRAY "
                       *> DISPLAY " " array
                       PERFORM printarray
                   ELSE
                       DISPLAY "! EMPTY ARRAY "
                   END-IF
               ELSE
                   IF CHOICE = 3
                       PERFORM smolnonrep
                       IF SMALLEST = 99999
                           DISPLAY "! THERE IS NO NON-REPEATING NUMBER "
                       ELSE
                           DISPLAY " SMALLEST NON-REPEATING NUMBER: "
                           DISPLAY " " SMALLEST
                       END-IF
                   ELSE
                       IF CHOICE = 4
                           DISPLAY " EXIT :P "
                           MOVE 1 TO EXITED
                       ELSE
                           DISPLAY "! INVALID INPUT"
                       END-IF
                   END-IF
               END-IF
           END-IF.

       fillarray.
           MOVE 1 TO idx
           PERFORM UNTIL idx > 5
               ACCEPT elements(idx)
               ADD 1 TO idx
           END-PERFORM.
           MOVE 0 TO ARRAY-EMPTY.

       printarray.
           MOVE 1 TO idx
           PERFORM UNTIL idx > 5
               DISPLAY " " elements(idx) WITH NO ADVANCING
               ADD 1 TO idx
           END-PERFORM.

       smolnonrep.
           MOVE 99999 TO SMALLEST
           MOVE 1 TO idx
           PERFORM UNTIL idx > 5
               MOVE 1 TO NON-REPEATED
               MOVE 1 TO SMALL
               PERFORM UNTIL SMALL > 5
                   IF elements(idx) = elements(SMALL)
                       IF idx NOT = SMALL
                           MOVE 0 TO NON-REPEATED
                       END-IF
                   END-IF
                   ADD 1 TO SMALL
               END-PERFORM
               IF NON-REPEATED = 1
                   IF elements(idx) < SMALLEST
                       MOVE elements(idx) TO SMALLEST
                   END-IF
               END-IF
               ADD 1 TO idx
           END-PERFORM.
