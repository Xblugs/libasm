section .text
global ft_write

extern __errno_location

ft_write:	;; ssize_t ft_write(int fd, const void *buf, size_t count)

	mov rax, 1		;; linux write syscall
	; mov rdi, fd	;; argument are already
	; mov rsi, buf	;; in the right buffers
	; mov rdx, n	;; just send
	syscall
	cmp rax, 0
	jne .set_errno
	ret

.set_errno:
	neg rax
	push rax
	call __errno_location ;; wrt ..plt
	pop rdi
	mov [rax], edi	;; errno is 32 bit
	mov rax, -1
	ret
