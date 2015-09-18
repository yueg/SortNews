//
// Created by yueg on 9/17/15.
//

#ifndef SORTNEWS_ARTICLE_H
#define SORTNEWS_ARTICLE_H
#include <string>
#include <map>
#include "term.h"
using namespace std;

class article
{
private:
    int article_id;
    int article_time;
    float article_heat;
    string title;
    string content;
    string url;

public:
    article();
    article(int article_id, int article_time, float article_heat, string title, string content, string url);
    article(int article_id, int article_time, string title, string content, string url, term *t);
    article *getArticle();
    map<string, int> getTermMap();
    int getArticleId();
    float computArticleHeat(term *t);
    string getArticleTitle();
    string getArticleContent();
    float getArticleHeat();
    void setArticleHeat(float heat);

};


#endif //SORTNEWS_ARTICLE_H
