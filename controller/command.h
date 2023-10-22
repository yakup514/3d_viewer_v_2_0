#ifndef COMMAND_H
#define COMMAND_H

#include <cmath>
#include <fstream>
#include <string>

#include "../model/model.h"
#include "afine_strategy.h"

namespace s21 {
class Command {
 public:
  Command(Model* m) : model_(m){};
  virtual void Execute() = 0;
  Model* GetModel() { return model_; }

 private:
  Model* model_;
};

class RotateCommand : public Command {
 public:
  RotateCommand(Model* m, char axis, double angle)
      : Command(m), axis_(axis), angle_(angle){};
  void Execute() override;

 private:
  char axis_;
  double angle_;
};

class MoveCommand : public Command {
 public:
  MoveCommand(Model* m, char axis, double dist)
      : Command(m), axis_(axis), dist_(dist){};
  void Execute() override;

 private:
  char axis_;
  double dist_;
};

class ScaleCommand : public Command {
 public:
  ScaleCommand(Model* m, double value) : Command(m), value_(value){};
  void Execute() override;

 private:
  double value_;
};

class ParseCommand : public Command {
 public:
  ParseCommand(Model* m, std::string path) : Command(m), path_(path){};
  void Execute() override;

 private:
  std::string path_;
};

}  // namespace s21
#endif  // COMMAND_H
