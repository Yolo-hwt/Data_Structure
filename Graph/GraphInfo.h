#pragma once
//课程信息
struct classMassage {
	int index;//储存位置
	string classname;//课程名称
	int wight;//学分
};
//弧信息
template<class ElemType>
struct ArcInfo {
	ElemType From;  //起点
	ElemType To;  //终点
	int weight;   //权值
};
//弧节点
struct ArcNode {
	int adjvex;  //弧头即箭头指向顶点位置
	int weight; //权值
	struct ArcNode* nextarc;//指向下一条弧指针
};
//顶点节点
template<class ElemType>
struct VNode {
	ElemType date;
	int in;//入度
	ArcNode* firstarc;//指向链域中第一个结点，注意：为ArcNode类型的指针
};
