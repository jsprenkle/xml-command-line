#define VERSION "@VERSION@"
#define BUILD "@BUILD@"
#define PACKAGE_NAME "@CMAKE_PROJECT_NAME@"

#ifndef INLINE
#if defined(__MINGW32__)
#define INLINE
#elif defined(__GNUC__)
#define INLINE __attribute__((always_inline))
#elif defined(_MSC_VER)
#define INLINE __forceinline
#else
#define INLINE
#endif
#endif

