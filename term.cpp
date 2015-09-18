//
// Created by yueg on 9/17/15.
//
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <set>
#include <time.h>
#include "term.h"
#include "string.h"

using namespace std;

term::term()
{
    this->createTime = (int)time(0);
    this->updateTime = this->createTime;
    this->termHeat.clear();
}

term::term(set<string> terms)
{
    set<string>::iterator iter;
    for(iter = terms.begin(); iter != terms.end(); iter++)
    {
        map<string, float>::iterator iterHeat = this->termHeat.find(*iter);
        if(iterHeat == termHeat.end())
        {
            this->termHeat.insert(make_pair(*iter, (float)0));
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
            for(int i = 0; i < strlen(s); i++)
            {
                if(s[i] == '\n')
                {
                    s[i] = '\0';
                }
            }
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
    if(flushTime - createTime == 0)
    {
        return;
    }
    float ratio = (float)1.0 - (float)(flushTime - updateTime) / (float)(flushTime - createTime);
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
        map<string, float>::iterator iterTemp = this->termHeat.find(iter->first);
        if(iterTemp != this->termHeat.end())
            iterTemp->second += (float)iter->second;
    }
    this->updateTime = (int)time(0);
}

map<string, float> term::getTermHeat()
{
    return this->termHeat;
}

term* term::getTermTable()
{
    return this;
}
