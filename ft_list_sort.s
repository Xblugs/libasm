section .text
global ft_list_sort

	;; Look data content
	;; compare values using *cmp
	;; if > 0, swap positions
	;; go until end of list
	;; loop back until sorted
	;; (keep a swap counter?, loop a fixed amount base on lst_size?)
	;; Profit

ft_list_sort:	;; void ft_list_sort(t_list **begin_list, int (*cmp)());

	;; TODO
	xor rax, rax
	push rdi
	push rsi
	mov rdi, 16 ;; structure size is hardcoded 😊
	call malloc
	cmp rax, 0
	je .set_errno
	
	pop rsi
	mov [rax], rsi
	pop rdi
	mov rdx, [rdi]
	mov [rax+8], rdx
	mov [rdi], rax
	
	.end:
	ret

.set_errno:
	call __errno_location ;; wrt ..plt
	mov dword [rax], 12	;; errno is 32 bit, 12 = ENOMEM
	xor rax, rax
	pop rdi	;; must be popped before the function ends
	pop rsi
	jmp .end