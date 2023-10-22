#include "afine_strategy.h"
using namespace s21;
void RotateStrategyX::use() {
  for (int i = 0; i < dots_.size(); i += 3) {
    double rem_cur = dots_[i + 1];
    dots_[i + 1] = rem_cur * cos(angle_) - dots_[i + 2] * sin(angle_);
    dots_[i + 2] = rem_cur * sin(angle_) + dots_[i + 2] * cos(angle_);
  }
}

void RotateStrategyZ::use() {
  for (int i = 0; i < dots_.size(); i += 3) {
    double rem_cur = dots_[i];
    dots_[i] = rem_cur * cos(angle_) - dots_[i + 1] * sin(angle_);
    dots_[i + 1] = rem_cur * sin(angle_) + dots_[i + 1] * cos(angle_);
  }
}

void RotateStrategyY::use() {
  for (int i = 0; i < dots_.size(); i += 3) {
    double rem_cur = dots_[i];
    dots_[i] = rem_cur * cos(angle_) - dots_[i + 2] * sin(angle_);
    dots_[i + 2] = rem_cur * sin(angle_) + dots_[i + 2] * cos(angle_);
  }
}

void MoveStrategy::use() {
  int i;
  if (axis_ == 'x') {
    i = 0;
  } else if (axis_ == 'y') {
    i = 1;
  } else {
    i = 2;
  }
  for (; i < dots_.size(); i += 3) {
    dots_[i] += mov_;
  }
}

void ScaleStrategy::use() {
  for (int i = 0; i < dots_.size() - 1; i++) {
    dots_[i] *= scale_;
  }
}
