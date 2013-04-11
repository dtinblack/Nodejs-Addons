#ifndef MYFRUIT_H
#define MYFRUIT_H

#include <node.h>

class MyFruit : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);

 private:
  MyFruit();
  ~MyFruit();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> PlusOne(const v8::Arguments& args);
  double counter_;
};

#endif
