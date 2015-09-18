//
// Created by yueg on 9/17/15.
//

#include "article.h"
#include <string>
#include <iterator>
#include "./extractTerms/countWord.h"
#define TERMSPATH "/home/yueg/innotree/SortNews/data/business.seg"

using namespace std;

article::article(){ }


article::article(int article_id, int article_time, float article_heat, string title, string content, string url)
{
    this->article_id = article_id;
    this->article_time = article_time;
    this->article_heat = article_heat;
    this->title = title;
    this->content = content;
    this->url = url;
}

article::article(int article_id, int article_time, string title, string content, string url, term *t)
{
    this->article_id = article_id;
    this->article_time = article_time;
    this->title = title;
    this->content = content;
    this->url = url;
    map<string, int> termMap = this->getTermMap();
    this->article_heat = this->computArticleHeat(t);
}

float article::computArticleHeat(term *t)
{
    map<string, int> termMap = getTermsMapFromStr(TERMSPATH, this->title + this->content);
    map<string, int>::iterator iter;
    map<string, float> termHeat = t->getTermHeat();
    float ret = 0;
    for(iter = termMap.begin(); iter != termMap.end(); iter++)
    {
        ret += termHeat[iter->first] * (float)iter->second;
    }
    return ret;
}

article * article::getArticle()
{
    return this;
}

map<string, int> article::getTermMap()
{
    return getTermsMapFromStr(TERMSPATH, this->title + this->content);
}

int article::getArticleId() {return this->article_id; }

float article::getArticleHeat() {return this->article_heat; }

string article::getArticleTitle() {return this->title; }

string article::getArticleContent() {return this->content; }

void article::setArticleHeat(float heat) {this->article_heat = heat; }
