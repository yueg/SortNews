//
// Created by yueg on 9/17/15.
//

#ifndef SORTNEWS_TERMS_CLASS_H
#define SORTNEWS_TERMS_CLASS_H
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <set>
#include <time.h>
using namespace std;

class term
{
private:
    map<string, float> termHeat;
    int createTime;
    int updateTime;

public:
    term();
    term(set<string> terms);
    term(string termFilePath);
    void reductionByTime(int flushTime);
    void update(map<string, int> termNum, int flushTime);
    map<string, float> getTermHeat();
    term *getTermTable();
};


#endif //SORTNEWS_TERMS_CLASS_H
