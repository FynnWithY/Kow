BITS 64
global WinMain
extern printf
extern exit
extern print
section .data
TEXT_INT db "%i ",10,0
section .bss
section .text
WinMain:
addr_0:

;--PUSH--
push 0

addr_1:

;--WHILE--

addr_2:

;--DUPLICATE--
pop rax
push rax
push rax

addr_3:

;--PUSH--
push 1000

addr_4:

;--SMALLER--
mov rcx, 0
mov rdx, 1
pop rax
pop rbx
cmp rax, rbx
cmovg rcx, rdx
push rcx
addr_5:

;--DO--
pop rax
test rax, rax
jz addr_11

addr_6:

;--PUSH--
push 1

addr_7:

;--PLUS--
pop rcx
pop rdx
add rcx, rdx
push rcx
addr_8:

;--DUPLICATE--
pop rax
push rax
push rax

addr_9:

;--PRINT--
pop rdx
call print
addr_10:

;--END--

jmp addr_1
addr_11:

addr_11:

;--WHILE--

addr_12:

;--PUSH--
push 1

addr_13:

;--DO--
pop rax
test rax, rax
jz addr_15

addr_14:

;--END--

jmp addr_11
addr_15:
