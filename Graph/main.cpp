#include"menu.hpp"
int main(void) 
{
	KIND = 30;
	RELA = 50;
	int vnum, anum;//��¼����ͱ���
	vnum = 0;anum = 0;
	VNode<classMassage>* data;//�γ���Ϣ����
	ArcInfo<VNode<classMassage>>* arcList;//�γ̹�ϵ����
	data = new VNode<classMassage>[KIND];
	arcList = new ArcInfo<VNode<classMassage>>[RELA];
	data->date.wight = -1;
	arcList->weight = -1;
 Graph<classMassage>* myGraph = new Graph<classMassage>();
 while (true) {
	 system("cls");
  showMenu();
  int a;
  cin >> a;
  switch (a) {
  case 1:
	  TestClas(data, arcList, vnum, anum);
	  break;
  case 2:
	  InitClassMassage(data, arcList, vnum, anum);//��ʼ���γ̷�����Ϣ
      break;
  case 3:
      addClass(data,arcList,vnum,anum);//��ӿγ�
      break;
  case 4:
      deleteClass(data, arcList, vnum, anum);//ɾ���γ�
      break;
  case 5:
      changeClass(data, arcList, vnum, anum);//���¿γ�
      break;
  case 6:
  { 
	  myGraph->CreateGrah(vnum,anum,data,arcList);//����ͼ
	  myGraph->TopOrder();//������������α�
	  break;
  }
  case 7:
      myGraph->DispGraph();//չʾͼ
	  break;
  case 8:
	  Printclass(data);//��ǰ�γ���ʾ
	  break;
  case 9:
	  PrintRela(arcList);//��ǰ�γ̹�ϵ��ʾ
	  break;
  case 10:
	  Clsclasstable(data, arcList);//��յ�ǰ�α�
	  break;
  case 0:
	  return 0;
  }
  system("pause");
 }
 return 0;
}