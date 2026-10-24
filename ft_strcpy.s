section .text
global ft_strcpy

ft_strcpy:	;; char *ft_strcpy(char *dest, const char *src);

	xor rax, rax
	mov rdx, rdi
	.check:
	cmp byte [rsi], 0
	jne .loop
	mov al, byte [rsi]
	mov [rdi], al
	mov rax, rdx
	ret


.loop:
	mov al, byte [rsi]
	mov [rdi], al
	inc rdi
	inc rsi
	jmp .check
