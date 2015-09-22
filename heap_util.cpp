//
// Created by yueg on 9/18/15.
//

#include "heap_util.h"
using namespace std;



HeapUtil::HeapUtil(int size) {
  this->heapSize = 0;
  this->heap.reserve(size);
  this->heapMax = size;
}

bool HeapUtil::InsertIntoHeap(const Article *article, bool type) {
  bool ret = false;
  float articleHeat = article->GetArticleHeat();
  if (this->heapSize == 0) {
    ret = true;
    this->heap.push_back((Article *)article);
    this->heapSize = (int)this->heap.size();
  }
  else if (this->heapSize == this->heapMax && articleHeat > this->heap[0]->GetArticleHeat()) {
    ret = true;
    this->heap[0] = (Article *)article;
    this->AdjustHeap(0, this->heapSize, type);
  }
  else if (this->heapSize < this->heapMax) {
    ret = true;
    this->heapSize += 1;
    this->heap.push_back((Article *)article);
    for (int i = this->heapSize / 2; i >= 1; i = (i - 1) / 2) {
      this->AdjustHeap(i, this->heapSize, type);
    }
  }
  return ret;
}

void HeapUtil::BuildHeap(const vector<Article *> articleVec,int n, bool type) {
    this->heap.reserve(n);
    int i;
    vector<Article *>::const_iterator iter;
    for(i = 0, iter = articleVec.begin(); i < n && iter != articleVec.end(); i++, iter++) {
        this->heap.push_back(*iter);
    }
    this->heapSize = i;
    for(int j = this->heapSize / 2; j >= 1; j--) {
        this->AdjustHeap(j, this->heapSize, type);
    }
    for(; iter != articleVec.end(); iter++) {
        if(type && this->heapSize > 0 && (*iter)->GetArticleHeat() > this->heap[0]->GetArticleHeat()) {
            this->heap[0] = *iter;
            this->AdjustHeap(0, this->heapSize, type);
        }
        else if(!type && this->heapSize > 0 && (*iter)->GetArticleHeat() < this->heap[0]->GetArticleHeat()) {
            this->heap[0] = *iter;
            this->AdjustHeap(0, this->heapSize, type);
        }
    }
}

void HeapUtil::AdjustHeap(int i, int size, bool type) {
    int lchild = 2 * i;
    int rchild = 2 * i + 1;
    int max = i;
    if(i <= size / 2 && type) {
        if(lchild < size && this->heap[lchild]->GetArticleHeat() < this->heap[max]->GetArticleHeat()) {
            max = lchild;
        }
        if(rchild < size && this->heap[rchild]->GetArticleHeat() < this->heap[max]->GetArticleHeat()) {
            max = rchild;
        }
        if(max != i) {
            swap(this->heap[i], this->heap[max]);
            AdjustHeap(max, size, type);
        }
    }
    else if(i <= size / 2 && !type) {
        if(lchild < size && this->heap[lchild]->GetArticleHeat() > this->heap[max]->GetArticleHeat()) {
            max = lchild;
        }
        if(rchild < size && this->heap[rchild]->GetArticleHeat() > this->heap[max]->GetArticleHeat()) {
            max = rchild;
        }
        if(max != i) {
            swap(this->heap[i], this->heap[max]);
            AdjustHeap(max, size, type);
        }
    }
}

void HeapUtil::GetHeap(vector<Article *> &article) const { article = this->heap;}

int HeapUtil::GetHeapSize() const {return this->heapSize; }

void HeapUtil::SetHeapMaxSize(int max) {
  this->heapSize = 0;
  this->heap.reserve((unsigned long)max);
  this->heapMax = max;
}