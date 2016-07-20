#ifndef QUADKEYMACROS_H_INCLUDED
#define QUADKEYMACROS_H_INCLUDED

#include <cstring>

#if defined (_MSC_VER) && (_MSC_VER <= 1800)
    #define snprintf _snprintf
    #define strdup _strdup
#endif

#endif
