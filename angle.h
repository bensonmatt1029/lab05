/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Matt Benson
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

/************************************
 * ANGLE
 ************************************/
class Angle
{
public:
   friend TestPosition;
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;

   // Constructors
   Angle() : radians(0.0) {}
   Angle(const Angle& rhs) : radians(rhs.radians) {}
   Angle(double degrees) : radians((2 * M_PI)* (degrees / 360)) {}

   // Getters
   double getDegrees() const { return (radians / (2 * M_PI)) * 360; }
   double getRadians() const { return radians; }

   // Setters
   void setDxDy(double dx, double dy);
   void setDegrees(double degrees);
   void setRadians(double radians);
   void setUp() { this->radians = 0.0; }
   void setDown() { this->radians = M_PI; }
   void setRight() { this->radians = M_PI_2; }
   void setLeft() { this->radians = M_PI + M_PI_2; }
   void reverse() { this->radians += M_PI; }
   Angle& add(double delta);
   void rotate(double amount)
   {
      radians += amount;
      if (radians > M_PI)
         radians -= 2.0 * M_PI;
      if (radians < -M_PI)
         radians += 2.0 * M_PI;
   }

protected:
   double normalize(double radians) const;

   double radians;   // 360 degrees equals 2 PI radians
};

/************************************
 * ANGLE NORTH
 ************************************/
class AngleNorth : public Angle
{
public:
   AngleNorth()
   {
      radians = 0.0;
   }
};

/************************************
 * ANGLE SOUTH
 ************************************/
class AngleSouth : public Angle
{
public:
   AngleSouth()
   {
      radians = M_PI;
   }
};

/************************************
 * ANGLE EAST
 ************************************/
class AngleEast : public Angle
{
public:
   AngleEast()
   {
      radians = M_PI / 2.0;
   }
};

/************************************
 * ANGLE WEST
 ************************************/
class AngleWest : public Angle
{
public:
   AngleWest()
   {
      radians = 3 * M_PI / 2.0;
   }
};