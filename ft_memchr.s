section .text

global ft_memchr

	;; search *s to find c in n memory slots

ft_memchr:	;; void	*ft_memchr(const void *s, int c, size_t n);

.init:
	xor rax, rax

.loop:
	cmp rdx, 0
	je .end_notfound

	mov cl, byte [rdi]
	cmp sil, cl
	je .end_success

	inc rdi		;; move to next data
	dec rdx		;; decrement n
	jmp .loop

.end_success:
	mov rax, rdi
	ret

.end_notfound:
	ret
