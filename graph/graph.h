#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>  
// #include <vector>
#include <queue>

using namespace std;

typedef enum { UNKNOWN, KNOWN} VStatus; //顶点状态
typedef enum { UNSORTED, SORTED} EStatus; //边状态

template <typename T>
struct Vertex
{
    T data;       //存储数据
    int inDegree, outDegree; //入度、出度
	int parentV, distance;
	VStatus status;

};

template <typename T>
struct Edge
{
    T data[2];
	int index1, index2;      //关联的节点
	int weight;              //权重
	EStatus status;

};

template <typename T>
struct 	AdjList
{
	int index;
	Edge<T> edg;
	AdjList<T>* next;

};

template <typename T>
struct 	VexList
{
	Vertex<T> vex;
	AdjList<T>* first;

};

// template <typename T>
// struct 	TreeNode
// {
// 	Vertex<T> vex;
// 	TreeNode<T>* firstChild;
// 	TreeNode<T>* nextSibling;

// };


template <typename T>
class GraphList{
	
	int VexNum;             // 图的顶点的数目
    int EdgNum;             // 图的边的数目
	VexList<T>* V;
	AdjList<T>* List;
		
	public:
	GraphList(){cout << "GraphList" << endl; }

	GraphList(T vexs[], int vlen, T edges[][2], int elen, int weight[]){

		// 初始化"顶点数"和"边数"
		VexNum = vlen;
		EdgNum = elen;
		V = new VexList<T>[VexNum]; 

		// 初始化"邻接表"的顶点
		for(int i = 0; i<VexNum; i++)
		{
			V[i].vex.data = vexs[i];
			V[i].vex.distance = UINT8_MAX;
			V[i].vex.status = UNKNOWN;
			V[i].first = NULL;
		}

		// 初始化"邻接表"的边
		for(int i = 0; i < EdgNum; i++)
		{
			T data1, data2;
			int index1, index2; 
			// 读取边的起始顶点和结束顶点
			data1 = edges[i][0];
			data2 = edges[i][1];

			index1 = findVex(data1);
			index2 = findVex(data2);

			// 初始化邻接表
			List = new AdjList<T>;
			List->index = index2;
			List->edg.data[0] = data1;
			List->edg.data[1] = data2;
			List->edg.weight = weight[i];
			// 将节点链接到"index1所在链表的末尾"
			if(V[index1].first == NULL){
				V[index1].first = List;
				
			}
				

			else
				addAdjVex(V[index1].first, List);
		}

		cout << "create GraphList" << endl; 
	}


	~GraphList(){
		for(int i = 0; i<VexNum; i++)
		{
			AdjList<T> *p = V[i].first;
			V[i].first = NULL;
			while (p != NULL){
				AdjList<T>* q = p;
				p = p->next;
				delete q;//当前节点指向下一节点后删除该节点
			}
		}
		delete[] V;
		cout << "~GraphList" << endl; }

	//查找指定节点
	int findVex(T data){
		for(int i = 0; i < VexNum; i++)
			if(V[i].vex.data == data)
				return i;
		return -1;
	}	
	
	//添加邻接节点到列表尾部
	void addAdjVex(AdjList<T> *list, AdjList<T> *node)
	{
		AdjList<T> *p = list;

		while(p->next)
			p = p->next;
		p->next = node;
	}


	void dijkstra(){

		for(int i = 0; i < VexNum; i++)
		{
			V[i].vex.distance = UINT8_MAX;
			V[i].vex.parentV = -1;
			V[i].vex.status = UNKNOWN;
		}
		V[0].vex.distance = 0;

		int index_short = 0;
		while ( V[index_short].vex.status == UNKNOWN )
		{
			AdjList<T> *p = V[index_short].first;
			V[index_short].vex.status = KNOWN;

			for(int index_temp = p->index; p != NULL ; p = p->next){
				index_temp = p->index;

				if( (V[index_temp].vex.status == UNKNOWN) && (V[index_temp].vex.distance > V[index_short].vex.distance + p->edg.weight) ){
					// cout << V[index_temp].vex.distance << endl;
					// cout << V[index_short].vex.distance << endl;
					// cout << p->edg.weight << " " << index_short << endl;

					V[index_temp].vex.distance = V[index_short].vex.distance + p->edg.weight;
					V[index_temp].vex.parentV = index_short;
				}
			}

			for(int shrotest_dist = UINT8_MAX, i = 0; i < VexNum; i++)
			{
				if( (V[i].vex.status == UNKNOWN) && (V[i].vex.distance < shrotest_dist) ){
					shrotest_dist = V[i].vex.distance;
					index_short = i;
				}
			}
		}
		

	}

	void printPath(T vex){
		int index;
		index = findVex(vex);
		cout << "\n" << "Path to " << vex << ":" << endl;
		// cout << V[3].vex.parentV << endl;
		while(V[index].vex.parentV != -1){
			cout << V[index].vex.data << "<-";
			index = V[index].vex.parentV;
		}
		cout << V[0].vex.data << endl;

	}

	//打印图
	void printGraph(){

		cout << "\n" << "List Graph:" << endl;
		cout << "index(node): index(adjnode, weight)" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << i << "(" << V[i].vex.data << "): ";
			AdjList<T> * node = V[i].first;

			while (node != NULL)
			{
				cout << node->index << "(" << V[node->index].vex.data << ", " << node->edg.weight << ") ";
				node = node->next;
			}
			cout << endl;
		}
	}

};


template <typename T> //顶点类型、边类型
class GraphMatrix{ //基于向量，以邻接矩阵形式实现的图

	int VexNum;             // 图的顶点的数目
    int EdgNum;             // 图的边的数目
	Vertex<T>* V; 			//顶点
	Edge<T>** E; 			//边
	Edge<T>* E_sorted; 
	// TreeNode<T>* MiniSpanTree;

	public:
	GraphMatrix(T vexs[], int vlen, T edges[][2], int elen, int weight[]){

		// 初始化"顶点数"和"边数"
		VexNum = vlen;
		EdgNum = elen;
		const int len = vlen;
		V = new Vertex<T>[len];
		E_sorted = new Edge<T>[elen];
		E = new Edge<T>*[len];

		// 初始化顶点
		for(int i = 0; i < VexNum; i++)
		{
			E[i] = new Edge<T>[len];
			V[i].data = vexs[i];
			V[i].parentV = -1;
			V[i].status = UNKNOWN;
			// cout << V[i].data << endl;
		}

		// 初始化"邻接矩阵"的边
		for(int i = 0; i < EdgNum; i++)
		{
			T data1, data2;
			int index1, index2; 
			// 读取边的起始顶点和结束顶点
			data1 = edges[i][0];
			data2 = edges[i][1];

			index1 = findVex(data1);
			index2 = findVex(data2);

			// 初始化邻接矩阵
			E_sorted[i].data[0] = data1;
			E_sorted[i].data[1] = data2;
			E_sorted[i].index1 = index1;
			E_sorted[i].index2 = index2;
			E_sorted[i].weight = weight[i];
			E_sorted[i].status = UNSORTED;
			// E[index1][index2].data = edges[i][2];
			// E[index1][index2].index1 = index1;
			// E[index1][index2].index2 = index2;
			// E[index1][index2].weight = weight[i];
			// E[index1][index2].status = UNSORTED;
			E[index1][index2] = E_sorted[i];
			E[index2][index1] = E[index1][index2];

		}

		cout << "create GraphMatrix" << endl; 
	}

	~GraphMatrix() { //析构

		delete [] V;
		for ( int k = 0; k < VexNum; k++ ) //边记录
			delete [] E[k]; //逐条清除
			
		delete[] E;
		delete[] E_sorted;
		cout << "~GraphMatrix" << endl;
	}

	void sortEdge(){
		for(int i = 1; i < EdgNum; i++){
			Edge<T> temp = E_sorted[i];
			int j;
			for(j = i; j > 0 && temp.weight < E_sorted[j-1].weight; j--){
				E_sorted[j] = E_sorted[j-1];
			}
			E_sorted[j] = temp;
			E_sorted[j].status = SORTED;
		}

		// for(int i = 0; i < EdgNum; i++)
		// cout << E_sorted[i].data << endl;
		
	}


	void Kruskal(){

		sortEdge();
		for(int i = 0; i < EdgNum; i++){
			if(findRoot(E_sorted[i].index1) != findRoot(E_sorted[i].index2))
				V[E_sorted[i].index2].parentV = E_sorted[i].index1;
		}
		// printTree();
		
		//单节点树初始化
		// MiniSpanTree = new TreeNode<T>[VexNum];
		// for(int i = 0; i < VexNum; i++){		
		// 	MiniSpanTree[i].vex = V[i];
		// 	MiniSpanTree[i].firstChild = NULL;
		// 	MiniSpanTree[i].nextSibling = NULL;
		// }
		//查找最短边
		// int miniEdge[2] = {0, 0};
		// cout << miniEdge[0] << miniEdge[1] << endl;
		//检查是否构成环
		//析构最小生成树
		// for(int i = 0; i < VexNum; i++){
		// 	MiniSpanTree[i].firstChild = NULL;
		// 	MiniSpanTree[i].nextSibling = NULL;
		// }
		// delete [] MiniSpanTree;

	}

		//查找指定节点
	int findVex(T data){
		for(int i = 0; i < VexNum; i++)
			if(V[i].data == data)
				return i;
		return -1;
	}

		//查找节点树的根
	int findRoot(int index){
		while(V[index].parentV != -1){
			index = V[index].parentV;
		}
		return index;
	}

	// 	//查找最短边
	// int* findMiniEdge(){
	// 	int miniEdge[2] = {0, 0};
	// 	int shortest_weight = UINT8_MAX;
	// 	for(int i = 0; i < VexNum; i++){
	// 		for(int j= i + 1; j < VexNum; j++){
	// 			if((E[i][j].weight < shortest_weight) && (E[i][j].weight != 0) ){
	// 				shortest_weight = E[i][j].weight;
	// 				miniEdge[0] = i;
	// 				miniEdge[1] = j;
	// 			}
	// 		}
	// 	}		
	// 	return miniEdge;
	// }

	void printTree(){

		queue<int> index_iterate;
		index_iterate.push(-1);
		// int level = 1;
		// int stashNode = 0;

		cout << "\n" << "MiniSpanTree is:";

		while(!index_iterate.empty()){
			
			for(int i = 0; i < VexNum; i++){
				if(V[i].parentV == index_iterate.front()){
					cout << "	"  << V[i].data;
					index_iterate.push(i);
					// stashNode++;//多一个该层父节点要找下层子节点
				}
			}
			// cout << endl;
			index_iterate.pop();
			// stashNode--;
			// if(stashNode == 0)	level++;		
		}
		cout << endl;

	}	

	//打印图
	void printGraph(){

		cout << "\n" << "Matrix Graph:" << endl;
		cout << "	A	B	C	D	E	F	G" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << V[i].data;
			for(int j = 0; j < VexNum; j++){
				cout << "	" << E[i][j].weight;
			}
			cout << endl;
		}
	}	

};


#endif
