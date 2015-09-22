//
// Created by yueg on 9/17/15.
//

#ifndef SORTNEWS_ARTICLE_H
#define SORTNEWS_ARTICLE_H
#include <string>
#include <map>
#include "term.h"

class Article
{
private:
    __int64_t article_id;
    int article_time;
    float article_heat;
    std::string title;
    std::string content;
    std::string url;

public:
    Article();
    Article(__int64_t article_id, int article_time, float article_heat, std::string title, std::string content, std::string url);
    Article(__int64_t article_id, int article_time, std::string title, std::string content, std::string url, Term *t);
    std::map<std::string, int> GetTermMap() const;
    __int64_t GetArticleId() const;
    float ComputArticleHeat(Term *t);
    std::string GetArticleTitle() const;
    std::string GetArticleContent() const;
    float GetArticleHeat() const;
    void SetArticleHeat(float heat);

};


#endif //SORTNEWS_ARTICLE_H
