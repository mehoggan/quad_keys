%module OperatorOverload
#pragma SWIG nowarn=503,362

#if defined(SWIGJAVA)
  %rename(assignLongitude) quad_keys::Longitude::operator=;
  %rename(lessThan) quad_keys::Longitude::operator<;
  %rename(lessThanOrEqual) quad_keys::Longitude::operator<=;
  %rename(greaterThan) quad_keys::Longitude::operator>;
  %rename(greaterThanOrEqual) quad_keys::Longitude::operator>=;
  %rename(equalTo) quad_keys::Longitude::operator==;
  %rename(notEqualTo) quad_keys::Longitude::operator!=;
  %rename(longitudeDifference) quad_keys::Longitude::operator-;

  %rename(assignLatitude) quad_keys::Latitude::operator=;
  %rename(lessThan) quad_keys::Latitude::operator<;
  %rename(lessThanOrEqual) quad_keys::Latitude::operator<=;
  %rename(greaterThan) quad_keys::Latitude::operator>;
  %rename(greaterThanOrEqual) quad_keys::Latitude::operator>=;
  %rename(equalTo) quad_keys::Latitude::operator==;
  %rename(notEqualTo) quad_keys::Latitude::operator!=;
  %rename(latitudeDifference) quad_keys::Latitude::operator-;

  %rename(assignGeoCoordinate2d) quad_keys::geo_coordinate2d::operator=;
  %rename(equalTo) quad_keys::geo_coordinate2d::operator==;
  %rename(notEqualTo) quad_keys::geo_coordinate2d::operator!=;

  %rename(assignQuadKey) quad_keys::QuadKey::operator=;
  %rename(lessThan) quad_keys::QuadKey::operator<;
  %rename(equalTo) quad_keys::QuadKey::operator==;
  %rename(notEqualTo) quad_keys::QuadKey::operator!=;
#endif

#if defined(SWIGPYTHON)
  %rename(__lt__) quad_keys::Longitude::operator<;
  %rename(__le__) quad_keys::Longitude::operator<=;
  %rename(__gt__) quad_keys::Longitude::operator>;
  %rename(__ge__) quad_keys::Longitude::operator>=;
  %rename(__eq__) quad_keys::Longitude::operator==;
  %rename(__ne__) quad_keys::Longitude::operator!=;
  %rename(__sub__) quad_keys::Longitude::operator-;

  %rename(__lt__) quad_keys::Latitude::operator<;
  %rename(__le__) quad_keys::Latitude::operator<=;
  %rename(__gt__) quad_keys::Latitude::operator>;
  %rename(__ge__) quad_keys::Latitude::operator>=;
  %rename(__eq__) quad_keys::Latitude::operator==;
  %rename(__ne__) quad_keys::Latitude::operator!=;
  %rename(__sub__) quad_keys::Latitude::operator-;

  %rename(__eq__) quad_keys::GeoCoordinate2d::operator==;
  %rename(__ne__) quad_keys::GeoCoordinate2d::operator!=;

  %rename(__lt__) quad_keys::QuadKey::operator<;
  %rename(__eq__) quad_keys::QuadKey::operator==;
  %rename(__ne__) quad_keys::QuadKey::operator!=;
#endif
