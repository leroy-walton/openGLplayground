#ifndef AXES_H
#define AXES_H

#include <GL/glew.h>

class Axes {
 public:
  Axes();
  ~Axes();
  void draw();

 private:
  GLuint vbo_, vao_;
};

#endif