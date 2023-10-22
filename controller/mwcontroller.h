#ifndef MWCONTROLLER_H
#define MWCONTROLLER_H
#include "../model/model.h"
namespace s21 {

class MWController {
 public:
  MWController();
  Model* model_;
  GLfloat* GetVertexes();
  GLuint GetVertexCount();
  std::vector<std::vector<GLuint>> GetFasets();
};
}  // namespace s21
#endif  // MWCONTROLLER_H
