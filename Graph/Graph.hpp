#pragma once
#include<iostream>
using namespace std;
#define MAX 30
#define TERMNUMBER 6//ѧ����
#define CREDITMAX 10//ÿ��ѧ��ѧ������
#include"GraphInfo.h"
template<class ElemType>
class Graph {
public:
    int vexnum;  //������Ŀ
    int arcnum;  //����Ŀ
    VNode<ElemType>vertices[MAX];//�ڽӱ�
public:
    Graph() {
        this->arcnum = 0;
        this->vexnum = 0;
        //ͼ�ڽӱ�Ĭ�ϳ�ʼ��
        for (int i = 0; i < MAX; i++) {
            this->vertices[i].in = 0;
            this->vertices[i].firstarc = NULL;
        }
    }
    ~Graph() {}
    void CreateGrah(int vnum, int anum, VNode<ElemType> *data, ArcInfo<VNode<ElemType> > *arcList);//����ͼ
    void DispGraph();  //չ��ͼ
    int TopOrder();//��������
    void ClsGraph();//����ͼ

};


//����ͼ
template<class ElemType>
void Graph<ElemType>::CreateGrah(int vnum, int anum, VNode<ElemType> *data, ArcInfo<VNode<ElemType> > *arcList) 
{
    this->ClsGraph();//����ͼ
    this->arcnum = anum;//����Ŀ
    this->vexnum = vnum;//������Ŀ
    //�Զ�����ĿΪѭ��������data���鸳ֵͼ�ڽӱ��ͷ���data��
    for (int i = 0; i < vnum; i++)    
        if (data[i].date.wight != -1)
        { this->vertices[i].date = data[i].date;
        this->vertices[i].firstarc = NULL;//�����ʼ����Ϊ��
        this->vertices[i].in = 0;//������ȳ�ʼΪ0
        }
    
    for (int i = 0; i < anum; i++) 
    {
        if (arcList[i].weight != -1)
        {
            ArcNode* a = new ArcNode();//Ϊ�����ָ����仡����С�ڴ�
        a->adjvex = arcList[i].To.date.index - 1;//�����㼴Ϊ����Ϣ����arcList��ӦԪ�ص��յ�λ��-1
        /*�˴������Ϊ����classname��Ԫ����ΪVNode�ṹ���ڵĳ�Աdata,���Ǳ�����index���classname�ṹ���ڶ���ĳ�Ա��
        ��ʱ�����������ڵ�arcList���鶨���֪index��1��ʼ�����������������Ԫ�ر����-1��ϵ*/
        a->nextarc = NULL;//����Ϊ��
        a->weight = arcList[i].weight;//Ȩֵ��ֵ
        //����pָ��
        //ָ����Ϣ�����i��Ԫ�ص����Form��Ӧ���ڽӱ���λ��Ԫ�ص�����
        ArcNode* p = this->vertices[arcList[i].From.date.index - 1].firstarc;
        int sign = 0;//��ʶ�������Ƿ��ظ�
        while (p != NULL) 
        {
            if (p->adjvex == a->adjvex) {
                sign = 1;
            }
            p = p->nextarc;
        }
        if (sign == 1)
            cout << "���ظ�";
        else 
        {
            //ʹ��ͷ�巨���¼���ı���Ϣ������������
            a->nextarc = this->vertices[arcList[i].From.date.index - 1].firstarc;
            this->vertices[arcList[i].From.date.index - 1].firstarc = a;
            //ͬʱ��ͷ����ͷ��ָ����������+1
            this->vertices[arcList[i].To.date.index - 1].in++;
        }

        }
       
    }
}
//չ��ͼ
template<class ElemType>
void Graph<ElemType>::DispGraph() {
    if (this->vexnum == 0)
    {
        cout << "ͼΪ�գ�" << endl;
        return;
    }
    for (int i = 0; i < this->vexnum; i++) {
        ArcNode* p = this->vertices[i].firstarc;
        if (this->vertices[i].date.index != -1) {
            cout << this->vertices[i].date.index << "���ӵĵ��У�";
            while (p != NULL) {
                cout << p->adjvex + 1 << " ";//+1�൱�ڴ�1��ʼ����
                p = p->nextarc;
            }
            cout << endl;
        }
    }
}
//������������γ�
template<class ElemType>
int Graph<ElemType>::TopOrder() {
    int signTrem = 1; //��¼ѧ����
    int number = this->vexnum;  //��¼�γ�����
    int a[MAX];     //��¼�γ̵���� 
    int everySum = 0;  //��¼ÿ��ѧ�ڵ�ѧ����
    int i,mini,index;//index:�γ����������
    index = 1;
    //��ʼ����
    for (i = 0; i < number; i++)
        if(this->vertices[i].in!=-1)
        a[i] = this->vertices[i].in;
    
        
    cout << "--------------------------------------" << endl;
    cout << "�� 1 ѧ�ڣ�" << endl;
    
        //�����Ϊ0�Ľڵ�
        //��Ϊ�������forѭ��ÿ��ѭ�������һ��ѧ��
        for (int j = 0; j < MAX; j++) 
        {
            int min = MAX;
            int signx = 0;
            //Ŀ���ǽ��γ̸�����������ǰ���ѧ�����棬���Ծ���Ҫ������������ǰ���¾����ܶ��ѡ��γ�
            //���ǲ�ȡ�ڲ�����ѧ�����ѧ����ǰ���¾����ܶ��Ѱ����Сֵ�ķ�ʽ
            for (i = 0; i < number; i++) //forѭ����Ѱ�Ҵ�ʱ��Сֵ
            {
                if (a[i] == 0) {
                    if (this->vertices[i].date.wight < min) {
                        min = this->vertices[i].date.wight;
                        mini = i;
                            signx = 1;
                    }
                }
            }
            if (signx == 1) {
                everySum += this->vertices[mini].date.wight;//ͳ����ѡ�γ�ѧ��
                if (everySum > CREDITMAX) {                  
                    cout << "-----------------------------------" << endl;
                    cout << "�� " << signTrem + 1 << " ѧ�ڣ�" << endl;
                    signTrem++;
                    everySum = 0;
                    continue;//������ǰѭ���������һ��ѭ��
                }
                else {               
                    cout << this->vertices[mini].date.classname << "��ѧ��" << this->vertices[mini].date.wight << endl;
                    a[mini] =-index;//��ʶΪ-index��ʾ�����,index��ʾ��Ϊ�ڼ������
                    index++;
                }
            }
            else
                 break; 
            for (int i = 0; i < number; i++) 
            {
            ArcNode* p = this->vertices[i].firstarc;
                if (a[i] == -(index-1)) 
                {
                    while (p != NULL) 
                    {
                        a[p->adjvex]--;
                        p = p->nextarc;
                    }
                }
            }          
        }
    return 0;
 }
//����ͼ
template<class ElemType>
void Graph<ElemType>::ClsGraph()
{
    this->arcnum = 0;
    this->vexnum = 0;
    for (int i = 0; i < MAX; i++) {
        this->vertices[i].in = -1;
        this->vertices[i].firstarc = NULL;
    }
}