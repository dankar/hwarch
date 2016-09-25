		ld		%r0, 0x0
		ld		%r1, 0xa
		xor		%r2, %r2, %r2
		ld		%r3, 0x1
loop:	add		%r2, %r2, %r3
		cmp		%r2, %r1
		jnz		loop
		ld		%r0, 0x0
		ld		%r1, [%r0+loop]
		ld		[%r0+loop], %r1
		hlt
