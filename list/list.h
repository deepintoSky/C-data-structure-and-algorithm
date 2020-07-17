#ifndef LIST_H
#define LIST_H

#include <iostream>  

using namespace std;
template <typename T>

class ArrayList{
		
	int SIZE=100, MAX_INDEX;
	T* list;
		
	public:
		ArrayList() : MAX_INDEX(0) {list = new T[SIZE]; }//初始化数组用于存储列表，列表长度为0
		ArrayList(int size, T data[]) : MAX_INDEX(size) {//输入数组初始化列表
			list = new T[SIZE];
			for(int i = 0; i < size; i++){
				list[i] = data[i];
			}
		}

		// void init(int size, T data[]){
		// 	for(int i = 0; i < size; i++){
		// 		list[i] = data[i];
		// 	}
		// 	MAX_INDEX = size;
		// }

		~ArrayList(){ delete[] list; cout << "~list" << endl; }

		void print(){
			for(int i =  0; i < MAX_INDEX; i++){
				cout << list[i] << " " ;
			}
			cout << endl;
		}
		

		void insert(int index, const T& data);
		void replace(int index, const T& data){ list[index-1] = data; }
		void remove(int index);
		T find(int index){return list[index-1]; }
		void clear(){ 
			list[MAX_INDEX] = {};
			MAX_INDEX = 0;
			}


		void reverse();
		
};

	template <typename T>
	void ArrayList<T>::insert(int index, const T& data){//index处插入，后面元素全部后移
		for(int i = MAX_INDEX; i >= index; i--){
			list[i] =  list[i-1];
		}
		list[index-1] = data;
		MAX_INDEX++;
	}

	template <typename T>
	void ArrayList<T>::remove(int index){////index处删除，后面元素全部前移
		for(int i = index; i < MAX_INDEX; i++){
			list[i-1] =  list[i];
		}
		MAX_INDEX--;
	}

	template <typename T>
	void ArrayList<T>::reverse(){//列表反向
		for(int i = 0; i < MAX_INDEX / 2; i++){
			T temp = list[i];
			list[i] = list[MAX_INDEX - i - 1];
			list[MAX_INDEX - i - 1] =  temp;
		}
	}


template <typename T>
struct Node
{
    T data;              //存储数据
    Node<T> *next;       //存储下一个节点的地址
};


template <typename T>

class LinkedList{
	
	int MAX_INDEX;
	Node<T>* list;
		
	public:
		LinkedList() : MAX_INDEX(0) {//初始化空列表，第一个元素指向NULL
			list = new Node<T>;
			list->next = NULL; 
		}

		LinkedList(int size, T data[]) : MAX_INDEX(size) {//从第二个节点开始存储列表
			list = new Node<T>;
			Node<T> *list_now = list;
			for (int i = 0; i < size; i++)
			{
				Node<T> *list_next = new Node<T>;
				list_next->data = data[i];
				list_now->next = list_next;
				list_now = list_next;//迭代节点指针
			}
			list_now->next = NULL;
		}

		~LinkedList(){
			while (list != NULL){
				Node<T>* q = list;
				list = list->next;
				delete q;//当前节点指向下一节点后删除该节点
			}
			MAX_INDEX = 0;
			cout << "~list" << endl;
		}

		void print()
		{
			Node<T> *p = list->next;
			while (p != NULL)
			{
				cout << p->data << " ";
				p = p->next;
			}
			cout << endl;
		}

		void insert(int index, const T& data)
		{
			Node<T> *p = list;
			int count = 0;
			while (p != NULL && count<index - 1)//移动到插入节点上一节点
			{
				p = p->next;
				count++;
			}
			Node<T> *list_next = new Node<T>;
			list_next->data = data;
			list_next->next = p->next;//原下一节点由插入节点接管
			p->next = list_next;//上一节点指向当前插入节点
			MAX_INDEX++;
		}

		void remove(int index)
		{
			Node<T> *p = list;
			int count = 0;
			while (p != NULL && count<index - 1)
			{
				p = p->next;
				count++;
			}
			Node<T> *list_next = p->next;
			p->next = list_next->next;//下一节点指向下下节点
			MAX_INDEX--;
		}

		T find(int index){
			Node<T> *p = list;
			int count = 0;
			while (p != NULL && count<index)//移动到指定节点
			{
				p = p->next;
				count++;
			}
			return p->data;
		}

		void reverse(){
			if (list->next == NULL || list->next->next == NULL) //链表为空或者仅1个数直接返回
				return;
			Node<T> *list_pre = list->next;
			Node<T> *list_cur = list_pre->next;
			Node<T> *list_next = list_cur->next;
			while (list_next != NULL)
			{
				list_cur->next = list_pre;
				list_pre = list_cur;
				list_cur = list_next;
				list_next = list_next->next;
			}
			list_cur->next = list_pre;
			list->next->next = NULL;//原首节点成为末节点，指向NULL
			list->next = list_cur;//链表头指向当前首节点（原末节点）
		}

};


#endif
