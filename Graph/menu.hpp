#include<iostream>
#include<string.h>
#include"Graph.hpp"
using namespace std;
static int KIND;//课程种类
static int RELA;//关系数，即边的条数
//显示主菜单
void showMenu() {
	cout << "1.添加测试数据" << endl;
	cout << "2.添加课表范例" << endl;
	cout << "3.添加课程" << endl;
	cout << "4.删除课程" << endl;
	cout << "5.修改课程" << endl;
	cout << "6.输出课表" << endl;
	cout << "7.图信息" << endl;
	cout << "8.当前课程显示" << endl;
	cout << "9.课程关系显示" << endl;
	cout << "10.清空当前课表" << endl;
	cout << "0.退出" << endl;
}
//清空当前课表
void Clsclasstable(VNode<classMassage>* data,ArcInfo<VNode<classMassage>>* arcList)
{
	for (int i = 0; i < KIND; i++)
	{data[i].date.index = -1; data[i].date.classname = "wu"; data[i].date.wight = -1;}
	for (int j = 0; j < RELA; j++)
	{arcList[j].From = data[0]; arcList[j].To = data[0]; arcList[j].weight = -1;}
}
//添加测试数据
void TestClas(VNode<classMassage>* data, ArcInfo<VNode<classMassage>>* arcList, int& vnum,int &anum)
{
	int a=1;
	int form, to;
	
	char c;
	char name[20] = { "0" };
	vnum = 0; anum = 0;
	Clsclasstable(data, arcList);//先清空课表
	while (a)
	{form = -1; to = -1;
	cout << "1.输入测试课程" << endl;
	cout << "2.输入约束关系" << endl;
	cout << "0.输入完成" << endl;
	cin >> a;
	switch (a)
	{
	case 1: {int flag = 0;
		VNode<classMassage> temp;
		cout << "输入课程名称" << endl;
		cin >> temp.date.classname;
		for (int i = 0; i < vnum; i++)
			if (data[i].date.classname == temp.date.classname)
			{
				cout << "课程已存在！" << endl; flag = 1;
				return;
			}
		if (flag)//课程已存在退回菜单界面
			break;
		cout << "输入课程学分" << endl;
		cin >> temp.date.wight;
		temp.date.index = vnum + 1;//从1开始计数
		data[vnum] = temp;
		vnum++;
		break;
	}
	case 2:
	{
		cout << "先决课程名称：";
		c = getchar();
		gets_s(name);
		for (int i = 0; i < vnum; i++)
			if (data[i].date.classname == name)
				form = i;
		if (form == -1)
		{
			cout << "课程不存在！"<<endl;
			break;
		}
		cout << "输入约束课程名称：";
		c = getchar();
		gets_s(name);
		for (int i = 0; i < vnum; i++)
			if (data[i].date.classname == name)
				to = i;
		if (to == -1)
		{
			cout << "课程不存在！" << endl;
			break;
		}
		arcList[anum].From = data[form];
		arcList[anum].To = data[to];
		arcList->weight = data[form].date.wight;
		anum++;
		break;
	}
	case 0:
		break;
	}
	}



}
//显示课程信息
void Printclass(VNode<classMassage>* data)
{
	if (data->date.wight ==-1)
	{
		cout << "课程为空！" << endl;
		return;
	}
	for (int i = 0; i < KIND; i++)
	{
		if (data[i].date.index == -1)
			break;
		cout << "课程名称：" << data[i].date.index << "_" << data[i].date.classname << "_" << "学分：" << data[i].date.wight << endl;
	}
}
//课程约束关系
void PrintRela(ArcInfo<VNode<classMassage>>* arcList)
{
	if (arcList->weight == -1)
	{
		cout << "约束关系为空！" << endl;
		return;
	}
	cout << "\"先修\"------------>" << "\"后修\"_" <<"wight"<< endl;
	for (int i = 0; i < RELA; i++)
	{
		if (arcList[i].From.date.index==-1)
			break;
		cout << arcList[i].From.date.classname << "------------>" << arcList[i].To.date.classname <<"_"<<arcList[i].weight<< endl;
	}
}
//范例课表信息初始化
void InitClassMassage(VNode<classMassage>* data, ArcInfo<VNode<classMassage>>* arcList,int &vnum,int &anum)
{//赋值各元素
	//VNode<classMassage> data[14];//14门课程
	//ArcInfo<VNode<classMassage>>arcList[19];//19条相应弧信息
	vnum = 14; anum = 19;
	data[0].date.index = 1; data[0].date.classname = "程序设计基础"; data[0].date.wight = 2;
	data[1].date.index = 2; data[1].date.classname = "离散数学"; data[1].date.wight = 3;
	data[2].date.index = 3; data[2].date.classname = "数据结构"; data[2].date.wight = 4;
	data[3].date.index = 4; data[3].date.classname = "汇编语言"; data[3].date.wight = 3;
	data[4].date.index = 5; data[4].date.classname = "程序设计与分析"; data[4].date.wight = 2;
	data[5].date.index = 6; data[5].date.classname = "计算机原理"; data[5].date.wight = 3;
	data[6].date.index = 7; data[6].date.classname = "编译原理"; data[6].date.wight = 4;
	data[7].date.index = 8; data[7].date.classname = "操作系统"; data[7].date.wight = 4;
	data[8].date.index = 9; data[8].date.classname = "高等数学"; data[8].date.wight = 7;
	data[9].date.index = 10; data[9].date.classname = "线性代数"; data[9].date.wight = 5;
	data[10].date.index = 11; data[10].date.classname = "普通物理"; data[10].date.wight = 2;
	data[11].date.index = 12; data[11].date.classname = "数值分析"; data[11].date.wight = 3;
	data[12].date.index = 13; data[12].date.classname = "软件工程"; data[12].date.wight = 3;
	data[13].date.index = 14; data[13].date.classname = "数据库原理"; data[13].date.wight = 3;
	//对应实验给出的有向图信息结合上述data元素给弧信息数组赋值,,,此处weight均为有向弧弧尾元素权值
	arcList[0].From = data[0]; arcList[0].To = data[1]; arcList[0].weight = 2;
	arcList[1].From = data[0]; arcList[1].To = data[2]; arcList[1].weight = 2;
	arcList[2].From = data[0]; arcList[2].To = data[3]; arcList[2].weight = 2;
	arcList[3].From = data[0]; arcList[3].To = data[11]; arcList[3].weight = 2;
	arcList[4].From = data[1]; arcList[4].To = data[2]; arcList[4].weight = 3;
	arcList[5].From = data[2]; arcList[5].To = data[4]; arcList[5].weight = 4;
	arcList[6].From = data[2]; arcList[6].To = data[6]; arcList[6].weight = 4;
	arcList[7].From = data[2]; arcList[7].To = data[7]; arcList[7].weight = 4;
	arcList[8].From = data[3]; arcList[8].To = data[4]; arcList[8].weight = 3;
	arcList[9].From = data[4]; arcList[9].To = data[12]; arcList[9].weight = 2;
	arcList[10].From = data[4]; arcList[10].To = data[6]; arcList[10].weight = 2;
	arcList[11].From = data[5]; arcList[11].To = data[7]; arcList[11].weight = 3;
	arcList[12].From = data[6]; arcList[12].To = data[13]; arcList[12].weight = 4;
	arcList[13].From = data[7]; arcList[13].To = data[13]; arcList[13].weight = 4;
	arcList[14].From = data[8]; arcList[14].To = data[9]; arcList[14].weight = 7;
	arcList[15].From = data[8]; arcList[15].To = data[10]; arcList[15].weight = 7;
	arcList[16].From = data[8]; arcList[16].To = data[11]; arcList[16].weight = 7;
	arcList[17].From = data[9]; arcList[17].To = data[11]; arcList[17].weight = 5;
	arcList[18].From = data[10]; arcList[18].To = data[5]; arcList[18].weight = 2;
//余下元素默认初始化
	for (int i = 14; i < KIND; i++){data[i].date.index = -1; data[i].date.classname = "wu"; data[i].date.wight = -1;}
	for (int j = 19; j < RELA; j++)
	{arcList[j].From = data[14]; arcList[j].To = data[14]; arcList[j].weight = -1;}

	cout << "默认课表信息已添加！" << endl;
}
//添加课程
void addClass(VNode<classMassage>* data, ArcInfo<VNode<classMassage>>* arcList,int &vnum,int &anum) {
	VNode<classMassage> target;
	int a,index=0;
	char s[20] = { "0" };
	target.firstarc = NULL;
	target.in = 0;
	cout << "输入课程编号" << endl;
	cin >> target.date.index;
	cout << "输入课程名称" << endl;
	cin >> target.date.classname;
	for(int i=0;i<vnum;i++)
		if (data[i].date.classname == target.date.classname)
		{
			cout << "课程已存在！" << endl;
			return;
		}
	cout << "输入课程学分" << endl;
	cin >> target.date.wight;
	data[vnum].date.classname = target.date.classname;
	data[vnum].date.index = vnum + 1;
	data[vnum].date.wight = target.date.wight;
	vnum++;
	cout << "课程是否有先修要求？（1.有  2.没有）" << endl;
	cin >> a;
	while (a!=2)
	{
		switch (a)
	{
		cout << "1.添加先修要求课程" << endl;
		cout << "2.添加完毕" << endl;
		cin >> a;
	case 1: {
		cout << "输入先修课程名称：";
		 gets_s(s);
		 for (int i = 0; i < vnum; i++)
		 {
			 if (data[i].date.classname == s)
			 {index = i;
			 break;
			 }	 
		 }
		 if (!index)
			 cout << "课程不存在！"<<endl;
		 else
		 {arcList[anum].From = data[index]; 
		 arcList[anum].To = data[vnum-1]; 
		 arcList[anum].weight = data[index].date.wight;
		 anum++;
		 }
		 index = 0;
		 break;
	}
	case 2:
	{break;
	cout << endl;
		}	
	  }
	}
	cout << "课程是否存在已有课程的约束？（1.有  2.没有）" << endl;
	cin >> a;
	while (a != 2)
	{
		switch (a)
		{
			cout << "1.添加约束课程" << endl;
			cout << "2.添加完毕" << endl;
			cin >> a;
		case 1: {
			cout << "输入约束课程名称：";
			gets_s(s);
			for (int i = 0; i < vnum; i++)
			{
				if (data[i].date.classname == s)
				{
					index = i;
					break;
				}
			}
			if (!index)
				cout << "课程不存在！" << endl;
			else
			{arcList[anum].From = data[vnum-1];
			arcList[anum].To = data[index];
			arcList[anum].weight = data[vnum].date.wight;
			anum++;
			}
			index = 0;
			break;
		}
		case 2:
		{break;
		cout << endl;
		}
		}
	}
	
}
//删除课程
void deleteClass(VNode<classMassage>* data, ArcInfo<VNode<classMassage>>* arcList, int& vnum, int& anum) {
	char s[20] = { "0" };
	char c;
	int index = 0;
	cout << "输入删除课程名称：";
	c = getchar();
	gets_s(s);
	for (int i = 0; i < vnum; i++)
	{
		if (data[i].date.classname == s)
		{
			index = i;
			break;
		}
	}
	if (!index)
	{
		cout << "课程不存在！" << endl;
		return;
	}
	else
	{//-1表示删除
		data[index].date.wight = -1;
		for (int j = 0; j < anum; j++)
		{
			if (arcList[j].From.date.classname == s || arcList[j].To.date.classname == s)
				arcList[j].weight = -1;
		}
	}
	cout << "课程已删除" << endl;
}
//更改课程信息
void changeClass(VNode<classMassage>* data, ArcInfo<VNode<classMassage>>* arcList, int& vnum, int& anum) {
	char s[20] = { "0" };
	char s1[20] = { "0" };
	int index = 0;
	int a; char c;
	cout << "输入更改课程名称：";
	c = getchar();
	gets_s(s);
	for (int i = 0; i < vnum; i++)
	{
		if (data[i].date.classname == s)
		{
			index = i;
			break;
		}
	}
	if (!index)
	{
		cout << "课程不存在！" << endl;
		return;
	}
	else
	{
		cout << "选择更改项" << endl;
		cout << "1.课程名称" << endl;
		cout << "2.课程学分" << endl;
		cin >> a;
		if (a == 1)
		{
			cout << "输入更改后名称：";
			c = getchar();
			gets_s(s);
			data[index].date.classname = s;
			for (int j = 0; j < anum; j++)
			{
				if (arcList[j].From.date.index==index + 1)
					arcList[j].From.date.classname = s;
				if(arcList[j].To.date.index == index + 1)
					arcList[j].To.date.classname = s;
			}
		}
		else
		{
			cout << "输入更改后学分：";
			cin >> a;
			data[index].date.wight = a;
			for (int j = 0; j < anum; j++)
			{
				if (arcList[j].From.date.index == index + 1)
					arcList[j].weight = a;
			}
		}
	}
	cout << "更改完成" << endl;
}


