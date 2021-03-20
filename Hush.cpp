#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>         //toascii����
#include <string.h>

#define H_SIZE 30//��ϣ��ĳ���
#define N_SIZE 20//��������
#define ERROR 0
#define OK 1
#define R 15//С�ڹ�ϣ���ȵ�R
//int i,key;
typedef struct NameTable
{
    const char *name;            //����
    int ascii;             //��Ӧ��ascii��
    int length;             //���ҳ���
    NameTable* next;
}Name;
typedef Name* NameArray;
typedef struct HashTable
{
    int num;//��ϣ���λ���ӵ����
   NameTable* first;
}Hash;
typedef Hash** Hashlist;//��ϣ���ַ����//0�ŵ�Ԫδ��
 //��ʼ��������
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
        NameList[i].length = -1;//�ÿձ�ʶ   
    for (i = 0; i < 8; i++)
    {
        NameList[i].ascii = 0;
        for (j = 0; (*(NameList[i].name + j)) != '\0'; j++)
            NameList[i].ascii += toascii(*(NameList[i].name + j));            //ascii���������toascii����
    }
}
//����hash��//������ϣ����
void CreatHush(Hashlist &htable,Name*NameList)                                   
{
    htable = (Hashlist)malloc((H_SIZE+1) * sizeof(Hash*));//ָ�����������ڴ�//0�ŵ�Ԫδ��
    int i, key;
    Name* temp = NULL;
    Name* cur=NULL;
    for (i = 1; i <= H_SIZE; i++) //��ʼ����ϣ��
    {
      htable[i] = (Hash*)malloc(sizeof(Hash));
      htable[i]->num = 0;     
      htable[i]->first = NULL;
    }
    for (i = 0; i < N_SIZE; i++)
    {
        if (NameList[i].length != -1)
        {
            key = (NameList[i].ascii) % R;                        //����������
            temp = (Name*)malloc(sizeof(Name));
            temp->name = NameList[i].name;
            temp->ascii = NameList[i].ascii;
            temp->next = NULL;
            if (htable[key]->num == 0)                      //δ������ͻ�������Ϣ�������ϣ��
            {
                temp->length = 1;
                htable[key]->first = temp;
                htable[key]->num++;
            }
            else                                                //������ͻ���������һ����¼
            {
                cur = htable[key]->first;
                while (cur->next != NULL)//Ѱ��β��Ԫ�ؼ�¼
                {
                   cur = cur->next;
                }
                cur->next = temp;//β���¼�¼
                temp->length = cur->length + 1;
                htable[key]->num++;
            }

        }                  
    }

}
//���Һ���
void Search(Hashlist htable)
{
    Name* cur=NULL;
    int j,i = 0;
    int key,Ascii=0;
    char name[10] = { "0" };
    fflush(stdin);//�����ַ�ǰ��ջ�����
    getchar();
    printf("�����������������");
    gets_s(name);
    for (j = 0; name[j]!= '\0'; j++)
        Ascii += toascii(name[j]);
    key = (Ascii) % R;
    printf("key�ǣ�%d\n", key);
    cur = htable[key]->first;
    while(cur!=NULL)
    {
        if (strcmp(cur->name,name)==0)
        {  printf("�Ѵӹ�ϣ���в��ҵ���¼\n");
        printf("��ϣ���λ:%-4d����:%-4sascii:%-4d���ҳ��ȣ�%-4d\n", key, cur->name, cur->ascii,cur->length);
        return;
        }
        cur = cur->next;
    }
    if (cur == NULL)
        printf("�޴˼�¼����!\n");
}
//��ӡ����
void Print_Namelist(Name* NameList)
{
    int i;
    for (i = 0; i < N_SIZE; i++)
    {
        if (NameList[i].length != -1)
            printf("���:%-4d����:%-4sascii:%-4d\n", i + 1, NameList[i].name, NameList[i].ascii);
        else
            break;
    }
}
//��ӡ��ϣ��
void Print_Hash(Hashlist htable)
{
    Name* cur = NULL;
    int j=1;
    float ASL=0.0;//ƽ�����ҳ���
    while (j != H_SIZE + 1)
    {
        if(htable[j]->first==NULL)
            printf("��ϣ���λ:%-4d__NULL\n",j);
        else
        for (cur = htable[j]->first; cur != NULL; cur = cur->next)
        {
            printf("��ϣ���λ:%-4d����:%-4sascii:%-4d���ҳ��ȣ�%-4d\n", j, cur->name, cur->ascii, cur->length);
            ASL += cur->length;
        }
        ++j;
    }
    ASL /= 8;
    printf("��ϣ��ƽ�����ҳ���Ϊ��%4f\n", ASL);
}
//С�˵���ʾ
void show()
{
    printf(" 1.��ӡ���� \n 2.��ӡ��ϣ��\n 3.���Ҽ�¼ \n 4.exit(0)\n");
}

int main()
{
   NameArray NameList=NULL;//����
    Hashlist Table=NULL;//��ϣ������
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
        case 0:printf("�����˳�...\n"); break;
        default: printf("EROOR INPUT!\a\n");break;
        }
        //system("cls");
    }
    return 0;
}
