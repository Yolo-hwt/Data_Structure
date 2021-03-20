
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define Status int
#define MAXSIZE 100
#define path1 "E:\\Huffman\\HuffmanTree.txt"
#define path2 "E:\\Huffman\\HuffmanCode.txt"

typedef struct HUffMANTree{
	int weight;//Ȩֵ
	int parent, lchild, rchild;//˫�׼����Һ���
	char CH;
}HTNode,*HuffmanTree;//�շ�����

typedef char** HuffmanCode;//�շ�������ָ������

typedef struct NumberNode {
	int ww;//���Ϲ�������Ϊ��ʶ��0��δ���ϣ�1��ʾ�����ϣ�>1ֵ��ʾ�����ظ���������ΪƵ�ȣ�Ȩֵ
	char cc;
	NumberNode* next;
}NNode,*Num;

typedef NNode** NUMBER;//���Ϲ���Ȩֵָ������


//���Ϲ����������
void Destroy(Num &list)
{
	Num del = list;
	Num note = NULL;
	while (del!=NULL)
	{
		note = del->next;
		free(del);
		del = note;
	}
	list = NULL;
	return ;
}

//�����ַ����������ַ�������
Status MangeStr(char*str,NUMBER w)
{
	int i,j,m;
	i = 0; j = 0; m = 0;
	Num head,temp,end;
	head = NULL; end = NULL;
	Num cur,p;
	char c;
	c = str[i];
	//�������ַ���Ϊģ������Num����
	while (c!='\0')
	{
		if (!head)
		{
			head = (Num)malloc(sizeof(NNode));
			head->ww = 0;head->cc = c;
			head->next = NULL;
			end = head;
			++i;
			c = str[i];
		}
		else
		{
		temp = (Num)malloc(sizeof(NNode));
		temp->ww = 0;//��ʶΪ0����ʾ������δ����
		temp->cc = c;
		end->next = temp;end = temp;end->next = NULL;
		++i;
		c = str[i];
		}
	}
	cur = head;
	while(cur)
	{
		if (cur->ww == 0)
		{
			cur->ww = 1;//��Ǵ�����Ϊ������
			w[j] = (Num)malloc(sizeof(NNode));
			w[j]->ww = 1; w[j]->cc = cur->cc;
			c = cur->cc;
			p = head;
			while(p)
			{
				if (p->cc == c && p->ww == 0)//Ѱ��temp���ַ���ͬ��δ������
				{
					p->ww = 1;//��Ǵ�����Ϊ������
					w[j]->ww++;
				}
				p = p->next;
			}
			j++;
		}
		cur = cur->next;
	}
	Destroy(head);
	return j;
}

//�շ�������ʼ��
void InitHffman(HuffmanTree &HT, NUMBER w, int n)
{
	HuffmanTree p=NULL;
	if (n <= 1)
		return;
	int m, i; //�շ�����������
	m= 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	HT[0] = { -1 ,-1,-1,'-1'};
	for (i = 1, p = HT, ++p; i <= n; ++i, ++p, ++w)//ǰn����Ȩֵ
		*p = { (*w)->ww,0,0,0,(*w)->cc};
	for (i; i <= m; ++i, ++p)//ʣ���ʼ��Ϊ0
		*p = { 0,0,0,0,'0' };

}

//��������Ѱ����С��˫����Ȩֵ�±�
void Select(HuffmanTree& HT, int range, int& s1, int& s2)
{
	HuffmanTree p=NULL;
	int i,j,h;
	i = 1;j = 1;h = 1;
	int temp1;
	int save[MAXSIZE] = { 0 };
	save[0] = -1;//0�ŵ�Ԫ�������ã���շ�����λ��ͳһ
	
	for (p = HT, ++p; i <= range; ++i,++p)//������������ȨֵΪ���鸳ֵ
	{
		if (p->parent == 0)
		{
			save[h] = p->weight;
			h++;
		}		
	}
	//��Ȩֵ�������������ҵ���С��λȨֵ
	for (i = 1; i <=h-1; i++)
	{
		temp1 = save[i];
		for (j = i + 1; j <=h-1; j++)
		{
			if (temp1 > save[j])
			{
				temp1 = save[j];
				save[j] = save[i];
				save[i] = temp1;
			}
		}
	}
	i = 1;
	for (p = HT, ++p; i <= range; ++p, ++i)
	{
		//�ȶԹ���������ʱ���ݣ�������Сֵ�±�s1
		if (p->parent == 0 && p->weight == save[1])
		{
			s1 = i;
			break;
		}
	}
	i = 1;
	for (p = HT, ++p; i <= range; ++p, ++i)
	{
		//�ȶԹ���������ʱ���ݣ������Сֵ�±�s2
		if (p->parent == 0 && p->weight == save[2]&&i!=s1)
		{
			s2 = i;
			break;
		}
	}
}

//��ӡ�շ�����
void printHT(HuffmanTree HT,int n) 
{
	int i;
	
	printf("---------------------------------------------\n");
	printf("%-8s%-8s%-8s%-8s%-8s%-8s\n", "���", "�ַ�", "Ȩֵ", "˫��", "����", "�Һ���");
	for (i = 1; i <= 2 * n - 1; i++)
		printf("%-8d%-8c%-8d%-8d%-8d%-8d\n", i, HT[i].CH, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	printf("---------------------------------------------\n");
}

//��ӡ����������
void printHC(HuffmanCode HC, HuffmanTree HT,int n)
{
	int i;
	printf("�շ������ѱ��룺\n");
	printf("------------------------------------\n");
	printf("%-5s%-5s%-20s\n", "���", "�ַ�", "�շ�������");
	for (i = 1; i <= n; i++)
		printf("%-5d%-5c%-20s\n", i, HT[i].CH, HC[i]);
	printf("------------------------------------\n");

}

//�����շ�����������д���ļ�HuffmanTree��HuffmanCode
Status CreatHuffman(HuffmanTree&HT,HuffmanCode& HC, int n)
{
	int m, i,s1,s2,site,c,f; //�շ�����������
	m = 2 * n - 1;
	char* cd;
	FILE* fp,*fh;
	//���ļ�
	fp = fopen(path1, "w");
	if (!fp)
		return ERROR;

	for (i = n + 1; i <= m; ++i)
	{
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	printf("�����շ��������£�\n");
	printHT(HT, n);
	//д���ļ�
		(fp, "%-8s%-8s%-8s%-8s%-8s%-8s\n", "���", "�ַ�", "Ȩֵ", "˫��", "����", "�Һ���");
	for (i = 1; i <=2 * n - 1; i++)
		fprintf(fp, "%-8d%-8c%-8d%-8d%-8d%-8d\n", i, HT[i].CH, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	fclose(fp);
	printf("���������Ѵ���HuffmanTree.txt�ĵ���..\n");

	//�շ�������
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));//�շ�������ͷָ��������0�ŵ�Ԫδ��

	cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++)
	{
		site = n - 1;
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
			if (HT[f].lchild == c)
				cd[--site] = '0';
			else
				cd[--site] = '1';
			HC[i] = (char*)malloc((n-site)*sizeof(char));//Ϊ�ַ��ĺշ����������ռ�
			strcpy(HC[i], &cd[site]);
	}
	printHC(HC, HT, n);
	//���ļ�
	fh = fopen(path2, "w");
	if (!fh)
		return ERROR;
	//д���ļ�
	fprintf(fh, "%-5s%-5s%-20s\n", "���", "�ַ�","�շ�������");
	for (i = 1; i <= n; i++) 
		fprintf(fh, "%-5d%-5c%-20s\n", i, HT[i].CH, HC[i]);
	fclose(fh);

	printf("�շ��������Ѵ���HuffmanCode.txt\n");
	free(cd);
	return OK;
}

//�������01���н���
void Decode(HuffmanTree &HT,int n)
{
	int i,j;
	i = 2*n - 1;
	j = 0;
	char sec[MAXSIZE];
	char endflag = '2';
	printf("���ݺշ�����������������01���У���2��β����\n");
	gets_s(sec);
	printf("��Ӧ����Ϊ��");
	while (sec[j] != '2')
	{
		if (sec[j] == '1')
			i = HT[i].rchild;
		else
			i = HT[i].lchild;
		if (HT[i].lchild == 0)
		{
			printf("%c", HT[i].CH);//��ȡһ������
			i = 2 * n - 1;//�ص����ڵ�
		}
		j++;	
	}
	printf("\n");
	if ((HT[i].lchild != 0)&&(i!=2*n-1) && (sec[j]= '2'))   //���ж��꣬����δ��Ҷ�ӽ��
		printf("\nERROR INPUT!\a\n");  //��������д�
}

int main()
{
	HuffmanTree HT;//�շ�����
	HuffmanCode HC;//�շ�������
	NUMBER w;//�����ַ����ṹ����������

	int i,n=0;
	char str[MAXSIZE];

	printf("��������������У�\n");
	gets_s(str);
	w = (NUMBER)malloc(strlen(str) * sizeof(NNode*));//Ȩֵͷָ������
	n=MangeStr(str, w);//�����ַ����������ַ�������
	printf("�ַ�������Ϊ��%d\n", n);
	printf("�����ַ�����Ϊ��\n");
	printf("%-8s%-8s\n", "�ַ�","Ȩֵ");

	for (i = 0; i < n; i++)
	{
		printf("%-8c%-8d\n", w[i]->cc, w[i]->ww);
	}

	InitHffman(HT, w, n);//�շ�������ʼ��
	printf("��ʼ����շ�����Ϊ��\n");
		printHT(HT,n);
	CreatHuffman(HT, HC, n);//�շ���������������,��ӡ��д���ļ�
	Decode(HT, n);//�շ�������

	return OK;
}
