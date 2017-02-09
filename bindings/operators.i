%module OperatorOverload
#pragma SWIG nowarn=503,362

#if defined(SWIGJAVA)
  %rename(assign_longitude) quad_keys::longitude::operator=;
  %rename(less_than) quad_keys::longitude::operator<;
  %rename(less_than_or_equal) quad_keys::longitude::operator<=;
  %rename(greater_than) quad_keys::longitude::operator>;
  %rename(greater_than_or_equal) quad_keys::longitude::operator>=;
  %rename(equal_to) quad_keys::longitude::operator==;
  %rename(not_equal_to) quad_keys::longitude::operator!=;
  %rename(longitude_difference) quad_keys::longitude::operator-;

  %rename(assign_latitude) quad_keys::latitude::operator=;
  %rename(less_than) quad_keys::latitude::operator<;
  %rename(less_than_or_equal) quad_keys::latitude::operator<=;
  %rename(greater_than) quad_keys::latitude::operator>;
  %rename(greater_than_or_equal) quad_keys::latitude::operator>=;
  %rename(equal_to) quad_keys::latitude::operator==;
  %rename(not_equal_to) quad_keys::latitude::operator!=;
  %rename(latitude_difference) quad_keys::latitude::operator-;

  %rename(assign_geo_coordinate2d) quad_keys::geo_coordinate2d::operator=;
  %rename(equal_to) quad_keys::geo_coordinate2d::operator==;
  %rename(notEqualTo) quad_keys::geo_coordinate2d::operator!=;

  %rename(assignquad_key) quad_keys::quad_key::operator=;
  %rename(less_than) quad_keys::quad_key::operator<;
  %rename(equal_to) quad_keys::quad_key::operator==;
  %rename(not_equal_to) quad_keys::quad_key::operator!=;
#endif

#if defined(SWIGPYTHON)
  %rename(__lt__) quad_keys::longitude::operator<;
  %rename(__le__) quad_keys::longitude::operator<=;
  %rename(__gt__) quad_keys::longitude::operator>;
  %rename(__ge__) quad_keys::longitude::operator>=;
  %rename(__eq__) quad_keys::longitude::operator==;
  %rename(__ne__) quad_keys::longitude::operator!=;
  %rename(__sub__) quad_keys::longitude::operator-;

  %rename(__lt__) quad_keys::latitude::operator<;
  %rename(__le__) quad_keys::latitude::operator<=;
  %rename(__gt__) quad_keys::latitude::operator>;
  %rename(__ge__) quad_keys::latitude::operator>=;
  %rename(__eq__) quad_keys::latitude::operator==;
  %rename(__ne__) quad_keys::latitude::operator!=;
  %rename(__sub__) quad_keys::latitude::operator-;

  %rename(__eq__) quad_keys::GeoCoordinate2d::operator==;
  %rename(__ne__) quad_keys::GeoCoordinate2d::operator!=;

  %rename(__lt__) quad_keys::quad_key::operator<;
  %rename(__eq__) quad_keys::quad_key::operator==;
  %rename(__ne__) quad_keys::quad_key::operator!=;
#endif
