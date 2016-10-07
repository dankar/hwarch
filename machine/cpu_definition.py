
reg4 = 0
imm16 = 1
imm20 = 2
imm32 = 3
null4 = 4
null0 = 5

op_codes = [
 [ 0x00, True, "ld", reg4, reg4 ],
 [ 0x01, True, "ld", reg4, null4, imm32 ],
 [ 0x02, True, "ld", reg4, [ 32, reg4 ] ],
 [ 0x03, True, "ld", [ 32, reg4 ], reg4 ],
 [ 0x04, True, "ld", reg4, [ 32, reg4, imm16 ] ],
 [ 0x05, True, "ld", [ 32, reg4, imm20 ], reg4 ],
 [ 0x06, True, "ld", reg4, [ 16, reg4 ] ],
 [ 0x07, True, "ld", [ 16, reg4 ], reg4 ],
 [ 0x08, True, "ld", reg4, [ 16, reg4, imm16 ] ],
 [ 0x09, True, "ld", [ 16, reg4, imm20 ], reg4 ],
 [ 0x0a, True, "ld", reg4, [ 8, reg4 ] ],
 [ 0x0b, True, "ld", [ 8, reg4 ], reg4 ],
 [ 0x0c, True, "ld", reg4, [ 8, reg4, imm16 ] ],
 [ 0x0d, True, "ld", [ 8, reg4, imm20 ], reg4 ],
 

 [ 0x10, True, "xor", reg4, reg4, reg4 ],
 [ 0x11, True, "and", reg4, reg4, reg4 ],
 [ 0x12, True, "or" , reg4, reg4, reg4 ],
 [ 0x13, True, "not", reg4, reg4 ],

 [ 0x14, True, "add", reg4, reg4, reg4 ],
 [ 0x15, True, "add", reg4, reg4, imm16 ],
 [ 0x16, True, "sub", reg4, reg4, reg4 ],
 [ 0x17, True, "shl", reg4, reg4, reg4 ],
 [ 0x18, True, "shr", reg4, reg4, reg4 ],
 [ 0x19, True, "rol", reg4, reg4, reg4 ],
 [ 0x1a, True, "ror", reg4, reg4, reg4 ],
 
 [ 0x20, True, "push", null0, reg4 ],
 [ 0x21, True, "push", null0, imm32],
 [ 0x22, True, "push", null4, [32, reg4, imm16]],
 
 [ 0x23, True, "pop", reg4 ],
 [ 0x24, True, "pop", [32, reg4, imm20]],

 [ 0x30, True, "hlt"],
 
 [ 0x40, False, "call", null0, imm32],
 [ 0x41, False, "ret", null0 ],
 
 [ 0xef, True, "cmp", null0, reg4, reg4 ],
 [ 0xf0, False, "jmp", null0, imm32 ],
 [ 0xf1, False, "jz", null0, imm32 ],
 [ 0xf2, False, "jnz", null0, imm32 ],
]
