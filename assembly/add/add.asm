;sys calls https://www.tutorialspoint.com/assembly_programming/assembly_system_calls.htm
;https://www.cs.uaf.edu/2010/fall/cs301/lecture/09_20_functions_parameters.html
BITS 64
global WinMain
extern printf
extern exit
section .data
	msg db "number is %i ", 10, 0
section .bss
mem: resb 640000
section .text



WinMain:
	;mov rcx,msg	;On Windows 64, the first four parameters go into rcx, rdx, r8, and r9. 
	push mem
	push 5
	
	pop rcx
	pop rdx 
	mov [rdx], rcx
	
	
	xor rcx, rcx
	mov rcx, [rdx]
	push rcx
	
	push msg
	pop rcx
	pop rdx
	call printf
	
	pop rdx
	mov rcx, msg
	call printf
	add esp, 8
	
	
	mov rcx, msg
	mov rdx, 5
	syscall
	;mov esp, ebp
	ret
	
	