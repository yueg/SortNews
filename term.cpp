//
// Created by yueg on 9/22/15.
//

#include "term.h"

Term::Term(std::string word) {
  word_ = word;
  heat_ = 0;
  createTime_ = (int)time(0);
  count_.clear();
  timeStamp_.clear();
}

Term::~Term() { }

void Term::UpdateTerm(int time, int count) {
  count_.push_back(count);
  timeStamp_.push_back(time);
}

void Term::DeleteTerm() {
  int now = (int)time(0);
  int deleteTime = now / 60 - 360;
  for (int i = 0; timeStamp_[i] <= deleteTime && !timeStamp_.empty(); i++) {
    timeStamp_.pop_front();
    count_.pop_front();
  }
}

void Term::SetTermHeat(float heat) {
  heat_ = heat;
}

float Term::GetTermHeat() {
  return heat_;
}