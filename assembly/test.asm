.386
.model flat, stdcall
option casemap :none

include \masm32\include\kernel32.inc
include \masm32\include\masm32.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\masm32.lib

.data
 ;message db "This is your first assembly program", 0
 message db "test %i",0
.code 
main:
 ;invoke StdOut, addr message
 ;invoke ExitProcess, 0
 invoke StdOut, addr message 
 invoke ExitProcess, 0
end main