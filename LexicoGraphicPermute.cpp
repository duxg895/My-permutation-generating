// InsertSort.cpp : �������̨Ӧ�ó������ڵ㡣
//��������

#include "stdafx.h"

void insert_sort(int* p,int n)
{
	int i,tmp,j;
	if (n > 2)
		insert_sort(p, n - 1);

		for (i = 0; i < n - 1; ++i)
		{
			if (p[i] < p[n - 1])continue;
			else
			{
				tmp = p[n - 1];
				for (j=n-1-i;j>0;--j)
				{
					p[i + j] = p[i+j-1];
				}
				p[i] = tmp;
			}
		}
}
void swap(int *a,int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;

}
/*����ݼ���׺����ǰ���Ǹ�Ԫ�ؾ���ai��������ոձ�ai����Ǹ�Ԫ�ؾ���aj*/
void find_ai_aj_swap_CreateSeries(int* a, int n, int lgps[][4])
{
/*aj[0]������aj,ai��ai�������е��±꣬de_length[]�Ǻ�׺�ĳ���*/
	int j = 0, i = 0, k = 0, h = 0, b[2] = { -2,-2 }, de_length[2] = { -2,-2 };
	int ai = -1, suffix_length = 0,aj[2],z=0,w=0;
/*�Ȱѳ�ʼ����д�������飬�����Ҫ��������д��ǰ��ִ�����������*/
	for (z = 0; z < n; ++z)
		lgps[w][z] = a[z];
	++w;
	/*������Ǵ�С�������У����Ƚ����������Ԫ�أ�Ȼ����ai��aj������������ÿһ��ѭ���õ���������*/
	do {
	swap(a+n-2,a+n-1);
	for (z = 0; z < n; ++z)
		lgps[w][z] = a[z];
	++w;
	{//�����������
		j = 0; i = 0;
		while (j < n - 1)
		{/*���������򲿷�*/
			while (j < n - 1 && a[j] < a[j + 1])
				++j;
			if (j < n - 1)
			{//���������飬�±��Ӧ�ļ�¼ai��λ�úͽ������ʼ����2
				b[i] = j - 1; de_length[i] = 2;	++j;
				//�ҽ������еĳ���
				while (j < n - 1 && a[j] > a[j + 1])
				{
					++de_length[i]; ++j;
				}
				++i;
				//��һ����Ԫ�������¼�����ж������ĳ��ȣ��������ȳ��ļ�¼���߿���ļ�¼
				if (i == 2)
				{
					if (de_length[0] > de_length[1])
					{//-2����Ч���֣�-1����ȫ����ļ���׼
						b[1] = -2; de_length[1] = -2;	i = 1;
					}
					else
					{
						b[0] = -2; de_length[0] = -2;	i = 0;
					}
				}
			}
		}
		//�ѵ�ǰ��ai�������е��±��¼b[0]��¼��ai�У���Ӧ�ĳ��ȼ�¼��suffix_length
		if (b[0] != -2)
		{
//			printf("i=%d, de_length=%d", b[0], de_length[0]);
			ai = b[0]; suffix_length = de_length[0];
		}
		else
		{
//			printf("i=%d, de_length=%d", b[1], de_length[1]);
			ai = b[1]; suffix_length = de_length[1];
		}
		//ai��-1��ʱ���Ѿ�����ȫ����������ǣ�����Ҫ��aj
		if (ai == -1) break;
		//��aj���֡�һ�������¼������ai�������Ȼ���С�ı�����aj[0]���µı�����aj[1]
		for (k = 1, h = 0; k <= suffix_length; k++)
			if (a[ai + k] > a[ai])
			{
				aj[h++] = ai + k;
				if (h == 2)
				{
					a[aj[0]] > a[aj[1]] ? swap(aj, aj + 1) : 0;
					h = 1;
				}
			}
//		printf("\naj=%d\n", a[aj[0]]);
		//�ҵ�aj����ai����
		swap(a + ai, a + aj[0]);
	}
	//����������ai����Ĳ��������򣬱�������������������
	insert_sort(a+ai+1, n-ai-1);
	for (z = 0; z < n; ++z)
		lgps[w][z] = a[z];
	++w;
	} while (ai!=-1 || w<24);
}

int main()
{
	int  a[10] = {34,12,765,4,2,76,68,30,69,29},i=0,j=0,k=0;
	int	 LexicoGraphicPermuteSeries[24][4] = {0};
	int  b[4] = {1,2,3,4};	
/*
	insert_sort(a,10);	
	printf("n=%d Results:",10);
	while (i < 10)
		printf("%d  ",a[i++]);
	printf("\n");
*/

	find_ai_aj_swap_CreateSeries(b, 4, LexicoGraphicPermuteSeries);
	printf("\n");
	for (j = 0; j < 24;++j)
	{
		for (k = 0; k < 4; ++k)
			printf("%d ", LexicoGraphicPermuteSeries[j][k]);
		printf("\n");
	}


	getchar();
	return 0;
}

