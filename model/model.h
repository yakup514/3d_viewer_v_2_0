#ifndef MODEL_H
#define MODEL_H

#include "OpenGL/OpenGL.h"
#include <vector>
namespace  s21  {


class Model
{
public:
    Model();
    std::vector<GLfloat> vertexes_;
    std::vector<std::vector<GLuint>> fasets_;
};
}
#endif // MODEL_H
