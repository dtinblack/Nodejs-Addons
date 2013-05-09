
#include <node.h>
#include <string>

#include "fruit_wrap.h"


using namespace v8;

struct Baton {      // Required for running on a separate thread
    Persistent<Function> callback;
    bool error;
    std::string error_message;
    int32_t result;
}; 

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
  NODE_SET_PROTOTYPE_METHOD(fruit_template, "getJuice", GetJuice);
  NODE_SET_PROTOTYPE_METHOD(fruit_template, "chopFruit", ChopFruit );
  NODE_SET_PROTOTYPE_METHOD(fruit_template, "squeezeFruit", SqueezeFruit );
               
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

Handle<Value> Fruit::GetJuice(const Arguments& args ) {
  HandleScope scope;
  
  return scope.Close(String::New("Fruit Juice"));

}


// Sync Callback Function

Handle<Value> Fruit::ChopFruit(const Arguments& args) {

   HandleScope scope;
   
   Local<Function> cb = Local<Function>::Cast(args[0]);
   const unsigned argc = 1;
   
   Local<Value> argv[argc] = { Local<Value>::New(String::New("Fruit chopped")) };
   
   cb->Call(Context::GetCurrent()->Global(), argc, argv);
   
   return scope.Close(Undefined());

}


// Async Callback Function

Handle<Value> Fruit::SqueezeFruit(const Arguments& args) {
    HandleScope scope;
        
    if( !args[0]->IsFunction() ){
       return ThrowException(Exception::TypeError(
         String::New("First argument must be a callback function")));
    }     
    
    Local<Function> callback = Local<Function>::Cast(args[0]);

    Baton *baton = new Baton();
        
    baton->error = false;
    baton->callback = Persistent<Function>::New(callback);
    uv_work_t *req = new uv_work_t();
    req->data = baton;
    

    int status = uv_queue_work(uv_default_loop(), req, Fruit::AsyncWork,
                            (uv_after_work_cb)Fruit::AsyncAfter); 
                            
     assert(status == 0);                       
    

    return scope.Close(Undefined());
}

void Fruit::AsyncWork(uv_work_t *req) {

     Baton *baton = static_cast<Baton*>(req->data);
     
     // do work in thread pool 
     
     baton->result = 42;
}

void Fruit::AsyncAfter(uv_work_t *req) {

   HandleScope scope;
   
   Baton *baton = static_cast<Baton*>(req->data);
   
   if(baton->error) {
   
      Local<Value> err = Exception::Error(String::New(baton->error_message.c_str()));   
   
      const unsigned argc = 1;
      Local<Value> argv[argc] = { err };
   
      TryCatch try_catch;
   
      baton->callback->Call(Context::GetCurrent()->Global(), argc, argv);
   
      if ( try_catch.HasCaught()) {
         node::FatalException(try_catch);
      }  
    } else {
    
      const unsigned argc = 2;
      Local<Value> argv[argc] = {
          Local<Value>::New(Null()),
          Local<Value>::New(Integer::New(baton->result))
       };
       
       TryCatch try_catch;
       baton->callback->Call(Context::GetCurrent()->Global(), argc, argv);
       if(try_catch.HasCaught()) {
          node::FatalException(try_catch);
       }
    }   
       
       baton->callback.Dispose();
       
       delete baton;
       delete req;
      
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
  NODE_SET_PROTOTYPE_METHOD(grapes_template, "getJuice", GetJuice ); 
  
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

Handle<Value> Grapes::GetJuice(const Arguments& args ) {
  HandleScope scope;
  
  return scope.Close(String::New("Grape Juice"));

}

Persistent<FunctionTemplate>Grapes::grapes_template;
   

