//
// Created by yueg on 9/17/15.
//

#include "Article.h"
#include <string>
#include <iterator>
#include "./extractTerms/countWord.h"
#define TERMSPATH "/home/yueg/innotree/SortNews/data/business.seg"

using namespace std;

Article::Article(){ }


Article::Article(int article_id, int article_time, float article_heat, string title, string content, string url)
{
    this->article_id = article_id;
    this->article_time = article_time;
    this->article_heat = article_heat;
    this->title = title;
    this->content = content;
    this->url = url;
}

Article::Article(int article_id, int article_time, string title, string content, string url, Term *t)
{
    this->article_id = article_id;
    this->article_time = article_time;
    this->title = title;
    this->content = content;
    this->url = url;
    map<string, int> termMap = this->GetTermMap();
    this->article_heat = this->ComputArticleHeat(t);
}

float Article::ComputArticleHeat(Term *t)
{
    map<string, int> termMap = getTermsMapFromStr(TERMSPATH, this->title + this->content);
    map<string, int>::iterator iter;
    map<string, float> termHeat = t->GetTermHeat();
    float ret = 0;
    for(iter = termMap.begin(); iter != termMap.end(); iter++)
    {
        ret += termHeat[iter->first] * (float)iter->second;
    }
    return ret;
}

Article * Article::GetArticle()
{
    return this;
}

map<string, int> Article::GetTermMap() const
{
    return getTermsMapFromStr(TERMSPATH, this->title + this->content);
}

int Article::GetArticleId() const {return this->article_id; }

float Article::GetArticleHeat() const {return this->article_heat; }

string Article::GetArticleTitle() const {return this->title; }

string Article::GetArticleContent() const {return this->content; }

void Article::SetArticleHeat(float heat) {this->article_heat = heat; }
