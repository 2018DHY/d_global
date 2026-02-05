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
#ifdef DLIB_EXPORT
#define DLIB_API_EXPORT __declspec(dllexport)
#else
#define DLIB_API_EXPORT
#endif

#endif /* COMMOM */
