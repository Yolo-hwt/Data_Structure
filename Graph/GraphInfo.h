#pragma once
//�γ���Ϣ
struct classMassage {
	int index;//����λ��
	string classname;//�γ�����
	int wight;//ѧ��
};
//����Ϣ
template<class ElemType>
struct ArcInfo {
	ElemType From;  //���
	ElemType To;  //�յ�
	int weight;   //Ȩֵ
};
//���ڵ�
struct ArcNode {
	int adjvex;  //��ͷ����ͷָ�򶥵�λ��
	int weight; //Ȩֵ
	struct ArcNode* nextarc;//ָ����һ����ָ��
};
//����ڵ�
template<class ElemType>
struct VNode {
	ElemType date;
	int in;//���
	ArcNode* firstarc;//ָ�������е�һ����㣬ע�⣺ΪArcNode���͵�ָ��
};
