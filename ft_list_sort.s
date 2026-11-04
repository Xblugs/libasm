section .text
global ft_list_sort

extern ft_list_size ;; unsigned int ft_list_size(t_list *begin_list);

	;; Look data content
	;; compare values using *cmp
	;; if > 0, swap positions ('b' - 'a' = 1)
	;; if equal check next until we reach max len
	;; go until end of list
	;; loop back until sorted
	;; unoptimized but functional

ft_list_sort:	;; void ft_list_sort(t_list **begin_list, int (*cmp)());

	push rbx		;; previous node, lst->ptr address
	push r12		;; list head
	push r13		;; cmp function addr
	push r14		;; current node
	push r15		;; next node

	mov r12, rdi
	mov r13, rsi

	mov rdi, [rdi]	;; init first time and get list size
	mov rbx, rdi
	call ft_list_size
	mov rdi, rbx

	mov rcx, rax
	dec rcx 		;; size n requires n-1 loop to sort at most
	cmp rcx, 0
	jle .end

	xor rdx, rdx
	mov rsi, [rdi+8]
	mov r14, [r12]	;; current = head
	mov r15, [r14+8];; next = head->next

.check:
	mov rdi, [r14]
	mov rsi, [r15]

	push rcx
	push rdx
	call r13 		;; assume (*cmp)(list_ptr->data, list_other_ptr->data);
	pop rdx
	pop rcx

	cmp eax, 0		;; real strcmp leaves garbage into rax upper part
	jg .swap
	jle .incr

.end:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret

.swap_head:
	;; nodes [a -> b] -> c
	;; currently swapping a & b
	push rdx
	mov [r12], r15		;; head ptr must point to b
	mov rdx, [r15+8]	;; save b->next
	mov [r15+8], r14	;; b->next is a
	mov [r14+8], rdx	;; set a->next to original b->next (c)

	mov rbx, [r12]		;; previous node is the head
	pop rdx
	inc rdx 			;; set flag

	xchg r14, r15
	jmp .check 

.swap:	;; rdx != 0 means we're not on list head ptr
	cmp rdx, 0
	je .swap_head

	;; nodes a -> [b -> c]
	;; currently swapping b & c
	push rdx
	mov [rbx+8], r15	;; a->next must point to c
	mov rdx, [r15+8]	;; save c->next
	mov [r15+8], r14	;; set b as c->next
	mov [r14+8], rdx	;; restore initial c->next in b->next (NULL here)

	mov rbx, r15
	pop rdx

	xchg r14, r15
	jmp .check

.incr:	;; set list to list->next
	inc rdx 			;; set flag
	mov rbx, r14
	mov r14, [r14+8]
	cmp r14, 0
	je .loop

	mov r15, [r15+8]
	cmp r15, 0
	je .loop
	
	jmp .check

.loop:
	mov r14, [r12] 		;; restart from head
	mov r15, [r14+8]
	xor rdx, rdx
	dec rcx
	cmp rcx, 0
	jle .end
	jmp .check
