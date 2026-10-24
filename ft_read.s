section .text
global ft_read

extern __errno_location

ft_read:	;; ssize_t ft_read(int fd, void *buf, size_t count);

	mov rax, 0		;; linux read syscall
	; mov rdi, fd	;; argument are already
	; mov rsi, buf	;; in the right buffers
	; mov rdx, n	;; just send
	syscall
	cmp rax, 0
	jl .set_errno
	ret

.set_errno:
	neg rax
	push rax
	call __errno_location ;; wrt ..plt
	pop rdi
	mov [rax], edi	;; errno is 32 bit
	mov rax, -1
	ret
