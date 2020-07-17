#ifndef TOURGUIDE_H
#define TOURGUIDE_H

#include <iostream>  
#include<cstring>
#include <math.h>
#include <float.h>

using namespace std;

typedef enum { UNKNOWN, KNOWN} VStatus; //顶点状态

template <typename T>
struct Vertex
{
    T name;       //地点名称
    T information; //地点信息
    float location[2]; //地点全局坐标
    int visit_order, parentV; //访问顺序和父节点
    float F, G, H;//A*打分变量
    VStatus status; 
	

};

template <typename T>
struct Edge
{
  T index1, index2;      //关联的地点
  float direction;
  float distance; //路径方向和距离信息
	
};


class TourGuide{

  #define INF    FLT_MAX       //无穷大
  #define FACTOR 40.0          //比例尺
  #define Pi     3.1415926     //圆周率
  int VexNum = 15;             // 图的顶点的数目
  int EdgNum = 24;             // 图的边的数目
  float dist[15][15]; // 距离矩阵
  int path[15][15]; // 路径矩阵
  int pathN[15]={0}, path_temp[15];    //最佳访问路径
  float pathLength;   //目前最佳方位路径长度

	Vertex<string> place[15] = { //顶点，按从下到上，从左到右存储
    {"T6栋", "教学楼VI", {15, 0}},

    {"3食堂", "荔园三食堂", {3, 1}},
    {"T5栋", "教学楼V", {12, 1}},

    {"4食堂", "荔园四食堂", {7, 3}},
    {"T4栋", "教学楼IV", {9, 3}},

    {"T3栋", "教学楼III", {10, 4}},
    {"H栋", "主楼", {13, 4}},
    {"T2栋", "教学楼II", {17, 4}},

    {"1食堂", "荔园一食堂", {0, 5}},
    {"J栋", "活动中心", {12, 5}},

    {"K栋", "实训楼", {12, 7}},
    
    {"G栋", "理学楼", {7, 8}},
    
    {"A栋", "教学楼I", {2, 9}},
    
    {"L栋", "信息楼", {11, 9}},

    {"B栋", "社科楼", {6, 10}}
  }; 

	Edge<string> road_list[24] = {//边，按从下到上，从左到右存储
    {"3食堂", "4食堂"},
    {"4食堂", "T4栋"},
    {"T4栋", "T5栋"},
    {"T5栋", "T6栋"},
    
    {"3食堂", "1食堂"},
    {"4食堂", "T3栋"},
    {"T4栋", "T3栋"},
    {"T5栋", "H栋"},
    {"T6栋", "H栋"},
    {"T6栋", "T2栋"},

    {"T3栋", "H栋"},
    {"H栋", "T2栋"},

    {"T3栋", "J栋"},
    {"H栋", "J栋"},

    {"1食堂", "A栋"},
    {"J栋", "K栋"},
    {"H栋", "K栋"},
    {"T2栋", "K栋"},

    {"A栋", "G栋"},
    {"G栋", "K栋"},
    
    {"A栋", "B栋"},
    {"G栋", "B栋"},
    {"G栋", "L栋"},
    {"K栋", "L栋"}
  }; 

  float road[15][15];
  // float road[15][15] = { //边, 0为自己，INF为不存在
  //   {   0,  200, INF, INF, INF, INF, INF, 200, INF, INF},
  //   { 200,    0, 180, INF, INF, INF, INF, INF, INF, INF},
  //   { INF,  180,   0,  90, INF, 120, INF, INF, INF, INF},
  //   { INF,  INF,  90,   0,  10, INF, 130, INF, INF, INF},
  //   { INF,  INF, INF,  10,   0, INF, INF, INF, INF, 200},
  //   { INF,  INF, 120, INF, INF,   0,  40, INF, 100, INF},
  //   { INF,  INF, INF, 130, INF,  40,   0, INF, INF, 100},
  //   { 200,  INF, INF, INF, INF, INF, INF,   0, 320, INF},
  //   { INF,  INF, INF, INF, INF, 100, INF, 320,   0, 160},
  //   { INF,  INF, INF, INF, 200, INF, 100, INF, 160,   0}
  // }; 
  
  public:
  TourGuide(){
    init_road();
		cout << "|----------------------------Campus navigation system---------------------------|" << endl;
    cout << "|                                                                               |" << endl;
    cout << "|  Welcome to the campus navigation system, here provides query and navigation  |" << endl;
    cout << "|services for the following places:                                             |" << endl;
    cout << "|                                                                               |" << endl;
    cout << "|  T6栋, 3食堂, T5栋, 4食堂, T4栋, T3栋, H栋, T2栋, 1食堂, J栋, K栋, G栋, A栋,  |" << endl;
    cout << "|L栋, B栋.                                                                      |" << endl;
    cout << "|                                                                               |" << endl;
    cout << "|  Note: The actual coordinates are about 40 times of the map coordinates.      |" << endl;
    cout << "|places' information are displayed according to the map coordinates; but when   |" << endl;
    cout << "|planning the path, the path information is given according to the actual length|" << endl;
    cout << "|-------------------------------------------------------------------------------|" << endl;
	}

  ~TourGuide(){ //析构
		cout << "|--------------------------Welcome to use it again, bye-------------------------|" << endl;

	}

  void init_road(){
    int index1, index2;
    
    
    for(int i = 0; i < VexNum; i++){
      road[i][i] = 0;
      for(int j = i+1; j < VexNum; j++){
        road[i][j] = INF;
        road[j][i] = INF;
      }
    }
    for(int i = 0; i < EdgNum; i++){
      index1 = findVex(road_list[i].index1);
      index2 = findVex(road_list[i].index2);
      float delta_x = place[index2].location[0] - place[index1].location[0];//后地点相对于前者的水平距离
      float delta_y = place[index2].location[1] - place[index1].location[1];//后地点相对于前者的垂直距离
      road_list[i].distance = sqrt(delta_x*delta_x + delta_y*delta_y);
      if(delta_x >= 0){
        road_list[i].direction = asin(delta_y/road_list[i].distance);//存储弧度制角度
      }
      else{
        road_list[i].direction = Pi - asin(delta_y/road_list[i].distance);
      }
      // cout << road_list[i].direction*180/Pi << endl;

      road[index1][index2] = road_list[i].distance;
      road[index2][index1] = road_list[i].distance;
    }
    
  }

  //打印图
	void printGraph(){
    // for(int i = 0; i < VexNum; i++){
    //   cout << "\n place" << i + 1 << endl; 
	  //   cout << place[i].name << " ";
    //   cout << place[i].information << " "; 
    //   cout << "(" << place[i].location[0] << "," << place[i].location[1] << ")" << endl; 
    // }
    cout << "|                                                                               |" << endl;
    cout << "|Matrix Graph:" << endl;
    cout << "|";
		for(int i = 0; i < VexNum; i++){
      cout  << "\t" << place[i].name;
    }  
    cout << endl;

		for (int i = 0; i < VexNum; i++){
			cout << "|" << place[i].name;
			for(int j = 0; j < VexNum; j++){
        if(road[i][j] == INF)
          cout << "\t   ";
        else 
				  cout << "\t" << road[i][j];
          // cout << "\t" << path[i][j];
			}
			cout << endl;
		} 
  }

  void searchPlace(string data){
    int i = findVex(data);
      if(i == -1){
        cout << "|" << endl;
        cout << "|place you want to konw does not exist" << endl; 
      }
      else{
        cout << "|" << endl;
        cout << "|place you want to konw is" << endl; 
        cout << "|  " << place[i].name << ", ";
        cout << place[i].information << ", "; 
        cout << "坐标(" << place[i].location[0] << "," << place[i].location[1] << ")" << endl; 
      }

  }

  void Floyd(){
    int i, j, k;
    float temp;

    // 初始化
    for (i = 0; i < VexNum; i++)
    {
        for (j = 0; j < VexNum; j++)
        {
            dist[i][j] = road[i][j];    // "顶点i"到"顶点j"的路径长度。
            path[i][j] = i;                // "顶点i"到"顶点j"的最短路径是经过顶点j。
        }
    }
            
    // 计算最短路径
    for (k = 0; k < VexNum; k++)
    {
        for (i = 0; i < VexNum; i++)
        {
            for (j = 0; j < VexNum; j++)
            {
                // 如果经过下标为k顶点路径比原两点间路径更短，则更新dist[i][j]和path[i][j]
                temp = (dist[i][k]== INF || dist[k][j]== INF) ? INF : (dist[i][k] + dist[k][j]);
                // temp = (dist[i][k] + dist[k][j]);
                // cout << temp << endl;
                if (dist[i][j] > temp)
                {
                    // "i到j最短路径"对应的值设，为更小的一个(即经过k)
                    dist[i][j] = temp;
                    // "i到j最短路径"对应的路径，经过k
                    path[i][j] = path[k][j];
                    // path[j][i] = path[i][k];
                }
            }
        }
    }
  }

  // void A_star(string data){
  //   // 初始化
  //   for(int i = 0; i < VexNum; i++)
	// 	{
	// 		place[i].F = INF;
  //     place[i].G = INF;
  //     place[i].H = INF;
	// 		place[i].parentV = -1;
	// 		place[i].status = UNKNOWN;
	// 	}

  //   int open_list[VexNum], close_list[VexNum];
  //   int index = findVex(data);

  // }


  // 递归得到节点之间最短路径
  void getPath(int start, int end){
    if(path[start][end] == start){
      cout << place[start].name << "\t" << place[end].name <<  "\t";
    }
    else{
      getPath(start, path[start][end]);
      cout << place[end].name <<   "\t";
    }
  }

  //查找指定节点
	int findVex(string data){
		for(int i = 0; i < VexNum; i++)
			if(place[i].name == data)
				return i;
		return -1;
	}

  //查找最短路径节点
  int findMinDist_index(int index){
    float min_dist = INF;
    int min_index = -1;
    for(int i = 0; i < VexNum; i++){
      if(dist[index][i] < min_dist && dist[index][i] != 0 && place[i].status == UNKNOWN){
        min_dist = dist[index][i];
        min_index = i;
      }
    }
    return min_index;
  }

  void AskRoad_fromX(string data){
    float minDist = INF;
    int index = findVex(data);
    Floyd();
    for(int i = 0; i < VexNum; i++){
      place[i].status = UNKNOWN;
    }
    
    for(int i = findMinDist_index(index); i != -1; i = findMinDist_index(index)){
      cout << "|" << endl;
      cout << "|the shortest path from " << place[index].name << "to " << place[i].name << "is:" << endl;
      cout << "|  ";
      getPath(index, i);
      cout << endl;
      cout << "|the distance is " << dist[index][i]*FACTOR << "m" << endl;
      place[i].status = KNOWN;     
    }
  }


  
  //返回顶点index的第一个邻接顶点的索引，失败则返回-1
  int findFirstNeighbor(int index)
  {
      int i;

      if (index<0 || index >= VexNum)
          return -1;

      for (i = 0; i < VexNum; i++)
          if (road[index][i] != INF && index != i)
              return i;

      return -1;
  }

  //返回顶点index的下一个邻接顶点的索引，失败则返回-1
  int findNextNeighbor(int index, int neighborLast)
  {
      int i;

      if (index<0 || index >= VexNum || neighborLast<0 || neighborLast >= VexNum)
          return -1;

      for (i = neighborLast + 1; i < VexNum; i++)
          if (road[index][i] != INF && index != i)
              return i;

      return -1;
  }




  void savePath(int num){
    float length = 0;
    for(int i = 0; i < num - 1; i++){//计算路径长度
      length = length + road[path_temp[i]][path_temp[i+1]];
    }
    if(length < pathLength){//保存最短路径
      pathLength = length;
      // cout << pathLength*FACTOR << "m" << endl;
      for(int i = 0; i < num; i++){
        pathN[i] = path_temp[i];
      }
    }
  }

  void DFS(int start, int end, int itearte, int num){
    
    // cout << place[itearte].name <<  " ";
    if((place[start].visit_order + 1 < num && itearte != end) || (place[start].visit_order + 1 == num && itearte == end)){ //寻找的地点数小于需要节点数
      int temp = place[start].visit_order + 1;
      place[itearte].visit_order = temp;//存储访问顺序
      path_temp[temp - 1] = itearte;    //下标存入路径

      if(itearte == end){
        savePath(num);
        // cout << endl;
        return;
      }
    }
    else{
      return;
    }

    // 遍历该顶点的所有邻接顶点
    for (int i = findFirstNeighbor(itearte); i >= 0; i = findNextNeighbor(itearte, i)){
        if (place[i].status == UNKNOWN){
          place[itearte].status = KNOWN;
          DFS(itearte, end, i, num);
          place[itearte].status = UNKNOWN;
        }
            
    }
  }

  void AskRoad_fromXtoYviaN(string data1, string data2, int num){
    int index1, index2, iterate;
    index1 = findVex(data1);
    index2 = findVex(data2);

    if(num < 2 || num > VexNum){
      cout << "|" << endl;
      cout << "|sorry， number of places is not realistic" << endl;
      cout << "|" << endl;
    }
    else{
      for(int i = 0; i < VexNum; i++){
        place[i].status = UNKNOWN;
        place[i].visit_order = 0;
      }
        

      pathLength = INF;
      DFS(index1, index2, index1, num);
      // for (int i = 0; i < VexNum; i++){
      //     cout << place[i].visit_order << endl;
      // }
      if(pathN[0] == 0){
        cout << "|" << endl;
        cout << "|sorry， The selected path does not exist" << endl;
        cout << "|" << endl;
      }
      else{
        cout << "|" << endl;
        cout << "|From " << place[index1].name << " to " << place[index2].name << ", the shortest path through " << num << " points is:" << endl;
        cout << "|  ";
        for(int i = 0; i < num; i++){
        cout  << place[pathN[i]].name << "\t";
        }
        cout << endl;
        cout << "|" << endl;
        cout << "|The step by step detailed information is:" << endl;
        // cout << "|                                                                               |" << endl;
        for(int i = 0; i < num - 1; i++){
          print_roadInformation(place[pathN[i]].name, place[pathN[i+1]].name);
        }
      }
    }
      
  }

  void print_roadInformation(string data1, string data2){
    for(int i = 0; i < EdgNum; i++){
      if((road_list[i].index1 == data1 && road_list[i].index2 == data2)){
        cout << "|place " << data2 <<" is located in the " << road_list[i].direction*180/Pi <<"° direction of " << data1 << ", and " << road_list[i].distance*FACTOR << "m away from " << data1 << endl;
        cout << "|" << endl;
      }
      else if((road_list[i].index2 == data1 && road_list[i].index1 == data2)){
        float direction = -(180 - road_list[i].direction*180/Pi);
        cout << "|place " << data2 <<" is located in the " << direction <<"° direction of " << data1 << ", and " << road_list[i].distance*FACTOR << "m away from " << data1 << endl;
        cout << "|" << endl;
      }
      
    }
  }

};



#endif
