#ifndef WEBASSEMBLYDEMO_VERTEX_H
#define WEBASSEMBLYDEMO_VERTEX_H

#include <GLES3/gl3.h>
#include "Position.hpp"
#include "Color.hpp"
#include "UV.hpp"

struct Vertex {

  // Relative position X, Y
  struct Position position;

  // R, G, B, A
  struct Color color;

  // UV Texture coordinates
  struct UV uv;

  void setPosition(float x, float y) {
    position.x = x;
    position.y = y;
  }

  void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
  }

  void setUV(float u, float v) {
    uv.u = u;
    uv.v = v;
  }

};

#endif //WEBASSEMBLYDEMO_VERTEX_H
