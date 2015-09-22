#include <iostream>
#include <string>
#include <map>
#include "./extractTerms/countWord.h"
#include "article.h"
#include "article_spool.h"

#define TERMSPATH "/home/yueg/innotree/SortNews/data/business.seg"

using namespace std;


int main()
{
  ArticleSpool *articleSpool = new ArticleSpool();
  articleSpool->Push("123", 0, "O2O", "O2M");
  articleSpool->Push("123", 0, "O2O", "O2M");
  articleSpool->Push("123", 0, "O2O", "O2M");
  articleSpool->Push("123", 0, "O2O", "O2M");
  vector<Article> *ret = new vector<Article>;
  articleSpool->GetArticleOfMaxHeat(3, ret);
  cout << ret->size() << endl;

  return 0;
}