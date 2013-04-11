#define BUILDING_NODE_EXTENSION

#include <node.h>
#include "myfruit.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  MyFruit::Init(exports);
}

NODE_MODULE(fruit, InitAll)
