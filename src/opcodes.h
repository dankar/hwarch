#pragma once

// Opcode		Assembler			C				Format
// Operation<0x02, add, true, Indirect<32, Register<4>, 0>, Register<4>, NullVal<0>, 0>::Register(cpu, "ld");
// 32 bit loads
// 0x00			ld Ra, Rb			Ra = Rb			F1 (Ra, Rb)
// 0x01			ld Ra, [Rb]			Ra = [Rb]       F1 (Ra, Rb)
// 0x02			ld [Ra], Rb			[Ra] = Rb       F1 (Ra, Rb)
// 0x03			ld Ra, [Rb + Cx]	Ra = [Rb+Cx]	F2 (Ra, Rb, Cx)
// 0x04			ld [Ra + Cx], Rb	[Ra+Cx] = Rb    F6 (Ra, Cx, Bx)
// 0x05			ld Ra, Imm			Ra = Imm        F5 (Ra, Imm)

// 0x06			xor Ra, Rb, Rc		Ra = Rb ^ Rc	F4 (Ra, Rb, Rc)
// 0x07			and Ra, Rb, Rc		Ra = Rb & Rc	F4 (Ra, Rb, Rc)
// 0x08			or Ra, Rb, Rc		Ra = Rb | Rc	F4 (Ra, Rb, Rc)
// 0x09			not Ra, Rb			Ra = ~Rb		F4 (Ra, Rb)

// 0x0a			add Ra, Rb, Rc		Ra = Rb + Rc	F4 (Ra, Rb, Rc)
// 0x0b			sub Ra, Rb, Rc		Ra = Rb - Rc	F4 (Ra, Rb, Rc)

// 0x0c			shl Ra, Rb, Rc		Ra = Rb << Rc	Ra, Rb, Rc
// 0x0d			shr Ra, Rb, Rc		Ra = Rb >> Rc	Ra, Rb, Rc
// 0x0e			rol Ra, Rb, Rc		Ra = Rb rol Rc  Ra, Rb, Rc
// 0x0d			ror Ra, Rb, Rc		Ra = Rb Ror Rc	Ra, Rb, Rc

// 0xef			cmp Ra, Rb			Ra - Rc			Op Ra Rb
// 0xf0			jmp Imm				goto Imm		F3 (Imm)
// 0xf1			jz Imm				goto Imm		F3 (Imm)
// 0xf2			jnz Imm				goto Imm		F3 (Imm)


