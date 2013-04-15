// #define BUILDING_NODE_EXTENSION

#include <node.h>

#include "fruit_wrap.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  Fruit::Init(exports);
}

NODE_MODULE(fruit, InitAll)
