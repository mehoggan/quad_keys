#ifndef GEOCOORDINATEBOUNDINGBOX2D_H_INCLUDED
#define GEOCOORDINATEBOUNDINGBOX2D_H_INCLUDED

#include "declspec.h"

#include "QuadKey/GeoCoordinate2d.h"

namespace QuadKeys
{
    class DLLSPEC_QUADKEY GeoCoordinateBoundingBox2d
    {
    private:
        GeoCoordinate2d m_LowerLeft;
        GeoCoordinate2d m_UpperRight;

    public:
        GeoCoordinateBoundingBox2d();

        GeoCoordinateBoundingBox2d(
            const GeoCoordinate2d &coordinate0,
            const GeoCoordinate2d &coordinate1);

        bool contains(const GeoCoordinate2d &coordinate) const;
        void growToContain(const GeoCoordinate2d &coordinate);

        const GeoCoordinate2d &lowerLeft() const {return m_LowerLeft;}
        const GeoCoordinate2d &upperRight() const {return m_UpperRight;}
        const GeoCoordinate2d upperLeft() const
        {
            return GeoCoordinate2d(m_LowerLeft.longitude(),
                m_UpperRight.latitude());
        }
        const GeoCoordinate2d lowerRight() const
        {
            return GeoCoordinate2d(m_UpperRight.longitude(),
                m_LowerLeft.latitude());
        }
        bool operator==(const GeoCoordinateBoundingBox2d &rhs) const
        {
            return (m_LowerLeft == rhs.m_LowerLeft &&
                m_UpperRight == rhs.m_UpperRight);
        }
        friend std::ostream &operator<<(std::ostream &out,
            const GeoCoordinateBoundingBox2d &obj)
        {
            return out << "[" << obj.m_LowerLeft << "," << obj.m_UpperRight <<
                "]";
        }

        bool isValid() const;
    };
}
#endif
