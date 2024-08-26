include \masm32\include\masm32rt.inc

.code
start:
   mov esi, 3   ; counter for three iterations
   mov edi, 5   ; start value
   .Repeat
      print str$(esi), " # "
      print str$(edi), " ", 10 ; 10 = \n
      add edi, 5
      dec esi   ; decrement the counter
   .Until Zero?   ; check for zero flag
   exit
end start