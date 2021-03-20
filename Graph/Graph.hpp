#pragma once
#include<iostream>
using namespace std;
#define MAX 30
#define TERMNUMBER 6//学期数
#define CREDITMAX 10//每个学期学分上限
#include"GraphInfo.h"
template<class ElemType>
class Graph {
public:
    int vexnum;  //顶点数目
    int arcnum;  //弧数目
    VNode<ElemType>vertices[MAX];//邻接表
public:
    Graph() {
        this->arcnum = 0;
        this->vexnum = 0;
        //图邻接表默认初始化
        for (int i = 0; i < MAX; i++) {
            this->vertices[i].in = 0;
            this->vertices[i].firstarc = NULL;
        }
    }
    ~Graph() {}
    void CreateGrah(int vnum, int anum, VNode<ElemType> *data, ArcInfo<VNode<ElemType> > *arcList);//创建图
    void DispGraph();  //展现图
    int TopOrder();//拓扑排序
    void ClsGraph();//重置图

};


//创建图
template<class ElemType>
void Graph<ElemType>::CreateGrah(int vnum, int anum, VNode<ElemType> *data, ArcInfo<VNode<ElemType> > *arcList) 
{
    this->ClsGraph();//重置图
    this->arcnum = anum;//弧数目
    this->vexnum = vnum;//顶点数目
    //以顶点数目为循环条件将data数组赋值图邻接表的头结点data域
    for (int i = 0; i < vnum; i++)    
        if (data[i].date.wight != -1)
        { this->vertices[i].date = data[i].date;
        this->vertices[i].firstarc = NULL;//链域初始设置为空
        this->vertices[i].in = 0;//顶点入度初始为0
        }
    
    for (int i = 0; i < anum; i++) 
    {
        if (arcList[i].weight != -1)
        {
            ArcNode* a = new ArcNode();//为弧结点指针分配弧结点大小内存
        a->adjvex = arcList[i].To.date.index - 1;//弧顶点即为弧信息数组arcList相应元素的终点位置-1
        /*此处可理解为当以classname类元素作为VNode结构体内的成员data,于是便有了index这个classname结构体内定义的成员，
        此时反观主函数内的arcList数组定义可知index从1开始计数，于是相较数组元素便存在-1关系*/
        a->nextarc = NULL;//链域为空
        a->weight = arcList[i].weight;//权值赋值
        //定义p指针
        //指向弧信息数组第i个元素的起点Form对应在邻接表中位置元素的链域
        ArcNode* p = this->vertices[arcList[i].From.date.index - 1].firstarc;
        int sign = 0;//标识，辨别边是否重复
        while (p != NULL) 
        {
            if (p->adjvex == a->adjvex) {
                sign = 1;
            }
            p = p->nextarc;
        }
        if (sign == 1)
            cout << "边重复";
        else 
        {
            //使用头插法将新加入的边信息链接至链表中
            a->nextarc = this->vertices[arcList[i].From.date.index - 1].firstarc;
            this->vertices[arcList[i].From.date.index - 1].firstarc = a;
            //同时弧头即箭头所指方向结点的入度+1
            this->vertices[arcList[i].To.date.index - 1].in++;
        }

        }
       
    }
}
//展现图
template<class ElemType>
void Graph<ElemType>::DispGraph() {
    if (this->vexnum == 0)
    {
        cout << "图为空！" << endl;
        return;
    }
    for (int i = 0; i < this->vexnum; i++) {
        ArcNode* p = this->vertices[i].firstarc;
        if (this->vertices[i].date.index != -1) {
            cout << this->vertices[i].date.index << "连接的点有：";
            while (p != NULL) {
                cout << p->adjvex + 1 << " ";//+1相当于从1开始计数
                p = p->nextarc;
            }
            cout << endl;
        }
    }
}
//拓扑排序输出课程
template<class ElemType>
int Graph<ElemType>::TopOrder() {
    int signTrem = 1; //记录学期数
    int number = this->vexnum;  //记录课程门数
    int a[MAX];     //记录课程的入度 
    int everySum = 0;  //记录每个学期的学分数
    int i,mini,index;//index:课程输出计数器
    index = 1;
    //初始化度
    for (i = 0; i < number; i++)
        if(this->vertices[i].in!=-1)
        a[i] = this->vertices[i].in;
    
        
    cout << "--------------------------------------" << endl;
    cout << "第 1 学期：" << endl;
    
        //输出度为0的节点
        //作为外层最大的for循环每次循环体输出一个学期
        for (int j = 0; j < MAX; j++) 
        {
            int min = MAX;
            int signx = 0;
            //目的是将课程负担尽量放在前面的学期里面，所以就需要在满足条件的前提下尽可能多的选择课程
            //于是采取在不超过学期最大学分数前提下尽可能多的寻找最小值的方式
            for (i = 0; i < number; i++) //for循环，寻找此时最小值
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
                everySum += this->vertices[mini].date.wight;//统计所选课程学分
                if (everySum > CREDITMAX) {                  
                    cout << "-----------------------------------" << endl;
                    cout << "第 " << signTrem + 1 << " 学期：" << endl;
                    signTrem++;
                    everySum = 0;
                    continue;//跳过当前循环体进入下一次循环
                }
                else {               
                    cout << this->vertices[mini].date.classname << "：学分" << this->vertices[mini].date.wight << endl;
                    a[mini] =-index;//标识为-index表示已输出,index表示其为第几次输出
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
//重置图
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