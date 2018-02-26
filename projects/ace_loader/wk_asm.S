        .global extra_cleanup
extra_cleanup: // 0x21208
	ldrb	w8, [x0, #48]
	cbz	w8, _ef_l0
	ldrh	w8, [x0, #48]
	and	w9, w8, #0xff
	cbz	w9, _ef_l0
	strb	wzr, [x0, #48]
	cmp	w8, #0x100
	strb	wzr, [x0, #51]
	b.cs	_ef_l1
_ef_l0:
	mov	x0, #1
	ret
_ef_l1:
	strb	wzr, [x0, #49]

	str	x19, [sp, #-32]!
	stp	x29, x30, [sp, #16]
	add	x29, sp, #0x10
	mov	x19, x0
	ldr	x0, [x19]
	cbz	x0, _ef_l2

	bl	wk_3edf74

	ldp	x29, x30, [sp, #16]
	ldr	x19, [sp], #32

	ret

_ef_l2:
	ldp	x29, x30, [sp, #16]
	ldr	x19, [sp], #32

	mov	x0, #1
	ret

wk_3edf74:
	stp	x22, x21, [sp, #-48]!
	stp	x20, x19, [sp, #16]
	stp	x29, x30, [sp, #32]
	add	x29, sp, #0x20
	mov	x19, x0
	ldr	x8, [x19, #8]
	mov	w20, #0x292
	orr	w1, wzr, #0x4
	mov	x0, x19
	mov	x2, xzr
	mov	x3, xzr
	mov	w5, 0x3e
	mov	w4, 0xe0bc
	bl	wk_call
	ldr	x0, [x19, #8]

	bl	wk_1c0a14

	ldp	x29, x30, [sp, #32]
	ldp	x20, x19, [sp, #16]
	ldp	x22, x21, [sp], #48
	ret

wk_1c0a14:
	stp	x20, x19, [sp, #-32]!
	stp	x29, x30, [sp, #16]
	add	x29, sp, #0x10
	mov	x19, x0
	ldr	x0, [x19, #16]
	orr	w8, wzr, #0x1
	strb	w8, [x19, #136]
	ldr	x8, [x0]
	ldr	x8, [x8, #80]
	blr	x8
	ldp	x29, x30, [sp, #16]
	ldp	x20, x19, [sp], #32
	ret

