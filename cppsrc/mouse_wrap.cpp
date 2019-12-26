#include "mouse_wrap.h"

using namespace mousecontroller;

Napi::Object MouseWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "MouseController",
                                      {
                                          InstanceMethod("doubleClick", &MouseWrap::DoubleClick),
                                          InstanceMethod("click", &MouseWrap::Click),
                                          InstanceMethod("getPosition", &MouseWrap::GetPosition),
                                          InstanceMethod("move", &MouseWrap::Move),
                                          InstanceMethod("drag", &MouseWrap::Drag),
                                          InstanceMethod("startDrag", &MouseWrap::StartDrag),
                                          InstanceMethod("endDrag", &MouseWrap::EndDrag),
                                      });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("MouseController", func);
    return exports;
}

MouseWrap::MouseWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<MouseWrap>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    this->mouse_ = new Mouse();
}

Napi::FunctionReference MouseWrap::constructor;

Napi::Value MouseWrap::GetPosition(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::Object point = Napi::Object::New(env);

    CGPoint mouse_position = this->mouse_->GetMousePosition();
    Napi::Number x = Napi::Number::New(env, float(mouse_position.x));
    Napi::Number y = Napi::Number::New(env, float(mouse_position.y));

    point.Set("x", x);
    point.Set("y", y);

    return point;
}

void MouseWrap::Move(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
        return;
    }

    Napi::Number first = info[0].As<Napi::Number>();
    Napi::Number second = info[1].As<Napi::Number>();
    CGPoint position = CGPointMake(first.FloatValue(), second.FloatValue());

    this->mouse_->SetMousePosition(position);
}

void MouseWrap::Click(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    Button button;
    CGPoint position;

    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments provided").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
        return;
    }
    if (!info[1].IsObject())
    {
        Napi::TypeError::New(env, "Object expected").ThrowAsJavaScriptException();
        return;
    }

    Napi::Number button_num = info[0].As<Napi::Number>();
    button = static_cast<Button>(button_num.Int32Value());

    Napi::Object point_obj = info[1].As<Napi::Object>();
    if (point_obj.Has("x") && point_obj.Has("y"))
    {
        if (!point_obj.Get("x").IsNumber())
        {
            Napi::TypeError::New(env, "Coordinate values has to be a number").ThrowAsJavaScriptException();
            return;
        }
        Napi::Number x = point_obj.Get("x").As<Napi::Number>();
        Napi::Number y = point_obj.Get("y").As<Napi::Number>();
        position = CGPointMake(x, y);
    }
    else
    {
        Napi::TypeError::New(env, "No coordinate values provided").ThrowAsJavaScriptException();
        return;
    }

    this->mouse_->MouseClick(button, position);
}

void MouseWrap::DoubleClick(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    Button button;
    CGPoint position;

    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments provided").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
        return;
    }
    if (!info[1].IsObject())
    {
        Napi::TypeError::New(env, "Object expected").ThrowAsJavaScriptException();
        return;
    }

    Napi::Number button_num = info[0].As<Napi::Number>();
    button = static_cast<Button>(button_num.Int32Value());

    Napi::Object point_obj = info[1].As<Napi::Object>();
    if (point_obj.Has("x") && point_obj.Has("y"))
    {
        if (!point_obj.Get("x").IsNumber())
        {
            Napi::TypeError::New(env, "Coordinate values has to be a number").ThrowAsJavaScriptException();
            return;
        }
        Napi::Number x = point_obj.Get("x").As<Napi::Number>();
        Napi::Number y = point_obj.Get("y").As<Napi::Number>();
        position = CGPointMake(x, y);
    }
    else
    {
        Napi::TypeError::New(env, "No coordinate values provided").ThrowAsJavaScriptException();
        return;
    }

    this->mouse_->MouseDoubleClick(button, position);
}

void MouseWrap::Drag(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
        return;
    }

    Napi::Number first = info[0].As<Napi::Number>();
    Napi::Number second = info[1].As<Napi::Number>();
    CGPoint position = CGPointMake(first.FloatValue(), second.FloatValue());

    this->mouse_->MouseDrag(position);
}

void MouseWrap::StartDrag(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
        return;
    }

    Napi::Number x = info[0].As<Napi::Number>();
    Napi::Number y = info[1].As<Napi::Number>();
    CGPoint position = CGPointMake(x.FloatValue(), y.FloatValue());

    this->mouse_->MouseStartDrag(position);
}

void MouseWrap::EndDrag(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
        return;
    }

    Napi::Number x = info[0].As<Napi::Number>();
    Napi::Number y = info[1].As<Napi::Number>();
    CGPoint position = CGPointMake(x.FloatValue(), y.FloatValue());

    this->mouse_->MouseEndDrag(position);
}
