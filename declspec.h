#if defined (WIN32) || defined (_WIN32) || defined (__WIN32__) || \
    defined(__CYGWIN__) || defined(__MINGW32__)
    #if defined(QUADKEY_SHARED)
        #if defined(QUADKEY_EXPORTS)
            #define DLLSPEC_QUADKEY __declspec(dllexport)
        #else
            #define DLLSPEC_QUADKEY __declspec(dllimport)
        #endif
    #elif defined(QUADKEY_STATIC)
        #define DLLSPEC_QUADKEY
    #else
        #define DLLSPEC_QUADKEY
    #endif
#else
    #define DLLSPEC_QUADKEY
#endif
