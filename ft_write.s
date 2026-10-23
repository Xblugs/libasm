section .text
global ft_write

ft_write:	;; ssize_t write(int fd, const void *buf, size_t count)

	mov rax, 1		;; linux write syscall
	mov rdi, 1		;; first argument
	mov rsi, msg
	mov rdx, 14
	syscall