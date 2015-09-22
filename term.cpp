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
#include <string.h>
#include "term.h"


using namespace std;

Term::Term()
{
    this->createTime = (int)time(0);
    this->updateTime = this->createTime;
    this->termHeat.clear();
}

Term::Term(const set<string> &terms)
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

Term::Term(const string &termFilePath)
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

void Term::ReductionByTime(int flushTime)
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

void Term::Update(const map<string, int> &termNum, int flushTime){
    ReductionByTime(flushTime);
    map<string, int>::const_iterator iter;
    for(iter = termNum.begin(); iter != termNum.end(); iter++)
    {
        map<string, float>::iterator iterTemp = this->termHeat.find(iter->first);
        if(iterTemp != this->termHeat.end())
            iterTemp->second += (float)iter->second;
    }
    this->updateTime = (int)time(0);
}

map<string, float> Term::GetTermHeat() const
{
    return this->termHeat;
}


