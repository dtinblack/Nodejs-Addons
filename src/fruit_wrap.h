#ifndef FRUIT_WRAP_H
#define FRUIT_WRAP_H

#include <node.h>

using namespace v8;


  
class Fruit : public node::ObjectWrap {
 public:
  
    Fruit( double weight, double calories );
  ~Fruit();
  
  static Persistent<FunctionTemplate> fruit_template;
  
  static void Init(Handle<Object> exports);  
  static Handle<Value> New(const Arguments& args);  
  static Handle<Value> GetWeight(const Arguments& args);
  static Handle<Value> GetCalories(const Arguments& args);
  static Handle<Value> GetJuice(const Arguments& args);
  
  // Sync Callback 
  
  static Handle<Value> ChopFruit(const Arguments& args);
  
  // Async Callback - requires AsyncWork and AsyncAfter - see below
  
  static Handle<Value> SqueezeFruit(const Arguments& args);
     
protected:

  static void AsyncWork(uv_work_t *req);
  static void AsyncAfter(uv_work_t *req);
   
  double weight_;
  double calories_;
       
};

class Grapes : public Fruit {

public:
    
     Grapes( double number, double weight, double calories );
     ~Grapes();
     
    static Persistent<FunctionTemplate> grapes_template;
    
    static void Init(Handle<Object> exports);
    static Handle<Value> New(const Arguments& args);
    static Handle<Value> GetBunchWeight(const Arguments& args);
    
    static Handle<Value> GetJuice(const Arguments& args);
     
protected:

     double number_;         

};




#endif
