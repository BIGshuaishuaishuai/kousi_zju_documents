#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct huffman_node 
{
	int data;
	int lchild;
	int rchild;
	int parent;
}bnode;  //定义二叉链表结点结构

void SelectIJ(int k, bnode node[], int *i, int *j)
{
	int x = -1, y = -1;
	for(int t = 0;t < k; t++)
	{
		if(node[t].parent == -1)
		{
			if(x == -1)
			{
				if(y == -1) y = t;
				else if(node[t].data > node[y].data) {
					x = y;
					y = t;
				}
				else x = t;
			}
			else if(node[t].data < node[y].data) {
				if(node[t].data < node[x].data) {
					y = x;
					x = t;
				}
				else y = t;
			}
		}
	}
	
	*i = x;
	*j = y;
	//printf("root %d %d, left %d %d, right %d %d\n", k, node[x].data+node[y].data, x, node[x].data, y,node[y].data);
}

void HuffmanTree(int n, bnode node[],int w[])
{
	int i, j, k;
	
	for(k = 0;k < n; k++) {
		node[k].data = w[k];
		node[k].lchild =node[k].rchild = -1;
	} 
	for(k = 0;k < 2*n-1; k++) {
		node[k].parent = -1;
	}
	for(k = n;k < 2*n-1; k++) {
		SelectIJ(k, node, &i, &j);
		node[k].data = node[i].data + node[j].data;
		node[k].lchild = i;
		node[k].rchild = j;
		node[i].parent = node[j].parent = k;
	}
}

//建议用递归比较容易 
void coding ( bnode *node, char scode[26][26], int root, char *str, int n)
{
	if(root < 26 && root >= 0) {
		strcpy(scode[root], str);
	}
	else {
		if(node[root].lchild != -1)
		{
			str[n] = '0';
			coding(node, scode, node[root].lchild, str, n+1);
			str[n] = 0;
		}
		if(node[root].rchild != -1)
		{
			str[n] = '1';
			coding(node, scode, node[root].rchild, str, n+1);
			str[n] = 0;
		}
	}
}

int main(void)
{
	FILE *fp;
	int weight[26];

	int i,j;
	int ch;
	int n;

	bnode *node;
	unsigned long code;

	for(i=0; i<26; i++)
	{
		weight[i] = 0;
	}

	if( (fp = fopen("StrayBirds.txt","r")) == NULL )
		return 0;

	do {
		ch = fgetc(fp);

		if (!( ((ch>=97)&&(ch<=122)) ||
			   ((ch>=65)&&(ch<=90 ))	 )
		   )
		{
			continue;
		}
		if( (ch>=97)&&(ch<=122) )
		{
			ch -= 32;
		}
        putchar(ch);
		weight[ch-65]++;
	} while(feof(fp)==0);

	printf("\n");

	n = 0;
	for(i=0; i<26; i++)
	{
		if(weight[i] > 0) 
		{
			n++;
			printf("%c  %d \n", i+65, weight[i]);
		}
	}

	node = (bnode *)malloc((2*26-1) * sizeof(bnode));

	//建立哈夫曼树
	HuffmanTree(26, node, weight);

	//哈夫曼编码
	char scode[26][26] = {0};
	char* str;
	str = (char*)malloc(20);
	for(int i = 0; i < 20; i++) *(str+i) = 0;
	coding (node, scode, 50, str, 0);
	for (i=0; i<26; i++)
	{
		printf("Now processing %c.Its code is %s\n", i+65, scode[i]);
	}
	
	free(node);
	fclose(fp);
}
