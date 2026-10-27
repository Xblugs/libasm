section .text
global ft_calloc

extern __errno_location
extern malloc ;; void *malloc(size_t size);

ft_calloc:	;; void *ft_calloc(size_t nmemb, size_t size);

	push r12
	mov rax, rsi
	mul rdi
	jc .set_errno ;; jump if overflow

	mov r12, rdi
	call malloc
	cmp rax, 0
	je .set_errno ;; jump on alloc error
	
	xor rcx, rcx
	mov rdi, r12
	mov rdx, rax
	.check:
	cmp rcx, rdi
	jne .loop

	.end:
	pop r12
	ret

.set_errno:
	call __errno_location ;; wrt ..plt
	mov dword [rax], 12	;; errno is 32 bit, 12 = ENOMEM
	xor rax, rax
	jmp .end

.loop:	;; clear each byte
	mov byte [rdx], 0
	inc rcx
	inc rdx
	jmp .check
