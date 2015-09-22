//
// Created by yueg on 9/22/15.
//

#ifndef SORTNEWS_TERM_H
#define SORTNEWS_TERM_H
#include <string>
#include <deque>

class Term {
public:
  Term(std::string word);
  ~Term();
  void UpdateTerm(int time, int count);
  void DeleteTerm();
  void SetTermHeat(float heat);
  float GetTermHeat();

private:
  std::string word_;
  std::deque<int> count_;
  std::deque<int> timeStamp_;
  float heat_;
  int createTime_;
};


#endif //SORTNEWS_TERM_H
