#include <stdio.h>
#include <math.h>

void swap(int *a,int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}


//简单选择排序
void SelectSort(int r[],int n)
{
	int i, min, j;
	for(i = 0;i < n-1; i++)
	{
		min = i;
		for(j = i;j < n; j++)
			if(r[j] < r[min]) min = j;
		swap(&r[i], &r[min]);
	} 
}

//堆排序
void Sift(int r[], int n, int k)  //调整r[]中的结点k,使其成为堆
{
	int i, j, t;
	i = k; j = 2*i+1; t = r[i];
	while(j < n) {
		if(j < n - 1 && r[j] < r[j+1]) j++;
		if(t < r[j]) {
			r[i] = r[j]; 
			i = j;
			j = 2*i+1;
		}
		else break;
	}
	r[i] = t;
}

void BSift(int r[],int n)
{
	int p = (n - 2)/2, i;
	for(i = p;i >= 0; i--)	Sift(r, n, i);
}

void HeapSort(int r[], int n)
{
	int i;
	BSift(r, n);
	for(i = n-1;i >= 0; i--)
	{
		swap(&r[0], &r[i]);
		Sift(r, i, 0);
	}
}


//插入排序
void InsertSort(int r[], int n)
{
	int i, j;
	for(i = 1;i < n; i++)
	{
		j = i-1;
		while(j >= 0)
		{
			if(r[j] > r[j+1]) swap(&r[j], &r[j+1]);
			j--;
		}
	}
}


//希尔排序
void ShellSort(int r[], int n)
{
	int i,j,k,h;
	int t;
	int m, index;
	int H[50];

	m=(int)(log(n)/log(2));
	for(index=0;index<m;index++)
	{
		H[index]=(int)(pow(2,index));
	}

	//希尔排序的增量序列存放在H中, H[0] = 1
	for(i = 0;i < m; i++)
	{
		h = H[m-1-i];
		for(j = 0;j < h; j++)
		{
			for(k = j+h;k < n;k = k+h)
			{
				t = k-h;
				while(t >= 0)
				{
					if(r[t] > r[t+h]) swap(&r[t], &r[t+h]);
					t = t-h;
				}
			}
		}
	}
}


//冒泡排序
void Bsort(int r[], int n)
{
	int i,j; 
	for( i = 0;i < n-1; i++)
	{
		for( j = 0; j < n-1-i; j++)
		{
			if(r[j] > r[j+1]) swap(&r[j], &r[j+1]);
		}
	}
}

//快速排序
void Qksort(int r[],  int  low,  int high)
{	
	if(low >= high) return;
	
	int key = r[low];
	int i = low;
	int j = high;
	
	while(i < j)
	{
		while(i < j && r[j] >= key) j--;
		r[i] = r[j];
		while(i < j && r[i] <= key) i++;
		r[j] = r[i];
	} 

	r[i] = key;
	Qksort(r, low, i-1);
	Qksort(r, i+1, high);
}


int main()
{
	int num[100];
	int n,i,sel;

	printf("输入数据长度:");
	scanf("%d",&n);
	printf("依次输入%d个数据:\n",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&num[i]);
	}
	
	printf("请选择排序方式:\n");
	printf(" ---- 选择排序:1\n");
	printf(" ---- 堆排序  :2\n");
	printf(" ---- 插入排序:3\n");
	printf(" ---- 希尔排序:4\n");
	printf(" ---- 冒泡排序:5\n");
	printf(" ---- 快速排序:6\n");
	scanf("%d",&sel);

	switch(sel)
    {
		case 1:SelectSort(num,n);break;
		case 2:HeapSort(num,n);break;
		case 3:InsertSort(num,n);break;
		case 4:ShellSort(num,n);break;
		case 5:Bsort(num,n);break;
		case 6:Qksort(num, 0,n-1);break;
	}

	
	printf("排序结果为:");
	for(i=0;i<n;++i)
	{
		printf("%d ",num[i]);
	}
	printf("\n");
	return 0;
}

