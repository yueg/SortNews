//
// Created by yueg on 9/17/15.
//
#include <iostream>
#include "ArticleSpool.h"
#include "Article.h"
#include "HeapUtil.h"
using namespace std;

ArticleSpool::ArticleSpool(vector<Article> articleVec, Term *termTable)
{
    this->termTable = termTable;
    vector<Article>::iterator iter;
    map<string, int> termMap = this->GetTermsFromMultiArticle(articleVec);
    this->UpdateTermTable(termMap, (int)time(0));
    for(iter = articleVec.begin(); iter != articleVec.end(); iter++)
    {
        int id = iter->GetArticleId();
        this->articleMap.insert(make_pair(id, *iter));
        float heat = iter->ComputArticleHeat(termTable);
        iter->SetArticleHeat(heat);
        this->articleHeat.insert(make_pair(id, heat));
    }
    this->createTime = (int)time(0);
    this->updateTime = this->createTime;
    this->spoolSize = 2000;
}

bool ArticleSpool::UpdateArticleSpool(vector<Article> newArticles)
{
    this->RemoveDumplicatedArticle(newArticles);
    map<string, int> termMap = this->GetTermsFromMultiArticle(newArticles);
    this->UpdateTermTable(termMap, (int)time(0));
    int currentSize = (int)this->articleMap.size();
    int newArticleSize = (int)newArticles.size();
    int deleteSize = newArticleSize < (this->spoolSize - currentSize) ? newArticleSize : (this->spoolSize - currentSize);
    this->DeleteLeastScoreArticle(deleteSize);
    vector<Article>::iterator iter;
    for(iter = newArticles.begin(); iter != newArticles.end(); iter++)
    {
        float articleHeap = iter->ComputArticleHeat(this->termTable);
        iter->SetArticleHeat(articleHeap);
        this->articleMap.insert(make_pair(iter->GetArticleId(), *iter));
        iter->SetArticleHeat(articleHeap);
        this->articleHeat.insert(make_pair(iter->GetArticleId(), articleHeap));
    }
}

bool ArticleSpool::DeleteLeastScoreArticle(int n)
{
    HeapUtil *deleteArticleHeap = new HeapUtil(this->articleHeat, n, false);
    int *deleteArticleTable = deleteArticleHeap->GetHeap();
    int heapSize = deleteArticleHeap->GetHeapSize();
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

void ArticleSpool::RemoveDumplicatedArticle(vector<Article> &articles)
{
    map<int, Article>::iterator iterMap;
    for(int i = 0; i < articles.size(); i++)
    {
        iterMap = this->articleMap.find(articles[i].GetArticleId());
        if(iterMap != this->articleMap.end())
        {
            articles.erase(articles.begin() + i);
            i--;
        }
    }
}

map<string, int> ArticleSpool::GetTermsFromMultiArticle(vector<Article> articles) const
{
    map<string, int> termMap;
    for(vector<Article>::iterator iter = articles.begin(); iter != articles.end(); iter++)
    {
        map<string, int> temp = iter->GetTermMap();
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

void ArticleSpool::UpdateTermTable(map<string, int> termMap, int flushTime)
{
    this->termTable->Update(termMap, flushTime);
}

vector<Article> ArticleSpool::GetArticleOfMaxHeat(int size)
{
    HeapUtil *dispalyArticleHeap = new HeapUtil(this->articleHeat, size, true);
    int *articleTable = dispalyArticleHeap->GetHeap();
    int heapSize = dispalyArticleHeap->GetHeapSize();
    vector<Article> ret;
    for(int i = 0; i < heapSize; i++)
    {
        ret.push_back(this->articleMap[articleTable[i]]);
    }
    return ret;
}