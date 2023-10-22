#ifndef CPP4_3DVIEWER_V_2_0_1_CONTROLLER_AFINE_STATEGY_H_
#define CPP4_3DVIEWER_V_2_0_1_CONTROLLER_AFINE_STATEGY_H_

#include <cmath>
#include <vector>

#include "OpenGL/OpenGL.h"
namespace s21 {
class AfineStrategy {
 public:
  AfineStrategy(std::vector<GLfloat> &vec) : dots_(vec) {}
  virtual ~AfineStrategy(){};
  virtual void use() = 0;

 protected:
  std::vector<GLfloat> &dots_;
};

class RotateStrategyX : public AfineStrategy {
 public:
  RotateStrategyX(std::vector<GLfloat> &vec, double angle)
      : AfineStrategy(vec), angle_(angle) {}

  void use() override;

 private:
  double angle_;
};

class RotateStrategyY : public AfineStrategy {
 public:
  RotateStrategyY(std::vector<GLfloat> &vec, double angle)
      : AfineStrategy(vec), angle_(angle) {}

  void use() override;

 private:
  double angle_;
};

class RotateStrategyZ : public AfineStrategy {
 public:
  RotateStrategyZ(std::vector<GLfloat> &vec, double angle)
      : AfineStrategy(vec), angle_(angle) {}

  void use() override;

 private:
  double angle_;
};

class MoveStrategy : public AfineStrategy {
 public:
  MoveStrategy(std::vector<GLfloat> &vec, double mov, char axis)
      : AfineStrategy(vec), mov_(mov), axis_(axis) {}

  void use() override;

 private:
  double mov_;
  char axis_;
};

class ScaleStrategy : public AfineStrategy {
 public:
  ScaleStrategy(std::vector<GLfloat> &vec, double scale)
      : AfineStrategy(vec), scale_(scale) {}

  void use() override;

 private:
  double scale_;
};
}
#endif
