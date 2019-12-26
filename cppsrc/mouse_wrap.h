#include <napi.h>
#include "mouse.h"

namespace mousecontroller
{
class MouseWrap : public Napi::ObjectWrap<MouseWrap>
{
public:
    static Napi::Object Init(Napi::Env env,
                             Napi::Object exports);
    MouseWrap(const Napi::CallbackInfo &info);

private:
    static Napi::FunctionReference
        constructor;
    Napi::Value GetPosition(const Napi::CallbackInfo &info);
    void Move(const Napi::CallbackInfo &info);
    void MouseUp(const Napi::CallbackInfo &info);
    void MouseDown(const Napi::CallbackInfo &info);
    void Click(const Napi::CallbackInfo &info);
    void DoubleClick(const Napi::CallbackInfo &info);
    void Drag(const Napi::CallbackInfo &info);
    void StartDrag(const Napi::CallbackInfo &info);
    void EndDrag(const Napi::CallbackInfo &info);
    Mouse *mouse_;
};
} // namespace mousecontroller
