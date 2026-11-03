section .text
global ft_list_sort

extern ft_list_size ;; unsigned int ft_list_size(t_list *begin_list);

	;; Look data content
	;; compare values using *cmp
	;; if > 0, swap positions ('b' - 'a' = 1)
	;; if equal check next until we reach max len
	;; go until end of list
	;; loop back until sorted
	;; (keep a swap counter?, loop a fixed amount base on lst_size?)
	;; Profit

ft_list_sort:	;; void ft_list_sort(t_list **begin_list, int (*cmp)());

	push r11
	push r12
	push r13
	push r14		;; current node
	push r15		;; next node
	xor r11, r11	;; ;; previous node, lst->ptr address
	mov r12, rdi	;; list head
	mov r13, rsi	;; cmp function addr

	mov rdi, [rdi]	;; init first time and get list size
	push rdi
	call ft_list_size
	pop rdi

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

	cmp rax, 0
	jg .swap
	jle .incr

.end:
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	ret

.swap_head:
	;; nodes a -> b -> c
	;; currently swapping a & b
	push rdx
	mov rdx, [r15+8]	;; save b->next
	mov [r12], r15		;; head ptr must point to b
	mov [r15+8], r14	;; b->next is a
	mov [r14+8], rdx	;; set a->next to original b->next (c)

	mov r11, [r12]		;; previous node is the head
	mov r14, [r15+8]
	mov r15, [r14+8]

	pop rdx
	inc rdx 			;; set flag

	xchg r14, r15
	jmp .incr

.swap:	;; rdx != 0 means we're not on list head ptr
	cmp rdx, 0
	je .swap_head

	;; nodes a -> b -> c
	;; currently swapping b & c
	push rdx
	mov [r11+8], r15	;; a->next must point to c
	mov rdx, [r15+8]	;; save c->next
	mov [r15+8], r14	;; set b as c->next
	mov [r14+8], rdx	;; restore initial c->next in b->next (NULL here)

	mov r11, r15
	mov r14, [r15+8]
	mov r15, [r14+8]

	pop rdx

	xchg r14, r15
	jmp .incr

.incr:	;; set list to list->next
	mov r11, r14
	mov r14, r15
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
