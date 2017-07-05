#include "Counter.h"

Counter::Counter() : _counter(0) {

}

Counter::~Counter() {

}

int Counter::count() {
  _counter += 1;
  return _counter;
}

