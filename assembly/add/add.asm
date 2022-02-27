;sys calls https://www.tutorialspoint.com/assembly_programming/assembly_system_calls.htm
;https://www.cs.uaf.edu/2010/fall/cs301/lecture/09_20_functions_parameters.html
BITS 64
global WinMain
extern printf
extern exit
section .data
	msg db "number is %i ", 10, 0
section .bss
section .text



WinMain:
	;mov rcx,msg	;On Windows 64, the first four parameters go into rcx, rdx, r8, and r9. 
	push 5
	push 10
	
	push 1
	push msg
	pop rcx
	pop rdx
	call printf
	
	pop rdx
	mov rcx, msg
	call printf
	add esp, 8
	;mov esp, ebp
	ret
	
	