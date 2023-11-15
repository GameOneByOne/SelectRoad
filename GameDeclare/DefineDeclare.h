#pragma once

#define DECLARE_SINGLETON(T) \
    public: static T &GetInstance() { static T ins; return ins; }


#define INIT_ONCE_BEGIN(T) \
    static bool init = false;\
    static T object; \
    if (init) { return object; }

#define INIT_ONCE_END() init = true;