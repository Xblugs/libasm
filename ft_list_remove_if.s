section .text
global ft_list_remove_if

extern free

ft_list_remove_if:	;; void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

	push rbx		;; previous node, lst->ptr address
	push rbp		;; free function addr
	push r12		;; list head
	push r13		;; cmp function addr
	push r14		;; current node
	push r15		;; data ref

	mov r12, rdi
	mov r13, rdx
	mov r14, [r12]	;; current = head
	mov r15, rsi
	mov rbp, rcx

	mov rbx, r14	;; previous = current for first

.check:
	cmp r14, 0
	je .end

	mov rdi, [r14]
	mov rsi, r15

	call r13 		;; assume (*cmp)(list_ptr->data, list_other_ptr->data);

	cmp eax, 0		;; real strcmp leaves garbage into rax upper part
	je .free
	jmp .incr

.end:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	pop rbx
	ret

.free_head:
	;; nodes [a] -> b -> c
	;; currently freeing a
	mov rdi, [r12]		;; charge head to rdi
	mov rsi, [r14+8]	;; head ptr must point to b
	mov [r12], rsi

	mov rdi, [rdi]		;; free data
	sub rsp, 8
	call rbp
	add rsp, 8
	mov rdi, r14		;; free link
	sub rsp, 8
	call free
	add rsp, 8

	mov rbx, [r12]		;; previous node is the head
	mov r14, [r12]

	jmp .check 

.free:
	cmp rbx, [r12]			;; check if on head
	je .free_head

	;; nodes a -> [b] -> c
	;; currently freeing b
	mov rdi, [r14]
	mov rsi, [r14+8];; a->next must point to c
	mov [rbx+8], rsi

	sub rsp, 8
	call rbp		;; free data
	add rsp, 8
	mov rdi, r14
	sub rsp, 8
	call free		;; free link
	add rsp, 8

	mov r14, [rbx+8]
	jmp .check

.incr:	;; set list to list->next
	mov rbx, r14
	mov r14, [r14+8]
	cmp r14, 0
	je .end
	
	jmp .check
