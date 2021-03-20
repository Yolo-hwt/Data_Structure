#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Status int
#define MAX 50
#define OK 1
#define ERROR 0
int a[MAX] = { 0 };
//�����Ƚϴ�С//��s1<s2������ֵ
Status Comper(int s1, int s2)
{
	if (s1 >= s2)
		return ERROR;
	else
		return OK;
}
//ֱ�Ӳ�������
void InsertSort(int *s,int length)
{
	int i,j,index,move;
	index = 0; move = 0;
	int temp[MAX] = { 0 };
	for ( i=0; i <length; i++)
			temp[i + 1] = s[i];//0�ŵ�Ԫ�䵱�ڱ�
	for (i = 2; i <= length; i++)
		if (Comper(temp[i], temp[i - 1]))
		{
			temp[0] = temp[i];
			temp[i] = temp[i - 1]; move++;//���ϴ��i-1����ֵ�Ƶ�iλ��
			for (j = i - 2; Comper(temp[0], temp[j]); --j)
			{
				temp[j + 1] = temp[j];//jָʾ��ֵ�����ڱ�ֵ���¼������j+1��
				index++;//ComperΪ��ʱ�Ƚ�
			}
			index++;//����ѭ����δ����ѭ�����ڲ�����ComperΪ0ֵʱ��Ƚ�
			temp[j + 1] = temp[0];
		}
		
	printf("ֱ�����������Ϊ��");
	for (i = 1; i <= length; i++)
		printf("%d ", temp[i]);
	printf("\n");
	printf("���ݱȽϴ���Ϊ��%d\n", index+length);//���ⲿ���forѭ����������i��i-1�Ƚ��ܼƻ���length�αȽ�
		printf("�����ƶ�����Ϊ��%d\n", move);
}
//��ѡ������
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
				index = j;//index����i+1֮����Сֵ�±�
				t = temp[j];
			}
			times++;
		}
			
		//����
		if (index != i)
		{move++;
				t = temp[i];
				temp[i] = temp[index];
				temp[index] = t;

		}
			

	}
	printf("��ѡ�����������Ϊ��");
	for (i = 0; i < length; i++)
		printf("%d ", temp[i]);
	printf("\n");
	printf("���ݱȽϴ���Ϊ��%d\n", times);//���ⲿ���forѭ����������i��i-1�Ƚ��ܼƻ���length�αȽ�
	printf("�����ƶ�����Ϊ��%d\n", move);
}
//ð������
void BubbleSort(int *s,int length)
{
	int i,j,t,move,times;
	move = 0; times = 0;
	int temp[MAX] = { 0 };
	for (i = 0; i < length; i++)
		temp[i] = s[i];
		
		for (i = 0; i < length - 1; i++) {
			for (j = 0; j < length - 1 - i; j++) {
				if (temp[j] > temp[j + 1]) {        // ����Ԫ�������Ա�
					t = temp[j + 1];        // Ԫ�ؽ���
					temp[j + 1] = temp[j];
					temp[j] = t;
					move++;
				}
				times++;
			}
		}
		
		printf("ð�����������Ϊ��");
		for (i = 0; i < length; i++)
			printf("%d ", temp[i]);
		printf("\n");
		printf("���ݱȽϴ���Ϊ��%d\n", times);//���ⲿ���forѭ����������i��i-1�Ƚ��ܼƻ���length�αȽ�
		printf("�����ƶ�����Ϊ��%d\n", move);

}
//��������
Status Partition(int *s, int low, int high,int &times,int& move)//��������λ��
{
	int piv;//����λ��
	int temp,l,h;
	l = low; h = high;
	piv = s[l];
	while (l< h)
	{
		while (l < h && s[h] >= piv)
		{--h;
		times++;
		}
		//����λ��
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
		//�Ըߵ��ӱ�ݹ�����
		QSort(s, l, pivloc - 1, times, move);		
		QSort(s, pivloc + 1,h, times, move);
	}

}
int main()
{
	char c;
	int i=0;//�������ݸ���_������
	int times, move;//��¼���������бȽϴ������ƶ�����
	times = 0; move = 0;
	printf("��������������ݣ�\n");
	while (OK)
	{
		scanf("%d", &a[i]);
		c = getchar();//��������������������
		i++;
		if (c == '\n')
			break;
	}
	InsertSort(a, i);
	SelectSort(a, i);
	BubbleSort(a, i);
	//��������
	int temp[MAX] = { 0 };
	for (int j=0; j < i; j++)
		temp[j] = a[j];//0�ŵ�Ԫ��������ֵ
	QSort(temp, 0, i-1,times,move);
	printf("�������������Ϊ��");
	for (int j=0; j <i; j++)
		printf("%d ", temp[j]);
	printf("\n");
	printf("���ݱȽϴ���Ϊ��%d\n", times);
	printf("�����ƶ�����Ϊ��%d\n", move);
	return 0;
}
	
	
