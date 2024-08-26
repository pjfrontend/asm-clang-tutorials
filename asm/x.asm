.386 
.model flat, stdcall 
option casemap :none 
include \masm32\include\windows.inc 
include \masm32\include\kernel32.inc 
include \masm32\include\masm32.inc 
includelib \masm32\lib\kernel32.lib 
includelib \masm32\lib\masm32.lib 
.data     
 ProgramText db      "Hello World!", 0     
 BadText     db      "Error: Sum is incorrect value", 0     
 GoodText    db      "Excellent! Sum is 6", 0     
 Sum         sdword  0 
.code 
start:                      
 ;                                  eax         
 mov ecx, 6   ; set the counter to 6             ?         
 xor eax, eax ; set eax to 0                     0 
_label: 
 add eax, ecx ; add the numbers                  ?         
 dec ecx      ;     from 0 to 6                  ?         
 jnz _label   ;                                  21         
 mov edx, 7   ;                                  21         
 mul edx      ; multiply by 7                    147         
 push eax     ; pushes eax into the stack         
 pop Sum      ; pops eax and places it in Sum         
 cmp Sum, 147 ; compares Sum to 147         
 jz _good     ; if they are equal, go to _good 
_bad:   
 invoke StdOut, addr BadText         
 jmp _quit 
_good:  
 invoke StdOut, addr GoodText 
_quit:  
 invoke ExitProcess, 0 
end start 