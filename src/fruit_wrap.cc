
#include <node.h>
#include "fruit_wrap.h"

using namespace v8;

Fruit::Fruit() {};
Fruit::~Fruit() {};

void Fruit::Init(Handle<Object> exports) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("Fruit"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("plusOne"),
      FunctionTemplate::New(PlusOne)->GetFunction());

  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("Fruit"), constructor);
}

Handle<Value> Fruit::New(const Arguments& args) {
  HandleScope scope;

  Fruit* obj = new Fruit();
  obj->counter_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
  obj->Wrap(args.This());

  return args.This();
}

Handle<Value> Fruit::PlusOne(const Arguments& args) {
  HandleScope scope;

  Fruit* obj = ObjectWrap::Unwrap<Fruit>(args.This());
  obj->counter_ += 1;

  return scope.Close(Number::New(obj->counter_));
}
