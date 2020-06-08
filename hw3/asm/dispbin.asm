mov ecx, 16

check:
mov bx, ax
and bx, 0x1
add bx, 0x30
mov BYTE PTR [0x600000 + ecx -1], bl
shr ax, 1
loop check
