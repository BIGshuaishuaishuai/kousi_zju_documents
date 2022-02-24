#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define null 0
#define n 100

typedef int keytype;

typedef struct node
{
	keytype key;//�������������Ĺؼ�����
	struct node *lchild;
	struct node  *rchild;
}bstnode; //�������������ṹ

typedef bstnode *bstree;//�������������Ͷ���



void insertbst(bstree *tptr,keytype key)	//�ڶ���������tptr�У�����ֵΪkey�Ľ��
{
	bstree tree = (bstree)malloc(sizeof(bstnode));
	tree->key = key;
	tree->lchild = NULL;
	tree->rchild = NULL;
	
	if(*tptr == NULL)
	{
		*tptr = tree;
		return;
	} 
	
	bstree ptr = *tptr;
	while(1)
	{
		if(ptr->key >= key)
		{
			if(ptr->lchild == NULL)
			{
				ptr->lchild = tree;
				break;
			}
			ptr = ptr->lchild;
			continue;
		}
		if(ptr->rchild == NULL)
		{
			ptr->rchild = tree;
			break;
		}
		ptr = ptr->rchild;
	}
}//end of insertbst

void createbst(bstree *t)
{
	//����һ�ö���������t
	keytype key;
	int i,m;

	//�������100�����ڵ��������ɶ���������
	m = rand()%100;
	printf("random source data:");
	for(i=1; i<=m; i++)
	{
			key=rand()%100;;
			printf("%d ",key);
			insertbst(t,key);//���ؼ���key���뵽����������t��
	}
	printf("\n");
	
}//end of createbst 

void inorder(bstree t)
{
	//�Զ���������t�����������
	if (t)
	{
		inorder(t->lchild);//�������������
		printf(" %d",t->key);//���ʸ����
		inorder(t->rchild);//�������������
	}//end of if 
}//end of inorder


void main()//������
{
	bstree t=null,q=null;
	
	srand( (unsigned)time( NULL ) );
	
	createbst(&t);//����һ�ö���������t
	printf("\nbst data:");
	
	inorder(t);//�������������t�������������
	printf("\n");
}

