#include "GeoCoordinateBoundingBox2d.h"

namespace QuadKeys
{
    GeoCoordinateBoundingBox2d::GeoCoordinateBoundingBox2d() :
        m_LowerLeft(Longitude(180.0), Latitude(90.0)),
        m_UpperRight(Longitude(-180.0), Latitude(-90.0))
    {}

    GeoCoordinateBoundingBox2d::GeoCoordinateBoundingBox2d(
        const GeoCoordinate2d &coordinate0,
        const GeoCoordinate2d &coordinate1) :
        m_LowerLeft(Longitude(180.0), Latitude(90.0)),
        m_UpperRight(Longitude(-180.0), Latitude(-90.0))
    {
        growToContain(coordinate0);
        growToContain(coordinate1);
    }

    bool GeoCoordinateBoundingBox2d::contains(
        const GeoCoordinate2d &coordinate) const
    {
        bool isIn = true;

        isIn &= isValid();
        isIn &= (coordinate.longitude() >= lowerLeft().longitude());
        isIn &= (coordinate.latitude() >= lowerLeft().latitude());
        isIn &= (coordinate.longitude() <= upperRight().longitude());
        isIn &= (coordinate.latitude() <= upperRight().latitude());

        return isIn;
    }

    void GeoCoordinateBoundingBox2d::growToContain(
        const GeoCoordinate2d &coordinate)
    {
        GeoCoordinate2d lowerLeft(
            std::min(m_LowerLeft.longitude(), coordinate.longitude()),
            std::min(m_LowerLeft.latitude(), coordinate.latitude()));
        GeoCoordinate2d upperRight(
            std::max(m_UpperRight.longitude(), coordinate.longitude()),
            std::max(m_UpperRight.latitude(), coordinate.latitude()));

        m_LowerLeft = lowerLeft;
        m_UpperRight = upperRight;
    }

    bool GeoCoordinateBoundingBox2d::isValid() const
    {
        bool valid = true;

        valid &= (m_LowerLeft.longitude() <= m_UpperRight.longitude());
        valid &= (m_LowerLeft.latitude() <= m_UpperRight.latitude());

        return valid;
    }
}
