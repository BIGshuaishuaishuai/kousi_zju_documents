#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//opcodes 
#define BR 	0
#define ADD 1
#define LD 	2
#define ST	3
#define JSR	4
#define AND 5
#define LDR 6
#define STR 7
#define NOT 9
#define LDI 10
#define STI 11
#define JMP 12
#define LEA 14
#define HALT 15

//16进制数据结构 
typedef unsigned short int uint16_t;
typedef short int int16_t;

//LC-3模拟器储存模块 
static uint16_t mem[65536];	//内存 
static uint16_t R[8];	//通用寄存器
static uint16_t PC, IR;
static int N = 0, Z = 1, P = 0;		//PC, IR 和条件码 
static uint16_t inst;	//IR中的指令 

//functions
	//input module
uint16_t BiStrToNum (char* str);
void input(void);
int power(int a, int b);
	//exert module
void exert(void);
void func_BR(void);
void func_ADD(void);
void func_LD(void);
void func_ST(void);
void func_JSR(void);
void func_AND(void);
void func_LDR(void);
void func_STR(void);
void func_NOT(void);
void func_LDI(void);
void func_STI(void);
void func_JMP(void);
void func_LEA(void);
void nzp_update(uint16_t DR);


int main()
{
	for(int i = 0; i<8; i++)	//initialization
	{
		R[i] = 0x7777;
	}
	for(int i = 0; i<65536; i++)
	{
		mem[i] = 0x7777;
	}
	
	input();
	exert();
	
	for(int i = 0; i < 8; i++)	//output
 	{
 		printf("R%d = x%04hX\n", i, R[i]);
 	}
}
//turn str to binary number
uint16_t BiStrToNum (char* str)
{
	uint16_t num = 0;
	for(int i = 16; i > 0; i--)
	{
		num = num + (*(str+i-1) - 48)* power(2, 16-i);
	}
	return num;
}

int power(int a, int b)
{
	int sum = 1;
	for(int i = 1;i <= b;i++)
	{
		sum = sum*a;
	}
	return sum;
}

void input(void)
{
	char* line; 
	uint16_t now;
	int i;
	
	line = (char*)malloc(17);
	gets(line);
	if(line != NULL)
	{
		IR = BiStrToNum(line);
	}
	else return;
	
	now = IR;	
	PC = IR + 1;
	while(gets(line) != NULL)
	{
		mem[now++] = BiStrToNum(line);
	}
	
	return;
}

void exert(void)
{
	int halt = 1;
	while(halt)
	{
		inst = mem[IR];
		uint16_t opcode = inst >> 12;
		
		switch(opcode)
		{
			case BR:
				func_BR();
				break; 
			case ADD:
				func_ADD();
				break;
			case LD:
				func_LD();
				break;
			case ST:
				func_ST();
				break;
			case JSR:
				func_JSR();
				break;
			case AND:
				func_AND();
				break;
			case LDR:
				func_LDR();
				break;
			case STR:
				func_STR();
				break;
			case NOT:
				func_NOT();
				break;
			case LDI:
				func_LDI();
				break;
			case STI:
				func_STI();
				break;
			case JMP:
				func_JMP();
				break;
			case LEA:
				func_LEA();
				break;
			case HALT:
				halt = 0;
				break;
		}
		IR = PC;
		PC = PC + 1;
	}
}

/*	先搞到nzp， 然后解译9位offset， 加到PC上去*/ 
void func_BR(void)
{
	int n = (inst >> 11) & 0x1;
	int z = (inst >> 10) & 0x1;
	int p = (inst >> 9) & 0x1;
	int16_t offset = inst & 0x1ff;
	if((offset >> 8) > 0)
	{
		offset = offset - 0x200;
	}
	if((N && n) || (Z && z) || (P && p)) PC = PC + offset;
	return;
}

void func_ADD(void)
{
	uint16_t DR = (inst >> 9) & 7;
	uint16_t SR1 = (inst >> 6) & 7;
	uint16_t bit5 = (inst >> 5) & 1;
	
	if(bit5 == 0)
	{
		uint16_t SR2 = inst & 7;
		R[DR] = R[SR1] + R[SR2];
	} 
	else
	{
		int16_t imm = inst & 0x1f;
		if((imm >> 4) > 0)
		{
			imm = imm - 32;
		}
		R[DR] = R[SR1] + imm;
	}
	
	nzp_update(DR);
	return;
}

void nzp_update(uint16_t DR)
{
	if(R[DR] == 0)
	{
		N = 0;	Z = 1;	P = 0;
	}
	else if((R[DR] >> 15) > 0)
	{
		N = 1;	Z = 0;	P = 0;
	}
	else {
		N = 0;	Z = 0;	P = 1;
	}
	return;
}

void func_LD(void)
{
	uint16_t DR = (inst >> 9) & 7;
	int16_t offset = inst & 0x1ff;
	if((offset >> 8) > 0)
	{
		offset = offset - 0x200;
	}
	R[DR] = mem[PC + offset];
	
	nzp_update(DR);
	return;
}

void func_ST(void)
{
	uint16_t SR = (inst >> 9) & 7;
	int16_t offset = inst & 0x1ff;
	if((offset >> 8) > 0)
	{
		offset = offset - 0x200;
	}
	mem[PC + offset] = R[SR];
	
	return;
}

void func_JSR(void)
{
	uint16_t bit11 = (inst >> 11) & 1;
	
	R[7] = PC;
	if(bit11)
	{
		int16_t offset = inst & 0x7ff;
		if((offset >> 10) > 0)
		{
			offset = offset - 0x800;
		}
		PC = PC + offset;
	}
	else
	{
		uint16_t baseR = (inst >> 6) & 7;
		PC = R[baseR];
	}
	return;
}

void func_AND(void)
{
	uint16_t DR = (inst >> 9) & 7;
	uint16_t SR1 = (inst >> 6) & 7;
	uint16_t bit5 = (inst >> 5) & 1;
	
	if(bit5 == 0)
	{
		uint16_t SR2 = inst & 7;
		R[DR] = R[SR1] & R[SR2];
	} 
	else
	{
		int16_t imm = inst & 0x1f;
		if((imm >> 4) > 0)
		{
			imm = imm - 32;
		}
		R[DR] = R[SR1] & imm;
	}
	
	nzp_update(DR);
	return;
}

void func_LDR(void)
{
	uint16_t DR = (inst >> 9) & 7;
	uint16_t baseR = (inst >> 6) & 7;
	int16_t offset = inst & 0x3f;
	if((offset >> 5) > 0)
	{
		offset = offset - 0x40;
	}
	R[DR] = mem[R[baseR] + offset];
	
	nzp_update(DR);
	return;
}

void func_STR(void)
{
	uint16_t SR = (inst >> 9) & 7;
	uint16_t baseR = (inst >> 6) & 7;
	int16_t offset = inst & 0x3f;
	if((offset >> 5) > 0)
	{
		offset = offset - 0x40;
	}
	mem[R[baseR] + offset] = R[SR];
	
	return;
}

void func_NOT(void)
{
	uint16_t DR = (inst >> 9) & 7;
    uint16_t SR = (inst >> 6) & 7;
    
    R[DR] = ~R[SR];
	nzp_update(DR);
	return;
}

void func_LDI(void)
{
	uint16_t DR = (inst >> 9) & 7;
	int16_t offset = inst & 0x1ff;
	if((offset >> 8) > 0)
	{
		offset = offset - 0x200;
	}
	R[DR] = mem[mem[PC + offset]];
	
	nzp_update(DR);
	return;
}

void func_STI(void)
{
	uint16_t SR = (inst >> 9) & 7;
	int16_t offset = inst & 0x1ff;
	if((offset >> 8) > 0)
	{
		offset = offset - 0x200;
	}
	mem[mem[PC + offset]] = R[SR];
	
	return;
}

void func_JMP(void)
{
	uint16_t baseR = (inst >> 6) & 7;
	PC = R[baseR];
}

void func_LEA(void)
{
	uint16_t DR = (inst >> 9) & 7;
	int16_t offset = inst & 0x1ff;
	if((offset >> 8) > 0)
	{
		offset = offset - 0x200;
	}
	R[DR] = PC + offset;
	
	return;
}

