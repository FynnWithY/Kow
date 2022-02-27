set projectName=add
nasm -f elf64 %projectName%.asm
gcc %projectName%.o 
a
pause
