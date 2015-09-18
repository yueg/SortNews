//
// Created by yueg on 9/18/15.
//

#ifndef SORTNEWS_HEAPUTIL_H
#define SORTNEWS_HEAPUTIL_H
#include <map>

using namespace std;

class heapUtil
{
private:
    map<int, float> dataMap;
    int *heap;
    int heapSize;
public:
    heapUtil(map<int, float> m, int heapSize);
    void buildHeap(int n);
    void adjustHeap(int i, int size);
    int *getHeap();
    int getHeapSize();
};


#endif //SORTNEWS_HEAPUTIL_H
