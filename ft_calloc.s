section .text
global ft_calloc

extern __errno_location
extern malloc ;; void *malloc(size_t size);

ft_calloc:	;; void *ft_calloc(size_t nmemb, size_t size);

;; TODO LOL
	push rdi
	call ft_strlen
	mov rdi, rax
	; mov rdi, 0xFFFFFFFFFFF ;; force malloc to fail
	mov rsi, 1
	call malloc
	cmp rax, 0
	je .set_errno
	mov rdi, rax
	pop rsi
	call ft_strcpy
	.end:
	ret

.set_errno:
	call __errno_location ;; wrt ..plt
	mov dword [rax], 12	;; errno is 32 bit
	xor rax, rax
	pop rdi	;; must be popped before the function ends
	jmp .end
