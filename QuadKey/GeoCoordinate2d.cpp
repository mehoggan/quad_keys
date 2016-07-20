#include "QuadKey/GeoCoordinate2d.h"

namespace QuadKeys
{
    const double Longitude::minLongitude = -180.0;
    const double Longitude::maxLongitude = 180.0;
    const double Latitude::minLatitude = -90.0;
    const double Latitude::maxLatitude = 90.0;

    Longitude::Longitude(double val) :
        m_Val(std::max(std::min(maxLongitude, val), minLongitude))
    {}

    Longitude::Longitude(const Longitude &other) :
        m_Val(other.m_Val)
    {}

    Longitude &Longitude::operator=(const Longitude &rhs)
    {
        m_Val = rhs.m_Val;

        return (*this);
    }

    bool Longitude::near(const Longitude &other,
        const double eps) const
    {
        const double diff = std::fabs(m_Val - other.m_Val);
        return (diff <= eps);
    }

    Latitude::Latitude(double val) :
        m_Val(std::max(std::min(maxLatitude, val), minLatitude))
    {}

    Latitude::Latitude(const Latitude &other) :
        m_Val(other.m_Val)
    {}

    Latitude &Latitude::operator=(const Latitude &rhs)
    {
        m_Val = rhs.m_Val;

        return (*this);
    }

    bool Latitude::near(const Latitude &other,
        const double eps) const
    {
        const double diff = std::fabs(m_Val - other.m_Val);
        return (diff <= eps);
    }

    GeoCoordinate2d::GeoCoordinate2d() :
        m_Longitude(0.0),
        m_Latitude(0.0)
    {}

    GeoCoordinate2d::GeoCoordinate2d(const GeoCoordinate2d &other) :
        m_Longitude(other.m_Longitude),
        m_Latitude(other.m_Latitude)
    {}

    GeoCoordinate2d &GeoCoordinate2d::operator=(const GeoCoordinate2d &rhs)
    {
         m_Longitude = rhs.m_Longitude;
         m_Latitude = rhs.m_Latitude;

         return (*this);
    }

    GeoCoordinate2d::GeoCoordinate2d(const Longitude &longitude,
        const Latitude &latitude) :
        m_Longitude(longitude),
        m_Latitude(latitude)
    {}

    bool GeoCoordinate2d::near(const GeoCoordinate2d &other,
        const double eps) const
    {
        return m_Latitude.near(other.m_Latitude, eps) &&
            m_Longitude.near(other.m_Longitude, eps);
    }
};
