#include <stdlib.h>
#include <stdio.h>
#include <emscripten.h>
#include <string.h>

#ifndef WEBASSEMBLYDEMO_ENGINE_H
#define WEBASSEMBLYDEMO_ENGINE_H


class Engine {

  public:

    Engine();

    ~Engine();

    EMSCRIPTEN_KEEPALIVE
    char* init(int w, int h);

    int cell_index(int i, int j);

    EMSCRIPTEN_KEEPALIVE
    char cell(int i, int j);

    EMSCRIPTEN_KEEPALIVE
    char cellSafe(int cellIndex);

    EMSCRIPTEN_KEEPALIVE
    char getNext(int i, int j);

    void loopCurrentState();

    EMSCRIPTEN_KEEPALIVE
    void computeNextState();

    EMSCRIPTEN_KEEPALIVE
    void set (int i, int j, int value);

    EMSCRIPTEN_KEEPALIVE
    void setNext (int i,int j, int value);

  private:

    int _width;
    int _height;
    char* _current;
    char* _next;

};


#endif //WEBASSEMBLYDEMO_ENGINE_H
