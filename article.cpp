//
// Created by yueg on 9/17/15.
//

#include "article.h"
#include <string>
#include <iterator>
#include "./extractTerms/countWord.h"

#define TERMSPATH "/home/yueg/innotree/SortNews/data/business.seg"

using namespace std;

Article::Article(int article_time, const string &title, const string &content, const string &url, const TermSpool *termSpool) {
  article_time_ = article_time;
  title_ = title;
  content_ = content;
  url_ = url;
  map<string, int> termMap;
  this->GetTermMap(termMap);
  this->ComputArticleHeat((TermSpool *)termSpool);
}

void Article::ComputArticleHeat(TermSpool *termSpool) {
  map<string, int> termMap = getTermsMapFromStr(TERMSPATH, title_ + title_ + title_ + content_);
  termSpool->UpdateTermCount(termMap, article_time_);
  float articleHeat = 0;
  for (map<string, int>::iterator iter = termMap.begin(); iter != termMap.end(); iter++) {
    Term *term = termSpool->GetTermByWord(iter->first);
    articleHeat += iter->second * term->GetTermHeat();
  }
  article_heat_ = articleHeat;
}

void Article::GetTermMap(map<string, int> &ret) const {
  ret = getTermsMapFromStr(TERMSPATH, title_ + content_);
}

float Article::GetArticleHeat() const {return article_heat_; }

void Article::GetArticleTitle(string &title) const {title = title_; }

void Article::GetArticleContent(string &content) const {content = content_; }

void Article::SetArticleHeat(float heat) {article_heat_ = heat; }
