#include "mwcontroller.h"
using namespace s21;
MWController::MWController() { model_ = new Model(); }

GLfloat *MWController::GetVertexes() { return model_->vertexes_.data(); }

GLuint MWController::GetVertexCount() { return model_->vertexes_.size(); }

std::vector<std::vector<GLuint> > MWController::GetFasets() {
  return model_->fasets_;
}
