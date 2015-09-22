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
//    Term *t = new Term(TERMSPATH);

//    map<string, float> termHeap = t->getTermHeat();
//    for(map<string, float>::iterator iter = termHeap.begin(); iter != termHeap.end(); iter++)
//    {
//        cout << iter->first << "   " << iter->second << endl;
//    }
//    cout << endl;
//    Article *a = new Article(10, (int)time(0), "O2OO2M", "O2OO2M", "www.baidu.com", t);
//    Article *b = new Article(5, (int)time(0), "O2O", "O2O", "www.baidu.com", t);
//    vector<Article> as;
//    as.push_back(*a);
//    as.push_back(*b);
//    ArticleSpool *aSpool = new ArticleSpool(as, t);
//    vector<Article> ret = aSpool->GetArticleOfMaxHeat(1);
//    cout << ret[0].GetArticleId() << endl;
//    cout << ret[0].GetArticleContent() << endl;
//    cout << ret[0].GetArticleHeat() << endl;


  ArticleSpool *articleSpool = new ArticleSpool();
  articleSpool->Push();
  articleSpool->GetArticleOfMaxHeat(12);

  return 0;
}