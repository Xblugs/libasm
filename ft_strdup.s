section .text
global ft_strdup

extern __errno_location
extern ft_strcpy ;; char *ft_strcpy(char *dest, const char *src);
extern ft_strlen ;; size_t ft_strlen(const char *s);
extern malloc ;; void *malloc(size_t size);

ft_strdup:	;; char *ft_strdup(const char *s);

	push rdi
	call ft_strlen
	mov rdi, rax
	; mov rdi, 0xFFFFFFFFFFF ;; force malloc to fail
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
	mov dword [rax], 12	;; errno is 32 bit, 12 = ENOMEM
	xor rax, rax
	pop rdi	;; must be popped before the function ends
	jmp .end
