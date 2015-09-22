//
// Created by yueg on 9/17/15.
//

#ifndef SORTNEWS_ARTICLE_H
#define SORTNEWS_ARTICLE_H
#include <string>
#include <map>
#include "term_spool.h"

class Article
{
private:
    int article_time;
    float article_heat;
    std::string title;
    std::string content;
    std::string url;

public:
    Article();
    Article(int article_time, float article_heat, std::string title, std::string content, std::string url);
    Article(int article_time, std::string title, std::string content, std::string url, TermSpool *t);
    std::map<std::string, int> GetTermMap() const;
    void ComputArticleHeat(TermSpool *t);
    std::string GetArticleTitle() const;
    std::string GetArticleContent() const;
    float GetArticleHeat() const;
    void SetArticleHeat(float heat);
};


#endif //SORTNEWS_ARTICLE_H
