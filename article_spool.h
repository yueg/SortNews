//
// Created by yueg on 9/17/15.
//

#ifndef SORTNEWS_ARTICLESPOOL_H
#define SORTNEWS_ARTICLESPOOL_H
#include <vector>
#include <map>
#include "article.h"
#include "term_spool.h"
#include "heap_util.h"


class ArticleSpool
{
public:
    ArticleSpool();
    ~ArticleSpool();
    void Push(const std::string &url, int pubtime, const std::string &title, const std::string &content);
    void AddArticleToSpool(const Article *article);
    void GetArticleOfMaxHeat(int size, std::vector<Article *> out) const;


private:

  void UpdateTermTable(std::map<std::string, int> termMap, int flushTime);
  int createTime;
  int updateTime;
  int spoolMax;
  int spoolSize;
  HeapUtil *heapUtil;
  TermSpool *termTable;
};


#endif //SORTNEWS_ARTICLESPOOL_H
