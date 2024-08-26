INCLUDE \masm32\include\masm32rt.inc

.CODE
_main PROC
    mov ecx, 4 ; number of repetitions
    mov eax, 5 ; initial accummulator value

myloop:
    add eax, 6
    push    eax
    push    ecx
    print str$(eax),13,10 ; 13=EOF, 10=\n
    pop     ecx
    pop     eax
    loop myloop

    inkey ; press any key to continue...
    exit

_main ENDP

END _main