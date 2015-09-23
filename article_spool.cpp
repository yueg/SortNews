//
// Created by yueg on 9/17/15.
//
#include "article_spool.h"
#include "article.h"
#include "heap_util.h"
#include "extractTerms/countWord.h"

using namespace std;

#define MAXSIZE 1000
#define TERMSPATH "/home/yueg/innotree/SortNews/data/business.seg"

ArticleSpool::ArticleSpool() {
  createTime_ = (int)time(0);
  updateTime_ = createTime_;
  spoolMax_ = MAXSIZE;
  spoolSize_ = 0;
  heapUtil_ = new HeapUtil(MAXSIZE);
  termTable_ = new TermSpool(TERMSPATH);
}

ArticleSpool::~ArticleSpool() {
  delete termTable_;
  delete heapUtil_;
}

void ArticleSpool::Push(const string &url, int pubtime, const string &title, const string &content) {
  updateTime_ = (int)time(0);
  Article *article = new Article(pubtime, title, content, url, termTable_);
  heapUtil_->InsertIntoHeap(article, true);
}

void ArticleSpool::GetArticleOfMaxHeat(int size, vector<Article> *out) const {
  HeapUtil *outHeap = new HeapUtil(size);
  vector<Article *> outArticleAddr;
  vector<Article *> articleHeap;
  heapUtil_->GetHeap(articleHeap);
  if (articleHeap.size() < size) {
    outArticleAddr = articleHeap;
  }
  else {
    outHeap->BuildHeap(articleHeap, size, true);
    outHeap->GetHeap(outArticleAddr);
  }
  out->clear();
  for (int i = 0; i < outArticleAddr.size(); i++) {
    out->push_back(*(outArticleAddr[i]));
  }
  delete outHeap;
}


void ArticleSpool::UpdateAllArticle() {
  termTable_->DeleteTimeOutTermInSpool();
  vector<Article *> articleVec;
  heapUtil_->GetHeap(articleVec);
  for (int i = 0; i < articleVec.size(); i++) {
    articleVec[i]->ComputArticleHeat(termTable_);
  }
  heapUtil_->BuildHeap(articleVec, MAXSIZE, true);
}