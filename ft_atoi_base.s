section .text
extern ft_strlen ;; size_t ft_strlen(const char *s)
extern ft_memchr ;; void *ft_memchr(const void *s, int c, size_t n)
extern ft_isspace ;; int ft_isspace(int c);


global ft_atoi_base	;; int ft_atoi_base(char *str, char *base);
	;; [man 3 strtol]
	;; exemple: base = "0123456789abcdef" for hexa
	;; check [base] parameter (rsi)
	;; save len somewhere
	;; save base args
	;; loop for each char, up to end
	;; if null, whitespace, - or +
	;;	--> mov rax, 0 -> ret
	;; check if a character is a duplicate
	;; 	--> mov rax, 0 -> ret

ft_atoi_base:			;; int ft_atoi_base(char *str, char *base);
	push rbx			;; free use
	push r11			;; free use
	push r12			;; *str  address
	push r13			;; *base adress
	push r14			;; str  len
	push r15			;; base len

.init:
	mov r12, rdi
	mov r13, rsi

	call ft_strlen
	mov r14, rax
	cmp r14, 0
	je .end_error

	mov rdi, r13
	call ft_strlen
	mov r15, rax
	cmp r15, 2
	jl .end_error

	xor rax, rax
	xor rcx, rcx
	mov rdx, r13


;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Verify the given base ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;

.loop_forbidden_check:
	;; looks for forbidden characters
	;; ' ' = 32, 	'\*' = 9 to 13 (\n, \t etc)
	;; '+' = 43		'-'  = 45

	xor rdi, rdi
	mov dil, byte [rdx]	;; sil = rsi lower byte

	cmp dil, 0
	je .loop_duplicate_check_init

	push rdi
	call ft_isspace		;; check whitespace inside
	pop rdi

	cmp rax, 0
	jne .end_error

.not_ws:				;; check for '+', '-'
	cmp dil, 43
	je .end_error
	cmp dil, 45
	je .end_error

	inc rdx
	jmp .loop_forbidden_check

.loop_duplicate_check_init:
	mov rbx, r13		;; ptr to current character
	mov rsi, rbx		;; set current base to rsi

	inc rbx
	mov rdi, rbx		;; start looking from next slot

	mov rcx, r15		;; loop counter
	dec rcx

.loop_dup:				;; check for duplicates in base
	cmp rcx, 0
	je .verify_str

	movzx esi, byte [rsi]
	mov rdx, rcx

	push rcx			;; my memchr doesn't use rcx but still
	call ft_memchr
	pop rcx
	cmp rax, 0
	jne .end_error

.loop_dup_inc:
	mov rsi, rbx		;; set current slot
	inc rbx
	mov rdi, rbx
	dec rcx

	jmp .loop_dup


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Verify the given string ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.verify_str:
	;; Skip whitespaces until eventual sign
	;;	-> only accept one sign if any
	;; Stop at the first invalid char (update len)

	mov r9, r12			;; *str adress
	xor r8, r8
	mov r8b, byte [r9]
	mov rcx, r14		;; str len
	xor rbx, rbx		;; part of rbx will be used as flags (bl, bh)

.verify_whitespace:
	cmp r8, 0			;; skip process on string end
	je .end_error

	movzx dil, r8b
	push r8
	call ft_isspace		;; check whitespace inside
	pop r8

	cmp rax, 0
	jne .loop_str_inc
	je .ws_end

.ws_end:
	;; no more whitespace is accepted from here
	;; Accept only one optional sign, default to positive values

	cmp r8b, 43			;; '+'
	je .loop_str_inc

	cmp r8b, 45			;; '-'
	je .minus_sign

	inc bl
	xor rax, rax		;; reset rax before processing
	jmp .loop_str

.minus_sign:			;; set negative flag
	inc bh
	jmp .loop_str_inc


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ASCII to int conversion part ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.loop_str:
	cmp r8, 0
	je .add_sign		;; str '\0'

	mov rdi, r13
	mov rsi, r8
	mov rdx, r15

	push r8
	push r9
	push rax
	call ft_memchr		;; void	*ft_memchr(const void *s, int c, size_t n);

	mov r11, rax		;; save returned address
	cmp rax, 0			;; 0 = not found = end of valid input, we stop
	pop rax				;; pop doesn't change cmp flags
	pop r9
	pop r8
	je	.add_sign		;; not found, first invalid char means we stop here

	jmp .process

.process:
	;; Get the number corresponding to the character scanned
	;; num = num * [base len] + num		; take off the ascii part

	imul rax, r15

	sub r11, r13		;; pointer arithmetic to convert easily from any base
	shr r11, 3			;; shift right 3 slots (convert from bytes)

	add rax, r11

	jmp .loop_str_inc

.loop_str_inc:			;; load next char
	inc r9
	mov r8b, byte [r9]

	dec rcx				;; space left in str

.jump_back:
	cmp bl, 0
	je .verify_whitespace

	cmp bl, 1
	je .loop_str

	jmp .end

.add_sign:			;; set back value to negative if bh flag
	cmp bh, 0
	je .end

	neg rax
	jmp .end

.end_error:
	xor rax, rax

.end:
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop rbx
	ret
