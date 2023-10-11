#include "viewer.h"

#include <QMessageBox>
#include <QMouseEvent>
using namespace s21;
Viewer::Viewer(QWidget *parent) : QOpenGLWidget(parent), index_buffer_(QOpenGLBuffer::IndexBuffer) {
    settings_= new QSettings(this);
    LoadSettings();

}

Viewer::~Viewer() { }

void Viewer::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}
void Viewer::resizeGL(int w, int h) { glViewport(0, 0, w, h); }
void Viewer::paintGL() {
  projection_matrix_.setToIdentity();
  if (projection_type_ == 0) {
    projection_matrix_.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 6.0f);
  } else {
    projection_matrix_.frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 6.0f);
  }
  projection_matrix_.translate(0.0, 0.0, -2.05);
  projection_matrix_.rotate(30, 0, 1, 0);
  glLineWidth((GLfloat)line_width_);
  if (line_type_ == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0X00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glEnable(GL_PROGRAM_POINT_SIZE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  InitShaders();
  program_->bind();
  glClearColor((GLfloat)background_color_[0], (GLfloat)background_color_[1],
               (GLfloat)background_color_[2], (GLfloat)background_color_[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vertex_buffer_.bind();
    index_buffer_.bind();

    program_->setUniformValue("qt_ModelViewProjectionMatrix",
                              projection_matrix_);
    program_->setUniformValue("color", line_color_);
    int vertLoc = program_->attributeLocation("qt_Vertex");
    program_->enableAttributeArray(vertLoc);
    program_->setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3, 0);
    program_->setUniformValue("point_size", vertex_size_);

   glDrawElements(GL_LINES, index_buffer_.size(), GL_UNSIGNED_INT, 0);

    if (vertex_type_ != 0) {
      program_->setUniformValue("color", vertex_color_);
      if (vertex_type_ == 1)
        glEnable(GL_POINT_SMOOTH);
      else
        glDisable(GL_POINT_SMOOTH);

        glDrawElements(GL_POINTS, index_buffer_.size(), GL_UNSIGNED_INT, 0 );

    }

    vertex_buffer_.release();
    index_buffer_.release();
  delete (program_);
}

//int Viewer::LoadModel(QString path) {
//  if (md_ != NULL && md_->err_ == -1) {
//    delete md_;
//  }
//  md_ = new ModelData(path);
//  int err = md_->err_;
//  if (md_->err_ != -1) {
//    delete md_;
//    md_ = NULL;

//  } else {
//    InitModel();
//    update();
//  }
//  return err;
//}

void Viewer::LoadSettings() {
  QColor tmp =
      settings_->value("background_color", QColor(Qt::black)).value<QColor>();
  background_color_[0] = (GLfloat)tmp.red() / 255;
  background_color_[1] = (GLfloat)tmp.green() / 255;
  background_color_[2] = (GLfloat)tmp.blue() / 255;
  background_color_[3] = (GLfloat)tmp.alpha() / 255;
  tmp = settings_->value("line_color", QColor(Qt::white)).value<QColor>();
  line_color_[0] = (GLfloat)tmp.red() / 255;
  line_color_[1] = (GLfloat)tmp.green() / 255;
  line_color_[2] = (GLfloat)tmp.blue() / 255;
  line_color_[3] = (GLfloat)tmp.alpha() / 255;
  tmp = settings_->value("vertex_color", QColor(Qt::blue)).value<QColor>();
  vertex_color_[0] = (GLfloat)tmp.red() / 255;
  vertex_color_[1] = (GLfloat)tmp.green() / 255;
  vertex_color_[2] = (GLfloat)tmp.blue() / 255;
  vertex_color_[3] = (GLfloat)1.0;
  line_type_ = settings_->value("line_type", 0).toInt();
  vertex_type_ = settings_->value("vertex_type", 0).toInt();
  vertex_size_ = settings_->value("vertex_size", 1.0).toFloat();
  line_width_ = settings_->value("line_width", 1.0).toFloat();
  projection_type_ = settings_->value("projection_type", 0).toInt();
}

void Viewer::InitModel(GLuint size, GLfloat* data,  std::vector<std::vector<GLuint>> fasets) {
    InitVertexBuffer(size, data);
    InitIndexBuffer(fasets);
}

void Viewer::InitVertexBuffer(GLuint size, GLfloat *data) {
    vertex_buffer_.create();
    vertex_buffer_.bind();
    vertex_buffer_.allocate(data, size * sizeof(GLfloat));
    vertex_buffer_.release();
}

void Viewer::InitIndexBuffer(std::vector<std::vector<GLuint> > fasets){
    std::vector<GLuint> indexes;

    for (int i = 0; i < fasets.size(); ++i) {
            for (int j = 0; j < fasets[i].size(); ++j) {
                if (j + 1 != fasets[i].size()) {
                    indexes.push_back(fasets[i][j]);
                    indexes.push_back(fasets[i][j + 1]);
                } else {
                    indexes.push_back(fasets[i][j]);
                    indexes.push_back(fasets[i][0]);
                }
            }
        }

        index_buffer_.create();
        index_buffer_.bind();
        index_buffer_.allocate(indexes.data(), indexes.size() * sizeof(GLuint));
        index_buffer_.release();
}

//void Viewer::DrawFasets(const std::vector<std::vector<GLuint> > &fasets) {

//}

//void Viewer::mousePressEvent(QMouseEvent *mo) { pos_ = mo->pos(); }

//void Viewer::mouseMoveEvent(QMouseEvent *mo) {
//  x_rot_ = (mo->pos().y() - pos_.y());
//  y_rot_ = (mo->pos().x() - pos_.x());
//  pos_ = mo->pos();
//  if (md_ != NULL) {
//    md_->RotateModel(x_rot_, y_rot_, 0);
//  }
//  update();
//}

//void Viewer::wheelEvent(QWheelEvent *event) {
//  GLfloat scale = event->angleDelta().y() / 1200.0;
//  if (md_ != NULL) {
//    md_->ScaleModel(scale);
//  }
//  update();
//}

void Viewer::InitShaders() {
  program_ = new QOpenGLShaderProgram();
  if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/vertex_shader.vsh")) {
    qDebug() << "vertex shader not compilated";
    close();
  }
  if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/flagment_shader.fsh")) {
    qDebug() << "fragment shader not compilated";
    close();
  }
  if (!program_->link()) {
    qDebug() << "shader program not linked";
    close();
  }
}
