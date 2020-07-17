#include <iostream>  
#include "sort.h"

using namespace std;
 


int main()
{
	int a[] = {1, 3, 2, 4, 9, 21, 13, 12, 4, 6, 15, 7, 1, 14, 17};
	int b[] = {1, 3, 2, 4, 9, 21, 13, 12, 4, 6, 15, 7, 1, 14, 17};
	merge_sort(a, getArrayLen(a));
	cout << "\n" << "merge_sort result:" << endl;
	for (int i = 0; i < getArrayLen(a); i++)
		cout << a[i] << endl;

	
	QuickSort(b, 0, getArrayLen(b) - 1);
	cout << "\n" << "quick_sort result:" << endl;
	for (int i = 0; i < getArrayLen(b); i++)
		cout << b[i] << endl;

	return 0;
}
