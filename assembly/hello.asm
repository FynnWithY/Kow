;section .text       
;global _WinMain@16  
     
;_WinMain@16:       
; mov eax, 0
; ret 16 
; ----------------------------------------------------------------------------
; helloworld.asm
;
; This is a Win32 console program that writes "Hello, World" on one line and
; then exits.  It needs to be linked with a C library.
;https://www.devdungeon.com/content/how-mix-c-and-assembly
;https://stackoverflow.com/questions/1023593/how-to-write-hello-world-in-assembler-under-windows
;https://dev.to/jmourtada/calling-printf-from-the-c-standard-library-in-assembly-1o39
; ----------------------------------------------------------------------------
	
section .text
	global  WinMain
	extern  printf
WinMain:
    ;push    message
	;call    printf
    ;add     esp, 4
    ;ret
	mov eax, 0x2f    ; NtClose() trägt die Nummer 0x2f in Windows Vista
	push 15          ; 15 auf den Stack legen
	mov edx, esp     ; Pointer auf 15 in EDX speichern
	sysenter         ; Systemaufruf durchführen
message:
    db  'Hello, World', 10, 0