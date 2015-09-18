//
// Created by yueg on 9/17/15.
//
#include <iostream>
#include "articleSpool.h"
#include "article.h"
#include "heapUtil.h"
using namespace std;

articleSpool::articleSpool(vector<article> articleVec, term *termTable)
{
    this->termTable = termTable;
    vector<article>::iterator iter;
    map<string, int> termMap = this->getTermsFromMultiArticle(articleVec);
    this->updateTermTable(termMap, (int)time(0));
    for(iter = articleVec.begin(); iter != articleVec.end(); iter++)
    {
        int id = iter->getArticleId();
        this->articleMap.insert(make_pair(id, *iter));
        float heat = iter->computArticleHeat(termTable);
        iter->setArticleHeat(heat);
        this->articleHeat.insert(make_pair(id, heat));
    }
    this->createTime = (int)time(0);
    this->updateTime = this->createTime;
    this->spoolSize = 2000;
}

bool articleSpool::updateArticleSpool(vector<article> newArticles)
{
    this->removeDumplicatedArticle(newArticles);
    map<string, int> termMap = this->getTermsFromMultiArticle(newArticles);
    this->updateTermTable(termMap, (int)time(0));
    int currentSize = (int)this->articleMap.size();
    int newArticleSize = (int)newArticles.size();
    int deleteSize = newArticleSize < (this->spoolSize - currentSize) ? newArticleSize : (this->spoolSize - currentSize);
    this->deleteLeastScoreArticle(deleteSize);
    vector<article>::iterator iter;
    for(iter = newArticles.begin(); iter != newArticles.end(); iter++)
    {
        float articleHeap = iter->computArticleHeat(this->termTable);
        iter->setArticleHeat(articleHeap);
        this->articleMap.insert(make_pair(iter->getArticleId(), *iter));
        this->articleHeat.insert(make_pair(iter->getArticleId(), articleHeap));
    }
}

bool articleSpool::deleteLeastScoreArticle(int n)
{
    heapUtil *deleteArticleHeap = new heapUtil(this->articleHeat, n, false);
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

map<string, int> articleSpool::getTermsFromMultiArticle(vector<article> articles)
{
    map<string, int> termMap;
    for(vector<article>::iterator iter = articles.begin(); iter != articles.end(); iter++)
    {
        map<string, int> temp = iter->getTermMap();
        for(map<string, int>::iterator iterMap = temp.begin(); iterMap != temp.end(); iterMap++)
        {
            map<string, int>::iterator iterFind = termMap.find(iterMap->first);
            if(iterFind == termMap.end())
            {
                termMap[iterMap->first] = iterMap->second;
            }
            else
            {
                iterFind->second += iterMap->second;
            }
        }
    }
    return termMap;
}

void articleSpool::updateTermTable(map<string, int> termMap, int flushTime)
{
    this->termTable->update(termMap, flushTime);
}

vector<article> articleSpool::getArticleOfMaxHeat(int size)
{
    heapUtil *dispalyArticleHeap = new heapUtil(this->articleHeat, size, true);
    int *articleTable = dispalyArticleHeap->getHeap();
    int heapSize = dispalyArticleHeap->getHeapSize();
    vector<article> ret;
    for(int i = 0; i < heapSize; i++)
    {
        ret.push_back(this->articleMap[articleTable[i]]);
    }
    return ret;
}