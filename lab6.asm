SC1 SEGMENT para public 'CODE'
	assume CS:SC1
    org 100h

main:
    jmp init
    SECS db 0
    SPEED db 1Fh

breaker proc
    push ax
    push cx
    push dx
    mov ah, 2Ch
    int 21h

    cmp SECS, dh
    je exit
    mov SECS, dh
    mov al, 0F3h
    OUT 60h, al
    mov al, SPEED
    OUT 60h, al
    cmp al, 0
    jne change_speed
    mov al, 20h
change_speed:
    dec al
    and al, 1Fh
    or SPEED, al
    or al, 0E0h
    and SPEED, al
exit:
    pop dx
    pop cx
    pop ax
    db 0EAh
    old_address dd 0
breaker endp

init:
    mov ax, 3508h
    int 21h

    mov word ptr old_address, bx
    mov word ptr old_address + 2, es

    lea dx, breaker
    mov ax, 2508h
    int 21h

    lea dx, init
    int 27h
SC1 ENDS
END main