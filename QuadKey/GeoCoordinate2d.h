#ifndef GEOCOORDINATE2D_H_INCLUDED
#define GEOCOORDINATE2D_H_INCLUDED

#include "declspec.h"

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdint>
#include <limits>
#include <ostream>
#include <type_traits>

namespace QuadKeys
{
    struct DLLSPEC_QUADKEY Longitude
    {
    public:
        static const double minLongitude;
        static const double maxLongitude;

    private:
        double m_Val;
        friend class GeoCoordinate2d;

    public:
        explicit Longitude(double val);

        /* Prevents C2280 attempting to reference a deleted function */
        Longitude(const Longitude &other);
        Longitude &operator=(const Longitude &rhs);

        double val() const { return m_Val; }

        bool near(const Longitude &other,
            const double eps = std::numeric_limits<double>::epsilon()) const;

        bool operator<(const Longitude &rhs) const
        {
            return m_Val < rhs.m_Val;
        }
        bool operator<=(const Longitude &rhs) const
        {
            return m_Val <= rhs.m_Val;
        }
        bool operator>(const Longitude &rhs) const
        {
            return !((*this) <= rhs);
        }
        bool operator>=(const Longitude &rhs) const
        {
            return !((*this) < rhs);
        }
        bool operator==(const Longitude &rhs) const
        {
            return m_Val == rhs.m_Val;
        }
        bool operator!=(const Longitude &rhs) const
        {
            return !((*this) == rhs);
        }
        double operator-(const Longitude &subtrahend) const
        {
            return (m_Val - subtrahend.m_Val);
        }
        friend std::ostream &operator<<(std::ostream &out, const Longitude &obj)
        {
            return out << obj.m_Val;
        }
    };

    struct DLLSPEC_QUADKEY Latitude
    {
    public:
        static const double minLatitude;
        static const double maxLatitude;

    private:
        double m_Val;
        friend class GeoCoordinate2d;

    public:
        explicit Latitude(double val);

        /* Prevents C2280 attempting to reference a deleted function */
        Latitude(const Latitude &other);
        Latitude &operator=(const Latitude &rhs);

        double val() const { return m_Val; }

        bool near(const Latitude &other,
            const double eps = std::numeric_limits<double>::epsilon()) const;

        bool operator<(const Latitude &rhs) const
        {
            return m_Val < rhs.m_Val;
        }
        bool operator<=(const Latitude &rhs) const
        {
            return m_Val <= rhs.m_Val;
        }
        bool operator>(const Latitude &rhs) const
        {
            return !((*this) <= rhs);
        }
        bool operator>=(const Latitude &rhs) const
        {
            return !((*this) < rhs);
        }
        bool operator==(const Latitude &rhs) const
        {
            return m_Val == rhs.m_Val;
        }
        bool operator!=(const Latitude &rhs) const
        {
            return !((*this) == rhs);
        }
        double operator-(const Latitude &subtrahend) const
        {
            return (m_Val - subtrahend.m_Val);
        }
        friend std::ostream &operator<<(std::ostream &out, const Latitude &obj)
        {
            return out << obj.m_Val;
        }
    };

    class DLLSPEC_QUADKEY GeoCoordinate2d
    {
    private:
        Longitude m_Longitude;
        Latitude m_Latitude;
        friend class GeoCoordinateBoundingBox2d;

    public:
        GeoCoordinate2d();

        GeoCoordinate2d(const Longitude &longitude, const Latitude &latitude);

        /* Prevents C2280 attempting to reference a deleted function */
        GeoCoordinate2d(const GeoCoordinate2d &other);
        GeoCoordinate2d &operator=(const GeoCoordinate2d &rhs);

        void longitude(double longitude) {m_Longitude = Longitude(longitude);}
        void latitude(double latitude) {m_Latitude = Latitude(latitude);}
        void longitude(const Longitude &longitude) {m_Longitude = longitude;}
        void latitude(const Latitude &latitude) {m_Latitude = latitude;}

        const Longitude &longitude() const {return m_Longitude;}
        const Latitude &latitude() const {return m_Latitude;}

        bool near(const GeoCoordinate2d &other,
            const double eps = std::numeric_limits<double>::epsilon()) const;

        inline bool operator==(const GeoCoordinate2d &rhs) const
        {
            return (m_Longitude == rhs.m_Longitude) &&
              (m_Latitude == rhs.m_Latitude);
        }

        inline bool operator!=(const GeoCoordinate2d &rhs) const
        {
            return !((*this) == rhs);
        }
        friend std::ostream &operator<<(std::ostream &out,
            const GeoCoordinate2d &obj)
        {
            return out << "(" << obj.m_Longitude << "," << obj.m_Latitude <<
                ")";
        }
    };
}
#endif
