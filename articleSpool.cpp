//
// Created by yueg on 9/17/15.
//

#include "articleSpool.h"
#include "article.h"
#include "heapUtil.h"
using namespace std;

articleSpool::articleSpool(vector<article> articleVec, term *termTable)
{
    vector<article>::iterator iter;
    for(iter = articleVec.begin(); iter != articleVec.end(); iter++)
    {
        int id = iter->getArticleId();
        this->articleMap.insert(make_pair(id, *iter));
        float heat = iter->computArticleHeat(termTable);
        iter->setArticleHeat(heat);
        this->articleHeat.insert(make_pair(id, heat));
    }
    this->termTable = termTable;
    this->createTime = (int)time(0);
    this->updateTime = this->createTime;
    this->spoolSize = 2000;
}

bool articleSpool::updateArticleSpool(vector<article> newArticles)
{
    this->removeDumplicatedArticle(newArticles);
    int currentSize = (int)this->articleMap.size();
    int newArticleSize = (int)newArticles.size();
    int deleteSize = newArticleSize < (this->spoolSize - currentSize) ? newArticleSize : (this->spoolSize - currentSize);
    this->deleteLeastScoreArticle(deleteSize);
}

bool articleSpool::deleteLeastScoreArticle(int n)
{
    heapUtil *deleteArticleHeap = new heapUtil(this->articleHeat, n);
    int *deleteArticleTable = deleteArticleHeap->getHeap();
    int heapSize = deleteArticleHeap->getHeapSize();
    if(n != heapSize)
    {
        return false;
    }
    for(int i = 0; i < heapSize; i++)
    {
        this->articleMap.erase(deleteArticleTable[i]);
        this->articleHeat.erase(deleteArticleTable[i]);
    }
    return true;
}

void articleSpool::removeDumplicatedArticle(vector<article> &articles)
{
    map<int, article>::iterator iterMap;
    for(int i = 0; i < articles.size(); i++)
    {
        iterMap = this->articleMap.find(articles[i].getArticleId());
        if(iterMap != this->articleMap.end())
        {
            articles.erase(articles.begin() + i);
            i--;
        }
    }
}