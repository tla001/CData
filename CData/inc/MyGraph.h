/*
 * MyGraph.h
 *
 *  Created on: 2016年9月18日
 *      Author: Administrator
 */

#ifndef INC_MYGRAPH_H_
#define INC_MYGRAPH_H_

#include "Include.h"

typedef char VertexType;	//顶点数据类型
typedef int EdgeType;		//边权重数据类型

#define MAXVEX 20			//最大顶点数
#define INF		65535		//代表正无穷

#define debug

typedef struct {
	VertexType vexs[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVer, numEdg;
} MGraph;

int LocateMGraph(MGraph *g, VertexType v);
void CreateMGraph(MGraph *g);
void PrintMGraph(MGraph g);
void MGraphDFS(MGraph g, int i);
void MGraphDFSTraverse(MGraph g);
void MGraphTest();

typedef struct EdgeNode         //边表结点
{
	int adjvex;         //邻接点域，存储该顶点对应的下标
	EdgeType weigth;        //用于存储权值，对于非网图可以不需要
	struct EdgeNode *next;      //链域，指向下一个邻接点
} EdgeNode;
typedef struct VertexNode       //顶点表结构
{
	VertexType data;        //顶点域，存储顶点信息
	EdgeNode *firstedge;        //边表头指针
} VertexNode, AdjList[MAXVEX];
typedef struct {
	AdjList adjList;
	int numVertexes, numEdges;  //图中当前顶点数和边数
} GraphList;

int LocateLGraph(GraphList *g, VertexType v);
void CreateLGraph(GraphList *g);
void PrintLGraph(GraphList *g);
void LGraphDFS(GraphList g, int i);
void LGraphDFSTraverse(GraphList g);
void LGraphTest();

//十字链表
typedef struct VertexTNode       //顶点表结构
{
	VertexType data;        //顶点域，存储顶点信息
	EdgeNode *firstin;        //边表头指针
	EdgeNode *firstout;
} VertexTNode, AdjTList[MAXVEX];
typedef struct {
	AdjTList adjList;
	int numVertexes, numEdges;  //图中当前顶点数和边数
} GraphTList;

int LocateTGraph(GraphTList *g, VertexType v);
void CreateTGraph(GraphTList *g);
void PrintTGraph(GraphTList *g);
void TGraphTest();

//Prim用结构体
struct CloseEdge {
	VertexType adjvex;
	EdgeType lowcost;
};
//Kruskal 用结构体
struct EdgeInfo {
	VertexType v1;
	VertexType v2;
	EdgeType cost;
	int used;		//0表示未用，1表示用了，筛选时用
};
void MGraphPrimTest();
void MGraphKruskalTest();		//传值方式
void MGraphKruskalTest1();		//返回值方式

void MGraphDijkstraTest();
void MGraphFloydTest();
void MGraphFloydTest1();
#endif /* INC_MYGRAPH_H_ */
