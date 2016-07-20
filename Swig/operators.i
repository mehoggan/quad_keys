%module OperatorOverload
#pragma SWIG nowarn=503,362

#if defined(SWIGJAVA)
    %rename(assignLongitude) QuadKeys::Longitude::operator=;
    %rename(lessThan) QuadKeys::Longitude::operator<;
    %rename(lessThanOrEqual) QuadKeys::Longitude::operator<=;
    %rename(greaterThan) QuadKeys::Longitude::operator>;
    %rename(greaterThanOrEqual) QuadKeys::Longitude::operator>=;
    %rename(equalTo) QuadKeys::Longitude::operator==;
    %rename(notEqualTo) QuadKeys::Longitude::operator!=;
    %rename(longitudeDifference) QuadKeys::Longitude::operator-;

    %rename(assignLatitude) QuadKeys::Latitude::operator=;
    %rename(lessThan) QuadKeys::Latitude::operator<;
    %rename(lessThanOrEqual) QuadKeys::Latitude::operator<=;
    %rename(greaterThan) QuadKeys::Latitude::operator>;
    %rename(greaterThanOrEqual) QuadKeys::Latitude::operator>=;
    %rename(equalTo) QuadKeys::Latitude::operator==;
    %rename(notEqualTo) QuadKeys::Latitude::operator!=;
    %rename(latitudeDifference) QuadKeys::Latitude::operator-;

    %rename(assignGeoCoordinate2d) QuadKeys::GeoCoordinate2d::operator=;
    %rename(equalTo) QuadKeys::GeoCoordinate2d::operator==;
    %rename(notEqualTo) QuadKeys::GeoCoordinate2d::operator!=;

    %rename(assignQuadKey) QuadKeys::QuadKey::operator=;
    %rename(lessThan) QuadKeys::QuadKey::operator<;
    %rename(equalTo) QuadKeys::QuadKey::operator==;
    %rename(notEqualTo) QuadKeys::QuadKey::operator!=;
#endif

#if defined(SWIGPYTHON)
    %rename(__lt__) QuadKeys::Longitude::operator<;
    %rename(__le__) QuadKeys::Longitude::operator<=;
    %rename(__gt__) QuadKeys::Longitude::operator>;
    %rename(__ge__) QuadKeys::Longitude::operator>=;
    %rename(__eq__) QuadKeys::Longitude::operator==;
    %rename(__ne__) QuadKeys::Longitude::operator!=;
    %rename(__sub__) QuadKeys::Longitude::operator-;

    %rename(__lt__) QuadKeys::Latitude::operator<;
    %rename(__le__) QuadKeys::Latitude::operator<=;
    %rename(__gt__) QuadKeys::Latitude::operator>;
    %rename(__ge__) QuadKeys::Latitude::operator>=;
    %rename(__eq__) QuadKeys::Latitude::operator==;
    %rename(__ne__) QuadKeys::Latitude::operator!=;
    %rename(__sub__) QuadKeys::Latitude::operator-;

    %rename(__eq__) QuadKeys::GeoCoordinate2d::operator==;
    %rename(__ne__) QuadKeys::GeoCoordinate2d::operator!=;

    %rename(__lt__) QuadKeys::QuadKey::operator<;
    %rename(__eq__) QuadKeys::QuadKey::operator==;
    %rename(__ne__) QuadKeys::QuadKey::operator!=;
#endif

#if defined(SWIGCSHARP)
    %rename(AssignLongitude) QuadKeys::Longitude::operator=;
    %rename(LessThan) QuadKeys::Longitude::operator<;
    %rename(LessThanOrEqual) QuadKeys::Longitude::operator<=;
    %rename(GreaterThan) QuadKeys::Longitude::operator>;
    %rename(GreaterThanOrEqual) QuadKeys::Longitude::operator>=;
    %rename(EqualTo) QuadKeys::Longitude::operator==;
    %rename(NotEqualTo) QuadKeys::Longitude::operator!=;
    %rename(LongitudeDifference) QuadKeys::Longitude::operator-;

    %rename(AssignLatitude) QuadKeys::Latitude::operator=;
    %rename(LessThan) QuadKeys::Latitude::operator<;
    %rename(LessThanOrEqual) QuadKeys::Latitude::operator<=;
    %rename(GreaterThan) QuadKeys::Latitude::operator>;
    %rename(GreaterThanOrEqual) QuadKeys::Latitude::operator>=;
    %rename(EqualTo) QuadKeys::Latitude::operator==;
    %rename(NotEqualTo) QuadKeys::Latitude::operator!=;
    %rename(LatitudeDifference) QuadKeys::Latitude::operator-;

    %rename(AssignGeoCoordinate2d) QuadKeys::GeoCoordinate2d::operator=;
    %rename(EqualTo) QuadKeys::GeoCoordinate2d::operator==;
    %rename(NotEqualTo) QuadKeys::GeoCoordinate2d::operator!=;

    %rename(AssignQuadKey) QuadKeys::QuadKey::operator=;
    %rename(LessThan) QuadKeys::QuadKey::operator<;
    %rename(EqualTo) QuadKeys::QuadKey::operator==;
    %rename(NotEqualTo) QuadKeys::QuadKey::operator!=;;
#endif
