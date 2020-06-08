main:
		mov		edi, 0x1d
		call	r
		jmp		.exit
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
