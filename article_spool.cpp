//
// Created by yueg on 9/17/15.
//
#include "article_spool.h"
#include <iostream>
#include "article.h"
#include "heap_util.h"
#include "extractTerms/countWord.h"

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
  Article *article = new Article(pubtime, title, content, url, this->termTable);
  map<string, int> termMap = getTermsMapFromStr(TERMSPATH, title + title + title + content);
  this->heapUtil->InsertIntoHeap(article, true);
}


void ArticleSpool::AddArticleToSpool(const Article *article) {
    if(this->spoolSize == 0) {
        this->heapUtil = new HeapUtil(MAXSIZE);
    }
    bool ret = this->heapUtil->InsertIntoHeap(article, true);

    this->spoolSize = this->heapUtil->GetHeapSize();
}

void ArticleSpool::GetArticleOfMaxHeat(int size, vector<Article> *out) const
{
    HeapUtil *outHeap = new HeapUtil(size);
    vector<Article *> outArticleAddr;
    vector<Article *> articleHeap;
    this->heapUtil->GetHeap(articleHeap);
    if (articleHeap.size() < size) {
      outArticleAddr = articleHeap;
    }
    else {
      outHeap->BuildHeap(articleHeap, size, true);
      int heapSize = outHeap->GetHeapSize();
      out->clear();
      outHeap->GetHeap(outArticleAddr);
    }
    for (int i = 0; i < outArticleAddr.size(); i++) {
      Article temp = *(outArticleAddr[i]);
      out->push_back(temp);
    }
    delete outHeap;
}


void ArticleSpool::UpdateTermTable(map<string, int> termMap, int flushTime) {
  this->termTable->UpdateTermCount(termMap, flushTime);
}

