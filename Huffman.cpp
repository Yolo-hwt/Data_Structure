
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
	int weight;//权值
	int parent, lchild, rchild;//双亲及左右孩子
	char CH;
}HTNode,*HuffmanTree;//赫夫曼树

typedef char** HuffmanCode;//赫夫曼编码指针向量

typedef struct NumberNode {
	int ww;//整合过程中作为标识，0则未整合，1表示已整合，>1值表示数据重复次数，即为频度，权值
	char cc;
	NumberNode* next;
}NNode,*Num;

typedef NNode** NUMBER;//整合过程权值指针向量


//整合过程链表清空
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

//整合字符串并返回字符种类数
Status MangeStr(char*str,NUMBER w)
{
	int i,j,m;
	i = 0; j = 0; m = 0;
	Num head,temp,end;
	head = NULL; end = NULL;
	Num cur,p;
	char c;
	c = str[i];
	//以输入字符串为模板生成Num链表
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
		temp->ww = 0;//标识为0，表示此数据未整合
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
			cur->ww = 1;//标记此数据为已整合
			w[j] = (Num)malloc(sizeof(NNode));
			w[j]->ww = 1; w[j]->cc = cur->cc;
			c = cur->cc;
			p = head;
			while(p)
			{
				if (p->cc == c && p->ww == 0)//寻找temp中字符相同且未整合项
				{
					p->ww = 1;//标记此数据为已整合
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

//赫夫曼树初始化
void InitHffman(HuffmanTree &HT, NUMBER w, int n)
{
	HuffmanTree p=NULL;
	if (n <= 1)
		return;
	int m, i; //赫夫曼树结点个数
	m= 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	HT[0] = { -1 ,-1,-1,'-1'};
	for (i = 1, p = HT, ++p; i <= n; ++i, ++p, ++w)//前n个赋权值
		*p = { (*w)->ww,0,0,0,(*w)->cc};
	for (i; i <= m; ++i, ++p)//剩余初始化为0
		*p = { 0,0,0,0,'0' };

}

//哈夫曼树寻找最小无双亲两权值下标
void Select(HuffmanTree& HT, int range, int& s1, int& s2)
{
	HuffmanTree p=NULL;
	int i,j,h;
	i = 1;j = 1;h = 1;
	int temp1;
	int save[MAXSIZE] = { 0 };
	save[0] = -1;//0号单元舍弃不用，与赫夫曼树位置统一
	
	for (p = HT, ++p; i <= range; ++i,++p)//遍历符合条件权值为数组赋值
	{
		if (p->parent == 0)
		{
			save[h] = p->weight;
			h++;
		}		
	}
	//以权值升序排列数组找到最小两位权值
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
		//比对哈夫曼树此时数据，保存最小值下标s1
		if (p->parent == 0 && p->weight == save[1])
		{
			s1 = i;
			break;
		}
	}
	i = 1;
	for (p = HT, ++p; i <= range; ++p, ++i)
	{
		//比对哈夫曼树此时数据，保存次小值下标s2
		if (p->parent == 0 && p->weight == save[2]&&i!=s1)
		{
			s2 = i;
			break;
		}
	}
}

//打印赫夫曼树
void printHT(HuffmanTree HT,int n) 
{
	int i;
	
	printf("---------------------------------------------\n");
	printf("%-8s%-8s%-8s%-8s%-8s%-8s\n", "序号", "字符", "权值", "双亲", "左孩子", "右孩子");
	for (i = 1; i <= 2 * n - 1; i++)
		printf("%-8d%-8c%-8d%-8d%-8d%-8d\n", i, HT[i].CH, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	printf("---------------------------------------------\n");
}

//打印哈夫曼编码
void printHC(HuffmanCode HC, HuffmanTree HT,int n)
{
	int i;
	printf("赫夫曼树已编码：\n");
	printf("------------------------------------\n");
	printf("%-5s%-5s%-20s\n", "序号", "字符", "赫夫曼编码");
	for (i = 1; i <= n; i++)
		printf("%-5d%-5c%-20s\n", i, HT[i].CH, HC[i]);
	printf("------------------------------------\n");

}

//创建赫夫曼树并编码写入文件HuffmanTree，HuffmanCode
Status CreatHuffman(HuffmanTree&HT,HuffmanCode& HC, int n)
{
	int m, i,s1,s2,site,c,f; //赫夫曼树结点个数
	m = 2 * n - 1;
	char* cd;
	FILE* fp,*fh;
	//打开文件
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
	printf("创建赫夫曼树如下：\n");
	printHT(HT, n);
	//写入文件
		(fp, "%-8s%-8s%-8s%-8s%-8s%-8s\n", "序号", "字符", "权值", "双亲", "左孩子", "右孩子");
	for (i = 1; i <=2 * n - 1; i++)
		fprintf(fp, "%-8d%-8c%-8d%-8d%-8d%-8d\n", i, HT[i].CH, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	fclose(fp);
	printf("哈夫曼树已存入HuffmanTree.txt文档中..\n");

	//赫夫曼编码
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));//赫夫曼编码头指针向量，0号单元未用

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
			HC[i] = (char*)malloc((n-site)*sizeof(char));//为字符的赫夫曼编码分配空间
			strcpy(HC[i], &cd[site]);
	}
	printHC(HC, HT, n);
	//打开文件
	fh = fopen(path2, "w");
	if (!fh)
		return ERROR;
	//写入文件
	fprintf(fh, "%-5s%-5s%-20s\n", "序号", "字符","赫夫曼编码");
	for (i = 1; i <= n; i++) 
		fprintf(fh, "%-5d%-5c%-20s\n", i, HT[i].CH, HC[i]);
	fclose(fh);

	printf("赫夫曼编码已存入HuffmanCode.txt\n");
	free(cd);
	return OK;
}

//对输入的01序列解码
void Decode(HuffmanTree &HT,int n)
{
	int i,j;
	i = 2*n - 1;
	j = 0;
	char sec[MAXSIZE];
	char endflag = '2';
	printf("根据赫夫曼编码输入待解码的01序列（以2结尾）：\n");
	gets_s(sec);
	printf("相应解码为：");
	while (sec[j] != '2')
	{
		if (sec[j] == '1')
			i = HT[i].rchild;
		else
			i = HT[i].lchild;
		if (HT[i].lchild == 0)
		{
			printf("%c", HT[i].CH);//读取一个译码
			i = 2 * n - 1;//回到根节点
		}
		j++;	
	}
	printf("\n");
	if ((HT[i].lchild != 0)&&(i!=2*n-1) && (sec[j]= '2'))   //序列读完，但尚未到叶子结点
		printf("\nERROR INPUT!\a\n");  //输入电文有错
}

int main()
{
	HuffmanTree HT;//赫夫曼树
	HuffmanCode HC;//赫夫曼编码
	NUMBER w;//整合字符串结构体数组向量

	int i,n=0;
	char str[MAXSIZE];

	printf("任意输入符号序列：\n");
	gets_s(str);
	w = (NUMBER)malloc(strlen(str) * sizeof(NNode*));//权值头指针向量
	n=MangeStr(str, w);//整合字符串，返回字符种类数
	printf("字符种类数为：%d\n", n);
	printf("整合字符串后为：\n");
	printf("%-8s%-8s\n", "字符","权值");

	for (i = 0; i < n; i++)
	{
		printf("%-8c%-8d\n", w[i]->cc, w[i]->ww);
	}

	InitHffman(HT, w, n);//赫夫曼树初始化
	printf("初始化后赫夫曼树为：\n");
		printHT(HT,n);
	CreatHuffman(HT, HC, n);//赫夫曼树创建及编码,打印并写入文件
	Decode(HT, n);//赫夫曼解码

	return OK;
}
