//
// Created by yueg on 9/18/15.
//

#include "HeapUtil.h"
using namespace std;

HeapUtil::HeapUtil(map<int, float> m, int heapSize, bool type)
{
    this->dataMap = m;
    this->BuildHeap(heapSize, type);
}

void HeapUtil::BuildHeap(int n, bool type)
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
        this->AdjustHeap(j, this->heapSize, type);
    }
    for(; iter != dataMap.end(); iter++)
    {
        if(type && this->heapSize > 0 && iter->second > dataMap[this->heap[0]])
        {
            this->heap[0] = iter->first;
            this->AdjustHeap(0, this->heapSize, type);
        }
        else if(!type && this->heapSize > 0 && iter->second < dataMap[this->heap[0]])
        {
            this->heap[0] = iter->first;
            this->AdjustHeap(0, this->heapSize, type);
        }
    }
}

void HeapUtil::AdjustHeap(int i, int size, bool type)
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
            AdjustHeap(max, size, type);
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
            AdjustHeap(max, size, type);
        }
    }
}

int * HeapUtil::GetHeap() const {return this->heap;}

int HeapUtil::GetHeapSize() const {return this->heapSize; }