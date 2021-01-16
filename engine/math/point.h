//
// Created by Diego Santos Seabra on 16/01/21.
//

#ifndef MAGICK_ENGINE_POINT_H
#define MAGICK_ENGINE_POINT_H

struct Point
{
    int x,y;

    Point();
    Point(int px, int py);
    ~Point();

    Point operator +(Point rhs) const;
    Point operator -(Point rhs) const;
    Point operator /(int rhs) const;
    Point operator *(int rhs) const;
    Point operator -() const;

    Point& operator +=(const Point& rhs);
    Point& operator -=(const Point& rhs);
    Point& operator /=(const Point& rhs);
    Point& operator *=(const Point& rhs);
    Point& operator /=(int rhs);
    Point& operator *=(int rhs);

    bool operator ==(const Point& rhs) const;
    bool operator !=(const Point& rhs) const;

    float length() const;
    int lengthSquared() const;

    static const Point unitX;
    static const Point unitY;
    static const Point right;
    static const Point up;
    static const Point down;
    static const Point left;
    static const Point zero;
    static const Point one;
};

#endif //MAGICK_ENGINE_POINT_H
