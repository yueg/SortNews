#include <iostream>
#include <string>
#include <map>
#include "./extractTerms/countWord.h"
#include "article.h"
#include "articleSpool.h"

#define TERMSPATH "/home/yueg/innotree/SortNews/data/business.seg"

using namespace std;


int main()
{
    term *t = new term(TERMSPATH);
//    map<string, float> termHeap = t->getTermHeat();
//    for(map<string, float>::iterator iter = termHeap.begin(); iter != termHeap.end(); iter++)
//    {
//        cout << iter->first << "   " << iter->second << endl;
//    }
    cout << endl;
    article *a = new article(10, (int)time(0), "O2OO2M", "O2OO2M", "www.baidu.com", t);
    article *b = new article(5, (int)time(0), "O2O", "O2O", "www.baidu.com", t);
    vector<article> as;
    as.push_back(*a);
    as.push_back(*b);
    articleSpool *aSpool = new articleSpool(as, t);
    vector<article> ret = aSpool->getArticleOfMaxHeat(1);
    cout << ret[0].getArticleId() << endl;
    cout << ret[0].getArticleContent() << endl;
    cout << ret[0].getArticleHeat() << endl;

    return 0;
}