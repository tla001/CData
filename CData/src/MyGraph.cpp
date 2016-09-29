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
	int res = 0;
	for (i = 0; i < g->numVer; i++) {
		if (g->vexs[i] == v) {
			res = 1;
			break;
		}
	}
	if (res > 0)
		return i;
	else
		return -1;
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
	int res = 0;
	for (i = 0; i < g->numVertexes; i++) {
		if (v == g->adjList[i].data) {
			res = 1;
			break;
		}
	}
	if (res > 0)
		return i;
	else
		return -1;
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
	int res = 0;
	for (i = 0; i < g->numVertexes; i++) {
		if (v == g->adjList[i].data) {
			break;
		}
	}
	if (res > 0)
		return i;
	else
		return -1;
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
/************************Prim ***********************/
int MiniEdge(int num, struct CloseEdge *closedge) {
	EdgeType min = 65535;
	int pos;
	int i;
	for (i = 0; i < num; i++) {
		if (closedge[i].lowcost != 0) {
			if (closedge[i].lowcost < min) {
				min = closedge[i].lowcost;
				pos = i;
			}
		}
	}
	if (i > num)
		return -1;
	return pos;
}
void MiniSpanTree_PRIM(MGraph *g, VertexType u, struct CloseEdge *closedge,
		struct CloseEdge *saver) {
	//step1 初始化，将根节点附近的顶点复制到closedge里，准备查找下一顶点
	int k = LocateMGraph(g, u);
	for (int j = 0; j < g->numVer; ++j) { //进行初始化
		if (j != k) {
			closedge[j].adjvex = u;
			closedge[j].lowcost = g->arc[k][j];
		}
	}
	closedge[k].lowcost = 0; //表示将u加入最小生成树定点集合（已经访问过的）
	//step2 遍历剩余顶点，查找权重最小，并将新加入顶点的附近顶点信息更新到closedge，
	//lowcost = 0意味着顶底在closegde内，可以避免重复
	for (int i = 1; i < g->numVer; i++) {
		//查找当前closedge集合里，边权重最小的顶点，保存输出，并更新到closedge集合
		k = MiniEdge(g->numVer, closedge); //找到下一个定点
		cout << closedge[k].adjvex << "\t" << g->vexs[k] << endl;
		saver[i] = closedge[i];
		closedge[k].lowcost = 0; //表示新找到的顶点加入最小生成树定点集合（已经访问过的）
		//更新下一步查找的顶点信息
		for (int j = 0; j < g->numVer; j++) {
			if (g->arc[k][j] < closedge[j].lowcost && j != k) {
				closedge[j].adjvex = g->vexs[k];
				closedge[j].lowcost = g->arc[k][j];
			}
		}
	}
}
void PrintMST_PRIM(MGraph *g, struct CloseEdge *saver) {
	int sum = 0;
	cout << "MST PRIM edges:" << endl;
	for (int i = 1; i < g->numVer; i++) {
		cout << "edge: " << saver[i].adjvex << "\t" << g->vexs[i]
				<< " weight is " << saver[i].lowcost << endl;
		sum += saver[i].lowcost;
	}
	cout << "MST PRIM weight sum= " << sum << endl;
}
void MGraphPrimTest() {
	MGraph g;
	VertexType u = 'a';
	struct CloseEdge closedge[MAXVEX], saver[MAXVEX];
	CreateMGraph(&g);
	PrintMGraph(g);
	//MGraphDFSTraverse(g);
	MiniSpanTree_PRIM(&g, u, closedge, saver);
	PrintMST_PRIM(&g, saver);
}
/************************Kruskal  ***********************/
//需要传递长度，无法直接通过指针得到长度，但是数组可以，区别
struct EdgeInfo *MiniEdgeInfo(struct EdgeInfo *allEdge, int size) {
	struct EdgeInfo *mini = (struct EdgeInfo *) malloc(sizeof(EdgeInfo));
	int lowcost = 65535;
	int pos = 65535;
	for (int i = 0; i < size; i++) {
		if (allEdge[i].used == 0) {
			if (allEdge[i].cost < lowcost) {
				lowcost = allEdge[i].cost;
				pos = i;
			}
		}
	}
	if (pos >= 0 && pos < 65535) {
		allEdge[pos].used = 1;
		mini->cost = allEdge[pos].cost;
//		mini->used = allEdge[pos].used;
//		mini->v1 = allEdge[pos].v1;
//		mini->v2 = allEdge[pos].v2;
		*mini = allEdge[pos];		//值传递
	} else {
		exit(-1);
	}
	return mini;
}
int getEnd(int *vexEnds, int p) {
	while (vexEnds[p] >= 0)
		p = vexEnds[p];
	return p;
}
struct EdgeInfo * MiniSpanTree_Kruskal(MGraph *g) {
	//筛选出所有的点/边信息，形成集合
	struct EdgeInfo *allEdge = (struct EdgeInfo *) malloc(
			sizeof(EdgeInfo) * g->numEdg);
	int k = 0;		//记录allEdge位置
	for (int i = 0; i < g->numVer; i++) {
		for (int j = 0; j < i; j++) {
			if (g->arc[i][j] > 0 && g->arc[i][j] < 65535) {
				allEdge[k].v1 = g->vexs[i];
				allEdge[k].v2 = g->vexs[j];
				allEdge[k].cost = g->arc[i][j];
				allEdge[k].used = 0;
				k++;
			}
		}
	}
	if (k != g->numEdg) {
		cout << "find EdgeInfo error" << endl;
	}
	struct EdgeInfo *saver = (struct EdgeInfo *) malloc(
			sizeof(EdgeInfo) * (g->numVer - 1));
	//用于记录每个顶点在该树中的终点，防止闭合回路
	int *vexEnds = (int *) malloc(sizeof(int) * g->numVer);
	for (int i = 0; i < g->numVer; i++) {
		vexEnds[i] = -1;
	}
	k = 0;		//用于记录已经找到的边
	struct EdgeInfo *mini;
	for (int i = 0; i < g->numEdg; i++) {
		mini = MiniEdgeInfo(allEdge, g->numEdg);
		int m = -1, n = -1;
		m = LocateMGraph(g, mini->v1);
		n = LocateMGraph(g, mini->v2);
		if (m == -1 || n == -1) {
			exit(-1);
		}
		int p1 = getEnd(vexEnds, m);
		int p2 = getEnd(vexEnds, n);
		if (p1 != p2) {
			vexEnds[p1] = p2;
			saver[k].cost = mini->cost;
			saver[k].used = mini->used;
			saver[k].v1 = mini->v1;
			saver[k].v2 = mini->v2;
			k++;
		}
		if (k == (g->numVer - 1))
			break;		//如果找够了n-1条边，提前结束
	}
	free(vexEnds);
	return saver;
}
void PrintMST_Kruskal(struct EdgeInfo *saver, int num) {
	int sum = 0;
	for (int i = 0; i < num; i++) {
		cout << "edge: " << saver[i].v1 << "\t" << saver[i].v2 << "\tcost: "
				<< saver[i].cost << endl;
		sum += saver[i].cost;
	}
	cout << "total cost: " << sum << endl;
}
void MGraphKruskalTest() {
	MGraph g;
	CreateMGraph(&g);
	PrintMGraph(g);
	//MGraphDFSTraverse(g);
	struct EdgeInfo *saver = MiniSpanTree_Kruskal(&g);
	PrintMST_Kruskal(saver, g.numVer - 1);
}
/************************Kruskal 一些测试 ***********************/

struct EdgeInfo *MiniEdgeInfo1(struct EdgeInfo *allEdge, int size) {
	struct EdgeInfo *mini = (struct EdgeInfo *) malloc(sizeof(EdgeInfo));
	int lowcost = 65535;
	int pos = 65535;
	for (int i = 0; i < size; i++) {
		if (allEdge[i].used == 0) {
			if (allEdge[i].cost < lowcost) {
				lowcost = allEdge[i].cost;
				pos = i;
			}
		}
	}
	if (pos >= 0 && pos < 65535) {
		allEdge[pos].used = 1;
		mini->cost = allEdge[pos].cost;
		mini->used = allEdge[pos].used;
		mini->v1 = allEdge[pos].v1;
		mini->v2 = allEdge[pos].v2;
		//*mini = allEdge[pos];
	} else {
		exit(-1);
	}
	return mini;
}
//struct EdgeInfo *&saver 需要修改指针的值，因而需要&
void MiniSpanTree_Kruskal1(MGraph *g, struct EdgeInfo *&saver) {
	//筛选出所有的点/边信息，形成集合
	struct EdgeInfo *allEdge = (struct EdgeInfo *) malloc(
			sizeof(EdgeInfo) * g->numEdg);
	int k = 0;		//记录allEdge位置
	for (int i = 0; i < g->numVer; i++) {
		for (int j = 0; j < i; j++) {
			if (g->arc[i][j] > 0 && g->arc[i][j] < 65535) {
				allEdge[k].v1 = g->vexs[i];
				allEdge[k].v2 = g->vexs[j];
				allEdge[k].cost = g->arc[i][j];
				allEdge[k].used = 0;
				k++;
			}
		}
	}
	if (k != g->numEdg) {
		cout << "find EdgeInfo error" << endl;
	}
	saver = (struct EdgeInfo *) malloc(sizeof(EdgeInfo) * (g->numVer - 1));
	//用于记录每个节点使用的次数，防止闭合回路
	int *vexEnds = (int *) malloc(sizeof(int) * g->numVer);
	for (int i = 0; i < g->numVer; i++) {
		vexEnds[i] = -1;
	}
	k = 0;		//用于记录已经找到的边
	struct EdgeInfo *mini;
	for (int i = 0; i < g->numEdg; i++) {
		mini = MiniEdgeInfo(allEdge, g->numEdg);
		int m = -1, n = -1;
		m = LocateMGraph(g, mini->v1);
		n = LocateMGraph(g, mini->v2);
		if (m == -1 || n == -1) {
			exit(-1);
		}
		int p1 = getEnd(vexEnds, m);
		int p2 = getEnd(vexEnds, n);
		if (p1 != p2) {
			vexEnds[p1] = p2;
			saver[k].cost = mini->cost;
			saver[k].used = mini->used;
			saver[k].v1 = mini->v1;
			saver[k].v2 = mini->v2;
			k++;
		}
		if (k == (g->numVer - 1))
			break;		//如果找够了n-1条边，提前结束
	}
	free(vexEnds);
}
void MGraphKruskalTest1() {
	MGraph g;
	CreateMGraph(&g);
	PrintMGraph(g);
	struct EdgeInfo *saver;
	//MGraphDFSTraverse(g);
	MiniSpanTree_Kruskal1(&g, saver);
	PrintMST_Kruskal(saver, g.numVer - 1);
}
/************************Dijkstra **********************/
void ShortPath_Dijkstra(MGraph *g, EdgeType *&dist, int *&path, VertexType s) {
	int k = LocateMGraph(g, s);
	dist = (EdgeType*) malloc(sizeof(EdgeType) * g->numVer);
	path = (int*) malloc(sizeof(int) * g->numVer);
	int *visited = (int*) malloc(sizeof(int) * g->numVer);
	//初始化距离值
	for (int i = 0; i < g->numVer; i++) {
		if (g->arc[k][i] != 65535) {
			dist[i] = g->arc[k][i];
			path[i] = k;
		} else {
			dist[i] = 65535;
			path[i] = -1;
		}
		visited[i] = 0;
	}
	visited[k] = 1;
	//大循环用于遍历余下的顶点，将余下顶点收进来，一圈一圈外扩
	for (int i = 1; i < g->numVer; i++) {
		int minDist = 65535;
		int pos = -1;
		//查找当前未访问且距离值最小的点
		for (int j = 0; j < g->numVer; j++) {
			if (visited[j] == 0 && dist[j] < minDist) {
				minDist = dist[j];
				pos = j;
			}
		}
		if (pos < 0)
			cout << "pos err" << endl;
		//将当前点归并，并更新剩下点（经过当前点）的距离值
		visited[pos] = 1;
		for (int j = 0; j < g->numVer; j++) {
			if (visited[j] == 0 && g->arc[pos][j] != 65535
					&& (minDist + g->arc[pos][j]) < dist[j]) {
				dist[j] = minDist + g->arc[pos][j];
				path[j] = pos;		//记录父节点
			}
		}
	}
}
#include <stack>
void PrintDShortPath(MGraph *g, EdgeType *dist, int *path, VertexType s,
		int end) {
	int k = LocateMGraph(g, s);
//	int *pa = (int *) malloc(sizeof(int) * g->numVer);
//	std::stack<int> p;
//	while (end != k) {
//		p.push(end);
//		end = path[end];
//	}
//	p.push(end);
//	int i = 0;
//	while (!p.empty()) {
//		pa[i] = p.top();
//		p.pop();
//		i++;
//	}
//
//	for (int j = 0; j < i; j++) {
//		cout << g->vexs[pa[j]] << "\t";
//	}
	std::stack<int> p;
	while (end != k) {
		p.push(end);
		end = path[end];
	}
	p.push(end);
	while (!p.empty()) {
		cout << g->vexs[p.top()] << "\t";
		p.pop();
	}
}
void MGraphDijkstraTest() {
	MGraph g;
	CreateMGraph(&g);
	PrintMGraph(g);
	EdgeType *dist;
	int *path;

	VertexType s = 'a';
	//MGraphDFSTraverse(g);
	ShortPath_Dijkstra(&g, dist, path, s);
	for (int i = 0; i < g.numVer; i++) {
		if (i != LocateMGraph(&g, s)) {
			cout << "from " << s << " to " << g.vexs[i] << " the short path : "
					<< endl;
			PrintDShortPath(&g, dist, path, s, i);
			cout << " long: " << dist[i] << endl;
		}
	}
}
/************************Floyd **********************/
void ShortPath_Floyd(MGraph *g, EdgeType dist[][MAXVEX], int path[][MAXVEX]) {
	for (int i = 0; i < g->numVer; i++) {
		for (int j = 0; j < g->numVer; j++) {
			dist[i][j] = g->arc[i][j];
			path[i][j] = -1;
		}
	}
	for (int k = 0; k < g->numVer; k++) {
		for (int i = 0; i < g->numVer; i++) {
			for (int j = 0; j < g->numVer; j++) {
				if (dist[i][j] > (dist[i][k] + dist[k][j])) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;
				}
			}
		}
	}
//	for (int i = 0; i < g->numVer; i++) {
//		for (int j = 0; j < g->numVer; j++) {
//			cout << dist[i][j] << "\t";
//
//		}
//		cout << endl;
//	}
//	for (int i = 0; i < g->numVer; i++) {
//		for (int j = 0; j < g->numVer; j++) {
//			cout << path[i][j] << "\t";
//
//		}
//		cout << endl;
//	}
}
void PrintFloyd(MGraph *g, EdgeType dist[][MAXVEX], int path[][MAXVEX],
		int start, int end) {
	std::stack<int> shortpath;
	int temp = end;
	while (temp >= 0 && temp != start) {
		shortpath.push(temp);
		temp = path[start][temp];
	}
	shortpath.push(start);
	cout << "from " << g->vexs[start] << " to " << g->vexs[end]
			<< " the short path : " << endl;
	while (!shortpath.empty()) {
		cout << g->vexs[shortpath.top()] << "\t";
		shortpath.pop();
	}
	cout << "*** cost : " << dist[start][end] << endl;
}
void MGraphFloydTest() {
	MGraph g;
	CreateMGraph(&g);
	PrintMGraph(g);
	EdgeType dist[MAXVEX][MAXVEX];
	int path[MAXVEX][MAXVEX];

	//MGraphDFSTraverse(g);
	ShortPath_Floyd(&g, dist, path);
	for (int i = 0; i < g.numVer; i++) {
		for (int j = 0; j < g.numVer; j++)
			if (i != j) {
				PrintFloyd(&g, dist, path, i, j);
			}
	}
}
/************************Floyd 动态数组版本**********************/
void ShortPath_Floyd1(MGraph *g, EdgeType **&dist, int **&path) {
	dist = (EdgeType **) malloc(sizeof(EdgeType *) * g->numVer);
	for (int i = 0; i < g->numVer; i++) {
		*(dist + i) = (EdgeType *) malloc(sizeof(EdgeType) * g->numVer);
	}
	path = (int **) malloc(sizeof(int *) * g->numVer);
	for (int i = 0; i < g->numVer; i++) {
		*(path + i) = (int *) malloc(sizeof(int) * g->numVer);
	}

	for (int i = 0; i < g->numVer; i++) {
		for (int j = 0; j < g->numVer; j++) {
			dist[i][j] = g->arc[i][j];
			path[i][j] = -1;
		}
	}
	for (int k = 0; k < g->numVer; k++) {
		for (int i = 0; i < g->numVer; i++) {
			for (int j = 0; j < g->numVer; j++) {
				if (dist[i][j] > (dist[i][k] + dist[k][j])) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;
				}
			}
		}
	}
//	for (int i = 0; i < g->numVer; i++) {
//		for (int j = 0; j < g->numVer; j++) {
//			cout << dist[i][j] << "\t";
//
//		}
//		cout << endl;
//	}
//	for (int i = 0; i < g->numVer; i++) {
//		for (int j = 0; j < g->numVer; j++) {
//			cout << path[i][j] << "\t";
//
//		}
//		cout << endl;
//	}
}
void PrintFloyd1(MGraph *g, EdgeType **dist, int **path, int start, int end) {
	std::stack<int> shortpath;
	int temp = end;
	while (temp >= 0 && temp != start) {
		shortpath.push(temp);
		temp = path[start][temp];
	}
	shortpath.push(start);
	cout << "from " << g->vexs[start] << " to " << g->vexs[end]
			<< " the short path : " << endl;
	while (!shortpath.empty()) {
		cout << g->vexs[shortpath.top()] << "\t";
		shortpath.pop();
	}
	cout << "*** cost : " << dist[start][end] << endl;
}
void MGraphFloydTest1() {
	MGraph g;
	CreateMGraph(&g);
	PrintMGraph(g);
	EdgeType **dist;
	int **path;

	//MGraphDFSTraverse(g);
	ShortPath_Floyd1(&g, dist, path);
	for (int i = 0; i < g.numVer; i++) {
		for (int j = 0; j < g.numVer; j++)
			if (i != j) {
				PrintFloyd1(&g, dist, path, i, j);
			}
	}
}

