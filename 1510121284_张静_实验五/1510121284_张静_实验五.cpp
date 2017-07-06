// 1510121284_张静_实验五.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<queue>
using namespace std;
#define OK 1
#define ERROR 0
const int MAX_VERTEX_NUM = 20;  //最大顶点数
typedef enum { DG, DN, UDG, UDN } GraphKind;//(有向图，有向网，无向图，无向网)
typedef int VRType;
typedef char InfoType;
typedef char VertexType;
typedef int Status;

typedef struct ArcCell {
	VRType adj;  //VRType是顶点关系类型，对于无权图，用1或者0表示顶点相邻与否，对于有权图，则为权值类型
	InfoType  info;//该弧相关信息指针
	ArcCell() {
		adj = 0;
		info = 0;
	}
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct MGraph {
	VertexType vexs[MAX_VERTEX_NUM]; //顶点向量
	AdjMatrix arcs;  //邻接矩阵
	int vexnum, arcnum;  //图当前的顶点数和弧数
	GraphKind kind;  //图的种类标志
}MGraph;

int LocateVex(MGraph G, char v1) {
	for (int i = 0; i<MAX_VERTEX_NUM; ++i) {
		if (G.vexs[i] == v1)
			return i;
	}
	return MAX_VERTEX_NUM + 1;
}

Status CreateUDN(MGraph &G) {//采用数组（邻接矩阵）表示法，构建无向网
	G.kind = UDN;  //手动赋值为无向网
	int vexnumber = 0, arcnumber = 0;
	char info;
	cout << "please input the vexnumber arcnumber and info:";
	cin >> vexnumber >> arcnumber >> info;
	G.vexnum = vexnumber;
	G.arcnum = arcnumber;
	for (int i = 0; i<G.vexnum; ++i) { //构造顶点向量
		cout << "please input the vertex of number " << i << "(type char) ";
		cin >> G.vexs[i];
	}
	for (int i = 0; i<G.vexnum; ++i)  //初始化邻接矩阵
		for (int j = 0; j<G.vexnum; ++j) {
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = 0;
		}
	char v1, v2;
	int weight = 0, i = 0, j = 0;
	char infomation;
	for (int k = 0; k<G.arcnum; ++k) {  //初始化邻接矩阵
		cout << "please input the two vertexs of the arc and it's weight " << k + 1 << " ";
		cin >> v1 >> v2 >> weight;
		i = LocateVex(G, v1);  j = LocateVex(G, v2);
		G.arcs[i][j].adj = weight;
		G.arcs[j][i].adj = weight;
		if (info != 48) {//0的ascii码为48
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

//树的深度优先遍历和广度优先搜索遍历
bool visited[MAX_VERTEX_NUM];//访问标志数组

Status VisitFunc(MGraph G, int v) { //函数变量
	if (G.vexs[v]) {
		cout << G.vexs[v] << " ";
		return OK;
	}
	return ERROR;
}

int FirstAdjVex(MGraph G, int v) {  //返回图G中顶点V的第一个邻接点
	if (G.vexnum == 0) return -1; //确定图G存在
	for (int j = 0; j<G.vexnum; ++j) {
		if (G.arcs[v][j].adj)
			return j;
	}
	return -1;
}

int NextAdjVex(MGraph G, int v, int w) {  //返回顶点v的相对与w的下一个邻接点
	if (G.vexnum == 0) return -1; //确定图G存在
	for (int j = w + 1; j<G.vexnum; ++j) {
		if (G.arcs[v][j].adj)
			return j;
	}
	return -1;
}

void DFS(MGraph G, int v) {  //从第v个顶点出发，深度优先搜索遍历图G
	visited[v] = true; VisitFunc(G, v); //访问第v个结点
	for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
		if (!visited[w]) DFS(G, w); //对v的尚未访问的邻接顶点W递归调用DFS
	}
}

void DFSTraverse(MGraph G, Status(*Visit)(MGraph G, int v)) {
	//对图做深度优先遍历
	for (int v = 0; v<G.vexnum; ++v) {  //访问标志数组初始化
		visited[v] = false;
	}
	for (int v = 0; v<G.vexnum; ++v) {
		if (!visited[v]) DFS(G, v); //对尚未访问的结点调用DFS
	}
}

void BFSTraverse(MGraph G, Status(*Visit)(MGraph G, int v)) {//广度优先搜索遍历图
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

