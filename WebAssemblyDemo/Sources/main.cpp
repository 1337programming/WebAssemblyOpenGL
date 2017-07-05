#include "OpenGL.hpp"

#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
int main() {
  OpenGL *demo = new OpenGL();
  emscripten_set_main_loop(demo->generateFrame, 0, 0);
}