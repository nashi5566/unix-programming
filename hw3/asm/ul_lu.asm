cmp ch, 0x60 ; ch>0x60 is upper
jg .upper
add ch, 0x20
jmp .end

.upper:
sub ch, 0x20

.end:

