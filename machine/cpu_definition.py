
reg4 = 0
imm16 = 1
imm20 = 2
imm32 = 3
null4 = 4
null0 = 5

op_codes = [
 [ 0x00, True, "ld", reg4, reg4 ],
 [ 0x01, True, "ld", reg4, [ reg4 ] ],
 [ 0x02, True, "ld", [ reg4 ], reg4 ],
 [ 0x03, True, "ld", reg4, [ reg4, imm16 ] ],
 [ 0x04, True, "ld", [ reg4, imm20 ], reg4 ],
 [ 0x05, True, "ld", reg4, null4, imm32 ],

 [ 0x06, True, "xor", reg4, reg4, reg4 ],
 [ 0x07, True, "and", reg4, reg4, reg4 ],
 [ 0x08, True, "or" , reg4, reg4, reg4 ],
 [ 0x09, True, "not", reg4, reg4 ],

 [ 0x0a, True, "add", reg4, reg4, reg4 ],
 [ 0x0b, True, "sub", reg4, reg4, reg4 ],
 [ 0x0c, True, "shl", reg4, reg4, reg4 ],
 [ 0x0d, True, "shr", reg4, reg4, reg4 ],
 [ 0x0e, True, "rol", reg4, reg4, reg4 ],
 [ 0x0f, True, "ror", reg4, reg4, reg4 ],

 [ 0x30, True, "hlt"],
 [ 0xef, True, "cmp", null0, reg4, reg4 ],
 [ 0xf0, False, "jmp", null0, imm32 ],
 [ 0xf1, False, "jz", null0, imm32 ],
 [ 0xf2, False, "jnz", null0, imm32 ],
]
