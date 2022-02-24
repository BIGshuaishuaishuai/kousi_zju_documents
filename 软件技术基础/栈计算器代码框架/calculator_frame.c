#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP    100
#define NUMBER   '0'    // signal that a number was found
#define EMPTY    0
#define MaxStack 50

struct stackCDT{
	void *array[MaxStack];	//ջ���� 
	int top;				//topλ�ã�ջ��ʱtopΪ-1 
}; 
typedef struct stackCDT *stackADT;	//ջָ�� 

int getop(char []);
stackADT NewStack(void);					//����һ����ջ 
void PushStack(stackADT stack, void *obj);	//��objָ������ݴ���ջ�� 
void *PopStack(stackADT stack);				//��ջ��������ȡ�� 
void *TopStack(stackADT stack);				//��ջ�������ݹ��� 
void cal(stackADT NS, stackADT OS);			//����������������һ��������������һ�β������� 

int main()
{
	char c;
	char s[MAXOP];
	stackADT NS, OS;	//NS������ջ��OS������ջ 
	char *ch; 
	double *num;
	
	NS = NewStack();
	OS = NewStack();
	
	while ((c = getop(s)) != EOF) 
	{
		switch (c) 
		{
			case NUMBER:	//�˴������񣺰����ִ�s�ж�ȡ����
				num = (double*)malloc(sizeof(double)); 
				*num = atof(s);
				PushStack(NS, num);
				printf("%f\n", atof(s));
				break;
			case '+':        // + �� - ���ȼ���ͣ��ѳ��� '(' �����ȫ����������������ջ
			case '-':
				while(OS->top != -1 && *((char*)OS->array[OS->top]) != '(')	//����'('֮ǰ��ȫ��������
					cal(NS, OS);
				ch = (char*)malloc(sizeof(char)); 
				*ch = c;
				PushStack(OS, ch);
				printf("%c\n", c);
				break;
			case '*':              // �˳����ȼ���ߣ�����ͬ���ȼ��ĳ˺ͳ���������ջ
			case '/':
				while(OS->top != -1 && (*((char*)OS->array[OS->top]) == '/' || *((char*)OS->array[OS->top]) == '*'))
					cal(NS, OS);
				ch = (char*)malloc(sizeof(char)); 
				*ch = c;
				PushStack(OS, ch);	//��'*''/'����ջ 
				printf("%c\n", c);
				break;
			case '(':        // '(' �������㣬ֱ�ӷ���optorջ��
				ch = (char*)malloc(sizeof(char)); 
				*ch = c;
				PushStack(OS, ch);
				printf("%c\n", c);
				break;
			case ')':        // �� '(' ֮ǰ��ȫ�������������������� '(' Ҳ����
				while( *((char*)OS->array[OS->top]) != '(')
					cal(NS, OS);
				PopStack(OS);	//����'(' 
				printf("%c\n", c);
				break;
			case '\n':        // �����µĲ�����ȫ�������������������
				while(OS->top != -1)
					cal(NS, OS);
				printf("the result is %lf\n", *((double*)NS->array[NS->top]));
				PopStack(NS);	//���ջ��Ԫ�ص��������ջ 
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
	while ((s[0] = c = getchar()) == ' ' || c == '\t')	//ȥ����ͷ�Ŀո� 
    ;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')	//�����ֵ���� 
		return c; 
	
	i = 0;
	if (isdigit(c)) 	//���ֵ��������������S�� 
		while (isdigit(s[++i] = c = getchar())) ;
	
	if (c == '.') 	//����С���㣬��С������S 
		while (isdigit(s[++i] = c = getchar()))  ;
	
	s[i] = '\0';	//��ֹ 
	if (c != EOF)  ungetc(c, stdin);	//�������EOF����C�Ż�ȥ 
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
	double* DR;		//��������� 
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
