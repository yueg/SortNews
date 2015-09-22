//
// Created by yueg on 9/18/15.
//

#include "heap_util.h"
using namespace std;

HeapUtil::HeapUtil(map<__int64_t, float> m, int heapSize, bool type) {
  this->dataMap = m;
  this->BuildHeap(heapSize, type);
}

HeapUtil::HeapUtil(int size) {
  this->heapSize = 0;
  this->heap = new __int64_t(size);
  this->heapMax = size;
}

__int64_t HeapUtil::InsertIntoHeap(const Article *article, bool type) {
  __int64_t ret = -1;
  float articleHeat = article->GetArticleHeat();
  __int64_t articleId = article->GetArticleId();
  if (this->heapSize == 0) {
    ret = -2;
    this->heap[0] = articleId;
    this->heapSize = 1;
    this->dataMap.insert(make_pair(articleId, articleHeat));
  }
  else if (this->heapSize == this->heapMax && this->dataMap[this->heap[0]] < articleHeat) {
    ret = this->heap[0];
    this->dataMap.erase(this->heap[0]);
    this->heap[0] = articleId;
    this->AdjustHeap(0, this->heapSize, type);
    this->dataMap.insert(make_pair(articleId, articleHeat));
  }
  else if (this->heapSize < this->heapMax) {
    ret = -2;
    this->heapSize += 1;
    this->heap[this->heapSize] = articleId;
    for (int i = this->heapSize / 2; i >= 0; i = (i - 1) / 2) {
      this->AdjustHeap(i, this->heapSize, type);
    }
    this->dataMap.insert(make_pair(articleId, articleHeat));
  }
  return ret;
}

void HeapUtil::BuildHeap(int n, bool type) {
    this->heap = new __int64_t(n);
    map<__int64_t, float>::iterator iter;
    int i;
    for(i = 0, iter = this->dataMap.begin(); i < n && iter != this->dataMap.end(); i++, iter++) {
        this->heap[i] = iter->first;
    }
    this->heapSize = i;
    for(int j = this->heapSize / 2; j >= 0; j--) {
        this->AdjustHeap(j, this->heapSize, type);
    }
    for(; iter != dataMap.end(); iter++) {
        if(type && this->heapSize > 0 && iter->second > dataMap[this->heap[0]]) {
            this->heap[0] = iter->first;
            this->AdjustHeap(0, this->heapSize, type);
        }
        else if(!type && this->heapSize > 0 && iter->second < dataMap[this->heap[0]]) {
            this->heap[0] = iter->first;
            this->AdjustHeap(0, this->heapSize, type);
        }
    }
}

void HeapUtil::AdjustHeap(int i, int size, bool type) {
    int lchild = 2 * i;
    int rchild = 2 * i + 1;
    int max = i;
    if(i <= size / 2 && type) {
        if(lchild < size && dataMap[this->heap[lchild]] < dataMap[this->heap[max]]) {
            max = lchild;
        }
        if(rchild < size && dataMap[this->heap[rchild]] < dataMap[this->heap[max]]) {
            max = rchild;
        }
        if(max != i) {
            swap(this->heap[i], this->heap[max]);
            AdjustHeap(max, size, type);
        }
    }
    else if(i <= size / 2 && !type) {
        if(lchild < size && dataMap[this->heap[lchild]] > dataMap[this->heap[max]]) {
            max = lchild;
        }
        if(rchild < size && dataMap[this->heap[rchild]] > dataMap[this->heap[max]]) {
            max = rchild;
        }
        if(max != i) {
            swap(this->heap[i], this->heap[max]);
            AdjustHeap(max, size, type);
        }
    }
}

__int64_t *HeapUtil::GetHeap() const {return this->heap;}

int HeapUtil::GetHeapSize() const {return this->heapSize; }

void HeapUtil::SetHeapMaxSize(int max) {this->heapSize = 0; this->heap = new __int64_t(max); this->heapMax = max; }