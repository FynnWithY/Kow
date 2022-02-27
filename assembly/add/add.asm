;sys calls https://www.tutorialspoint.com/assembly_programming/assembly_system_calls.htm
;https://www.cs.uaf.edu/2010/fall/cs301/lecture/09_20_functions_parameters.html
BITS 64
global WinMain
extern printf
extern exit
section .data
	msg db "number is %i ",0
section .bss
section .text



WinMain:
	;mov rcx,msg	;On Windows 64, the first four parameters go into rcx, rdx, r8, and r9. 
	push 5
	;access 0
	pop rax
	push 1
	push 2
	push 3
	push 4
	
	pop rdx
	pop rdx
	mov ebp, esp 
	mov rcx, msg
	call printf
	mov esp, ebp
	
	pop rdx
	mov rcx, msg
	call printf
	ret
	
	