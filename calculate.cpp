#include <node.h>
#include "calculo.h"

namespace calculate {
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::Number;
    using v8::Value;

    void Generar(const FunctionCallbackInfo<Value>&args){
        Isolate* isolate = args.GetIsolate();
        /* std::string  nonce1="";
        std::string  hash_1= "";
        std::string  hash_prev_1="";

        test(1, nonce1,  hash_1, hash_prev_1);
        
         */
        int x = 30;
        
        /* auto total = Number::New(isolate , x);
        args.GetReturnValue().Set(total); */
        
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world").ToLocalChecked());

        //auto total = Text::New(isolate , nonce1);

        //args.GetReturnValue().Set(String::New(isolate, nonce1.c_str()).ToLocalChecked());
        //args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world").ToLocalChecked());
        //args.GetReturnValue().Set(total);
    }

    
    /* void Insertar(const FunctionCallbackInfo<Value>&args){}
    
    void Insertar(const FunctionCallbackInfo<Value>&args){} */
        


    void Method(const FunctionCallbackInfo<Value>&args){
        Isolate* isolate = args.GetIsolate();
        int i;
        
        int x = 30;
        
        auto total = Number::New(isolate , x);
        args.GetReturnValue().Set(total);
    }

    void Method2(const FunctionCallbackInfo<Value>&args){
        Isolate* isolate = args.GetIsolate();
        int i;
        double x = 20000;

        auto total = Number::New(isolate , x);
        args.GetReturnValue().Set(total);
    }

    void Initialize(Local<Object> exports){
        NODE_SET_METHOD(exports , "calc" , Generar);
        NODE_SET_METHOD(exports , "calc2" , Method2);
    }

    NODE_MODULE(NODE_GY_MODULE_NAME , Initialize);

};