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

class Term
{
private:
    std::map<std::string, float> termHeat;
    std::map<std::string, std::vector<int>> termCount;
    int createTime;
    int updateTime;

public:
    Term();
    Term(const std::set<std::string> &terms);
    Term(const std::string &termFilePath);
    void ReductionByTime(int flushTime);
    void Update(const std::map<std::string, int> &termNum, int flushTime);
    std::map<std::string, float> GetTermHeat() const;


};


#endif //SORTNEWS_TERMS_CLASS_H
