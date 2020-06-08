cmp eax, 0x0
jl .v1
xor esi, esi
inc esi
mov [0x600000], esi

.c2:
cmp ebx, 0x0
jl .v2
xor esi, esi
inc esi
mov [0x600004], esi

.c3:
cmp ecx, 0x0
jl .v3
xor esi, esi
inc esi
mov [0x600008], esi

.c4:
cmp edx, 0x0
jl .v4
xor esi, esi
inc esi
mov [0x600004], esi
jmp .end

.v1:
xor esi, esi
inc esi
neg esi
mov [0x600000], esi
jmp .c2

.v2:
xor esi, esi
inc esi
neg esi
mov [0x600004], esi
jmp .c3

.v3:
xor esi, esi
inc esi
neg esi
mov [0x600008], esi
jmp .c4

.v4:
xor esi, esi
inc esi
neg esi
mov [0x60000c], esi

.end:

recur

main:
mov edi, 0x13   ; depends on the question
call r
jmp	.exit

r:
push    rbp
mov     rbp, rsp
push    rbx
sub     rsp, 24
mov     DWORD PTR [rbp-20], edi
cmp     DWORD PTR [rbp-20], 0
jg      .L2
mov     eax, 0
jmp     .L3

.L2:
cmp     DWORD PTR [rbp-20], 1
jne     .L4
mov     eax, 1
jmp     .L3

.L4:
mov     eax, DWORD PTR [rbp-20]
sub     eax, 1
mov     edi, eax
call    r
lea     rbx, [rax+rax]
mov     eax, DWORD PTR [rbp-20]
sub     eax, 2
mov     edi, eax
call    r
mov     rdx, rax
mov     rax, rdx
add     rax, rax
add     rax, rdx
add     rax, rbx

.L3:
add     rsp, 24
pop     rbx
pop     rbp
ret

.exit:

