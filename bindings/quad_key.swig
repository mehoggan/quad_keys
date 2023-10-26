#if defined(SWIGPYTHON)
%module quad_key
#elif defined(SWIGJAVA)
%module quad_key_java
#endif

%{
#include "quad_key/quad_key.h"
%}

%include "operators.i"

%include <stdint.i>
%include <std_string.i>

%include "quad_keys/geo_coordinate2d.h"
%include "quad_keys/geo_coordinate_bounding_box2d.h"
%include "quad_keys/quad_key_types.h"

%rename(GeoCoordinate2d) QuadKeys::GeoCoordinate2d;

%include "quad_keys/quad_key.h"

%include <std_vector.i>
%template(QuadKeysVector) std::vector<quad_keys::QuadKey>;

