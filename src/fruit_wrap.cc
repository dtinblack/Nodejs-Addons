/* Based on http://nodejs.org/api/addons.html#addons_object_factory */

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
    
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getWeight"),
      FunctionTemplate::New(GetWeight)->GetFunction()); 
      
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getCalories"),
      FunctionTemplate::New(GetCalories)->GetFunction());       

  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("Fruit"), constructor);
}

Handle<Value> Fruit::New(const Arguments& args) {
  HandleScope scope;

  Fruit* obj = new Fruit(); // Conventional C++ Call see notes
  
  obj->weight_   = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
  obj->calories_ = args[1]->IsUndefined() ? 0 : args[1]->NumberValue();
  
  obj->Wrap(args.This());

  return args.This();
}

Handle<Value> Fruit::GetWeight(const Arguments& args) {
  HandleScope scope;

  Fruit* obj = ObjectWrap::Unwrap<Fruit>(args.This());

  return scope.Close(Number::New(obj->weight_));
}

Handle<Value> Fruit::GetCalories(const Arguments& args) {
  HandleScope scope;

  Fruit* obj = ObjectWrap::Unwrap<Fruit>(args.This());
    
  return scope.Close(Number::New(obj->calories_));
}

