section .text
global ft_strlen

ft_strlen:	;; size_t ft_strlen(const char *s)
	xor rax, rax
	.check:
	cmp byte [rdi], 0
	jne .loop
	ret

.loop:
	inc rax
	inc rdi
	jmp .check
