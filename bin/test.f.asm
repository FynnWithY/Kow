BITS 64
global WinMain
extern printf
extern exit
section .data
TEXT_INT db "%i ",0
section .bss
section .text
WinMain:
addr_0:

;--PUSH--
push 0

addr_1:

;--PRINT--
mov rcx, TEXT_INT
pop rdx
call printf
add esp, 8
addr_2:

;--PUSH--
push 100

addr_3:

;--WHILE--

addr_4:

;--DUPLICATE--
pop rax
push rax
push rax

addr_5:

;--PUSH--
push 0

addr_6:

;--SMALLER--
mov rcx, 0
mov rdx, 1
pop rax
pop rbx
cmp rax, rbx
cmovg rcx, rdx
push rcx
addr_7:

;--INVERT--
pop rcx
xor rcx, 0x01
push rcx

addr_8:

;--DO--
pop rax
test rax, rax
jz addr_13

addr_9:

;--PUSH--
push 1

addr_10:

;--MINUS--
pop rdx
pop rcx
sub rcx, rdx
push rcx
addr_11:

;--PRINT--
mov rcx, TEXT_INT
pop rdx
call printf
add esp, 8
addr_12:

;--END--

jmp addr_3
addr_13:

addr_13:

;--WHILE--

addr_14:

;--PUSH--
push 1

addr_15:

;--DO--
pop rax
test rax, rax
jz addr_17

addr_16:

;--END--

jmp addr_13
addr_17:
