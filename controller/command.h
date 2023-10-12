#ifndef COMMAND_H
#define COMMAND_H
#include "../model/model.h"

namespace s21 {
class Command {
    Model* model_;
public:
    Command(Model* m): model_(m){};
    virtual void Execute();
};

class RotateCommand : public Command {
    char axis_;
    int angle_;
public:
    RotateCommand(Model* m, char axis, int angle) : Command(m),
                                                    axis_(axis),
                                                    angle_(angle) {};
    void Execute() override;
};

class MoveCommand : public Command {
    char axis_;
    int dist_;
public:
    MoveCommand(Model* m, char axis, int dist) : Command(m),
                                                    axis_(axis),
                                                    dist_(dist) {};
    void Execute() override;
};

class ScaleCommand : public Command {
    int value_;
public:
    ScaleCommand(Model* m, int value) : Command(m),
                                       value_(value) {};
    void Execute() override;
};
}
#endif // COMMAND_H
