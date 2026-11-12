section .text

global ft_isspace

ft_isspace:	;; int	ft_isspace(int c);
	;; ' ' = 32, 	'\*' = 9 to 13 (\n, \t etc)

.init:
	xor rax, rax

.verify_whitespace:
	cmp dil, 9			;; x < 9   not whitespace
	jl .end

	cmp dil, 13			;; x <= 12 means whitespace
	jle .is_space

	cmp dil, 32			;; ' '
	jne .end

.is_space:
	inc rax

.end:
	ret