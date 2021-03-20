#include<iostream>
#include<string.h>
#include"Graph.hpp"
using namespace std;
static int KIND;//�γ�����
static int RELA;//��ϵ�������ߵ�����
//��ʾ���˵�
void showMenu() {
	cout << "1.��Ӳ�������" << endl;
	cout << "2.��ӿα���" << endl;
	cout << "3.��ӿγ�" << endl;
	cout << "4.ɾ���γ�" << endl;
	cout << "5.�޸Ŀγ�" << endl;
	cout << "6.����α�" << endl;
	cout << "7.ͼ��Ϣ" << endl;
	cout << "8.��ǰ�γ���ʾ" << endl;
	cout << "9.�γ̹�ϵ��ʾ" << endl;
	cout << "10.��յ�ǰ�α�" << endl;
	cout << "0.�˳�" << endl;
}
//��յ�ǰ�α�
void Clsclasstable(VNode<classMassage>* data,ArcInfo<VNode<classMassage>>* arcList)
{
	for (int i = 0; i < KIND; i++)
	{data[i].date.index = -1; data[i].date.classname = "wu"; data[i].date.wight = -1;}
	for (int j = 0; j < RELA; j++)
	{arcList[j].From = data[0]; arcList[j].To = data[0]; arcList[j].weight = -1;}
}
//��Ӳ�������
void TestClas(VNode<classMassage>* data, ArcInfo<VNode<classMassage>>* arcList, int& vnum,int &anum)
{
	int a=1;
	int form, to;
	
	char c;
	char name[20] = { "0" };
	vnum = 0; anum = 0;
	Clsclasstable(data, arcList);//����տα�
	while (a)
	{form = -1; to = -1;
	cout << "1.������Կγ�" << endl;
	cout << "2.����Լ����ϵ" << endl;
	cout << "0.�������" << endl;
	cin >> a;
	switch (a)
	{
	case 1: {int flag = 0;
		VNode<classMassage> temp;
		cout << "����γ�����" << endl;
		cin >> temp.date.classname;
		for (int i = 0; i < vnum; i++)
			if (data[i].date.classname == temp.date.classname)
			{
				cout << "�γ��Ѵ��ڣ�" << endl; flag = 1;
				return;
			}
		if (flag)//�γ��Ѵ����˻ز˵�����
			break;
		cout << "����γ�ѧ��" << endl;
		cin >> temp.date.wight;
		temp.date.index = vnum + 1;//��1��ʼ����
		data[vnum] = temp;
		vnum++;
		break;
	}
	case 2:
	{
		cout << "�Ⱦ��γ����ƣ�";
		c = getchar();
		gets_s(name);
		for (int i = 0; i < vnum; i++)
			if (data[i].date.classname == name)
				form = i;
		if (form == -1)
		{
			cout << "�γ̲����ڣ�"<<endl;
			break;
		}
		cout << "����Լ���γ����ƣ�";
		c = getchar();
		gets_s(name);
		for (int i = 0; i < vnum; i++)
			if (data[i].date.classname == name)
				to = i;
		if (to == -1)
		{
			cout << "�γ̲����ڣ�" << endl;
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
//��ʾ�γ���Ϣ
void Printclass(VNode<classMassage>* data)
{
	if (data->date.wight ==-1)
	{
		cout << "�γ�Ϊ�գ�" << endl;
		return;
	}
	for (int i = 0; i < KIND; i++)
	{
		if (data[i].date.index == -1)
			break;
		cout << "�γ����ƣ�" << data[i].date.index << "_" << data[i].date.classname << "_" << "ѧ�֣�" << data[i].date.wight << endl;
	}
}
//�γ�Լ����ϵ
void PrintRela(ArcInfo<VNode<classMassage>>* arcList)
{
	if (arcList->weight == -1)
	{
		cout << "Լ����ϵΪ�գ�" << endl;
		return;
	}
	cout << "\"����\"------------>" << "\"����\"_" <<"wight"<< endl;
	for (int i = 0; i < RELA; i++)
	{
		if (arcList[i].From.date.index==-1)
			break;
		cout << arcList[i].From.date.classname << "------------>" << arcList[i].To.date.classname <<"_"<<arcList[i].weight<< endl;
	}
}
//�����α���Ϣ��ʼ��
void InitClassMassage(VNode<classMassage>* data, ArcInfo<VNode<classMassage>>* arcList,int &vnum,int &anum)
{//��ֵ��Ԫ��
	//VNode<classMassage> data[14];//14�ſγ�
	//ArcInfo<VNode<classMassage>>arcList[19];//19����Ӧ����Ϣ
	vnum = 14; anum = 19;
	data[0].date.index = 1; data[0].date.classname = "������ƻ���"; data[0].date.wight = 2;
	data[1].date.index = 2; data[1].date.classname = "��ɢ��ѧ"; data[1].date.wight = 3;
	data[2].date.index = 3; data[2].date.classname = "���ݽṹ"; data[2].date.wight = 4;
	data[3].date.index = 4; data[3].date.classname = "�������"; data[3].date.wight = 3;
	data[4].date.index = 5; data[4].date.classname = "������������"; data[4].date.wight = 2;
	data[5].date.index = 6; data[5].date.classname = "�����ԭ��"; data[5].date.wight = 3;
	data[6].date.index = 7; data[6].date.classname = "����ԭ��"; data[6].date.wight = 4;
	data[7].date.index = 8; data[7].date.classname = "����ϵͳ"; data[7].date.wight = 4;
	data[8].date.index = 9; data[8].date.classname = "�ߵ���ѧ"; data[8].date.wight = 7;
	data[9].date.index = 10; data[9].date.classname = "���Դ���"; data[9].date.wight = 5;
	data[10].date.index = 11; data[10].date.classname = "��ͨ����"; data[10].date.wight = 2;
	data[11].date.index = 12; data[11].date.classname = "��ֵ����"; data[11].date.wight = 3;
	data[12].date.index = 13; data[12].date.classname = "�������"; data[12].date.wight = 3;
	data[13].date.index = 14; data[13].date.classname = "���ݿ�ԭ��"; data[13].date.wight = 3;
	//��Ӧʵ�����������ͼ��Ϣ�������dataԪ�ظ�����Ϣ���鸳ֵ,,,�˴�weight��Ϊ���򻡻�βԪ��Ȩֵ
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
//����Ԫ��Ĭ�ϳ�ʼ��
	for (int i = 14; i < KIND; i++){data[i].date.index = -1; data[i].date.classname = "wu"; data[i].date.wight = -1;}
	for (int j = 19; j < RELA; j++)
	{arcList[j].From = data[14]; arcList[j].To = data[14]; arcList[j].weight = -1;}

	cout << "Ĭ�Ͽα���Ϣ����ӣ�" << endl;
}
//��ӿγ�
void addClass(VNode<classMassage>* data, ArcInfo<VNode<classMassage>>* arcList,int &vnum,int &anum) {
	VNode<classMassage> target;
	int a,index=0;
	char s[20] = { "0" };
	target.firstarc = NULL;
	target.in = 0;
	cout << "����γ̱��" << endl;
	cin >> target.date.index;
	cout << "����γ�����" << endl;
	cin >> target.date.classname;
	for(int i=0;i<vnum;i++)
		if (data[i].date.classname == target.date.classname)
		{
			cout << "�γ��Ѵ��ڣ�" << endl;
			return;
		}
	cout << "����γ�ѧ��" << endl;
	cin >> target.date.wight;
	data[vnum].date.classname = target.date.classname;
	data[vnum].date.index = vnum + 1;
	data[vnum].date.wight = target.date.wight;
	vnum++;
	cout << "�γ��Ƿ�������Ҫ�󣿣�1.��  2.û�У�" << endl;
	cin >> a;
	while (a!=2)
	{
		switch (a)
	{
		cout << "1.�������Ҫ��γ�" << endl;
		cout << "2.������" << endl;
		cin >> a;
	case 1: {
		cout << "�������޿γ����ƣ�";
		 gets_s(s);
		 for (int i = 0; i < vnum; i++)
		 {
			 if (data[i].date.classname == s)
			 {index = i;
			 break;
			 }	 
		 }
		 if (!index)
			 cout << "�γ̲����ڣ�"<<endl;
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
	cout << "�γ��Ƿ�������пγ̵�Լ������1.��  2.û�У�" << endl;
	cin >> a;
	while (a != 2)
	{
		switch (a)
		{
			cout << "1.���Լ���γ�" << endl;
			cout << "2.������" << endl;
			cin >> a;
		case 1: {
			cout << "����Լ���γ����ƣ�";
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
				cout << "�γ̲����ڣ�" << endl;
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
//ɾ���γ�
void deleteClass(VNode<classMassage>* data, ArcInfo<VNode<classMassage>>* arcList, int& vnum, int& anum) {
	char s[20] = { "0" };
	char c;
	int index = 0;
	cout << "����ɾ���γ����ƣ�";
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
		cout << "�γ̲����ڣ�" << endl;
		return;
	}
	else
	{//-1��ʾɾ��
		data[index].date.wight = -1;
		for (int j = 0; j < anum; j++)
		{
			if (arcList[j].From.date.classname == s || arcList[j].To.date.classname == s)
				arcList[j].weight = -1;
		}
	}
	cout << "�γ���ɾ��" << endl;
}
//���Ŀγ���Ϣ
void changeClass(VNode<classMassage>* data, ArcInfo<VNode<classMassage>>* arcList, int& vnum, int& anum) {
	char s[20] = { "0" };
	char s1[20] = { "0" };
	int index = 0;
	int a; char c;
	cout << "������Ŀγ����ƣ�";
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
		cout << "�γ̲����ڣ�" << endl;
		return;
	}
	else
	{
		cout << "ѡ�������" << endl;
		cout << "1.�γ�����" << endl;
		cout << "2.�γ�ѧ��" << endl;
		cin >> a;
		if (a == 1)
		{
			cout << "������ĺ����ƣ�";
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
			cout << "������ĺ�ѧ�֣�";
			cin >> a;
			data[index].date.wight = a;
			for (int j = 0; j < anum; j++)
			{
				if (arcList[j].From.date.index == index + 1)
					arcList[j].weight = a;
			}
		}
	}
	cout << "�������" << endl;
}


