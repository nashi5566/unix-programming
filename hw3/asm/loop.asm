xor ecx, ecx
.count:
cmp ecx, 0xf
jle .loop
jg  .exit

.loop:
mov al, BYTE PTR [0x600000 + ecx]
cmp al, 0
je .null
cmp al, 0x60
jle .upper
jg .lower

.inc:
inc ecx
jmp .count

.upper:
add al, 0x20
mov BYTE PTR [0x600010 + ecx], al
jmp .inc

.lower:
mov BYTE PTR [0x600010 + ecx], al
jmp .inc

.null:
mov BYTE PTR [0x600010 + ecx], al
jmp .inc

.exit:
