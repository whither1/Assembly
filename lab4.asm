STK SEGMENT para STACK 'STACK'
	db 100 dup(0)
STK ENDS

SD1 SEGMENT para public 'DATA'
	MATRIX db 9*9 dup(0)
	N db 0
	M db 0
	INPUT_STR_SIZE db "Enter number of row and column: $"
	INPUT_STR_MATR db "Enter matrix: $"
	OUTPUT_STR db "Resulting matrix: $"
	EMPTY_STR db "Matrix is empty $"
SD1 ENDS

SC1 SEGMENT para public 'CODE'
	assume CS:SC1, DS:SD1, SS:STK

main:	
	mov ax, SD1
	mov ds, ax
	mov ah, 9h
	mov dx, offset INPUT_STR_SIZE
	int 21h
	mov ah, 2
	mov dl, 10
	int 21h
	
	mov ah, 1
	int 21h
	sub al, "0"
	mov [N], al
	mov ah, 2
	mov dl, " "
	int 21h

	
	mov ah, 1
	int 21h
	sub al, "0"
	mov [M], al
	mov ah, 2
	mov dl, 10
	int 21h
	
	mov ah, 9h
	mov dx, offset INPUT_STR_MATR
	int 21h
	mov ah, 2
	mov dl, 10
	int 21h

	mov bx, [offset MATRIX]
	mov cl, N
	xor	ch, ch
	input_for_i:
	push cx 
	mov cl, M
		input_for_j:
		mov ah, 1
		int 21h
		sub al, "0"
		mov [bx], al
		inc bx
		mov ah, 2
		mov dl, " "
		int 21h
		loop input_for_j
	mov ah, 2
	mov dl, 10
	int 21h
	pop cx
	add bx, 9
	sub bl, M
	loop input_for_i
	
	mov bx, [offset MATRIX]
	mov ax, 0
	mov cl, M
	xor	ch, ch
	max_for_j:
	mov dx, 0
	push cx
	push bx	
	mov cl, N
		max_for_i:
		add dl, [bx]
		add bx, 9
		loop max_for_i
	pop bx
	pop cx
	cmp dx, ax
	jle not_max
	mov ax, dx
	mov si, bx

	not_max:
	inc bx
	loop max_for_j
	
	mov bx, si
	mov cl, N
	xor	ch, ch
	offset_for_i:
	push cx 
	mov cl, M
	sub cx, si
		offset_for_j:
		mov dx, [bx + 1]
		mov [bx], dl
		inc bx
		loop offset_for_j
	pop cx
	add bx, 9
	sub bl, M
	add bx, si
	loop offset_for_i
	
	
	mov ah, 9h
	mov dx, offset OUTPUT_STR
	int 21h
	mov ah, 2
	mov dl, 10
	int 21h
	
	cmp M, 1
	jg output
	
	mov ah, 9h
	mov dx, offset EMPTY_STR
	int 21h
	mov ah, 2
	mov dl, 10
	int 21h
	jmp end_prog
	
	output:
	mov bx, [offset MATRIX]
	mov cl, N
	xor	ch, ch
	output_for_i:
	push cx 
	mov cl, M
	sub cl, 1
		output_for_j:
		mov ah, 2
		mov dx, [bx]
		add dl, "0"
		int 21h
		inc bx
		mov ah, 2
		mov dl, " "
		int 21h
		loop output_for_j
	mov ah, 2
	mov dl, 10
	int 21h
	pop cx
	add bx, 10
	sub bl, M
	loop output_for_i
	
	end_prog:
	mov ax, 4c00h
    int 21h
SC1 ENDS
END main