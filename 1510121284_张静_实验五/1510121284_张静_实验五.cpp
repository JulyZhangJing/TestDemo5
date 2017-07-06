// 1510121284_�ž�_ʵ����.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<queue>
using namespace std;
#define OK 1
#define ERROR 0
const int MAX_VERTEX_NUM = 20;  //��󶥵���
typedef enum { DG, DN, UDG, UDN } GraphKind;//(����ͼ��������������ͼ��������)
typedef int VRType;
typedef char InfoType;
typedef char VertexType;
typedef int Status;

typedef struct ArcCell {
	VRType adj;  //VRType�Ƕ����ϵ���ͣ�������Ȩͼ����1����0��ʾ����������񣬶�����Ȩͼ����ΪȨֵ����
	InfoType  info;//�û������Ϣָ��
	ArcCell() {
		adj = 0;
		info = 0;
	}
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct MGraph {
	VertexType vexs[MAX_VERTEX_NUM]; //��������
	AdjMatrix arcs;  //�ڽӾ���
	int vexnum, arcnum;  //ͼ��ǰ�Ķ������ͻ���
	GraphKind kind;  //ͼ�������־
}MGraph;

int LocateVex(MGraph G, char v1) {
	for (int i = 0; i<MAX_VERTEX_NUM; ++i) {
		if (G.vexs[i] == v1)
			return i;
	}
	return MAX_VERTEX_NUM + 1;
}

Status CreateUDN(MGraph &G) {//�������飨�ڽӾ��󣩱�ʾ��������������
	G.kind = UDN;  //�ֶ���ֵΪ������
	int vexnumber = 0, arcnumber = 0;
	char info;
	cout << "please input the vexnumber arcnumber and info:";
	cin >> vexnumber >> arcnumber >> info;
	G.vexnum = vexnumber;
	G.arcnum = arcnumber;
	for (int i = 0; i<G.vexnum; ++i) { //���춥������
		cout << "please input the vertex of number " << i << "(type char) ";
		cin >> G.vexs[i];
	}
	for (int i = 0; i<G.vexnum; ++i)  //��ʼ���ڽӾ���
		for (int j = 0; j<G.vexnum; ++j) {
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = 0;
		}
	char v1, v2;
	int weight = 0, i = 0, j = 0;
	char infomation;
	for (int k = 0; k<G.arcnum; ++k) {  //��ʼ���ڽӾ���
		cout << "please input the two vertexs of the arc and it's weight " << k + 1 << " ";
		cin >> v1 >> v2 >> weight;
		i = LocateVex(G, v1);  j = LocateVex(G, v2);
		G.arcs[i][j].adj = weight;
		G.arcs[j][i].adj = weight;
		if (info != 48) {//0��ascii��Ϊ48
			cout << "please input infomation: ";
			cin >> infomation;
			G.arcs[i][j].info = infomation;
			G.arcs[j][i].info = infomation;
		}
	}
	return OK;
}

void DisMGraph(MGraph m) {
	for (int i = 0; i<m.vexnum; ++i) {
		for (int j = 0; j<m.vexnum; ++j) {
			cout << m.arcs[i][j].adj << " ";
		}
		cout << endl;
	}
}

//����������ȱ����͹��������������
bool visited[MAX_VERTEX_NUM];//���ʱ�־����

Status VisitFunc(MGraph G, int v) { //��������
	if (G.vexs[v]) {
		cout << G.vexs[v] << " ";
		return OK;
	}
	return ERROR;
}

int FirstAdjVex(MGraph G, int v) {  //����ͼG�ж���V�ĵ�һ���ڽӵ�
	if (G.vexnum == 0) return -1; //ȷ��ͼG����
	for (int j = 0; j<G.vexnum; ++j) {
		if (G.arcs[v][j].adj)
			return j;
	}
	return -1;
}

int NextAdjVex(MGraph G, int v, int w) {  //���ض���v�������w����һ���ڽӵ�
	if (G.vexnum == 0) return -1; //ȷ��ͼG����
	for (int j = w + 1; j<G.vexnum; ++j) {
		if (G.arcs[v][j].adj)
			return j;
	}
	return -1;
}

void DFS(MGraph G, int v) {  //�ӵ�v��������������������������ͼG
	visited[v] = true; VisitFunc(G, v); //���ʵ�v�����
	for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
		if (!visited[w]) DFS(G, w); //��v����δ���ʵ��ڽӶ���W�ݹ����DFS
	}
}

void DFSTraverse(MGraph G, Status(*Visit)(MGraph G, int v)) {
	//��ͼ��������ȱ���
	for (int v = 0; v<G.vexnum; ++v) {  //���ʱ�־�����ʼ��
		visited[v] = false;
	}
	for (int v = 0; v<G.vexnum; ++v) {
		if (!visited[v]) DFS(G, v); //����δ���ʵĽ�����DFS
	}
}

void BFSTraverse(MGraph G, Status(*Visit)(MGraph G, int v)) {//���������������ͼ
	for (int v = 0; v<G.vexnum; ++v) visited[v] = false;
	queue<char> que;
	char tempvex = 0;
	for (int v = 0; v<G.vexnum; ++v) {
		if (!visited[v]) {
			visited[v] = true; Visit(G, v);
			que.push(G.vexs[v]);
			while (!que.empty()) {
				tempvex = que.front();
				que.pop();
				for (int w = FirstAdjVex(G, tempvex); w >= 0; w = NextAdjVex(G, tempvex, w)) {
					if (!visited[w]) {
						visited[w] = true;
						Visit(G, w);
						que.push(G.vexs[w]);
					}
				}
			}
		}
	}
}
int main()
{
	MGraph m;
	CreateUDN(m);
	DisMGraph(m);
	cout << "DFS result:";
	DFSTraverse(m, VisitFunc);
	cout << endl << "BFS result:";
	BFSTraverse(m, VisitFunc);
	return 0;
}

