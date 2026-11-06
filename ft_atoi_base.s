section .text
extern ft_strlen ;; size_t ft_strlen(const char *s)

global ft_atoi_base
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
	;; 

ft_atoi_base:	;; int ft_atoi_base(char *str, char *base);
	push rbx		;; 
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
	xor rdx, r13

.loop_forbidden_check:	;; looks for forbidden characters
	;; ' ' = 32, 	'\*' = 9 to 13 (\n, \t etc)
	;; '+' = 43		'-'  = 45
	mov rsi, [rdx]

	cmp rsi, 0
	je .loop_duplicate_check_init

	cmp rsi, 9
	je .end_error
	cmp rsi, 10
	je .end_error
	cmp rsi, 11
	je .end_error
	cmp rsi, 12
	je .end_error
	cmp rsi, 13
	je .end_error
	cmp rsi, 32
	je .end_error
	cmp rsi, 43
	je .end_error
	cmp rsi, 45
	je .end_error

	inc rdx
	jmp .loop_forbidden_check

.loop_duplicate_check_init:
	mov rdx, r13
	mov rcx, r13

.loop_duplicate_check:	;; looks for duplicate characters
	mov rdi, [rdx]
	inc rdx
	mov rsi, [rdx]
	cmp rsi, 0		;; done with base len
	je .process



.end_error:
	xor rax, rax

.end:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret
