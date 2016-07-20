#if defined(SWIGPYTHON)
%module quadkey
#elif defined(SWIGJAVA)
%module SwigQuadKey
#elif defined(SWIGCSHARP)
%module SwigQuadKey
#endif

%{
#include "QuadKey/QuadKey.h"
%}

%include "operators.i"

%include <stdint.i>
%include <std_string.i>

%include "declspec.h"

%include "QuadKey/GeoCoordinate2d.h"
%include "QuadKey/GeoCoordinateBoundingBox2d.h"
%include "QuadKey/QuadKeyTypes.h"

%rename(GeoCoordinate2d) QuadKeys::GeoCoordinate2d;

%include "QuadKey/QuadKey.h"

%include <std_vector.i>
%template(QuadKeyVector) std::vector<QuadKeys::QuadKey>;

