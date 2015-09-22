//
// Created by yueg on 9/17/15.
//
#include <iostream>
#include "article_spool.h"
#include "article.h"
#include "heap_util.h"
using namespace std;

#define MAXSIZE 1000

ArticleSpool::ArticleSpool() {
    this->articleMap.clear();
    this->articleHeat.clear();
    this->createTime = (int)time(0);
    this->updateTime = this->createTime;
    this->spoolMax = 1000;
    this->spoolSize = 0;
    this->heapUtil->SetHeapMaxSize(this->spoolMax);
}


void ArticleSpool::AddArticleToSpool(const Article *article) {
    if(this->spoolSize == 0) {
        this->heapUtil = new HeapUtil(MAXSIZE);
    }
    __int64_t articleId = article->GetArticleId();
    float articleHeat = article->GetArticleHeat();
    __int64_t replaceId = this->heapUtil->InsertIntoHeap(article, true);
    if (replaceId == -2) {
        this->articleMap.insert(make_pair(articleId, article));
        this->articleHeat.insert(make_pair(articleId, articleHeat));
    }
    else if (replaceId != -1) {
        this->articleMap.erase(replaceId);
        this->articleMap.insert(make_pair(article->GetArticleId(), article));
        this->articleHeat.erase(replaceId);
        this->articleHeat.insert(make_pair(articleId, articleHeat));
    }
    this->spoolSize = this->heapUtil->GetHeapSize();
}

vector<Article> ArticleSpool::GetArticleOfMaxHeat(int size)
{
    HeapUtil *dispalyArticleHeap = new HeapUtil(this->articleHeat, size, true);
    __int64_t *articleTable = dispalyArticleHeap->GetHeap();
    int heapSize = dispalyArticleHeap->GetHeapSize();
    vector<Article> ret;
    for(int i = 0; i < heapSize; i++)
    {
        ret.push_back(this->articleMap[articleTable[i]]);
    }
    return ret;
}





ArticleSpool::ArticleSpool(vector<Article> articleVec, Term *termTable)
{
    this->termTable = termTable;
    vector<Article>::iterator iter;
    map<string, int> *termMap = new map<string, int>;
    this->GetTermsFromMultiArticle(termMap, articleVec);
    this->UpdateTermTable(*termMap, (int)time(0));
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
    this->spoolSize = (int)this->articleMap.size();
    this->spoolMax = 1000;
}

void ArticleSpool::UpdateArticleSpool(vector<Article> newArticles)
{
    this->RemoveDumplicatedArticle(newArticles);
    map<string, int> *termMap = new map<string, int>;
    this->GetTermsFromMultiArticle(termMap, newArticles);
    this->UpdateTermTable(*termMap, (int)time(0));
    int currentSize = (int)this->articleMap.size();
    int newArticleSize = (int)newArticles.size();
    int deleteSize = newArticleSize < (this->spoolMax - currentSize) ? newArticleSize : (this->spoolMax - currentSize);
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
    __int64_t *deleteArticleTable = deleteArticleHeap->GetHeap();
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

void ArticleSpool::GetTermsFromMultiArticle(map<string, int> *termMap,vector<Article> articles) const
{
    for(vector<Article>::const_iterator iter = articles.begin(); iter != articles.end(); iter++)
    {
        map<string, int> temp = iter->GetTermMap();
        for(map<string, int>::iterator iterMap = temp.begin(); iterMap != temp.end(); iterMap++)
        {
            map<string, int>::iterator iterFind = termMap->find(iterMap->first);
            if(iterFind == termMap->end())
            {
                termMap->insert(make_pair(iterMap->first, iterMap->second));
            }
            else
            {
                iterFind->second += iterMap->second;
            }
        }
    }
}

void ArticleSpool::UpdateTermTable(map<string, int> termMap, int flushTime)
{
    this->termTable->Update(termMap, flushTime);
}

