/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich and Daniel Malasky
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;
class TestLander;

/************************************
 * ANGLE
 ************************************/
class Angle
{
public:
    friend TestAcceleration;
    friend TestVelocity;
    friend TestAngle;
    friend TestLander;

    // Constructors
    Angle() : radians(0.0) {}
    Angle(const Angle& rhs) : radians(rhs.radians) {}
    Angle(double degrees) : radians((2 * M_PI)* (degrees / 360)) {}

    // Getters
    double getDegrees() const { return (radians / (2 * M_PI)) * 360; }
    double getRadians() const { return radians; } // Matt Benson put the return radians to get a test to pass in acceleration. :)

    // Setters
    void setDegrees(double degrees);
    void setRadians(double radians);
    void setUp() { this->radians = 0.0; }
    void setDown() { this->radians = M_PI; }
    void setRight() { this->radians = M_PI_2; }
    void setLeft() { this->radians = M_PI + M_PI_2; }
    void reverse() { this->radians += M_PI; }
    Angle& add(double delta);

private:
    double normalize(double radians) const;

    double radians;   // 360 degrees equals 2 PI radians
};