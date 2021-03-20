#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 10

//采用带头结点链表
typedef struct NormalNode {
	//一元多项式结点
	int coef;//系数
	int expo;//指数
	int length;//相应多项式长度,链表长度则+1
}Node;

typedef struct Poly {
	//多项式
	Node elem;//数据域
	struct Poly* next;//指针域
}*Polylist;

void Creatlist(Polylist *h,int n)//创建空多项式，n为多项式长度
{
	int index = 0;//位序
	int coeff=0;//系数临时变量
	int exopp = 0;//指数临时变量
	Polylist vule = NULL;//多项式临时变量
	Polylist pend = NULL;//尾指针

	//初始化头结点
	*h = (Polylist)malloc(sizeof(Poly));
	(*h)->elem.coef = 0;
	(*h)->elem.expo = 0;
	(*h)->elem.length = 0;//用以保存多项式长度
	//初始化尾结点
	pend = *h;
	(*h)->next = NULL;

	printf("输入多项式长度：");
	scanf_s("%d", &n);

	while (n)//0退出循环
	{
		printf("请输入第%d项的系数和指数： ",(index+1));
		scanf_s("%d %d", &coeff, &exopp);
		index++;
		n--;

		vule = (Polylist)malloc(sizeof(Poly));
		if (!vule)//vule分配空间为空
			exit(ERROR);
		//vule赋值
		vule->elem.coef = coeff;
		vule->elem.expo = exopp;
		vule->elem.length = index;

		if (!((*h)->next))//仅有头结点
		{
			(*h)->next = vule;
			pend = vule;
			pend->next = NULL;
		}
		else
		{
			pend->next = vule;
			pend = vule;
			vule->next = NULL;
		}
		
	}
	(*h)->elem.length = n;//头结点处保存多项式长度信息
	printf("\n");
}

void PrintPoly(Polylist *L)//打印多项式
{
	Polylist show=NULL;
	int co;
	int ex;
	if (!((*L)->next))
		printf("多项式为空！！！");
	else
	{
		
		show = (*L) ->next;
		while (show)
		{
			co = show->elem.coef;
			ex = show->elem.expo;
			//每一个数据后面的空格是细节
			if (co == 0)
				printf("0 ");
			else if (co != 0 && ex == 0)
				printf("%d ", co);
			else
			printf("%dX^%d ", co, ex);

			if (show->next)
				printf("+ ");
			show = show->next;
		}
	}
	printf("\n\n");
}

int Destroy(Polylist *list)//清空多项式
{
	int status = 0;//清空标识 0 初始值为未清空
	Polylist del = *list;
	Polylist note = NULL;
	while (del)
	{
		note = del->next;
		free(del);//由malloc分配的内存匹配free()函数进行内存释放
		del = note;
	}
	*list = NULL;
	if (!del && !(*list))
		status = 1;
		
	return status;	
}

void SortPoly(Polylist* l)//多项式排序及自身整和（降序）
{
	Polylist gather1,gather2;
	Polylist formart;

	//内部整理
	for (gather1 = (*l)->next; gather1->next != NULL; gather1 = gather1->next) 
	{
		Node ga1, ga2;
		formart = gather1;
		gather2 = gather1->next;
		while (gather2) {
			ga1 = gather1->elem;
			ga2 = gather2->elem;
			if (ga1.expo == ga2.expo) //指数相同，系数相加
			{
				gather1->elem.coef =ga1.coef + ga2.coef;
				formart->next = gather2->next;
				Polylist Todelete=gather2;
				gather2 = gather2->next;
				free(Todelete);
			}
			else//指针跳变
			{
				formart = formart->next;
				gather2 = gather2->next;
			}
		}
		
	}

	//降幂排序
	Polylist cur1;
	Polylist cur2;
	Node temp;
	cur1 = (*l)->next;
	while (cur1)
	{
		cur2 = cur1->next;
		if (!cur2)//到达多项式末尾-->退出循环
			break;
		for (cur2; cur2 != NULL; cur2 = cur2->next)
		{
			if (cur2->elem.expo > cur1->elem.expo)
			{
				temp.coef = cur2->elem.coef;
				temp.expo = cur2->elem.expo;
				cur2->elem = cur1->elem;
				cur1->elem = temp;
			}
		}
		cur1 = cur1->next;
	}

}

int SumPoly(Polylist* l1, Polylist* l2)//多项式求和(已降幂排序）
{//l2归并至l1求和

	Polylist pcur1 = (*l1)->next;
	Polylist pcur2 = (*l2)->next;
	//前向指针
	Polylist ptr1 = *l1;
	Polylist ptr2 = *l2;
	int coeff = 0;
	int expoo = 0;
	while (pcur1 && pcur2)
	{
		if (pcur1->elem.expo > pcur2->elem.expo)//多项式一中指数大于多项式二
		{
			//多项式一后移一位
			ptr1 = pcur1;
			pcur1 = pcur1->next;
		}
		else if (pcur1->elem.expo == pcur2->elem.expo)//多项式一中指数等于多项式二
		{
			coeff = pcur1->elem.coef + pcur2->elem.coef;
			if (coeff!=0)//系数不为0
			{
				pcur1->elem.coef = coeff;
				ptr1 = pcur1;
				pcur1 = ptr1->next;
			}
			else//合并后系数为0
			{
				ptr1->next = pcur1->next;
				free(pcur1);//释放p结点
				pcur1 = ptr1->next;
			}

			ptr2->next = pcur2->next;
			free(pcur2);//释放表二结点
			pcur2 = ptr2->next;
			
		}
		else//多项式一中指数小于多项式二
		{
			ptr2->next = pcur2->next;
			ptr1->next = pcur2;
			ptr1 = pcur2;
			pcur2->next = pcur1;
			pcur2 = ptr2->next;
		}
	}

	//将多项式一指针ptr1置于于多项式一表尾
	if (ptr1->next)
	{
		while (ptr1->next)
		{
			ptr1 = ptr1->next;
		}
	}

	if (pcur2)//多项式二中仍有元素
		ptr1->next = pcur2;
	else
		ptr1->next = NULL;
	
	(*l2)->next = NULL;

	return OK;
}

int AccumPoly(Polylist* l1, Polylist* l2)//多项式求积
{
	int i = 0;
	int time = 1;
	int size = (*l1)->elem.length;
	int coeff,expoo,lengthh;
	coeff = expoo = lengthh=0;

	Polylist head[MAXSIZE] = { NULL };//头结点指针数组

	Polylist end = NULL;
	Polylist vule = NULL;
	Polylist pcur1 = (*l1)->next;
	Polylist pcur2 = (*l2)->next;
	Polylist CUR = (*l2)->next;
	while (pcur1)
	{
		head[i]= (Polylist)malloc(sizeof(Poly));//新建头结点(每次多项式l1其中一项与l2遍历相乘所得链表）
		head[i]->elem.coef = 0;
		head[i]->elem.expo = 0;
		head[i]->elem.length = (*l2)->elem.length;
		head[i]->next = NULL;
		end = head[i];
		
		for (pcur2=CUR; pcur2 != NULL; pcur2 = pcur2->next)
		{
			coeff = pcur1->elem.coef * pcur2->elem.coef;//系数相乘
			expoo = pcur1->elem.expo + pcur2->elem.expo;//指数相加
			lengthh = pcur2->elem.length;

			vule= (Polylist)malloc(sizeof(Poly));
			vule->elem.coef = coeff;
			vule->elem.expo = expoo;
			vule->elem.length = lengthh;

			//创建遍历相乘所得乘积链表（尾插法）
			if (!head[i]->next)
			{
				head[i]->next = vule;
				end = vule;
				vule->next = NULL;
			}
			else
			{
				end->next = vule;
				end = vule;
				vule->next = NULL;
			}
			
		}
		pcur1 = pcur1->next;
		if (pcur1)//后移之后不为空
			i++;
	}
	//printf("i=%d\n", i);
	//PrintPoly(&head[0]);

	//将多项式乘积链表累加
	for (time; time <= i; time++)
	{
		//PrintPoly(&head[time]);
		SumPoly(&head[0], &head[time]);
		//PrintPoly(&head[0]);
	}
	printf("两多项式乘积为：\n");
	PrintPoly(&head[0]);

	//清空乘积链表释放内存
	for (time = 0; time <= i; time++)
	{
		Destroy(&head[time]);
	}
	return OK;
}

void Copy(Polylist* l1, Polylist* l2)//将l1多项式复制到l2
{
	Node num;
	Polylist cur = (*l1)->next;
	Polylist temp = NULL;
	Polylist pend = NULL;

	*l2= (Polylist)malloc(sizeof(Poly));
	(*l2)->elem = (*l1)->elem;
	(*l2)->next = NULL;

	for (cur; cur != NULL; cur = cur->next)
	{
		num.coef = cur->elem.coef;
		num.expo = cur->elem.expo;
		num.length = cur->elem.length;
		temp= (Polylist)malloc(sizeof(Poly));
		temp->elem = num;
		if (!((*l2)->next))//仅有头结点
		{
			(*l2)->next = temp;
			pend = temp;
			pend->next = NULL;
		}
		else
		{
			pend->next = temp;
			pend = temp;
			temp->next = NULL;
		}
	}
}

int main()
{
	int l=0;
	Polylist la = NULL;
	Polylist lb = NULL;
	Polylist la1 = NULL;
	Polylist lb1 = NULL;
	
	Creatlist(&la,l);
	Creatlist(&lb,l);

	printf("输入多项式为：\n");
	PrintPoly(&la);
	PrintPoly(&lb);
	
	SortPoly(&la);
	SortPoly(&lb);
	
	
	Copy(&la, &la1);
	Copy(&lb, &lb1);
	
	printf("排序后：\n");
	PrintPoly(&la);
	PrintPoly(&lb);
	
	AccumPoly(&la, &lb);//多项式相乘
	SumPoly(&la1, &lb1);//多项式相加

	printf("两多项式求和后：\n");
	PrintPoly(&la1);

	//释放内存
	if(!(Destroy(&la)) && !(Destroy(&lb)) && !(Destroy(&la1)) && !(Destroy(&lb1)))
		printf("多项式未清空ERROR");

	return OK;
}