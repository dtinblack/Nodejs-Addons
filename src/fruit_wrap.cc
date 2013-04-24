
#include <node.h>
#include "fruit_wrap.h"

using namespace v8;

Fruit::Fruit( double weight, double calories) {
    
    weight_ = weight;
    calories_ = calories;

};

Fruit::~Fruit() {};

void Fruit::Init(Handle<Object> exports) {

  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  
  fruit_template = Persistent<FunctionTemplate>::New(tpl);
  
  fruit_template->InstanceTemplate()->SetInternalFieldCount(1);  
  fruit_template->SetClassName(String::NewSymbol("Fruit"));
  
  NODE_SET_PROTOTYPE_METHOD(fruit_template, "getWeight", GetWeight);
  NODE_SET_PROTOTYPE_METHOD(fruit_template, "getCalories", GetCalories);
               
  exports->Set(String::NewSymbol("Fruit"), fruit_template->GetFunction());
  
}

Handle<Value> Fruit::New(const Arguments& args) {
  HandleScope scope;
  
  double weight   = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
  double calories = args[1]->IsUndefined() ? 0 : args[1]->NumberValue();
  
  Fruit* obj = new Fruit( weight, calories ); 
    
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

Persistent<FunctionTemplate> Fruit::fruit_template;

Grapes::Grapes( double number, double weight, double calories )
   : Fruit( weight, calories ), number_(number) {};
   
Grapes::~Grapes(){};   
   
void Grapes::Init(Handle<Object> exports) {

  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
     
  grapes_template = Persistent<FunctionTemplate>::New(tpl);
  
  grapes_template->Inherit(Fruit::fruit_template); 
  
  grapes_template->InstanceTemplate()->SetInternalFieldCount(1);
  
  grapes_template->SetClassName(String::NewSymbol("Grapes"));
  
  NODE_SET_PROTOTYPE_METHOD(grapes_template, "getBunchWeight", GetBunchWeight); 
  
  exports->Set(String::NewSymbol("Grapes"), grapes_template->GetFunction());
   
}

Handle<Value> Grapes::New(const Arguments& args ){

      HandleScope scope;

      double number   = args[0]->IsUndefined() ? 0 : args[0]->NumberValue(); 
      double weight   = args[1]->IsUndefined() ? 0 : args[1]->NumberValue();
      double calories = args[2]->IsUndefined() ? 0 : args[2]->NumberValue();  

      Grapes* obj = new Grapes(number, weight, calories);
                                    
      obj->Wrap(args.This());
      
      return args.This();

}

Handle<Value> Grapes::GetBunchWeight(const Arguments& args) {

    HandleScope scope;
        
    Grapes* obj = ObjectWrap::Unwrap<Grapes>(args.This());
    
    double total_weight = obj->number_ * obj->weight_;
            
    return scope.Close(Number::New( total_weight )); 

}



Persistent<FunctionTemplate>Grapes::grapes_template;
   

