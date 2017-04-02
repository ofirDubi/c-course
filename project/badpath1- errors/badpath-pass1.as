
; 1. this line is ok (DATA4 is declared later)

Start:  dec DATA4

; 2. missing operand -Y
        sub #5

; 3. missing operand -Y
        red

; 4. this line is ok
       .extern DATA4

; 5. invalid target operand (immediate) -Y
        add  #5,#6

; 6. this line is ok (immediate target operand allowed for cmp)
Next:   cmp  #5,#6

; 7. invalid operand (immediate) -Y
        inc  #50
		-Z moozar
; 8. undefined instruction -Y
        and  r1,r2

; 9. undefined instruction (case sensitivity) -Y
        jSr  Start

; 10. this line is ok (r9 is a label declared later)
        add  r1,r9

; 11. invalid characters (,r2) -Y
        cmp  r1,,r2

; 12. invalid characters (,r3) -Y 
        add  #5,r1,r3 

; 13. invalid characters (blabla)  -Y
        prn r1 blabla

; 14. invalid characters (8]) -??
        cmp r1,r3[r8]

; 15. invalid characters (r5]) -Z
        prn Next[r5]

; 16. invalid characters ([r1]) -Y -Z
        cmp #3,r2 [r1]

; 17. invalid characters (123) -Y -Z
        inc  123

; 18. invalid characters (xyz) -??
        cmp  #xyz,r1

; 19. label previously declared -Y
Next:   clr  r2



; 20. invalid source operand (register) -Y
        lea  r3,r1

; 21. invalid source operand (immediate)    -Y
        lea  #3,r5

; 22. invalid characters (Start) -Y
        stop Start

	

; 23. invalid characters (4000)   -Y
        .data   200 4000

; 24. this line is ok (arbitrary whitespace between operands)
DATA1:  .data   3000,   4000 ,  5000, 6000

; 25. invalid characters (,3)  -Y
        .data   1, ,3

; 26. invalid character (,)  -Y
        .data   4,

; 27. invalid characters (#123) -Y
        .data   #123

; 28. invalid characters (.4) -Y
        .data   12.4

; 39. invalid characters (-5) -Y
        .data   --5

; 30. this line is ok (case sensitive labels)
Data1:  .data   100, +200, -300

; 31. invalid label (cannot be an instruction) -Y
mov:    .data   5

; 32. invalid label (cannot be a register) -Y
r1:     .data   200,300



; 33. label previously declared -Y
DATA1:  .data   300

; 34. invalid label(non-alphabetic first character) -Y
1DATA:  .data   300

	

; 35. this line is ok (r9 is not the name of a register)
   .data   200



; 36. this line is ok (label declaration X is ignored - warning to be issued)
X:      .entry  DATA1



; 37. this line is ok (it is ok to declare the same external more than once)
        .extern DATA4
				
		

; 38. local label cannot be declared as external  -Y
        .extern Start    
		
; 39. this line is ok (STR1 is declared later) 
        .entry STR1


; 40. label is already designated as external -??
        ;.entry  DATA4

; 41. undefined instruction (note: DATA2 is not a label declaration)-Y
DATA2   .data   4

; 42. undefined directive (case sensitivity)
        .DATA   5

; 43. This line is ok (it is ok to designate the same entry more than once)
        .entry  STR1

		
; 45. invalid characters (blabla is not a string) -Y
        .string blabla

; 46. invalid characters (blabla) -Y
 .string "abcdefg" blabla


 

; 47. invalid label (too long) -YY
SuperCalifragilisticExpiAlidocious: .data	4	

          
; 48. missing operands in directive -Y
        .data

; 49. missing operand in directive -Z
        .entry

; 50. undefined directive -Y
        .invalid 85,90

; 51. this line is ok
;      stop