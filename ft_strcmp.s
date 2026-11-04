section .text
global ft_strcmp

ft_strcmp:	;; int ft_strcmp(const char *s1, const char *s2);

	xor rax, rax
	.check:
	mov al, byte [rdi]
	cmp al, byte [rsi]
	je .loop

	.end:
	xor rax, rax
	xor rcx, rcx
	mov al, byte [rdi]
	mov cl, byte [rsi]
	sub rax, rcx
	ret

.loop:
	cmp byte [rdi], 0
	je .end
	cmp byte [rsi], 0
	je .end
	
	inc rdi
	inc rsi
	jmp .check
