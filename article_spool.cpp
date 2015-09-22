//
// Created by yueg on 9/17/15.
//
#include "article_spool.h"
#include <iostream>
#include "article.h"
#include "heap_util.h"
using namespace std;

#define MAXSIZE 1000
#define TERMSPATH "/home/yueg/innotree/SortNews/data/business.seg"

ArticleSpool::ArticleSpool() {
    this->createTime = (int)time(0);
    this->updateTime = this->createTime;
    this->spoolMax = MAXSIZE;
    this->spoolSize = 0;
    this->heapUtil = new HeapUtil(MAXSIZE);
    this->termTable = new TermSpool(TERMSPATH);
}

ArticleSpool::~ArticleSpool() {
    delete this->termTable;
    delete this->heapUtil;
}

void ArticleSpool::Push(const string &url, int pubtime, const string &title, const string &content) {
    this->updateTime = (int)time(0);
}


void ArticleSpool::AddArticleToSpool(const Article *article) {
    if(this->spoolSize == 0) {
        this->heapUtil = new HeapUtil(MAXSIZE);
    }
    bool ret = this->heapUtil->InsertIntoHeap(article, true);

    this->spoolSize = this->heapUtil->GetHeapSize();
}

void ArticleSpool::GetArticleOfMaxHeat(int size, vector<Article *> out) const
{
    HeapUtil *outHeap = new HeapUtil(size);
    outHeap->BuildHeap(this->heapUtil->GetHeap(), size, true);
    int heapSize = outHeap->GetHeapSize();
    out.clear();
    out = outHeap->GetHeap();
    delete outHeap;
}


void ArticleSpool::UpdateTermTable(map<string, int> termMap, int flushTime)
{

}

