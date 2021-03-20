#include"menu.hpp"
int main(void) 
{
	KIND = 30;
	RELA = 50;
	int vnum, anum;//记录顶点和边数
	vnum = 0;anum = 0;
	VNode<classMassage>* data;//课程信息数组
	ArcInfo<VNode<classMassage>>* arcList;//课程关系数组
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
	  InitClassMassage(data, arcList, vnum, anum);//初始化课程范例信息
      break;
  case 3:
      addClass(data,arcList,vnum,anum);//添加课程
      break;
  case 4:
      deleteClass(data, arcList, vnum, anum);//删除课程
      break;
  case 5:
      changeClass(data, arcList, vnum, anum);//更新课程
      break;
  case 6:
  { 
	  myGraph->CreateGrah(vnum,anum,data,arcList);//创建图
	  myGraph->TopOrder();//拓扑排序输出课表
	  break;
  }
  case 7:
      myGraph->DispGraph();//展示图
	  break;
  case 8:
	  Printclass(data);//当前课程显示
	  break;
  case 9:
	  PrintRela(arcList);//当前课程关系显示
	  break;
  case 10:
	  Clsclasstable(data, arcList);//清空当前课表
	  break;
  case 0:
	  return 0;
  }
  system("pause");
 }
 return 0;
}