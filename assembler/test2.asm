current_line: dw 0x0

# 1st arg in %fp+4
print:
	push %fp
	ld %fp, %sp
	push %r0
	push %r1
	push %r2
	push %r3

	# arg in r0
	ld %r0, [%fp+0x8]
	ld %r1, 0x0
	ld %r3, target

print_loop:
	ld %r2, [%r0]
	cmp %r2, %r1
	jz print_end

	ld [%r3], %r2
	add %r3, %r3, 0x1
	add %r0, %r0, 0x1
	jmp print_loop
	
print_end:
	pop %r3
	pop %r2
	pop %r1
	pop %r0
	ld %sp, %fp
	pop %fp
	ret

target:
