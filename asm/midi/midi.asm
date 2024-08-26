.386
.model flat, stdcall
option casemap :none
include \masm32\include\winmm.inc
include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
includelib \masm32\lib\winmm.lib
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib
.data
 WindowText db "Press OK to stop playing", 0
 WindowTitle db "Micro MIDI Player", 0
 OpenCom db "open canon.mid type sequencer alias Music1", 0 
 PlayCom db "play Music1", 0
.code
start:
 invoke mciSendString, addr OpenCom, NULL, 0, NULL
 invoke mciSendString, addr PlayCom, NULL, 0, NULL
 invoke MessageBox, NULL, addr WindowText, addr WindowTitle, MB_OK 
 invoke ExitProcess, 0
end start