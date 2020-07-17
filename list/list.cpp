#include <iostream>  
#include "list.h"

using namespace std;
 


int main()
{
	int N;
	float a[] = {1, 2, 3, 4};
	// ArrayList<int> list1;
	ArrayList<float> list2(4, a);
	LinkedList<float> list3(4, a);
	cout << "inital list by array" << endl;
	list2.print();

	cout << "\n" << endl;
	cout << "inital list by link" << endl;
	list3.print();


	cout << "\n" << endl;
	list2.insert(3, 9.8);
	// list2.insert(2, 9.11);
	cout << "insert arraylist at 3rd index" << endl;
	list2.print();

	cout << "\n" << endl;
	list2.remove(1);
	cout << "delete arraylist at 1st index" << endl;
	list2.print();

	cout << "\n" << endl;
	list2.reverse();
	cout << "reverse arraylist" << endl;
	list2.print();

	cout << "\n" << endl;
	cout << "arraylist value at 3rd index is: " << list2.find(3) << endl;

	cout << "\n" << endl;
	list3.insert(3, 8.2);
	cout << "insert linkedlist at 3rd index" << endl;
	list3.print();

	cout << "\n" << endl;
	list3.remove(2);
	cout << "delete linkedlist at 2nd index" << endl;
	list3.print();

	cout << "\n" << endl;
	list3.reverse();
	cout << "reverse linkedlist" << endl;
	list3.print();

	cout << "\n" << endl;
	cout << "linkedlist value at 4th index is: " << list3.find(4) << endl;
	return 0;
}
