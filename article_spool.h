//
// Created by yueg on 9/17/15.
//

#ifndef SORTNEWS_ARTICLESPOOL_H
#define SORTNEWS_ARTICLESPOOL_H
#include <vector>
#include <map>
#include "article.h"
#include "term.h"
#include "heap_util.h"

using namespace std;

class ArticleSpool
{
private:
    map<int, Article> articleMap;
    map<__int64_t, float> articleHeat;
    int createTime;
    int updateTime;
    int spoolMax;
    int spoolSize;
    HeapUtil *heapUtil;
    Term *termTable;
public:
    ArticleSpool();
    void AddArticleToSpool(const Article *article);
    vector<Article> GetArticleOfMaxHeat(int size);

    ArticleSpool(vector<Article> articleVec, Term *termTable);
    void UpdateArticleSpool(vector<Article> newArticles);
    bool DeleteLeastScoreArticle(int n);
    void RemoveDumplicatedArticle(vector<Article> &articles);
    void GetTermsFromMultiArticle(map<string, int> *termMap,vector<Article> articles) const;
    void UpdateTermTable(map<string, int> termMap, int flushTime);

};


#endif //SORTNEWS_ARTICLESPOOL_H
