//
// Created by yueg on 9/18/15.
//

#include "heapUtil.h"

heapUtil::heapUtil(map<int, float> m, int heapSize, bool type)
{
    this->dataMap = m;
    this->buildHeap(heapSize, type);
}

void heapUtil::buildHeap(int n, bool type)
{
    this->heap = new int(n);
    map<int, float>::iterator iter;
    int i;
    for(i = 0, iter = this->dataMap.begin(); i < n && iter != this->dataMap.end(); i++, iter++)
    {
        this->heap[i] = iter->first;
    }
    this->heapSize = i;
    for(int j = this->heapSize / 2; j >= 1; j--)
    {
        this->adjustHeap(j, this->heapSize, type);
    }
    for(; iter != dataMap.end(); iter++)
    {
        if(type && this->heapSize > 0 && iter->second > dataMap[this->heap[0]])
        {
            this->heap[0] = iter->first;
            this->adjustHeap(0, this->heapSize, type);
        }
        else if(!type && this->heapSize > 0 && iter->second < dataMap[this->heap[0]])
        {
            this->heap[0] = iter->first;
            this->adjustHeap(0, this->heapSize, type);
        }
    }
}

void heapUtil::adjustHeap(int i, int size, bool type)
{
    int lchild = 2 * i;
    int rchild = 2 * i + 1;
    int max = i;
    if(i <= size / 2 && type)
    {
        if(lchild < size && dataMap[this->heap[lchild]] < dataMap[this->heap[max]])
        {
            max = lchild;
        }
        if(rchild < size && dataMap[this->heap[rchild]] < dataMap[this->heap[max]])
        {
            max = rchild;
        }
        if(max != i)
        {
            swap(this->heap[i], this->heap[max]);
            adjustHeap(max, size, type);
        }
    }
    else if(i <= size / 2 && !type)
    {
        if(lchild < size && dataMap[this->heap[lchild]] > dataMap[this->heap[max]])
        {
            max = lchild;
        }
        if(rchild < size && dataMap[this->heap[rchild]] > dataMap[this->heap[max]])
        {
            max = rchild;
        }
        if(max != i)
        {
            swap(this->heap[i], this->heap[max]);
            adjustHeap(max, size, type);
        }
    }
}

int * heapUtil::getHeap(){return this->heap;}

int heapUtil::getHeapSize() {return this->heapSize; }