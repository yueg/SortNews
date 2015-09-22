//
// Created by yueg on 9/17/15.
//

#include "article.h"
#include <string>
#include <iterator>
#include "./extractTerms/countWord.h"
#include "term_spool.h"

#define TERMSPATH "/home/yueg/innotree/SortNews/data/business.seg"

using namespace std;

Article::Article(){ }


Article::Article(int article_time, float article_heat, string title, string content, string url)
{
    this->article_time = article_time;
    this->article_heat = article_heat;
    this->title = title;
    this->content = content;
    this->url = url;
}

Article::Article(int article_time, string title, string content, string url, TermSpool *t)
{
    this->article_time = article_time;
    this->title = title;
    this->content = content;
    this->url = url;
    map<string, int> termMap = this->GetTermMap();
    this->ComputArticleHeat(t);
}

void Article::ComputArticleHeat(TermSpool *termSpool) {
    map<string, int> termMap = getTermsMapFromStr(TERMSPATH, this->title + this->title + this->title + this->content);
    float articleHeat = 0;
    for (map<string, int>::iterator iter = termMap.begin(); iter != termMap.end(); iter++) {
        Term *term = termSpool->GetTermByWord(iter->first);
        articleHeat += iter->second * term->GetTermHeat();
    }
}

map<string, int> Article::GetTermMap() const
{
    return getTermsMapFromStr(TERMSPATH, this->title + this->content);
}

float Article::GetArticleHeat() const {return this->article_heat; }

string Article::GetArticleTitle() const {return this->title; }

string Article::GetArticleContent() const {return this->content; }

void Article::SetArticleHeat(float heat) {this->article_heat = heat; }
