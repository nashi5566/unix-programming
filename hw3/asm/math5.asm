mov eax, [0x600000]		  ;val1
mov esi, [0x600004]       ;val2
neg esi                   ;-val2
imul eax, esi             ; eax = val1 * -val2                       
mov esi, [0x600008]       ; val3
sub esi, ebx  ; esi = val3 - ebx                                                                               
xor rdx, rdx                                    
cdq                                             
idiv esi                                                                        
mov DWORD PTR [0x600008], eax
