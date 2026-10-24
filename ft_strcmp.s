section .text
global ft_strcmp

ft_strcmp:	;; int ft_strcmp(const char *s1, const char *s2);

	xor rax, rax
	.check:
	mov al, [rdi]
	cmp byte al, [rsi]
	je .loop
	.end:
	mov al, [rdi]
	sub byte al, [rsi]
	; js  handle_sign
	ret


.loop:
	cmp byte [rdi], 0
	je .end
	inc rdi
	inc rsi
	jmp .check

; .handle_sign:

