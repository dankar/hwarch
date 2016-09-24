	ld %r0, 0x0
	ld %r1, 0xa
	xor %r2, %r2, %r2
	ld %r3, 0x1
	add %r2, %r2, %r3
	cmp %r2, %r1
	jnz  0x15
	hlt
