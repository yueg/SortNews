#include <iostream>
#include <string>
#include <map>
#include "./extractTerms/countWord.h"
#define TERMSPATH "/home/yueg/innotree/SortNews/data/business.seg"

using namespace std;

typedef struct article
{
    int article_id;
    int article_time;
    string title;
    string content;
    string url;
    article(int a, int b, string c, string d, string e){article_id = a; article_time = b; title = c; content = d; url = e;}
};

static map<string, int> termSpool;

map<string, int> getTermsFromNews(article a)
{
    map<string, int> ret = getTermsMapFromStr(TERMSPATH, a.title + a.content);
    return ret;
};

void updateTermSpool(map<string, int> newTerms, map<string, int> &termSpool)
{
    map<string, int>::iterator it;
    for(it = newTerms.begin(); it != newTerms.end(); it++)
    {
        map<string, int>::iterator iterFind = termSpool.find(it->first);
        if(iterFind != termSpool.end())
        {
            iterFind->second += it->second;
        }
        else
        {
            termSpool.insert(make_pair(it->first, it->second));
        }
    }
}

int main() {
    article a = {0, 0, "垂直电商", "O2O", ""};
    map<string, int> termsMap = getTermsFromNews(a);
    map<string, int>::iterator it = termsMap.begin();
    for(; it != termsMap.end(); it++)
    {
        cout << it->first << "   ";
        cout << it->second << endl;
    }
    updateTermSpool(termsMap, termSpool);
    it = termSpool.begin();
    for(; it != termSpool.end(); it++)
    {
        cout << it->first << "   ";
        cout << it->second << endl;
    }
    return 0;
}