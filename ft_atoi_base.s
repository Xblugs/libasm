section .text
extern ft_strlen ;; size_t ft_strlen(const char *s)
extern ft_memchr ;; void *ft_memchr(const void *s, int c, size_t n)

global ft_atoi_base	;; int ft_atoi_base(char *str, char *base);
	;; [man 3 strtol]
	;; exemple: base = "0123456789abcdef" for hexa
	;; check base parameter (rsi)
	;; save len somewhere
	;; save base args
	;; loop for each char, up to end
	;; if null, whitespace, - or +
	;;	--> mov rax, 0 -> ret
	;; check if a character is a duplicate
	;; 	--> mov rax, 0 -> ret

ft_atoi_base:	;; int ft_atoi_base(char *str, char *base);
	push rbx		;; 
	; push r11		;;
	push r12		;; *str  address
	push r13		;; *base adress
	push r14		;; str  len
	push r15		;; base len

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

.loop_forbidden_check:	;; looks for forbidden characters
	;; ' ' = 32, 	'\*' = 9 to 13 (\n, \t etc)
	;; '+' = 43		'-'  = 45
	mov sil, byte [rdx]	;; sil = rsi lower byte

	cmp sil, 0
	je .loop_duplicate_check_init

	cmp sil, 9			;; x < 9   not whitespace
	jl .not_ws
	cmp sil, 13			;; x <= 12 means whitespace
	jle .end_error

.not_ws:
	cmp sil, 32
	je .end_error
	cmp sil, 43
	je .end_error
	cmp sil, 45
	je .end_error

	inc rdx
	jmp .loop_forbidden_check

.loop_duplicate_check_init:
	mov rbx, r13	;; ptr to current character
	mov rsi, rbx	;; set current base to rsi

	inc rbx
	mov rdi, rbx	;; start looking from next slot

	mov rcx, r15	;; loop counter
	dec rcx

.loop:
	cmp rcx, 0
	je .process

	mov sil, byte [rsi]
	mov rdx, rcx

	push rcx		;; my memchr doesn't use rcx but still
	call ft_memchr
	pop rcx
	cmp rax, 0
	jne .end_error

.loop_inc:
	mov rsi, rbx	;; set current slot
	inc rbx
	mov rdi, rbx
	dec rcx

	jmp .loop

.process:
	mov rax, 42
	jmp .end

.end_error:
	xor rax, rax

.end:
	pop r15
	pop r14
	pop r13
	pop r12
	; pop r11
	pop rbx
	ret
