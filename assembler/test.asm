
ld %r0, 0x1234
ld %r1, %r0
ld %r2, %r1

ld %r3, 0x100
ld [%r3], %r0
ld [%r3+0x4], %r0
ld %r10, [%r3+0x4]

jmp 0x0
