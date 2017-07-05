#include "Engine.h"

Engine::Engine() : _width(0), _height(0) {

}

Engine::~Engine() {

}

char* Engine::init(int w, int h) {
  EM_ASM(
    console.log("ok, run");
  );
  _width = w + 2;
  _height = h + 2;
  _current = static_cast<char*>(malloc(_width * _height * sizeof(char)));
  _next = static_cast<char*>(malloc(_width * _height * sizeof(char)));
  return _current;
}

int Engine::cell_index(int i, int j) {
  return i * _width + j;
}

char Engine::cell(int i, int j) {
  return _current[cell_index(i, j)];
}

char Engine::cellSafe(int cellIndex) {
  return _current[cellIndex];
}

char Engine::getNext(int i, int j) {
  return _next[cell_index(i, j)];
}

void Engine::loopCurrentState() {
  for (int j=1; j < _width + 1; j++) {
    _current[cell_index(0, j)] = _current[cell_index(_height - 2, j)];
    _current[cell_index(_height - 1, j)] = _current[cell_index(1, j)];
  }
  for (int i=1; i < _height + 1; i++) {
    _current[cell_index(i, 0)] = _current[cell_index(i, _width - 2)];
    _current[cell_index(i, _width - 1)] = _current[cell_index(i, 1)];
  }
  _current[cell_index(0, 0)] = _current[cell_index(_height - 2, _width - 2)];
  _current[cell_index(0, _width - 1)] = _current[cell_index(_height - 2, 1)];
  _current[cell_index(_height - 1, 0)] = _current[cell_index(1, _width - 2)];
  _current[cell_index(_height - 1, _width - 1)] = _current[cell_index(1, 1)];
}

void Engine::computeNextState() {
  loopCurrentState();

  int neighbors = 0;
  int i_m1, i_p1, i_;
  int j_m1, j_p1;
  int height_limit = _height - 1;
  int width_limit = _width - 1;
  for (int i = 1; i < height_limit; i++) {
    i_m1 = (i - 1) * _width;
    i_p1 = (i + 1) * _width;
    i_ = i * _width;
    for (int j = 1; j < width_limit; j++) {
      j_m1 = j - 1;
      j_p1 = j + 1;
      neighbors = _current[i_m1 + j_m1];
      neighbors += _current[i_m1 + j];
      neighbors += _current[i_m1 + j_p1];
      neighbors += _current[i_+ j_m1];
      neighbors += _current[i_ + j_p1];
      neighbors += _current[i_p1 + j_m1];
      neighbors += _current[i_p1 + j];
      neighbors += _current[i_p1 + j_p1];
      if (neighbors == 3) {
        _next[i_ + j] = 1;
      } else if (neighbors == 2) {
        _next[i_ + j] = _current[i_ + j];
      } else {
        _next[i_ + j] = 0;
      }
    }
  }
  memcpy(_current, _next, _width * _height);
}

void Engine::set(int i, int j, int value) {
  _current[cell_index(i, j)] = value;
}

void Engine::setNext(int i, int j, int value) {
  _next[cell_index(i, j)] = value;
}

EMSCRIPTEN_KEEPALIVE
int main() {
  return 0;
}
