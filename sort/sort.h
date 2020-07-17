#ifndef SORT_H
#define SORT_H

#include <iostream>  
#include <vector>
using namespace std;

template <class T>
int getArrayLen(T& array){
  return (sizeof(array) / sizeof(array[0]));
}


template<typename T> 
void merge_sort(T input[], int length) {
    T *a = input;
    T *b = new T[length];
    for (int devide = 1; devide < length; devide += devide) {
        for (int start = 0; start < length; start += devide + devide) {
            int low = start, mid = min(start + devide, length), high = min(start + devide + devide, length);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        T *temp = a;
        a = b;
        b = temp;
    }
    if (a != input) {
        for (int i = 0; i < length; i++)
            b[i] = a[i];
        b = a;
    }
    delete[] b;
}


template<typename T>
int Paritition(T input[], int low, int high) {
   T pivot = input[low];
   while (low < high) {
     while (low < high && input[high] >= pivot) {
       --high;
     }
     input[low] = input[high];
     while (low < high && input[low] <= pivot) {
       ++low;
     }
     input[high] = input[low];
   }
   input[low] = pivot;
   return low;
 }

template<typename T>
 void QuickSort(T input[], int low, int high) //快排函数
 {
   if (low < high) {
     int pivot = Paritition(input, low, high);
     QuickSort(input, low, pivot - 1);
     QuickSort(input, pivot + 1, high);
   }
 }

#endif
