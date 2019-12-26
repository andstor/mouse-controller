#include <napi.h>
#include "mouse_wrap.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
    return mousecontroller::MouseWrap::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll);
