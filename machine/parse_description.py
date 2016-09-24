import os
from cpu_definition import *


for inst in op_codes:
	print("Operation<0x" + format(inst[0], '02x') + ", " + inst[2] + ", " + ("true" if inst[1] else "false") + ", "),
	
	num_parameters = len(inst) - 3
	operands_bits = 0
	for i in range(num_parameters):
		operand = inst[3+i]
		if operand == reg4:
			operands_bits += 4
			print "Register<4>,",
		if operand == null4:
			operands_bits += 4
			print "NullVal<4>,",
			
		if type(operand) is list:
			print "Indirect<32, ",
			if len(operand) == 1:
				print "Register<4>, NullVal<0>>,",
				operands_bits += 4
			else:
				print "Register<4>, ",
				operands_bits += 4
				if operand[1] == imm16:
					operands_bits += 16
					print "Immediate<16>>,",
				if operand[1] == imm20:
					operands_bits += 20
					print "Immediate<20>>,",
				if operand[1] == imm32:
					operands_bits += 32
					print "Immediate<32>>,",
		if operand == imm16:
			operands_bits += 16
			print "Immediate<16>,",
		if operand == imm20:
			operands_bits += 20
			print "Immediate<20>,",
		if operand == imm32:
			operands_bits += 32
			print "Immediate<32>,",
			
		if operand == null0:
			print "NullVal<0>,",
	
	for i in range(3 - num_parameters):
		print "NullVal<0>,",
	
	if operands_bits % 8 == 4:
		print "4>",
	else:
		print "0>",
		
	print "::Register(cpu, \"" + inst[2] + "\");"
	
for inst in op_codes:
	print "{ \"" + inst[2] + "\", {"
	num_parameters = len(inst) - 3
	operands_bits = 0
	for i in range(num_parameters):
		operand = inst[3+i]
		if operand == reg4:
			print " { REG, 0, 0 },"
			
		if type(operand) is list:
			if len(operand) == 1:
				print " { IND, 0, 0 },"
			else:
				print " { IND_OFFSET, 0, 0 },"
				
		if operand == imm32:
			operands_bits += 32
			print " { IMM, 0, 0 },"
			
		
	
	
		
	for i in range(3 - num_parameters):
		print " { NONE, 0, 0 },"
		
	print "},"
	
	print " 0x" + format(inst[0], '02x')
	print "},"
		
		
		
	
	
		