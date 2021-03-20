#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>         //toascii函数
#include <string.h>

#define H_SIZE 30//哈希表的长度
#define N_SIZE 20//名单长度
#define ERROR 0
#define OK 1
#define R 15//小于哈希表长度的R
//int i,key;
typedef struct NameTable
{
    const char *name;            //姓名
    int ascii;             //对应的ascii码
    int length;             //查找长度
    NameTable* next;
}Name;
typedef Name* NameArray;
typedef struct HashTable
{
    int num;//哈希表表位链接点个数
   NameTable* first;
}Hash;
typedef Hash** Hashlist;//哈希表地址向量//0号单元未用
 //初始化名单表
void InitNamelist(NameArray &NameList)
{ 
    NameList = (NameArray)malloc(N_SIZE * sizeof(Name));
    int i, j;
    NameList[0].name = "xmz";
    NameList[1].name="gwq";
    NameList[2].name="lhy";
    NameList[3].name="zqx";
    NameList[4].name = "hwt";
    NameList[5].name = "hzy";
    NameList[6].name = "pll";
    NameList[7].name = "hd";
    for (i = 8; i < N_SIZE; i++)
        NameList[i].length = -1;//置空标识   
    for (i = 0; i < 8; i++)
    {
        NameList[i].ascii = 0;
        for (j = 0; (*(NameList[i].name + j)) != '\0'; j++)
            NameList[i].ascii += toascii(*(NameList[i].name + j));            //ascii码求和运用toascii函数
    }
}
//创建hash表//创建哈希函数
void CreatHush(Hashlist &htable,Name*NameList)                                   
{
    htable = (Hashlist)malloc((H_SIZE+1) * sizeof(Hash*));//指针向量分配内存//0号单元未用
    int i, key;
    Name* temp = NULL;
    Name* cur=NULL;
    for (i = 1; i <= H_SIZE; i++) //初始化哈希表
    {
      htable[i] = (Hash*)malloc(sizeof(Hash));
      htable[i]->num = 0;     
      htable[i]->first = NULL;
    }
    for (i = 0; i < N_SIZE; i++)
    {
        if (NameList[i].length != -1)
        {
            key = (NameList[i].ascii) % R;                        //除留余数法
            temp = (Name*)malloc(sizeof(Name));
            temp->name = NameList[i].name;
            temp->ascii = NameList[i].ascii;
            temp->next = NULL;
            if (htable[key]->num == 0)                      //未发生冲突则将相关信息填充至哈希表
            {
                temp->length = 1;
                htable[key]->first = temp;
                htable[key]->num++;
            }
            else                                                //发生冲突链接于最后一个记录
            {
                cur = htable[key]->first;
                while (cur->next != NULL)//寻找尾部元素记录
                {
                   cur = cur->next;
                }
                cur->next = temp;//尾接新纪录
                temp->length = cur->length + 1;
                htable[key]->num++;
            }

        }                  
    }

}
//查找函数
void Search(Hashlist htable)
{
    Name* cur=NULL;
    int j,i = 0;
    int key,Ascii=0;
    char name[10] = { "0" };
    fflush(stdin);//接受字符前清空缓冲区
    getchar();
    printf("请输入待查找姓名：");
    gets_s(name);
    for (j = 0; name[j]!= '\0'; j++)
        Ascii += toascii(name[j]);
    key = (Ascii) % R;
    printf("key是：%d\n", key);
    cur = htable[key]->first;
    while(cur!=NULL)
    {
        if (strcmp(cur->name,name)==0)
        {  printf("已从哈希表中查找到记录\n");
        printf("哈希表表位:%-4d姓名:%-4sascii:%-4d查找长度：%-4d\n", key, cur->name, cur->ascii,cur->length);
        return;
        }
        cur = cur->next;
    }
    if (cur == NULL)
        printf("无此记录！！!\n");
}
//打印名单
void Print_Namelist(Name* NameList)
{
    int i;
    for (i = 0; i < N_SIZE; i++)
    {
        if (NameList[i].length != -1)
            printf("序号:%-4d名称:%-4sascii:%-4d\n", i + 1, NameList[i].name, NameList[i].ascii);
        else
            break;
    }
}
//打印哈希表
void Print_Hash(Hashlist htable)
{
    Name* cur = NULL;
    int j=1;
    float ASL=0.0;//平均查找长度
    while (j != H_SIZE + 1)
    {
        if(htable[j]->first==NULL)
            printf("哈希表表位:%-4d__NULL\n",j);
        else
        for (cur = htable[j]->first; cur != NULL; cur = cur->next)
        {
            printf("哈希表表位:%-4d姓名:%-4sascii:%-4d查找长度：%-4d\n", j, cur->name, cur->ascii, cur->length);
            ASL += cur->length;
        }
        ++j;
    }
    ASL /= 8;
    printf("哈希表平均查找长度为：%4f\n", ASL);
}
//小菜单显示
void show()
{
    printf(" 1.打印名单 \n 2.打印哈希表\n 3.查找记录 \n 4.exit(0)\n");
}

int main()
{
   NameArray NameList=NULL;//名单
    Hashlist Table=NULL;//哈希表向量
    char c;
    int choice=1;
    InitNamelist(NameList);
    CreatHush(Table, NameList);
    while (choice) {
        show();     
        scanf("%d", &choice);
        
        switch (choice)
        {
        case 1:Print_Namelist(NameList); break;
        case 2:Print_Hash(Table); break;
        case 3:Search(Table);break;
        case 0:printf("正在退出...\n"); break;
        default: printf("EROOR INPUT!\a\n");break;
        }
        //system("cls");
    }
    return 0;
}
