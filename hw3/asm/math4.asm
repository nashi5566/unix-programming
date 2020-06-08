mov eax, [0x600000]; val1
imul eax, -5
mov ecx, [0x600004]
neg ecx                                         
push rax                                        
mov eax, ecx                                    
xor rdx, rdx                                    
cdq                                             
idiv DWORD PTR [0x600008]
mov ecx, edx                                    
pop rax                                         
xor rdx, rdx                                    
cdq                                             
idiv ecx                                        
mov [0x60000c], eax
