// InsertSort.cpp : 定义控制台应用程序的入口点。
//我来过！

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
/*找最长递减后缀，它前面那个元素就是ai，它里面刚刚比ai大的那个元素就是aj*/
void find_ai_aj_swap_CreateSeries(int* a, int n, int lgps[][4])
{
/*aj[0]里面是aj,ai是ai在数组中的下标，de_length[]是后缀的长度*/
	int j = 0, i = 0, k = 0, h = 0, b[2] = { -2,-2 }, de_length[2] = { -2,-2 };
	int ai = -1, suffix_length = 0,aj[2],z=0,w=0;
/*先把初始序列写入结果数组，如果需要，可以在写入前先执行排增序操作*/
	for (z = 0; z < n; ++z)
		lgps[w][z] = a[z];
	++w;
	/*输入的是从小到大序列，首先交换最后两个元素，然后找ai，aj，交换，排序，每一轮循环得到两个序列*/
	do {
	swap(a+n-2,a+n-1);
	for (z = 0; z < n; ++z)
		lgps[w][z] = a[z];
	++w;
	{//找最长降序序列
		j = 0; i = 0;
		while (j < n - 1)
		{/*跳过递增序部分*/
			while (j < n - 1 && a[j] < a[j + 1])
				++j;
			if (j < n - 1)
			{//用两个数组，下标对应的记录ai的位置和降序的起始长度2
				b[i] = j - 1; de_length[i] = 2;	++j;
				//找降序序列的长度
				while (j < n - 1 && a[j] > a[j + 1])
				{
					++de_length[i]; ++j;
				}
				++i;
				//用一个两元素数组记录序列中多个降序的长度，保留长度长的记录或者靠后的记录
				if (i == 2)
				{
					if (de_length[0] > de_length[1])
					{//-2是无效数字，-1是完全降序的检测标准
						b[1] = -2; de_length[1] = -2;	i = 1;
					}
					else
					{
						b[0] = -2; de_length[0] = -2;	i = 0;
					}
				}
			}
		}
		//把当前的ai在数组中的下标记录b[0]记录在ai中，对应的长度记录在suffix_length
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
		//ai是-1的时候，已经是完全降序，如果不是，就需要找aj
		if (ai == -1) break;
		//找aj部分。一个数组记录两个比ai大的数，然后把小的保留在aj[0]，新的保存在aj[1]
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
		//找到aj后，与ai交换
		swap(a + ai, a + aj[0]);
	}
	//对整个数组ai后面的部分排增序，保存结果到生成排列数组
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

