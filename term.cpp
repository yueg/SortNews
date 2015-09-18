//
// Created by yueg on 9/17/15.
//
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <set>
#include <time.h>
#include "term.h"

using namespace std;

term::term()
{
    this->createTime = (int)time(0);
    this->updateTime = this->createTime;
}

term::term(set<string> terms)
{
    set<string>::iterator iter;
    for(iter = terms.begin(); iter != terms.end(); iter++)
    {
        map<string, float>::iterator iterHeat = this->termHeat.find(*iter);
        if(iterHeat == termHeat.end())
        {
            this->termHeat.insert(make_pair(*iter, 0));
        }
    }
this->createTime = (int)time(0);
this->updateTime = this->createTime;
}

term::term(string termFilePath)
{
    FILE *fp = fopen(termFilePath.c_str(), "r");
    if(NULL==fp)
    {
        fprintf(stderr,"open file error:%s\n", termFilePath.c_str());
    }
    else
    {
        char *s = (char *)malloc(2048);
        while(fgets(s, 2048, fp))
        {
            string t(s);
            map<string, float>::iterator iterHeat = this->termHeat.find(t);
            if(iterHeat == termHeat.end())
            {
                this->termHeat.insert(make_pair(t, 0));
            }
        }
    }
    this->createTime = (int)time(0);
    this->updateTime = this->createTime;
}

void term::reductionByTime(int flushTime)
{
    map<string, float>::iterator iter;
    float ratio = (float)(flushTime - updateTime) / (float)(flushTime - updateTime);
    for(iter = this->termHeat.begin(); iter != this->termHeat.end(); iter++)
    {
        iter->second *= ratio;
    }
    this->updateTime = flushTime;
}

void term::update(map<string, int> termNum, int flushTime){
    reductionByTime(flushTime);
    map<string, int>::iterator iter;
    for(iter = termNum.begin(); iter != termNum.end(); iter++)
    {
        this->termHeat[iter->first] += (float)iter->second;
    }
}

map<string, float> term::getTermHeat()
{
    return this->termHeat;
}

term* term::getTermTable()
{
    return this;
}
