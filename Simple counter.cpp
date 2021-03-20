//简单计算器
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define STACK_INT_SIZE 100//栈储存空间初始分配量
#define STACKINCREMENT 10//栈储存空间分配增量
#define status int

//栈类型定义
typedef struct OperaStack//符号栈OPTR
{
	char* base;
	char* top;
	int size;//当前已分配储存空间
}Ostack;
typedef struct NumStack//操作数栈栈OPND
{
	int* base;
	int* top;
	int size;//当前已分配储存空间
}Nstack;

//栈的初始化
void InitStack(Ostack& oper)
{
	oper.base = (char*)malloc(STACK_INT_SIZE * sizeof(OperaStack));
	if (!oper.base)
		exit(ERROR);
	oper.top = oper.base;
	oper.size = STACK_INT_SIZE;
}
void InitStack(Nstack& num)
{
	num.base = (int*)malloc(STACK_INT_SIZE * sizeof(NumStack));
	if (!num.base)
		exit(ERROR);
	num.top = num.base;
	num.size = STACK_INT_SIZE;
}

//栈顶插入元素
status Push(Ostack& oper, char s)
{
	if (oper.top - oper.base >= oper.size)//栈满情况，追加内存
	{
		printf("栈满情况出现");
		//realloc函数动态分配
		oper.base = (char*)realloc(oper.base, (oper.size + STACKINCREMENT) * sizeof(OperaStack));
		if (oper.base == NULL)
			exit(ERROR);
		oper.top = oper.base + oper.size;
		oper.size += STACKINCREMENT;
	}

	*oper.top++ = s;//先执行,后++
	return OK;
}
status Push(Nstack& num, int s)
{
	if (num.top - num.base >= num.size)//栈满，追加内存
	{
		num.base = (int*)realloc(num.base, (num.size + STACKINCREMENT) * sizeof(NumStack));
		if (!num.base)
			exit(ERROR);
		num.top = num.base + num.size;
		num.size += STACKINCREMENT;
	}

	*num.top++ = s;
	return OK;
}

//栈顶删除元素
char Pop(Ostack& oper)
{
	char val;
	if (oper.base == oper.top)//空栈
		return ERROR;
	val = *--oper.top;
	return val;
}
status Pop(Nstack& num, int &e)
{
	if (num.base == num.top)//空栈
		return ERROR;
	e = *--num.top;
	return e;
}

//获取栈顶元素
char GetTop(Ostack& oper)
{
	if (oper.base == oper.top)//栈为空
		return ERROR;
	return *(oper.top - 1);
}
status GetTop(Nstack& num)
{
	if (num.base == num.top)//栈为空
		return ERROR;
	return *(num.top - 1);
}

//检测是否为运算符(返回'1'则是)
status Checkoper(char c)
{
	int sta = 1;
	if (c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')' && c != '#')
		sta = 0;
	return sta;
}

//比较运算符优先级(返回'>','<','=',或语法错误'!'
char Precede(char top, char c)
{
	char result = '>';
	if (top == '+' || top == '-')//+-
	{
		if (c == '*' || c == '/' || c == '(')
			result = '<';
	}
	if (top == '*' || top == '/')//*'/'
	{
		if (c == '(')
			result = '<';
	}
	if (top == '(')//(
	{
		result = '<';
		if (c == ')')
			result = '=';
		if (c == '#')
			result = '!';
	}
	if (top == ')')//)
	{
		if (c == '(')
			result = '!';
	}
	if (top == '#')//#
	{
		result = '<';
		if (c == ')')
			result = '!';
		if (c == '#')
			result = '=';
	}
	return result;
}

//二元运算
status Operation(int a, char op, int b)
{
	int result = 0;
	
	switch (op)
	{
	case '+': {result = a + b; break; }
	case '-': {result = a - b; break; }
	case '*': {result = a * b; break; }
	case '/': {result = a / b; break; }		
	default: {printf("运算符%c未定义！", op); return ERROR; }
	}
	return result;
}

//销毁栈
status Destroy(Ostack& oper)
{
	int sta = 0;
	char* temp = oper.top;
	while(oper.base != oper.top)
	{
		oper.top--;
		temp = oper.top;
		free(temp);
	}
		sta = 1;
		free(oper.top);
		oper.top = oper.base = NULL;
		temp = NULL;
	return sta;
}
status Del(Nstack& num)
{
	int sta = 0;
	free(num.base);
	num.base = NULL;
	num.top = NULL;
	num.size = 0;
	if (!num.base)
		sta = 1;
	return sta;
}
status Del(Ostack& num)
{
	int sta = 0;
	free(num.base);
	num.base = NULL;
	num.top = NULL;
	num.size = 0;
	if (!num.base)
		sta = 1;
	return sta;
}
status Destroy(Nstack& num)
{
	int sta = 0;
	int* temp = num.top;
	while (num.base != num.top)
	{
		num.top--;
		temp = num.top;
		free(temp);
	}
		sta = 1;
		free(num.top);
		num.base = num.top = NULL;
		temp = NULL;
	return sta;
}

int main()
{
	char str[20] = { "\0" };//字符数组，临时储存表达式
	int save[20] = { 0 };//储存临时变量

	char c, e,theta;
	e=theta = '1';

	int a, b;//二元运算
	a = b = 1;

	int m, index,h,j,i,temp;
	index = -1;//数字位数计数器
	m=h=temp=i= 0;
	
	Ostack OPTR;
	Nstack OPND;
	InitStack(OPTR); Push(OPTR, '#');//符号栈栈底以'#'开始，接收到另一个'#'结束
	InitStack(OPND);

	printf("请输入表达式\n");
	gets_s(str);
	//将字符串中'='转化为'#'
	for (i; i <= 20; i++)
	{
		if (str[i] == '=')
		{
			str[i] = '#';
			break;
		}
	}

	i = 0;
	c = str[i];
	while (c != '#' || GetTop(OPTR) != '#')//当c='#'且符号栈顶元素也为'#'时退出循环
	{
		if(!Checkoper(str[i]))
		{
			while (!Checkoper(str[i]))//判断是否为操作数
		    {
				//检测是否是运算符,不是则为操作数，进入
				++index;//指示当前输入数字位数
				temp = (int)(str[i] - '0');//ascll码值转换——字符转化为数字
				save[m] = temp;
				m++;
				i++;
		    }//while 
			temp = 0;
			while (index + 1)//当有数据时,index指示数据最高加权位
			{
				m = 0;
				//重整生成变量数据
				for (j = index; j > 0; j--)
				{
					h = j;
					while (h)
					{
						save[m] *= 10;
						h--;
					}
					m++;
				}
				
				for (m = 0; m <= index; m++)//求和
					temp =temp+save[m];
			
				memset(save, 0, sizeof(save));//清空数组
				m = 0;
				index = -1;
			}
			Push(OPND, temp);//整合后操作数进栈
			temp = 0;
		}//if
		else//为运算符时
		{
			c = str[i];
			switch (Precede(GetTop(OPTR), c))
			{
			case '<':
				Push(OPTR, c);
				
				c = str[++i];
				break;
			case '=':
				Pop(OPTR);
				c = str[++i];
				break;
			case '>':
				theta=Pop(OPTR);
				Pop(OPND, b); Pop(OPND, a);
				Push(OPND, Operation(a, theta, b));
				break;
			case '!':
				printf("输入错误！");
				return ERROR;
				break;
			}//switch

		}//else
		
	}//while
	
	printf("表达式运算结果为%d\n", GetTop(OPND));
	//if (Del(OPND)&& Del(OPTR))
		//printf("栈已清空");

	return OK;
}