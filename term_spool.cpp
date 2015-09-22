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
#include "term_spool.h"


using namespace std;

TermSpool::TermSpool(const string &termFilePath)
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
            Term *term = new Term(s);
            termSpool_.push_back(term);
            termMap_.insert(make_pair(s, term));
        }
    }
    createTime_ = (int)time(0);
    updateTime_ = createTime_;
}


void TermSpool::UpdateTermCount(const map<string, int> &aticleTerm, int flushtime) {
    for (map<string, int>::const_iterator iter = aticleTerm.begin(); iter != aticleTerm.end(); iter++) {
        Term *term = termMap_[iter->first];
        term->UpdateTerm((int)time(0), iter->second);
    }
    updateTime_ = (int)time(0);
}

Term* TermSpool::GetTermByWord(const std::string &word) {
    return termMap_[word];
}


