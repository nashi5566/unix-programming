mov ecx, 9

outer:
push rcx
mov ecx, 9
mov esi, 0x600000

inner:
mov ebx, [esi]
mov edx, [esi+4]
cmp ebx, edx
jle pass
mov [esi], edx
mov [esi+4], ebx

pass:
add esi, 4
loop inner
pop rcx
loop outer
