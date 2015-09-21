//
// Created by yueg on 9/17/15.
//

#ifndef SORTNEWS_ARTICLE_H
#define SORTNEWS_ARTICLE_H
#include <string>
#include <map>
#include "Term.h"

class Article
{
private:
    int article_id;
    int article_time;
    float article_heat;
    std::string title;
    std::string content;
    std::string url;

public:
    Article();
    Article(int article_id, int article_time, float article_heat, std::string title, std::string content, std::string url);
    Article(int article_id, int article_time, std::string title, std::string content, std::string url, Term *t);
    Article *GetArticle();
    std::map<std::string, int> GetTermMap() const;
    int GetArticleId() const;
    float ComputArticleHeat(Term *t);
    std::string GetArticleTitle() const;
    std::string GetArticleContent() const;
    float GetArticleHeat() const;
    void SetArticleHeat(float heat);

};


#endif //SORTNEWS_ARTICLE_H
