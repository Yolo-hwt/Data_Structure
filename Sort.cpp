#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Status int
#define MAX 50
#define OK 1
#define ERROR 0
int a[MAX] = { 0 };
//两数比较大小//若s1<s2返回真值
Status Comper(int s1, int s2)
{
	if (s1 >= s2)
		return ERROR;
	else
		return OK;
}
//直接插入排序
void InsertSort(int *s,int length)
{
	int i,j,index,move;
	index = 0; move = 0;
	int temp[MAX] = { 0 };
	for ( i=0; i <length; i++)
			temp[i + 1] = s[i];//0号单元充当哨兵
	for (i = 2; i <= length; i++)
		if (Comper(temp[i], temp[i - 1]))
		{
			temp[0] = temp[i];
			temp[i] = temp[i - 1]; move++;//将较大的i-1储存值移到i位置
			for (j = i - 2; Comper(temp[0], temp[j]); --j)
			{
				temp[j + 1] = temp[j];//j指示的值大于哨兵值则记录后移至j+1处
				index++;//Comper为真时比较
			}
			index++;//跳出循环后未进入循环体内部，即Comper为0值时候比较
			temp[j + 1] = temp[0];
		}
		
	printf("直接排序后数据为：");
	for (i = 1; i <= length; i++)
		printf("%d ", temp[i]);
	printf("\n");
	printf("数据比较次数为：%d\n", index+length);//由外部最大for循环控制数据i与i-1比较总计还有length次比较
		printf("数据移动次数为：%d\n", move);
}
//简单选择排序
void SelectSort(int *s,int length)
{
	int index,i,j,t,move,times;
	move = 0; times = 0;
	int temp[MAX] = { 0 };
	for (i = 0; i < length; i++)
		temp[i] = s[i];
	for (i = 0; i < length-1; i++)
	{
		index = i; t = temp[i];
		for (j = i+1; j < length; j++)
		{
			if (temp[j] < t) {
				index = j;//index保存i+1之后最小值下标
				t = temp[j];
			}
			times++;
		}
			
		//交换
		if (index != i)
		{move++;
				t = temp[i];
				temp[i] = temp[index];
				temp[index] = t;

		}
			

	}
	printf("简单选择排序后数据为：");
	for (i = 0; i < length; i++)
		printf("%d ", temp[i]);
	printf("\n");
	printf("数据比较次数为：%d\n", times);//由外部最大for循环控制数据i与i-1比较总计还有length次比较
	printf("数据移动次数为：%d\n", move);
}
//冒泡排序
void BubbleSort(int *s,int length)
{
	int i,j,t,move,times;
	move = 0; times = 0;
	int temp[MAX] = { 0 };
	for (i = 0; i < length; i++)
		temp[i] = s[i];
		
		for (i = 0; i < length - 1; i++) {
			for (j = 0; j < length - 1 - i; j++) {
				if (temp[j] > temp[j + 1]) {        // 相邻元素两两对比
					t = temp[j + 1];        // 元素交换
					temp[j + 1] = temp[j];
					temp[j] = t;
					move++;
				}
				times++;
			}
		}
		
		printf("冒泡排序后数据为：");
		for (i = 0; i < length; i++)
			printf("%d ", temp[i]);
		printf("\n");
		printf("数据比较次数为：%d\n", times);//由外部最大for循环控制数据i与i-1比较总计还有length次比较
		printf("数据移动次数为：%d\n", move);

}
//快速排序
Status Partition(int *s, int low, int high,int &times,int& move)//返回枢轴位置
{
	int piv;//枢轴位置
	int temp,l,h;
	l = low; h = high;
	piv = s[l];
	while (l< h)
	{
		while (l < h && s[h] >= piv)
		{--h;
		times++;
		}
		//交换位置
		temp = s[l];
		s[l] = s[h]; 
		s[h] = temp;
		move++;
		while (l < h && s[h] <= piv)
		{++l;
		times++;
		}
		temp = s[l];
		s[l] = s[h];
		s[h] = temp;
		move++;
	}
	return l;
}
void QSort(int* s, int low, int high,int &times,int &move)
{
	int pivloc;
	int l, h;
	l = low; h = high;
	if (l < h)
	{
		pivloc = Partition(s, l, h,times,move);		
		//对高低子表递归排序
		QSort(s, l, pivloc - 1, times, move);		
		QSort(s, pivloc + 1,h, times, move);
	}

}
int main()
{
	char c;
	int i=0;//输入数据个数_计数器
	int times, move;//记录快速排序中比较次数及移动次数
	times = 0; move = 0;
	printf("请输入待排序数据：\n");
	while (OK)
	{
		scanf("%d", &a[i]);
		c = getchar();//控制整型数组数据输入
		i++;
		if (c == '\n')
			break;
	}
	InsertSort(a, i);
	SelectSort(a, i);
	BubbleSort(a, i);
	//快速排序
	int temp[MAX] = { 0 };
	for (int j=0; j < i; j++)
		temp[j] = a[j];//0号单元保存枢轴值
	QSort(temp, 0, i-1,times,move);
	printf("快速排序后数据为：");
	for (int j=0; j <i; j++)
		printf("%d ", temp[j]);
	printf("\n");
	printf("数据比较次数为：%d\n", times);
	printf("数据移动次数为：%d\n", move);
	return 0;
}
	
	
