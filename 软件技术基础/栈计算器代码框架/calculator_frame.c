#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP    100
#define NUMBER   '0'    // signal that a number was found
#define EMPTY    0
#define MaxStack 50

struct stackCDT{
	void *array[MaxStack];	//栈数组 
	int top;				//top位置，栈空时top为-1 
}; 
typedef struct stackCDT *stackADT;	//栈指针 

int getop(char []);
stackADT NewStack(void);					//创建一个新栈 
void PushStack(stackADT stack, void *obj);	//将obj指向的数据存入栈中 
void *PopStack(stackADT stack);				//将栈顶的数据取出 
void *TopStack(stackADT stack);				//将栈顶的数据公布 
void cal(stackADT NS, stackADT OS);			//弹出两个操作数，一个操作符，进行一次操作运算 

int main()
{
	char c;
	char s[MAXOP];
	stackADT NS, OS;	//NS操作数栈，OS操作符栈 
	char *ch; 
	double *num;
	
	NS = NewStack();
	OS = NewStack();
	
	while ((c = getop(s)) != EOF) 
	{
		switch (c) 
		{
			case NUMBER:	//此处的任务：把数字从s中读取出来
				num = (double*)malloc(sizeof(double)); 
				*num = atof(s);
				PushStack(NS, num);
				printf("%f\n", atof(s));
				break;
			case '+':        // + 和 - 优先级最低，把除了 '(' 以外的全部操作符弹出后入栈
			case '-':
				while(OS->top != -1 && *((char*)OS->array[OS->top]) != '(')	//弹出'('之前的全部操作符
					cal(NS, OS);
				ch = (char*)malloc(sizeof(char)); 
				*ch = c;
				PushStack(OS, ch);
				printf("%c\n", c);
				break;
			case '*':              // 乘除优先级最高，把相同优先级的乘和除弹出后入栈
			case '/':
				while(OS->top != -1 && (*((char*)OS->array[OS->top]) == '/' || *((char*)OS->array[OS->top]) == '*'))
					cal(NS, OS);
				ch = (char*)malloc(sizeof(char)); 
				*ch = c;
				PushStack(OS, ch);	//把'*''/'存入栈 
				printf("%c\n", c);
				break;
			case '(':        // '(' 不作运算，直接放入optor栈。
				ch = (char*)malloc(sizeof(char)); 
				*ch = c;
				PushStack(OS, ch);
				printf("%c\n", c);
				break;
			case ')':        // 把 '(' 之前的全部操作符弹出，计算后把 '(' 也弹出
				while( *((char*)OS->array[OS->top]) != '(')
					cal(NS, OS);
				PopStack(OS);	//弹出'(' 
				printf("%c\n", c);
				break;
			case '\n':        // 把余下的操作符全部弹出，计算后输出结果
				while(OS->top != -1)
					cal(NS, OS);
				printf("the result is %lf\n", *((double*)NS->array[NS->top]));
				PopStack(NS);	//最后将栈顶元素弹出，清空栈 
				printf("%c\n", c);
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}


int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getchar()) == ' ' || c == '\t')	//去掉开头的空格 
    ;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')	//非数字的情况 
		return c; 
	
	i = 0;
	if (isdigit(c)) 	//数字的情况，连续存入S中 
		while (isdigit(s[++i] = c = getchar())) ;
	
	if (c == '.') 	//遇到小数点，把小数存入S 
		while (isdigit(s[++i] = c = getchar()))  ;
	
	s[i] = '\0';	//休止 
	if (c != EOF)  ungetc(c, stdin);	//如果不是EOF，把C放回去 
	return NUMBER;
}

stackADT NewStack(void)
{
	stackADT stack;
	
	stack = (stackADT)malloc(sizeof(struct stackCDT));
	stack->top = -1;
	return (stack);
}

void PushStack(stackADT stack, void *obj)
{
	if(stack->top == MaxStack - 1)
	{
        printf("\nThe stack is full.\n");
        exit(1);
	}
	
	stack->array[++stack->top] = obj;
}

void *PopStack(stackADT stack)
{
	void *obj;
	
	if(stack->top == -1) 
	{
		printf("\nThe stack is full.\n");
        exit(1);
	}
	obj = stack->array[(stack->top)--];
	
	return(obj);
}

void *TopStack(stackADT stack)
{
	if(stack->top == -1) return NULL;
	return(stack->array[stack->top]);
}

void cal(stackADT NS, stackADT OS)
{
	double* DR;		//保存计算结果 
	DR = (double*)malloc(sizeof(double)); 
	
	char* ch = (char*)PopStack(OS);
	double* SR1 = (double*)PopStack(NS);
	double* SR2 = (double*)PopStack(NS);
	switch(*ch)
	{
		case '+': *DR = *SR1 + *SR2; break; 
		case '-': *DR = *SR2 - *SR1; break; 
		case '*': *DR = *SR2 * *SR1; break; 
		case '/': *DR = *SR2 / *SR1; break; 
	}
	free(SR1);
	free(SR2);
	free(ch); 
	PushStack(NS, DR);
}
