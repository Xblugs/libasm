section .text
global ft_list_size

	;; take list->next addr and look inside
	;; loop until NULL, inc each step

ft_list_size:	;; unsigned int ft_list_size(t_list *begin_list);

	xor rax, rax
	; push rdi
	.check:
	cmp QWORD rdi, 0
	jne .loop

	; pop rdi
	ret

.loop:
	inc rax
	mov rdi, [rdi + 8]
	jmp .check
