#ifndef COMMOM
#define COMMOM
#ifdef __cplusplus
#define EXTERN_C_BEGIN \
    extern "C"         \
    {
#define EXTERN_C_END }
#define INLINE inline
#else
#define EXTERN_C_BEGIN 
#define EXTERN_C_END 
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define INLINE inline
#else
#define INLINE
#endif
#endif
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) \
    || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define LIB_EXPORT __declspec(dllexport)
#define LIB_IMPORT __declspec(dllimport)
#else
#define LIB_EXPORT __attribute__((visibility("default")))
#define LIB_IMPORT __attribute__((visibility("default")))
#endif

#ifdef DLIB_EXPORT
#define DLIB_API LIB_EXPORT
#else
#define DLIB_API LIB_IMPORT
#endif

#endif /* COMMOM */
