#ifndef FRUIT_WRAP_H
#define FRUIT_WRAP_H

#include <node.h>

class Fruit : public node::ObjectWrap {
 public:
  
    Fruit();
  ~Fruit();
  
  static void Init(v8::Handle<v8::Object> exports);
  
  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  
  static v8::Handle<v8::Value> GetWeight(const v8::Arguments& args);
  static v8::Handle<v8::Value> GetCalories(const v8::Arguments& args);
  
 private:
   double weight_;
   double calories_;
       
};



#endif
