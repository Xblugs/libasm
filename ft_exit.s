section .text
global ft_exit

ft_exit:	;; void _exit(int status);

	mov rax, 60		;; 60 = exit syscall on linux
	syscall