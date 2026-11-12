section .text
global ft_simd_memchr   ;; void *ft_simd_memchr(const void *s, int c, size_t n);

; ft_simd_memchr:	;; void *ft_simd_memchr(const void *s, int c, size_t n);
	;; The  memchr()  and memrchr() functions return a pointer to the matching
	;;   byte or NULL if the character does not occur in the given memory area.
	;; (using SSE instructions or more recent)


;; AI made for reference
ft_simd_memchr: ;; void *ft_simd_memchr(const void *s, int c, size_t n);
    ; 1. Early exit check: if n == 0, return NULL immediately
    test    rdx, rdx
    jz      .not_found

    ; 2. Broadcast the target byte across all 16 bytes of XMM1
    movd    xmm1, esi           ; xmm1 = [00|00|00|00|00|00|00|c ]
    punpcklbw xmm1, xmm1        ; xmm1 = [00|00|00|00|00|00|c |c ]
    punpcklwd xmm1, xmm1        ; xmm1 = [00|00|00|00|c |c |c |c ]
    pshufd  xmm1, xmm1, 0       ; xmm1 = [c |c |c |c |c |c |c |c ...] (all 16 bytes filled)
	;; MOVe Doubleword (32bit)
	;; Packed UNPaCK Low Bytes to Words			(duplicate values)
	;; Packed UNPaCK Low Words to Doublewords	(duplicate values again)
	;; Packed SHUFfle Doublewords				(duplicate again)

.align_loop:
    ; 3. Check if we are 16-byte aligned. If yes, jump to main SIMD loop
    test    rdi, 15
    jz      .main_simd_setup

    ; Check if our scalar alignment loop ran out of bytes (n == 0)
    test    rdx, rdx
    jz      .not_found

    ; Check current single byte
    cmp     byte [rdi], sil
    je      .match_found_scalar

    inc     rdi                 ; s++
    dec     rdx                 ; n--
    jmp     .align_loop

.main_simd_setup:
    ; 4. Check if we have at least 16 bytes left to search in SIMD
    cmp     rdx, 16
    jb      .scalar_cleanup

.simd_loop:
    movdqa  xmm0, [rdi]         ; Load 16 aligned bytes into xmm0
    pcmpeqb xmm0, xmm1          ; Compare elements for equality (matches = 0xFF, else 0x00)
    pmovmskb eax, xmm0          ; Extract MSB of each byte into a 16-bit mask in EAX
    ;; Packed Compare for Euality (unsigned Quadword/Vector) Bytes
	;; Packed MOVe MaSk Key Bytes

    test    eax, eax            ; Did any byte match? (mask != 0)
    jnz     .match_found_simd

    add     rdi, 16             ; Advance pointer by 16 bytes
    sub     rdx, 16             ; Decrement counter by 16
    cmp     rdx, 16             ; Keep going if we have >= 16 bytes left
    jae     .simd_loop

.scalar_cleanup:
    ; 5. Process any remaining trailing bytes (less than 16) one by one
    test    rdx, rdx
    jz      .not_found

    cmp     byte [rdi], sil
    je      .match_found_scalar

    inc     rdi
    dec     rdx
    jmp     .scalar_cleanup

.match_found_simd:
    ; 6. Calculate exact matching pointer using Bit Scanning
    tzcnt   eax, eax            ; Count trailing zeros to find the 0-indexed byte offset
    add     rdi, rax            ; Add offset to the base pointer
    mov     rax, rdi            ; Set return value
    ret

.match_found_scalar:
    mov     rax, rdi            ; Found via scalar loop; return current pointer
    ret

.not_found:
    xor     rax, rax            ; Return NULL (0)
    ret
