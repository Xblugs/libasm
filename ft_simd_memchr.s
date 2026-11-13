section .text
global ft_simd_memchr   ;; void *ft_simd_memchr(const void *s, int c, size_t n);

	;; The  memchr()  and memrchr() functions return a pointer to the matching
	;;   byte or NULL if the character does not occur in the given memory area.
	;; (using SSE instructions or more recent)
    ;; [Made with SSE2 (Streaming SIMD Extensions 2)]

    ;;  Register sizes:
    ;;     8-bit = byte       16-bit = word        32-bit = doubleword
    ;;    64-bit = quadword  128-bit = double quadword
    ;;  registers are 128-bit

;; AI made for reference
ft_simd_memchr: ;; void *ft_simd_memchr(const void *s, int c, size_t n);
    ; 1. Early exit check (*s = NULL)
    test    rdx, rdx
    jz      .not_found

    ; 2. Fill xmm1
    movd    xmm1, esi
    punpcklbw xmm1, xmm1
    punpcklwd xmm1, xmm1
    pshufd  xmm1, xmm1, 0

    ;; SIMD EXPLANATIONS
	;; MOVe Doubleword (32bit)
    ;; Packed Unpack interleave values from src and dst (here used to fill the register)
    ;;  --> Fill all with what we are looking for
	;;  Packed UNPaCK Low Bytes to Words
	;;  Packed UNPaCK Low Words to Doublewords
    ;; Pshuf copies byte 0 into xmm1 32bit slots
	;;  Packed SHUFfle Doublewords

.align_loop:
    ;; 3. Check alignment
    test    rdi, 15
    jz      .main_simd_setup

   ; ; Check if our scalar alignment loop ran out of bytes (n == 0)
    test    rdx, rdx
    jz      .not_found

    ;; Check current single byte
    cmp     byte [rdi], sil
    je      .match_found_scalar

    inc     rdi                 ; s++
    dec     rdx                 ; n--
    jmp     .align_loop

.main_simd_setup:
    ;; 4. Check if we have >16 bytes left to search
    cmp     rdx, 16
    jb      .scalar_cleanup

.simd_loop:
    movdqa  xmm0, [rdi]
    pcmpeqb xmm0, xmm1
    pmovmskb eax, xmm0

    ;; SIMD EXPLANATIONS
    ;; MOVe Double Quadwords Aligned
    ;;  --> Load enough rdi content to fill xmm0 (16 bytes, xmm are 128 bits)
    ;; Packed Compare for Equal Bytes
    ;;  --> instruction to compare using SIMD
	;; Packed MOVe MaSk Key Bytes
    ;;  --> 0x00 is left when nothing is found, otherwise 0xFF
    ;;      With the MSB we can look how many bytes in we found our match

    test    eax, eax
    jnz     .match_found_simd

    add     rdi, 16             ;; Hop to the next batch
    sub     rdx, 16
    cmp     rdx, 16
    jae     .simd_loop

.scalar_cleanup:
    ;; 5. Process one by one (less than 16 bytes left)
    test    rdx, rdx
    jz      .not_found

    cmp     byte [rdi], sil
    je      .match_found_scalar

    inc     rdi
    dec     rdx
    jmp     .scalar_cleanup

.match_found_simd:
    ;; 6. Pointer arithmetic
    tzcnt   eax, eax            ;; Count trailing zeros to offset properly
    add     rdi, rax
    mov     rax, rdi
    ret

.match_found_scalar:
    mov     rax, rdi
    ret

.not_found:
    xor     rax, rax
    ret
