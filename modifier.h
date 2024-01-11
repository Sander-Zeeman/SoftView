#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define SOV_FUNCTION EMSCRIPTEN_KEEPALIVE
#elif _WIN32_
#define EMSCRIPTEN_KEEPALIVE
#if SOV_LIB_EXPORT
#define SOV_FUNCTION __declspec(dllexport)
#else
#define SOV_FUNCTION __declspec(dllimport)
#endif
#else
#define EMSCRIPTEN_KEEPALIVE
#define SOV_FUNCTION
#endif