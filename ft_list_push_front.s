section .text
global ft_list_push_front

extern __errno_location
extern malloc ;; void *malloc(size_t size);

	;; alloc new list
	;; on alloc success copy data ptr into list->data
	;; else stop
	;; take current head addr and copy into list->next
	;; set current addr to begin_list

ft_list_push_front:	;; void ft_list_push_front(t_list **begin_list, void *data);

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
	pop rsi	;; must be popped before the function ends
	pop rdi
	jmp .end
