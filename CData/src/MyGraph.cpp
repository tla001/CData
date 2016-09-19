/*
 * MyGraph.cpp
 *
 *  Created on: 2016年9月18日
 *      Author: Administrator
 */

#include "MyGraph.h"

//定位
int LocateMGraph(MGraph *g, VertexType v) {
	int i = 0;
	for (i = 0; i < g->numVer; i++) {
		if (g->vexs[i] == v) {
			break;
		}
	}
	if (i >= g->numVer) {
		return -1;
	}
	return i;
}
//建立一个无向网图的邻接矩阵表示
void CreateMGraph(MGraph *g) {
	int i, j, k;
	cout << "please input the nums of vertexs and edges: \n";
	cin >> g->numVer >> g->numEdg;
#ifdef debug
	cout<<"you have input vertexs num= "<<g->numVer<<"\tedges num= "<<g->numEdg<<endl;
#endif
	cout << "input vertexs:\n";
	for (i = 0; i < g->numVer; i++) {
		cin >> g->vexs[i];
	}
	cout << "input done\n";
#ifdef debug
	for(i=0;i<g->numVer;i++) {
		cout<<g->vexs[i]<<"\t";
	}
	cout<<endl;
#endif
	for (i = 0; i < g->numVer; i++) {
		for (j = 0; j < g->numVer; j++) {
			if (i == j)
				g->arc[i][j] = 0;
			else
				g->arc[i][j] = INF; //初始化
		}
	}
	for (k = 0; k < g->numEdg; k++) {
		VertexType p, q;
		EdgeType w;
		cout << "input (vi,vj) as 'vi vj' " << endl;
		cin >> p >> q;
		cout << "input edge pounds:" << endl;
		cin >> w;
		int m = -1;
		int n = -1;
		m = LocateMGraph(g, p);
		n = LocateMGraph(g, q);
		if (m == -1 || n == -1) {
			cout << "err" << endl;
			exit(-1);
		}
		g->arc[m][n] = w;
		g->arc[n][m] = g->arc[m][n];
#ifdef debug
		cout<<w<<endl;
		cout<<"m= "<<m<<"\tn= "<<n<<endl;
		cout<<g->arc[m][n]<<endl;
#endif
	}
}

//打印图
void PrintMGraph(MGraph g) {
	int i, j;
	for (i = 0; i < g.numVer; i++) {
		for (j = 0; j < g.numVer; j++) {
			cout << g.arc[i][j] << "\t";
		}
		cout << "\n";
	}
}
void MGraphVisit(VertexType v) {
	cout << v << " ";
}
int visited[MAXVEX];
//邻接矩阵的深度优先递归算法
void MGraphDFS(MGraph g, int i) {
	int j;
	visited[i] = 1;
	MGraphVisit(g.vexs[i]);
	for (j = 0; j < g.numVer; j++) {
		if (g.arc[i][j] > 0 && g.arc[i][j] < 65535 && !visited[j]) {
			MGraphDFS(g, j);
		}
	}
}
//邻接矩阵的深度遍历
void MGraphDFSTraverse(MGraph g) {
	int i;
	for (i = 0; i < g.numVer; i++) {
		visited[i] = 0;
	}
	for (i = 0; i < g.numVer; i++) {
		if (!visited[i]) {
			MGraphDFS(g, i);
		}
	}
}
void MGraphTest() {
	MGraph g;
	CreateMGraph(&g);
	PrintMGraph(g);
	MGraphDFSTraverse(g);
}
/***********************************************/
int LocateLGraph(GraphList *g, VertexType v) {
	int i;
	for (i = 0; i < g->numVertexes; i++) {
		if (v == g->adjList[i].data) {
			break;
		}
	}
	if (i >= MAXVEX) {
		return -1;
	}
	return i;
}
void CreateLGraph(GraphList *g) {
	int i;
	EdgeNode *e, *f;

	cout << "please input the nums of vertexs and edges: \n";
	cin >> g->numVertexes >> g->numEdges;
#ifdef debug
	cout<<"you have input vertexs num= "<<g->numVertexes<<"\tedges num= "<<g->numEdges<<endl;
#endif
	cout << "input vertexs data:\n";
	for (i = 0; i < g->numVertexes; i++) {
		cin >> g->adjList[i].data;
		g->adjList[i].firstedge = NULL;
	}
	//建表
	for (i = 0; i < g->numEdges; i++) {
		VertexType p, q;
		EdgeType w;
		cout << "input (vi,vj) as 'vi vj' " << endl;
		cin >> p >> q;
		cout << "input edge pounds:" << endl;
		cin >> w;
		int m = -1, n = -1;
		m = LocateLGraph(g, p);
		n = LocateLGraph(g, q);
#ifdef debug
		cout<<"m= "<<m<<"\tn= "<<n<<endl;
		cout<<"p= "<<p<<"\tq= "<<q<<endl;
#endif
		if (m == -1 || n == -1) {
			return;
		}
		//申请内存，生成边表节点
		e = (EdgeNode *) malloc(sizeof(EdgeNode));
		if (e == NULL) {
			exit(-1);
		}
		e->adjvex = n;
		e->next = g->adjList[m].firstedge;
		e->weigth = w;
		g->adjList[m].firstedge = e;

		f = (EdgeNode *) malloc(sizeof(EdgeNode));
		if (f == NULL) {
			exit(-1);
		}
		f->adjvex = m;
		f->next = g->adjList[n].firstedge;
		f->weigth = w;
		g->adjList[n].firstedge = f;
	}
}
void PrintLGraph(GraphList *g) {
	int i = 0;
	while (i < g->numVertexes) {
		cout << "顶点 " << g->adjList[i].data << " :";
		EdgeNode *e = NULL;
		e = g->adjList[i].firstedge;
		while (e != NULL) {
			cout << g->adjList[e->adjvex].data << "( " << e->weigth << " )\t";
			e = e->next;
		}
		cout << endl;
		i++;
	}
}
void LGraphVisit(VertexType v) {
	cout << v << " ";
}
//邻接表的深度优先递归算法
void LGraphDFS(GraphList g, int i) {
	EdgeNode *p;
	visited[i] = 1;
	LGraphVisit(g.adjList[i].data);
	p = g.adjList[i].firstedge;
	while (p) {
		if (!visited[p->adjvex]) {
			LGraphDFS(g, p->adjvex);
		}
		p = p->next;
	}
}
//邻接表的深度遍历
void LGraphDFSTraverse(GraphList g) {
	int i;
	for (i = 0; i < g.numVertexes; i++) {
		visited[i] = 0;
	}
	for (i = 0; i < g.numVertexes; i++) {
		if (!visited[i]) {
			LGraphDFS(g, i);
		}
	}
}
void LGraphTest() {
	GraphList g;
	CreateLGraph(&g);
	PrintLGraph(&g);
	LGraphDFSTraverse(g);
}
/***********************************************/
int LocateTGraph(GraphTList *g, VertexType v) {
	int i;
	for (i = 0; i < g->numVertexes; i++) {
		if (v == g->adjList[i].data) {
			break;
		}
	}
	if (i >= MAXVEX) {
		return -1;
	}
	return i;
}
void CreateTGraph(GraphTList *g) {
	int i;
	EdgeNode *e, *f;

	cout << "please input the nums of vertexs and edges: \n";
	cin >> g->numVertexes >> g->numEdges;
#ifdef debug
	cout<<"you have input vertexs num= "<<g->numVertexes<<"\tedges num= "<<g->numEdges<<endl;
#endif
	cout << "input vertexs data:\n";
	for (i = 0; i < g->numVertexes; i++) {
		cin >> g->adjList[i].data;
		g->adjList[i].firstin = NULL;
		g->adjList[i].firstout = NULL;
	}
	//建表
	for (i = 0; i < g->numEdges; i++) {
		VertexType p, q;
		EdgeType w;
		cout << "input (vi,vj) as 'vi vj' " << endl;
		cin >> p >> q;
		cout << "input edge pounds:" << endl;
		cin >> w;
		int m = -1, n = -1;
		m = LocateTGraph(g, p);
		n = LocateTGraph(g, q);
#ifdef debug
		cout<<"m= "<<m<<"\tn= "<<n<<endl;
		cout<<"p= "<<p<<"\tq= "<<q<<endl;
#endif
		if (m == -1 || n == -1) {
			return;
		}
		//申请内存，生成边表节点
		e = (EdgeNode *) malloc(sizeof(EdgeNode));
		if (e == NULL) {
			exit(-1);
		}
		e->adjvex = n;
		e->next = g->adjList[m].firstout;
		e->weigth = w;
		g->adjList[m].firstout = e;

		f = (EdgeNode *) malloc(sizeof(EdgeNode));
		if (f == NULL) {
			exit(-1);
		}
		f->adjvex = m;
		f->next = g->adjList[n].firstin;
		f->weigth = w;
		g->adjList[n].firstin = f;
	}
}
void PrintTGraph(GraphTList *g) {
	int i = 0;
	while (i < g->numVertexes) {
		cout << "顶点 " << g->adjList[i].data << " :\n";
		EdgeNode *e = NULL;
		cout << "\tout: ";
		e = g->adjList[i].firstout;
		while (e != NULL) {
			cout << g->adjList[e->adjvex].data << "( " << e->weigth << " )\t";
			e = e->next;
		}
		cout << endl;
		cout << "\tin: ";
		e = g->adjList[i].firstin;
		while (e != NULL) {
			cout << g->adjList[e->adjvex].data << "( " << e->weigth << " )\t";
			e = e->next;
		}
		cout << endl;
		i++;
	}
}
void TGraphTest() {
	GraphTList g;
	CreateTGraph(&g);
	PrintTGraph(&g);
}
