//
// Created by yueg on 9/17/15.
//

#ifndef SORTNEWS_ARTICLESPOOL_H
#define SORTNEWS_ARTICLESPOOL_H
#include <vector>
#include <map>
#include "Article.h"
#include "Term.h"

using namespace std;

class ArticleSpool
{
private:
    map<int, Article> articleMap;
    map<int, float> articleHeat;
    int createTime;
    int updateTime;
    int spoolSize;
    Term *termTable;
public:
    ArticleSpool(vector<Article> articleVec, Term *termTable);
    bool UpdateArticleSpool(vector<Article> newArticles);
    bool DeleteLeastScoreArticle(int n);
    void RemoveDumplicatedArticle(vector<Article> &articles);
    map<string, int>  GetTermsFromMultiArticle(vector<Article> articles) const;
    void UpdateTermTable(map<string, int> termMap, int flushTime);
    vector<Article> GetArticleOfMaxHeat(int size);
};


#endif //SORTNEWS_ARTICLESPOOL_H
