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
#include "term.h"
#include "article.h"

class TermSpool {
private:
    std::vector<Term *> termSpool_;
    std::map<std::string, Term *> termMap_;
    int createTime_;
    int updateTime_;

public:
    TermSpool(const std::string &termFilePath);
    void UpdateTermCount(const std::map<std::string, int> &aticleTerm);
    Term *GetTermByWord(const std::string &word);
};


#endif //SORTNEWS_TERMS_CLASS_H
