//
// Created by yueg on 9/17/15.
//

#ifndef SORTNEWS_ARTICLESPOOL_H
#define SORTNEWS_ARTICLESPOOL_H
#include <vector>
#include <map>
#include "article.h"
#include "term.h"

using namespace std;

class articleSpool
{
private:
    map<int, article> articleMap;
    map<int, float> articleHeat;
    int createTime;
    int updateTime;
    int spoolSize;
    term *termTable;
public:
    articleSpool(vector<article> articleVec, term *termTable);
    bool updateArticleSpool(vector<article> newArticles);
    bool deleteLeastScoreArticle(int n);
    void removeDumplicatedArticle(vector<article> &articles);
};


#endif //SORTNEWS_ARTICLESPOOL_H
