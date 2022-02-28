BITS 64
global WinMain
extern printf
extern exit
extern print
section .data
TEXT_INT db "%i ",10,0
section .bss
mem: resb 640000
section .text
WinMain:
addr_0:

;--MEMORY--
push mem

addr_1:

;--PUSH--
push 0

addr_2:

;--PLUS--
pop rcx
pop rdx
add rcx, rdx
push rcx
addr_3:

;--PUSH--
push 254

addr_4:

;--STORE--
pop rcx
pop rdx
mov [rdx], rcx

addr_5:

;--MEMORY--
push mem

addr_6:

;--PUSH--
push 8

addr_7:

;--PLUS--
pop rcx
pop rdx
add rcx, rdx
push rcx
addr_8:

;--PUSH--
push 255

addr_9:

;--STORE--
pop rcx
pop rdx
mov [rdx], rcx

addr_10:

;--MEMORY--
push mem

addr_11:

;--PUSH--
push 16

addr_12:

;--PLUS--
pop rcx
pop rdx
add rcx, rdx
push rcx
addr_13:

;--PUSH--
push 256

addr_14:

;--STORE--
pop rcx
pop rdx
mov [rdx], rcx

addr_15:

;--MEMORY--
push mem

addr_16:

;--PUSH--
push 0

addr_17:

;--PLUS--
pop rcx
pop rdx
add rcx, rdx
push rcx
addr_18:

;--LOAD--
xor rcx, rcx
pop rdx
mov rcx, [rdx]
push rcx

addr_19:

;--PRINT--
pop rdx
call print
addr_20:

;--MEMORY--
push mem

addr_21:

;--PUSH--
push 8

addr_22:

;--PLUS--
pop rcx
pop rdx
add rcx, rdx
push rcx
addr_23:

;--LOAD--
xor rcx, rcx
pop rdx
mov rcx, [rdx]
push rcx

addr_24:

;--PRINT--
pop rdx
call print
addr_25:

;--MEMORY--
push mem

addr_26:

;--PUSH--
push 16

addr_27:

;--PLUS--
pop rcx
pop rdx
add rcx, rdx
push rcx
addr_28:

;--LOAD--
xor rcx, rcx
pop rdx
mov rcx, [rdx]
push rcx

addr_29:

;--PRINT--
pop rdx
call print