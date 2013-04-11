
#include <node.h>
#include "myfruit.h"

using namespace v8;

MyFruit::MyFruit() {};
MyFruit::~MyFruit() {};

void MyFruit::Init(Handle<Object> exports) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("MyFruit"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("plusOne"),
      FunctionTemplate::New(PlusOne)->GetFunction());

  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("MyFruit"), constructor);
}

Handle<Value> MyFruit::New(const Arguments& args) {
  HandleScope scope;

  MyFruit* obj = new MyFruit();
  obj->counter_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
  obj->Wrap(args.This());

  return args.This();
}

Handle<Value> MyFruit::PlusOne(const Arguments& args) {
  HandleScope scope;

  MyFruit* obj = ObjectWrap::Unwrap<MyFruit>(args.This());
  obj->counter_ += 1;

  return scope.Close(Number::New(obj->counter_));
}
