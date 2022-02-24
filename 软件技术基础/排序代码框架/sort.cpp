#include <stdio.h>
#include <math.h>

void swap(int *a,int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}


//��ѡ������
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

//������
void Sift(int r[], int n, int k)  //����r[]�еĽ��k,ʹ���Ϊ��
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


//��������
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


//ϣ������
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

	//ϣ��������������д����H��, H[0] = 1
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


//ð������
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

//��������
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

	printf("�������ݳ���:");
	scanf("%d",&n);
	printf("��������%d������:\n",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&num[i]);
	}
	
	printf("��ѡ������ʽ:\n");
	printf(" ---- ѡ������:1\n");
	printf(" ---- ������  :2\n");
	printf(" ---- ��������:3\n");
	printf(" ---- ϣ������:4\n");
	printf(" ---- ð������:5\n");
	printf(" ---- ��������:6\n");
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

	
	printf("������Ϊ:");
	for(i=0;i<n;++i)
	{
		printf("%d ",num[i]);
	}
	printf("\n");
	return 0;
}

